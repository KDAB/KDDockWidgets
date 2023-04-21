/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:KDDockWidgets/FloatingWindow.dart' as KDDW;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;

/// @brief A Widget that hosts a single KDDW FloatingWindow
/// Since Flutter doesn't support real OS level multi-windows we need
/// to draw the windows ourselves
class WindowWidget extends StatefulWidget {
  late final KDDW.FloatingWindow kddwFloatingWindowView;
  WindowWidget(KDDWBindingsCore.FloatingWindow fw) {
    kddwFloatingWindowView =
        KDDWBindingsFlutter.View_flutter.fromCache(fw.view().thisCpp)
            as KDDW.FloatingWindow;
  }

  @override
  State<StatefulWidget> createState() {
    return WindowWidgetState(kddwFloatingWindowView);
  }
}

class WindowWidgetState extends State<WindowWidget> {
  late final KDDW.FloatingWindow kddwFloatingWindowView;
  WindowWidgetState(this.kddwFloatingWindowView);

  @override
  Widget build(BuildContext context) {
    final x = kddwFloatingWindowView.m_x;
    final y = kddwFloatingWindowView.m_y;
    final width = kddwFloatingWindowView.m_width;
    final height = kddwFloatingWindowView.m_height;

    return Positioned(
        left: x.toDouble(),
        top: y.toDouble(),
        width: width.toDouble(),
        height: height.toDouble(),
        child: kddwFloatingWindowView.flutterWidget);
  }
}
