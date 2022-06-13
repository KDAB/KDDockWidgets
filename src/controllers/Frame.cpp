/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Frame.h"

#include "kddockwidgets/Config.h"
#include "kddockwidgets/ViewFactory.h"

#include "Controller.h"
#include "View.h"
#include "Platform.h"
#include "views/Frame.h"

#include "controllers/TitleBar.h"
#include "controllers/Stack.h"
#include "controllers/FloatingWindow.h"
#include "controllers/MDILayout.h"
#include "controllers/DropArea.h"
#include "controllers/Layout.h"
#include "controllers/MainWindow.h"

#include "private/Logging_p.h"
#include "private/Utils_p.h"
#include "private/DockRegistry_p.h"
#include "DockWidget_p.h"
#include "private/LayoutSaver_p.h"
#include "private/Position_p.h"
#include "private/WidgetResizeHandler_p.h"
#include "private/multisplitter/Item_p.h"

#include <QCloseEvent>
#include <QTimer>

#define MARGIN_THRESHOLD 100

static int s_dbg_numFrames = 0;

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

namespace KDDockWidgets {

static FrameOptions actualOptions(FrameOptions options)
{
    if (Config::self().flags() & Config::Flag_AlwaysShowTabs)
        options |= FrameOption_AlwaysShowsTabs;

    return options;
}

static StackOptions tabWidgetOptions(FrameOptions options)
{
    if (options & FrameOption_NonDockable) {
        /// If we can't tab things into this Frame then let's not draw the QTabWidget frame either
        return StackOption_DocumentMode;
    }

    return StackOption_None;
}

}

Frame::Frame(View *parent, FrameOptions options, int userType)
    : Controller(Type::Frame, Config::self().viewFactory()->createFrame(this, parent))
    , FocusScope(view())
    , m_tabWidget(new Controllers::Stack(this, tabWidgetOptions(options)))
    , m_titleBar(new Controllers::TitleBar(this))
    , m_options(actualOptions(options))
    , m_userType(userType)
{
    s_dbg_numFrames++;
    DockRegistry::self()->registerFrame(this);

    connect(this, &Frame::currentDockWidgetChanged, this, &Frame::updateTitleAndIcon);
    connect(m_tabWidget, &Controllers::Stack::currentTabChanged,
            this, &Frame::onCurrentTabChanged);

    setLayout(parent ? parent->asLayout() : nullptr);
    view()->init();
    view()->closeRequested.connect([this](QCloseEvent *ev) {
        onCloseEvent(ev);
    });

    m_inCtor = false;
}

Frame::~Frame()
{
    m_inDtor = true;
    s_dbg_numFrames--;
    if (m_layoutItem)
        m_layoutItem->unref();

    delete m_resizeHandler;
    m_resizeHandler = nullptr;

    DockRegistry::self()->unregisterFrame(this);

    // Run some disconnects() too, so we don't receive signals during destruction:
    setLayout(nullptr);
    delete m_titleBar;
    delete m_tabWidget;
}

void Frame::onCloseEvent(QCloseEvent *e)
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

void Frame::setLayout(Layout *dt)
{
    if (dt == m_layout)
        return;

    const bool wasInMainWindow = dt && isInMainWindow();

    m_layout = dt;
    delete m_resizeHandler;
    m_resizeHandler = nullptr;

    if (m_layout) {
        if (isMDI())
            m_resizeHandler = new WidgetResizeHandler(/*topLevel=*/false, view());

        // We keep the connect result so we don't dereference m_layout at shutdown
        m_visibleWidgetCountChangedConnection->disconnect(); // TODOm3: Remove if tests pass. It's a KDBindings bug.
        m_visibleWidgetCountChangedConnection = m_layout->visibleWidgetCountChanged.connect(&Frame::updateTitleBarVisibility, this);
        updateTitleBarVisibility();
        if (wasInMainWindow != isInMainWindow())
            Q_EMIT isInMainWindowChanged();
    }

    Q_EMIT isMDIChanged();
}

