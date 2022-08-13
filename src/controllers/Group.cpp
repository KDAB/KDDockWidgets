/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Group.h"

#include "kddockwidgets/Config.h"
#include "kddockwidgets/ViewFactory.h"

#include "Controller.h"
#include "View.h"
#include "Platform.h"
#include "views/GroupViewInterface.h"

#include "controllers/TitleBar.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"
#include "controllers/MDILayout.h"
#include "controllers/DropArea.h"
#include "controllers/Layout.h"
#include "controllers/MainWindow.h"

#include "DockRegistry.h"
#include "DockWidget_p.h"

#include "private/Logging_p.h"
#include "private/Utils_p.h"
#include "private/View_p.h"
#include "private/LayoutSaver_p.h"
#include "private/Position_p.h"
#include "private/WidgetResizeHandler_p.h"
#include "private/multisplitter/Item_p.h"

#include "kdbindings/signal.h"

#include <QCloseEvent>
#include <QTimer>

#define MARGIN_THRESHOLD 100

static int s_dbg_numFrames = 0;

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

namespace KDDockWidgets {

class Group::Private
{
public:
    KDBindings::ScopedConnection m_visibleWidgetCountChangedConnection;
};

static FrameOptions actualOptions(FrameOptions options)
{
    if (Config::self().flags() & Config::Flag_AlwaysShowTabs)
        options |= FrameOption_AlwaysShowsTabs;

    return options;
}

static StackOptions tabWidgetOptions(FrameOptions options)
{
    if (options & FrameOption_NonDockable) {
        /// If we can't tab things into this Frame then let's not draw the QTabWidget group either
        return StackOption_DocumentMode;
    }

    return StackOption_None;
}

}

Group::Group(View *parent, FrameOptions options, int userType)
    : Controller(Type::Frame, Config::self().viewFactory()->createGroup(this, parent))
    , FocusScope(view())
    , d(new Private())
    , m_stack(new Controllers::Stack(this, tabWidgetOptions(options)))
    , m_tabBar(m_stack->tabBar())
    , m_titleBar(new Controllers::TitleBar(this))
    , m_options(actualOptions(options))
    , m_userType(userType)
{
    s_dbg_numFrames++;
    DockRegistry::self()->registerGroup(this);

    connect(m_tabBar, &TabBar::currentDockWidgetChanged, this, &Group::updateTitleAndIcon);
    connect(m_tabBar, &TabBar::currentTabChanged, this, &Group::onCurrentTabChanged);

    setLayout(parent ? parent->asLayout() : nullptr);
    m_stack->setTabBarAutoHide(!alwaysShowsTabs());
    view()->init();
    view()->d->closeRequested.connect([this](QCloseEvent *ev) { onCloseEvent(ev); });

    m_inCtor = false;
}

Group::~Group()
{
    m_inDtor = true;
    s_dbg_numFrames--;
    if (m_layoutItem)
        m_layoutItem->unref();

    delete m_resizeHandler;
    m_resizeHandler = nullptr;

    DockRegistry::self()->unregisterGroup(this);

    // Run some disconnects() too, so we don't receive signals during destruction:
    setLayout(nullptr);
    delete m_titleBar;
    delete m_stack;
    delete d;
}

void Group::onCloseEvent(QCloseEvent *e)
{
    qCDebug(closing) << "Frame::closeEvent";
    e->accept(); // Accepted by default (will close unless ignored)
    const DockWidget::List docks = dockWidgets();
    for (DockWidget *dock : docks) {
        Platform::instance()->sendEvent(dock->view(), e);
        if (!e->isAccepted())
            break; // Stop when the first dockwidget prevents closing
    }
}

void Group::setLayout(Layout *dt)
{
    if (dt == m_layout)
        return;

    const bool wasInMainWindow = dt && isInMainWindow();

    m_layout = dt;
    delete m_resizeHandler;
    m_resizeHandler = nullptr;

    if (m_layout) {
        if (isMDI())
            m_resizeHandler = new WidgetResizeHandler(WidgetResizeHandler::EventFilterMode::Global,
                                                      WidgetResizeHandler::WindowMode::MDI, view());

        // We keep the connect result so we don't dereference m_layout at shutdown
        d->m_visibleWidgetCountChangedConnection->disconnect(); // TODOm3: Remove if tests pass.
                                                                // It's a KDBindings bug.
        d->m_visibleWidgetCountChangedConnection =
            m_layout->visibleWidgetCountChanged.connect(&Group::updateTitleBarVisibility, this);
        updateTitleBarVisibility();
        if (wasInMainWindow != isInMainWindow())
            Q_EMIT isInMainWindowChanged();
    }

    Q_EMIT isMDIChanged();
}

