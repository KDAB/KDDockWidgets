/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow_p.h"
#include "KDDockWidgets.h"
#include "MainWindowBase.h"
#include "Logging_p.h"
#include "Frame_p.h"
#include "TitleBar_p.h"
#include "WindowBeingDragged_p.h"
#include "Utils_p.h"
#include "WidgetResizeHandler_p.h"
#include "DockRegistry_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "DragController_p.h"
#include "LayoutSaver_p.h"
#include "DockWidgetBase_p.h"

#include "multisplitter/Item_p.h"

#include <QCloseEvent>
#include <QScopedValueRollback>
#include <QTimer>
#include <QWindow>

#if defined(Q_OS_WIN)
#if defined(Q_CC_MSVC)
// NOMINMAX tells windows.h not to define the max and min macros
// which will interfere with the max() from std::numeric_limits
#define NOMINMAX
#endif
#include <windows.h>
#include <dwmapi.h>
#endif

using namespace KDDockWidgets;

/** static */
Qt::WindowFlags FloatingWindow::s_windowFlagsOverride = {};

static Qt::WindowFlags windowFlagsToUse(FloatingWindowFlags requestedFlags)
{
    if (requestedFlags & FloatingWindowFlag::UseQtTool) {
        // User has explicitly chosen Qt::Tool for this FloatingWindow
        return Qt::Tool;
    }

    if (requestedFlags & FloatingWindowFlag::UseQtWindow) {
        // User has explicitly chosen Qt::Window for this FloatingWindow
        return Qt::Window;
    }

    if (FloatingWindow::s_windowFlagsOverride) {
        // User overridden the default for all FloatingWindows
        return FloatingWindow::s_windowFlagsOverride;
    }

    if (KDDockWidgets::usesNativeDraggingAndResizing())
        return Qt::Window;

    if (Config::self().internalFlags() & Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows)
        return Qt::Window;

    return Qt::Tool;
}

static MainWindowBase *hackFindParentHarder(Frame *frame, MainWindowBase *candidateParent)
{
    const FloatingWindowFlags requestedFlags = frame ? frame->requestedFloatingWindowFlags() : FloatingWindowFlag::FromGlobalConfig;
    if (requestedFlags & FloatingWindowFlag::DontUseParentForFloatingWindows) {
        // User explicitly requested no parent for this floating window
        return nullptr;
    }

    if (Config::self().internalFlags() & Config::InternalFlag_DontUseParentForFloatingWindows) {
        return nullptr;
    }

    // TODO: Using a parent helps the floating windows stay in front of the main window always.
    // We're not receiving the parent via ctor argument as the app can have multiple-main windows,
    // so use a hack here.
    // Not quite clear what to do if the app supports multiple main windows though.

    if (candidateParent)
        return candidateParent;

    const MainWindowBase::List windows = DockRegistry::self()->mainwindows();

    if (windows.isEmpty())
        return nullptr;

    if (windows.size() == 1) {
        return windows.first();
    } else {
        const QStringList affinities = frame ? frame->affinities() : QStringList();
        const MainWindowBase::List mainWindows = DockRegistry::self()->mainWindowsWithAffinity(affinities);

        if (mainWindows.isEmpty()) {
            qWarning() << Q_FUNC_INFO << "No window with affinity" << affinities << "found";
            return nullptr;
        } else {
            return mainWindows.first();
        }
    }
}

MainWindowBase *actualParent(MainWindowBase *candidate)
{
    return (Config::self().internalFlags() & Config::InternalFlag_DontUseParentForFloatingWindows)
        ? nullptr
        : candidate;
}