void Frame::renameTab(int index, const QString &title)
{
    dynamic_cast<Views::Frame *>(view())->renameTab(index, title);
}

void Frame::changeTabIcon(int index, const QIcon &icon)
{
    dynamic_cast<Views::Frame *>(view())->changeTabIcon(index, icon);
}

void Frame::removeWidget_impl(DockWidget *dw)
{
    dynamic_cast<Views::Frame *>(view())->removeWidget_impl(dw);
}

int Frame::indexOfDockWidget_impl(const DockWidget *dw)
{
    return dynamic_cast<Views::Frame *>(view())->indexOfDockWidget_impl(dw);
}

int Frame::currentIndex_impl() const
{
    return dynamic_cast<Views::Frame *>(view())->currentIndex_impl();
}

void Frame::setCurrentTabIndex_impl(int index)
{
    dynamic_cast<Views::Frame *>(view())->setCurrentTabIndex_impl(index);
}

void Frame::setCurrentDockWidget_impl(DockWidget *dw)
{
    dynamic_cast<Views::Frame *>(view())->setCurrentDockWidget_impl(dw);
}

void Frame::insertDockWidget_impl(DockWidget *dw, int index)
{
    dynamic_cast<Views::Frame *>(view())->insertDockWidget_impl(dw, index);
}

Controllers::DockWidget *Frame::dockWidgetAt_impl(int index) const
{
    return dynamic_cast<Views::Frame *>(view())->dockWidgetAt_impl(index);
}

Controllers::DockWidget *Frame::currentDockWidget_impl() const
{
    return dynamic_cast<Views::Frame *>(view())->currentDockWidget_impl();
}

int Frame::nonContentsHeight() const
{
    return dynamic_cast<Views::Frame *>(view())->nonContentsHeight();
}

Controllers::Stack *Frame::tabWidget() const
{
    return m_tabWidget;
}

Controllers::TabBar *Frame::tabBar() const
{
    return m_tabWidget->tabBar();
}

void Frame::updateTitleAndIcon()
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
        qWarning() << Q_FUNC_INFO << "Invalid dock widget for frame." << currentTabIndex();
    }
}

void Frame::onDockWidgetTitleChanged()
{
    updateTitleAndIcon();

    if (!m_inCtor) { // don't call pure virtual in ctor
        if (auto dw = qobject_cast<DockWidget *>(sender())) {
            int index = indexOfDockWidget(dw);
            renameTab(index, dw->title());
            changeTabIcon(index, dw->icon(DockWidget::IconPlace::TabBar));
        }
    }
}

void Frame::addWidget(DockWidget *dockWidget, InitialOption addingOption)
{
    insertWidget(dockWidget, dockWidgetCount(), addingOption); // append
}

void Frame::addWidget(Frame *frame, InitialOption addingOption)
{
    if (frame->isEmpty()) {
        qWarning() << "Frame::addWidget: frame is empty." << frame;
        return;
    }

    const auto &docks = frame->dockWidgets();
    for (DockWidget *dockWidget : docks)
        addWidget(dockWidget, addingOption);
}

void Frame::addWidget(FloatingWindow *floatingWindow, InitialOption addingOption)
{
    Q_ASSERT(floatingWindow);
    for (Frame *f : floatingWindow->frames())
        addWidget(f, addingOption);
}

void Frame::insertWidget(DockWidget *dockWidget, int index, InitialOption addingOption)
{
    Q_ASSERT(dockWidget);
    if (containsDockWidget(dockWidget)) {
        if (!dockWidget->isPersistentCentralDockWidget())
            qWarning() << "Frame::addWidget dockWidget already exists. this=" << this << "; dockWidget=" << dockWidget;
        return;
    }
    if (m_layoutItem)
        dockWidget->d->addPlaceholderItem(m_layoutItem);

    insertDockWidget(dockWidget, index);

    if (addingOption.startsHidden()) {
        dockWidget->view()->close(); // Ensure closed
    } else {
        if (hasSingleDockWidget()) {
            Q_EMIT currentDockWidgetChanged(dockWidget);
            setObjectName(dockWidget->uniqueName());

            if (!m_layoutItem) {
                // When adding the 1st dock widget of a fresh frame, let's give the frame the size
                // of the dock widget, so that when adding it to the main window, the main window can
                // use that size as the initial suggested size.
                view()->resize(dockWidget->size());
            }
        }
    }

    connect(dockWidget, &DockWidget::titleChanged, this, &Frame::onDockWidgetTitleChanged);
    connect(dockWidget, &DockWidget::iconChanged, this, &Frame::onDockWidgetTitleChanged);
}

