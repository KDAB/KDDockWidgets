/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:io';
import 'dart:ui';

import 'package:KDDockWidgets/KDDockWidgets.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:KDDockWidgets/widgets/DropAreaWidget.dart';
import 'package:integration_test/integration_test.dart';
import 'package:kddockwidgets_integration_tests/MyWidget.dart';

import 'package:kddockwidgets_integration_tests/utils.dart';

Future<Finder?> waitForWidget(WidgetTester tester, Key key,
    {int maxTries = 10}) async {
  for (int i = 0; i < maxTries; ++i) {
    final finder = find.byKey(key);
    if (finder.evaluate().isNotEmpty) return finder;
    await tester.pump(const Duration(seconds: 1));
  }

  return null;
}

// Returns true when the widget can't be seen anymore
Future<bool> waitForWidgetToHide(WidgetTester tester, Key key,
    {int maxTries = 10}) async {
  for (int i = 0; i < maxTries; ++i) {
    await tester.pump(const Duration(seconds: 1));
    final finder = find.byKey(key);
    if (finder.evaluate().isEmpty) return true;
  }

  return false;
}

Future<void> pumps(WidgetTester tester, int numPumps) async {
  for (int i = 0; i < numPumps; ++i) {
    await tester.pump(const Duration(seconds: 1));
  }
}

class MyApp extends StatelessWidget {
  final Widget child;
  const MyApp({super.key, required this.child});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
        home: RepaintBoundary(
      key: const Key('boundary'),
      child: Scaffold(
        body: child,
      ),
    ));
  }
}

void main() async {
  testWidgets('Basic test', (WidgetTester tester) async {
    final dock1 = DockItem(uniqueName: "dw1", guestWidget: MyWidget());
    final dock2 = DockItem(uniqueName: "dw2", guestWidget: MyWidget());
    final dock3 = DockItem(uniqueName: "dw3", guestWidget: MyWidget());

    final dock11 = DockItem(uniqueName: "dw11", guestWidget: MyWidget());
    final dock12 = DockItem(uniqueName: "dw12", guestWidget: MyWidget());

    final dropArea = DropArea();
    dropArea.addDockItem(dock1, Location.LocationOnTop);
    dropArea.addDockItem(dock2, Location.LocationOnBottom);
    final group = dropArea.groups.first;
    group.addDockWidget(dock3);
    group.addDockWidget(dock11);
    group.addDockWidget(dock12);

    dropArea.setLayoutSize(700, 700);
    final dropAreaWidget = DropAreaWidget(dropArea);

    // Build the widget tree
    await tester.pumpWidget(MyApp(
      child: dropAreaWidget,
    ));

    await tester.pump();
    await tester.pumpAndSettle();
    await saveScreenShot(tester, prefix: "basic");
  });

  testWidgets('TitleBar close button', (WidgetTester tester) async {
    final dock1 = DockItem(uniqueName: "dw1", guestWidget: MyWidget());
    final dock2 = DockItem(uniqueName: "dw2", guestWidget: MyWidget());

    final dropArea = DropArea();
    dropArea.addDockItem(dock1, Location.LocationOnTop);
    dropArea.addDockItem(dock2, Location.LocationOnBottom);

    dropArea.setLayoutSize(700, 700);
    final dropAreaWidget = DropAreaWidget(dropArea);

    // Build the widget tree
    await tester.pumpWidget(MyApp(
      child: dropAreaWidget,
    ));

    await tester.pump();
    await saveScreenShot(tester, prefix: "titlebar-close-button");

    expect(dropArea.groups.length, 2);
    var topGroup = dropArea.groups.first;
    var bottomGroup = dropArea.groups.last;

    topGroup.titlebar.onCloseClicked();
    expect(dropArea.containsGroup(topGroup), false);
    expect(dropArea.containsGroup(bottomGroup), true);
    expect(dropArea.groups.length, 1);
    expect(dropArea.groups.first, bottomGroup);
    expect(bottomGroup.numDockWidgets(), 1);
    expect(bottomGroup.dockWidgetAt(0), dock2);

    await tester.pumpAndSettle();
    await saveScreenShot(tester, prefix: "titlebar-close-button-2");
  });
}
