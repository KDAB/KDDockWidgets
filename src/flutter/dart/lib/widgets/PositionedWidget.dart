/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/models/GeometryItem.dart';
import 'package:flutter/material.dart';

/// A widget that supports being positioned. It's child of a Stack widget.
class PositionedWidget extends StatefulWidget {
  final GeometryItem geometryItem;

  PositionedWidget(this.geometryItem, {Key? key}) : super(key: key);

  @override
  State<PositionedWidget> createState() {
    return PositionedWidgetState(geometryItem);
  }
}

class PositionedWidgetState extends State<PositionedWidget> {
  final GeometryItem geometryItem;
  PositionedWidgetState(this.geometryItem);

  /// Called when the KDDW View changes size. Rebuilds the flutter Widget.
  void updatePosition() {
    _updateState();
  }

  /// Called when the KDDW View changes size. Rebuilds the flutter Widget.
  void updateSize() {
    _updateState();
  }

  void _updateState() {
    // print("_updateState $this");
    setState(() {});
  }

  void rebuildRequested() {
    _updateState();
  }

  /// This is factored-out from build() so derived classes can return something else
  Widget buildContents(BuildContext ctx) {
    return Container(color: Colors.blue);
  }

  @override
  Widget build(BuildContext ctx) {
    final container = buildContents(ctx);
    final geo = geometryItem.geometry;

    return Positioned(
        width: geo.width * 1.0,
        height: geo.height * 1.0,
        top: geo.top * 1.0,
        left: geo.left * 1.0,
        child: container);
  }
}