void Frame::removeWidget(DockWidget *dw)
{
    disconnect(dw, &DockWidget::titleChanged, this, &Frame::onDockWidgetTitleChanged);
    disconnect(dw, &DockWidget::iconChanged, this, &Frame::onDockWidgetTitleChanged);
    removeWidget_impl(dw);
}

FloatingWindow *Frame::detachTab(DockWidget *dockWidget)
{
    if (m_inCtor || m_inDtor)
        return nullptr;

    dockWidget->d->saveTabIndex();

    QRect r = dockWidget->geometry();
    removeWidget(dockWidget);

    auto newFrame = new Frame();
    const QPoint globalPoint = mapToGlobal(QPoint(0, 0));
    newFrame->addWidget(dockWidget);

    // We're potentially already dead at this point, as frames with 0 tabs auto-destruct. Don't access members from this point.

    auto floatingWindow = new FloatingWindow(newFrame, {});
    r.moveTopLeft(globalPoint);
    floatingWindow->setSuggestedGeometry(r, SuggestedGeometryHint_GeometryIsFromDocked);
    floatingWindow->view()->show();

    return floatingWindow;
}

int Frame::indexOfDockWidget(const DockWidget *dw)
{
    if (m_inCtor || m_inDtor)
        return -1;

    return indexOfDockWidget_impl(dw);
}

int Frame::currentIndex() const
{
    if (m_inCtor || m_inDtor)
        return -1;

    return currentIndex_impl();
}

void Frame::setCurrentTabIndex(int index)
{
    if (m_inCtor || m_inDtor)
        return;

    setCurrentTabIndex_impl(index);
}

void Frame::setCurrentDockWidget(DockWidget *dw)
{
    if (m_inCtor || m_inDtor)
        return;

    setCurrentDockWidget_impl(dw);
}

void Frame::insertDockWidget(DockWidget *dw, int index)
{
    if (m_inCtor || m_inDtor)
        return;

    insertDockWidget_impl(dw, index);
}

Controllers::DockWidget *Frame::dockWidgetAt(int index) const
{
    if (m_inCtor || m_inDtor)
        return nullptr;

    return dockWidgetAt_impl(index);
}

Controllers::DockWidget *Frame::currentDockWidget() const
{
    if (m_inCtor || m_inDtor)
        return nullptr;

    return currentDockWidget_impl();
}

int Frame::dockWidgetCount() const
{
    if (m_inCtor || m_inDtor)
        return 0;

    return m_tabWidget->numDockWidgets();
}

void Frame::onDockWidgetCountChanged()
{
    qCDebug(docking) << "Frame::onDockWidgetCountChanged:" << this << "; widgetCount=" << dockWidgetCount();
    if (isEmpty() && !isCentralFrame()) {
        scheduleDeleteLater();
    } else {
        updateTitleBarVisibility();

        // We don't really keep track of the state, so emit even if the visibility didn't change. No biggie.
        if (!(m_options & FrameOption_AlwaysShowsTabs))
            Q_EMIT hasTabsVisibleChanged();

        const DockWidget::List docks = dockWidgets();
        for (DockWidget *dock : docks)
            dock->d->updateFloatAction();
    }

    Q_EMIT numDockWidgetsChanged();
}

void Frame::onCurrentTabChanged(int index)
{
    if (index != -1) {
        if (auto dock = dockWidgetAt(index)) {
            Q_EMIT currentDockWidgetChanged(dock);
        } else {
            qWarning() << "dockWidgetAt" << index << "returned nullptr" << this;
        }
    }
}