void Group::renameTab(int index, const QString &title)
{
    dynamic_cast<Views::GroupViewInterface *>(view())->renameTab(index, title);
}

void Group::changeTabIcon(int index, const QIcon &icon)
{
    dynamic_cast<Views::GroupViewInterface *>(view())->changeTabIcon(index, icon);
}

int Group::nonContentsHeight() const
{
    return dynamic_cast<Views::GroupViewInterface *>(view())->nonContentsHeight();
}

Controllers::Stack *Group::stack() const
{
    return m_stack;
}

Controllers::TabBar *Group::tabBar() const
{
    return m_stack->tabBar();
}

void Group::updateTitleAndIcon()
{
    if (DockWidget *dw = currentDockWidget()) {
        m_titleBar->setTitle(dw->title());
        m_titleBar->setIcon(dw->icon());

        if (auto fw = floatingWindow()) {
            if (fw->hasSingleFrame()) {
                fw->updateTitleAndIcon();
            }
        }

        setObjectName(dw->uniqueName());

    } else if (currentTabIndex() != -1) {
        qWarning() << Q_FUNC_INFO << "Invalid dock widget for group." << currentTabIndex();
    }
}

void Group::onDockWidgetTitleChanged()
{
    updateTitleAndIcon();

    if (!m_inCtor) { // don't call pure virtual in ctor
        if (auto dw = qobject_cast<DockWidget *>(sender())) {
            int index = indexOfDockWidget(dw);
            renameTab(index, dw->title());
            changeTabIcon(index, dw->icon(IconPlace::TabBar));
        }
    }
}

void Group::addTab(DockWidget *dockWidget, InitialOption addingOption)
{
    insertWidget(dockWidget, dockWidgetCount(), addingOption); // append
}

void Group::addTab(Group *group, InitialOption addingOption)
{
    if (group->isEmpty()) {
        qWarning() << "Group::addTab: group is empty." << group;
        return;
    }

    const auto &docks = group->dockWidgets();
    for (DockWidget *dockWidget : docks)
        addTab(dockWidget, addingOption);
}

void Group::addTab(FloatingWindow *floatingWindow, InitialOption addingOption)
{
    Q_ASSERT(floatingWindow);
    for (Group *f : floatingWindow->groups())
        addTab(f, addingOption);
}

void Group::insertWidget(DockWidget *dockWidget, int index, InitialOption addingOption)
{
    Q_ASSERT(dockWidget);
    if (containsDockWidget(dockWidget)) {
        if (!dockWidget->isPersistentCentralDockWidget())
            qWarning() << "Group::addTab dockWidget already exists. this=" << this
                       << "; dockWidget=" << dockWidget;
        return;
    }
    if (m_layoutItem)
        dockWidget->d->addPlaceholderItem(m_layoutItem);

    const int originalCurrentIndex = currentIndex();
    insertDockWidget(dockWidget, index);

    if (addingOption.startsHidden()) {
        dockWidget->view()->close(); // Ensure closed
    } else {
        if (hasSingleDockWidget()) {
            Q_EMIT m_tabBar->currentDockWidgetChanged(dockWidget);
            setObjectName(dockWidget->uniqueName());

            if (!m_layoutItem) {
                // When adding the 1st dock widget of a fresh group, let's give the group the size
                // of the dock widget, so that when adding it to the main window, the main window
                // can use that size as the initial suggested size.
                view()->resize(dockWidget->size());
            }
        } else if (addingOption.preservesCurrentTab() && originalCurrentIndex != -1) {
            setCurrentTabIndex(originalCurrentIndex);
        }
    }

    connect(dockWidget, &DockWidget::titleChanged, this, &Group::onDockWidgetTitleChanged);
    connect(dockWidget, &DockWidget::iconChanged, this, &Group::onDockWidgetTitleChanged);
}

void Group::removeWidget(DockWidget *dw)
{
    disconnect(dw, &DockWidget::titleChanged, this, &Group::onDockWidgetTitleChanged);
    disconnect(dw, &DockWidget::iconChanged, this, &Group::onDockWidgetTitleChanged);

    dynamic_cast<Views::GroupViewInterface *>(view())->removeWidget_impl(dw);
}

