/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockRegistry.h"
#include "Config.h"
#include "private/Logging_p.h"
#include "private/Position_p.h"
#include "private/Utils_p.h"
#include "private/Platform_p.h"
#include "private/WidgetResizeHandler_p.h"
#include "private/WindowBeingDragged_p.h"
#include "private/multisplitter/Item_p.h"
#include "Window.h"
#include "views/MainWindowViewInterface.h"
#include "Platform.h"
#include "kddockwidgets/controllers/FloatingWindow.h"
#include "kddockwidgets/controllers/SideBar.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "kddockwidgets/controllers/DockWidget.h"
#include "kddockwidgets/controllers/DockWidget_p.h"
#include "kddockwidgets/controllers/DropArea.h"

#include "kdbindings/signal.h"

#include <QPointer>
#include <QDebug>
#include <QGuiApplication>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

class DockRegistry::Private
{
public:
    KDBindings::ConnectionHandle m_connection;
};

DockRegistry::DockRegistry(QObject *parent)
    : QObject(parent)
    , d(new Private())
{
    qGuiApp->installEventFilter(this);
    d->m_connection = Platform::instance()->d->focusedViewChanged.connect(&DockRegistry::onFocusedViewChanged, this);
}

DockRegistry::~DockRegistry()
{
    d->m_connection.disconnect();
    delete d;
}

void DockRegistry::maybeDelete()
{
    if (isEmpty())
        delete this;
}

void DockRegistry::onFocusedViewChanged(std::shared_ptr<View> view)
{
    auto p = view;
    while (p && !p->isNull()) {
        if (auto group = p->asGroupController()) {
            // Special case: The focused widget is inside the group but not inside the dockwidget.
            // For example, it's a line edit in the QTabBar. We still need to send the signal for
            // the current dw in the tab group
            if (auto dw = group->currentDockWidget()) {
                setFocusedDockWidget(dw);
            }

            return;
        }

        if (auto dw = p->asDockWidgetController()) {
            DockRegistry::self()->setFocusedDockWidget(dw);
            return;
        }
        p = p->parentView();
    }

    setFocusedDockWidget(nullptr);
}

void DockRegistry::setFocusedDockWidget(Controllers::DockWidget *dw)
{
    if (m_focusedDockWidget.data() == dw)
        return;

    if (m_focusedDockWidget)
        Q_EMIT m_focusedDockWidget->isFocusedChanged(false);

    m_focusedDockWidget = dw;

    if (m_focusedDockWidget)
        Q_EMIT m_focusedDockWidget->isFocusedChanged(true);
}

bool DockRegistry::isEmpty(bool excludeBeingDeleted) const
{
    if (!m_dockWidgets.isEmpty() || !m_mainWindows.isEmpty())
        return false;

    return excludeBeingDeleted ? !hasFloatingWindows()
                               : m_floatingWindows.isEmpty();
}

void DockRegistry::checkSanityAll(bool dumpLayout)
{
    for (auto layout : qAsConst(m_layouts)) {
        layout->checkSanity();
        if (dumpLayout)
            layout->dumpLayout();
    }
}

bool DockRegistry::affinitiesMatch(const QStringList &affinities1, const QStringList &affinities2) const
{
    if (affinities1.isEmpty() && affinities2.isEmpty())
        return true;

    for (const QString &a1 : affinities1) {
        for (const QString &a2 : affinities2) {
            if (a1 == a2)
                return true;
        }
    }

    return false;
}

QStringList DockRegistry::mainWindowsNames() const
{
    QStringList names;
    names.reserve(m_mainWindows.size());
    for (auto mw : m_mainWindows)
        names.push_back(mw->uniqueName());

    return names;
}

QStringList DockRegistry::dockWidgetNames() const
{
    QStringList names;
    names.reserve(m_dockWidgets.size());
    for (auto dw : m_dockWidgets)
        names.push_back(dw->uniqueName());

    return names;
}

