/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Singletons_p.h"
#include "ViewFactory.h"
#include "core/DockRegistry.h"
#include "core/DockWidget.h"
#include "Platform.h"
#include "Helpers_p.h"

using namespace KDDockWidgets::QtQuick;

Singletons::~Singletons() = default;

KDDockWidgets::QtQuick::ViewFactory *Singletons::widgetFactory() const
{
    return QtQuick::ViewFactory::self();
}

KDDockWidgets::DockRegistry *Singletons::dockRegistry() const
{
    return DockRegistry::self();
}

KDDockWidgets::QtQuickHelpers *Singletons::helpers() const
{
    if (auto plat = QtQuick::Platform::instance()) {
        return plat->helpers();
    }

    return nullptr;
}
