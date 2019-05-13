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

#ifndef KD_DRAGCONTROLLER_P_H
#define KD_DRAGCONTROLLER_P_H

#include "TitleBar_p.h"
#include "TabWidget_p.h"
#include "WindowBeingDragged_p.h"

#include <QStateMachine>
#include <QPoint>
#include <memory>

namespace KDDockWidgets {

class StateBase;
class DropArea;
class Draggable;

class DragController : public QStateMachine
{
    Q_OBJECT
public:
    enum State {
        State_None = 0,
        State_PreDrag,
        State_Dragging
    };
    Q_ENUM(State)

    static DragController *instance();

    // Registers something that wants to be able to be dragged
    void registerDraggable(Draggable *);
    void unregisterDraggable(Draggable *);

    bool isDragging() const;

Q_SIGNALS:
    void mousePressed();
    void manhattanLengthMove();
    void dragCanceled();
    void dropped();

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    friend class StateBase;
    friend class StateNone;
    friend class StatePreDrag;
    friend class StateDragging;
    friend class StateDropped;

    DragController(QObject * = nullptr);
    StateBase *activeState() const;
    QWidget *qtTopLevelUnderCursor() const;
    DropArea *dropAreaUnderCursor() const;
    Draggable *draggableForQObject(QObject *o) const;
    QPoint m_pressPos;
    QPoint m_offset;

    Draggable::List m_draggables;
    Draggable *m_draggable = nullptr;
    std::unique_ptr<WindowBeingDragged> m_windowBeingDragged;
    DropArea *m_currentDropArea = nullptr;
    bool m_nonClientDrag = false;
};
}

#endif
