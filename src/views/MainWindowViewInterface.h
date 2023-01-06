/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

QT_BEGIN_NAMESPACE
class QMargins;
class QRect;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Controllers {
class SideBar;
class MainWindow;
}

namespace Views {

class DockWidgetViewInterface;

/// @brief The interface that MainWindow views should implement
class DOCKS_EXPORT MainWindowViewInterface
{
public:
    explicit MainWindowViewInterface(Controllers::MainWindow *);
    virtual ~MainWindowViewInterface();
    virtual QMargins centerWidgetMargins() const = 0;
    virtual QRect centralAreaGeometry() const = 0;
    virtual void setContentsMargins(int left, int top, int right, int bottom) = 0;

    /// @brief Returns the main window controller
    Controllers::MainWindow *mainWindow() const;


    // controllers/MainWindow.h public interface:
    QString uniqueName() const;
    QStringList affinities() const;
    void setAffinities(const QStringList &names);
    MainWindowOptions options() const;
    bool isMDI() const;
    bool closeDockWidgets(bool force = false);
    bool sideBarIsVisible(KDDockWidgets::SideBarLocation) const;
    void clearSideBarOverlay(bool deleteFrame = true);
    void layoutEqually();
    bool anySideBarIsVisible() const;

    void addDockWidgetAsTab(DockWidgetViewInterface *dockwidget);
    void addDockWidget(DockWidgetViewInterface *dockWidget, KDDockWidgets::Location location,
                       DockWidgetViewInterface *relativeTo = nullptr,
                       KDDockWidgets::InitialOption initialOption = {});

    void moveToSideBar(DockWidgetViewInterface *);
    void moveToSideBar(DockWidgetViewInterface *, KDDockWidgets::SideBarLocation);
    void restoreFromSideBar(DockWidgetViewInterface *);
    void overlayOnSideBar(DockWidgetViewInterface *);
    void toggleOverlayOnSideBar(DockWidgetViewInterface *);
    void layoutParentContainerEqually(DockWidgetViewInterface *);

    void moveToSideBar(const QString &dockId);
    void moveToSideBar(const QString &dockId, KDDockWidgets::SideBarLocation);
    void restoreFromSideBar(const QString &dockId);
    void overlayOnSideBar(const QString &dockId);
    void toggleOverlayOnSideBar(const QString &dockId);
    void layoutParentContainerEqually(const QString &dockId);
    void addDockWidgetAsTab(const QString &dockId);
    void addDockWidget(const QString &dockId, KDDockWidgets::Location,
                       const QString &relativeToDockId = {}, KDDockWidgets::InitialOption = {});

protected:
    void init(const QString &name);
    Controllers::MainWindow *const m_mainWindow;
};

}

}
