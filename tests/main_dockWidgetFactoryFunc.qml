/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// @brief Used by tst_dockWidgetFactoryFunc, which restores a layout with unknown dock widgets

import QtQuick 2.6
import QtQuick.Controls 2.12
import com.kdab.dockwidgets 2.0 as KDDW

ApplicationWindow {
    id: window
    visible: true
    width: 1000
    height: 800

    // What the factory function does: "create", "null" or "wrongType"
    property string mode: "create"
    property var requested: []

    KDDW.DockingArea {
        objectName: "area"
        anchors.fill: parent
        uniqueName: "factory-mw"
    }

    Component {
        id: dockWidgetComponent
        KDDW.DockWidget {
            Rectangle {
                color: "blue"
                anchors.fill: parent
            }
        }
    }

    Component {
        id: notADockWidgetComponent
        QtObject {}
    }

    function installFactory() {
        KDDW.Config.dockWidgetFactoryFunc = function (dockWidgetId) {
            requested.push(dockWidgetId);

            if (mode === "null")
                return null;
            if (mode === "wrongType")
                return notADockWidgetComponent.createObject(null);

            return dockWidgetComponent.createObject(null, {
                uniqueName: dockWidgetId
            });
        };
    }

    function removeFactory() {
        KDDW.Config.dockWidgetFactoryFunc = null;
    }

    Component.onCompleted: installFactory()
}