bool DockRegistry::isProbablyObscured(Window::Ptr window, Controllers::FloatingWindow *exclude) const
{
    if (!window)
        return false;

    const QRect geo = window->geometry();
    for (Controllers::FloatingWindow *fw : m_floatingWindows) {
        Window::Ptr fwWindow = fw->view()->window();
        if (fw == exclude || fwWindow->equals(window))
            continue;

        if (fwWindow->geometry().intersects(geo)) {
            // fw might be below, but we don't have a way to check. So be conservative and return true.
            return true;
        }
    }

    // Floating windows are Tool (keep above), unless we disabled it in Config
    const bool targetIsToolWindow = KDDockWidgets::usesUtilityWindows() && floatingWindowForHandle(window) != nullptr;

    for (Controllers::MainWindow *mw : m_mainWindows) {
        Window::Ptr mwWindow = mw->view()->window();

        if (mwWindow && !mwWindow->equals(window) && !targetIsToolWindow && mwWindow->geometry().intersects(geo)) {
            // Two main windows that intersect. Return true. If the target is a tool window it will be above, so we don't care.
            return true;
        }
    }

    return false;
}

bool DockRegistry::isProbablyObscured(Window::Ptr target, WindowBeingDragged *exclude) const
{
    Controllers::FloatingWindow *fw = exclude ? exclude->floatingWindow()
                                              : nullptr; // It's null on Wayland. On wayland obscuring never happens anyway, so not a problem.

    return isProbablyObscured(target, fw);
}

SideBarLocation DockRegistry::sideBarLocationForDockWidget(const Controllers::DockWidget *dw) const
{
    if (Controllers::SideBar *sb = sideBarForDockWidget(dw))
        return sb->location();

    return SideBarLocation::None;
}

Controllers::SideBar *DockRegistry::sideBarForDockWidget(const Controllers::DockWidget *dw) const
{
    for (auto mw : m_mainWindows) {
        if (Controllers::SideBar *sb = mw->sideBarForDockWidget(dw))
            return sb;
    }

    return nullptr;
}

Controllers::Group *DockRegistry::groupInMDIResize() const
{
    for (auto mw : m_mainWindows) {
        if (!mw->isMDI())
            continue;

        Layout *layout = mw->layout();
        const QList<Controllers::Group *> groups = layout->groups();
        for (Controllers::Group *group : groups) {
            if (WidgetResizeHandler *wrh = group->resizeHandler()) {
                if (wrh->isResizing())
                    return group;
            }
        }
    }

    return nullptr;
}

Controllers::MainWindow::List DockRegistry::mainWindowsWithAffinity(const QStringList &affinities) const
{
    Controllers::MainWindow::List result;
    result.reserve(m_mainWindows.size());

    for (auto mw : m_mainWindows) {
        const QStringList mwAffinities = mw->affinities();
        if (affinitiesMatch(mwAffinities, affinities))
            result << mw;
    }

    return result;
}

Controllers::Layout *DockRegistry::layoutForItem(const Layouting::Item *item) const
{
    if (!item->hostView())
        return nullptr;

    return item->hostView()->asLayout();
}

bool DockRegistry::itemIsInMainWindow(const Layouting::Item *item) const
{
    if (Controllers::Layout *layout = layoutForItem(item)) {
        return layout->isInMainWindow(/*honoursNesting=*/true);
    }

    return false;
}

DockRegistry *DockRegistry::self()
{
    static QPointer<DockRegistry> s_dockRegistry;

    if (!s_dockRegistry) {
        s_dockRegistry = new DockRegistry();
    }

    return s_dockRegistry;
}

void DockRegistry::registerDockWidget(Controllers::DockWidget *dock)
{
    if (dock->uniqueName().isEmpty()) {
        qWarning() << Q_FUNC_INFO << "DockWidget" << dock << " doesn't have an ID";
    } else if (auto other = dockByName(dock->uniqueName())) {
        qWarning() << Q_FUNC_INFO << "Another DockWidget" << other << "with name" << dock->uniqueName() << " already exists." << dock;
    }

    m_dockWidgets << dock;
}

void DockRegistry::unregisterDockWidget(Controllers::DockWidget *dock)
{
    if (m_focusedDockWidget == dock)
        m_focusedDockWidget = nullptr;

    m_dockWidgets.removeOne(dock);
    maybeDelete();
}

void DockRegistry::registerMainWindow(Controllers::MainWindow *mainWindow)
{
    if (mainWindow->uniqueName().isEmpty()) {
        qWarning() << Q_FUNC_INFO << "MainWindow" << mainWindow << " doesn't have an ID";
    } else if (auto other = mainWindowByName(mainWindow->uniqueName())) {
        qWarning() << Q_FUNC_INFO << "Another MainWindow" << other << "with name" << mainWindow->uniqueName() << " already exists." << mainWindow;
    }

    m_mainWindows << mainWindow;
}

