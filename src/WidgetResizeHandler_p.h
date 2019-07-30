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

#ifndef KD_WIDGET_RESIZE_HANDLER_P_H
#define KD_WIDGET_RESIZE_HANDLER_P_H

#include <QWidget>
#include <QPoint>


#if defined(Q_OS_WIN)
# include <Windowsx.h>
# include <Windows.h>
# pragma comment(lib,"User32.lib")
#endif

class QMouseEvent;
namespace KDDockWidgets {


#if defined(Q_OS_WIN)

static bool resizeHandlerNativeEvent(QWidget *w, const QByteArray &eventType, void *message, long *result)
{
    if (eventType != "windows_generic_MSG")
        return false;

    if (w->window() != w)
        return false;

    const int borderWidth = 8;
    const bool hasFixedWidth = w->minimumWidth() == w->maximumWidth();
    const bool hasFixedHeight = w->minimumHeight() == w->maximumHeight();

    auto msg = static_cast<MSG *>(message);
    if (msg->message == WM_NCCALCSIZE) {
        *result = 0;
        return true;
    } else if (msg->message == WM_NCHITTEST) {

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
            *result = HTCAPTION;
        }

        return *result != 0;
    }

    return false;
}
#endif

class WidgetResizeHandler : public QObject
{
    Q_OBJECT
public:
    explicit WidgetResizeHandler(QWidget *target = nullptr);
    ~WidgetResizeHandler() override;

    void setTarget(QWidget *w);
    static bool s_disableAllHandlers;
protected:
    bool eventFilter(QObject *o, QEvent *e) override;

private:
    enum class CursorPosition {
        Left,
        Right,
        TopLeft,
        TopRight,
        BottomRight,
        BottomLeft,
        Top,
        Bottom,
        Undefined
    };
    void mouseMoveEvent(QMouseEvent *e);
    void updateCursor(CursorPosition m);
    CursorPosition cursorPosition(QPoint) const;
    QWidget *mTarget = nullptr;
    CursorPosition mCursorPos = CursorPosition::Undefined;
    QPoint mNewPosition;
    bool mResizeWidget = false;
};

}

#endif
