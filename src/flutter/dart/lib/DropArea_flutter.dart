/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'View_flutter.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';

class DropArea_flutter extends View_flutter {
  DropArea_flutter(KDDockWidgetBindings.Controller? controller, int type,
      KDDockWidgetBindings.View? parent,
      {int windowFlags = 0})
      : super(controller, type, parent, windowFlags: windowFlags) {
    print("DropArea_flutter CTOR");
  }

  Widget createFlutterWidget() {
    return DropAreaWidget(kddwView, this, key: widgetKey);
  }
}

class DropAreaWidget extends PositionedWidget {
  final DropArea_flutter DockWidgetView;
  DropAreaWidget(var kddwView, this.DockWidgetView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return DockWidgetPositionedWidgetState(kddwView, DockWidgetView);
  }
}

class DockWidgetPositionedWidgetState extends PositionedWidgetState {
  final DropArea_flutter DockWidgetView;

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
