/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';

import 'Group_flutter.dart';
import 'View_flutter.dart';

class View_mixin {
  late final Widget flutterWidget;
  late final GlobalObjectKey<PositionedWidgetState> widgetKey;
  late final KDDockWidgetBindings.View_flutter kddwView;

  Color m_color = Colors.red;
  int m_x = 100;
  int m_y = 100;
  int m_width = 400;
  int m_height = 400;
  bool m_fillsParent = false;
  String debugName = "";

  int m_maxHeight = 16777215;
  int m_maxWidth = 16777215;

  var childWidgets = <Widget>[];

  setSize_2(int width, int height) {
    // print(
    //     "View_mixin::setSize called ${width}x${height} ; old=${m_width}x${height}");
    if (m_width != width || height != m_height) {
      m_width = width;
      m_height = height;

      final state = widgetKey.currentState;
      if (state != null) {
        state.updateSize(m_width, m_height);
      }
    }
  }

  void setWidth(int width) {
    setSize_2(width, m_height);
  }

  setHeight(int height) {
    setSize_2(m_width, height);
  }

  void setFixedWidth(int width) {
    // TODO
    setSize_2(width, m_height);
  }

  setFixedHeight(int height) {
    // TODO
    setSize_2(m_width, height);
  }

  void onChildAdded(KDDockWidgetBindings.View? childView) {
    final state = widgetKey.currentState;

    final viewFlutter =
        KDDockWidgetBindings.View_flutter.fromCache(childView!.thisCpp)
            as View_mixin;

    print(
        "View_mixin::onChildAdded: this=${debugName}, child=${viewFlutter.debugName}");

    childWidgets.add(viewFlutter.flutterWidget);

    if (state != null) {
      state.childrenChanged();
    }
  }

  void onChildRemoved(KDDockWidgetBindings.View? childView) {
    final state = widgetKey.currentState;
    final viewFlutter =
        KDDockWidgetBindings.View_flutter.fromCache(childView!.thisCpp)
            as View_mixin;
    childWidgets.remove(viewFlutter.flutterWidget);
    if (state != null) {
      state.childrenChanged();
    }
  }

  setGeometry(KDDockWidgetBindings.QRect geo) {
    // print("View_mixin: setGeometry .name=${debugName}");
    final sz = geo.size();
    final topLeft = geo.topLeft();
    setSize_2(sz.width(), sz.height());
    move_2(topLeft.x(), topLeft.y());
  }

  KDDockWidgetBindings.QRect geometry() {
    return KDDockWidgetBindings.QRect.ctor4(m_x, m_y, m_width, m_height);
  }

  KDDockWidgetBindings.QRect normalGeometry() {
    // TODO
    return geometry();
  }

  KDDockWidgetBindings.QSize maxSizeHint() {
    // print("View_flutter::maximumSize()");
    return KDDockWidgetBindings.QSize.ctor2(m_maxWidth, m_maxHeight);
  }

  move_2(int x, int y) {
    // print("View_flutter::move called ${x},${y}");
    if (m_x != x || m_y != y) {
      m_x = x;
      m_y = y;
      final state = widgetKey.currentState;
      if (state != null) {
        state.updatePosition(m_x, m_y);
      }
    }
  }
}
