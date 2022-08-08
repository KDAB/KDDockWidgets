/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/cupertino.dart';
import 'View_mixin.dart';

class View_flutter extends KDDockWidgetBindings.View_flutter with View_mixin {
  View_flutter(KDDockWidgetBindings.Controller? controller, int type,
      KDDockWidgetBindings.View? parent,
      {int windowFlags = 0})
      : super(controller, type, parent, windowFlags: windowFlags) {
    createFlutterWidget();
  }

  View_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {
    createFlutterWidget();
  }

  void createFlutterWidget() {
    // The key is the C++ KDDockWidget pointer, which is stable and unique
    final ffi.Pointer<ffi.Void> ptr = thisCpp.cast<ffi.Void>();
    widgetKey = GlobalObjectKey(ptr.address);
    flutterWidget = PositionedWidget(this, key: widgetKey);
  }
}