FloatingWindow *Group::detachTab(DockWidget *dockWidget)
{
    if (m_inCtor || m_inDtor)
        return nullptr;

    dockWidget->d->saveTabIndex();

    QRect r = dockWidget->geometry();
    removeWidget(dockWidget);

    auto newFrame = new Group();
    const QPoint globalPoint = mapToGlobal(QPoint(0, 0));
    newFrame->addTab(dockWidget);

    // We're potentially already dead at this point, as groups with 0 tabs auto-destruct. Don't
    // access members from this point.

    auto floatingWindow = new FloatingWindow(newFrame, {});
    r.moveTopLeft(globalPoint);
    floatingWindow->setSuggestedGeometry(r, SuggestedGeometryHint_GeometryIsFromDocked);
    floatingWindow->view()->show();

    return floatingWindow;
}

int Group::indexOfDockWidget(const DockWidget *dw)
{
    if (m_inCtor || m_inDtor)
        return -1;

    return m_tabBar->indexOfDockWidget(dw);
}

int Group::currentIndex() const
{
    if (m_inCtor || m_inDtor)
        return -1;

    return m_tabBar->currentIndex();
}

void Group::setCurrentTabIndex(int index)
{
    if (m_inCtor || m_inDtor)
        return;

    dynamic_cast<Views::GroupViewInterface *>(view())->setCurrentTabIndex_impl(index);
}

void Group::setCurrentDockWidget(DockWidget *dw)
{
    if (m_inCtor || m_inDtor)
        return;

    dynamic_cast<Views::GroupViewInterface *>(view())->setCurrentDockWidget_impl(dw);
}

void Group::insertDockWidget(DockWidget *dw, int index)
{
    if (m_inCtor || m_inDtor)
        return;

    dynamic_cast<Views::GroupViewInterface *>(view())->insertDockWidget_impl(dw, index);
    dw->d->onParentChanged();
}

Controllers::DockWidget *Group::dockWidgetAt(int index) const
{
    if (m_inCtor || m_inDtor)
        return nullptr;

    return dynamic_cast<Views::GroupViewInterface *>(view())->dockWidgetAt_impl(index);
}

Controllers::DockWidget *Group::currentDockWidget() const
{
    if (m_inCtor || m_inDtor)
        return nullptr;

    return dynamic_cast<Views::GroupViewInterface *>(view())->currentDockWidget_impl();
}

int Group::dockWidgetCount() const
{
    if (m_inCtor || m_inDtor)
        return 0;

    return m_stack->numDockWidgets();
}

void Group::onDockWidgetCountChanged()
{
    qCDebug(docking) << "Frame::onDockWidgetCountChanged:" << this
                     << "; widgetCount=" << dockWidgetCount();
    if (isEmpty() && !isCentralFrame()) {
        scheduleDeleteLater();
    } else {
        updateTitleBarVisibility();

        // We don't really keep track of the state, so emit even if the visibility didn't change. No
        // biggie.
        if (!(m_options & FrameOption_AlwaysShowsTabs))
            Q_EMIT hasTabsVisibleChanged();

        const DockWidget::List docks = dockWidgets();
        for (DockWidget *dock : docks)
            dock->d->updateFloatAction();
    }

    Q_EMIT numDockWidgetsChanged();
}

void Group::onCurrentTabChanged(int index)
{
    if (index != -1) {
        if (auto dock = dockWidgetAt(index)) {
            Q_EMIT m_tabBar->currentDockWidgetChanged(dock);
        } else {
            qWarning() << "dockWidgetAt" << index << "returned nullptr" << this;
        }
    }
}

void Group::isFocusedChangedCallback()
{
    Q_EMIT isFocusedChanged();
}

void Group::focusedWidgetChangedCallback()
{
    Q_EMIT focusedWidgetChanged();
}

void Group::updateTitleBarVisibility()
{
    if (m_updatingTitleBar || m_beingDeleted) {
        // To break a cyclic dependency
        return;
    }

    QScopedValueRollback<bool> guard(m_updatingTitleBar, true);

    bool visible = false;
    if (isCentralFrame()) {
        visible = false;
    } else if ((Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible)
               && hasTabsVisible()) {
        visible = false;
    } else if (FloatingWindow *fw = floatingWindow()) {
        // If there's nested groups then show each Frame's title bar
        visible = !fw->hasSingleFrame();
    } else if (isMDIWrapper()) {
        auto dropArea = this->mdiDropAreaWrapper();
        visible = !dropArea->hasSingleFrame();
    } else {
        visible = true;
    }

    const bool wasVisible = m_titleBar->view()->isVisible();
    m_titleBar->view()->setVisible(visible);

    if (wasVisible != visible) {
        Q_EMIT actualTitleBarChanged();
        for (auto dw : dockWidgets())
            Q_EMIT dw->actualTitleBarChanged();
    }

    if (auto fw = floatingWindow()) {
        // Update the floating window which might be using Flag_HideTitleBarWhenTabsVisible
        // In that case it might not show title bar depending on the number of tabs that the group
        // has
        fw->updateTitleBarVisibility();
    }
}

