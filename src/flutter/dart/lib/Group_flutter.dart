/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ffi' as ffi;
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/material.dart';

class Group_flutter extends KDDockWidgetBindings.Group_flutter with View_mixin {
  Group_flutter(
      KDDockWidgetBindings.Group? group, KDDockWidgetBindings.View? parent)
      : super(group, parent: parent) {
    m_color = Colors.amber;
    kddwView = this;
    final ffi.Pointer<ffi.Void> ptr = thisCpp.cast<ffi.Void>();
    widgetKey = GlobalObjectKey(ptr.address);
    flutterWidget = PositionedWidget(this, key: widgetKey);
    debugName = "group";
    print("Group_flutter CTOR");
  }
}
