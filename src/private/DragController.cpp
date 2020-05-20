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

#include "DragController_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "DropArea_p.h"
#include "FloatingWindow_p.h"
#include "WidgetResizeHandler_p.h"
#include "Utils_p.h"
#include "DockRegistry_p.h"

#include <QMouseEvent>
#include <QApplication>
#include <QCursor>
#include <QWindow>

#if defined(Q_OS_WIN)
# include <QWindow>
# include <Windows.h>
#endif

using namespace KDDockWidgets;

namespace KDDockWidgets {
///@brief Custom mouse grabber, as platforms like wayland don't support grabbing the mouse
class FallbackMouseGrabber : public QObject /// clazy:exclude=missing-qobject-macro
{
public:
    FallbackMouseGrabber(QObject *parent)
        : QObject(parent)
    {
    }

    ~FallbackMouseGrabber() override;

    void grabMouse(QWidgetOrQuick *target)
    {
        m_target = target;
        qApp->installEventFilter(this);
    }

    void releaseMouse()
    {
        m_target = nullptr;
        qApp->removeEventFilter(this);
    }

    bool eventFilter(QObject *, QEvent *ev) override
    {
        if (m_reentrancyGuard || !m_target)
            return false;

        if (ev->type() == QEvent::MouseButtonPress ||
            ev->type() == QEvent::MouseButtonRelease ||
            ev->type() == QEvent::MouseMove ||
            ev->type() == QEvent::NonClientAreaMouseButtonPress ||
            ev->type() == QEvent::NonClientAreaMouseButtonRelease ||
            ev->type() == QEvent::NonClientAreaMouseMove) {
            m_reentrancyGuard = true;
            qApp->sendEvent(m_target, ev);
            m_reentrancyGuard = false;
            return true;
        }

        return false;
    }

    bool m_reentrancyGuard = false;
    QPointer<QWidgetOrQuick> m_target;
};

FallbackMouseGrabber::~FallbackMouseGrabber() {}

}

StateBase::StateBase(DragController *parent)
    : QState(parent)
    , q(parent)
{
}

StateBase::~StateBase() = default;

StateNone::StateNone(DragController *parent)
    : StateBase(parent)
{
}

void StateNone::onEntry(QEvent *)
{
    qCDebug(state) << "StateNone entered";
    q->m_pressPos = QPoint();
    q->m_offset = QPoint();
    q->m_draggable = nullptr;
    q->m_windowBeingDragged.reset();
    WidgetResizeHandler::s_disableAllHandlers = false; // Re-enable resize handlers

    q->m_nonClientDrag = false;
    if (q->m_currentDropArea) {
        q->m_currentDropArea->removeHover();
        q->m_currentDropArea = nullptr;
    }
}

bool StateNone::handleMouseButtonPress(Draggable *draggable, QPoint globalPos, QPoint pos)
{
    qCDebug(state) << "StateNone::handleMouseButtonPress: draggable"
                   << draggable << "; globalPos" << globalPos;

    if (!draggable->isPositionDraggable(pos))
        return false;

    q->m_draggable = draggable;
    q->m_pressPos = globalPos;
    q->m_offset = pos;
    Q_EMIT q->mousePressed();
    return false;
}

StateNone::~StateNone() = default;


StatePreDrag::StatePreDrag(DragController *parent)
    : StateBase(parent)
{
}

StatePreDrag::~StatePreDrag() = default;

void StatePreDrag::onEntry(QEvent *)
{
    qCDebug(state) << "StatePreDrag entered";
    WidgetResizeHandler::s_disableAllHandlers = true; // Disable the resize handler during dragging
}

bool StatePreDrag::handleMouseMove(QPoint globalPos)
{
    if (q->m_draggable->dragCanStart(q->m_pressPos, globalPos)) {
        Q_EMIT q->manhattanLengthMove();
        return true;
    }
    return false;
}

bool StatePreDrag::handleMouseButtonRelease(QPoint)
{
    Q_EMIT q->dragCanceled();
    return false;
}

StateDragging::StateDragging(DragController *parent)
    : StateBase(parent)
{
}

StateDragging::~StateDragging() = default;

void StateDragging::onEntry(QEvent *)
{
    q->m_windowBeingDragged = q->m_draggable->makeWindow();
    if (q->m_windowBeingDragged) {
        qCDebug(state) << "StateDragging entered. m_draggable=" << q->m_draggable << "; m_windowBeingDragged=" << q->m_windowBeingDragged->floatingWindow();
    } else {
        // Shouldn't happen
        qWarning() << Q_FUNC_INFO << "No window being dragged for " << q->m_draggable->asWidget();
        Q_EMIT q->dragCanceled();
    }
}

