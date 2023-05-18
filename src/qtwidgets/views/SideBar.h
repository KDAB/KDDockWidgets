/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SIDEBARWIDGET_P_H
#define KD_SIDEBARWIDGET_P_H

#include "View.h"
#include "kddockwidgets/docks_export.h"
#include "core/views/SideBarViewInterface.h"

#include <QToolButton>
#include <QPointer>

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QAbstractButton;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Core {
class SideBar;
}

namespace qtwidgets {
class SideBar;
}

class DOCKS_EXPORT SideBarButton : public QToolButton
{
    Q_OBJECT
public:
    explicit SideBarButton(Core::DockWidget *dw, qtwidgets::SideBar *parent);

protected:
    void paintEvent(QPaintEvent *) override;
    QSize sizeHint() const override;

private:
    bool isVertical() const;
    Core::SideBar *const m_sideBar;
    const QPointer<Core::DockWidget> m_dockWidget;
};

namespace qtwidgets {

class DOCKS_EXPORT SideBar : public View<QWidget>, public Core::SideBarViewInterface
{
    Q_OBJECT
public:
    explicit SideBar(Core::SideBar *, QWidget *parent);

protected:
    void addDockWidget_Impl(Core::DockWidget *dock) override;
    void removeDockWidget_Impl(Core::DockWidget *dock) override;

    // virtual so users can provide their own buttons
    virtual SideBarButton *createButton(Core::DockWidget *dw,
                                        SideBar *parent) const;

private:
    void init() override;

    QBoxLayout *m_layout = nullptr;
};
}

}

#endif