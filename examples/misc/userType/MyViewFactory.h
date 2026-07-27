/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/qtwidgets/ViewFactory.h>

// clazy:excludeall=ctor-missing-parent-argument

/// The values passed to DockWidget::setUserType(). Each one gets a differently styled
/// TitleBar, Group and TabBar, picked by UserDataViewFactory below.
enum UserType {
    UserType_Note = 1,
    UserType_Task = 2,
    UserType_Alert = 3,
};

/// A ViewFactory that instantiates a different KDDockWidgets::Core::TitleBar,
/// KDDockWidgets::Core::Group and KDDockWidgets::Core::TabBar sub-class depending on the
/// userType() of the DockWidget that's initially covered by them.
class UserDataViewFactory : public KDDockWidgets::QtWidgets::ViewFactory
{
    Q_OBJECT
public:
    // Needed since we're only overriding the userType overloads below; without this the
    // 2-arg createTitleBar()/createGroup()/createTabBar() inherited from QtWidgets::ViewFactory
    // would be hidden.
    using KDDockWidgets::QtWidgets::ViewFactory::createGroup;
    using KDDockWidgets::QtWidgets::ViewFactory::createTabBar;
    using KDDockWidgets::QtWidgets::ViewFactory::createTitleBar;

    KDDockWidgets::Core::View *createTitleBar(KDDockWidgets::Core::TitleBar *controller,
                                              KDDockWidgets::Core::View *parent,
                                              int userType) const override;

    KDDockWidgets::Core::View *createGroup(KDDockWidgets::Core::Group *controller,
                                           KDDockWidgets::Core::View *parent,
                                           int userType) const override;

    KDDockWidgets::Core::View *createTabBar(KDDockWidgets::Core::TabBar *tabBar,
                                            KDDockWidgets::Core::View *parent,
                                            int userType) const override;
};
