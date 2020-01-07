/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include <QDebug>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

namespace KDDockWidgets {

class FloatingWindow;

class WidgetResizeHandler : public QObject
{
    Q_OBJECT
public:
    explicit WidgetResizeHandler(QWidget *target = nullptr);
    ~WidgetResizeHandler() override;

    void setTarget(QWidget *w);

#ifdef Q_OS_WIN
    static bool handleWindowsNativeEvent(FloatingWindow *w, const QByteArray &eventType, void *message, long *result);
#endif
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
