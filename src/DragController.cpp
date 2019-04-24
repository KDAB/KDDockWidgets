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

#include "DragController_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "DropArea_p.h"
#include "FloatingWindow_p.h"
#include "Draggable_p.h"
#include "WidgetResizeHandlerBase_p.h"

#include <QMouseEvent>
#include <QApplication>
#include <QCursor>

#if defined(Q_OS_WIN)
# include <Windows.h>
#endif

using namespace KDDockWidgets;

namespace KDDockWidgets {
class StateBase : public QState
{
public:
    StateBase(DragController *parent)
        : QState(parent)
        , q(parent)
    {
    }

    ~StateBase();

    // Not using QEvent here, to abstract platform differences regarding production of such events
    virtual bool handleMouseButtonPress(Draggable * /*receiver*/, QPoint /*globalPos*/, QPoint /*pos*/) { return false; }
    virtual bool handleMouseMove(QPoint /*globalPos*/) { return false; }
    virtual bool handleMouseButtonRelease(QPoint /*globalPos*/, QPoint /*pos*/) { return false; }

    DragController *const q;
};

StateBase::~StateBase() = default;

class StateNone : public StateBase
{
public:
    explicit StateNone(DragController *parent)
        : StateBase(parent)
    {
    }

    ~StateNone() override;

    void onEntry(QEvent *) override
    {
        qCDebug(state) << "StateNone entered";
        q->m_pressPos = QPoint();
        q->m_offset = QPoint();
        q->m_draggable = nullptr;
        q->m_windowBeingDragged.reset();
        WidgetResizeHandlerBase::s_disableAllHandlers = false; // Re-enable resize handlers

        q->m_nonClientDrag = false;
        if (q->m_currentDropArea) {
            q->m_currentDropArea->removeHover();
            q->m_currentDropArea = nullptr;
        }
    }

    bool handleMouseButtonPress(Draggable *draggable, QPoint globalPos, QPoint pos) override
    {
        qCDebug(state) << "StateNone::handleMouseButtonPress: draggable" << draggable << "; globalPos" << globalPos;

        q->m_draggable = draggable;
        q->m_pressPos = globalPos;
        q->m_offset = pos;
        emit q->mousePressed();
        return false;
    }
};

StateNone::~StateNone() = default;

class StatePreDrag : public StateBase
{
public:
    explicit StatePreDrag(DragController *parent)
        : StateBase(parent)
    {
    }

    ~StatePreDrag() override;

    void onEntry(QEvent *) override
    {
        qCDebug(state) << "StatePreDrag entered";
        WidgetResizeHandlerBase::s_disableAllHandlers = true; // Disable the resize handler during dragging
    }

    bool handleMouseMove(QPoint globalPos) override
    {
        if ((globalPos - q->m_pressPos).manhattanLength() > QApplication::startDragDistance()) {
            emit q->manhattanLengthMove();
        }
        return true;
    }

    bool handleMouseButtonRelease(QPoint, QPoint) override
    {
        emit q->dragCanceled();
        return true;
    }
};

StatePreDrag::~StatePreDrag() = default;

class StateDragging : public StateBase
{
public:
    explicit StateDragging(DragController *parent)
        : StateBase(parent)
    {
    }

    ~StateDragging() override;

    void onEntry(QEvent *) override
    {
        q->m_windowBeingDragged = q->m_draggable->makeWindow();
        qCDebug(state) << "StateDragging entered. m_draggable=" << q->m_draggable << "; m_windowBeingDragged=" << q->m_windowBeingDragged->window();
    }

    bool handleMouseButtonRelease(QPoint globalPos, QPoint) override
    {
        qCDebug(state) << "StateDragging: handleMouseButtonRelease";

        Draggable *draggable = q->m_windowBeingDragged->draggable();
        if (!draggable) {
            // It was deleted externally
            qCDebug(state) << "StateDragging: Bailling out, deleted externally";
            emit q->dragCanceled();
            return true;
        }

        if (q->m_currentDropArea) {
            if (q->m_currentDropArea->drop(draggable, globalPos)) {
                emit q->dropped();
            } else {
                qCDebug(state) << "StateDragging: Bailling out, drop not accepted";
                emit q->dragCanceled();
            }
        } else {
            qCDebug(state) << "StateDragging: Bailling out, not over a drop area";
            emit q->dragCanceled();
        }
        return true;
    }

    bool handleMouseMove(QPoint globalPos) override
    {
        if (!q->m_windowBeingDragged->window()) {
            qCDebug(state) << "Canceling drag, window was deleted";
            emit q->dragCanceled();
            return true;
        }

        if (!q->m_nonClientDrag)
            q->m_windowBeingDragged->window()->move(globalPos - q->m_offset);

        DropArea *dropArea = q->dropAreaUnderCursor();
        if (q->m_currentDropArea && dropArea != q->m_currentDropArea)
            q->m_currentDropArea->removeHover();

        if (dropArea)
            dropArea->hover(q->m_windowBeingDragged->draggable(), globalPos);

        q->m_currentDropArea = dropArea;

        return true;
    }
};

StateDragging::~StateDragging() = default;

}

DragController::DragController()
{
    qCDebug(creation) << "DragController()";

    auto stateNone = new StateNone(this);
    auto statepreDrag = new StatePreDrag(this);
    auto stateDragging = new StateDragging(this);

    stateNone->addTransition(this, &DragController::mousePressed, statepreDrag);
    statepreDrag->addTransition(this, &DragController::dragCanceled, stateNone);
    statepreDrag->addTransition(this, &DragController::manhattanLengthMove, stateDragging);
    stateDragging->addTransition(this, &DragController::dragCanceled, stateNone);
    stateDragging->addTransition(this, &DragController::dropped, stateNone);

    setInitialState(stateNone);
    start();
}

