/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DockWidgetBase.h"
#include "DragController_p.h"
#include "Frame_p.h"
#include "FloatingWindow_p.h"
#include "Logging_p.h"
#include "TabWidget_p.h"
#include "Utils_p.h"
#include "DockRegistry_p.h"
#include "WidgetResizeHandler_p.h"
#include "DropArea_p.h"
#include "Position_p.h"
#include "multisplitter/Item_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

#include <QAction>
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
    Private(const QString &dockName, DockWidgetBase::Options options_, DockWidgetBase *qq)
        : name(dockName)
        , title(dockName)
        , q(qq)
        , options(options_)
        , toggleAction(new QAction(q))
        , floatAction(new QAction(q))
    {
        q->connect(q, &DockWidgetBase::shown, q, [this] { onDockWidgetShown(); } );
        q->connect(q, &DockWidgetBase::hidden, q, [this] { onDockWidgetHidden(); } );

        q->connect(toggleAction, &QAction::toggled, q, [this] (bool enabled) {
            if (!m_updatingToggleAction) { // guard against recursiveness
                toggleAction->blockSignals(true); // and don't emit spurious toggle. Like when a dock widget is inserted into a tab widget it might get hide events, ignore those. The Dock Widget is open.
                toggle(enabled);
                toggleAction->blockSignals(false);
            }
        });

        q->connect(floatAction, &QAction::toggled, q, [this] (bool enabled) {
            if (!m_updatingFloatAction) { // guard against recursiveness
                q->setFloating(enabled);
            }
        });

        toggleAction->setCheckable(true);
        floatAction->setCheckable(true);
    }

    void init()
    {
        updateTitle();
    }

    QPoint defaultCenterPosForFloating();

    void updateTitle();
    void updateIcon();
    void toggle(bool enabled);
    void updateToggleAction();
    void updateFloatAction();
    void onDockWidgetShown();
    void onDockWidgetHidden();
    TabWidget *parentTabWidget() const;
    void show();
    void close();
    void restoreToPreviousPosition();
    void maybeRestoreToPreviousPosition();
    int currentTabIndex() const;

    /**
     * Before floating a dock widget we save its position. So it can be restored when calling
     * DockWidget::setFloating(false)
     */
    void saveTabIndex();

    const QString name;
    QString affinityName;
    QString title;
    QIcon icon;
    QWidget *widget = nullptr;
    DockWidgetBase *const q;
    DockWidgetBase::Options options;
    QAction *const toggleAction;
    QAction *const floatAction;
    LastPositions m_lastPositions;
    bool m_updatingToggleAction = false;
    bool m_updatingFloatAction = false;
    bool m_isForceClosing = false;
};

DockWidgetBase::DockWidgetBase(const QString &name, Options options)
    : QWidgetOrQuick(nullptr, Qt::Tool)
    , d(new Private(name, options, this))
{
    d->init();
    DragController::instance();
    DockRegistry::self()->registerDockWidget(this);
    qCDebug(creation) << "DockWidget" << this;

    if (name.isEmpty())
        qWarning() << Q_FUNC_INFO << "Name can't be null";
}

DockWidgetBase::~DockWidgetBase()
{
    DockRegistry::self()->unregisterDockWidget(this);
    qCDebug(creation) << "~DockWidget" << this;
    delete d;
}

