/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SIDEBARWIDGET_P_H
#define KD_SIDEBARWIDGET_P_H


#include "../../docks_export.h"
#include "../SideBar_p.h"

QT_BEGIN_NAMESPACE
class QBoxLayout;
class QAbstractButton;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DockWidget;
class Frame;

class DOCKS_EXPORT SideBarWidget : public SideBar
{
    Q_OBJECT
public:
    explicit SideBarWidget(Qt::Orientation orientation, QWidget *parent);

protected:
    void addDockWidget_Impl(DockWidgetBase *dock) override;
    void removeDockWidget_Impl(DockWidgetBase *dock) override;

    // virtual so users can provide their own buttons
    virtual QAbstractButton* createButton();

private:
    QBoxLayout *const m_layout;
};

}

#endif
