/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindowQuick_p.h"
#include "DropAreaWithCentralFrame_p.h"

#include <QDebug>

using namespace KDDockWidgets;

MainWindowQuick::MainWindowQuick(const QString &uniqueName, MainWindowOptions options,
                                 QWidgetAdapter *parent)
    : MainWindowBase(uniqueName, options, parent)
{
    QWidgetAdapter::makeItemFillParent(this);
    QWidgetAdapter::makeItemFillParent(dropArea());
}

SideBar *MainWindowQuick::sideBar(SideBarLocation) const
{
    qWarning() << Q_FUNC_INFO << "SideBar hasn't been implemented yet";
    return nullptr;
}

QMargins MainWindowQuick::centerWidgetMargins() const
{
    qWarning() << Q_FUNC_INFO << "SideBar hasn't been implemented yet";
    return {};
}