static FloatingWindowFlags flagsForFloatingWindow(FloatingWindowFlags requestedFlags)
{
    if (!(requestedFlags & FloatingWindowFlag::FromGlobalConfig)) {
        // User requested specific flags for this floating window
        return requestedFlags;
    }

    // Use from KDDockWidgets::Config instead. This is app-wide and not per window.

    FloatingWindowFlags flags = {};

    if ((Config::self().flags() & Config::Flag_TitleBarHasMinimizeButton) == Config::Flag_TitleBarHasMinimizeButton)
        flags |= FloatingWindowFlag::TitleBarHasMinimizeButton;

    if (Config::self().flags() & Config::Flag_TitleBarHasMaximizeButton)
        flags |= FloatingWindowFlag::TitleBarHasMaximizeButton;

    if (Config::self().flags() & Config::Flag_KeepAboveIfNotUtilityWindow)
        flags |= FloatingWindowFlag::KeepAboveIfNotUtilityWindow;

    if (Config::self().flags() & Config::Flag_NativeTitleBar)
        flags |= FloatingWindowFlag::NativeTitleBar;

    if (Config::self().flags() & Config::Flag_HideTitleBarWhenTabsVisible)
        flags |= FloatingWindowFlag::HideTitleBarWhenTabsVisible;

    if (Config::self().flags() & Config::Flag_AlwaysTitleBarWhenFloating)
        flags |= FloatingWindowFlag::AlwaysTitleBarWhenFloating;

    if (Config::self().internalFlags() & Config::InternalFlag_DontUseParentForFloatingWindows)
        flags |= FloatingWindowFlag::DontUseParentForFloatingWindows;

    if (Config::self().internalFlags() & Config::InternalFlag_DontUseQtToolWindowsForFloatingWindows)
        flags |= FloatingWindowFlag::UseQtWindow;

    return flags;
}

FloatingWindow::FloatingWindow(QRect suggestedGeometry, MainWindowBase *parent,
                               FloatingWindowFlags requestedFlags)
    : QWidgetAdapter(actualParent(parent), windowFlagsToUse(requestedFlags))
    , Draggable(this, KDDockWidgets::usesNativeDraggingAndResizing()) // FloatingWindow is only draggable when using a native title bar. Otherwise the KDDockWidgets::TitleBar is the draggable
    , m_flags(flagsForFloatingWindow(requestedFlags))
    , m_dropArea(new DropArea(this))
    , m_titleBar(Config::self().frameworkWidgetFactory()->createTitleBar(this))
{
    if (!suggestedGeometry.isNull())
        setGeometry(suggestedGeometry);

    if (kddwUsesQtWidgets()) {
        // For QtQuick we do it a bit later, once we have the QQuickWindow
#ifdef Q_OS_WIN
        create();
#ifdef KDDOCKWIDGETS_QTWIDGETS
        m_nchittestFilter = new NCHITTESTEventFilter(this);
        qApp->installNativeEventFilter(m_nchittestFilter);
#endif
        WidgetResizeHandler::setupWindow(windowHandle());
#endif
    }

    DockRegistry::self()->registerFloatingWindow(this);

    if (m_flags & FloatingWindowFlag::KeepAboveIfNotUtilityWindow)
        setWindowFlag(Qt::WindowStaysOnTopHint, true);

    if (kddwUsesQtWidgets()) {
        // QtQuick will do it a bit later, once it has a QWindow
        maybeCreateResizeHandler();
    }

    updateTitleBarVisibility();
    connect(m_dropArea, &LayoutWidget::visibleWidgetCountChanged, this,
            &FloatingWindow::onFrameCountChanged);
    connect(m_dropArea, &LayoutWidget::visibleWidgetCountChanged, this,
            &FloatingWindow::numFramesChanged);
    connect(m_dropArea, &LayoutWidget::visibleWidgetCountChanged, this,
            &FloatingWindow::onVisibleFrameCountChanged);
    m_layoutDestroyedConnection = connect(m_dropArea, &QObject::destroyed, this, &FloatingWindow::scheduleDeleteLater);
}

static FloatingWindowFlags floatingWindowFlagsForFrame(Frame *frame)
{
    if (!frame)
        return FloatingWindowFlag::FromGlobalConfig;

    return frame->requestedFloatingWindowFlags();
}

