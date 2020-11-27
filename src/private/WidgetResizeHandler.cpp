/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
#include <QWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QWindow>
#include <QAbstractButton>
#include <QLineEdit>

#if defined(Q_OS_WIN)
# include <QtGui/private/qhighdpiscaling_p.h>
# include <Windowsx.h>
# include <Windows.h>
# if defined(Q_CC_MSVC)
#  pragma comment(lib,"User32.lib")
# endif
#endif

namespace  {
int widgetResizeHandlerMargin = 4; //4 pixel
}

using namespace KDDockWidgets;

bool WidgetResizeHandler::s_disableAllHandlers = false;
WidgetResizeHandler::WidgetResizeHandler(QWidgetOrQuick *target)
    : QObject(target)
{
    setTarget(target);
}

WidgetResizeHandler::~WidgetResizeHandler()
{
}

bool WidgetResizeHandler::eventFilter(QObject *o, QEvent *e)
{
    if (s_disableAllHandlers || o != mTarget) {
        return false;
    }

    auto widget = qobject_cast<QWidgetOrQuick*>(o);
    if (!widget || !widget->isTopLevel()) {
        return false;
    }

    switch (e->type()) {
    case QEvent::MouseButtonPress: {
        if (mTarget->isMaximized())
            break;
        auto mouseEvent = static_cast<QMouseEvent *>(e);
        auto cursorPos = cursorPosition(Qt5Qt6Compat::eventGlobalPos(mouseEvent));
        if (cursorPos == CursorPosition::Undefined)
            return false;

        const QRect widgetRect = mTarget->rect().marginsAdded(QMargins(widgetResizeHandlerMargin, widgetResizeHandlerMargin, widgetResizeHandlerMargin, widgetResizeHandlerMargin));
        const QPoint cursorPoint = mTarget->mapFromGlobal(Qt5Qt6Compat::eventGlobalPos(mouseEvent));
        if (!widgetRect.contains(cursorPoint))
            return false;
        if (mouseEvent->button() == Qt::LeftButton) {
            mResizeWidget = true;
        }

        mNewPosition = Qt5Qt6Compat::eventGlobalPos(mouseEvent);
        mCursorPos = cursorPos;
        return true;
    }
    case QEvent::MouseButtonRelease: {
        if (mTarget->isMaximized())
            break;
        auto mouseEvent = static_cast<QMouseEvent *>(e);
        if (mouseEvent->button() == Qt::LeftButton) {
            mResizeWidget = false;
            mTarget->releaseMouse();
            mTarget->releaseKeyboard();
            return true;
        }
        break;
    }
    case QEvent::MouseMove: {
        if (mTarget->isMaximized())
            break;
        auto mouseEvent = static_cast<QMouseEvent *>(e);
        mResizeWidget = mResizeWidget && (mouseEvent->buttons() & Qt::LeftButton);
        const bool state = mResizeWidget;
        mResizeWidget = ((o == mTarget) && mResizeWidget);
        mouseMoveEvent(mouseEvent);
        mResizeWidget = state;
        return true;
    }
    default:
        break;
    }
    return false;
}