void Group::updateFloatingActions()
{
    const QVector<DockWidget *> widgets = dockWidgets();
    for (DockWidget *dw : widgets)
        dw->d->updateFloatAction();
}

bool Group::containsMouse(QPoint globalPos) const
{
    return rect().contains(view()->mapFromGlobal(globalPos));
}

Controllers::TitleBar *Group::titleBar() const
{
    return m_titleBar;
}

Controllers::TitleBar *Group::actualTitleBar() const
{
    if (FloatingWindow *fw = floatingWindow()) {
        // If there's nested groups then show each Group's title bar
        if (fw->hasSingleFrame())
            return fw->titleBar();
    } else if (auto mdiDropArea = mdiDropAreaWrapper()) {
        if (mdiDropArea->hasSingleFrame()) {
            return mdiFrame()->titleBar();
        }
    }

    return titleBar();
}

QString Group::title() const
{
    return m_titleBar->title();
}

QIcon Group::icon() const
{
    return m_titleBar->icon();
}

const Controllers::DockWidget::List Group::dockWidgets() const
{
    if (m_inCtor || m_inDtor)
        return {};

    DockWidget::List dockWidgets;
    const int count = dockWidgetCount();
    dockWidgets.reserve(count);
    for (int i = 0; i < count; ++i)
        dockWidgets << dockWidgetAt(i);

    return dockWidgets;
}

bool Group::containsDockWidget(DockWidget *dockWidget) const
{
    const int count = dockWidgetCount();
    for (int i = 0, e = count; i != e; ++i) {
        if (dockWidget == dockWidgetAt(i))
            return true;
    }
    return false;
}

FloatingWindow *Group::floatingWindow() const
{
    // Returns the first FloatingWindow* parent in the hierarchy.
    // However, if there's a MainWindow in the hierarchy it stops, which can
    // happen with nested main windows.

    auto p = view()->parentView();
    while (p) {
        if (p->is(Type::MainWindow))
            return nullptr;

        if (auto fw = p->asFloatingWindowController())
            return fw;

        if (p->equals(view()->rootView())) {
            // We stop at the window. (top-levels can have parent, but we're not interested)
            return nullptr;
        }

        p = p->parentView();
    }

    return nullptr;
}

void Group::restoreToPreviousPosition()
{
    if (hasSingleDockWidget()) {
        qWarning() << Q_FUNC_INFO << "Invalid usage, there's no tabs";
        return;
    }

    if (!m_layoutItem) {
        qCDebug(placeholder) << Q_FUNC_INFO << "There's no previous position known";
        return;
    }

    if (!m_layoutItem->isPlaceholder()) {
        // Maybe in this case just fold the group into the placeholder, which probably has other
        // dockwidgets which were added meanwhile. TODO
        qCDebug(placeholder) << Q_FUNC_INFO << "Previous position isn't a placeholder";
        return;
    }

    m_layoutItem->restore(view());
}

int Group::currentTabIndex() const
{
    return currentIndex();
}

bool Group::anyNonClosable() const
{
    for (auto dw : dockWidgets()) {
        if ((dw->options() & DockWidgetOption_NotClosable)
            && !Platform::instance()->isProcessingAppQuitEvent())
            return true;
    }

    return false;
}

bool Group::anyNonDockable() const
{
    for (auto dw : dockWidgets()) {
        if (dw->options() & DockWidgetOption_NotDockable)
            return true;
    }

    return false;
}

void Group::onDockWidgetShown(DockWidget *w)
{
    if (hasSingleDockWidget() && containsDockWidget(w)) { // We have to call contains because it
                                                          // might be being in process of being
                                                          // reparented
        if (!isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was shown, we're="
                            << "; visible=" << isVisible();
            setVisible(true);
        }
    }
}

void Group::onDockWidgetHidden(DockWidget *w)
{
    if (!isCentralFrame() && hasSingleDockWidget()
        && containsDockWidget(w)) { // We have to call contains because it might be being in process
                                    // of being reparented
        if (isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was hidden, we're="
                            << "; visible=" << isVisible() << "; dockWidgets=" << dockWidgets();
            setVisible(false);
        }
    }
}

