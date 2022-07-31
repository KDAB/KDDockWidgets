/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

class View_flutter extends KDDockWidgetBindings.View_flutter {
  late final PositionedWidget flutterWidget;

  Function(int, int)? updatePositionCallback;
  Function(int, int)? updateSizeCallback;

  int m_x = 100;
  int m_y = 100;
  int m_width = 400;
  int m_height = 400;
  bool m_fillsParent = false;

  View_flutter(KDDockWidgetBindings.Controller? controller, int type,
      KDDockWidgetBindings.View? parent,
      {int windowFlags = 0})
      : super(controller, type, parent, windowFlags: windowFlags) {
    flutterWidget = PositionedWidget(this);
  }

  View_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {
    flutterWidget = PositionedWidget(this);
  }

  setSize_2(int width, int height) {
    print("View_flutter::setSize called ${width}x${height}");
    if (m_width != width || m_height != height) {
      m_width = width;
      m_height = height;
      if (updateSizeCallback != null) updateSizeCallback!(width, height);
    }
  }

  move_2(int x, int y) {
    print("View_flutter::move called ${x},${y}");
    if (m_x != x || m_y != y) {
      m_x = x;
      m_y = y;
      print(updatePositionCallback);
      print(updateSizeCallback);
      if (updatePositionCallback != null) updatePositionCallback!(x, y);
    }
  }
}
