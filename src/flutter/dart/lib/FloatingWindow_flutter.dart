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

class FloatingWindow_flutter extends KDDockWidgetBindings.View_flutter
    with View_mixin {
  FloatingWindow_flutter(KDDockWidgetBindings.Controller? controller, int type,
      KDDockWidgetBindings.View? parent,
      {int windowFlags = 0})
      : super(controller, type, parent, windowFlags: windowFlags) {
    initMixin(this, color: Colors.black12, debugName: "FloatingWindow");
    print("FloatingWindow_flutter CTOR");
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
    return super.buildContents();
  }
}
