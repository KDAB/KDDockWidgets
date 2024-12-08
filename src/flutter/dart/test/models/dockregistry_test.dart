/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter_test/flutter_test.dart';
import 'package:KDDockWidgets/KDDockWidgets.dart';
import 'package:KDDockWidgets/private/Bindings.dart';

void main() {
  test('Dockregistry', () {
    final dr = DockRegistry.instance;
    expect(dr.dockItems.isEmpty, true);
    expect(dr.floatingItems.isEmpty, true);

    final dock = DockItem(uniqueName: "dw1");

    expect(dr.dockItems.length, 1);
    expect(dr.floatingItems.isEmpty, true);

    final fw = FloatingItem();
    fw.dropArea.addDockItem(dock, Location.LocationOnTop);
    expect(dr.dockItems.length, 1);
    expect(dr.floatingItems.isEmpty, false);
    expect(fw.dropArea.groups.length, 1);
    expect(dr.dockItems.length, 1);
    expect(dr.floatingItems.length, 1);

    fw.dropArea.groups.first.titlebar.onCloseClicked();
    expect(dr.dockItems.length, 1); // dock items are persistent
    expect(dr.floatingItems.isEmpty, true); // discarded when empty
    expect(fw.dropArea.groups.isEmpty, true);

    final dock2 = DockItem(uniqueName: "dw2");

    final fw2 = FloatingItem();
    fw2.dropArea.addDockItem(dock2, Location.LocationOnTop);
    expect(dr.floatingItems.length, 1);
    fw2.dropArea.removeDockItem(fw2.dropArea.groups.first.currentDockItem!);
    expect(dr.floatingItems.isEmpty, true);
  });
}