void Frame::isFocusedChangedCallback()
{
    Q_EMIT isFocusedChanged();
}

void Frame::focusedWidgetChangedCallback()
{
    Q_EMIT focusedWidgetChanged();
}

void Frame::updateTitleBarVisibility()
{
    if (m_updatingTitleBar || m_beingDeleted) {
        // To break a cyclic dependency
        return;
    }

    QScopedValueRollback<bool> guard(m_updatingTitleBar, true);

    bool visible = false;
    if (isCentralFrame()) {
        visible = false;
    } else if ((Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible) && hasTabsVisible()) {
        visible = false;
    } else if (FloatingWindow *fw = floatingWindow()) {
        // If there's nested frames then show each Frame's title bar
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
        // In that case it might not show title bar depending on the number of tabs that the frame has
        fw->updateTitleBarVisibility();
    }
}

void Frame::updateFloatingActions()
{
    const QVector<DockWidget *> widgets = dockWidgets();
    for (DockWidget *dw : widgets)
        dw->d->updateFloatAction();
}

bool Frame::containsMouse(QPoint globalPos) const
{
    return rect().contains(view()->mapFromGlobal(globalPos));
}

Controllers::TitleBar *Frame::titleBar() const
{
    return m_titleBar;
}

Controllers::TitleBar *Frame::actualTitleBar() const
{
    if (FloatingWindow *fw = floatingWindow()) {
        // If there's nested frames then show each Frame's title bar
        if (fw->hasSingleFrame())
            return fw->titleBar();
    } else if (auto mdiDropArea = mdiDropAreaWrapper()) {
        if (mdiDropArea->hasSingleFrame()) {
            return mdiFrame()->titleBar();
        }
    }

    return titleBar();
}

QString Frame::title() const
{
    return m_titleBar->title();
}

QIcon Frame::icon() const
{
    return m_titleBar->icon();
}

const Controllers::DockWidget::List Frame::dockWidgets() const
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

bool Frame::containsDockWidget(DockWidget *dockWidget) const
{
    const int count = dockWidgetCount();
    for (int i = 0, e = count; i != e; ++i) {
        if (dockWidget == dockWidgetAt(i))
            return true;
    }
    return false;
}

FloatingWindow *Frame::floatingWindow() const
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

void Frame::restoreToPreviousPosition()
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
        // Maybe in this case just fold the frame into the placeholder, which probably has other dockwidgets which were added meanwhile. TODO
        qCDebug(placeholder) << Q_FUNC_INFO << "Previous position isn't a placeholder";
        return;
    }

    m_layoutItem->restore(view());
}

int Frame::currentTabIndex() const
{
    return currentIndex();
}

bool Frame::anyNonClosable() const
{
    for (auto dw : dockWidgets()) {
        if ((dw->options() & DockWidget::Option_NotClosable) && !DockRegistry::self()->isProcessingAppQuitEvent())
            return true;
    }

    return false;
}

bool Frame::anyNonDockable() const
{
    for (auto dw : dockWidgets()) {
        if (dw->options() & DockWidget::Option_NotDockable)
            return true;
    }

    return false;
}

void Frame::onDockWidgetShown(DockWidget *w)
{
    if (hasSingleDockWidget() && containsDockWidget(w)) { // We have to call contains because it might be being in process of being reparented
        if (!isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was shown, we're="
                            << "; visible="
                            << isVisible();
            setVisible(true);
        }
    }
}

void Frame::onDockWidgetHidden(DockWidget *w)
{
    if (!isCentralFrame() && hasSingleDockWidget() && containsDockWidget(w)) { // We have to call contains because it might be being in process of being reparented
        if (isVisible()) {
            qCDebug(hiding) << "Widget" << w << " was hidden, we're="
                            << "; visible=" << isVisible()
                            << "; dockWidgets=" << dockWidgets();
            setVisible(false);
        }
    }
}

void Frame::setLayoutItem(Layouting::Item *item)
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

