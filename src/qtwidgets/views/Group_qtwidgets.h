/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"
#include "views/GroupViewInterface.h"

namespace KDDockWidgets::Controllers {
class Group;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT Group_qtwidgets : public View_qtwidgets<QWidget>, public GroupViewInterface
{
    Q_OBJECT
public:
    explicit Group_qtwidgets(Controllers::Group *controller, QWidget *parent = nullptr);
    void init() override;

    void renameTab(int index, const QString &) override;
    void changeTabIcon(int index, const QIcon &) override;
    void removeWidget_impl(Controllers::DockWidget *) override;
    int indexOfDockWidget_impl(const Controllers::DockWidget *) override;
    int currentIndex_impl() const override;
    void setCurrentTabIndex_impl(int index) override;
    void setCurrentDockWidget_impl(Controllers::DockWidget *) override;
    void insertDockWidget_impl(Controllers::DockWidget *, int index) override;
    Controllers::DockWidget *dockWidgetAt_impl(int index) const override;
    Controllers::DockWidget *currentDockWidget_impl() const override;
    int nonContentsHeight() const override;
    QRect dragRect() const override;

protected:
    void free_impl() override;
    void paintEvent(QPaintEvent *) override;
    QSize maxSizeHint() const override;
};

}
