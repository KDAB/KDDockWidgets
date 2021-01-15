/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidgetBase.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "Utils_p.h"
#include "DockRegistry_p.h"
#include "DropArea_p.h"
#include "Config.h"
#include "TitleBar_p.h"
#include "FrameworkWidgetFactory.h"
#include "private/Position_p.h"
#include "WindowBeingDragged_p.h"
#include "SideBar_p.h"

#include <QEvent>
#include <QCloseEvent>
#include <QTimer>
#include <QScopedValueRollback>

/**
 * @file
 * @brief The DockWidget base-class that's shared between QtWidgets and QtQuick stack.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

using namespace KDDockWidgets;

class DockWidgetBase::Private
{
public:
    Private(const QString &dockName, DockWidgetBase::Options options_,
            LayoutSaverOptions layoutSaverOptions_, DockWidgetBase *qq)
        : name(dockName)
        , title(dockName)
        , q(qq)
        , options(options_)
        , layoutSaverOptions(layoutSaverOptions_)
        , toggleAction(new QAction(q))
        , floatAction(new QAction(q))
    {
        q->connect(toggleAction, &QAction::toggled, q, [this] (bool enabled) {
            if (!m_updatingToggleAction) { // guard against recursiveness
                toggleAction->blockSignals(true); // and don't emit spurious toggle. Like when a dock widget is inserted into a tab widget it might get hide events, ignore those. The Dock Widget is open.
                toggle(enabled);
                toggleAction->blockSignals(false);
            }
        });

        q->connect(floatAction, &QAction::toggled, q, [this] (bool checked) {
            if (!m_updatingFloatAction) { // guard against recursiveness
                q->setFloating(checked);
            }

            Q_EMIT q->isFloatingChanged(checked);
        });

        toggleAction->setCheckable(true);
        floatAction->setCheckable(true);
    }

    void init()
    {
        updateTitle();
    }

    FloatingWindow *floatingWindow() const
    {
        return qobject_cast<FloatingWindow*>(q->window());
    }

    MainWindowBase *mainWindow() const
    {
        if (q->isWindow())
            return nullptr;

        // Note: Don't simply use window(), as the MainWindow might be embedded into something else
        QWidgetOrQuick *p = q->parentWidget();
        while (p) {
            if (auto window = qobject_cast<MainWindowBase*>(p))
                return window;

            if (p->isWindow())
                return nullptr;

            p = p->parentWidget();
        }

        return nullptr;
    }

    SideBar* sideBar() const
    {
        return DockRegistry::self()->sideBarForDockWidget(q);
    }

    QPoint defaultCenterPosForFloating();

    void updateTitle();
    void toggle(bool enabled);
    void updateToggleAction();
    void updateFloatAction();
    void onDockWidgetShown();
    void onDockWidgetHidden();
    void show();
    void close();
    bool restoreToPreviousPosition();
    void maybeRestoreToPreviousPosition();
    int currentTabIndex() const;

    /**
     * Before floating a dock widget we save its position. So it can be restored when calling
     * DockWidget::setFloating(false)
     */
    void saveTabIndex();

    const QString name;
    QStringList affinities;
    QString title;
    QIcon titleBarIcon;
    QIcon tabBarIcon;
    QWidgetOrQuick *widget = nullptr;
    DockWidgetBase *const q;
    DockWidgetBase::Options options;
    const LayoutSaverOptions layoutSaverOptions;
    QAction *const toggleAction;
    QAction *const floatAction;
    LastPositions m_lastPositions;
    bool m_updatingToggleAction = false;
    bool m_updatingFloatAction = false;
    bool m_isForceClosing = false;
    QSize m_lastOverlayedSize = QSize(0, 0);
};

DockWidgetBase::DockWidgetBase(const QString &name, Options options,
                               LayoutSaverOptions layoutSaverOptions)
    : QWidgetAdapter(nullptr, Qt::Tool)
    , d(new Private(name, options, layoutSaverOptions, this))
{
    d->init();
    DockRegistry::self()->registerDockWidget(this);

    if (name.isEmpty())
        qWarning() << Q_FUNC_INFO << "Name can't be null";

    setAttribute(Qt::WA_PendingMoveEvent, false);
    qApp->installEventFilter(this);
}

