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

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DOCKWIDGET_H
#define KD_DOCKWIDGET_H

#include "DockWidgetBase.h"

namespace KDDockWidgets {

/**
 * @brief Represents a dock widget.
 */
class DOCKS_EXPORT DockWidget : public DockWidgetBase
{
    Q_OBJECT
public:

    /**
     * @brief constructs a new DockWidgets
     * @param name the name of the dockwidget, should be unique. Use title for user visible text.
     * @param options optional options controlling behaviour
     * @param parent optional QWidget parent, for ownership purposes
     * @param flags optional Qt::WindowFlags to apply to the window
     */
    explicit DockWidget(const QString &name, Options options = {},
                        QWidget *parent = nullptr, Qt::WindowFlags flags = {});

    ///@brief destructor
    ~DockWidget() override;

protected:

    class Private;
    Private *const d;
};

}

#endif
