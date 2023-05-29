/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB TitleBar company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:flutter/material.dart' hide View;

class IndicatorWindow extends KDDWBindingsFlutter.IndicatorWindow
    with View_mixin {
  IndicatorWindow(
      KDDWBindingsCore.ClassicDropIndicatorOverlay? classicIndicators,
      KDDWBindingsCore.View? parent)
      : super(classicIndicators, parent) {
    m_fillsParent = true;
    initMixin(this, debugName: "IndicatorWindow");
  }

  Widget createFlutterWidget() {
    return IndicatorWindowWidget(this, key: widgetKey);
  }
}

class IndicatorWindowWidget extends PositionedWidget {
  final IndicatorWindow indicatorWindow;
  IndicatorWindowWidget(this.indicatorWindow, {Key? key})
      : super(indicatorWindow, key: key);

  @override
  State<PositionedWidget> createState() {
    return IndicatorWindowWidgetState(indicatorWindow);
  }
}

class IndicatorWindowWidgetState extends PositionedWidgetState {
  final IndicatorWindow indicatorWindow;

  IndicatorWindowWidgetState(this.indicatorWindow) : super(indicatorWindow);

  @override
  Widget buildContents(BuildContext ctx) {
    return Container(color: Color(0xffF6E8EA));
  }
}