DockWidgetBase::~DockWidgetBase()
{
    DockRegistry::self()->unregisterDockWidget(this);
    delete d;
}

void DockWidgetBase::addDockWidgetAsTab(DockWidgetBase *other, InitialOption option)
{
    if (other == this) {
        qWarning() << Q_FUNC_INFO << "Refusing to add dock widget into itself" << other;
        return;
    }

    if (!other) {
        qWarning() << Q_FUNC_INFO << "dock widget is null";
        return;
    }

    if (!DockRegistry::self()->affinitiesMatch(other->affinities(), d->affinities)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << other->affinities() << affinities();
        return;
    }

    if ((other->options() & DockWidgetBase::Option_NotDockable) ||
        (options() & DockWidgetBase::Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    Frame *frame = this->frame();

    if (frame) {
        if (frame->containsDockWidget(other)) {
            qWarning() << Q_FUNC_INFO << "Already contains" << other;
            return;
        }
    } else {
        if (isWindow()) {
            // Doesn't have a frame yet
            morphIntoFloatingWindow();
            frame = this->frame();
        } else {
            // Doesn't happen
            qWarning() << Q_FUNC_INFO << "null frame";
            return;
        }
    }

    other->setParent(nullptr);
    frame->addWidget(other, option);
}

void DockWidgetBase::addDockWidgetToContainingWindow(DockWidgetBase *other,
                                                     Location location,
                                                     DockWidgetBase *relativeTo,
                                                     InitialOption initialOption)
{
    if (auto mainWindow = qobject_cast<MainWindowBase*>(window())) {
        // It's inside a main window. Simply use the main window API.
        mainWindow->addDockWidget(other, location, relativeTo, initialOption);
        return;
    }

    if (!DockRegistry::self()->affinitiesMatch(other->affinities(), d->affinities)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << other->affinities() << affinities();
        return;
    }

    if ((other->options() & DockWidgetBase::Option_NotDockable) ||
        (options() & DockWidgetBase::Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    if (isWindow())
        morphIntoFloatingWindow();

    if (auto fw = floatingWindow()) {
        fw->dropArea()->addDockWidget(other, location, relativeTo, initialOption);
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find floating nested window";
    }
}

void DockWidgetBase::setWidget(QWidgetOrQuick *w)
{
    Q_ASSERT(w);
    if (w == d->widget)
        return;

    if (d->widget) {
        // Unparent the old widget, we're giving back ownership
        d->widget->setParent(nullptr);
    }

    d->widget = w;
    if (w)
        setSizePolicy(w->sizePolicy());

    Q_EMIT widgetChanged(w);
    setWindowTitle(uniqueName());
}

QWidgetOrQuick *DockWidgetBase::widget() const
{
    return d->widget;
}

bool DockWidgetBase::isFloating() const
{
    if (isWindow())
        return true;

    auto fw = floatingWindow();
    return fw && fw->hasSingleDockWidget();
}

bool DockWidgetBase::setFloating(bool floats)
{
    const bool alreadyFloating = isFloating();

    if ((floats && alreadyFloating) || (!floats && !alreadyFloating))
        return true; // Nothing to do

    if (!floats && (Config::self().internalFlags() & Config::InternalFlag_DontShowWhenUnfloatingHiddenWindow) && !isVisible()) {
        // Mimics behaviour of QDockWidget, which you might need during porting.
        // Not something we suggest though. For KDDW, setFloating(false) means dock, and that implies showing.
        return false;
    }

    if (floats) {
        d->saveTabIndex();
        if (isTabbed()) {
            auto frame = this->frame();
            if (!frame) {
                qWarning() << "DockWidget::setFloating: Tabbed but no frame exists"
                           << this;
                Q_ASSERT(false);
                return false;
            }

            frame->detachTab(this);
        } else {
            frame()->titleBar()->makeWindow();
        }

        auto lastGeo = lastPositions().lastFloatingGeometry();
        if (lastGeo.isValid()) {
            if (auto fw = floatingWindow())
                fw->setSuggestedGeometry(lastGeo, /*preserveCenter=*/true);
        }
        return true;
    } else {
        saveLastFloatingGeometry();
        return d->restoreToPreviousPosition();
    }
}

QAction *DockWidgetBase::toggleAction() const
{
    return d->toggleAction;
}

QAction *DockWidgetBase::floatAction() const
{
    return d->floatAction;
}

QString DockWidgetBase::uniqueName() const
{
    return d->name;
}

QString DockWidgetBase::title() const
{
    return d->title;
}

void DockWidgetBase::setTitle(const QString &title)
{
    if (title != d->title) {
        d->title = title;
        d->updateTitle();
        Q_EMIT titleChanged(title);
    }
}

DockWidgetBase::Options DockWidgetBase::options() const
{
    return d->options;
}

DockWidgetBase::LayoutSaverOptions DockWidgetBase::layoutSaverOptions() const
{
    return d->layoutSaverOptions;
}

void DockWidgetBase::setOptions(Options options)
{
    if ((d->options & Option_NotDockable) != (options & Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Option_NotDockable not allowed to change. Pass via ctor only.";
        return;
    }

    if (options != d->options) {
        d->options = options;
        Q_EMIT optionsChanged(options);
        if (auto tb = titleBar())
            tb->updateButtons();
    }
}

bool DockWidgetBase::isTabbed() const
{
    if (Frame *frame = this->frame()) {
        return frame->alwaysShowsTabs() || frame->dockWidgetCount() > 1;
    } else {
        if (!isFloating())
            qWarning() << "DockWidget::isTabbed() Couldn't find any tab widget.";
        return false;
    }
}

bool DockWidgetBase::isCurrentTab() const
{
    if (Frame *frame = this->frame()) {
        return frame->currentIndex() == frame->indexOfDockWidget(const_cast<DockWidgetBase*>(this));
    } else {
        return true;
    }
}

void DockWidgetBase::setAsCurrentTab()
{
    if (Frame *frame = this->frame())
        frame->setCurrentDockWidget(this);
}

void DockWidgetBase::setIcon(const QIcon &icon, IconPlaces places)
{
    if (places & IconPlace::TitleBar)
        d->titleBarIcon = icon;

    if (places & IconPlace::TabBar)
        d->tabBarIcon = icon;

    if (places & IconPlace::ToggleAction)
        d->toggleAction->setIcon(icon);

    Q_EMIT iconChanged();
}

QIcon DockWidgetBase::icon(IconPlace place) const
{
    if (place == IconPlace::TitleBar)
        return d->titleBarIcon;

    if (place == IconPlace::TabBar)
        return d->tabBarIcon;

    if (place == IconPlace::ToggleAction)
        return d->toggleAction->icon();

    return {};
}

void DockWidgetBase::forceClose()
{
    QScopedValueRollback<bool> rollback(d->m_isForceClosing, true);
    d->close();
}

TitleBar *DockWidgetBase::titleBar() const
{
    if (Frame *f = frame())
        return f->actualTitleBar();

    return nullptr;
}

bool DockWidgetBase::isOpen() const
{
    return d->toggleAction->isChecked();
}

QStringList DockWidgetBase::affinities() const
{
    return d->affinities;
}

void DockWidgetBase::show()
{
    if (isWindow() && (d->m_lastPositions.wasFloating() || !d->m_lastPositions.isValid())) {
        // Create the FloatingWindow already, instead of waiting for the show event.
        // This reduces flickering on some platforms
        morphIntoFloatingWindow();
    } else {
        QWidgetOrQuick::show();
    }
}

void DockWidgetBase::raise()
{
    if (!isOpen())
        return;

    setAsCurrentTab();

    if (auto fw = floatingWindow()) {
        fw->raise();
        fw->activateWindow();
    }
}

bool DockWidgetBase::isMainWindow() const
{
    return qobject_cast<MainWindowBase*>(widget());
}

bool DockWidgetBase::isInMainWindow() const
{
    return d->mainWindow() != nullptr;
}

MainWindowBase* DockWidgetBase::mainWindow() const
{
    return d->mainWindow();
}

bool DockWidgetBase::isFocused() const
{
    auto f = this->frame();
    return f && f->isFocused() && isCurrentTab();
}

void DockWidgetBase::setAffinityName(const QString &affinity)
{
    setAffinities({ affinity });
}

void DockWidgetBase::setAffinities(const QStringList &affinityNames)
{
    QStringList affinities = affinityNames;
    affinities.removeAll(QString());

    if (d->affinities == affinities)
        return;

    if (!d->affinities.isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Affinity is already set, refusing to change."
                   << "Submit a feature request with a good justification.";
        return;
    }

    d->affinities = affinities;
}

void DockWidgetBase::moveToSideBar()
{
    if (MainWindowBase *m = mainWindow())
        m->moveToSideBar(this);
}

bool DockWidgetBase::isOverlayed() const
{
    if (MainWindowBase *m = mainWindow())
        return m->overlayedDockWidget() == this;

    return false;
}

SideBarLocation DockWidgetBase::sideBarLocation() const
{
    return DockRegistry::self()->sideBarLocationForDockWidget(this);
}

bool DockWidgetBase::isInSideBar() const
{
    return sideBarLocation() != SideBarLocation::None;
}

bool DockWidgetBase::hasPreviousDockedLocation() const
{
    return d->m_lastPositions.isValid();
}

QSize DockWidgetBase::lastOverlayedSize() const
{
    return d->m_lastOverlayedSize;
}

DockWidgetBase *DockWidgetBase::byName(const QString &uniqueName)
{
    return DockRegistry::self()->dockByName(uniqueName);
}

bool DockWidgetBase::skipsRestore() const
{
    return d->layoutSaverOptions & LayoutSaverOption::Skip;
}

FloatingWindow *DockWidgetBase::morphIntoFloatingWindow()
{
    if (auto fw = floatingWindow())
        return fw; // Nothing to do

    if (isWindow()) {
        QRect geo = d->m_lastPositions.lastFloatingGeometry();
        if (geo.isNull()) {
            geo = geometry();

            if (!testAttribute(Qt::WA_PendingMoveEvent)) { // If user already moved it, we don't interfere
                const QPoint center = d->defaultCenterPosForFloating();
                if (!center.isNull())
                    geo.moveCenter(center);
            }
        }

        auto frame = Config::self().frameworkWidgetFactory()->createFrame();
        frame->addWidget(this);
        auto floatingWindow = Config::self().frameworkWidgetFactory()->createFloatingWindow(frame);
        floatingWindow->setSuggestedGeometry(geo);
        floatingWindow->show();

        return floatingWindow;
    } else {
        return nullptr;
    }
}

void DockWidgetBase::maybeMorphIntoFloatingWindow()
{
    if (isWindow() && isVisible())
        morphIntoFloatingWindow();
}

Frame *DockWidgetBase::frame() const
{
    QWidgetOrQuick *p = parentWidget();
    while (p) {
        if (auto frame = qobject_cast<Frame *>(p))
            return frame;
        p = p->parentWidget();
    }
    return nullptr;
}

FloatingWindow *DockWidgetBase::floatingWindow() const
{
    return d->floatingWindow();
}

void DockWidgetBase::addPlaceholderItem(Layouting::Item *item)
{
    Q_ASSERT(item);
    d->m_lastPositions.addPosition(item);
}

LastPositions& DockWidgetBase::lastPositions() const
{
    return d->m_lastPositions;
}

void DockWidgetBase::saveLastFloatingGeometry()
{
    if (isFloating() && isVisible()) {
        // It's getting docked, save last floating position
        lastPositions().setLastFloatingGeometry(window()->geometry());
    }
}

void DockWidgetBase::updateFloatAction()
{
    d->updateFloatAction();
}

bool DockWidgetBase::eventFilter(QObject *watched, QEvent *event)
{
    const bool isWindowActivate = event->type() == QEvent::WindowActivate;
    const bool isWindowDeactivate = event->type() == QEvent::WindowDeactivate;
    if ((isWindowActivate || isWindowDeactivate) && watched == window())
        Q_EMIT windowActiveAboutToChange(isWindowActivate);

    return QWidgetAdapter::eventFilter(watched, event);
}

QPoint DockWidgetBase::Private::defaultCenterPosForFloating()
{
    MainWindowBase::List mainWindows = DockRegistry::self()->mainwindows();
    // We don't care about multiple mainwindows yet. Or, let's just say that the first one is more main than the others
    MainWindowBase *mw = mainWindows.isEmpty() ? nullptr : mainWindows.constFirst();
    if (!mw || !q->isFloating())
        return {};

    return mw->geometry().center();
}

void DockWidgetBase::Private::updateTitle()
{
    if (q->isFloating())
        q->window()->setWindowTitle(title);


    toggleAction->setText(title);
}

void DockWidgetBase::Private::toggle(bool enabled)
{
    if (SideBar *sb = sideBar()) {
        // The widget is in the sidebar, let's toggle its overlayed state
        sb->toggleOverlay(q);
    } else {
        // The most common case. The dock widget is not in the sidebar. just close or open it.
        if (enabled) {
            show();
        } else {
            q->close();
        }
    }
}

void DockWidgetBase::Private::updateToggleAction()
{
    QScopedValueRollback<bool> recursionGuard(m_updatingToggleAction, true); // Guard against recursiveness
    m_updatingToggleAction = true;
    if ((q->isVisible() || q->frame()) && !toggleAction->isChecked()) {
        toggleAction->setChecked(true);
    } else if ((!q->isVisible() && !q->frame()) && toggleAction->isChecked()) {
        toggleAction->setChecked(false);
    }
}

void DockWidgetBase::Private::updateFloatAction()
{
    QScopedValueRollback<bool> recursionGuard(m_updatingFloatAction, true); // Guard against recursiveness

    if (q->isFloating()) {
        floatAction->setEnabled(m_lastPositions.isValid());
        floatAction->setChecked(true);
        floatAction->setToolTip(tr("Dock"));
    } else {
        floatAction->setEnabled(true);
        floatAction->setChecked(false);
        floatAction->setToolTip(tr("Detach"));
    }
}

void DockWidgetBase::Private::onDockWidgetShown()
{
    updateToggleAction();
    updateFloatAction();
}

void DockWidgetBase::Private::onDockWidgetHidden()
{
    updateToggleAction();
    updateFloatAction();
}

void DockWidgetBase::Private::close()
{
    if (!m_isForceClosing && q->isFloating() && q->isVisible()) { // only user-closing is interesting to save the geometry
        // We check for isVisible so we don't save geometry if you call close() on an already closed dock widget
        m_lastPositions.setLastFloatingGeometry(q->window()->geometry());
    }

    saveTabIndex();

    // Do some cleaning. Widget is hidden, but we must hide the tab containing it.
    if (Frame *frame = q->frame()) {
        frame->removeWidget(q);
        q->setParent(nullptr);

        if (SideBar *sb = DockRegistry::self()->sideBarForDockWidget(q)) {
            sb->removeDockWidget(q);
        }
    }

    if (options & DockWidgetBase::Option_DeleteOnClose)
        q->deleteLater();
}

bool DockWidgetBase::Private::restoreToPreviousPosition()
{
    if (!m_lastPositions.isValid())
        return false;

    Layouting::Item *item = m_lastPositions.lastItem();

    MultiSplitter *layout = DockRegistry::self()->layoutForItem(item);
    Q_ASSERT(layout);
    layout->restorePlaceholder(q, item, m_lastPositions.lastTabIndex());
    return true;
}

void DockWidgetBase::Private::maybeRestoreToPreviousPosition()
{
    // This is called when we get a QEvent::Show. Let's see if we have to restore it to a previous position.

    if (!m_lastPositions.isValid())
        return;

    Layouting::Item *layoutItem = m_lastPositions.lastItem();
    if (!layoutItem)
        return; // nothing to do, no last position

    if (m_lastPositions.wasFloating())
        return; // Nothing to do, it was floating before, now it'll just get visible

    Frame *frame = q->frame();

    if (frame && frame->QWidgetAdapter::parentWidget() == DockRegistry::self()->layoutForItem(layoutItem)) {
        // There's a frame already. Means the DockWidget was hidden instead of closed.
        // Nothing to do, the dock widget will simply be shown
        return;
    }

    // Now we deal with the case where the DockWidget was close()ed. In this case it doesn't have a parent.

    if (q->parentWidget()) {
        // The QEvent::Show is due to it being made floating. Nothing to restore.
        return;
    }

    // Finally, restore it
    restoreToPreviousPosition();
}

int DockWidgetBase::Private::currentTabIndex() const
{
    Frame *frame = q->frame();
    return frame ? frame->indexOfDockWidget(q) : 0;
}

void DockWidgetBase::Private::saveTabIndex()
{
    m_lastPositions.saveTabIndex(currentTabIndex(), q->isFloating());
}

void DockWidgetBase::Private::show()
{
    // Only show for now
    q->show();
}

void DockWidgetBase::onParentChanged()
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    // TODO: In v1.4, remove this part and use the signal emitting the arg
    Q_EMIT parentChanged();
#else
    Q_EMIT parentChanged(this);
#endif
    d->updateToggleAction();
    d->updateFloatAction();
}

void DockWidgetBase::onShown(bool spontaneous)
{
    d->onDockWidgetShown();
    Q_EMIT shown();

    if (Frame *f = frame()) {
        if (!spontaneous) {
            f->onDockWidgetShown(this);
        }
    }

    d->maybeRestoreToPreviousPosition();

    // Transform into a FloatingWindow if this will be a regular floating dock widget.
    QTimer::singleShot(0, this, &DockWidgetBase::maybeMorphIntoFloatingWindow);
}

void DockWidgetBase::onHidden(bool spontaneous)
{
    d->onDockWidgetHidden();
    Q_EMIT hidden();

    if (Frame *f = frame()) {
        if (!spontaneous) {
            f->onDockWidgetHidden(this);
        }
    }
}

bool DockWidgetBase::onResize(QSize newSize)
{
    if (isOverlayed()) {
        if (auto frame = this->frame()) {
            d->m_lastOverlayedSize = frame->QWidgetAdapter::size();
        } else {
            qWarning() << Q_FUNC_INFO << "Overlayed dock widget without frame shouldn't happen";
        }
    }

    return QWidgetAdapter::onResize(newSize);
}

void DockWidgetBase::onCloseEvent(QCloseEvent *e)
{
    e->accept(); // By default we accept, means DockWidget closes
    if (d->widget)
        qApp->sendEvent(d->widget, e); // Give a chancefor the widget to ignore

    if (e->isAccepted())
        d->close();
}

DockWidgetBase *DockWidgetBase::deserialize(const LayoutSaver::DockWidget::Ptr &saved)
{
    DockWidgetBase *dw = DockRegistry::self()->dockByName(saved->uniqueName);
    if (!dw) {
        if (auto factoryFunc = Config::self().dockWidgetFactoryFunc()) {
            // DockWidget doesn't exist, ask to create it
            dw = factoryFunc(saved->uniqueName);
        }
    }

    if (dw) {
        if (QWidgetOrQuick *w = dw->widget())
            w->setVisible(true);
        dw->setProperty("kddockwidget_was_restored", true);

        if (dw->affinities() != saved->affinities) {
            qWarning() << Q_FUNC_INFO << "Affinity name changed from" << dw->affinities()
                       << "; to" << saved->affinities;
            dw->d->affinities = saved->affinities;
        }

    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << saved->uniqueName;
    }

    return dw;
}

LayoutSaver::DockWidget::Ptr DockWidgetBase::serialize() const
{
    auto ptr = LayoutSaver::DockWidget::dockWidgetForName(uniqueName());
    ptr->affinities = affinities();

    return ptr;
}