Layouting::Item *Frame::layoutItem() const
{
    return m_layoutItem;
}

int Frame::dbg_numFrames()
{
    return s_dbg_numFrames;
}

bool Frame::beingDeletedLater() const
{
    return m_beingDeleted;
}

bool Frame::hasTabsVisible() const
{
    if (m_beingDeleted)
        return false;

    return alwaysShowsTabs() || dockWidgetCount() > 1;
}

QStringList Frame::affinities() const
{
    if (isEmpty()) {
        return {};
    } else {
        return dockWidgetAt(0)->affinities();
    }
}

bool Frame::isTheOnlyFrame() const
{
    return m_layout && m_layout->visibleCount() == 1;
}

bool Frame::isOverlayed() const
{
    return m_options & FrameOption_IsOverlayed;
}

void Frame::unoverlay()
{
    m_options &= ~FrameOption_IsOverlayed;
}

bool Frame::isFloating() const
{
    if (isInMainWindow() || isMDI())
        return false;

    return isTheOnlyFrame();
}

bool Frame::isInFloatingWindow() const
{
    return floatingWindow() != nullptr;
}

bool Frame::isInMainWindow() const
{
    return mainWindow() != nullptr;
}

Frame *Frame::deserialize(const LayoutSaver::Frame &f)
{
    if (!f.isValid())
        return nullptr;

    const FrameOptions options = FrameOptions(f.options);
    Frame *frame = nullptr;
    const bool isPersistentCentralFrame = options & FrameOption::FrameOption_IsCentralFrame;

    if (isPersistentCentralFrame) {
        // Don't create a new Frame if we're restoring the Persistent Central frame (the one created
        // by MainWindowOption_HasCentralFrame). It already exists.

        if (f.mainWindowUniqueName.isEmpty()) {
            // Can happen with older serialization formats
            qWarning() << Q_FUNC_INFO << "Frame is the persistent central frame but doesn't have"
                       << "an associated window name";
        } else {
            if (MainWindow *mw = DockRegistry::self()->mainWindowByName(f.mainWindowUniqueName)) {
                frame = mw->dropArea()->m_centralFrame;
                if (!frame) {
                    // Doesn't happen...
                    qWarning() << "Main window" << f.mainWindowUniqueName << "doesn't have central frame";
                }
            } else {
                // Doesn't happen...
                qWarning() << Q_FUNC_INFO << "Couldn't find main window"
                           << f.mainWindowUniqueName;
            }
        }
    }

    if (!frame)
        frame = new Frame(nullptr, options);

    frame->setObjectName(f.objectName);

    for (const auto &savedDock : qAsConst(f.dockWidgets)) {
        if (DockWidget *dw = DockWidget::deserialize(savedDock)) {
            frame->addWidget(dw);
        }
    }

    frame->setCurrentTabIndex(f.currentTabIndex);
    frame->view()->setGeometry(f.geometry);

    return frame;
}

LayoutSaver::Frame Frame::serialize() const
{
    LayoutSaver::Frame frame;
    frame.isNull = false;

    const DockWidget::List docks = dockWidgets();

    frame.objectName = objectName();
    frame.geometry = geometry();
    frame.options = options();
    frame.currentTabIndex = currentTabIndex();
    frame.id = view()->id(); // for coorelation purposes

    if (MainWindow *mw = mainWindow()) {
        frame.mainWindowUniqueName = mw->uniqueName();
    }

    for (DockWidget *dock : docks)
        frame.dockWidgets.push_back(dock->d->serialize());

    return frame;
}

void Frame::scheduleDeleteLater()
{
    qCDebug(creation) << Q_FUNC_INFO << this;
    m_beingDeleted = true;
    QTimer::singleShot(0, this, [this] {
        // Can't use deleteLater() here due to QTBUG-83030 (deleteLater() never delivered if triggered by a sendEvent() before event loop starts)
        delete this;
    });
}

QSize Frame::dockWidgetsMinSize() const
{
    QSize size = Layouting::Item::hardcodedMinimumSize;
    for (DockWidget *dw : dockWidgets())
        size = size.expandedTo(dw->view()->minSize());

    return size;
}

