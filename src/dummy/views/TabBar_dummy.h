/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Implements a QTabWidget derived class with support for docking and undocking
 * KDockWidget::DockWidget as tabs .
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#pragma once

#include "View_dummy.h"
#include "views/TabBarViewInterface.h"

#include <QPointer>
#include <QHash>

#include "kdbindings/signal.h"

namespace KDDockWidgets::Controllers {
class TabBar;
}

namespace KDDockWidgets::Views {

class DockWidget;
class TabWidget;

class DOCKS_EXPORT TabBar_dummy
    : public View_dummy,
      public TabBarViewInterface
{
public:
    explicit TabBar_dummy(Controllers::TabBar *controller, View *parent = nullptr);
    int tabAt(QPoint localPos) const override;

    QString text(int index) const override;
    QRect rectForTab(int index) const override;

    void moveTabTo(int from, int to) override;
    Controllers::DockWidget *currentDockWidget() const override;
    bool tabsAreMovable() const override;

protected:
    void init() override;
};
}
