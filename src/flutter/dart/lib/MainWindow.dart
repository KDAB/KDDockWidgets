/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/DropArea.dart';
import 'package:flutter/material.dart' hide View;
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;

import 'PositionedWidget.dart';

class MainWindow extends KDDWBindingsFlutter.MainWindow with View_mixin {
  late final KDDWBindingsCore.MainWindow m_controller;

  MainWindow(String? uniqueName,
      {int options = 0,
      required KDDWBindingsFlutter.View? parent,
      int flags = 0})
      : super(uniqueName, options: options, parent: parent, flags: flags) {
    m_controller =
        KDDWBindingsCore.MainWindow.fromCppPointer(controller().thisCpp);
    m_fillsParent = true;
    initMixin(this, debugName: "MainWindow");
    m_controller.init(uniqueName);
  }

  Widget createFlutterWidget() {
    return MainWindowWidget(m_controller, this, key: widgetKey);
  }
}

class MainWindowWidget extends PositionedWidget {
  final MainWindow view;
  late final KDDWBindingsCore.MainWindow kddwController;

  MainWindowWidget(this.kddwController, this.view, {Key? key})
      : super(view, key: key);

  @override
  State<PositionedWidget> createState() {
    return MainWindowWidgetState(kddwController, view);
  }
}

class MainWindowWidgetState extends PositionedWidgetState {
  final MainWindow view;
  late final KDDWBindingsCore.MainWindow kddwController;
  MainWindowWidgetState(this.kddwController, this.view) : super(view);

  Widget dropAreaWidget() {
    final dropAreaView = KDDWBindingsFlutter.View.fromCache(
        kddwController.dropArea().view().thisCpp) as DropArea;

    return dropAreaView.flutterWidget;
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      child: dropAreaWidget(),
    );
  }
}