QSize Frame::biggestDockWidgetMaxSize() const
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
            size = dw->view()->maximumSize().expandedTo(size);
    }

    // Interpret 0 max-size as not having one too.
    if (size.width() == 0)
        size.setWidth(Layouting::Item::hardcodedMaximumSize.width());
    if (size.height() == 0)
        size.setHeight(Layouting::Item::hardcodedMaximumSize.height());

    return size;
}

QRect Frame::dragRect() const
{
    QRect rect;
    if (m_titleBar->view()->isVisible()) {
        rect = m_titleBar->view()->rect();
        rect.moveTopLeft(m_titleBar->view()->mapToGlobal(QPoint(0, 0)));
    }

    if (rect.isValid())
        return rect;

    return dynamic_cast<Views::Frame *>(view())->dragRect();
}

MainWindow *Frame::mainWindow() const
{
    return m_layout ? m_layout->mainWindow() : nullptr;
}

///@brief Returns whether all dock widgets have the specified option set
bool Frame::allDockWidgetsHave(DockWidget::Option option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::all_of(docks.cbegin(), docks.cend(), [option](DockWidget *dw) {
        return dw->options() & option;
    });
}

///@brief Returns whether at least one dock widget has the specified option set
bool Frame::anyDockWidgetsHas(DockWidget::Option option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::any_of(docks.cbegin(), docks.cend(), [option](DockWidget *dw) {
        return dw->options() & option;
    });
}

bool Frame::allDockWidgetsHave(DockWidget::LayoutSaverOption option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::all_of(docks.cbegin(), docks.cend(), [option](DockWidget *dw) {
        return dw->layoutSaverOptions() & option;
    });
}

bool Frame::anyDockWidgetsHas(DockWidget::LayoutSaverOption option) const
{
    const DockWidget::List docks = dockWidgets();
    return std::any_of(docks.cbegin(), docks.cend(), [option](DockWidget *dw) {
        return dw->layoutSaverOptions() & option;
    });
}

void Frame::setAllowedResizeSides(CursorPositions sides)
{
    if (sides) {
        delete m_resizeHandler;
        m_resizeHandler = new WidgetResizeHandler(/*topLevel=*/false, view());
        m_resizeHandler->setAllowedResizeSides(sides);
    } else {
        delete m_resizeHandler;
        m_resizeHandler = nullptr;
    }
}

bool Frame::isMDI() const
{
    return mdiLayoutWidget() != nullptr;
}

bool Frame::isMDIWrapper() const
{
    return mdiDropAreaWrapper() != nullptr;
}

Frame *Frame::mdiFrame() const
{
    if (auto dwWrapper = mdiDockWidgetWrapper()) {
        return dwWrapper->d->frame();
    }

    return nullptr;
}

Controllers::DockWidget *Frame::mdiDockWidgetWrapper() const
{
    if (auto dropArea = mdiDropAreaWrapper())
        return dropArea->view()->parentView()->asDockWidgetController();

    return nullptr;
}

DropArea *Frame::mdiDropAreaWrapper() const
{
    auto p = view()->parentView();
    auto dropArea = p ? p->asDropAreaController() : nullptr;
    if (dropArea && dropArea->isMDIWrapper())
        return dropArea;
    return nullptr;
}

MDILayout *Frame::mdiLayoutWidget() const
{
    return m_layout ? m_layout->asMDILayout() : nullptr;
}

bool Frame::hasNestedMDIDockWidgets() const
{
    if (!isMDI() || dockWidgetCount() == 0)
        return false;

    if (dockWidgetCount() != 1) {
        qWarning() << Q_FUNC_INFO << "Expected a single dock widget wrapper as frame child";
        return false;
    }

    return dockWidgetAt(0)->d->isMDIWrapper();
}

int Frame::userType() const
{
    return m_userType;
}

WidgetResizeHandler *Frame::resizeHandler() const
{
    return m_resizeHandler;
}
