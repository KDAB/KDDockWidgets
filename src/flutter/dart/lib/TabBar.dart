/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart' hide View;
import 'package:flutter/material.dart' as material show TabBar;

class TabBar extends KDDWBindingsFlutter.TabBar with View_mixin {
  late final KDDWBindingsCore.TabBar m_controller;

  TabBar(KDDWBindingsCore.TabBar? tabBar, KDDWBindingsCore.View? parent)
      : super(tabBar, parent: parent) {
    m_fillsParent = true;
    m_controller = tabBar!;
    initMixin(this);
  }

  Widget createFlutterWidget() {
    return TabBarWidget(kddwView, this, key: widgetKey);
  }

  @override
  onRebuildRequested() {
    // print("TabBar: onRebuildRequested");
  }
}

class TabBarWidget extends PositionedWidget {
  final TabBar TabBarView;
  TabBarWidget(var kddwView, this.TabBarView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return TabBarPositionedWidgetState(kddwView, TabBarView);
  }
}

class TabBarPositionedWidgetState extends PositionedWidgetState {
  final TabBar m_tabBarView;

  TabBarPositionedWidgetState(var kddwView, this.m_tabBarView)
      : super(kddwView);

  @override
  Widget buildContents() {
    final int numTabs = m_tabBarView.m_controller.numDockWidgets();
    final tabs = <Widget>[];
    for (var i = 0; i < numTabs; ++i) {
      final dw = m_tabBarView.m_controller.dockWidgetAt_2(i);
      tabs.add(Tab(text: "${dw.title().toDartString()}"));
    }

    return Listener(
        onPointerDown: (event) {
          kddwView.onFlutterMouseEvent(event);
        },
        onPointerUp: (event) {
          kddwView.onFlutterMouseEvent(event);
        },
        onPointerMove: (event) {
          if (event.buttons != kPrimaryButton) return;
          kddwView.onFlutterMouseEvent(event);
        },
        child: SizedBox(
            height: 50,
            child: DefaultTabController(
              length: numTabs,
              child: material.TabBar(
                tabs: tabs,
                labelColor: Colors.black,
              ),
            )));
  }
}
