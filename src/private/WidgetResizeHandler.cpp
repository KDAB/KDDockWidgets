/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "WidgetResizeHandler_p.h"
#include "FloatingWindow_p.h"
#include "TitleBar_p.h"
#include "DragController_p.h"
#include "Config.h"
#include "Qt5Qt6Compat_p.h"
#include "Utils_p.h"

#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>

#if defined(Q_OS_WIN)
# include <QtGui/private/qhighdpiscaling_p.h>
# include <windowsx.h>
# include <windows.h>
# include <dwmapi.h>
# if defined(Q_CC_MSVC)
#  pragma comment(lib,"User32.lib")
# endif
#endif

using namespace KDDockWidgets;

bool WidgetResizeHandler::s_disableAllHandlers = false;
WidgetResizeHandler::WidgetResizeHandler(bool isTopLevelResizer, QWidgetOrQuick *target)
    : QObject(target)
    , m_isTopLevelWindowResizer(isTopLevelResizer)
{
    setTarget(target);
}

WidgetResizeHandler::~WidgetResizeHandler()
{
}

void WidgetResizeHandler::setAllowedResizeSides(CursorPositions sides)
{
    mAllowedResizeSides = sides;
}

void WidgetResizeHandler::setResizeGap(int gap)
{
    m_resizeGap = gap;
}

bool WidgetResizeHandler::isMDI() const
{
    auto frame = qobject_cast<Frame*>(mTarget);
    return frame && frame->isMDI();
}

int WidgetResizeHandler::widgetResizeHandlerMargin()
{
    return 4; // pixels
}

bool WidgetResizeHandler::eventFilter(QObject *o, QEvent *e)
{
    if (s_disableAllHandlers)
        return false;

    auto widget = qobject_cast<QWidgetOrQuick*>(o);

#ifdef KDDOCKWIDGETS_QTWIDGETS
    if (!widget)
        return false;

    if (m_isTopLevelWindowResizer && (!widget->isTopLevel() || o != mTarget))
        return false;
#else

    // The QtQuick case is a bit different, as the Frame QQuickItem doesn't receive the MouseMove
    // events, the QWindow does. (The frame instead receives HoverMove).
    // So, if widget is nullptr we still allow for the case of it being a mouse move event
    // to the QWindow

    if (m_isTopLevelWindowResizer) {
        if (!widget)
            return false;

        if (!widget->isTopLevel() || o != mTarget)
            return false;
    } else {
        if (!isMDI()) {
            // For QtQuick we only support the MDI case
            return false;
        }

        if (!widget) {
            auto qquickWindow = qobject_cast<QQuickWindow*>(o);
            if (!(qquickWindow && e->type() == QEvent::MouseMove))
                return false;
        }
    }

#endif

    switch (e->type()) {
    case QEvent::MouseButtonPress: {
        if (mTarget->isMaximized())
            break;
        auto mouseEvent = static_cast<QMouseEvent *>(e);
        auto cursorPos = cursorPosition(Qt5Qt6Compat::eventGlobalPos(mouseEvent));
        if (cursorPos == CursorPosition_Undefined)
            return false;

        const int m = widgetResizeHandlerMargin();
        const QRect widgetRect = mTarget->rect().marginsAdded(QMargins(m, m, m, m));
        const QPoint cursorPoint = mTarget->mapFromGlobal(Qt5Qt6Compat::eventGlobalPos(mouseEvent));
        if (!widgetRect.contains(cursorPoint) || mouseEvent->button() != Qt::LeftButton)
            return false;

        m_resizingInProgress = true;
        mNewPosition = Qt5Qt6Compat::eventGlobalPos(mouseEvent);
        mCursorPos = cursorPos;

        return true;
    }
    case QEvent::MouseButtonRelease: {
        m_resizingInProgress = false;
        auto mouseEvent = static_cast<QMouseEvent *>(e);

        if (mTarget->isMaximized() || !m_resizingInProgress || mouseEvent->button() != Qt::LeftButton)
            break;

        mTarget->releaseMouse();
        mTarget->releaseKeyboard();
        return true;

        break;
    }
    case QEvent::MouseMove: {
        if (mTarget->isMaximized())
            break;
        auto mouseEvent = static_cast<QMouseEvent *>(e);
        m_resizingInProgress = m_resizingInProgress && (mouseEvent->buttons() & Qt::LeftButton);
        const bool state = m_resizingInProgress;
        if (m_isTopLevelWindowResizer)
            m_resizingInProgress = ((o == mTarget) && m_resizingInProgress);
        const bool consumed = mouseMoveEvent(mouseEvent);
        m_resizingInProgress = state;
        return consumed;
    }
    default:
        break;
    }
    return false;
}

