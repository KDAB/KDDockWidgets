/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// import 'package:KDDockWidgets/IndicatorWindow.dart';
import 'package:KDDockWidgets/models/Separator.dart';
import 'package:KDDockWidgets/widgets/RubberBandWidget.dart';
import 'package:KDDockWidgets/widgets/GroupWidget.dart';
import 'package:KDDockWidgets/KDDockWidgets.dart';
import 'package:KDDockWidgets/widgets/SeparatorWidget.dart';

import 'package:flutter/material.dart';

class DropAreaWidget extends StatefulWidget {
  final DropArea dropArea;
  DropAreaWidget(this.dropArea) : super(key: dropArea.key);

  @override
  State<DropAreaWidget> createState() {
    return DropAreaWidgetState(dropArea);
  }
}

class DropAreaWidgetState extends State<DropAreaWidget> {
  final DropArea dropArea;
  var oldSize = Size(-1, -1);

  DropAreaWidgetState(this.dropArea) {
    dropArea.layoutChanged.connect(() {
      setState(() {});
    });
  }

  void scheduleCheckLayoutSize() {
    WidgetsBinding.instance.addPostFrameCallback((_) {
      final renderBox =
          dropArea.key.currentContext?.findRenderObject() as RenderBox?;

      if (renderBox == null) return;

      final Size size = renderBox.size;
      if (size != oldSize) {
        dropArea.setLayoutSize(size.width.toInt(), size.height.toInt());
        oldSize = size;
      }
      scheduleCheckLayoutSize();
    });
  }

  @override
  void initState() {
    super.initState();
    scheduleCheckLayoutSize();
  }

  @override
  void dispose() {
    super.dispose();
  }

  // IndicatorWindow indicatorWindow() {
  //   final DropArea da = kddwView.asFlutterView() as DropArea;
  //   return KDDWBindingsFlutter.IndicatorWindow.fromCache(
  //       da.indicatorWindow().thisCpp) as IndicatorWindow;
  // }

  // RubberWidgetBand rubberBand() {
  //   return KDDWBindingsFlutter.View.fromCache(
  //       indicatorWindow().rubberBand().thisCpp) as RubberBand;
  // }

  Widget buildContents(BuildContext ctx) {
    final List<Widget> groupWidgets =
        dropArea.groups.map((group) => GroupWidget(group)).toList();

    final List<Widget> separatorWidgets = dropArea.separators
        .map((separator) => SeparatorWidget(separator))
        .toList();

    return Container(
        color: Colors.yellow,
        child: Stack(
          fit: StackFit.expand,
          children: [...groupWidgets, ...separatorWidgets],
        ));
  }

  @override
  Widget build(BuildContext context) {
    return buildContents(context);
  }
}
