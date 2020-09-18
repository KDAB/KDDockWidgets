/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SIDEBAR_P_H
#define KD_SIDEBAR_P_H

#include "docks_export.h"
#include "QWidgetAdapter.h"

namespace KDDockWidgets {

class DockWidgetBase;

class DOCKS_EXPORT SideBar : public QWidgetAdapter
{
    Q_OBJECT
public:
    explicit SideBar(Qt::Orientation orientation, QWidgetOrQuick *parent = nullptr);

    void addDockWidget(DockWidgetBase *dw);
    void removeDockWidget(DockWidgetBase *dw);
    bool contains(DockWidgetBase *) const;

    /// @brief Returns this side bar's orientation
    Qt::Orientation orientation() const;

    /// @brief returns if this side bar has vertical orientation
    bool isVertical() const { return m_orientation == Qt::Vertical; }

    /// @brief returns whether there's no dock widgets
    bool isEmpty() const;

protected:
    virtual void addDockWidget_Impl(DockWidgetBase *dock) = 0;
    virtual void removeDockWidget_Impl(DockWidgetBase *dock) = 0;

    void onButtonClicked(DockWidgetBase *dw);

private:
    void onDockWidgetDestroyed(QObject *dw);
    void updateSize();

    QVector<DockWidgetBase *> m_dockWidgets;
    const Qt::Orientation m_orientation;
};

}

#endif