void DockRegistry::unregisterMainWindow(Controllers::MainWindow *mainWindow)
{
    m_mainWindows.removeOne(mainWindow);
    maybeDelete();
}

void DockRegistry::registerFloatingWindow(Controllers::FloatingWindow *window)
{
    m_floatingWindows << window;
}

void DockRegistry::unregisterFloatingWindow(Controllers::FloatingWindow *window)
{
    m_floatingWindows.removeOne(window);
    maybeDelete();
}

void DockRegistry::registerLayout(Controllers::Layout *layout)
{
    m_layouts << layout;
}

void DockRegistry::unregisterLayout(Controllers::Layout *layout)
{
    m_layouts.removeOne(layout);
}

void DockRegistry::registerGroup(Controllers::Group *group)
{
    m_groups << group;
}

void DockRegistry::unregisterGroup(Controllers::Group *group)
{
    m_groups.removeOne(group);
}

Controllers::DockWidget *DockRegistry::focusedDockWidget() const
{
    return m_focusedDockWidget;
}

bool DockRegistry::containsDockWidget(const QString &uniqueName) const
{
    return dockByName(uniqueName) != nullptr;
}

bool DockRegistry::containsMainWindow(const QString &uniqueName) const
{
    return mainWindowByName(uniqueName) != nullptr;
}

Controllers::DockWidget *DockRegistry::dockByName(const QString &name, DockByNameFlags flags) const
{
    for (auto dock : qAsConst(m_dockWidgets)) {
        if (dock->uniqueName() == name)
            return dock;
    }

    if (flags.testFlag(DockByNameFlag::ConsultRemapping)) {
        // Name doesn't exist, let's check if it was remapped during a layout restore.
        const QString newName = m_dockWidgetIdRemapping.value(name);
        if (!newName.isEmpty())
            return dockByName(newName);
    }

    if (flags.testFlag(DockByNameFlag::CreateIfNotFound)) {
        // DockWidget doesn't exist, ask to create it
        if (auto factoryFunc = Config::self().dockWidgetFactoryFunc()) {
            auto dw = factoryFunc(name);
            if (dw && dw->uniqueName() != name) {
                // Very special case
                // The user's factory function returned a dock widget with a different ID.
                // We support it. Save the mapping though.
                m_dockWidgetIdRemapping.insert(name, dw->uniqueName());
            }
            return dw;
        } else {
            qWarning() << Q_FUNC_INFO << "Couldn't find dock widget" << name;
        }
    }

    return nullptr;
}

Controllers::MainWindow *DockRegistry::mainWindowByName(const QString &name) const
{
    for (auto mainWindow : qAsConst(m_mainWindows)) {
        if (mainWindow->uniqueName() == name)
            return mainWindow;
    }

    return nullptr;
}

Controllers::DockWidget *DockRegistry::dockWidgetForGuest(View *guest) const
{
    if (!guest)
        return nullptr;

    for (Controllers::DockWidget *dw : m_dockWidgets) {
        if (guest->equals(dw->guestView()))
            return dw;
    }

    return nullptr;
}

bool DockRegistry::isSane() const
{
    QSet<QString> names;
    for (auto dock : qAsConst(m_dockWidgets)) {
        const QString name = dock->uniqueName();
        if (name.isEmpty()) {
            qWarning() << "DockRegistry::isSane: DockWidget" << dock << "is missing a name";
            return false;
        } else if (names.contains(name)) {
            qWarning() << "DockRegistry::isSane: dockWidgets with duplicate names:" << name;
            return false;
        } else {
            names.insert(name);
        }
    }

    names.clear();
    for (auto mainwindow : qAsConst(m_mainWindows)) {
        const QString name = mainwindow->uniqueName();
        if (name.isEmpty()) {
            qWarning() << "DockRegistry::isSane: MainWindow" << mainwindow << "is missing a name";
            return false;
        } else if (names.contains(name)) {
            qWarning() << "DockRegistry::isSane: mainWindow with duplicate names:" << name;
            return false;
        } else {
            names.insert(name);
        }

        if (!mainwindow->multiSplitter()->checkSanity())
            return false;
    }

    return true;
}