bool StateDragging::handleMouseButtonRelease(QPoint globalPos)
{
    qCDebug(state) << "StateDragging: handleMouseButtonRelease";

    FloatingWindow *floatingWindow = q->m_windowBeingDragged->floatingWindow();
    if (!floatingWindow) {
        // It was deleted externally
        qCDebug(state) << "StateDragging: Bailling out, deleted externally";
        Q_EMIT q->dragCanceled();
        return true;
    }

    if (floatingWindow->anyNonDockable()) {
        qCDebug(state) << "StateDragging: Ignoring floating window with non dockable widgets";
        Q_EMIT q->dragCanceled();
        return true;
    }

    if (q->m_currentDropArea) {
        if (q->m_currentDropArea->drop(floatingWindow, globalPos)) {
            Q_EMIT q->dropped();
        } else {
            qCDebug(state) << "StateDragging: Bailling out, drop not accepted";
            Q_EMIT q->dragCanceled();
        }
    } else {
        qCDebug(state) << "StateDragging: Bailling out, not over a drop area";
        Q_EMIT q->dragCanceled();
    }
    return true;
}

bool StateDragging::handleMouseMove(QPoint globalPos)
{
    FloatingWindow *fw = q->m_windowBeingDragged->floatingWindow();
    if (!fw) {
        qCDebug(state) << "Canceling drag, window was deleted";
        Q_EMIT q->dragCanceled();
        return true;
    }

    if (!q->m_nonClientDrag)
        fw->windowHandle()->setPosition(globalPos - q->m_offset);


    if (fw->anyNonDockable()) {
        qCDebug(state) << "StateDragging: Ignoring non dockable floating window";
        return true;
    }

    DropArea *dropArea = q->dropAreaUnderCursor();
    if (q->m_currentDropArea && dropArea != q->m_currentDropArea)
        q->m_currentDropArea->removeHover();

    if (dropArea) {
        if (FloatingWindow *targetFw = dropArea->floatingWindow()) {
            if (targetFw->anyNonDockable()) {
                qCDebug(state) << "StateDragging: Ignoring non dockable target floating window";
                return false;
            }
        }

        dropArea->hover(fw, globalPos);
    }

    q->m_currentDropArea = dropArea;

    return true;
}

DragController::DragController(QObject *)
{
    if (KDDockWidgets::usesNativeDraggingAndResizing()) { // probably also good for wayland, which doesn't support mouse grabbing
        // Aero-snap jams if we're grabbing the mouse, so use the fallback grabber
        m_fallbackMouseGrabber = new FallbackMouseGrabber(this);
    }

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

bool DragController::isInNonClientDrag() const
{
    return isDragging() && m_nonClientDrag;
}

bool DragController::isInClientDrag() const
{
    return isDragging() && !m_nonClientDrag;
}

void DragController::grabMouseFor(QWidgetOrQuick *target)
{
    if (m_fallbackMouseGrabber) {
        m_fallbackMouseGrabber->grabMouse(target);
    } else {
        target->grabMouse();
    }
}

void DragController::releaseMouse(QWidgetOrQuick *target)
{
    if (m_fallbackMouseGrabber) {
        m_fallbackMouseGrabber->releaseMouse();
    } else {
        target->releaseMouse();
    }
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
        qCDebug(mouseevents) << "DragController::eventFilter e=" << e->type() << "; o=" << o;
        activeState()->handleMouseMove(QCursor::pos());
        return QStateMachine::eventFilter(o, e);
    }

    QMouseEvent *me = mouseEvent(e);
    if (!me)
        return QStateMachine::eventFilter(o, e);

    auto w = qobject_cast<QWidget*>(o);
    if (!w)
        return QStateMachine::eventFilter(o, e);

    qCDebug(mouseevents) << "DragController::eventFilter e=" << e->type() << "; o=" << o;

    switch (e->type()) {
    case QEvent::NonClientAreaMouseButtonPress: {
        if (auto fw = qobject_cast<FloatingWindow*>(o)) {
            if (fw->isInTitleBar(me->globalPos())) { // TODO: Port to isPositionDraggable()
                m_nonClientDrag = true;
                return activeState()->handleMouseButtonPress(draggableForQObject(o), me->globalPos(), me->pos());
            }
        }
        return QStateMachine::eventFilter(o, e);
    }
    case QEvent::MouseButtonPress:
        // For top-level windows that support native dragging all goes through the NonClient* events.
        // This also forbids dragging a FloatingWindow simply by pressing outside of the title area, in the background
        if (!KDDockWidgets::usesNativeDraggingAndResizing() || !w->isWindow())
            return activeState()->handleMouseButtonPress(draggableForQObject(o), me->globalPos(), me->pos());
        else break;
    case QEvent::MouseButtonRelease:
    case QEvent::NonClientAreaMouseButtonRelease:
        return activeState()->handleMouseButtonRelease(me->globalPos());
    case QEvent::NonClientAreaMouseMove:
    case QEvent::MouseMove:
        return activeState()->handleMouseMove(me->globalPos());
    default:
        break;
    }

    return QStateMachine::eventFilter(o, e);
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

    qCDebug(toplevels) << Q_FUNC_INFO << "Couldn't find hwnd for top-level" << hwnd;
    return nullptr;
}
#endif
template <typename T>
static QWidget* qtTopLevelUnderCursor_impl(QPoint globalPos, const QVector<T> &topLevels, T windowBeingDragged)
{
    for (int i = topLevels.size() -1; i >= 0; --i) {
        auto tl = topLevels.at(i);
        if (!tl->isVisible() || tl == windowBeingDragged || tl->isMinimized())
            continue;

        if (windowBeingDragged && windowBeingDragged->window() == tl->window())
            continue;

        if (tl->geometry().contains(globalPos)) {
            qCDebug(toplevels) << Q_FUNC_INFO << "Found top-level" << tl;
            return tl;
        }
    }

    return nullptr;
}

