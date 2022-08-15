/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "views/TabBarViewInterface.h"

#include <QTabBar>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QTabWidget;
QT_END_NAMESPACE

namespace KDDockWidgets::Controllers {
class TabBar;
class DockWidget;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT TabBar_qtwidgets : public View_qtwidgets<QTabBar>, public TabBarViewInterface
{
    Q_OBJECT
public:
    explicit TabBar_qtwidgets(Controllers::TabBar *controller, QWidget *parent = nullptr);

    Controllers::TabBar *tabBar() const;

    void setCurrentIndex(int index) override;

    QString text(int index) const override;
    QRect rectForTab(int index) const override;
    void moveTabTo(int from, int to) override;

    int tabAt(QPoint localPos) const override;
    void renameTab(int index, const QString &) override;
    void changeTabIcon(int index, const QIcon &icon) override;
    void removeDockWidget(Controllers::DockWidget *) override;
    void insertDockWidget(int index, Controllers::DockWidget *, const QIcon &,
                          const QString &title) override;
    QTabWidget *tabWidget() const;
    void setTabsAreMovable(bool) override;

Q_SIGNALS:
    void dockWidgetInserted(int index);
    void dockWidgetRemoved(int index);

protected:
    void init() override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    bool event(QEvent *) override;
    void tabInserted(int index) override;
    void tabRemoved(int index) override;

private:
    Controllers::TabBar *const m_controller;
};

}