void Group::setLayoutItem(Layouting::Item *item)
{
    if (item == m_layoutItem)
        return;

    if (m_layoutItem)
        m_layoutItem->unref();

    if (item)
        item->ref();

    m_layoutItem = item;
    if (item) {
        for (DockWidget *dw : dockWidgets())
            dw->d->addPlaceholderItem(item);
    } else {
        for (DockWidget *dw : dockWidgets())
            dw->d->lastPosition()->removePlaceholders();
    }
}

Layouting::Item *Group::layoutItem() const
{
    return m_layoutItem;
}

int Group::dbg_numFrames()
{
    return s_dbg_numFrames;
}

bool Group::beingDeletedLater() const
{
    return m_beingDeleted;
}

bool Group::hasTabsVisible() const
{
    if (m_beingDeleted)
        return false;

    return alwaysShowsTabs() || dockWidgetCount() > 1;
}

QStringList Group::affinities() const
{
    if (isEmpty()) {
        return {};
    } else {
        return dockWidgetAt(0)->affinities();
    }
}

bool Group::isTheOnlyFrame() const
{
    return m_layout && m_layout->visibleCount() == 1;
}

bool Group::isOverlayed() const
{
    return m_options & FrameOption_IsOverlayed;
}

void Group::unoverlay()
{
    m_options &= ~FrameOption_IsOverlayed;
}

bool Group::isFloating() const
{
    if (isInMainWindow() || isMDI())
        return false;

    return isTheOnlyFrame();
}

bool Group::isInFloatingWindow() const
{
    return floatingWindow() != nullptr;
}

bool Group::isInMainWindow() const
{
    return mainWindow() != nullptr;
}

Group *Group::deserialize(const LayoutSaver::Group &f)
{
    if (!f.isValid())
        return nullptr;

    const FrameOptions options = FrameOptions(f.options);
    Group *group = nullptr;
    const bool isPersistentCentralFrame = options & FrameOption::FrameOption_IsCentralFrame;

    if (isPersistentCentralFrame) {
        // Don't create a new Group if we're restoring the Persistent Central group (the one created
        // by MainWindowOption_HasCentralFrame). It already exists.

        if (f.mainWindowUniqueName.isEmpty()) {
            // Can happen with older serialization formats
            qWarning() << Q_FUNC_INFO << "Frame is the persistent central group but doesn't have"
                       << "an associated window name";
        } else {
            if (MainWindow *mw = DockRegistry::self()->mainWindowByName(f.mainWindowUniqueName)) {
                group = mw->dropArea()->m_centralFrame;
                if (!group) {
                    // Doesn't happen...
                    qWarning() << "Main window" << f.mainWindowUniqueName
                               << "doesn't have central group";
                }
            } else {
                // Doesn't happen...
                qWarning() << Q_FUNC_INFO << "Couldn't find main window" << f.mainWindowUniqueName;
            }
        }
    }

    if (!group)
        group = new Group(nullptr, options);

    group->setObjectName(f.objectName);

    for (const auto &savedDock : qAsConst(f.dockWidgets)) {
        if (DockWidget *dw = DockWidget::deserialize(savedDock)) {
            group->addTab(dw);
        }
    }

    group->setCurrentTabIndex(f.currentTabIndex);
    group->view()->setGeometry(f.geometry);

    return group;
}

LayoutSaver::Group Group::serialize() const
{
    LayoutSaver::Group group;
    group.isNull = false;

    const DockWidget::List docks = dockWidgets();

    group.objectName = objectName();
    group.geometry = geometry();
    group.options = options();
    group.currentTabIndex = currentTabIndex();
    group.id = view()->id(); // for coorelation purposes

    if (MainWindow *mw = mainWindow()) {
        group.mainWindowUniqueName = mw->uniqueName();
    }

    for (DockWidget *dock : docks)
        group.dockWidgets.push_back(dock->d->serialize());

    return group;
}

void Group::scheduleDeleteLater()
{
    qCDebug(creation) << Q_FUNC_INFO << this;
    m_beingDeleted = true;
    QTimer::singleShot(0, this, [this] {
        // Can't use deleteLater() here due to QTBUG-83030 (deleteLater() never delivered if
        // triggered by a sendEvent() before event loop starts)
        delete this;
    });
}

QSize Group::dockWidgetsMinSize() const
{
    QSize size = Layouting::Item::hardcodedMinimumSize;
    for (DockWidget *dw : dockWidgets())
        size = size.expandedTo(dw->view()->minSize());

    return size;
}

