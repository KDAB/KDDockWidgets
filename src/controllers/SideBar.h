/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SIDEBAR_P_H
#define KD_SIDEBAR_P_H

#pragma once

#include "kddockwidgets/docks_export.h"

#include "kddockwidgets/KDDockWidgets.h"
#include "../Controller.h"

namespace KDDockWidgets {

class MainWindowBase;

namespace Controllers {

class DockWidgetBase;

class DOCKS_EXPORT SideBar : public Controller
{
    Q_OBJECT
public:
    explicit SideBar(SideBarLocation, MainWindowBase *parent = nullptr);

    void addDockWidget(DockWidgetBase *dw);
    void removeDockWidget(DockWidgetBase *dw);
    bool containsDockWidget(DockWidgetBase *) const;

    /// @brief Returns this side bar's orientation
    Qt::Orientation orientation() const;

    /// @brief returns if this side bar has vertical orientation
    bool isVertical() const
    {
        return m_orientation == Qt::Vertical;
    }

    /// @brief returns whether there's no dock widgets
    bool isEmpty() const;

    /// @brief returns the sidebar's location in the main window
    SideBarLocation location() const;

    /// @brief Returns the main window this side bar belongs to
    MainWindowBase *mainWindow() const;

    /// @brief Toggles the dock widget overlay. Equivalent to the user clicking on the button.
    void toggleOverlay(DockWidgetBase *);

    /// @brief returns a serialization of this sidebar's state
    /// Currently it's just a list of dock widget ids
    QStringList serialize() const;

    /// @brief clears the sidebar (removes all dock widgets from it)
    void clear();

    void onButtonClicked(DockWidgetBase *dw);

private:
    void onDockWidgetDestroyed(QObject *dw);
    void updateSize();

    MainWindowBase *const m_mainWindow;
    QVector<DockWidgetBase *> m_dockWidgets;
    const SideBarLocation m_location;
    const Qt::Orientation m_orientation;
};

}

}

#endif
