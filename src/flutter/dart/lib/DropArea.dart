/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'View.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:flutter/material.dart' hide View;

class DropArea extends KDDWBindingsFlutter.DropArea with View_mixin {
  DropArea(KDDWBindingsCore.DropArea? controller, int type,
      KDDWBindingsCore.View? parent,
      {int windowFlags = 0})
      : super(controller, parent) {
    m_fillsParent = true;
    initMixin(this, debugName: "DropArea");
  }

  Widget createFlutterWidget() {
    return DropAreaWidget(kddwView, this, key: widgetKey);
  }
}

class DropAreaWidget extends PositionedWidget {
  final DropArea DockWidgetView;
  DropAreaWidget(var kddwView, this.DockWidgetView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return DropAreaPositionedWidgetState(kddwView, DockWidgetView);
  }
}

class DropAreaPositionedWidgetState extends PositionedWidgetState {
  final DropArea DockWidgetView;

  DropAreaPositionedWidgetState(var kddwView, this.DockWidgetView)
      : super(kddwView);

  @override
  Widget buildContents(BuildContext ctx) {
    return Container(
        color: kddwView.m_color,
        child: Stack(
          children: kddwView.visibleChildWidgets(),
        ));
  }
}