bool WidgetResizeHandler::mouseMoveEvent(QMouseEvent *e)
{
    const QPoint globalPos = Qt5Qt6Compat::eventGlobalPos(e);
    if (!m_resizingInProgress) {
        const CursorPosition pos = cursorPosition(globalPos);
        updateCursor(pos);
        return pos != CursorPosition_Undefined;
    }

    const QRect oldGeometry = KDDockWidgets::globalGeometry(mTarget);
    QRect newGeometry = oldGeometry;

    QRect parentGeometry;
    if (!mTarget->isTopLevel()) {
        auto parent = KDDockWidgets::Private::parentWidget(mTarget);
        parentGeometry = KDDockWidgets::globalGeometry(parent);
    }

    {
        int deltaWidth = 0;
        int newWidth = 0;
        const int maxWidth = Layouting::Widget::widgetMaxSize(mTarget).width();
        const int minWidth = Layouting::Widget::widgetMinSize(mTarget).width();

        switch (mCursorPos) {
        case CursorPosition_TopLeft:
        case CursorPosition_Left:
        case CursorPosition_BottomLeft: {
            parentGeometry = parentGeometry.adjusted(0, m_resizeGap, 0, 0);
            deltaWidth = oldGeometry.left() - globalPos.x();
            newWidth = qBound(minWidth, mTarget->width() + deltaWidth, maxWidth);
            deltaWidth = newWidth - mTarget->width();
            if (deltaWidth != 0) {
                newGeometry.setLeft(newGeometry.left() - deltaWidth);
            }

            break;
        }

        case CursorPosition_TopRight:
        case CursorPosition_Right:
        case CursorPosition_BottomRight: {
            parentGeometry = parentGeometry.adjusted(0, 0, -m_resizeGap, 0);
            deltaWidth = globalPos.x() - newGeometry.right();
            newWidth = qBound(minWidth, mTarget->width() + deltaWidth, maxWidth);
            deltaWidth = newWidth - mTarget->width();
            if (deltaWidth != 0) {
                newGeometry.setRight(oldGeometry.right() + deltaWidth);
            }
            break;
        }
        default:
            break;
        }
    }

    {
        const int maxHeight = Layouting::Widget::widgetMaxSize(mTarget).height();
        const int minHeight = Layouting::Widget::widgetMinSize(mTarget).height();
        int deltaHeight = 0;
        int newHeight = 0;
        switch (mCursorPos) {
        case CursorPosition_TopLeft:
        case CursorPosition_Top:
        case CursorPosition_TopRight: {
            parentGeometry = parentGeometry.adjusted(0, m_resizeGap, 0, 0);
            deltaHeight = oldGeometry.top() - globalPos.y();
            newHeight = qBound(minHeight, mTarget->height() + deltaHeight, maxHeight);
            deltaHeight = newHeight - mTarget->height();
            if (deltaHeight != 0) {
                newGeometry.setTop(newGeometry.top() - deltaHeight);
            }

            break;
        }

        case CursorPosition_BottomLeft:
        case CursorPosition_Bottom:
        case CursorPosition_BottomRight: {
            parentGeometry = parentGeometry.adjusted(0, 0, 0, -m_resizeGap);
            deltaHeight = globalPos.y() - newGeometry.bottom();
            newHeight = qBound(minHeight, mTarget->height() + deltaHeight, maxHeight);
            deltaHeight = newHeight - mTarget->height();
            if (deltaHeight != 0) {
                newGeometry.setBottom(oldGeometry.bottom() + deltaHeight);
            }
            break;
        }
        default:
            break;
        }
    }

    if (newGeometry == mTarget->geometry()) {
        // Nothing to do.
        return true;
    }

    if (!mTarget->isTopLevel()) {

        // Clip to parent's geometry.
        newGeometry = newGeometry.intersected(parentGeometry);

        // Back to local.
        newGeometry.moveTopLeft(mTarget->mapFromGlobal(newGeometry.topLeft()) + mTarget->pos());
    }

    mTarget->setGeometry(newGeometry);
    return true;
}

