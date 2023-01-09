/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidget.h"
#include "DockWidget_p.h"
#include "DockRegistry.h"
#include "private/LayoutSaver_p.h"
#include "private/Logging_p.h"
#include "controllers/MDILayout.h"
#include "controllers/TitleBar.h"
#include "controllers/Group.h"
#include "controllers/FloatingWindow.h"
#include "controllers/SideBar.h"
#include "controllers/DropArea.h"
#include "controllers/TabBar.h"
#include "controllers/MainWindow.h"
#include "private/Utils_p.h"
#include "private/WindowBeingDragged_p.h"
#include "private/Position_p.h"
#include "private/Platform_p.h"
#include "Platform.h"
#include "private/multisplitter/Item_p.h"

#include "Config.h"
#include "kddockwidgets/ViewFactory.h"

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

DockWidget::DockWidget(View *view, const QString &name, DockWidgetOptions options,
                       LayoutSaverOptions layoutSaverOptions)
    : Controller(Type::DockWidget, view)
    , d(new Private(name, options, layoutSaverOptions, this))
{
    DockRegistry::self()->registerDockWidget(this);

    if (name.isEmpty())
        qWarning() << Q_FUNC_INFO << "Name can't be null";

    d->m_windowActivatedConnection = Platform::instance()->d->windowActivated.connect(
        &DockWidget::Private::onWindowActivated, d);
    d->m_windowDeactivatedConnection = Platform::instance()->d->windowDeactivated.connect(
        &DockWidget::Private::onWindowDeactivated, d);
}

DockWidget::~DockWidget()
{
    Q_EMIT aboutToDelete(this);
    DockRegistry::self()->unregisterDockWidget(this);
    delete d;
}

void DockWidget::init()
{
    d->init();
    view()->setAttribute(Qt::WA_PendingMoveEvent, false);
}

