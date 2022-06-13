/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/ViewFactory.h>

#include <QPainter>

// clazy:excludeall=ctor-missing-parent-argument

class CustomWidgetFactory : public KDDockWidgets::DefaultWidgetFactory
{
    Q_OBJECT
public:
    KDDockWidgets::TitleBar *createTitleBar(KDDockWidgets::Frame *frame) const override;
    KDDockWidgets::TitleBar *createTitleBar(KDDockWidgets::FloatingWindow *fw) const override;
    KDDockWidgets::View *createSeparator(KDDockWidgets::Controllers::Separator *, KDDockWidgets::View *parent = nullptr) const override;
};
