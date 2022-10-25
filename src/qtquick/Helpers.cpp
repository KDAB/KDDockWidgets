/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Helpers_p.h"
#include "DockRegistry.h"
#include "controllers/Group.h"
#include "qtcommon/View_qt.h"

#include <QQuickItem>

using namespace KDDockWidgets;

QtQuickHelpers::QtQuickHelpers()
{
    connect(DockRegistry::self(), &DockRegistry::groupInMDIResizeChanged, this,
            &QtQuickHelpers::groupInMDIResizeChanged);
}

qreal QtQuickHelpers::logicalDpiFactor(const QQuickItem *) const
{
    return 1; // TODO: Support the actual dpi factor.
    // return KDDockWidgets::logicalDpiFactor(item);
}

QObject *QtQuickHelpers::groupViewInMDIResize() const
{
    if (auto group = DockRegistry::self()->groupInMDIResize())
        return Views::View_qt::asQObject(group->view());

    return nullptr;
}
