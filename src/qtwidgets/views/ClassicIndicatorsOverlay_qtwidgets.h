/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"

namespace KDDockWidgets {

class ClassicIndicators;

namespace Views {

class DOCKS_EXPORT ClassicIndicatorsOverlay_qtwidgets : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit ClassicIndicatorsOverlay_qtwidgets(ClassicIndicators *controller, QWidget *parent = nullptr);
    ~ClassicIndicatorsOverlay_qtwidgets() override;
    bool onResize(QSize newSize) override;

private:
    ClassicIndicators *const m_controller;
};

}

}
