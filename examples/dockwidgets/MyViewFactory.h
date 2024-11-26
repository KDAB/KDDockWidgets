/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/qtwidgets/ViewFactory.h>

// clazy:excludeall=ctor-missing-parent-argument

class CustomWidgetFactory : public KDDockWidgets::QtWidgets::ViewFactory
{
    Q_OBJECT
public:
    KDDockWidgets::Core::View *createTitleBar(KDDockWidgets::Core::TitleBar *,
                                              KDDockWidgets::Core::View *parent) const override;
    KDDockWidgets::Core::View *createSeparator(KDDockWidgets::Core::Separator *,
                                               KDDockWidgets::Core::View *parent = nullptr) const override;
    KDDockWidgets::Core::View *createGroup(KDDockWidgets::Core::Group *, KDDockWidgets::Core::View *parent) const override;
};
