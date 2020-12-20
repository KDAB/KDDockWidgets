/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief The QQuickItem counter part of TabWidgetQuick. Handles GUI while TabWidget handles state.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDTABWIDGETQUICK_P_H
#define KDTABWIDGETQUICK_P_H

#include "TabWidget_p.h"
#include "QWidgetAdapter_quick_p.h"

#include <QQuickItem>

namespace KDDockWidgets {

class Frame;
class TabBar;

class DOCKS_EXPORT TabWidgetQuick
    : public QWidgetAdapter
    , public TabWidget
{
    Q_OBJECT
public:
    explicit TabWidgetQuick(Frame *parent);

    TabBar *tabBar() const override;

    int numDockWidgets() const override;
    void removeDockWidget(DockWidgetBase *) override;
    int indexOfDockWidget(DockWidgetBase *) const override;
protected:

    bool isPositionDraggable(QPoint p) const override;
    void setCurrentDockWidget(int index) override;
    void insertDockWidget(int index, DockWidgetBase *, const QIcon&, const QString &title) override;
    void setTabBarAutoHide(bool) override;
    void renameTab(int index, const QString &) override;

    DockWidgetBase *dockwidgetAt(int index) const override;
    int currentIndex() const override;

private:
    Q_DISABLE_COPY(TabWidgetQuick)
    TabBar *const m_tabBar;
};

}

#endif
