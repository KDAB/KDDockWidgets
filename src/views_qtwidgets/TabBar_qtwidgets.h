/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "views/TabBar.h"

#include <QTabBar>

QT_BEGIN_NAMESPACE
class QMouseEvent;
QT_END_NAMESPACE

namespace KDDockWidgets::Controllers {
class TabBar;
class DockWidget;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT TabBar_qtwidgets : public View_qtwidgets<QTabBar>, public TabBar
{
    Q_OBJECT
public:
    explicit TabBar_qtwidgets(Controllers::TabBar *controller, QWidget *parent = nullptr);

    Controllers::TabBar *tabBar() const;

    Controllers::DockWidget *currentDockWidget() const override;

    QString text(int index) const override;
    QRect rectForTab(int index) const override;
    void moveTabTo(int from, int to) override;

    bool tabsAreMovable() const override;
    int tabAt(QPoint localPos) const override;

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    bool event(QEvent *) override;

private:
    Controllers::TabBar *const m_controller;
};

}
