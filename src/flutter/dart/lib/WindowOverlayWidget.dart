/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';

/// @brief A Widget to host KDDW floating windows
/// Since Flutter doesn't support real OS level multi-window we need
/// to draw the floating windows into an overlay
class WindowOverlayWidget extends StatefulWidget {
  @override
  State<StatefulWidget> createState() {
    return WindowOverlayWidgetState();
  }
}

class WindowOverlayWidgetState extends State<WindowOverlayWidget> {
  @override
  Widget build(BuildContext context) {
    return Stack(children: []);
  }
}
