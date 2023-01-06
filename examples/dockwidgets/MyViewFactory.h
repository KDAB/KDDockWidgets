/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/ViewFactory_qtwidgets.h>

// clazy:excludeall=ctor-missing-parent-argument

class CustomWidgetFactory : public KDDockWidgets::ViewFactory_qtwidgets
{
    Q_OBJECT
public:
    KDDockWidgets::View *createTitleBar(KDDockWidgets::Controllers::TitleBar *,
                                        KDDockWidgets::View *parent) const override;
    KDDockWidgets::View *createSeparator(KDDockWidgets::Controllers::Separator *,
                                         KDDockWidgets::View *parent = nullptr) const override;
};
