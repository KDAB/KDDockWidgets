/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

class QMargins;
class QRect;

namespace KDDockWidgets {

namespace Controllers {
class SideBar;
class MainWindow;
}

namespace Views {

/// @brief The interface that MainWindow views should implement
class DOCKS_EXPORT MainWindowViewInterface
{
public:
    explicit MainWindowViewInterface(Controllers::MainWindow *);
    virtual ~MainWindowViewInterface();
    virtual QMargins centerWidgetMargins() const = 0;
    virtual QRect centralAreaGeometry() const = 0;
    virtual void setContentsMargins(int left, int top, int right, int bottom) = 0;
    virtual Controllers::SideBar *sideBar(SideBarLocation loc) const = 0;

    /// @brief Returns the main window controller
    Controllers::MainWindow *mainWindow() const;

protected:
    Controllers::MainWindow *const m_mainWindow;
};

}

}
