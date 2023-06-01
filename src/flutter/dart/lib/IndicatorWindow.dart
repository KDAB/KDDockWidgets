/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/IndicatorWidget.dart';
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
    return IndicatorWindowWidget(this, widgetKey);
  }

  @override
  void updatePositions_flutter(int overlayWidth, int overlayHeight,
      KDDWBindingsCore.Group? hoveredGroup) {
    final state = widgetState<IndicatorWindowWidgetState>();
    state?.updatePositions(overlayWidth, overlayHeight, hoveredGroup);
  }

  @override
  int hover_flutter(QPoint pt) {
    return 0;
  }
}

class IndicatorWindowWidget extends PositionedWidget {
  final IndicatorWindow indicatorWindow;
  IndicatorWindowWidget(this.indicatorWindow, Key key)
      : super(indicatorWindow, key: key);

  @override
  State<PositionedWidget> createState() {
    return IndicatorWindowWidgetState(indicatorWindow);
  }
}

class IndicatorWindowWidgetState extends PositionedWidgetState {
  final IndicatorWindow indicatorWindow;
  final List<IndicatorWidget> indicatorWidgets = [];
  final List<int> locations = [
    KDDockWidgets_DropLocation.DropLocation_Left,
    KDDockWidgets_DropLocation.DropLocation_Top,
    KDDockWidgets_DropLocation.DropLocation_Right,
    KDDockWidgets_DropLocation.DropLocation_Bottom,
    KDDockWidgets_DropLocation.DropLocation_Center,
    KDDockWidgets_DropLocation.DropLocation_OutterLeft,
    KDDockWidgets_DropLocation.DropLocation_OutterTop,
    KDDockWidgets_DropLocation.DropLocation_OutterRight,
    KDDockWidgets_DropLocation.DropLocation_OutterBottom
  ];

  IndicatorWindowWidgetState(this.indicatorWindow) : super(indicatorWindow) {
    for (var loc in locations) {
      indicatorWidgets.add(IndicatorWidget(indicatorWindow, loc));
    }
  }

  @override
  Widget buildContents(BuildContext ctx) {
    return Container(
      color: Color.fromARGB(120, 246, 232, 234),
      child: Stack(
        children: indicatorWidgets,
      ),
    );
  }

  void updatePositions(int overlayWidth, int overlayHeight,
      KDDWBindingsCore.Group? hoveredGroup) {
    for (var widget in indicatorWidgets)
      widget.updatePosition(overlayWidth, overlayHeight, hoveredGroup);
  }
}
