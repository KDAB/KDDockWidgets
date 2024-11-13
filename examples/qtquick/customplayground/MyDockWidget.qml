/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.6

// Will be moved to a plugin in the future, if there's enough demand
import "qrc:/kddockwidgets/qtquick/views/qml/" as KDDW

KDDW.DockWidget {
    id: root
    color:  "black"
    border.color: (dockWidgetCpp && dockWidgetCpp.isFocused) ? "orange" : "black"
    border.width: (dockWidgetCpp && dockWidgetCpp.isFocused) ? 2 : 1
}