QWidgetOrQuick *DragController::qtTopLevelUnderCursor() const
{
#ifdef KDDOCKWIDGETS_QTWIDGETS

    QPoint globalPos = QCursor::pos();

    if (qApp->platformName() == QLatin1String("windows")) { // So -platform offscreen on Windows doesn't use this
        auto topLevels = qApp->topLevelWidgets();
# if defined(Q_OS_WIN)
        POINT globalNativePos;
        if (!GetCursorPos(&globalNativePos))
            return nullptr;

        // There might be windows that don't belong to our app in between, so use win32 to travel by z-order.
        // Another solution is to set a parent on all top-levels. But this code is orthogonal.
        HWND hwnd = HWND(m_windowBeingDragged->floatingWindow()->winId());
        while (hwnd) {
            hwnd = GetWindow(hwnd, GW_HWNDNEXT);
            RECT r;
            if (!GetWindowRect(hwnd, &r) || !IsWindowVisible(hwnd))
                continue;

            if (!PtInRect(&r, globalNativePos)) // Check if window is under cursor
                continue;

            if (auto tl = qtTopLevelForHWND(hwnd)) {
                if (tl->geometry().contains(globalPos) && tl->objectName() != QStringLiteral("_docks_IndicatorWindow_Overlay")) {
                    qCDebug(toplevels) << Q_FUNC_INFO << "Found top-level" << tl;
                    return tl;
                }
            } else {
                // Maybe it's embedded in a QWinWidget:
                for (auto topLevel : topLevels) {
                    if (QLatin1String(topLevel->metaObject()->className()) == QLatin1String("QWinWidget")) {
                        if (hwnd == GetParent(HWND(topLevel->windowHandle()->winId()))) {
                            if (topLevel->rect().contains(topLevel->mapFromGlobal(globalPos)) && topLevel->objectName() != QStringLiteral("_docks_IndicatorWindow_Overlay")) {
                                qCDebug(toplevels) << Q_FUNC_INFO << "Found top-level" << topLevel;
                                return topLevel;
                            }
                        }
                    }
                }

                // A window belonging to another app is below the cursor
                qCDebug(toplevels) << Q_FUNC_INFO << "Window from another app is under cursor" << hwnd;
                return nullptr;
            }
        }
# endif
    } else {
        // !Windows: Linux, macOS, offscreen (offscreen on Windows too), etc.

        // On Linux we don't have API to check the z-order of top-levels. So first check the floating windows
        // and check the MainWindow last, as the MainWindow will have lower z-order as it's a parent (TODO: How will it work with multiple MainWindows ?)
        // The floating window list is sorted by z-order, as we catch QEvent::Expose and move it to last of the list

        FloatingWindow *tlwBeingDragged = m_windowBeingDragged->floatingWindow();
        if (auto tl = qtTopLevelUnderCursor_impl(globalPos, DockRegistry::self()->nestedwindows(), tlwBeingDragged))
            return tl;

        return qtTopLevelUnderCursor_impl<QWidget*>(globalPos,
                                                    DockRegistry::self()->topLevels(/*excludeFloating=*/true),
                                                    tlwBeingDragged);
    }
#else
    // QtQuick:
    qWarning() << Q_FUNC_INFO << "Implement me!";
#endif

    qCDebug(toplevels) << Q_FUNC_INFO << "No top-level found";
    return nullptr;
}

DropArea *DragController::dropAreaUnderCursor() const
{
    auto topLevel = qtTopLevelUnderCursor();
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

    if (auto dock = qobject_cast<DockWidgetBase *>(topLevel)) {
        FloatingWindow *fw = dock->morphIntoFloatingWindow();
        m_windowBeingDragged->floatingWindow()->raise();
        return fw->dropArea();
    }

    auto *w = topLevel->childAt(topLevel->mapFromGlobal(QCursor::pos()));
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