const Controllers::DockWidget::List DockRegistry::dockwidgets() const
{
    return m_dockWidgets;
}

const Controllers::DockWidget::List DockRegistry::dockWidgets(const QStringList &names)
{
    Controllers::DockWidget::List result;
    result.reserve(names.size());

    for (auto dw : qAsConst(m_dockWidgets)) {
        if (names.contains(dw->uniqueName()))
            result.push_back(dw);
    }

    return result;
}

const Controllers::MainWindow::List DockRegistry::mainWindows(const QStringList &names)
{
    Controllers::MainWindow::List result;
    result.reserve(names.size());

    for (auto mw : qAsConst(m_mainWindows)) {
        if (names.contains(mw->uniqueName()))
            result.push_back(mw);
    }

    return result;
}

const Controllers::DockWidget::List DockRegistry::closedDockwidgets() const
{
    Controllers::DockWidget::List result;
    result.reserve(m_dockWidgets.size());

    for (Controllers::DockWidget *dw : m_dockWidgets) {
        if (dw->parent() == nullptr && !dw->isVisible())
            result.push_back(dw);
    }

    return result;
}

const Controllers::MainWindow::List DockRegistry::mainwindows() const
{
    return m_mainWindows;
}

const QList<Views::MainWindowViewInterface *> DockRegistry::mainDockingAreas() const
{
    QList<Views::MainWindowViewInterface *> areas;

    for (auto mw : m_mainWindows) {
        if (View *view = mw->view()) {
            auto viewInterface = dynamic_cast<Views::MainWindowViewInterface *>(view);
            areas << viewInterface;
        }
    }

    return areas;
}

const QVector<Controllers::Layout *> DockRegistry::layouts() const
{
    return m_layouts;
}

const Controllers::Group::List DockRegistry::groups() const
{
    return m_groups;
}

const QVector<Controllers::FloatingWindow *> DockRegistry::floatingWindows(bool includeBeingDeleted) const
{
    // Returns all the FloatingWindow which aren't being deleted
    QVector<Controllers::FloatingWindow *> result;
    result.reserve(m_floatingWindows.size());
    for (Controllers::FloatingWindow *fw : m_floatingWindows) {
        if (includeBeingDeleted || !fw->beingDeleted())
            result.push_back(fw);
    }

    return result;
}

const Window::List DockRegistry::floatingQWindows() const
{
    Window::List windows;
    windows.reserve(m_floatingWindows.size());
    for (Controllers::FloatingWindow *fw : m_floatingWindows) {
        if (!fw->beingDeleted()) {
            if (Window::Ptr window = fw->view()->window()) {
                windows.push_back(window);
            } else {
                qWarning() << Q_FUNC_INFO << "FloatingWindow doesn't have QWindow";
            }
        }
    }

    return windows;
}

bool DockRegistry::hasFloatingWindows() const
{
    return std::any_of(m_floatingWindows.begin(), m_floatingWindows.end(), [](Controllers::FloatingWindow *fw) {
        return !fw->beingDeleted();
    });
}

Controllers::FloatingWindow *DockRegistry::floatingWindowForHandle(Window::Ptr windowHandle) const
{
    for (Controllers::FloatingWindow *fw : m_floatingWindows) {
        if (fw->view()->window()->equals(windowHandle))
            return fw;
    }

    return nullptr;
}

Controllers::FloatingWindow *DockRegistry::floatingWindowForHandle(WId hwnd) const
{
    for (Controllers::FloatingWindow *fw : m_floatingWindows) {
        Window::Ptr window = fw->view()->window();
        if (window && window->handle() == hwnd)
            return fw;
    }

    return nullptr;
}

Controllers::MainWindow *DockRegistry::mainWindowForHandle(Window::Ptr window) const
{
    if (!window)
        return nullptr;

    for (Controllers::MainWindow *mw : m_mainWindows) {
        if (mw->view()->isInWindow(window))
            return mw;
    }

    return nullptr;
}

