/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtwidgets.h"

namespace KDDockWidgets::Controllers {
class Frame;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT Frame_qtwidgets : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit Frame_qtwidgets(Controllers::Frame *controller, QWidget *parent = nullptr);
    void init() override;

    void setLayoutItem(Layouting::Item *item) override;

    void renameTab(int index, const QString &);
    void changeTabIcon(int index, const QIcon &);
    void removeWidget_impl(Controllers::DockWidgetBase *);
    int indexOfDockWidget_impl(const Controllers::DockWidgetBase *);
    int currentIndex_impl() const;
    void setCurrentTabIndex_impl(int index);
    void setCurrentDockWidget_impl(Controllers::DockWidgetBase *);
    void insertDockWidget_impl(Controllers::DockWidgetBase *, int index);
    Controllers::DockWidgetBase *dockWidgetAt_impl(int index) const;
    Controllers::DockWidgetBase *currentDockWidget_impl() const;
    int nonContentsHeight() const;

    Controllers::Frame *frame() const;
    QRect dragRect() const;

Q_SIGNALS:
    void layoutInvalidated();

protected:
    void free_impl() override;
    void paintEvent(QPaintEvent *) override;
    QSize maxSizeHint() const override;

private:
    void closeEvent(QCloseEvent *e) override;
    bool event(QEvent *) override;
    Controllers::Frame *const m_controller;
};

}
