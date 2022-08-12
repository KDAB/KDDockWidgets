/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ffi' as ffi;
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';

class DockWidget_flutter extends KDDockWidgetBindings.DockWidget_flutter
    with View_mixin {
  DockWidget_flutter(String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0})
      : super(uniqueName,
            options: options, layoutSaverOptions: layoutSaverOptions) {
    m_color = Colors.pink;
    m_fillsParent = true;
    kddwView = this;
    final ffi.Pointer<ffi.Void> ptr = thisCpp.cast<ffi.Void>();
    widgetKey = GlobalObjectKey(ptr.address);
    flutterWidget = PositionedWidget(this, key: widgetKey);
    debugName = "DockWidget";
    print("DockWidget_flutter CTOR");
  }
}
