/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SIDEBARWIDGET_P_H
#define KD_SIDEBARWIDGET_P_H

#include "View_qtwidgets.h"
#include "kddockwidgets/docks_export.h"
#include "../controllers/SideBar.h"

#include <QToolButton>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QAbstractButton;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DockWidget;
class Frame;

namespace Controllers {
class SideBar;
}

namespace Views {
class SideBar_qtwidgets;
}

class SideBarButton : public QToolButton
{
    Q_OBJECT
public:
    explicit SideBarButton(Controllers::DockWidgetBase *dw, Views::SideBar_qtwidgets *parent);
    bool isVertical() const;
    void paintEvent(QPaintEvent *) override;
    QSize sizeHint() const override;

private:
    Views::SideBar_qtwidgets *const m_sideBar;
    const QPointer<Controllers::DockWidgetBase> m_dockWidget;
};

namespace Views {

class DOCKS_EXPORT SideBar_qtwidgets : public View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit SideBar_qtwidgets(KDDockWidgets::Controllers::SideBar *,
                               KDDockWidgets::MainWindowBase *parent);

    bool isVertical() const; // TODO: Move to a potential base class

    void addDockWidget_Impl(Controllers::DockWidgetBase *dock); // TODO: Either override or remove Impl
    void removeDockWidget_Impl(Controllers::DockWidgetBase *dock);

    // virtual so users can provide their own buttons
    virtual SideBarButton *createButton(Controllers::DockWidgetBase *dw, SideBar_qtwidgets *parent) const;

private:
    Controllers::SideBar *const m_controller;
    QBoxLayout *const m_layout;
};
}

}

#endif