void DockWidget::addDockWidgetAsTab(DockWidget *other, InitialOption option)
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

    if ((other->options() & DockWidgetOption_NotDockable)
        || (options() & DockWidgetOption_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    if (isPersistentCentralDockWidget()) {
        qWarning() << Q_FUNC_INFO << "Not supported with MainWindowOption_HasCentralWidget."
                   << "MainWindowOption_HasCentralWidget can only have 1 widget in the center."
                   << "Use MainWindowOption_HasCentralFrame instead, which is similar but supports "
                      "tabbing.";
        return;
    }

    Controllers::Group *group = d->group();

    if (group) {
        if (group->containsDockWidget(other)) {
            qWarning() << Q_FUNC_INFO << "Already contains" << other;
            return;
        }
    } else {
        if (view()->isRootView()) {
            // Doesn't have a group yet
            d->morphIntoFloatingWindow();
            group = d->group();
        } else {
            // Doesn't happen
            qWarning() << Q_FUNC_INFO << "null group";
            return;
        }
    }

    other->setParentView(nullptr);
    group->addTab(other, option);
}

void DockWidget::addDockWidgetToContainingWindow(DockWidget *other, Location location,
                                                 DockWidget *relativeTo,
                                                 InitialOption initialOption)
{
    if (auto mainWindow = view()->rootView()->asMainWindowController()) {
        // It's inside a main window. Simply use the main window API.
        mainWindow->addDockWidget(other, location, relativeTo, initialOption);
        return;
    }

    if (!DockRegistry::self()->affinitiesMatch(other->affinities(), d->affinities)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock widget with incompatible affinity."
                   << other->affinities() << affinities();
        return;
    }

    if ((other->options() & DockWidgetOption_NotDockable)
        || (options() & DockWidgetOption_NotDockable)) {
        qWarning() << Q_FUNC_INFO << "Refusing to dock non-dockable widget" << other;
        return;
    }

    if (view()->isRootView())
        d->morphIntoFloatingWindow();

    if (auto fw = floatingWindow()) {
        fw->addDockWidget(other, location, relativeTo, initialOption);
    } else {
        qWarning() << Q_FUNC_INFO << "Couldn't find floating nested window";
    }
}

std::shared_ptr<View> DockWidget::guestView() const
{
    return d->guest;
}

void DockWidget::setGuestView(std::shared_ptr<View> guest)
{
    if ((guest && guest->equals(d->guest)) || (!guest && !d->guest))
        return;

    if (d->guest) {
        // Unparent the old widget, we're giving back ownership
        d->guest->setParent(nullptr);
    }

    d->guest = guest;
    if (guest)
        view()->setSizePolicy(guest->horizontalSizePolicy(), guest->verticalSizePolicy());

    Q_EMIT guestViewChanged();
}

bool DockWidget::isFloating() const
{
    if (view()->isRootView())
        return true;

    auto fw = floatingWindow();
    return fw && fw->hasSingleDockWidget();
}

bool DockWidget::setFloating(bool floats)
{
    const bool alreadyFloating = isFloating();

    if (floats == alreadyFloating)
        return true; // Nothing to do

    if (!floats
        && (Config::self().internalFlags()
            & Config::InternalFlag_DontShowWhenUnfloatingHiddenWindow)
        && !isVisible()) {
        // Mimics behaviour of QDockWidget, which you might need during porting.
        // Not something we suggest though. For KDDW, setFloating(false) means dock, and that
        // implies showing.
        return false;
    }

    if (floats && isPersistentCentralDockWidget())
        return false;

    if (floats) {
        d->saveTabIndex();
        if (isTabbed()) {
            auto group = d->group();
            if (!group) {
                qWarning() << "DockWidget::setFloating: Tabbed but no group exists" << this;
                Q_ASSERT(false);
                return false;
            }

            group->detachTab(this);
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

QAction *DockWidget::toggleAction() const
{
    return d->toggleAction;
}

QAction *DockWidget::floatAction() const
{
    return d->floatAction;
}

QString DockWidget::uniqueName() const
{
    return d->name;
}

QString DockWidget::title() const
{
    if (d->isMDIWrapper()) {
        // It's just a wrapper to help implementing Option_MDINestable. Return the title of the real
        // dock widget we're hosting.
        auto dropAreaGuest = d->guest ? guestView()->asDropAreaController() : nullptr;
        Q_ASSERT(dropAreaGuest);
        if (dropAreaGuest->hasSingleFrame()) {
            return dropAreaGuest->groups().constFirst()->title();
        } else {
            return Platform::instance()->applicationName();
        }
    }

    return d->title;
}

void DockWidget::setTitle(const QString &title)
{
    if (title != d->title) {
        d->title = title;
        d->updateTitle();
        Q_EMIT titleChanged(title);
    }
}

QRect DockWidget::groupGeometry() const
{
    if (Controllers::Group *f = d->group())
        return f->view()->geometry();

    // Means the dock widget isn't visible. Just fallback to its own geometry
    return geometry();
}

DockWidgetOptions DockWidget::options() const
{
    return d->options;
}

LayoutSaverOptions DockWidget::layoutSaverOptions() const
{
    return d->layoutSaverOptions;
}

void DockWidget::setOptions(DockWidgetOptions options)
{
    if ((d->options & DockWidgetOption_NotDockable) != (options & DockWidgetOption_NotDockable)) {
        qWarning() << Q_FUNC_INFO
                   << "Option_NotDockable not allowed to change. Pass via ctor only.";
        return;
    }

    if (options != d->options) {
        d->options = options;
        Q_EMIT optionsChanged(options);
        if (auto tb = titleBar())
            tb->updateButtons();
    }
}

bool DockWidget::isTabbed() const
{
    if (Controllers::Group *group = d->group()) {
        return group->alwaysShowsTabs() || group->dockWidgetCount() > 1;
    } else {
        if (!isFloating())
            qWarning() << "DockWidget::isTabbed() Couldn't find any tab widget.";
        return false;
    }
}

bool DockWidget::isCurrentTab() const
{
    if (Controllers::Group *group = d->group()) {
        return group->currentIndex() == group->indexOfDockWidget(const_cast<DockWidget *>(this));
    } else {
        return true;
    }
}

void DockWidget::setAsCurrentTab()
{
    if (Controllers::Group *group = d->group())
        group->setCurrentDockWidget(this);
}

int DockWidget::tabIndex() const
{
    if (Controllers::Group *group = d->group())
        return group->indexOfDockWidget(this);

    return 0;
}

int DockWidget::currentTabIndex() const
{
    if (Group *group = d->group())
        return group->currentTabIndex();

    return 0;
}

void DockWidget::setIcon(const QIcon &icon, IconPlaces places)
{
    if (places & IconPlace::TitleBar)
        d->titleBarIcon = icon;

    if (places & IconPlace::TabBar)
        d->tabBarIcon = icon;

    if (places & IconPlace::ToggleAction)
        d->toggleAction->setIcon(icon);

    Q_EMIT iconChanged();
}

QIcon DockWidget::icon(IconPlace place) const
{
    if (place == IconPlace::TitleBar)
        return d->titleBarIcon;

    if (place == IconPlace::TabBar)
        return d->tabBarIcon;

    if (place == IconPlace::ToggleAction)
        return d->toggleAction->icon();

    return {};
}

void DockWidget::forceClose()
{
    d->forceClose();
}

Controllers::TitleBar *DockWidget::titleBar() const
{
    if (Controllers::Group *f = d->group())
        return f->actualTitleBar();

    return nullptr;
}

bool DockWidget::isOpen() const
{
    return d->m_isOpen;
}

QStringList DockWidget::affinities() const
{
    return d->affinities;
}

void DockWidget::show()
{
    open();
}

void DockWidget::open()
{
    if (view()->isRootView()
        && (d->m_lastPosition->wasFloating() || !d->m_lastPosition->isValid())) {
        // Create the FloatingWindow already, instead of waiting for the show event.
        // This reduces flickering on some platforms
        d->morphIntoFloatingWindow();
    } else {
        d->setIsOpen(true);
        view()->show();
    }
}

void DockWidget::raise()
{
    if (!isOpen())
        return;

    setAsCurrentTab();

    if (auto fw = floatingWindow()) {
        fw->view()->raise();
        fw->view()->activateWindow();
    } else if (Controllers::Group *group = d->group()) {
        if (group->isMDI())
            group->view()->raise();
    }
}

bool DockWidget::isMainWindow() const
{
    if (auto guest = guestView())
        return guest->is(Type::MainWindow);
    return false;
}

bool DockWidget::isInMainWindow() const
{
    return d->mainWindow() != nullptr;
}

MainWindow *DockWidget::mainWindow() const
{
    return d->mainWindow();
}

bool DockWidget::isFocused() const
{
    auto group = d->group();
    return group && group->isFocused() && isCurrentTab();
}

void DockWidget::setAffinityName(const QString &affinity)
{
    setAffinities({ affinity });
}

void DockWidget::setAffinities(const QStringList &affinityNames)
{
    QStringList affinities = affinityNames;
    affinities.removeAll(QString());

    if (d->affinities == affinities)
        return;

    if (!d->affinities.isEmpty()) {
        qWarning() << Q_FUNC_INFO << "Affinity is already set, refusing to change."
                   << "Submit a feature request with a good justification.";
        return;
    }

    d->affinities = affinities;
}

void DockWidget::moveToSideBar()
{
    if (MainWindow *m = mainWindow())
        m->moveToSideBar(this);
}

bool DockWidget::isOverlayed() const
{
    if (MainWindow *m = mainWindow())
        return m->overlayedDockWidget() == this;

    return false;
}

SideBarLocation DockWidget::sideBarLocation() const
{
    return DockRegistry::self()->sideBarLocationForDockWidget(this);
}

bool DockWidget::isInSideBar() const
{
    return sideBarLocation() != SideBarLocation::None;
}

bool DockWidget::hasPreviousDockedLocation() const
{
    return d->m_lastPosition->isValid();
}

QSize DockWidget::lastOverlayedSize() const
{
    return d->m_lastOverlayedSize;
}

Controllers::DockWidget *DockWidget::byName(const QString &uniqueName)
{
    return DockRegistry::self()->dockByName(uniqueName);
}

void DockWidget::setParentView_impl(View *parent)
{
    if (Controllers::Group *group = d->group()) {
        group->tabBar()->removeDockWidget(this);
    }

    Controller::setParentView_impl(parent);
    d->onParentChanged();
}

bool DockWidget::skipsRestore() const
{
    return d->layoutSaverOptions & LayoutSaverOption::Skip;
}

void DockWidget::setFloatingGeometry(QRect geometry)
{
    if (isOpen() && isFloating()) {
        view()->rootView()->setGeometry(geometry);
    } else {
        d->m_lastPosition->setLastFloatingGeometry(geometry);
    }
}

Controllers::FloatingWindow *DockWidget::floatingWindow() const
{
    if (auto fw = view()->rootView()->asFloatingWindowController())
        return fw;

    return nullptr;
}

Controllers::FloatingWindow *DockWidget::Private::morphIntoFloatingWindow()
{
    if (auto fw = floatingWindow())
        return fw; // Nothing to do

    if (q->view()->isRootView()) {
        QRect geo = m_lastPosition->lastFloatingGeometry();
        if (geo.isNull()) {
            geo = q->geometry();

            if (!q->view()->testAttribute(Qt::WA_PendingMoveEvent)) { // If user already moved it,
                                                                      // we don't
                // interfere
                const QPoint center = defaultCenterPosForFloating();
                if (!center.isNull())
                    geo.moveCenter(center);
            }
        }

        auto group = new Controllers::Group();
        group->addTab(q);
        geo.setSize(geo.size().boundedTo(group->view()->maxSizeHint()));
        geo.setSize(geo.size().expandedTo(group->view()->minSize()));
        Controllers::FloatingWindow::ensureRectIsOnScreen(geo);
        auto floatingWindow = new Controllers::FloatingWindow(group, geo);

        Layouting::AtomicSanityChecks checks(floatingWindow->dropArea()->rootItem());
        floatingWindow->view()->show();
        setIsOpen(true);

        return floatingWindow;
    } else {
        return nullptr;
    }
}

void DockWidget::Private::maybeMorphIntoFloatingWindow()
{
    if (q->view()->isRootView() && q->isVisible())
        morphIntoFloatingWindow();
}

MDILayout *DockWidget::Private::mdiLayout() const
{
    auto p = q->view()->parentView();
    while (p) {
        // We found a layout
        if (auto mdiLayout = p->asMDILayoutController()) {
            // And it's MDI
            return mdiLayout;
        } else if (auto dropArea = p->asDropAreaController()) {
            // It's a DropArea. But maybe it's a drop area that's just helping
            // making the MDI windows accept drops (Option_MDINestable)
            if (!dropArea->isMDIWrapper())
                return nullptr;

            // It's a MDI wrapper, keep looking up.
        }

        p = p->parentView();
    }

    return nullptr;
}

bool DockWidget::Private::isMDIWrapper() const
{
    return mdiDropAreaWrapper() != nullptr;
}

DropArea *DockWidget::Private::mdiDropAreaWrapper() const
{
    if (auto dropAreaGuest = guest ? q->guestView()->asDropAreaController() : nullptr) {
        if (dropAreaGuest->isMDIWrapper())
            return dropAreaGuest;
    }

    return nullptr;
}

Controllers::DockWidget *DockWidget::Private::mdiDockWidgetWrapper() const
{
    if (isMDIWrapper()) {
        // We are the wrapper
        return q;
    }

    auto p = q->view()->parentView();
    while (p) {

        if (p->is(Type::DropArea) || p->is(Type::MDILayout)) {
            if (auto dropArea = p->asDropAreaController()) {
                if (dropArea->isMDIWrapper())
                    return dropArea->mdiDockWidgetWrapper();
            }

            return nullptr;
        }

        p = p->parentView();
    }

    return nullptr;
}

DockWidget::Private *DockWidget::dptr() const
{
    return d;
}

DockWidget::Private::~Private() = default;

QPoint DockWidget::Private::defaultCenterPosForFloating()
{
    MainWindow::List mainWindows = DockRegistry::self()->mainwindows();
    // We don't care about multiple mainwindows yet. Or, let's just say that the first one is more
    // main than the others
    MainWindow *mw = mainWindows.isEmpty() ? nullptr : mainWindows.constFirst();
    if (!mw || !q->isFloating())
        return {};

    return mw->geometry().center();
}

void DockWidget::Private::onWindowActivated(std::shared_ptr<View> rootView)
{
    if (View::equals(rootView.get(), q->view()->rootView().get()))
        Q_EMIT q->windowActiveAboutToChange(true);
}

void DockWidget::Private::onWindowDeactivated(std::shared_ptr<View> rootView)
{
    if (View::equals(rootView.get(), q->view()->rootView().get()))
        Q_EMIT q->windowActiveAboutToChange(false);
}


void DockWidget::Private::updateTitle()
{
    if (q->isFloating())
        q->view()->rootView()->setWindowTitle(title);

    toggleAction->setText(title);
}

void DockWidget::Private::toggle(bool enabled)
{
    if (Controllers::SideBar *sb = sideBar()) {
        // The widget is in the sidebar, let's toggle its overlayed state
        QScopedValueRollback<bool> guard(m_removingFromOverlay, true);
        sb->toggleOverlay(q);
    } else {
        // The most common case. The dock widget is not in the sidebar. just close or open it.
        if (enabled) {
            q->show();
        } else {
            q->view()->close();
        }
    }
}

void DockWidget::Private::updateToggleAction()
{
    QScopedValueRollback<bool> recursionGuard(m_updatingToggleAction,
                                              true); // Guard against recursiveness

    if ((q->isVisible() || group()) && !toggleAction->isChecked()) {
        toggleAction->setChecked(true);
    } else if ((!q->isVisible() && !group()) && toggleAction->isChecked()) {
        toggleAction->setChecked(false);
    }
}

void DockWidget::Private::updateFloatAction()
{
    if (m_willUpdateActions || m_removingFromOverlay)
        return;

    QScopedValueRollback<bool> recursionGuard(m_updatingFloatAction,
                                              true); // Guard against recursiveness

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

void DockWidget::Private::close()
{
    if (m_inClose)
        return;
    QScopedValueRollback<bool> guard(m_inClose, true);

    if (!m_processingToggleAction && !q->isOpen()) {
        q->setParentView(nullptr);
        return;
    }

    if (m_isPersistentCentralDockWidget)
        return;

    setIsOpen(false);

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
    if (Controllers::Group *group = this->group()) {
        q->QObject::setParent(nullptr);
        q->setParentView(nullptr);
        group->removeWidget(q);

        if (Controllers::SideBar *sb = DockRegistry::self()->sideBarForDockWidget(q)) {
            sb->removeDockWidget(q);
        }
    }

    if (!m_isMovingToSideBar && (options & DockWidgetOption_DeleteOnClose)) {
        Q_EMIT q->aboutToDeleteOnClose();
        q->deleteLater();
    }
}

bool DockWidget::Private::restoreToPreviousPosition()
{
    if (!m_lastPosition->isValid())
        return false;

    Layouting::Item *item = m_lastPosition->lastItem();

    Layout *layout = DockRegistry::self()->layoutForItem(item);
    Q_ASSERT(layout);
    layout->restorePlaceholder(q, item, m_lastPosition->lastTabIndex());
    return true;
}

void DockWidget::Private::maybeRestoreToPreviousPosition()
{
    // This is called when we open a dock widget. Let's see if we have to restore it to a previous
    // position.

    if (!m_lastPosition->isValid())
        return;

    Layouting::Item *layoutItem = m_lastPosition->lastItem();
    if (!layoutItem)
        return; // nothing to do, no last position

    if (m_lastPosition->wasFloating())
        return; // Nothing to do, it was floating before, now it'll just get visible

    Controllers::Group *group = this->group();

    if (group && group->view()->equals(DockRegistry::self()->layoutForItem(layoutItem)->view())) {
        // There's a group already. Means the DockWidget was hidden instead of closed.
        // Nothing to do, the dock widget will simply be shown
        return;
    }

    // Now we deal with the case where the DockWidget was close()ed. In this case it doesn't have a
    // parent.

    if (q->view()->parentView()) {
        // Was called due to it being made floating. Nothing to restore.
        return;
    }

    // Finally, restore it
    restoreToPreviousPosition();
}

int DockWidget::Private::currentTabIndex() const
{
    Controllers::Group *group = this->group();
    return group ? group->indexOfDockWidget(q) : 0;
}

void DockWidget::Private::saveTabIndex()
{
    m_lastPosition->saveTabIndex(currentTabIndex(), q->isFloating());
}

void DockWidget::Private::onParentChanged()
{
    updateToggleAction();
    updateFloatAction();

    Q_EMIT q->actualTitleBarChanged();
}

void DockWidget::onResize(QSize)
{
    if (isOverlayed()) {
        if (auto group = d->group()) {
            d->m_lastOverlayedSize = group->view()->size();
        } else {
            qWarning() << Q_FUNC_INFO << "Overlayed dock widget without group shouldn't happen";
        }
    }
}

Controllers::DockWidget *DockWidget::deserialize(const LayoutSaver::DockWidget::Ptr &saved)
{
    auto dr = DockRegistry::self();
    DockWidget *dw =
        dr->dockByName(saved->uniqueName, DockRegistry::DockByNameFlag::CreateIfNotFound);
    if (dw) {
        if (auto guest = dw->guestView())
            guest->controller()->setVisible(true);
        dw->setProperty("kddockwidget_was_restored", true);

        if (dw->affinities() != saved->affinities) {
            qWarning() << Q_FUNC_INFO << "Affinity name changed from" << dw->affinities() << "; to"
                       << saved->affinities;
            dw->d->affinities = saved->affinities;
        }
    }

    return dw;
}

void DockWidget::setUserType(int userType)
{
    d->m_userType = userType;
}

int DockWidget::userType() const
{
    return d->m_userType;
}

void DockWidget::setMDIPosition(QPoint pos)
{
    if (MDILayout *layout = d->mdiLayout()) {
        if (auto wrapperDW = d->mdiDockWidgetWrapper()) {
            // Case of using Option_MDINestable. We need to layout the actual top level DW
            layout->moveDockWidget(wrapperDW, pos);
        } else {
            layout->moveDockWidget(this, pos);
        }
    }
}

void DockWidget::setMDISize(QSize size)
{
    if (MDILayout *layout = d->mdiLayout()) {
        if (auto wrapperDW = d->mdiDockWidgetWrapper()) {
            // Case of using Option_MDINestable. We need to layout the actual top level DW
            layout->resizeDockWidget(wrapperDW, size);
        } else {
            layout->resizeDockWidget(this, size);
        }
    }
}

void DockWidget::setMDIZ(int z)
{
    if (Group *group = d->group()) {
        if (group->isMDI())
            group->view()->setZOrder(z);
    }
}

bool DockWidget::isPersistentCentralDockWidget() const
{
    return d->m_isPersistentCentralDockWidget;
}

LayoutSaver::DockWidget::Ptr DockWidget::Private::serialize() const
{
    auto ptr = LayoutSaver::DockWidget::dockWidgetForName(q->uniqueName());
    ptr->affinities = q->affinities();

    return ptr;
}

void DockWidget::Private::forceClose()
{
    QScopedValueRollback<bool> rollback(m_isForceClosing, true);
    close();
}

DockWidget::Private::Private(const QString &dockName, DockWidgetOptions options_,
                             LayoutSaverOptions layoutSaverOptions_, DockWidget *qq)

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
}

void DockWidget::Private::addPlaceholderItem(Layouting::Item *item)
{
    Q_ASSERT(item);
    m_lastPosition->addPlaceholderItem(item);
}

Position::Ptr &DockWidget::Private::lastPosition()
{
    return m_lastPosition;
}

Controllers::Group *DockWidget::Private::group() const
{
    auto p = q->view()->parentView();
    while (p) {
        if (auto group = p->asGroupController())
            return group;
        p = p->parentView();
    }
    return nullptr;
}

void DockWidget::Private::saveLastFloatingGeometry()
{
    if (q->isFloating() && q->isVisible()) {
        // It's getting docked, save last floating position
        lastPosition()->setLastFloatingGeometry(q->view()->windowGeometry());
    }
}

void DockWidget::Private::onCloseEvent(QCloseEvent *e)
{
    e->accept(); // By default we accept, means DockWidget closes
    if (guest) {
        // Give a chance for the widget to ignore
        Platform::instance()->sendEvent(guest.get(), e);
    }

    if (e->isAccepted())
        close();
}

void DockWidget::Private::setIsOpen(bool is)
{
    if (is == m_isOpen || m_inOpenSetter)
        return;

    QScopedValueRollback<bool> guard(m_inOpenSetter, true);

    if (!is)
        close();

    m_isOpen = is;

    if (is) {
        maybeRestoreToPreviousPosition();

        // Transform into a FloatingWindow if this will be a regular floating dock widget.
        QTimer::singleShot(0, this, &DockWidget::Private::maybeMorphIntoFloatingWindow);
    }

    updateToggleAction();
    updateFloatAction();

    if (!is) {
        Q_EMIT q->closed();
    }

    Q_EMIT q->isOpenChanged(is);
}

void DockWidget::setFloatingWindowFlags(FloatingWindowFlags flags)
{
    if (floatingWindow()) {
        qWarning() << Q_FUNC_INFO << "Call this function only before having a floating window";
    } else {
        d->m_flags = flags;
    }
}

KDDockWidgets::FloatingWindowFlags DockWidget::floatingWindowFlags() const
{
    return d->m_flags;
}
