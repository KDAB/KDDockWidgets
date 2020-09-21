/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The QWidget counter part of TabWidgetWidget. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDTABWIDGETWIDGET_P_H
#define KDTABWIDGETWIDGET_P_H

#include "TabWidget_p.h"

#include <QTabWidget>

namespace KDDockWidgets {

class Frame;
class TabBar;

class DOCKS_EXPORT TabWidgetWidget : public QTabWidget, public TabWidget
{
    Q_OBJECT
public:
    explicit TabWidgetWidget(Frame *parent);

    TabBar *tabBar() const override;

    int numDockWidgets() const override;
    void removeDockWidget(DockWidgetBase *) override;
    int indexOfDockWidget(DockWidgetBase *) const override;
protected:
    void paintEvent(QPaintEvent *) override;
    void tabInserted(int index) override;
    void tabRemoved(int index) override;
    bool isPositionDraggable(QPoint p) const override;
    void setCurrentDockWidget(int index) override;
    void insertDockWidget(int index, DockWidgetBase *, const QIcon&, const QString &title) override;
    void setTabBarAutoHide(bool) override;
    void detachTab(DockWidgetBase *dockWidget) override;
    void renameTab(int index, const QString &) override;

    DockWidgetBase *dockwidgetAt(int index) const override;
    int currentIndex() const override;

private:
    Q_DISABLE_COPY(TabWidgetWidget)
    TabBar *const m_tabBar;
};
}

#endif
