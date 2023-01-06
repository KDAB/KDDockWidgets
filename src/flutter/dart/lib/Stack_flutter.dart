/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';

class Stack_flutter extends KDDockWidgetBindings.Stack_flutter with View_mixin {
  Stack_flutter(
      KDDockWidgetBindings.Stack? stack, KDDockWidgetBindings.View? parent)
      : super(stack, parent: parent) {
    print("Stack_flutter CTOR");
  }

  Widget createFlutterWidget() {
    return StackWidget(kddwView, this, key: widgetKey);
  }
}

class StackWidget extends PositionedWidget {
  final Stack_flutter StackView;
  StackWidget(var kddwView, this.StackView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return StackPositionedWidgetState(kddwView, StackView);
  }
}

class StackPositionedWidgetState extends PositionedWidgetState {
  final Stack_flutter StackView;

  StackPositionedWidgetState(var kddwView, this.StackView) : super(kddwView);

  @override
  Widget buildContents() {
    return super.buildContents();
  }
}