#ifdef Q_OS_WIN

/// Handler to enable Aero-snap
bool WidgetResizeHandler::handleWindowsNativeEvent(FloatingWindow *fw, const QByteArray &eventType,
                                                   void *message, Qt5Qt6Compat::qintptr *result)
{
    if (eventType != "windows_generic_MSG")
        return false;

    auto msg = static_cast<MSG *>(message);
    if (msg->message == WM_NCHITTEST) {
        if (DragController::instance()->isInClientDrag()) {
            // There's a non-native drag going on.
            *result = 0;
            return false;
        }

        const QRect htCaptionRect = fw->dragRect();
        const bool ret = handleWindowsNativeEvent(fw->windowHandle(), msg, result, htCaptionRect);

        fw->setLastHitTest(*result);
        return ret;
    } else if (msg->message == WM_NCLBUTTONDBLCLK) {
        if ((Config::self().flags() & Config::Flag_DoubleClickMaximizes)) {
            return handleWindowsNativeEvent(fw->windowHandle(), msg, result);
        } else {
            // Let the title bar handle it. It will re-dock the window.
            if (TitleBar *titleBar = fw->titleBar()) {
                if (titleBar->isVisible()) { // can't be invisible afaik
                    titleBar->onDoubleClicked();
                }
            }

            return true;
        }

        const bool ret = handleWindowsNativeEvent(fw->windowHandle(), msg, result);
        return ret;
    }

    return handleWindowsNativeEvent(fw->windowHandle(), msg, result);
}

bool WidgetResizeHandler::handleWindowsNativeEvent(QWindow *w, MSG *msg,
                                                   Qt5Qt6Compat::qintptr *result,
                                                   QRect htCaptionRect)
{
    if (msg->message == WM_NCCALCSIZE) {
        *result = 0;
        return true;
    } else if (msg->message == WM_NCHITTEST) {
        const int borderWidth = 8;
        const bool hasFixedWidth = w->minimumWidth() == w->maximumWidth();
        const bool hasFixedHeight = w->minimumHeight() == w->maximumHeight();

        *result = 0;
        const int xPos = GET_X_LPARAM(msg->lParam);
        const int yPos = GET_Y_LPARAM(msg->lParam);
        RECT rect;
        GetWindowRect(reinterpret_cast<HWND>(w->winId()), &rect);

        if (xPos >= rect.left && xPos <= rect.left + borderWidth &&
                yPos <= rect.bottom && yPos >= rect.bottom - borderWidth) {
            *result = HTBOTTOMLEFT;
        } else if (xPos < rect.right && xPos >= rect.right - borderWidth &&
                   yPos <= rect.bottom && yPos >= rect.bottom - borderWidth) {
            *result = HTBOTTOMRIGHT;
        } else if (xPos >= rect.left && xPos <= rect.left + borderWidth &&
                   yPos >= rect.top && yPos <= rect.top + borderWidth) {
            *result = HTTOPLEFT;
        } else if (xPos <= rect.right && xPos >= rect.right - borderWidth &&
                   yPos >= rect.top && yPos < rect.top + borderWidth) {
            *result = HTTOPRIGHT;
        } else if (!hasFixedWidth && xPos >= rect.left && xPos <= rect.left + borderWidth) {
            *result = HTLEFT;
        } else if (!hasFixedHeight && yPos >= rect.top && yPos <= rect.top + borderWidth) {
            *result = HTTOP;
        } else if (!hasFixedHeight && yPos <= rect.bottom && yPos >= rect.bottom - borderWidth) {
            *result = HTBOTTOM;
        } else if (!hasFixedWidth && xPos <= rect.right && xPos >= rect.right - borderWidth) {
            *result = HTRIGHT;
        } else if (!htCaptionRect.isNull()) {
            const QPoint globalPosQt = QHighDpi::fromNativePixels(QPoint(xPos, yPos), w);
            // htCaptionRect is the rect on which we allow for Windows to do a native drag
            if (globalPosQt.y() >= htCaptionRect.top() && globalPosQt.y() <= htCaptionRect.bottom() && globalPosQt.x() >= htCaptionRect.left() && globalPosQt.x() <= htCaptionRect.right()) {
                if (!KDDockWidgets::inDisallowDragWidget(globalPosQt)) { // Just makes sure the mouse isn't over the close button, we don't allow drag in that case.
                   *result = HTCAPTION;
                }
            }
        }

        return *result != 0;
    } else if (msg->message == WM_NCLBUTTONDBLCLK) {
        // By returning false we accept Windows native action, a maximize.
        // We could also call titleBar->onDoubleClicked(); here which will maximize if Flag_DoubleClickMaximizes is set,
        // but there's a bug in QWidget::showMaximized() on Windows when we're covering the native title bar, the window is maximized with an offset.
        // So instead, use a native maximize which works well
        return false;
    } else if (msg->message == WM_GETMINMAXINFO) {
        // Qt doesn't work well with windows that don't have title bar but have native frames.
        // When maximized they go out of bounds and the title bar is clipped, so catch WM_GETMINMAXINFO
        // and patch the size

        // According to microsoft docs it only works for the primary screen, but extrapolates for the others
        QScreen *screen = QGuiApplication::primaryScreen();
        if (!screen || w->screen() != screen) {
            return false;
        }

        DefWindowProc(msg->hwnd, msg->message, msg->wParam, msg->lParam);

        const QRect availableGeometry = screen->availableGeometry();

        auto mmi = reinterpret_cast<MINMAXINFO *>(msg->lParam);
        const qreal dpr = screen->devicePixelRatio();

        mmi->ptMaxSize.y = int(availableGeometry.height() * dpr);
        mmi->ptMaxSize.x = int(availableGeometry.width() * dpr) - 1; // -1 otherwise it gets bogus size
        mmi->ptMaxPosition.x = availableGeometry.x();
        mmi->ptMaxPosition.y = availableGeometry.y();

        mmi->ptMinTrackSize.x = int(w->minimumWidth() * dpr);
        mmi->ptMinTrackSize.y = int(w->minimumHeight() * dpr);

        *result = 0;
        return true;
    }

    return false;
}

