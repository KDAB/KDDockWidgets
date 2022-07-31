/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_flutter.dart';
import 'package:flutter/material.dart';

class PositionedWidget extends StatefulWidget {
  final View_flutter kddwView;

  const PositionedWidget(this.kddwView, {Key? key}) : super(key: key);

  @override
  State<PositionedWidget> createState() => _PositionedWidgetState(kddwView);
}

class _PositionedWidgetState extends State<PositionedWidget> {
  final View_flutter kddwView;
  int x = 100;
  int y = 100;
  int width = 400;
  int height = 400;

  var childWidgets = <PositionedWidget>[];

  _PositionedWidgetState(this.kddwView) {
    kddwView.updatePositionCallback = updatePosition;
    kddwView.updateSizeCallback = updateSize;
  }

  void updatePosition(int kddwX, int kddwY) {
    final int kddwX = kddwView.x();
    final int kddwY = kddwView.y();
    setState(() {
      this.x = kddwX;
      this.y = kddwY;
    });
  }

  void updateSize(int kddwWidth, int kddwHeight) {
    setState(() {
      height = kddwHeight;
      width = kddwWidth;
    });
  }

  @override
  Widget build(BuildContext context) {
    return Positioned(
        height: height * 1.0,
        width: width * 1.0,
        top: y * 1.0,
        left: x * 1.0,
        child: Container(
            color: Colors.red,
            child: Stack(
              children: childWidgets,
            )));
  }
}