FloatingWindow::FloatingWindow(Frame *frame, QRect suggestedGeometry, MainWindowBase *parent)
    : FloatingWindow(suggestedGeometry, hackFindParentHarder(frame, parent), floatingWindowFlagsForFrame(frame))
{
    QScopedValueRollback<bool> guard(m_disableSetVisible, true);

    if (frame->hasNestedMDIDockWidgets()) {
        // When using DockWidget::MDINestable, the docked MDI widget is wrapped by a drop area so we can drop things into it.
        // When floating it, we can delete that helper drop area, as FloatingWindow already has one

        if (frame->dockWidgetCount() == 0) {
            // doesn't happen
            qWarning() << Q_FUNC_INFO << "Unexpected empty frame";
            return;
        }

        DockWidgetBase *dwMDIWrapper = frame->dockWidgetAt(0);
        DropArea *dropAreaMDIWrapper = dwMDIWrapper->d->mdiDropAreaWrapper();

        if (dropAreaMDIWrapper->hasSingleFrame()) {
            Frame *innerFrame = dropAreaMDIWrapper->frames().constFirst();
            if (innerFrame->hasSingleDockWidget()) {
                // When pressing the unfloat button, the dock widgets gets docked to the previous
                // position it was at. DockWidgetBase::Private::m_lastPosition stores that location,
                // however, when having nested MDI, we have an extra Dock Widget, the wrapper, and it
                // contains the last position. So, when floating, we need to transfer that and not lose it.
                DockWidgetBase *dw = innerFrame->dockWidgetAt(0);
                dw->d->lastPosition() = dwMDIWrapper->d->lastPosition();
            }
        }

        m_dropArea->addMultiSplitter(dropAreaMDIWrapper, Location_OnTop);
        dwMDIWrapper->setVisible(false);
        if (!DragController::instance()->isIdle()) {
            // We're dragging a MDI window and we reached the border, detaching it, and making it float. We can't delete the wrapper frame just yet,
            // as that would delete the title bar which is currently being dragged. Delete it once the drag finishes
            connect(DragController::instance(), &DragController::currentStateChanged, dwMDIWrapper, [dwMDIWrapper] {
                if (DragController::instance()->isIdle())
                    delete dwMDIWrapper;
            });
        } else {
            dwMDIWrapper->deleteLater();
        }

    } else {
        // Adding a widget will trigger onFrameCountChanged, which triggers a setVisible(true).
        // The problem with setVisible(true) will forget about or requested geometry and place the window at 0,0
        // So disable the setVisible(true) call while in the ctor.
        m_dropArea->addWidget(frame, KDDockWidgets::Location_OnTop, {});
    }
}

FloatingWindow::~FloatingWindow()
{
    m_inDtor = true;
    disconnect(m_layoutDestroyedConnection);
    delete m_nchittestFilter;

    DockRegistry::self()->unregisterFloatingWindow(this);
}

#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
bool FloatingWindow::nativeEvent(const QByteArray &eventType, void *message, Qt5Qt6Compat::qintptr *result)
{
    if (m_inDtor || m_deleteScheduled)
        return QWidget::nativeEvent(eventType, message, result);

    if (KDDockWidgets::usesAeroSnapWithCustomDecos()) {
        // To enable aero snap we need to tell Windows where's our custom title bar
        if (WidgetResizeHandler::handleWindowsNativeEvent(this, eventType, message, result))
            return true;
    } else if (KDDockWidgets::usesNativeTitleBar()) {
        auto msg = static_cast<MSG *>(message);
        if (msg->message == WM_SIZING) {
            // Cancel any drag if we're resizing
            Q_EMIT DragController::instance()->dragCanceled();
        }
    }

    return QWidget::nativeEvent(eventType, message, result);
}
#endif

