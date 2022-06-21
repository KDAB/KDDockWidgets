/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/KDDockWidgets.h"

namespace KDDockWidgets {

namespace Controllers {
class DockWidget;
class Group;
class TitleBar;
}

namespace Views {

/// @brief The interface that DockWidget views should implement
class DOCKS_EXPORT DockWidgetViewInterface
{
public:
    explicit DockWidgetViewInterface(Controllers::DockWidget *);
    virtual ~DockWidgetViewInterface();

    Controllers::Group *frame() const;
    Controllers::DockWidget *dockWidget() const;
    Controllers::TitleBar *actualTitleBar() const;

    bool isFocused() const;
    bool isFloating() const;
    void setFloating(bool);
    QString uniqueName() const;
    QString title() const;
    void setTitle(const QString &);
    void setAsCurrentTab();
    QAction *toggleAction() const;
    QAction *floatAction() const;
    bool isOpen() const;
    void forceClose();
    void show();
    void raise();
    void moveToSideBar();
    void setIcon(const QIcon &icon, IconPlaces places = IconPlace::All);
    QIcon icon(IconPlace place = IconPlace::TitleBar) const;

    void setAffinities(const QStringList &);
    void setAffinityName(const QString &name);
    QStringList affinities() const;

    void addDockWidgetAsTab(DockWidgetViewInterface *other,
                            KDDockWidgets::InitialOption initialOption = {});

    void
    addDockWidgetToContainingWindow(DockWidgetViewInterface *other,
                                    KDDockWidgets::Location location,
                                    DockWidgetViewInterface *relativeTo = nullptr,
                                    KDDockWidgets::InitialOption initialOption = {});

    DockWidgetOptions options() const;
    void setOptions(DockWidgetOptions);

protected:
    Controllers::DockWidget *const m_dockWidget;
};

}

}