QSize Group::biggestDockWidgetMaxSize() const
{
    QSize size = Layouting::Item::hardcodedMaximumSize;
    for (DockWidget *dw : dockWidgets()) {
        const QSize dwMax = dw->view()->maxSizeHint();
        if (size == Layouting::Item::hardcodedMaximumSize) {
            size = dwMax;
            continue;
        }

        const bool hasMaxSize = dwMax != Layouting::Item::hardcodedMaximumSize;
        if (hasMaxSize)
            size = dwMax.expandedTo(size);
    }

    // Interpret 0 max-size as not having one too.
    if (size.width() == 0)
        size.setWidth(Layouting::Item::hardcodedMaximumSize.width());
    if (size.height() == 0)
        size.setHeight(Layouting::Item::hardcodedMaximumSize.height());

    return size;
}

QRect Group::dragRect() const
{
    QRect rect;
    if (m_titleBar->view()->isVisible()) {
        rect = m_titleBar->view()->rect();
        rect.moveTopLeft(m_titleBar->view()->mapToGlobal(QPoint(0, 0)));
    }

    if (rect.isValid())
        return rect;

    return dynamic_cast<Views::GroupViewInterface *>(view())->dragRect();
}

MainWindow *Group::mainWindow() const
{
    return m_layout ? m_layout->mainWindow() : nullptr;
}

///@brief Returns whether all dock widgets have the specified option set
bool Group::allDockWidgetsHave(DockWidgetOption option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::all_of(docks.cbegin(), docks.cend(),
                       [option](DockWidget *dw) { return dw->options() & option; });
}

///@brief Returns whether at least one dock widget has the specified option set
bool Group::anyDockWidgetsHas(DockWidgetOption option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::any_of(docks.cbegin(), docks.cend(),
                       [option](DockWidget *dw) { return dw->options() & option; });
}

bool Group::allDockWidgetsHave(LayoutSaverOption option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::all_of(docks.cbegin(), docks.cend(),
                       [option](DockWidget *dw) { return dw->layoutSaverOptions() & option; });
}

bool Group::anyDockWidgetsHas(LayoutSaverOption option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::any_of(docks.cbegin(), docks.cend(),
                       [option](DockWidget *dw) { return dw->layoutSaverOptions() & option; });
}

void Group::setAllowedResizeSides(CursorPositions sides)
{
    if (sides) {
        delete m_resizeHandler;
        m_resizeHandler = new WidgetResizeHandler(WidgetResizeHandler::EventFilterMode::Global,
                                                  WidgetResizeHandler::WindowMode::MDI, view());
        m_resizeHandler->setAllowedResizeSides(sides);
    } else {
        delete m_resizeHandler;
        m_resizeHandler = nullptr;
    }
}

bool Group::isMDI() const
{
    return mdiLayout() != nullptr;
}

bool Group::isMDIWrapper() const
{
    return mdiDropAreaWrapper() != nullptr;
}

Group *Group::mdiFrame() const
{
    if (auto dwWrapper = mdiDockWidgetWrapper()) {
        return dwWrapper->d->group();
    }

    return nullptr;
}

Controllers::DockWidget *Group::mdiDockWidgetWrapper() const
{
    if (auto dropArea = mdiDropAreaWrapper())
        return dropArea->view()->parentView()->asDockWidgetController();

    return nullptr;
}

DropArea *Group::mdiDropAreaWrapper() const
{
    auto p = view()->parentView();
    auto dropArea = p ? p->asDropAreaController() : nullptr;
    if (dropArea && dropArea->isMDIWrapper())
        return dropArea;
    return nullptr;
}

MDILayout *Group::mdiLayout() const
{
    return m_layout ? m_layout->asMDILayout() : nullptr;
}

bool Group::hasNestedMDIDockWidgets() const
{
    if (!isMDI() || dockWidgetCount() == 0)
        return false;

    if (dockWidgetCount() != 1) {
        qWarning() << Q_FUNC_INFO << "Expected a single dock widget wrapper as group child";
        return false;
    }

    return dockWidgetAt(0)->d->isMDIWrapper();
}

int Group::userType() const
{
    return m_userType;
}

WidgetResizeHandler *Group::resizeHandler() const
{
    return m_resizeHandler;
}

void Group::setParentView_impl(View *parent)
{
    Controller::setParentView_impl(parent);
    setLayout(parent ? parent->asLayout() : nullptr);
}
