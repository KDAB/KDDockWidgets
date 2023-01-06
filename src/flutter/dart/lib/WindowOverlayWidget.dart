/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/WindowWidget.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:KDDockWidgets/Platform_flutter.dart';

/// @brief A Widget to host KDDW floating windows
/// Since Flutter doesn't support real OS level multi-windows we need
/// to draw the floating windows into an overlay
class WindowOverlayWidget extends StatefulWidget {
  // We only have one overlay per application
  static GlobalObjectKey<WindowOverlayWidgetState> globalKey() {
    return GlobalObjectKey<WindowOverlayWidgetState>("windowOverlayState");
  }

  WindowOverlayWidget() : super(key: globalKey());

  @override
  State<StatefulWidget> createState() {
    return WindowOverlayWidgetState();
  }
}

class WindowOverlayWidgetState extends State<WindowOverlayWidget> {
  @override
  Widget build(BuildContext context) {
    final floatingWindows = Platform_flutter.plat().floatingWindows;
    List<Widget> windowWidgets = [];
    for (var fw in floatingWindows) {
      windowWidgets.add(WindowWidget(fw));
    }

    return Stack(children: windowWidgets);
  }

  onFloatingWindowCountChanged() {
    print("onFloatingWindowCountChanged!");
    setState(() {});
  }
}
