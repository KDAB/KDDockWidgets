/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef KD_LAST_POSITION_H
#define KD_LAST_POSITION_H

/**
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include <QPointer>

namespace KDDockWidgets {

class DockWidget;
class Frame;
/**
 * @internal
 * @brief Represents the DockWidget's last position.
 *
 * The DockWidget's position is saved when its closed and restored when it's shown.
 * This class holds that position.
 */
class LastPosition {
public:

    /**
     * @brief returns if the dock widget was in a tab
     * @return if the position is tabbed, false otherwise
     */
    bool isTabbed() const
    {
        return m_tabIndex != -1 && !m_frame.isNull();
    }

    ///@brief The tab index in case the dock widget was in a TabWidget, -1 otherwise.
    int m_tabIndex = -1;

    ///@brief The frame that contained this dock widget
    QPointer<Frame> m_frame;
};
}

#endif
