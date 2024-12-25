/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/KDDockWidgets.dart';
import 'package:KDDockWidgets/widgets/DropAreaWidget.dart';
import 'package:KDDockWidgets/widgets/PositionedWidget.dart';
import 'package:KDDockWidgets/widgets/TabBarWidget.dart';
import 'package:KDDockWidgets/widgets/TitleBarWidget.dart';
import 'package:KDDockWidgets/widgets/DockWidget.dart';

import 'package:flutter/material.dart';

class FloatingWidget extends StatefulWidget {
  final FloatingItem floatingItem;
  FloatingWidget(this.floatingItem, {Key? key}) : super(key: key);

  @override
  State<FloatingWidget> createState() {
    return FloatingWidgetState(floatingItem);
  }
}

class FloatingWidgetState extends State<FloatingWidget> {
  final FloatingItem floatingItem;
  FloatingWidgetState(this.floatingItem) {}

  Widget buildContents(BuildContext ctx) {
    final titleBarWidget = TitleBarWidget(floatingItem.titleBar);
    final dropAreaWidget = DropAreaWidget(floatingItem.dropArea);

    return Column(
      crossAxisAlignment: CrossAxisAlignment.stretch,
      children: [
        if (floatingItem.showsTitleBar()) titleBarWidget,
        Expanded(child: dropAreaWidget)
      ],
    );
  }

  @override
  Widget build(BuildContext context) {
    return buildContents(context);
  }
}
