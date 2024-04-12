/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sergio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import QtQuick.Controls 2.15
import com.kdab.dockwidgets 2.0 as KDDW

Item {
    anchors.fill: parent

    property var background
    property var logo

    KDDW.LayoutSaver {
        id: layoutSaver
    }

    Row {
    Button {
        text: "Save1"
        onClicked: layoutSaver.saveToFile("mySavedLayout1.json");
    }

    Button {
        text: "Restore1"
        onClicked: layoutSaver.restoreFromFile("mySavedLayout1.json");
    }

    Button {
        text: "Save2"
        onClicked: layoutSaver.saveToFile("mySavedLayout2.json");
    }

    Button {
        text: "Restore2"
        onClicked: layoutSaver.restoreFromFile("mySavedLayout2.json");
    }
    }
}