void FloatingWindow::maybeCreateResizeHandler()
{
    if (!KDDockWidgets::usesNativeDraggingAndResizing()) {
        setFlag(Qt::FramelessWindowHint, true);
        // EGLFS can't have different mouse cursors per window, needs global filter hack to unset when cursor leaves
        const auto filterMode = isEGLFS() ? WidgetResizeHandler::EventFilterMode::Global
                                          : WidgetResizeHandler::EventFilterMode::Local;

        setWidgetResizeHandler(new WidgetResizeHandler(filterMode,
                                                       WidgetResizeHandler::WindowMode::TopLevel,
                                                       this));
    }
}

std::unique_ptr<WindowBeingDragged> FloatingWindow::makeWindow()
{
    return std::unique_ptr<WindowBeingDragged>(new WindowBeingDragged(this, this));
}

DockWidgetBase *FloatingWindow::singleDockWidget() const
{
    const Frame::List frames = this->frames();
    if (frames.size() == 1) {
        Frame *frame = frames.first();
        if (frame->hasSingleDockWidget())
            return frame->dockWidgetAt(0);
    }

    return nullptr;
}

const DockWidgetBase::List FloatingWindow::dockWidgets() const
{
    return m_dropArea->dockWidgets();
}

const Frame::List FloatingWindow::frames() const
{
    Q_ASSERT(m_dropArea);
    return m_dropArea->frames();
}

QSize FloatingWindow::maxSizeHint() const
{
    QSize result = Layouting::Item::hardcodedMaximumSize;

    if (!m_dropArea) {
        // Still early, no layout set
        return result;
    }

    const Frame::List frames = this->frames();
    if (frames.size() == 1) {
        // Let's honour max-size when we have a single-frame.
        // multi-frame cases are more complicated and we're not sure if we want the window to
        // bounce around. single-frame is the most common case, like floating a dock widget, so
        // let's do that first, it's also easy.
        Frame *frame = frames[0];
        if (frame->dockWidgetCount() == 1) { // We don't support if there's tabbing
            const QSize waste = (minimumSize() - frame->minSize()).expandedTo(QSize(0, 0));
            result = frame->maxSizeHint() + waste;
        }
    }

    // Semantically the result is fine, but bound it so we don't get:
    // QWidget::setMaximumSize: (/KDDockWidgets::FloatingWindowWidget) The largest allowed size is (16777215,16777215)
    return result.boundedTo(Layouting::Item::hardcodedMaximumSize);
}

void FloatingWindow::setSuggestedGeometry(QRect suggestedRect, SuggestedGeometryHints hint)
{
    const QSize maxSize = maxSizeHint();
    const bool hasMaxSize = maxSize != Layouting::Item::hardcodedMaximumSize;
    if (hasMaxSize) {
        // Resize to new size but preserve center
        const QPoint originalCenter = suggestedRect.center();
        suggestedRect.setSize(maxSize.boundedTo(suggestedRect.size()));

        if ((hint & SuggestedGeometryHint_GeometryIsFromDocked)
            && (m_flags & FloatingWindowFlag::NativeTitleBar)) {
            const QMargins margins = contentMargins();
            suggestedRect.setHeight(suggestedRect.height() - m_titleBar->height() + margins.top()
                                    + margins.bottom());
        }

        if (hint & SuggestedGeometryHint_PreserveCenter)
            suggestedRect.moveCenter(originalCenter);
    }

    ensureRectIsOnScreen(suggestedRect);

    setGeometry(suggestedRect);
}

void FloatingWindow::scheduleDeleteLater()
{
    m_deleteScheduled = true;
    DockRegistry::self()->unregisterFloatingWindow(this);
    deleteLater();
}

MultiSplitter *FloatingWindow::multiSplitter() const
{
    return m_dropArea;
}

LayoutWidget *FloatingWindow::layoutWidget() const
{
    return m_dropArea;
}

