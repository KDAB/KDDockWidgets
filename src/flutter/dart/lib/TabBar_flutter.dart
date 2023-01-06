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

class TabBar_flutter extends KDDockWidgetBindings.TabBar_flutter
    with View_mixin {
  late final KDDockWidgetBindings.TabBar m_controller;

  TabBar_flutter(
      KDDockWidgetBindings.TabBar? tabBar, KDDockWidgetBindings.View? parent)
      : super(tabBar, parent: parent) {
    m_fillsParent = true;
    m_controller = tabBar!;
    initMixin(this);
    print("TabBar_flutter CTOR");
  }

  Widget createFlutterWidget() {
    return TabBarWidget(kddwView, this, key: widgetKey);
  }

  @override
  onRebuildRequested() {
    print("TabBar_flutter: onRebuildRequested");
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
  final TabBar_flutter m_tabBarView;

  TabBarPositionedWidgetState(var kddwView, this.m_tabBarView)
      : super(kddwView);

  @override
  Widget buildContents() {
    final int numTabs = m_tabBarView.m_controller.numDockWidgets();
    var tabs = <Tab>[];
    for (var i = 0; i < numTabs; ++i) {
      tabs.add(Tab(text: "test"));
    }

    return SizedBox(
        height: 50,
        child: DefaultTabController(
          length: numTabs,
          child: TabBar(tabs: tabs),
        ));
  }
}
