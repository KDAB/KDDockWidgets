/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "Helpers_p.h"
#include "ViewFactory.h"
#include "core/DockRegistry.h"

#include <QQmlEngine>

namespace KDDockWidgets::QtQuick {

class Singletons : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(KDDockWidgets::QtQuick::ViewFactory *widgetFactory READ widgetFactory CONSTANT)
    Q_PROPERTY(KDDockWidgets::DockRegistry *dockRegistry READ dockRegistry CONSTANT)
    Q_PROPERTY(KDDockWidgets::QtQuickHelpers *helpers READ helpers CONSTANT)
public:
    ~Singletons() override;
    KDDockWidgets::QtQuick::ViewFactory *widgetFactory() const;
    KDDockWidgets::DockRegistry *dockRegistry() const;
    KDDockWidgets::QtQuickHelpers *helpers() const;
};

}