Window::List DockRegistry::topLevels(bool excludeFloatingDocks) const
{
    Window::List windows;
    windows.reserve(m_floatingWindows.size() + m_mainWindows.size());

    if (!excludeFloatingDocks) {
        for (Controllers::FloatingWindow *fw : m_floatingWindows) {
            if (fw->isVisible()) {
                if (Window::Ptr window = fw->view()->window()) {
                    windows << window;
                } else {
                    qWarning() << Q_FUNC_INFO << "FloatingWindow doesn't have QWindow";
                }
            }
        }
    }

    for (Controllers::MainWindow *m : m_mainWindows) {
        if (m->isVisible()) {
            if (Window::Ptr window = m->view()->window()) {
                windows << window;
            } else {
                qWarning() << Q_FUNC_INFO << "MainWindow doesn't have QWindow";
            }
        }
    }

    return windows;
}

void DockRegistry::clear(const QStringList &affinities)
{
    // Clears everything
    clear(m_dockWidgets, m_mainWindows, affinities);
}

void DockRegistry::clear(const Controllers::DockWidget::List &dockWidgets,
                         const Controllers::MainWindow::List &mainWindows,
                         const QStringList &affinities)
{
    for (auto dw : qAsConst(dockWidgets)) {
        if (affinities.isEmpty() || affinitiesMatch(affinities, dw->affinities())) {
            dw->forceClose();
            dw->d->lastPosition()->removePlaceholders();
        }
    }

    for (auto mw : qAsConst(mainWindows)) {
        if (affinities.isEmpty() || affinitiesMatch(affinities, mw->affinities())) {
            mw->multiSplitter()->clearLayout();
        }
    }
}

void DockRegistry::ensureAllFloatingWidgetsAreMorphed()
{
    for (Controllers::DockWidget *dw : qAsConst(m_dockWidgets)) {
        if (dw->view()->rootView()->equals(dw->view()) && dw->isVisible())
            dw->d->morphIntoFloatingWindow();
    }
}

bool DockRegistry::eventFilter(QObject *watched, QEvent *event)
{
    auto view = Platform::instance()->qobjectAsView(watched);
    if (!view)
        return false;

    if (event->type() == QEvent::Expose) {
        if (auto window = Platform::instance()->qobjectAsWindow(watched)) {
            if (Controllers::FloatingWindow *fw = floatingWindowForHandle(window)) {
                // This floating window was exposed
                m_floatingWindows.removeOne(fw);
                m_floatingWindows.append(fw);
            }
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        // When clicking on a MDI Frame we raise the window
        if (Controller *c = View::firstParentOfType(watched, Type::Frame)) {
            auto group = static_cast<Group *>(c);
            if (group->isMDI())
                group->view()->raise();
        }

        // The following code is for hididng the overlay
        if (!(Config::self().flags() & Config::Flag_AutoHideSupport))
            return false;

        if (view->is(Type::Frame)) {
            // break recursion
            return false;
        }

        auto p = view;
        while (p) {
            if (auto dw = p->asDockWidgetController())
                return onDockWidgetPressed(dw, static_cast<QMouseEvent *>(event));

            if (auto layout = p->asLayout()) {
                if (auto mw = layout->mainWindow()) {
                    // The user clicked somewhere in the main window's drop area, but outside of the
                    // overlayed dock widget
                    mw->clearSideBarOverlay();
                    return false;
                }
            }

            p = p->parentView();
        }
    }

    return false;
}

bool DockRegistry::onDockWidgetPressed(Controllers::DockWidget *dw, QMouseEvent *ev)
{
    // Here we implement "auto-hide". If there's a overlayed dock widget, we hide it if some other
    // dock widget is clicked.

    // Don't be sending mouse events around if a popup is open, they are sensitive
    if (Platform::instance()->hasActivePopup())
        return false;

    Controllers::MainWindow *mainWindow = dw->mainWindow();
    if (!mainWindow) // Only docked widgets are interesting
        return false;

    if (Controllers::DockWidget *overlayedDockWidget = mainWindow->overlayedDockWidget()) {
        ev->ignore();
        Platform::instance()->sendEvent(overlayedDockWidget->d->group()->view(), ev);

        if (ev->isAccepted()) {
            // The Frame accepted it. It means the user is resizing it. We allow for 4px outside for better resize.
            return true; // don't propagate the event further
        }
        if (dw != overlayedDockWidget) {
            // User clicked outside if the overlay, then we close the overlay.
            mainWindow->clearSideBarOverlay();
            return false;
        }
    }

    return false;
}
