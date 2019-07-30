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

#ifndef KD_WINDOWBEINGDRAGGED_P_H
#define KD_WINDOWBEINGDRAGGED_P_H

#include "docks_export.h"

#include "FloatingWindow_p.h"
#include "DockWidget.h"
#include "TitleBar_p.h"
#include "Logging_p.h"

#include <QPointer>

namespace KDDockWidgets {

struct DOCKS_EXPORT_FOR_UNIT_TESTS WindowBeingDragged
{
public:
    WindowBeingDragged(FloatingWindow *fw)
        : m_floatingWindow(fw)
        , m_dockWidget(nullptr)
        , m_draggable(fw)
    {
        init();
    }

    ~WindowBeingDragged();
    void init();

    DockWidget *dockWidget() const { return m_dockWidget; }
    FloatingWindow *floatingWindow() const { return m_floatingWindow; }
    Draggable *draggable() const { return window() ? m_draggable : nullptr; }

    QWidget *window() const
    {
        if (m_floatingWindow)
            return m_floatingWindow;

        return m_dockWidget;
    }

    ///@brief grabs or releases the mouse
    void grabMouse(bool grab);

private:
    Q_DISABLE_COPY(WindowBeingDragged)
    QPointer<FloatingWindow> m_floatingWindow;
    QPointer<DockWidget> m_dockWidget;
    Draggable *const m_draggable;
};
}

#endif
