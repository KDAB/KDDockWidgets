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

#include "WindowBeingDragged_p.h"
#include "DragController_p.h"
#include "Logging_p.h"

using namespace KDDockWidgets;

static Draggable* bestDraggable(Draggable *draggable)
{
    // When de detach a title bar it will get hidden and we only the title bar of the FloatingWindow is visible
    /// Apparently that causes problems with grabbing the mouse, so instead use a visible draggable.
    // grabbing mouse on an hidden window works usually, it's some edge case on Windows with MFC.
    if (auto titleBar = qobject_cast<TitleBar*>(draggable->asWidget())) {
        if (titleBar->isVisible())
            return draggable;

        auto fw = qobject_cast<FloatingWindow*>(titleBar->window());
        if (!fw) // defensive, doesn't happen
            return draggable;

        if (fw->titleBar() == titleBar) {
            // Defensive, doesn't happen
            return draggable;
        } else {
            return fw;
        }
    } else {
        return draggable;
    }
}

WindowBeingDragged::WindowBeingDragged(FloatingWindow *fw, Draggable *draggable)
    : m_floatingWindow(fw)
    , m_draggable(bestDraggable(draggable)->asWidget())
{
    init();
}

WindowBeingDragged::~WindowBeingDragged()
{
    grabMouse(false);
}

void WindowBeingDragged::init()
{
    Q_ASSERT(m_floatingWindow);
    grabMouse(true);
    m_floatingWindow->raise();
}

void WindowBeingDragged::grabMouse(bool grab)
{
    if (!m_draggable)
        return;

    qCDebug(hovering) << "WindowBeingDragged: grab " << m_floatingWindow << grab << m_draggable;
    if (grab)
        DragController::instance()->grabMouseFor(m_draggable);
    else
        DragController::instance()->releaseMouse(m_draggable);
}
