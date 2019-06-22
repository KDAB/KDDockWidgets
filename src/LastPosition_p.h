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

/**
 * @file Helper class so dockwidgets can be restored to their previous position.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_LAST_POSITION_P_H
#define KD_LAST_POSITION_P_H

#include "multisplitter/Item_p.h"
#include "MainWindow.h"
#include "Logging_p.h"

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
    Q_DISABLE_COPY(LastPosition)
public:
    LastPosition() = default;
    ~LastPosition()
    {
        if (m_layoutItemInMainWindow) {
            m_layoutItemInMainWindow->unref();
            m_layoutItemInMainWindow = nullptr;
        }
    }

    /**
     * @brief Returns whether the LastPosition is valid. If invalid then the DockWidget was never
     * in a MainWindow.
     */
    bool isValid() const { return !m_layoutItemInMainWindow.isNull(); }

    /**
     * @brief returns if the dock widget was in a tab
     * @return if the position is tabbed, false otherwise
     */
    bool isTabbed() const
    {
        return m_tabIndex != -1;
    }

    ///@brief The tab index in case the dock widget was in a TabWidget, -1 otherwise.
    int m_tabIndex = -1;

    ///@brief Sets the last layout item where the dock widget was
    void setLayoutItem(Item *layoutItem)
    {
        Q_ASSERT(layoutItem);
        if (layoutItem == m_layoutItemInMainWindow)
            return;

        const bool isMainWindow = qobject_cast<MainWindow*>(layoutItem->window());
        if (!isMainWindow) { // For now we only restore widgets to the main window, for simplicity. TODO: Support restoring to FloatingWindow once the concept is proven.
            qCDebug(placeholder) << Q_FUNC_INFO <<"Ignoring non main window placeholder.";
            return;
        }

        if (m_layoutItemInMainWindow)
            m_layoutItemInMainWindow->unref();

        m_layoutItemInMainWindow = layoutItem;

        if (m_layoutItemInMainWindow)
            m_layoutItemInMainWindow->ref();
    }

    QWidget *window() const { return m_layoutItemInMainWindow ? m_layoutItemInMainWindow->window() : nullptr; }
    Item* layoutItem() const { return m_layoutItemInMainWindow; }

private:
    ///@brief The item where the DockWidget was in the MainWindow layout.
    QPointer<Item> m_layoutItemInMainWindow; // QPointer just for the case of someone deleting a whole MainWindow
};
}

#endif