void DockWidgetBase::addDockWidgetAsTab(DockWidgetBase *other, AddingOption addingOption)
{
    qCDebug(addwidget) << Q_FUNC_INFO << other;
    if (other == this) {
        qWarning() << Q_FUNC_INFO << "Refusing to add dock widget into itself" << other;
        return;
    }

    if (!other) {
        qWarning() << Q_FUNC_INFO << "dock widget is null";
        return;
    }

    if (other->affinityName() != affinityName()) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << other->affinityName() << affinityName();
        return;
    }

    if ((other->options() & DockWidgetBase::Option_NotDockable) ||
        (options() & DockWidgetBase::Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    Frame *frame = this->frame();

    if (frame) {
        if (frame->contains(other)) {
            qWarning() << Q_FUNC_INFO << "Already contains" << other;
            return;
        }
    } else {
        if (isWindow()) {
            // Doesn't have a frame yet
            morphIntoFloatingWindow();
            frame = this->frame();
        }
    }

    Q_ASSERT(frame);
    other->setParent(nullptr);
    frame->addWidget(other, addingOption);
}

void DockWidgetBase::addDockWidgetToContainingWindow(DockWidgetBase *other, Location location, DockWidgetBase *relativeTo)
{
    qCDebug(addwidget) << Q_FUNC_INFO << other << location << relativeTo;
    if (qobject_cast<MainWindowBase*>(window())) {
        qWarning() << Q_FUNC_INFO << "Just use MainWindow::addWidget() directly. This function is for floating nested windows only.";
        return;
    }

    if (other->affinityName() != affinityName()) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << other->affinityName() << affinityName();
        return;
    }

    if ((other->options() & DockWidgetBase::Option_NotDockable) ||
        (options() & DockWidgetBase::Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    if (isWindow())
        morphIntoFloatingWindow();

    if (auto fw = qobject_cast<FloatingWindow *>(window())) {
        fw->dropArea()->addDockWidget(other, location, relativeTo);
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find floating nested window";
    }
}

void DockWidgetBase::setWidget(QWidget *w)
{
    Q_ASSERT(w && !d->widget);
    qCDebug(addwidget) << Q_FUNC_INFO << w;

    d->widget = w;
    Q_EMIT widgetChanged(w);
    setWindowTitle(uniqueName());
}

QWidget *DockWidgetBase::widget() const
{
    return d->widget;
}

bool DockWidgetBase::isFloating() const
{
    if (isWindow())
        return true;

    auto fw = qobject_cast<FloatingWindow *>(window());
    return fw && fw->hasSingleDockWidget();
}

void DockWidgetBase::setFloating(bool floats)
{
    const bool alreadyFloating = isFloating();

    qCDebug(docking) << Q_FUNC_INFO << "yes=" << floats
                     << "; already floating=" << alreadyFloating;

    if ((floats && alreadyFloating) || (!floats && !alreadyFloating))
        return; // Nothing to do

    if (floats) {
        d->saveTabIndex();
        if (isTabbed()) {
            TabWidget *tabWidget= d->parentTabWidget();
            if (!tabWidget) {
                qWarning() << "DockWidget::setFloating: Tabbed but no tabbar exists"
                           << this;
                Q_ASSERT(false);
            }

            tabWidget->detachTab(this);
        } else {
            frame()->titleBar()->makeWindow();
        }
    } else {
        d->restoreToPreviousPosition();
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
        Q_EMIT titleChanged();
    }
}

DockWidgetBase::Options DockWidgetBase::options() const
{
    return d->options;
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
            tb->updateCloseButton();
    }
}

bool DockWidgetBase::isTabbed() const
{
    if (TabWidget* tabWidget = d->parentTabWidget()) {
        return frame()->alwaysShowsTabs() || tabWidget->numDockWidgets() > 1;
    } else {
        if (!isFloating())
            qWarning() << "DockWidget::isTabbed() Couldn't find any tab widget.";
        return false;
    }
}

bool DockWidgetBase::isCurrentTab() const
{
    if (TabWidget* tabWidget = d->parentTabWidget()) {
        return tabWidget->currentIndex() == tabWidget->indexOfDockWidget(const_cast<DockWidgetBase*>(this));
    } else {
        return true;
    }
}

void DockWidgetBase::setAsCurrentTab()
{
    if (TabWidget* tabWidget = d->parentTabWidget())
        tabWidget->setCurrentDockWidget(this);
}

void DockWidgetBase::setIcon(const QIcon &icon)
{
    d->icon = icon;
    d->updateIcon();
    Q_EMIT iconChanged();
}

QIcon DockWidgetBase::icon() const
{
    return d->icon;
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

QString DockWidgetBase::affinityName() const
{
    return d->affinityName;
}

void DockWidgetBase::show()
{
    if (isWindow() && (lastPosition()->m_wasFloating || !lastPosition()->isValid())) {
        // Create the FloatingWindow already, instead of waiting for the show event.
        // This reduces flickering on some platforms
        morphIntoFloatingWindow();
    } else {
        QWidget::show();
    }
}

void DockWidgetBase::raise()
{
    if (!isOpen())
        return;

    setAsCurrentTab();

    if (auto fw = qobject_cast<FloatingWindow*>(window())) {
        fw->raise();
        fw->activateWindow();
    }
}

void DockWidgetBase::setAffinityName(const QString &name)
{
    if (d->affinityName == name)
        return;

    if (!d->affinityName.isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Affinity is already set, refusing to change."
                   << "Submit a feature request with a good justification.";
        return;
    }

    d->affinityName = name;
}

FloatingWindow *DockWidgetBase::morphIntoFloatingWindow()
{
    qCDebug(creation) << "DockWidget::morphIntoFloatingWindow() this=" << this
                      << "; visible=" << isVisible();

    if (auto fw = qobject_cast<FloatingWindow*>(window()))
        return fw; // Nothing to do

    if (isWindow()) {
        QRect geo = lastPosition()->lastFloatingGeometry();
        if (geo.isNull()) {
            geo = geometry();
            const QPoint center = d->defaultCenterPosForFloating();
            if (!center.isNull())
                geo.moveCenter(center);
        }

        auto frame = Config::self().frameworkWidgetFactory()->createFrame();
        frame->addWidget(this);
        auto floatingWindow = Config::self().frameworkWidgetFactory()->createFloatingWindow(frame);
        floatingWindow->setGeometry(geo);
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
    return qobject_cast<FloatingWindow*>(window());
}

void DockWidgetBase::addPlaceholderItem(Layouting::Item *item)
{
    qCDebug(placeholder) << Q_FUNC_INFO << this << item;
    Q_ASSERT(item);
    d->m_lastPositions.addPosition(item);
}

Position *DockWidgetBase::lastPosition() const
{
    return &d->m_lastPositions.lastPosition;
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

void DockWidgetBase::Private::updateIcon()
{
}

void DockWidgetBase::Private::toggle(bool enabled)
{
    if (enabled) {
        show();
    } else {
        q->close();
    }
}

void DockWidgetBase::Private::updateToggleAction()
{
    QScopedValueRollback<bool> recursionGuard(m_updatingToggleAction, true); // Guard against recursiveness
    m_updatingToggleAction = true;
    if ((q->isVisible() || parentTabWidget()) && !toggleAction->isChecked()) {
        toggleAction->setChecked(true);
    } else if ((!q->isVisible() && !parentTabWidget()) && toggleAction->isChecked()) {
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
    qCDebug(hiding) << Q_FUNC_INFO << "parent=" << q->parentWidget();
}

void DockWidgetBase::Private::onDockWidgetHidden()
{
    updateToggleAction();
    updateFloatAction();
    qCDebug(hiding) << Q_FUNC_INFO << "parent=" << q->parentWidget();
}

TabWidget *DockWidgetBase::Private::parentTabWidget() const
{
    if (auto f = q->frame())
        return f->tabWidget();

    return nullptr;
}

void DockWidgetBase::Private::close()
{
    if (!m_isForceClosing && q->isFloating() && q->isVisible()) { // only user-closing is interesting to save the geometry
        // We check for isVisible so we don't save geometry if you call close() on an already closed dock widget
        m_lastPositions.setLastFloatingGeometry(q->window()->geometry());
    }

    qCDebug(hiding) << "DockWidget::close" << this;
    saveTabIndex();

    // Do some cleaning. Widget is hidden, but we must hide the tab containing it.
    if (auto tabWidget = parentTabWidget()) {
        tabWidget->removeDockWidget(q);
        q->setParent(nullptr);
    }
}

void DockWidgetBase::Private::restoreToPreviousPosition()
{
    if (!m_lastPositions.isValid()) {
        qWarning() << Q_FUNC_INFO << "Only restoring to MainWindow supported for now";
        return;
    }

    auto &lp = m_lastPositions.lastPosition;
    Layouting::Item *item = lp.layoutItem();

    MultiSplitterLayout *layout = DockRegistry::self()->layoutForItem(item);
    Q_ASSERT(layout);
    layout->restorePlaceholder(q, lp.layoutItem(), lp.m_tabIndex);
}

void DockWidgetBase::Private::maybeRestoreToPreviousPosition()
{
    // This is called when we get a QEvent::Show. Let's see if we have to restore it to a previous position.

    auto &lp = m_lastPositions.lastPosition;
    if (!lp.isValid())
        return;

    Layouting::Item *layoutItem = lp.layoutItem();
    qCDebug(placeholder) << Q_FUNC_INFO << layoutItem << lp.m_wasFloating;
    if (!layoutItem)
        return; // nothing to do, no last position

    if (lp.m_wasFloating)
        return; // Nothing to do, it was floating before, now it'll just get visible

    Frame *frame = q->frame();

    if (frame && frame->parentWidget() == DockRegistry::self()->layoutForItem(layoutItem)->multiSplitter()) {
        // There's a frame already. Means the DockWidget was hidden instead of closed.
        // Nothing to do, the dock widget will simply be shown
        qCDebug(placeholder) << Q_FUNC_INFO << "Already had frame.";
        return;
    }

    // Now we deal with the case where the DockWidget was close()ed. In this case it doesn't have a parent.

    if (q->parentWidget()) {
        // The QEvent::Show is due to it being made floating. Nothing to restore.
        qCDebug(placeholder) << Q_FUNC_INFO << "Already had parentWidget";
        return;
    }

    // Finally, restore it
    restoreToPreviousPosition();
}

int DockWidgetBase::Private::currentTabIndex() const
{
    TabWidget *tabWidget = parentTabWidget();
    return tabWidget ? tabWidget->indexOfDockWidget(q) : 0;
}

void DockWidgetBase::Private::saveTabIndex()
{
    m_lastPositions.lastPosition.m_tabIndex = currentTabIndex();
    m_lastPositions.lastPosition.m_wasFloating = q->isFloating();
}

void DockWidgetBase::Private::show()
{
    // Only show for now
    q->show();
}

void DockWidgetBase::onParentChanged()
{
    Q_EMIT parentChanged();
    d->updateToggleAction();
    d->updateFloatAction();
}

void DockWidgetBase::onShown(bool spontaneous)
{
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
    Q_EMIT hidden();

    if (Frame *f = frame()) {
        if (!spontaneous) {
            f->onDockWidgetHidden(this);
        }
    }
}

void DockWidgetBase::onClosed(QCloseEvent *e)
{
    e->accept(); // By default we accept, means DockWidget closes
    if (d->widget)
        qApp->sendEvent(d->widget, e); // Give a change for the widget to ignore

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
        if (QWidget *w = dw->widget())
            w->setVisible(true);
        dw->setProperty("kddockwidget_was_restored", true);

        if (dw->affinityName() != saved->affinityName) {
            qWarning() << Q_FUNC_INFO << "Affinity name changed from" << dw->affinityName()
                       << "; to" << saved->affinityName;
            dw->d->affinityName = saved->affinityName;
        }

    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << saved->uniqueName;
    }

    return dw;
}

LayoutSaver::DockWidget::Ptr DockWidgetBase::serialize() const
{
    auto ptr = LayoutSaver::DockWidget::dockWidgetForName(uniqueName());
    ptr->affinityName = affinityName();

    return ptr;
}
