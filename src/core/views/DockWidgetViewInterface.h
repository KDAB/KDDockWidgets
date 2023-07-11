/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/KDDockWidgets.h"

namespace KDDockWidgets {

namespace Core {

class DockWidget;
class Group;
class TitleBar;

/// @brief The interface that DockWidget views should implement
class DOCKS_EXPORT DockWidgetViewInterface
{
public:
    explicit DockWidgetViewInterface(DockWidget *);
    virtual ~DockWidgetViewInterface();

    Group *group() const;
    DockWidget *dockWidget() const;
    TitleBar *actualTitleBar() const;

    bool isFocused() const;
    bool isFloating() const;
    void setFloating(bool);
    QString uniqueName() const;
    QString title() const;
    void setTitle(const QString &);
    void setAsCurrentTab();
    bool isOpen() const;
    void forceClose();
    void open();
    void raise();
    void moveToSideBar();
    void setIcon(const Icon &icon, IconPlaces places = IconPlace::All);
    Icon icon(IconPlace place = IconPlace::TitleBar) const;

    void setAffinities(const Vector<QString> &);
    void setAffinityName(const QString &name);
    Vector<QString> affinities() const;

    void addDockWidgetAsTab(DockWidgetViewInterface *other,
                            KDDockWidgets::InitialOption initialOption = {});

    void addDockWidgetToContainingWindow(DockWidgetViewInterface *other,
                                         KDDockWidgets::Location location,
                                         DockWidgetViewInterface *relativeTo = nullptr,
                                         KDDockWidgets::InitialOption initialOption = {});

    DockWidgetOptions options() const;
    void setOptions(DockWidgetOptions);

    /// @deprecated. Use open() instead.
    void show();

protected:
    DockWidget *const m_dockWidget;
};

}

}
