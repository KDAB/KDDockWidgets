/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DRAGCONTROLLER_P_H
#define KD_DRAGCONTROLLER_P_H

#include "TitleBar_p.h"
#include "WindowBeingDragged_p.h"

#include <QStateMachine>
#include <QPoint>
#include <memory>

namespace KDDockWidgets {

class StateBase;
class DropArea;
class Draggable;
class FallbackMouseGrabber;

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
    bool isInNonClientDrag() const;
    bool isInClientDrag() const;

    void grabMouseFor(QWidgetOrQuick *);
    void releaseMouse(QWidgetOrQuick *);

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
    WidgetType *qtTopLevelUnderCursor() const;
    DropArea *dropAreaUnderCursor() const;
    Draggable *draggableForQObject(QObject *o) const;
    QPoint m_pressPos;
    QPoint m_offset;

    Draggable::List m_draggables;
    Draggable *m_draggable = nullptr;
    std::unique_ptr<WindowBeingDragged> m_windowBeingDragged;
    DropArea *m_currentDropArea = nullptr;
    bool m_nonClientDrag = false;
    FallbackMouseGrabber *m_fallbackMouseGrabber = nullptr;
};

class StateBase : public QState
{
    Q_OBJECT
public:
    explicit StateBase(DragController *parent);
    ~StateBase();

    // Not using QEvent here, to abstract platform differences regarding production of such events
    virtual bool handleMouseButtonPress(Draggable * /*receiver*/, QPoint /*globalPos*/, QPoint /*pos*/) { return false; }
    virtual bool handleMouseMove(QPoint /*globalPos*/) { return false; }
    virtual bool handleMouseButtonRelease(QPoint /*globalPos*/) { return false; }

    DragController *const q;
};

class StateNone : public StateBase
{
    Q_OBJECT
public:
    explicit StateNone(DragController *parent);
    ~StateNone() override;
    void onEntry(QEvent *) override;
    bool handleMouseButtonPress(Draggable *draggable, QPoint globalPos, QPoint pos) override;
};

class StatePreDrag : public StateBase
{
    Q_OBJECT
public:
    explicit StatePreDrag(DragController *parent);
    ~StatePreDrag() override;
    void onEntry(QEvent *) override;
    bool handleMouseMove(QPoint globalPos) override;
    bool handleMouseButtonRelease(QPoint) override;
};

class StateDragging : public StateBase
{
    Q_OBJECT
public:
    explicit StateDragging(DragController *parent);
    ~StateDragging() override;
    void onEntry(QEvent *) override;
    bool handleMouseButtonRelease(QPoint globalPos) override;
    bool handleMouseMove(QPoint globalPos) override;
};

}

#endif
