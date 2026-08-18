/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import QtQuick.Controls 2.12

// The alternative guest, so "Swap component" has something to swap to.
Rectangle {
    anchors.fill: parent
    color: "#4a6fa5"

    Label {
        anchors.centerIn: parent
        color: "white"
        text: "Guest2.qml"
    }
}
