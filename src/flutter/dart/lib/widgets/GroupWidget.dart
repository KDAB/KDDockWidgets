/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/KDDockWidgets.dart';
import 'package:KDDockWidgets/widgets/PositionedWidget.dart';
import 'package:KDDockWidgets/widgets/TabBarWidget.dart';
import 'package:KDDockWidgets/widgets/TitleBarWidget.dart';
import 'package:KDDockWidgets/widgets/DockWidget.dart';

import 'package:flutter/material.dart';

class GroupWidget extends PositionedWidget {
  final Group group;
  GroupWidget(this.group, {Key? key}) : super(group, key: key);

  @override
  State<PositionedWidget> createState() {
    return GroupWidgetState(group);
  }
}

class GroupWidgetState extends PositionedWidgetState {
  final Group group;
  GroupWidgetState(this.group) : super(group) {
    group.changed.connect(() {
      setState(() {});
    });

    group.titleChanged.connect(() {
      setState(() {});
    });
  }

  @override
  Widget buildContents(BuildContext ctx) {
    final titleBarWidget = TitleBarWidget(group.titlebar);
    final tabBarWidget = TabBarWidget(group);
    final dockItem = group.currentDockItem;
    final dockWidget = dockItem == null
        ? Container(color: Colors.black)
        : DockWidget(dockItem);

    return Column(
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [
        if (group.showsTitleBar()) titleBarWidget,
        if (group.showsTabs()) tabBarWidget,
        Expanded(child: dockWidget)
      ],
    );
  }
}
