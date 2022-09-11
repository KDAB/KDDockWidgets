/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';
import 'TitleBar_flutter.dart';
import 'DropArea_flutter.dart';

class FloatingWindow_flutter extends KDDockWidgetBindings.View_flutter
    with View_mixin {
  late final KDDockWidgetBindings.FloatingWindow m_controller;

  FloatingWindow_flutter(KDDockWidgetBindings.Controller? controller,
      KDDockWidgetBindings.View? parent, {int windowFlags = 0})
      : super(controller,
            KDDockWidgetBindings.KDDockWidgets_Type.FloatingWindow, parent,
            windowFlags: windowFlags) {
    m_controller = controller! as KDDockWidgetBindings.FloatingWindow;
    m_fillsParent = true;

    initMixin(this, color: Colors.black12, debugName: "FloatingWindow");
    print("FloatingWindow_flutter CTOR");
  }

  TitleBar_flutter titleBarView() {
    return KDDockWidgetBindings.View_flutter.fromCache(
        m_controller.titleBar().view().thisCpp) as TitleBar_flutter;
  }

  DropArea_flutter dropAreaView() {
    return KDDockWidgetBindings.View_flutter.fromCache(
        m_controller.dropArea().view().thisCpp) as DropArea_flutter;
  }

  Widget createFlutterWidget() {
    return FloatingWindowWidget(kddwView, this, key: widgetKey);
  }
}

class FloatingWindowWidget extends PositionedWidget {
  final FloatingWindow_flutter view;
  FloatingWindowWidget(var kddwView, this.view, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return FloatingWindowPositionedWidgetState(kddwView, view);
  }
}

class FloatingWindowPositionedWidgetState extends PositionedWidgetState {
  final FloatingWindow_flutter view;

  FloatingWindowPositionedWidgetState(var kddwView, this.view)
      : super(kddwView);

  @override
  Widget buildContents() {
    final titleBarWidget = view.titleBarView().flutterWidget;
    final dropAreaWidget = view.dropAreaView().flutterWidget;

    return Column(children: [titleBarWidget, Expanded(child: dropAreaWidget)]);
  }
}
