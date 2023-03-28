/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/DockWidget_flutter.dart';
import 'package:KDDockWidgets/DropArea_flutter.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:flutter/material.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDWBindings;
import 'package:KDDockWidgets/Platform_flutter.dart' as KDDW;
import 'package:KDDockWidgets/View_flutter.dart' as KDDW;
import 'package:KDDockWidgets/WindowOverlayWidget.dart' as KDDW;
import 'package:flutter/scheduler.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Flutter Demos',
      theme: ThemeData(
        primarySwatch: Colors.blue,
      ),
      home: const MyHomePage(title: 'Flutter Demo Home Page'),
    );
  }
}

class MyHomePage extends StatefulWidget {
  const MyHomePage({Key? key, required this.title}) : super(key: key);

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late KDDWBindings.DropArea dropArea;
  late Widget dropAreaWidget;

  _MyHomePageState() {
    KDDW.Platform_flutter();
    dropArea = KDDWBindings.DropArea(null,
        KDDWBindings.KDDockWidgets_MainWindowOption.MainWindowOption_None);

    final dropAreaView =
        KDDWBindings.View_flutter.fromCache(dropArea.view().thisCpp)
            as KDDW.View_flutter;

    KDDW.View_flutter.fromCppPointer(dropArea.view().thisCpp);
    dropAreaView.setObjectName("droparea");

    dropAreaView.m_fillsParent = true;
    dropAreaWidget = dropAreaView.flutterWidget;

    final group1 = KDDWBindings.Group(parent: null);
    final group2 = KDDWBindings.Group(parent: null);
    final group3 = KDDWBindings.Group(parent: null);

    dropArea.addWidget(
        group1.view(), KDDWBindings.KDDockWidgets_Location.Location_OnLeft,
        relativeTo: null, option: KDDWBindings.InitialOption());

    dropArea.addWidget(
        group2.view(), KDDWBindings.KDDockWidgets_Location.Location_OnRight,
        relativeTo: null, option: KDDWBindings.InitialOption());

    dropArea.addWidget(
        group3.view(), KDDWBindings.KDDockWidgets_Location.Location_OnBottom,
        relativeTo: null, option: KDDWBindings.InitialOption());

    final dw1 = DockWidget_flutter("dw1");
    final dw2 = DockWidget_flutter("dw2");
    final dw3 = DockWidget_flutter("dw3");
    dw3.dockWidget().setFloating(true);
    dw3.dockWidget().open();

    dropArea.addDockWidget(dw1.dockWidget(),
        KDDWBindings.KDDockWidgets_Location.Location_OnRight, null,
        initialOption: KDDWBindings.InitialOption());

    // dw1.dockWidget().addDockWidgetAsTab(dw2.dockWidget(),
    //     initialOption: KDDWBindings.InitialOption());
  }

  void _incrementCounter() {
    dropArea.dumpLayout();
    print("Layout out equally");
    dropArea.layoutEqually();
    print("Layout out equally done");
    dropArea.dumpLayout();
  }

  @override
  Widget build(BuildContext context) {
    final windowOverlay = KDDW.WindowOverlayWidget();

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(child: Stack(children: [dropAreaWidget, windowOverlay])),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}
