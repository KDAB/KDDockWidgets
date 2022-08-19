/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:flutter/material.dart';

class PositionedWidget extends StatefulWidget {
  final View_mixin kddwView;

  const PositionedWidget(this.kddwView, {Key? key}) : super(key: key);

  @override
  State<PositionedWidget> createState() {
    return PositionedWidgetState(kddwView);
  }
}

class PositionedWidgetState extends State<PositionedWidget>
    with WidgetsBindingObserver {
  final View_mixin kddwView;
  int x = 0;
  int y = 0;
  int width = 400;
  int height = 400;
  final bool _fillsParent;

  PositionedWidgetState(this.kddwView) : _fillsParent = kddwView.m_fillsParent {
    x = kddwView.m_x;
    y = kddwView.m_y;
    width = kddwView.m_width;
    height = kddwView.m_height;

    // print("Creating PositionedWidgetState  width=${width}");
  }

  @override
  void initState() {
    WidgetsBinding.instance.addObserver(this);
    super.initState();
    // print("PositionedWidgetState::initState: width=${width}");
  }

  @override
  void dispose() {
    WidgetsBinding.instance.removeObserver(this);
    super.dispose();
  }

  @override
  void didChangeMetrics() {
    // Whenever the window resizes we rebuild
    if (_fillsParent) {
      // setState(() {});
      resizeKDDWLayout();
    }
  }

  void childrenChanged() {
    setState(() {});
  }

  void updatePosition(int kddwX, int kddwY) {
    // print("PositionedWidgetState::updatePosition()");
    setState(() {
      x = kddwX;
      y = kddwY;
    });
  }

  void updateSize(int kddwWidth, int kddwHeight) {
    // print("PositionedWidgetState::updateSize()");
    setState(() {
      height = kddwHeight;
      width = kddwWidth;
    });
  }

  void resizeKDDWLayout() {
    // If the widget is resized by flutter then tell KDDW.
    // Example use case: User resizes the window, which resizes the KDDW layout
    if (!_fillsParent) return;

    final renderBox =
        kddwView.widgetKey.currentContext?.findRenderObject() as RenderBox;

    final Size size = renderBox.size;

    if (size.width != width || size.height != height) {
      kddwView.kddwView.onResize_2(size.width.toInt(), size.height.toInt());
    }
  }

  /// This is factored-out from build() so derived classes can return something else
  Widget buildContents() {
    return Container(color: kddwView.m_color);
  }

  @override
  Widget build(BuildContext context) {
    WidgetsBinding.instance.addPostFrameCallback((_) {
      resizeKDDWLayout();
    });

    if (_fillsParent)
      print("Build started width=${width} but ${kddwView.m_width}");

    final container = buildContents();

    if (_fillsParent) return container;

    return Positioned(
        width: width * 1.0,
        height: height * 1.0,
        top: y * 1.0,
        left: x * 1.0,
        child: container);
  }
}
