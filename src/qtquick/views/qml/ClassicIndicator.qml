/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import com.kdab.dockwidgets 2.0

Image {
    id: root
    required property ClassicDropIndicatorOverlay overlayWindow
    property int indicatorType: KDDockWidgets.DropLocation_None
    readonly property bool isHovered: root.overlayWindow && root.overlayWindow.currentDropLocation === indicatorType

    source: root.overlayWindow ? ("qrc:/img/classic_indicators/" + root.overlayWindow.iconName(indicatorType, isHovered) + ".png") : ""
    width: 64
    height: 64
}
