/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#ifndef KD_TABBAR_WIDGET_P_H
#define KD_TABBAR_WIDGET_P_H

#include "TabWidget_p.h"

#include <QTabBar>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DockWidget;
class TabWidget;

class DOCKS_EXPORT TabBarWidget : public QTabBar, public TabBar
{
    Q_OBJECT
public:
    explicit TabBarWidget(TabWidget *parent = nullptr);
    int numDockWidgets() const override;
    int tabAt(QPoint localPos) const override;
protected:
    bool dragCanStart(QPoint pressPos, QPoint pos) const override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *e) override;

};
}

#endif
