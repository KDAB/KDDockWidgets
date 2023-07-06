/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import QtQuick 2.9

DropArea {
    id: root

    property QtObject dropAreaCpp: null

    onPositionChanged: (drag) => {
        dropAreaCpp.beginDrag(mapToGlobal(drag.x, drag.y), drag.source);
    }
    onExited: (drag) => {
        dropAreaCpp.stop();
    }
    onDropped: (drag) => {
        dropAreaCpp.drop(mapToGlobal(drag.x, drag.y), drag.source);
    }
}