bool FloatingWindow::isInDragArea(QPoint globalPoint) const
{
#ifdef Q_OS_WIN
    // A click near the border will still send a Qt::NonClientMousePressEvent. We shouldn't
    // interpret that as a drag, as it's for a native resize.
    // Keep track of how we handled the WM_NCHITTEST
    if (usesAeroSnapWithCustomDecos())
        return m_lastHitTest == HTCAPTION;
#endif

    return dragRect().contains(globalPoint);
}

bool FloatingWindow::anyNonClosable() const
{
    for (Frame *frame : frames()) {
        if (frame->anyNonClosable())
            return true;
    }
    return false;
}

bool FloatingWindow::anyNonDockable() const
{
    for (Frame *frame : frames()) {
        if (frame->anyNonDockable())
            return true;
    }
    return false;
}

bool FloatingWindow::hasSingleFrame() const
{
    return m_dropArea->hasSingleFrame();
}

bool FloatingWindow::hasSingleDockWidget() const
{
    const Frame::List frames = this->frames();
    if (frames.size() != 1)
        return false;

    Frame *frame = frames.first();
    return frame->dockWidgetCount() == 1;
}

Frame *FloatingWindow::singleFrame() const
{
    const Frame::List frames = this->frames();

    return frames.isEmpty() ? nullptr
                            : frames.first();
}

bool FloatingWindow::beingDeleted() const
{
    if (m_deleteScheduled || m_inDtor)
        return true;

    // TODO: Confusing logic
    for (Frame *f : frames()) {
        if (!f->beingDeletedLater())
            return false;
    }

    return true;
}

void FloatingWindow::onFrameCountChanged(int count)
{
    if (count == 0) {
        scheduleDeleteLater();
    } else {
        updateTitleBarVisibility();
        if (count == 1) // if something was removed, then our single dock widget is floating, we need to check the QAction
            dropArea()->updateFloatingActions();
    }
}

void FloatingWindow::onVisibleFrameCountChanged(int count)
{
    if (m_disableSetVisible)
        return;

    updateSizeConstraints();
    setVisible(count > 0);
}

Qt::WindowState FloatingWindow::windowStateOverride() const
{
    Qt::WindowState state = Qt::WindowNoState;

    if (isMaximizedOverride())
        state = Qt::WindowMaximized;
    else if (isMinimizedOverride())
        state = Qt::WindowMinimized;

    return state;
}

void FloatingWindow::updateTitleBarVisibility()
{
    if (m_updatingTitleBarVisibility)
        return; // Break recursion

    QScopedValueRollback<bool> guard(m_updatingTitleBarVisibility, true);
    updateTitleAndIcon();

    bool visible = true;

    for (Frame *frame : frames())
        frame->updateTitleBarVisibility();

    if (KDDockWidgets::usesClientTitleBar()) {
        if ((m_flags & FloatingWindowFlag::HideTitleBarWhenTabsVisible) && !(m_flags & FloatingWindowFlag::AlwaysTitleBarWhenFloating)) {
            if (hasSingleFrame()) {
                visible = !frames().first()->hasTabsVisible();
            }
        }

        m_titleBar->updateButtons();
    } else {
        visible = false;
    }

    m_titleBar->setVisible(visible);
}

QStringList FloatingWindow::affinities() const
{
    auto frames = this->frames();
    return frames.isEmpty() ? QStringList() : frames.constFirst()->affinities();
}

void FloatingWindow::updateTitleAndIcon()
{
    QString title;
    QIcon icon;
    if (hasSingleFrame()) {
        const Frame *frame = frames().constFirst();
        title = frame->title();
        icon = frame->icon();
    } else {
        title = qApp->applicationName();
    }
    m_titleBar->setTitle(title);
    m_titleBar->setIcon(icon);

    // Even without a native title bar it's nice to set the window title/icon, so it shows
    // in the taskbar (when minimization is supported), or Alt-Tab (in supporting Window Managers)
    setWindowTitle(title);
    setWindowIcon(icon);
}

