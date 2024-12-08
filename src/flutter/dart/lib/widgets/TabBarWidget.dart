/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/KDDockWidgets.dart';

import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';
import 'package:flutter/material.dart' as material show TabBar;
import 'package:flutter/material.dart' as Geometry show Size;
import 'dart:ui';

class TabBarWidget extends StatefulWidget {
  final Group group;
  TabBarWidget(this.group, {Key? key}) : super(key: key);

  @override
  State<TabBarWidget> createState() {
    return TabBarWidgetState(group);
  }
}

class TabBarWidgetState extends State<TabBarWidget> {
  bool _calledFromFlutter = false;
  final Group group;

  TabBarWidgetState(this.group);

  Widget buildContents(BuildContext ctx) {
    final int numTabs = group.numDockWidgets();
    final tabHeight = 40.0;
    final double tabWidth = 120;

    if (numTabs == 0) return Container();

    final tabs = <Widget>[];
    for (var i = 0; i < numTabs; ++i) {
      final dw = group.dockWidgetAt(i);
      tabs.add(MyTab(
          height: tabHeight,
          child: Text("${dw.title}",
              style: Theme.of(context).textTheme.bodyMedium)));
    }

    final curIndex = group.currentIndex;
    if (curIndex == -1) {
      print("ERROR: Expected curIndex >= 0");
    }

    return Listener(
        onPointerDown: (event) {
          // kddwView.onFlutterMouseEvent(event);
        },
        onPointerUp: (event) {
          // kddwView.onFlutterMouseEvent(event);
        },
        onPointerMove: (event) {
          if (event.buttons != kPrimaryButton) return;
          // kddwView.onFlutterMouseEvent(event);
        },
        child: Align(
          alignment: Alignment.topLeft,
          child: SizedBox(
              height: tabHeight,
              width: tabWidth * numTabs,
              child: DefaultTabController(
                  initialIndex: curIndex == -1 ? 0 : curIndex,
                  length: numTabs,
                  child: Builder(
                    builder: (context) {
                      final TabController controller =
                          DefaultTabController.of(context);
                      controller.addListener(() {
                        if (!controller.indexIsChanging) {
                          _calledFromFlutter = true;
                          group.currentIndex = controller.index;
                          _calledFromFlutter = false;
                        }
                      });

                      return material.TabBar(
                        tabs: tabs,
                        splashBorderRadius: BorderRadius.circular(8),
                        indicatorSize: TabBarIndicatorSize.label,
                      );
                    },
                  ))),
        ));
  }

  @override
  Widget build(BuildContext ctx) {
    return buildContents(ctx);
  }
}

class MyTab extends StatelessWidget implements PreferredSizeWidget {
  MyTab({
    super.key,
    required this.child,
    required this.height,
  });

  final Widget child;
  final double height;
  final isHovering = ValueNotifier(false);

  @override
  Widget build(BuildContext context) {
    return MouseRegion(
      onHover: (event) {
        if (isHovering.value) return;
        isHovering.value = true;
      },
      onExit: (event) {
        if (!isHovering.value) return;
        isHovering.value = false;
      },
      child: ValueListenableBuilder(
        valueListenable: isHovering,
        builder: (context, isHovering, widget) {
          return SizedBox(
            height: height,
            child: isHovering
                ? Stack(
                    children: [
                      Align(
                        child: child,
                      ),
                      Align(
                        alignment: Alignment.centerRight,
                        child: Icon(
                          Icons.open_with,
                          size: 18,
                          color: Theme.of(context)
                              .colorScheme
                              .onSurfaceVariant
                              .withAlpha(100),
                        ),
                      ),
                    ],
                  )
                : Center(
                    widthFactor: 1.5,
                    child: child,
                  ),
          );
        },
      ),
    );
  }

  @override
  Geometry.Size get preferredSize {
    return Geometry.Size.fromHeight(height);
  }
}
