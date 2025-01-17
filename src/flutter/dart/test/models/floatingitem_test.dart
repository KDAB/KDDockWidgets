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
  group('FloatingItem', () {
    test('isFloating', () {
      var dropArea = DropArea();
      final dockName = "dock1";
      expect(dropArea.containsDockItem(dockName), false);
      var dock = DockItem(uniqueName: dockName);
      dropArea.addDockItem(dock, Location.LocationOnTop);

      var group = dropArea.groups.first;
      // It's docked, so not floating yet
      expect(group.isFloating(), false);
      expect(dropArea.groups.length, 1);
      expect(group.dropArea, dropArea);

      // Undock:
      group.titlebar.onFloatClicked();
      expect(group.isFloating(), true);
      expect(dropArea.groups.length, 0);
      expect(group.dropArea != dropArea, true);

      // Redock:
      // group.titlebar.onFloatClicked();
      // expect(group.isFloating(), false);
    });
  });
}