void FloatingWindow::onCloseEvent(QCloseEvent *e)
{
    if (e->spontaneous() && anyNonClosable()) {
        // Event from the window system won't close us
        e->ignore();
        return;
    }

    m_dropArea->onCloseEvent(e);
}

bool FloatingWindow::deserialize(const LayoutSaver::FloatingWindow &fw)
{
    if (dropArea()->deserialize(fw.multiSplitterLayout)) {
        updateTitleBarVisibility();

        if (fw.windowState & Qt::WindowMaximized) {
            showMaximized();
        } else if (fw.windowState & Qt::WindowMinimized) {
            showMinimized();
        } else {
            showNormal();
        }

        return true;
    } else {
        return false;
    }
}

LayoutSaver::FloatingWindow FloatingWindow::serialize() const
{
    LayoutSaver::FloatingWindow fw;

    fw.geometry = geometry();
    fw.normalGeometry = normalGeometry();
    fw.isVisible = isVisible();
    fw.multiSplitterLayout = dropArea()->serialize();
    fw.screenIndex = screenNumberForWidget(this);
    fw.screenSize = screenSizeForWidget(this);
    fw.affinities = affinities();
    fw.windowState = windowStateOverride();
    fw.flags = m_flags;

    auto mainWindow = qobject_cast<MainWindowBase *>(parentWidget());
    fw.parentIndex = mainWindow ? DockRegistry::self()->mainwindows().indexOf(mainWindow)
                                : -1;

    return fw;
}

QRect FloatingWindow::dragRect() const
{
    QRect rect;
    if (m_titleBar->isVisible()) {
        rect = m_titleBar->rect();
        rect.moveTopLeft(m_titleBar->mapToGlobal(QPoint(0, 0)));
    } else if (hasSingleFrame()) {
        rect = frames().constFirst()->dragRect();
    } else {
        qWarning() << Q_FUNC_INFO << "Expected a title bar";
    }

    return rect;
}

bool FloatingWindow::event(QEvent *ev)
{
    if (ev->type() == QEvent::ActivationChange) {
        // Since QWidget is missing a signal for window activation
        Q_EMIT activatedChanged();
    } else if (ev->type() == QEvent::StatusTip && parent()) {
        // show status tips in the main window
        return parent()->event(ev);
    } else if (ev->type() == QEvent::LayoutRequest) {
        updateSizeConstraints();
    }

    return QWidgetAdapter::event(ev);
}

bool FloatingWindow::allDockWidgetsHave(DockWidgetBase::Option option) const
{
    const Frame::List frames = this->frames();
    return std::all_of(frames.begin(), frames.end(), [option](Frame *frame) {
        return frame->allDockWidgetsHave(option);
    });
}

bool FloatingWindow::anyDockWidgetsHas(DockWidgetBase::Option option) const
{
    const Frame::List frames = this->frames();
    return std::any_of(frames.begin(), frames.end(), [option](Frame *frame) {
        return frame->anyDockWidgetsHas(option);
    });
}

bool FloatingWindow::allDockWidgetsHave(DockWidgetBase::LayoutSaverOption option) const
{
    const Frame::List frames = this->frames();
    return std::all_of(frames.begin(), frames.end(), [option](Frame *frame) {
        return frame->allDockWidgetsHave(option);
    });
}

bool FloatingWindow::anyDockWidgetsHas(DockWidgetBase::LayoutSaverOption option) const
{
    const Frame::List frames = this->frames();
    return std::any_of(frames.begin(), frames.end(), [option](Frame *frame) {
        return frame->anyDockWidgetsHas(option);
    });
}

void FloatingWindow::addDockWidget(DockWidgetBase *dw, Location location,
                                   DockWidgetBase *relativeTo, InitialOption option)
{
    m_dropArea->addDockWidget(dw, location, relativeTo, option);
}

