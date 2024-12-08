/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:developer';
import 'package:KDDockWidgets/KDDockWidgets.dart';

import 'package:KDDockWidgets/widgets/DockWidget.dart';
import 'package:KDDockWidgets/widgets/GroupWidget.dart';
import 'package:KDDockWidgets/widgets/DropAreaWidget.dart';

import 'package:flutter/material.dart';
// import 'package:KDDockWidgets/WindowOverlayWidget.dart' as KDDW;
// import 'package:KDDockWidgets/Platform.dart' as KDDW;
// import 'package:KDDockWidgets/LibraryLoader.dart' as KDDW;
import 'package:kddockwidgets_flutter_example/MyMenuBar.dart';
import 'package:kddockwidgets_flutter_example/MyWidget.dart';

void main(List<String> args) {
  // Just for debug
  if (args.contains("--wait")) debugger();

  // Needs to be called before using, so it loads the C++ library
  // KDDW.initLibraryLoader();

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
  final String title;

  const MyHomePage({required this.title, Key? key}) : super(key: key);

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  // late KDDWBindingsCore.DropArea dropArea;
  // late MainWindow mainWindow;

  final DropArea dropArea = DropArea();

  _MyHomePageState() {
    // final windowOverlay = KDDW.WindowOverlayWidget();
    final dock1 = DockItem(uniqueName: "dw1", guestWidget: MyWidget());
    final dock2 = DockItem(uniqueName: "dw2", guestWidget: MyWidget());
    final dock3 = DockItem(uniqueName: "dw3", guestWidget: MyWidget());

    final dock11 = DockItem(uniqueName: "dw11", guestWidget: MyWidget());
    final dock12 = DockItem(uniqueName: "dw12", guestWidget: MyWidget());
    final dock13 = DockItem(uniqueName: "dw13", guestWidget: MyWidget());

    dropArea.addDockItem(dock1, Location.LocationOnTop);
    dropArea.addDockItem(dock2, Location.LocationOnBottom);

    dropArea.groups.first.addDockWidget(dock3);
    dropArea.groups.first.addDockWidget(dock11);
    dropArea.groups.first.addDockWidget(dock12);
    dropArea.groups.first.addDockWidget(dock13);
  }

  void _incrementCounter() {}

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      // body: Column(children: [
      //   const MyMenuBar(),
      //   Expanded(
      //       child: Stack(children: [mainWindow.flutterWidget, windowOverlay]))
      // ]),
      body: DropAreaWidget(dropArea),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}