#endif

void WidgetResizeHandler::setTarget(QWidgetOrQuick *w)
{
    if (w) {
        mTarget = w;
        mTarget->setMouseTracking(true);
        if (m_isTopLevelWindowResizer) {
            mTarget->installEventFilter(this);
        } else {
            qApp->installEventFilter(this);
        }
    } else {
        qWarning() << "Target widget is null!";
    }
}

void WidgetResizeHandler::updateCursor(CursorPosition m)
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    //Need for updating cursor when we change child widget
    const QObjectList children = mTarget->children();
    for (int i = 0, total = children.size(); i < total; ++i) {
        if (auto child = qobject_cast<WidgetType*>(children.at(i))) {

            if (!child->testAttribute(Qt::WA_SetCursor)) {
                child->setCursor(Qt::ArrowCursor);
            }
        }
    }
#endif

    switch (m) {
    case CursorPosition_TopLeft:
    case CursorPosition_BottomRight:
        setMouseCursor(Qt::SizeFDiagCursor);
        break;
    case CursorPosition_BottomLeft:
    case CursorPosition_TopRight:
        setMouseCursor(Qt::SizeBDiagCursor);
        break;
    case CursorPosition_Top:
    case CursorPosition_Bottom:
        setMouseCursor(Qt::SizeVerCursor);
        break;
    case CursorPosition_Left:
    case CursorPosition_Right:
        setMouseCursor(Qt::SizeHorCursor);
        break;
    case CursorPosition_Undefined:
        restoreMouseCursor();
        break;
    case CursorPosition_All:
        // Doesn't happen
        break;
    }
}

void WidgetResizeHandler::setMouseCursor(Qt::CursorShape cursor)
{
    if (m_isTopLevelWindowResizer)
        mTarget->setCursor(cursor);
    else
        qApp->setOverrideCursor(cursor);
}

void WidgetResizeHandler::restoreMouseCursor()
{
    if (m_isTopLevelWindowResizer)
        mTarget->setCursor(Qt::ArrowCursor);
    else
        qApp->restoreOverrideCursor();
}

