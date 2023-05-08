/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/DropArea.dart';
import 'package:flutter/material.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;

class MainWindow extends KDDWBindingsFlutter.MainWindow with View_mixin {
  late final KDDWBindingsCore.MainWindow m_controller;

  MainWindow(String? uniqueName,
      {int options = 0,
      required KDDWBindingsFlutter.View? parent,
      int flags = 0})
      : super(uniqueName, options: options, parent: parent, flags: flags) {
    m_controller =
        KDDWBindingsCore.MainWindow.fromCppPointer(controller().thisCpp);
    initMixin(this, color: Colors.black12, debugName: "MainWindow");
  }

  Widget createFlutterWidget() {
    return MainWindowWidget(m_controller, key: widgetKey);
  }
}

class MainWindowWidget extends StatefulWidget {
  late final KDDWBindingsCore.MainWindow kddwController;

  MainWindowWidget(this.kddwController, {Key? key});

  @override
  State<MainWindowWidget> createState() {
    return MainWindowWidgetState(kddwController);
  }
}

class MainWindowWidgetState extends State<MainWindowWidget> {
  late final KDDWBindingsCore.MainWindow kddwController;
  MainWindowWidgetState(this.kddwController);

  Widget dropAreaWidget() {
    final dropAreaView = KDDWBindingsFlutter.View.fromCache(
        kddwController.dropArea().view().thisCpp) as DropArea;

    return dropAreaView.flutterWidget;
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.black,
      child: dropAreaWidget(),
    );
  }
}
