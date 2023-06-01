/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/IndicatorWindow.dart';
import 'package:KDDockWidgets/RubberBand.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
// ignore: undefined_hidden_name
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
    return DropAreaWidget(kddwView, key: widgetKey);
  }
}

class DropAreaWidget extends PositionedWidget {
  DropAreaWidget(var kddwView, {Key? key}) : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return DropAreaPositionedWidgetState(kddwView);
  }
}

class DropAreaPositionedWidgetState extends PositionedWidgetState {
  late final IndicatorWindow indicatorWindow;
  late final RubberBand rubberBand;

  DropAreaPositionedWidgetState(View_mixin kddwView) : super(kddwView) {
    final DropArea da = kddwView.asFlutterView() as DropArea;

    indicatorWindow = KDDWBindingsFlutter.IndicatorWindow.fromCache(
        da.indicatorWindow().thisCpp) as IndicatorWindow;

    rubberBand =
        KDDWBindingsFlutter.View.fromCache(indicatorWindow.rubberBand().thisCpp)
            as RubberBand;
  }

  @override
  Widget buildContents(BuildContext ctx) {
    return Container(
        color: kddwView.m_color,
        child: Stack(
          fit: StackFit.expand,
          children: [
            ...kddwView.visibleChildWidgets(),
            if (rubberBand.isVisible()) rubberBand.flutterWidget
          ],
        ));
  }
}
