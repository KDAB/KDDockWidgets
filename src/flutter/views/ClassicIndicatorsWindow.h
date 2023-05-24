/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "core/views/ClassicIndicatorWindowViewInterface.h"

namespace KDDockWidgets {

class Indicator;

namespace Core {
class ClassicDropIndicatorOverlay;
}

namespace flutter {

class IndicatorWindow : public Core::ClassicIndicatorWindowViewInterface
{
public:
    explicit IndicatorWindow(Core::ClassicDropIndicatorOverlay *classicIndicators);

    DropLocation hover(QPoint globalPos) override;
    void updatePositions() override;
    QPoint posForIndicator(DropLocation) const override;
    void raise() override;
    void setVisible(bool) override;
    bool isWindow() const override;
    void setGeometry(QRect) override;
    void resize(QSize) override;
    void setObjectName(const QString &) override;

private:
    Core::ClassicDropIndicatorOverlay *const classicIndicators;
};

}

}