CursorPosition WidgetResizeHandler::cursorPosition(QPoint globalPos) const
{
    if (!mTarget)
        return CursorPosition_Undefined;

    QPoint pos = mTarget->mapFromGlobal(globalPos);

    const int x = pos.x();
    const int y = pos.y();
    const int margin = widgetResizeHandlerMargin();

    unsigned int result = CursorPosition_Undefined;
    if (qAbs(x) <= margin)
        result |= CursorPosition_Left;
    else if (qAbs(x - (mTarget->width() - margin)) <= margin)
        result |= CursorPosition_Right;

    if (qAbs(y) <= margin)
        result |= CursorPosition_Top;
    else if (qAbs(y - (mTarget->height() - margin)) <= margin)
        result |= CursorPosition_Bottom;

    // Filter out sides we don't allow
    result = result & mAllowedResizeSides;

    return static_cast<CursorPosition>(result);
}

/** static */
void WidgetResizeHandler::setupWindow(QWindow *window)
{
    // Does some minor setup on our QWindow.
    // Like adding the drop shadow on Windows and two other workarounds.

#if defined(Q_OS_WIN)
    if (KDDockWidgets::usesAeroSnapWithCustomDecos()) {
        const auto wid = HWND(window->winId());
        connect(window, &QWindow::screenChanged, window, [window, wid] {
            // Qt honors our frame hijacking usually... but when screen changes we must give it a
            // nudge. Otherwise what Qt thinks is the client area is not what Windows knows it is.
            // SetWindowPos() will trigger an NCCALCSIZE message, which Qt will intercept and take
            // note of the margins we're using.
            SetWindowPos(wid, 0, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
        });

        // Show drop-shadow:
        MARGINS margins = { 0, 0, 0, 1 }; // arbitrary, just needs to be > 0 it seems
        DwmExtendFrameIntoClientArea(wid, &margins);
    }
#else
    Q_UNUSED(window);
#endif // Q_OS_WIN
}

#if defined(Q_OS_WIN) && defined(KDDOCKWIDGETS_QTWIDGETS)
bool NCHITTESTEventFilter::nativeEventFilter(const QByteArray &eventType, void *message,
                                             Qt5Qt6Compat::qintptr *result)

{
    if (eventType != "windows_generic_MSG" || !m_floatingWindow)
        return false;

    auto msg = static_cast<MSG *>(message);
    if (msg->message != WM_NCHITTEST)
        return false;
    const WId wid = WId(msg->hwnd);

    QWidget *child = QWidget::find(wid);
    if (!child || child->window() != m_floatingWindow)
        return false;
    const bool isThisWindow = child == m_floatingWindow;

    if (!isThisWindow) {
        *result = HTTRANSPARENT;
        return true;
    }

    return false;
}
#endif


CustomFrameHelper::CustomFrameHelper(ShouldUseCustomFrame func, QObject *parent)
    : QObject(parent)
    , QAbstractNativeEventFilter()
    , m_shouldUseCustomFrameFunc(func)
{
#ifdef Q_OS_WIN
    qApp->installNativeEventFilter(this);
#endif
}

CustomFrameHelper::~CustomFrameHelper()
{
    m_inDtor = true;
}

void CustomFrameHelper::applyCustomFrame(QWindow *window)
{
#ifdef Q_OS_WIN
    WidgetResizeHandler::setupWindow(window);
#else
    Q_UNUSED(window);
    qWarning() << Q_FUNC_INFO << "Not implemented on this platform";
#endif
}

bool CustomFrameHelper::nativeEventFilter(const QByteArray &eventType, void *message,
                                          Qt5Qt6Compat::qintptr *result)
{
    if (m_shouldUseCustomFrameFunc == nullptr)
        return false;

#ifdef Q_OS_WIN
    if (m_inDtor || !KDDockWidgets::usesAeroSnapWithCustomDecos())
        return false;

    if (eventType != "windows_generic_MSG")
        return false;

    auto msg = static_cast<MSG *>(message);

    QWindow *window = QWindow::fromWinId(WId(msg->hwnd));
    if (!window || !m_shouldUseCustomFrameFunc(window))
        return false;

    const char *propertyName = "kddw_customframe_setup_ran";
    const bool setupRan = window->property(propertyName).toBool();
    if (!setupRan) {
        // Add drop shadow
        WidgetResizeHandler::setupWindow(window);
        window->setProperty(propertyName, true);
    }

    return WidgetResizeHandler::handleWindowsNativeEvent(window, msg, result);
#else
    Q_UNUSED(eventType);
    Q_UNUSED(message);
    Q_UNUSED(result);
    return false;
#endif
}
