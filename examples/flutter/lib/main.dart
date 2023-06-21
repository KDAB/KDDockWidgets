/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:developer';
import 'package:KDDockWidgets/DockWidget.dart';
import 'package:KDDockWidgets/MainWindow.dart';
import 'package:flutter/material.dart' hide View;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgets/WindowOverlayWidget.dart' as KDDW;
import 'package:KDDockWidgets/Platform.dart' as KDDW;
import 'package:KDDockWidgets/LibraryLoader.dart' as KDDW;
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDWBindings;
import 'package:kddockwidgets_flutter_example/MyMenuBar.dart';
import 'package:kddockwidgets_flutter_example/MyWidget.dart';

void main(List<String> args) {
  // Just for debug
  if (args.contains("--wait")) debugger();

  // Needs to be called before using, so it loads the C++ library
  KDDW.initLibraryLoader();

  runApp(const MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'KDDockWidgets minimal example',
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
  late KDDWBindingsCore.DropArea dropArea;
  late MainWindow mainWindow;

  _MyHomePageState() {
    KDDW.Platform();

    mainWindow = MainWindow("MyMainWindow", parent: null);

    final dw1 = DockWidget("dw1");
    final dw2 = DockWidget("dw2");
    final dw3 = DockWidget("dw3");
    final dw4 = DockWidget("dw4");
    final dw5 = DockWidget("dw5");
    final dw6 = DockWidget("dw6");

    dw1.setGuestWidget(MyWidget());
    dw2.setGuestWidget(MyWidget());
    dw3.setGuestWidget(MyWidget());
    dw4.setGuestWidget(MyWidget());
    dw5.setGuestWidget(MyWidget());
    dw6.setGuestWidget(MyWidget());

    mainWindow.asMainWindowController().addDockWidget(
        dw1.asDockWidgetController(),
        KDDWBindings.KDDockWidgets_Location.Location_OnLeft,
        relativeTo: null,
        initialOption: KDDWBindings.InitialOption());

    mainWindow.asMainWindowController().addDockWidget(
        dw2.asDockWidgetController(),
        KDDWBindings.KDDockWidgets_Location.Location_OnRight,
        relativeTo: null,
        initialOption: KDDWBindings.InitialOption());

    mainWindow.asMainWindowController().addDockWidget(
        dw3.asDockWidgetController(),
        KDDWBindings.KDDockWidgets_Location.Location_OnBottom,
        relativeTo: null,
        initialOption: KDDWBindings.InitialOption());

    dw2.asDockWidgetController().addDockWidgetAsTab(
        dw5.asDockWidgetController(),
        initialOption: KDDWBindings.InitialOption());

    dw2.asDockWidgetController().addDockWidgetAsTab(
        dw6.asDockWidgetController(),
        initialOption: KDDWBindings.InitialOption());

    dw4.show();

    mainWindow.show();
  }

  void _incrementCounter() {}

  @override
  Widget build(BuildContext context) {
    final windowOverlay = KDDW.WindowOverlayWidget();

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Column(children: [
        const MyMenuBar(),
        Expanded(
            child: Stack(children: [mainWindow.flutterWidget, windowOverlay]))
      ]),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}
