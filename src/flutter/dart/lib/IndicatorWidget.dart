/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgetsBindings/Bindings.dart';
import 'package:flutter/material.dart';

/// Represents a single drop indicator

class IndicatorWidget extends StatefulWidget {
  final int loc;
  IndicatorWidget(this.loc);

  @override
  State<IndicatorWidget> createState() => _IndicatorWidgetState(loc);
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
  String filename() {
    var name = filenameForLocationType(loc);
    if (active) name += "_active";
    return "packages/KDDockWidgets/assets/classic_indicators/${name}.png";
  }

  _IndicatorWidgetState(this.loc);

  @override
  Widget build(BuildContext context) {
    return Positioned(child: Image.asset(filename()));
  }
}
