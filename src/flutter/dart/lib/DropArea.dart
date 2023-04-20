/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'View.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';

class DropArea extends View {
  DropArea(KDDockWidgetBindings.Controller? controller, int type,
      KDDockWidgetBindings.View? parent,
      {int windowFlags = 0})
      : super(controller, type, parent, windowFlags: windowFlags) {
    print("DropArea CTOR");
    m_fillsParent = true;
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
    return DockWidgetPositionedWidgetState(kddwView, DockWidgetView);
  }
}

class DockWidgetPositionedWidgetState extends PositionedWidgetState {
  final DropArea DockWidgetView;

  DockWidgetPositionedWidgetState(var kddwView, this.DockWidgetView)
      : super(kddwView);

  @override
  Widget buildContents() {
    return Container(
        color: kddwView.m_color,
        child: Stack(
          children: kddwView.childWidgets,
        ));
  }
}
