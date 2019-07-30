/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#include "WidgetResizeHandler_p.h"
#include <QEvent>
#include <QMouseEvent>
#include <QWidget>
#include <QDebug>

#if defined(Q_OS_WIN)
# include <Windowsx.h>
# include <Windows.h>
# pragma comment(lib,"User32.lib")
#endif

namespace  {
int widgetResizeHandlerMargin = 4; //4 pixel
}

using namespace KDDockWidgets;

bool WidgetResizeHandler::s_disableAllHandlers = false;
WidgetResizeHandler::WidgetResizeHandler(QWidget *target)
    : QObject(target)
{
    setTarget(target);
}

WidgetResizeHandler::~WidgetResizeHandler()
{
}

bool WidgetResizeHandler::eventFilter(QObject *o, QEvent *e)
{
    if (s_disableAllHandlers || o != mTarget)
        return false;

    auto widget = qobject_cast<QWidget*>(o);
    if (!widget || !widget->isTopLevel()) {
        return false;
    }

    switch (e->type()) {
    case QEvent::MouseButtonPress: {
        if (mTarget->isMaximized())
            break;
        auto mouseEvent = static_cast<QMouseEvent *>(e);
        auto cursorPos = cursorPosition(mouseEvent->globalPos());
        if (cursorPos == CursorPosition::Undefined)
            return false;

        const QRect widgetRect = mTarget->rect().marginsAdded(QMargins(widgetResizeHandlerMargin, widgetResizeHandlerMargin, widgetResizeHandlerMargin, widgetResizeHandlerMargin));
        const QPoint cursorPoint = mTarget->mapFromGlobal(mouseEvent->globalPos());
        if (!widgetRect.contains(cursorPoint))
            return false;
        if (mouseEvent->button() == Qt::LeftButton) {
            mResizeWidget = true;
        }

        mNewPosition = mouseEvent->globalPos();
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
    const QPoint globalPos = e->globalPos();
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
bool WidgetResizeHandler::handleWindowsNativeEvent(QWidget *w, QRect titleBarRectGlobal, const QByteArray &eventType, void *message, long *result)
{


    if (eventType != "windows_generic_MSG")
        return false;

    auto msg = static_cast<MSG *>(message);
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
        } else if (yPos >= titleBarRectGlobal.top() && yPos <= titleBarRectGlobal.bottom() && xPos >= titleBarRectGlobal.left() && xPos >= titleBarRectGlobal.right()) {
            // User clicked on the title bar, let's allow it, so we get Aero-Snap.
            *result = HTCAPTION;
        }

        return *result != 0;
    }

    return false;
}

#endif

void WidgetResizeHandler::setTarget(QWidget *w)
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
