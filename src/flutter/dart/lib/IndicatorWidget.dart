/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings.dart';
import 'package:flutter/material.dart';
import 'dart:ffi' as ffi;
import 'IndicatorWindow.dart';

/// Represents a single drop indicator

class IndicatorWidget extends StatefulWidget {
  final int loc;
  final IndicatorWindow indicatorWindow;
  IndicatorWidget(this.indicatorWindow, this.loc)
      : super(key: indicatorKey(indicatorWindow, loc)) {}

  static GlobalObjectKey indicatorKey(
      IndicatorWindow indicatorWindow, int loc) {
    final ffi.Pointer<ffi.Void> ptr =
        indicatorWindow.kddwView.thisCpp.cast<ffi.Void>();

    return GlobalObjectKey("${ptr.address}-${loc}");
  }

  @override
  State<IndicatorWidget> createState() => _IndicatorWidgetState(loc);

  _IndicatorWidgetState? widgetState() {
    final globalKey = key as GlobalObjectKey;
    return globalKey.currentState as _IndicatorWidgetState?;
  }

  int hover(Offset pt) {
    return widgetState()?.hover(pt) ??
        KDDockWidgets_DropLocation.DropLocation_None;
  }

  void updatePosition(int overlayWidth, int overlayHeight,
      KDDWBindingsCore.Group? hoveredGroup) {
    final globalKey = key as GlobalObjectKey;
    final state = widgetState();

    if (state == null) {
      print("Null state for key $globalKey");
    } else {
      state.updatePosition(overlayWidth, overlayHeight, hoveredGroup);
    }
  }
}

String filenameForLocationType(int loc) {
  switch (loc) {
    case KDDockWidgets_DropLocation.DropLocation_Left:
      return "inner_left";
    case KDDockWidgets_DropLocation.DropLocation_Top:
      return "inner_top";
    case KDDockWidgets_DropLocation.DropLocation_Right:
      return "inner_right";
    case KDDockWidgets_DropLocation.DropLocation_Bottom:
      return "inner_bottom";
    case KDDockWidgets_DropLocation.DropLocation_Center:
      return "center";
    case KDDockWidgets_DropLocation.DropLocation_OutterLeft:
      return "outter_left";
    case KDDockWidgets_DropLocation.DropLocation_OutterTop:
      return "outter_top";
    case KDDockWidgets_DropLocation.DropLocation_OutterRight:
      return "outter_right";
    case KDDockWidgets_DropLocation.DropLocation_OutterBottom:
      return "outter_bottom";
  }
  return "";
}

class _IndicatorWidgetState extends State<IndicatorWidget> {
  final int loc;
  bool active = false;
  double x = 0;
  double y = 0;
  final length = 50.0;
  get halfLength => length / 2;

  String filename() {
    var name = filenameForLocationType(loc);
    if (active) name += "_active";
    return "packages/KDDockWidgets/assets/classic_indicators/${name}.png";
  }

  _IndicatorWidgetState(this.loc);

  @override
  Widget build(BuildContext context) {
    return Positioned(
        left: x,
        top: y,
        width: length,
        height: length,
        child: Image.asset(filename()));
  }

  Offset _positionForInnerLocation(KDDWBindingsCore.Group? hoveredGroup) {
    if (hoveredGroup == null) return Offset.zero;

    QRect groupGeo = hoveredGroup.geometry();
    var x = groupGeo.x().toDouble();
    var y = groupGeo.y().toDouble();
    var width = groupGeo.width().toDouble();
    var height = groupGeo.height().toDouble();

    final spacing = 10.0;
    final center =
        Offset(x + width / 2 - halfLength, y + height / 2 - halfLength);

    switch (loc) {
      case KDDockWidgets_DropLocation.DropLocation_Left:
        return center + Offset(-length - spacing, 0);
      case KDDockWidgets_DropLocation.DropLocation_Top:
        return center + Offset(0, -length - spacing);
      case KDDockWidgets_DropLocation.DropLocation_Right:
        return center + Offset(length + spacing, 0);
      case KDDockWidgets_DropLocation.DropLocation_Bottom:
        return center + Offset(0, length + spacing);

      case KDDockWidgets_DropLocation.DropLocation_Center:
        return center;
    }

    return Offset.zero;
  }

  Offset _positionForLocation(double overlayWidth, double overlayHeight,
      KDDWBindingsCore.Group? hoveredGroup) {
    switch (loc) {
      case KDDockWidgets_DropLocation.DropLocation_Left:
      case KDDockWidgets_DropLocation.DropLocation_Top:
      case KDDockWidgets_DropLocation.DropLocation_Right:
      case KDDockWidgets_DropLocation.DropLocation_Bottom:
      case KDDockWidgets_DropLocation.DropLocation_Center:
        return _positionForInnerLocation(hoveredGroup);
      case KDDockWidgets_DropLocation.DropLocation_OutterLeft:
        return Offset(halfLength, overlayHeight / 2 - halfLength);
      case KDDockWidgets_DropLocation.DropLocation_OutterTop:
        return Offset(overlayWidth / 2 - halfLength, halfLength);
      case KDDockWidgets_DropLocation.DropLocation_OutterRight:
        return Offset(
            overlayWidth - 3 * halfLength, overlayHeight / 2 - halfLength);
      case KDDockWidgets_DropLocation.DropLocation_OutterBottom:
        return Offset(
            overlayWidth / 2 - halfLength, overlayHeight - 3 * halfLength);
    }
    return Offset(0, 0);
  }

  /// Returns this indicator's rect, in coordinates of parent (i.e. drop indicator overlay coordinates)
  Rect geometry() {
    return Rect.fromLTWH(x, y, length, length);
  }

  int hover(Offset pt) {
    if (geometry().contains(pt)) return loc;
    return KDDockWidgets_DropLocation.DropLocation_None;
  }

  void updatePosition(int overlayWidth, int overlayHeight,
      KDDWBindingsCore.Group? hoveredGroup) {
    final newPos = _positionForLocation(
        overlayWidth.toDouble(), overlayHeight.toDouble(), hoveredGroup);
    if (newPos != Offset(x, y)) {
      setState(() {
        x = newPos.dx;
        y = newPos.dy;
      });
    }
  }
}
