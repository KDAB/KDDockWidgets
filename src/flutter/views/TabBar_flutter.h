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

#include "View_flutter.h"
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

class DOCKS_EXPORT TabBar_flutter : public View_flutter, public TabBarViewInterface
{
public:
    explicit TabBar_flutter(Controllers::TabBar *controller, View *parent = nullptr);
    int tabAt(QPoint localPos) const override;

    QString text(int index) const override;
    QRect rectForTab(int index) const override;

    void moveTabTo(int from, int to) override;

    void changeTabIcon(int index, const QIcon &icon) override;
    void removeDockWidget(Controllers::DockWidget *dw) override;
    void insertDockWidget(int index, Controllers::DockWidget *dw, const QIcon &icon,
                          const QString &title) override;
    void renameTab(int index, const QString &name) override;
    void setCurrentIndex(int index) override;

    /// Tells flutter to rebuild our tab widget. Called when adding or removing tabs.
    virtual void onRebuildRequested() = 0;

protected:
    void init() override;
};
}
