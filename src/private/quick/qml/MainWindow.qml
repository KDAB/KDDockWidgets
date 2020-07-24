/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9
import com.kdab.dockwidgets 1.0

MainWindowQuick {
    id: root
    dropArea: dropArea
    anchors.fill: parent

    Item {
        id: centralItem // mimic the hierarchy of QtWidgets
        anchors.fill: parent

        DropAreaWithCentralFrame {
            id: dropArea
            anchors.fill: parent
        }
    }
}