bool FloatingWindow::isMDI() const
{
    return false;
}

bool FloatingWindow::isWindow() const
{
    return true;
}

MainWindowBase *FloatingWindow::mainWindow() const
{
    return qobject_cast<MainWindowBase *>(parent());
}

QMargins FloatingWindow::contentMargins() const
{
    return { 4, 4, 4, 4 };
}

bool FloatingWindow::isMaximizedOverride() const
{
    return QWidgetAdapter::isMaximized();
}

bool FloatingWindow::isMinimizedOverride() const
{
    return QWidgetAdapter::isMinimized();
}

void FloatingWindow::showMaximized()
{
    QWidgetAdapter::showMaximized();
}

void FloatingWindow::showNormal()
{
    QWidgetAdapter::showNormal();
}

void FloatingWindow::showMinimized()
{
    QWidgetAdapter::showMinimized();
}

QRect FloatingWindow::normalGeometry() const
{
    return QWidgetAdapter::normalGeometry();
}

Qt::WindowState FloatingWindow::lastWindowManagerState() const
{
    return m_lastWindowManagerState;
}

int FloatingWindow::userType() const
{
    if (Frame *f = singleFrame())
        return f->userType();
    return 0;
}

void FloatingWindow::updateSizeConstraints()
{
    // Doing a delayed call to make sure the layout has completled any ongoing operation.
    QTimer::singleShot(0, this, [this] {
        // Not simply using layout's max-size support because
        // 1) that's not portable to QtQuick
        // 2) QStackedLayout (from tab-widget) doesn't propagate size constraints up
        // Doing it manually instead.
        setMaximumSize(maxSizeHint());
    });
}

void FloatingWindow::ensureRectIsOnScreen(QRect &geometry)
{
    const auto screens = qApp->screens();
    if (screens.empty())
        return;

    int nearestDistSq = std::numeric_limits<int>::max();
    int nearestIndex = -1;

    const int screenCount = screens.count();
    for (int i = 0; i < screenCount; i++) {
        const QRect scrGeom = screens[i]->geometry();

        // If the rectangle is visible at all, we need do nothing
        if (scrGeom.intersects(geometry))
            return;

        // Find the nearest screen, so we can move the geometry onto it
        const QPoint dist2D = geometry.center() - scrGeom.center();
        const int distSq = (dist2D.x() * dist2D.x()) + (dist2D.y() * dist2D.y());
        if (distSq < nearestDistSq) {
            nearestDistSq = distSq;
            nearestIndex = i;
        }
    }

    // Move the rectangle to the nearest vertical and/or horizontal screen edge
    auto scrGeom = screens[nearestIndex]->geometry();
    scrGeom.moveTopLeft(scrGeom.topLeft() - screens[nearestIndex]->virtualGeometry().topLeft());

    if (geometry.left() < scrGeom.left()) {
        geometry.moveLeft(scrGeom.left());
    } else if (geometry.left() > scrGeom.right()) {
        geometry.moveRight(scrGeom.right());
    }

    if (geometry.top() < scrGeom.top()) {
        geometry.moveTop(scrGeom.top());
    } else if (geometry.top() > scrGeom.bottom()) {
        geometry.moveBottom(scrGeom.bottom());
    }
}

bool FloatingWindow::supportsMinimizeButton() const
{
    return m_flags & FloatingWindowFlag::TitleBarHasMinimizeButton;
}

bool FloatingWindow::supportsMaximizeButton() const
{
    return m_flags & FloatingWindowFlag::TitleBarHasMaximizeButton;
}

bool FloatingWindow::isUtilityWindow() const
{
    const bool dontUse = (m_flags & FloatingWindowFlag::DontUseParentForFloatingWindows) && (m_flags & FloatingWindowFlag::UseQtWindow);
    return !dontUse;
}

FloatingWindowFlags FloatingWindow::floatingWindowFlags() const
{
    return m_flags;
}
