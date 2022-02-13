/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget.h"
#include "DockWidget_p.h"
#include "private/DockRegistry_p.h"
#include "private/LayoutSaver_p.h"
#include "private/Logging_p.h"
#include "private/MDILayoutWidget_p.h"
#include "controllers/TitleBar.h"
#include "controllers/Frame.h"
#include "controllers/FloatingWindow.h"
#include "controllers/SideBar.h"
#include "private/Utils_p.h"
#include "private/WindowBeingDragged_p.h"
#include "private/Position_p.h"

#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "views_qtwidgets/Frame_qtwidgets.h"
#include "views_qtwidgets/DockWidget_qtwidgets.h"

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
using namespace KDDockWidgets::Controllers;

DockWidgetBase::DockWidgetBase(const QString &name, Options options,
                               LayoutSaverOptions layoutSaverOptions)
    : Controller(new Views::DockWidget_qtwidgets(this, Qt::Tool))
    , d(new Private(name, options, layoutSaverOptions, this))
{
    d->init();
    view()->init();
    DockRegistry::self()->registerDockWidget(this);

    if (name.isEmpty())
        qWarning() << Q_FUNC_INFO << "Name can't be null";

    view()->setAttribute(Qt::WA_PendingMoveEvent, false);
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

    if ((other->options() & DockWidgetBase::Option_NotDockable) || (options() & DockWidgetBase::Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    if (isPersistentCentralDockWidget()) {
        qWarning() << Q_FUNC_INFO << "Not supported with MainWindowOption_HasCentralWidget."
                   << "MainWindowOption_HasCentralWidget can only have 1 widget in the center."
                   << "Use MainWindowOption_HasCentralFrame instead, which is similar but supports tabbing.";
        return;
    }

    Controllers::Frame *frame = d->frame();

    if (frame) {
        if (frame->containsDockWidget(other)) {
            qWarning() << Q_FUNC_INFO << "Already contains" << other;
            return;
        }
    } else {
        if (view()->isWindow()) {
            // Doesn't have a frame yet
            d->morphIntoFloatingWindow();
            frame = d->frame();
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
    if (auto mainWindow = qobject_cast<MainWindowBase *>(view()->asQWidget()->window())) {
        // It's inside a main window. Simply use the main window API.
        mainWindow->addDockWidget(other, location, relativeTo, initialOption);
        return;
    }

    if (!DockRegistry::self()->affinitiesMatch(other->affinities(), d->affinities)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << other->affinities() << affinities();
        return;
    }

    if ((other->options() & DockWidgetBase::Option_NotDockable) || (options() & DockWidgetBase::Option_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    if (view()->isWindow())
        d->morphIntoFloatingWindow();

    if (auto fw = floatingWindow()) {
        fw->addDockWidget(other, location, relativeTo, initialOption);
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find floating nested window";
    }
}

void DockWidgetBase::setWidget(QWidgetOrQuick *w)
{
    if (w == d->widget)
        return;

    if (d->widget) {
        // Unparent the old widget, we're giving back ownership
        d->widget->setParent(nullptr);
    }

    d->widget = w;
    if (w)
        view()->setSizePolicy(w->sizePolicy());

    Q_EMIT widgetChanged(w);
}

QWidgetOrQuick *DockWidgetBase::widget() const
{
    return d->widget;
}

bool DockWidgetBase::isFloating() const
{
    if (view()->isTopLevel())
        return true;

    auto fw = floatingWindow();
    return fw && fw->hasSingleDockWidget();
}

bool DockWidgetBase::setFloating(bool floats)
{
    const bool alreadyFloating = isFloating();

    if (floats == alreadyFloating)
        return true; // Nothing to do

    if (!floats && (Config::self().internalFlags() & Config::InternalFlag_DontShowWhenUnfloatingHiddenWindow) && !isVisible()) {
        // Mimics behaviour of QDockWidget, which you might need during porting.
        // Not something we suggest though. For KDDW, setFloating(false) means dock, and that implies showing.
        return false;
    }

    if (floats && isPersistentCentralDockWidget())
        return false;

    if (floats) {
        d->saveTabIndex();
        if (isTabbed()) {
            auto frame = d->frame();
            if (!frame) {
                qWarning() << "DockWidget::setFloating: Tabbed but no frame exists"
                           << this;
                Q_ASSERT(false);
                return false;
            }

            frame->detachTab(this);
        } else {
            titleBar()->makeWindow();
        }

        auto lastGeo = d->lastPosition()->lastFloatingGeometry();
        if (lastGeo.isValid()) {
            if (auto fw = floatingWindow())
                fw->setSuggestedGeometry(lastGeo, SuggestedGeometryHint_PreserveCenter);
        }
        return true;
    } else {
        d->saveLastFloatingGeometry();
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
    if (d->isMDIWrapper()) {
        // It's just a wrapper to help implementing Option_MDINestable. Return the title of the real dock widget we're hosting.
        auto dropAreaGuest = qobject_cast<DropArea *>(widget());
        Q_ASSERT(dropAreaGuest);
        if (dropAreaGuest->hasSingleFrame()) {
            return dropAreaGuest->frames().constFirst()->title();
        } else {
            return qApp->applicationName();
        }
    }

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

QRect DockWidgetBase::frameGeometry() const
{
    if (Controllers::Frame *f = d->frame())
        return f->view()->geometry();

    // Means the dock widget isn't visible. Just fallback to its own geometry
    return geometry();
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
    if (Controllers::Frame *frame = d->frame()) {
        return frame->alwaysShowsTabs() || frame->dockWidgetCount() > 1;
    } else {
        if (!isFloating())
            qWarning() << "DockWidget::isTabbed() Couldn't find any tab widget.";
        return false;
    }
}

bool DockWidgetBase::isCurrentTab() const
{
    if (Controllers::Frame *frame = d->frame()) {
        return frame->currentIndex() == frame->indexOfDockWidget(const_cast<DockWidgetBase *>(this));
    } else {
        return true;
    }
}

void DockWidgetBase::setAsCurrentTab()
{
    if (Controllers::Frame *frame = d->frame())
        frame->setCurrentDockWidget(this);
}

int DockWidgetBase::tabIndex() const
{
    if (Controllers::Frame *frame = d->frame())
        return frame->indexOfDockWidget(this);

    return 0;
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
    d->forceClose();
}

Controllers::TitleBar *DockWidgetBase::titleBar() const
{
    if (Controllers::Frame *f = d->frame())
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
    if (view()->isTopLevel() && (d->m_lastPosition->wasFloating() || !d->m_lastPosition->isValid())) {
        // Create the FloatingWindow already, instead of waiting for the show event.
        // This reduces flickering on some platforms
        d->morphIntoFloatingWindow();
    } else {
        view()->show();
    }
}

void DockWidgetBase::raise()
{
    if (!isOpen())
        return;

    setAsCurrentTab();

    if (auto fw = floatingWindow()) {
        fw->view()->raise();
        fw->view()->activateWindow();
    } else if (Controllers::Frame *frame = d->frame()) {
        if (frame->isMDI())
            frame->view()->raise();
    }
}

bool DockWidgetBase::isMainWindow() const
{
    return qobject_cast<MainWindowBase *>(widget());
}

bool DockWidgetBase::isInMainWindow() const
{
    return d->mainWindow() != nullptr;
}

MainWindowBase *DockWidgetBase::mainWindow() const
{
    return d->mainWindow();
}

bool DockWidgetBase::isFocused() const
{
    auto f = d->frame();
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
    return d->m_lastPosition->isValid();
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

void DockWidgetBase::setFloatingGeometry(QRect geometry)
{
    if (isOpen() && isFloating()) {
        view()->asQWidget()->window()->setGeometry(geometry);
    } else {
        d->m_lastPosition->setLastFloatingGeometry(geometry);
    }
}

Controllers::FloatingWindow *DockWidgetBase::floatingWindow() const
{
    if (auto view = qobject_cast<Views::FloatingWindow_qtwidgets *>(this->view()->asQWidget()->window()))
        return view->floatingWindow();

    return nullptr;
}

Controllers::FloatingWindow *DockWidgetBase::Private::morphIntoFloatingWindow()
{
    if (auto fw = floatingWindow())
        return fw; // Nothing to do

    if (q->view()->isWindow()) {
        QRect geo = m_lastPosition->lastFloatingGeometry();
        if (geo.isNull()) {
            geo = q->geometry();

            if (!q->view()->testAttribute(Qt::WA_PendingMoveEvent)) { // If user already moved it, we don't
                // interfere
                const QPoint center = defaultCenterPosForFloating();
                if (!center.isNull())
                    geo.moveCenter(center);
            }
        }

        auto frame = new Controllers::Frame();
        frame->addWidget(q);
        geo.setSize(geo.size().boundedTo(frame->view()->maxSizeHint()));
        Controllers::FloatingWindow::ensureRectIsOnScreen(geo);
        auto floatingWindow = new Controllers::FloatingWindow(frame, geo);
        floatingWindow->view()->show();

        return floatingWindow;
    } else {
        return nullptr;
    }
}

void DockWidgetBase::Private::maybeMorphIntoFloatingWindow()
{
    if (q->view()->isWindow() && q->isVisible())
        morphIntoFloatingWindow();
}

MDILayoutWidget *DockWidgetBase::Private::mdiLayout() const
{
    auto p = const_cast<QObject *>(q->view()->parent());
    while (p) {
        if (qobject_cast<const QWindow *>(p)) {
            // Ignore QObject hierarchies spanning though multiple windows
            return nullptr;
        }

        if (qobject_cast<LayoutWidget *>(p)) {
            // We found a layout
            if (auto mdiLayout = qobject_cast<MDILayoutWidget *>(p)) {
                // And it's MDI
                return mdiLayout;
            } else if (auto dropArea = qobject_cast<DropArea *>(p)) {
                // It's a DropArea. But maybe it's a drop area that's just helping
                // making the MDI windows accept drops (Option_MDINestable)
                if (!dropArea->isMDIWrapper())
                    return nullptr;

                // It's a MDI wrapper, keep looking up.
            }
        }

        p = p->parent();
    }

    return nullptr;
}

bool DockWidgetBase::Private::isMDIWrapper() const
{
    return mdiDropAreaWrapper() != nullptr;
}

DropArea *DockWidgetBase::Private::mdiDropAreaWrapper() const
{
    if (auto dropAreaGuest = qobject_cast<DropArea *>(q->widget())) {
        if (dropAreaGuest->isMDIWrapper())
            return dropAreaGuest;
    }

    return nullptr;
}

DockWidgetBase *DockWidgetBase::Private::mdiDockWidgetWrapper() const
{
    if (isMDIWrapper()) {
        // We are the wrapper
        return q;
    }

    auto p = const_cast<QObject *>(q->view()->parent());
    while (p) {
        if (qobject_cast<const QWindow *>(p)) {
            // Ignore QObject hierarchies spanning though multiple windows
            return nullptr;
        }

        if (qobject_cast<LayoutWidget *>(p)) {
            if (auto dropArea = qobject_cast<DropArea *>(p)) {
                if (dropArea->isMDIWrapper())
                    return dropArea->mdiDockWidgetWrapper();
            }

            return nullptr;
        }

        p = p->parent();
    }

    return nullptr;
}

DockWidgetBase::Private *DockWidgetBase::dptr() const
{
    return d;
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

bool DockWidgetBase::Private::eventFilter(QObject *watched, QEvent *event)
{
    const bool isWindowActivate = event->type() == QEvent::WindowActivate;
    const bool isWindowDeactivate = event->type() == QEvent::WindowDeactivate;
    if ((isWindowActivate || isWindowDeactivate) && watched == q->view()->asQWidget()->window())
        Q_EMIT q->windowActiveAboutToChange(isWindowActivate);

    return QObject::eventFilter(watched, event);
}

void DockWidgetBase::Private::updateTitle()
{
    if (q->isFloating())
        q->view()->asQWidget()->window()->setWindowTitle(title);

    toggleAction->setText(title);
}

void DockWidgetBase::Private::toggle(bool enabled)
{
    if (Controllers::SideBar *sb = sideBar()) {
        // The widget is in the sidebar, let's toggle its overlayed state
        sb->toggleOverlay(q);
    } else {
        // The most common case. The dock widget is not in the sidebar. just close or open it.
        if (enabled) {
            show();
        } else {
            q->view()->close();
        }
    }
}

void DockWidgetBase::Private::updateToggleAction()
{
    QScopedValueRollback<bool> recursionGuard(m_updatingToggleAction, true); // Guard against recursiveness
    m_updatingToggleAction = true;
    if ((q->isVisible() || frame()) && !toggleAction->isChecked()) {
        toggleAction->setChecked(true);
    } else if ((!q->isVisible() && !frame()) && toggleAction->isChecked()) {
        toggleAction->setChecked(false);
    }
}

void DockWidgetBase::Private::updateFloatAction()
{
    QScopedValueRollback<bool> recursionGuard(m_updatingFloatAction, true); // Guard against recursiveness

    if (q->isFloating()) {
        floatAction->setEnabled(m_lastPosition->isValid());
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
    if (!m_processingToggleAction && !q->isOpen()) {
        return;
    }

    if (m_isPersistentCentralDockWidget)
        return;

    // If it's overlayed and we're closing, we need to close the overlay
    if (Controllers::SideBar *sb = DockRegistry::self()->sideBarForDockWidget(q)) {
        auto mainWindow = sb->mainWindow();
        if (mainWindow->overlayedDockWidget() == q) {
            mainWindow->clearSideBarOverlay(/* deleteFrame=*/false);
        }
    }

    if (!m_isForceClosing && q->isFloating()
        && q->isVisible()) { // only user-closing is interesting to save the geometry
        // We check for isVisible so we don't save geometry if you call close() on an already closed
        // dock widget
        m_lastPosition->setLastFloatingGeometry(q->view()->windowGeometry());
    }

    saveTabIndex();

    // Do some cleaning. Widget is hidden, but we must hide the tab containing it.
    if (Controllers::Frame *frame = this->frame()) {
        q->setParent(nullptr);
        q->view()->setParent(nullptr);
        frame->removeWidget(q);

        if (Controllers::SideBar *sb = DockRegistry::self()->sideBarForDockWidget(q)) {
            sb->removeDockWidget(q);
        }
    }

    if (!m_isMovingToSideBar && (options & DockWidgetBase::Option_DeleteOnClose)) {
        Q_EMIT q->aboutToDeleteOnClose();
        q->deleteLater();
    }
}

bool DockWidgetBase::Private::restoreToPreviousPosition()
{
    if (!m_lastPosition->isValid())
        return false;

    Layouting::Item *item = m_lastPosition->lastItem();

    LayoutWidget *layout = DockRegistry::self()->layoutForItem(item);
    Q_ASSERT(layout);
    layout->restorePlaceholder(q, item, m_lastPosition->lastTabIndex());
    return true;
}

void DockWidgetBase::Private::maybeRestoreToPreviousPosition()
{
    // This is called when we get a QEvent::Show. Let's see if we have to restore it to a previous position.

    if (!m_lastPosition->isValid())
        return;

    Layouting::Item *layoutItem = m_lastPosition->lastItem();
    if (!layoutItem)
        return; // nothing to do, no last position

    if (m_lastPosition->wasFloating())
        return; // Nothing to do, it was floating before, now it'll just get visible

    Controllers::Frame *frame = this->frame();

    if (frame && frame->view()->asQWidget()->parentWidget() == DockRegistry::self()->layoutForItem(layoutItem)) {
        // There's a frame already. Means the DockWidget was hidden instead of closed.
        // Nothing to do, the dock widget will simply be shown
        return;
    }

    // Now we deal with the case where the DockWidget was close()ed. In this case it doesn't have a parent.

    if (q->view()->asQWidget()->parentWidget()) {
        // The QEvent::Show is due to it being made floating. Nothing to restore.
        return;
    }

    // Finally, restore it
    restoreToPreviousPosition();
}

int DockWidgetBase::Private::currentTabIndex() const
{
    Controllers::Frame *frame = this->frame();
    return frame ? frame->indexOfDockWidget(q) : 0;
}

void DockWidgetBase::Private::saveTabIndex()
{
    m_lastPosition->saveTabIndex(currentTabIndex(), q->isFloating());
}

void DockWidgetBase::Private::show()
{
    // Only show for now
    q->show();
}

void DockWidgetBase::onParentChanged()
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    Q_EMIT parentChanged();
#else
    Q_EMIT QQuickItem::parentChanged(parentItem());
#endif
    d->updateToggleAction();
    d->updateFloatAction();

    Q_EMIT actualTitleBarChanged();
}

void DockWidgetBase::onShown(bool spontaneous)
{
    d->onDockWidgetShown();
    Q_EMIT shown();

    if (Controllers::Frame *f = d->frame()) {
        if (!spontaneous) {
            f->onDockWidgetShown(this);
        }
    }

    d->maybeRestoreToPreviousPosition();

    // Transform into a FloatingWindow if this will be a regular floating dock widget.
    QTimer::singleShot(0, d, &DockWidgetBase::Private::maybeMorphIntoFloatingWindow);
}

void DockWidgetBase::onHidden(bool spontaneous)
{
    d->onDockWidgetHidden();
    Q_EMIT hidden();

    if (Controllers::Frame *f = d->frame()) {
        if (!spontaneous) {
            f->onDockWidgetHidden(this);
        }
    }
}

void DockWidgetBase::onResize(QSize)
{
    if (isOverlayed()) {
        if (auto frame = d->frame()) {
            d->m_lastOverlayedSize = frame->view()->size();
        } else {
            qWarning() << Q_FUNC_INFO << "Overlayed dock widget without frame shouldn't happen";
        }
    }
}

void DockWidgetBase::onCloseEvent(QCloseEvent *e)
{
    e->accept(); // By default we accept, means DockWidget closes
    if (d->widget)
        qApp->sendEvent(d->widget, e); // Give a chance for the widget to ignore

    if (e->isAccepted())
        d->close();
}

DockWidgetBase *DockWidgetBase::deserialize(const LayoutSaver::DockWidget::Ptr &saved)
{
    auto dr = DockRegistry::self();
    DockWidgetBase *dw = dr->dockByName(saved->uniqueName, DockRegistry::DockByNameFlag::CreateIfNotFound);
    if (dw) {
        if (QWidgetOrQuick *w = dw->widget())
            w->setVisible(true);
        dw->setProperty("kddockwidget_was_restored", true);

        if (dw->affinities() != saved->affinities) {
            qWarning() << Q_FUNC_INFO << "Affinity name changed from" << dw->affinities()
                       << "; to" << saved->affinities;
            dw->d->affinities = saved->affinities;
        }
    }

    return dw;
}

void DockWidgetBase::setUserType(int userType)
{
    d->m_userType = userType;
}

int DockWidgetBase::userType() const
{
    return d->m_userType;
}

void DockWidgetBase::setMDIPosition(QPoint pos)
{
    if (MDILayoutWidget *layout = d->mdiLayout()) {
        if (auto wrapperDW = d->mdiDockWidgetWrapper()) {
            // Case of using Option_MDINestable. We need to layout the actual top level DW
            layout->moveDockWidget(wrapperDW, pos);
        } else {
            layout->moveDockWidget(this, pos);
        }
    }
}

void DockWidgetBase::setMDISize(QSize size)
{
    if (MDILayoutWidget *layout = d->mdiLayout()) {
        if (auto wrapperDW = d->mdiDockWidgetWrapper()) {
            // Case of using Option_MDINestable. We need to layout the actual top level DW
            layout->resizeDockWidget(wrapperDW, size);
        } else {
            layout->resizeDockWidget(this, size);
        }
    }
}

void DockWidgetBase::setMDIZ(int z)
{
#ifdef KDDOCKWIDGETS_QTQUICK
    if (Frame *frame = d->frame()) {
        if (!frame->isMDI())
            return;
        frame->setZ(z);
    }
#else
    Q_UNUSED(z);
    qWarning() << Q_FUNC_INFO << "Not implemented for QtQuick";
#endif
}

bool DockWidgetBase::isPersistentCentralDockWidget() const
{
    return d->m_isPersistentCentralDockWidget;
}

LayoutSaver::DockWidget::Ptr DockWidgetBase::Private::serialize() const
{
    auto ptr = LayoutSaver::DockWidget::dockWidgetForName(q->uniqueName());
    ptr->affinities = q->affinities();

    return ptr;
}

void DockWidgetBase::Private::forceClose()
{
    QScopedValueRollback<bool> rollback(m_isForceClosing, true);
    close();
}

DockWidgetBase::Private::Private(const QString &dockName, DockWidgetBase::Options options_,
                                 LayoutSaverOptions layoutSaverOptions_, DockWidgetBase *qq)

    : name(dockName)
    , title(dockName)
    , q(qq)
    , options(options_)
    , layoutSaverOptions(layoutSaverOptions_)
    , toggleAction(new QAction(q))
    , floatAction(new QAction(q))
{
    q->connect(toggleAction, &QAction::toggled, q, [this](bool enabled) {
        if (!m_updatingToggleAction) { // guard against recursiveness
            toggleAction->blockSignals(true); // and don't emit spurious toggle. Like when a dock
                                              // widget is inserted into a tab widget it might get
                                              // hide events, ignore those. The Dock Widget is open.
            m_processingToggleAction = true;
            toggle(enabled);
            toggleAction->blockSignals(false);
            m_processingToggleAction = false;
        }
    });

    q->connect(floatAction, &QAction::toggled, q, [this](bool checked) {
        if (!m_updatingFloatAction) { // guard against recursiveness
            q->setFloating(checked);
        }

        Q_EMIT q->isFloatingChanged(checked);

        // When floating, we remove from the sidebar
        if (checked && q->isOpen()) {
            if (Controllers::SideBar *sb = DockRegistry::self()->sideBarForDockWidget(q)) {
                sb->mainWindow()->clearSideBarOverlay(/* deleteFrame=*/false);
                sb->removeDockWidget(q);
            }
        }
    });

    toggleAction->setCheckable(true);
    floatAction->setCheckable(true);

    qApp->installEventFilter(this);
}

void DockWidgetBase::Private::addPlaceholderItem(Layouting::Item *item)
{
    Q_ASSERT(item);
    m_lastPosition->addPlaceholderItem(item);
}

Position::Ptr &DockWidgetBase::Private::lastPosition()
{
    return m_lastPosition;
}

Controllers::Frame *DockWidgetBase::Private::frame() const
{
    QWidgetOrQuick *p = q->view()->asQWidget()->parentWidget();
    while (p) {
        if (auto frameView = qobject_cast<Views::Frame_qtwidgets *>(p))
            return frameView->frame();
        p = p->parentWidget();
    }
    return nullptr;
}

void DockWidgetBase::Private::saveLastFloatingGeometry()
{
    if (q->isFloating() && q->isVisible()) {
        // It's getting docked, save last floating position
        lastPosition()->setLastFloatingGeometry(q->view()->windowGeometry());
    }
}
