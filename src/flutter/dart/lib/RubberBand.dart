/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB company <info@kdab.com>
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
import 'package:flutter/gestures.dart';

import 'package:flutter/material.dart' hide View;

class RubberBand extends KDDWBindingsFlutter.View with View_mixin {
  RubberBand(KDDWBindingsCore.View? parent)
      : super(null, KDDockWidgetBindings.Core_ViewType.RubberBand, parent) {
    initMixin(this, debugName: "RubberBand");
  }

  Widget createFlutterWidget() {
    return RubberBandWidget(this, key: widgetKey);
  }
}

class RubberBandWidget extends PositionedWidget {
  final RubberBand view;
  RubberBandWidget(this.view, {Key? key}) : super(view, key: key);

  @override
  State<PositionedWidget> createState() {
    return RubberBandPositionedWidgetState(view);
  }
}

class RubberBandPositionedWidgetState extends PositionedWidgetState {
  final RubberBand view;

  RubberBandPositionedWidgetState(this.view) : super(view);

  @override
  Widget buildContents(BuildContext ctx) {
    return Container(color: Color(0xffF6E8EA));
  }
}