DragController *DragController::instance()
{
    static DragController dragController;
    return &dragController;
}

void DragController::registerDraggable(Draggable *drg)
{
    m_draggables << drg;
    drg->asWidget()->installEventFilter(this);
}

void DragController::unregisterDraggable(Draggable *drg)
{
    m_draggables.removeOne(drg);
    drg->asWidget()->removeEventFilter(this);
}

bool DragController::isDragging() const
{
    return m_windowBeingDragged != nullptr;
}

static QMouseEvent *mouseEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::NonClientAreaMouseButtonPress:
    case QEvent::NonClientAreaMouseButtonRelease:
    case QEvent::NonClientAreaMouseMove:
        return static_cast<QMouseEvent *>(e);
    default:
        break;
    }

    return nullptr;
}

bool DragController::eventFilter(QObject *o, QEvent *e)
{
    if (m_nonClientDrag && e->type() == QEvent::Move) {
        // On Windows, non-client mouse moves are only sent at the end, so we must fake it:
        activeState()->handleMouseMove(QCursor::pos());
        return QStateMachine::eventFilter(o, e);
    }

    QMouseEvent *me = mouseEvent(e);
    if (!me)
        return QStateMachine::eventFilter(o, e);

    qCDebug(mouseevents) << "DragController::eventFilter e=" << e->type() << "; o=" << o;

    switch (e->type()) {
    case QEvent::NonClientAreaMouseButtonPress:
        m_nonClientDrag = true;
        Q_FALLTHROUGH();
    case QEvent::MouseButtonPress:
        return activeState()->handleMouseButtonPress(draggableForQObject(o), me->globalPos(), me->pos());
    case QEvent::MouseButtonRelease:
    case QEvent::NonClientAreaMouseButtonRelease:
        return activeState()->handleMouseButtonRelease(me->globalPos(), me->pos());
    case QEvent::MouseMove:
        return activeState()->handleMouseMove(me->globalPos());
    default:
        return QStateMachine::eventFilter(o, e);
    }
}

StateBase *DragController::activeState() const
{
    auto set = configuration();
    if (set.isEmpty())
        return nullptr;
    return static_cast<StateBase *>(*(set.begin()));
}

#if defined(Q_OS_WIN)
static QWidget *qtTopLevelForHWND(HWND hwnd)
{
    auto topLevels = qApp->topLevelWidgets();
    for (auto topLevel : topLevels) {
        if (hwnd == (HWND)topLevel->winId())
            return topLevel;
    }
    return nullptr;
}
#endif

QWidget *DragController::qtTopLevelUnderCursor() const
{
    QPoint globalPos = QCursor::pos();
    auto topLevels = qApp->topLevelWidgets();
#if defined(Q_OS_WIN)
    POINT globalNativePos;
    if (!GetCursorPos(&globalNativePos))
        return nullptr;

    // There might be windows that don't belong to our app in between, so use win32 to travel by z-order.
    // Another solution is to set a parent on all top-levels. But this code is orthogonal.
    HWND hwnd = (HWND)m_windowBeingDragged->window()->winId();
    while (hwnd) {
        hwnd = GetWindow(hwnd, GW_HWNDNEXT);
        RECT r;
        if (!GetWindowRect(hwnd, &r))
            continue;

        if (!PtInRect(&r, globalNativePos)) // Check if window is under cursor
            continue;

        if (auto tl = qtTopLevelForHWND(hwnd)) {
            if (tl->geometry().contains(globalPos) && tl->objectName() != QStringLiteral("_docks_IndicatorWindow_Overlay"))
                return tl;
        } else {
            // A window belonging to another app is below the cursor
            return nullptr;
        }
    }
#else
    for (auto tl : topLevels) {
        if (!tl->isVisible() || tl == m_windowBeingDragged->window() || tl->isMinimized() || tl->objectName() == QLatin1String("_docks_IndicatorWindow_Overlay"))
            continue;
        if (tl->geometry().contains(globalPos)) {
            return tl;
        }
    }
#endif
    return nullptr;
}

DropArea *DragController::dropAreaUnderCursor() const
{
    QWidget *topLevel = qtTopLevelUnderCursor();
    if (!topLevel) {
        //qCDebug(state) << "DragController::dropAreaUnderCursor: null";
        return nullptr;
    }

    if (auto dt = qobject_cast<DropArea *>(topLevel)) {
        return dt;
    }

    if (auto fw = qobject_cast<FloatingWindow *>(topLevel)) {
        return fw->dropArea();
    }

    if (topLevel->objectName() == QStringLiteral("_docks_IndicatorWindow")) {
        qWarning() << "Indicator window should be hidden " << topLevel << topLevel->isVisible();
        Q_ASSERT(false);
    }

    if (auto dock = qobject_cast<DockWidget *>(topLevel)) {
        FloatingWindow *fw = dock->morphIntoFloatingWindow();
        m_windowBeingDragged->window()->raise();
        return fw->dropArea();
    }

    QWidget *w = topLevel->childAt(topLevel->mapFromGlobal(QCursor::pos()));
    while (w) {
        if (auto dt = qobject_cast<DropArea *>(w)) {
            return dt;
        }
        w = w->parentWidget();
    }

    qCDebug(state) << "DragController::dropAreaUnderCursor: null2";
    return nullptr;
}

Draggable *DragController::draggableForQObject(QObject *o) const
{
    for (auto draggable : m_draggables)
        if (draggable->asWidget() == o) {
            return draggable;
        }

    return nullptr;
}
