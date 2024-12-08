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
  group('DropArea', () {
    test('Constructor', () {
      DropArea();
    });

    test('containsDockItem', () {
      var dropArea = DropArea();
      final dockName = "dock1";
      expect(dropArea.containsDockItem(dockName), false);
      var dock = DockItem(uniqueName: dockName);
      dropArea.addDockItem(dock, Location.LocationOnTop);
      expect(dropArea.containsDockItem(dockName), true);
    });
  });

  test('basic', () {
    const length = 501;
    const separatorLength = 5;

    var dropArea = DropArea();
    dropArea.setLayoutSize(length, length);

    var dock1 = DockItem(uniqueName: "dock1");
    dropArea.addDockItem(dock1, Location.LocationOnTop);

    var groups = dropArea.groups;
    expect(groups.length, 1);
    var group = groups.first;
    expect(group.geometry.width, length);
    expect(group.geometry.height, length);
    expect(group.geometry.left, 0);
    expect(group.geometry.top, 0);
    expect(group.isVisible, true);
    expect(dropArea.separators.length, 0);

    var dock2 = DockItem(uniqueName: "dock2");
    dropArea.addDockItem(dock2, Location.LocationOnBottom);
    expect(dropArea.separators.length, 1);
    final sep = dropArea.separators.first;
    expect(sep.isVertical, true);
    expect(sep.pos, (length - separatorLength) / 2);

    expect(groups.length, 2);
    groups = dropArea.groups;
    group = groups.first;
    expect(group.geometry.width, length);
    expect(group.geometry.height, (length - separatorLength) / 2);
    expect(group.geometry.left, 0);
    expect(group.geometry.top, 0);
    expect(group.isVisible, true);

    /// test removing
    expect(dropArea.containsDockItem(dock1.uniqueName), true);
    expect(dropArea.removeDockItem(dock1), true);
    expect(dropArea.removeDockItem(dock1), false);
    expect(dropArea.containsDockItem(dock1.uniqueName), false);
    expect(dropArea.groups.length, 1);
    expect(dropArea.separators.length, 0);
  });

  test('group tabbing', () {
    var dropArea = DropArea();
    var dock1 = DockItem(uniqueName: "dock1");
    dropArea.addDockItem(dock1, Location.LocationOnLeft);
    var group = dropArea.groups.first;
    expect(group.numDockWidgets(), 1);
    expect(group.showsTabs(), false);

    var dock2 = DockItem(uniqueName: "dock2");
    group.addDockWidget(dock2);
    expect(group.numDockWidgets(), 2);
    expect(group.currentIndex, 0);
    expect(group.currentDockItem, dock1);

    dock1.title = "title1";
    expect(group.showsTitleBar(), true);
    expect(group.showsTabs(), true);
    expect(group.titlebar.title, group.currentDockItem!.title);
    expect(group.titlebar.title, "title1");
  });

  test('titlebar closebutton', () {
    var dropArea = DropArea();
    var dock1 = DockItem(uniqueName: "dock1");
    dropArea.addDockItem(dock1, Location.LocationOnLeft);
    final group = dropArea.groups.first;
    expect(group.titlebar.isExplicitlyHidden, false);
    group.titlebar.onCloseClicked();
    expect(dropArea.groups.isEmpty, true);
  });
}
