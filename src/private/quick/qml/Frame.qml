/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9

Rectangle {
    id: root
    property QtObject frameCpp

    color: "cyan"
    anchors.fill: parent

    TitleBar {
        height: 30
        titleBarCpp: frameCpp ? frameCpp.titleBar : null
        anchors {
            top:  parent.top
            left: parent.left
            right: parent.right
        }
    }
}
