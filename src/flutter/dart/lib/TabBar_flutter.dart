/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';

class TabBar_flutter extends KDDockWidgetBindings.TabBar_flutter
    with View_mixin {
  TabBar_flutter(
      KDDockWidgetBindings.TabBar? tabBar, KDDockWidgetBindings.View? parent)
      : super(tabBar, parent: parent) {
    print("TabBar_flutter CTOR");
  }

  Widget createFlutterWidget() {
    return TabBarWidget(kddwView, this, key: widgetKey);
  }
}

class TabBarWidget extends PositionedWidget {
  final TabBar_flutter TabBarView;
  TabBarWidget(var kddwView, this.TabBarView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return TabBarPositionedWidgetState(kddwView, TabBarView);
  }
}

class TabBarPositionedWidgetState extends PositionedWidgetState {
  final TabBar_flutter TabBarView;

  TabBarPositionedWidgetState(var kddwView, this.TabBarView) : super(kddwView);

  @override
  Widget buildContents() {
    return super.buildContents();
  }
}
