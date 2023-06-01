/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/core/Screen.h"


namespace KDDockWidgets::flutter {

/// Class to represent a hardware screen. For now only returns dummy values
/// We'll see what to do after flutter has multi-window
class Screen : public Core::Screen
{
public:
    ~Screen() override;
    QString name() const override;
    QSize size() const override;
    QRect geometry() const override;
    qreal devicePixelRatio() const override;
    QSize availableSize() const override;
    QRect availableGeometry() const override;
    QSize virtualSize() const override;
    QRect virtualGeometry() const override;
    bool equals(std::shared_ptr<Core::Screen> other) const override;
};

}