void WidgetResizeHandler::mouseMoveEvent(QMouseEvent *e)
{
    const QPoint globalPos = Qt5Qt6Compat::eventGlobalPos(e);
    if (!mResizeWidget) {
        updateCursor(cursorPosition(globalPos));
        return;
    }

    const QRect oldGeometry = mTarget->geometry();
    QRect newGeometry = oldGeometry;

    {
        int deltaWidth = 0;
        int newWidth = 0;
        const int minWidth = mTarget->minimumWidth();
        const int maxWidth = mTarget->maximumWidth();
        switch (mCursorPos) {
        case CursorPosition::TopLeft:
        case CursorPosition::Left:
        case CursorPosition::BottomLeft: {
            deltaWidth = oldGeometry.left() - globalPos.x();
            newWidth = qBound(minWidth, mTarget->width() + deltaWidth, maxWidth);
            deltaWidth = newWidth - mTarget->width();
            if (deltaWidth != 0) {
                newGeometry.setLeft(newGeometry.left() - deltaWidth);
            }

            break;
        }

        case CursorPosition::TopRight:
        case CursorPosition::Right:
        case CursorPosition::BottomRight: {
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
        const int maxHeight = mTarget->maximumHeight();
        const int minHeight = mTarget->minimumHeight();
        int deltaHeight = 0;
        int newHeight = 0;
        switch (mCursorPos) {
        case CursorPosition::TopLeft:
        case CursorPosition::Top:
        case CursorPosition::TopRight: {
            deltaHeight = oldGeometry.top() - globalPos.y();
            newHeight = qBound(minHeight, mTarget->height() + deltaHeight, maxHeight);
            deltaHeight = newHeight - mTarget->height();
            if (deltaHeight != 0) {
                newGeometry.setTop(newGeometry.top() - deltaHeight);
            }

            break;
        }

        case CursorPosition::BottomLeft:
        case CursorPosition::Bottom:
        case CursorPosition::BottomRight: {
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

    if (newGeometry != mTarget->geometry())
        mTarget->setGeometry(newGeometry);
}


#ifdef Q_OS_WIN

/// Handler to enable Aero-snap
bool WidgetResizeHandler::handleWindowsNativeEvent(FloatingWindow *w, const QByteArray &eventType, void *message, long *result)
{
    if (eventType != "windows_generic_MSG")
        return false;

    auto msg = static_cast<MSG *>(message);
    if (msg->message == WM_NCCALCSIZE) {
        *result = 0;
        return true;
    } else if (msg->message == WM_NCHITTEST) {

        if (DragController::instance()->isInClientDrag()) {
            // There's a non-native drag going on.
            *result = 0;
            return false;
        }

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
        } else {
            const QPoint globalPosQt = QHighDpi::fromNativePixels(QPoint(xPos, yPos), w->windowHandle());

            const QRect htCaptionRect = w->dragRect(); // The rect on which we allow for Windows to do Ba native drag
            if (globalPosQt.y() >= htCaptionRect.top() && globalPosQt.y() <= htCaptionRect.bottom() && globalPosQt.x() >= htCaptionRect.left() && globalPosQt.x() <= htCaptionRect.right()) {
                WidgetType *hoveredWidget = KDDockWidgets::widgetAt(globalPosQt);
                if (!qobject_cast<QAbstractButton*>(hoveredWidget) &&
                    !qobject_cast<QLineEdit*>(hoveredWidget)) { // User might have a line edit on the toolbar. TODO: Not so elegant fix, we should make the user's tabbar implement some virtual method...
                    // User clicked on the title bar, let's allow it, so we get Aero-Snap.
                    *result = HTCAPTION;
                }
            }
        }

        return *result != 0;
    } else if (msg->message == WM_NCLBUTTONDBLCLK) {
        if ((Config::self().flags() & Config::Flag_DoubleClickMaximizes)) {
            // By returning false we accept Windows native action, a maximize.
            // We could also call titleBar->onDoubleClicked(); here which will maximize if Flag_DoubleClickMaximizes is set,
            // but there's a bug in QWidget::showMaximized() on Windows when we're covering the native title bar, the window is maximized with an offset.
            // So instead, use a native maximize which works well
            return false;
        } else {
            // Let the title bar handle it. It will re-dock the window.

            if (TitleBar *titleBar = w->titleBar()) {
                if (titleBar->isVisible()) { // can't be invisible afaik
                    titleBar->onDoubleClicked();
                }
            }

            return true;
        }
    } else if (msg->message == WM_GETMINMAXINFO) {
        // Qt doesn't work well with windows that don't have title bar but have native frames.
        // When maximized they go out of bounds and the title bar is clipped, so catch WM_GETMINMAXINFO
        // and patch the size

        // According to microsoft docs it only works for the primary screen, but extrapolates for the others
        QScreen *screen = QGuiApplication::primaryScreen();
        if (!screen || w->windowHandle()->screen() != screen) {
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

        QWindow *window = w->windowHandle();
        mmi->ptMinTrackSize.x = int(window->minimumWidth() * dpr);
        mmi->ptMinTrackSize.y = int(window->minimumHeight() * dpr);

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
        mTarget->installEventFilter(this);
    } else {
        qWarning() << "Target widget is null!";
    }
}

void WidgetResizeHandler::updateCursor(CursorPosition m)
{
    //Need for updating cursor when we change child widget
    const QObjectList children = mTarget->children();
    for (int i = 0, total = children.size(); i < total; ++i) {
        if (auto child = qobject_cast<QWidget*>(children.at(i))) {
            if (!child->testAttribute(Qt::WA_SetCursor)) {
                child->setCursor(Qt::ArrowCursor);
            }
        }
    }
    switch (m) {
    case CursorPosition::TopLeft:
    case CursorPosition::BottomRight:
        mTarget->setCursor(Qt::SizeFDiagCursor);
        break;
    case CursorPosition::BottomLeft:
    case CursorPosition::TopRight:
        mTarget->setCursor(Qt::SizeBDiagCursor);
        break;
    case CursorPosition::Top:
    case CursorPosition::Bottom:
        mTarget->setCursor(Qt::SizeVerCursor);
        break;
    case CursorPosition::Left:
    case CursorPosition::Right:
        mTarget->setCursor(Qt::SizeHorCursor);
        break;
    case CursorPosition::Undefined:
        mTarget->setCursor(Qt::ArrowCursor);
        break;
    }
}

WidgetResizeHandler::CursorPosition WidgetResizeHandler::cursorPosition(QPoint globalPos) const
{
    if (!mTarget)
        return CursorPosition::Undefined;

    QPoint pos = mTarget->mapFromGlobal(globalPos);

    if (pos.y() <= widgetResizeHandlerMargin && pos.x() <= widgetResizeHandlerMargin) {
        return CursorPosition::TopLeft;
    } else if (pos.y() >= mTarget->height() - widgetResizeHandlerMargin && pos.x() >= mTarget->width() - widgetResizeHandlerMargin) {
        return CursorPosition::BottomRight;
    } else if (pos.y() >= mTarget->height() - widgetResizeHandlerMargin && pos.x() <= widgetResizeHandlerMargin) {
        return CursorPosition::BottomLeft;
    } else if (pos.y() <= widgetResizeHandlerMargin && pos.x() >= mTarget->width() - widgetResizeHandlerMargin) {
        return CursorPosition::TopRight;
    } else if (pos.y() <= widgetResizeHandlerMargin) {
        return CursorPosition::Top;
    } else if (pos.y() >= mTarget->height() - widgetResizeHandlerMargin) {
        return CursorPosition::Bottom;
    } else if (pos.x() <= widgetResizeHandlerMargin) {
        return CursorPosition::Left;
    } else if ( pos.x() >= mTarget->width() - widgetResizeHandlerMargin) {
        return CursorPosition::Right;
    } else {
        return CursorPosition::Undefined;
    }
}
