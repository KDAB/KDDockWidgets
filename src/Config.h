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
 * @file
 * @brief Application wide config to tune certain beahviours of the framework.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DOCKWIDGETS_CONFIG_H
#define KD_DOCKWIDGETS_CONFIG_H

#include "docks_export.h"

namespace KDDockWidgets
{
class DockWidget;
typedef KDDockWidgets::DockWidget* (*DockWidgetFactoryFunc)(const QString &name);

/**
 * @brief Singleton to allow to choose certain behaviours of the framework.
 *
 * The setters should only be used before creating a QApplication.
 */
class DOCKS_EXPORT Config
{
public:

    ///@brief returns the singleton Config instance
    static Config &self();

    ~Config();

    enum Flag {
        Flag_None = 0,
        Flag_NativeTitleBar = 1, ///> Enables the Native OS title bar on OSes that support it (Windows 10, macOS), ignored otherwise. This is mutually exclusive with Flag_AeroSnap
        Flag_AeroSnapWithClientDecos = 2, ///> Enables AeroSnap even if we're not using the native title bar. Only supported on Windows 10.
        Flag_DraggableTabBar = 4, ///> The TabBar background next to the tabs is draggable and can be used to detach/attach windows
        Flag_Default = Flag_AeroSnapWithClientDecos ///> The defaults if nothing is set
    };
    Q_DECLARE_FLAGS(Flags, Flag)

    ///@brief getter for the flags
    Flags flags() const;

    ///@brief setter for the flags. Not all flags are guaranteed to be set, as the OS might not supported them
    ///Call @ref flags() after the setter if you need to know what was really set
    void setFlags(Flags flags);

    /**
     * @brief Registers the DockWidgetFactoryFunc. The default is nullptr, and is optional.
     *
     * A DockWidgetFactoryFunc is a function that receives a dock widget name and returns a DockWidget.
     *
     * When restoring @ref LayoutSaver requires all dock widgets to exist. If a DockWidget doesn't
     * exist then a DockWidgetFactoryFunc function is required, so the layout saver can ask
     * to create the DockWidget and then restore it.
     */
    void setDockWidgetFactoryFunc(DockWidgetFactoryFunc);

    ///@brief Getter for the DockWidgetFactoryFunc. nullptr by default
    DockWidgetFactoryFunc dockWidgetFactoryFunc() const;

private:
    Q_DISABLE_COPY(Config)
    Config();
    class Private;
    Private *const d;
};

}

#endif
