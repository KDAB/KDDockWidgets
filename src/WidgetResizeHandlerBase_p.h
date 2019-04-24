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

#ifndef KD_WIDGETRESIZEHANDLERBASE_P_H
#define KD_WIDGETRESIZEHANDLERBASE_P_H

#include <QObject>
#include <QPoint>
class QMouseEvent;
class WidgetResizeHandlerBase : public QObject
{
    Q_OBJECT
public:
    explicit WidgetResizeHandlerBase(QObject *parent = nullptr);
    ~WidgetResizeHandlerBase() override;

    void setTarget(QWidget *w);

    void setActive(bool b);
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
    QWidget *mTarget = nullptr;
    CursorPosition mCursorPos = CursorPosition::Undefined;
    QPoint mNewPosition;
    bool mResizeWidget = false;
};

#endif // WIDGETRESIZEHANDLERBASE_H
