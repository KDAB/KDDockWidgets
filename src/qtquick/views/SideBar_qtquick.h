/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "View_qtquick.h"
#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/views/SideBarViewInterface.h"

#include <QToolButton>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QAbstractButton;
QT_END_NAMESPACE

namespace KDDockWidgets {

class Group;

namespace Controllers {
class SideBar;
}

namespace Views {
class SideBar_qtquick;
}

class SideBarButton : public QToolButton
{
    Q_OBJECT
public:
    explicit SideBarButton(Controllers::DockWidget *dw, Views::SideBar_qtquick *parent);
    bool isVertical() const;
    void paintEvent(QPaintEvent *) override;
    QSize sizeHint() const override;

private:
    Views::SideBar_qtquick *const m_sideBar;
    const QPointer<Controllers::DockWidget> m_dockWidget;
};

namespace Views {

class DOCKS_EXPORT SideBar_qtquick : public View_qtquick<QQuickItem>, public SideBarViewInterface
{
    Q_OBJECT
public:
    explicit SideBar_qtquick(Controllers::SideBar *, QQuickItem *parent);

    void init() override;
    bool isVertical() const; // TODOm3: Move to a potential base class

    void addDockWidget_Impl(Controllers::DockWidget *) override;
    void removeDockWidget_Impl(Controllers::DockWidget *) override;

    // virtual so users can provide their own buttons
    virtual SideBarButton *createButton(Controllers::DockWidget *dw, SideBar_qtquick *parent) const;

private:
    QBoxLayout *m_layout = nullptr;
};
}

}

#endif
