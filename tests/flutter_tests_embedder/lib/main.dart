/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:async';
import 'dart:ui';
import 'dart:developer';

import 'package:flutter/material.dart' hide View;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:KDDockWidgets/WindowOverlayWidget.dart' as KDDW;
import 'package:flutter/scheduler.dart';
import 'package:KDDockWidgets/View.dart' as KDDW;
import 'package:KDDockWidgets/Platform.dart' as KDDW;
import 'package:KDDockWidgets/LibraryLoader.dart' as KDDW;
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDWBindings;

void main(List<String> args) {
  window.setIsolateDebugName("Main dart isolate");

  if (args.contains("--wait")) debugger();

  // Needs to be called before using, so it loads the C++ library
  KDDW.initLibraryLoader();

  runApp(const MyApp());

  var plat = KDDW.Platform();
  plat.runTests();
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
  _MyHomePageState();

  void _incrementCounter() {}

  @override
  Widget build(BuildContext context) {
    final windowOverlay = KDDW.WindowOverlayWidget(supportsMainWindow: true);

    return Scaffold(
      appBar: AppBar(
        title: Text(widget.title),
      ),
      body: Center(child: Stack(children: [windowOverlay])),
      floatingActionButton: FloatingActionButton(
        onPressed: _incrementCounter,
        tooltip: 'Increment',
        child: const Icon(Icons.add),
      ),
    );
  }
}
