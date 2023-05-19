/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ffi' as ffi;
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgets/WindowWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:flutter/gestures.dart';

import 'package:flutter/material.dart' hide View;

class View_mixin {
  late final Widget flutterWidget;
  late final GlobalObjectKey<PositionedWidgetState> widgetKey;
  late final KDDWBindingsFlutter.View kddwView;
  WindowWidget?
      windowWidget; // For now, while we don't have multi-window support

  Color m_color = Colors.red;
  bool m_fillsParent = false;
  String debugName = "";

  var childWidgets = <Widget>[];

  void initMixin(var kddwView,
      {var color = Colors.transparent, var debugName = ""}) {
    this.kddwView = kddwView;
    m_color = color;
    this.debugName = debugName;

    // The key is the C++ View pointer, which is stable and unique
    final ffi.Pointer<ffi.Void> ptr = kddwView.thisCpp.cast<ffi.Void>();
    widgetKey = GlobalObjectKey(ptr.address);

    flutterWidget = createFlutterWidget();
  }

  QRect viewGeometry() {
    return kddwView.geometry();
  }

  /// Casts to our flutter::View class
  KDDWBindingsFlutter.View asFlutterView() {
    return KDDWBindingsFlutter.View.fromCache(kddwView.thisCpp);
  }

  void onFlutterMouseEvent(PointerEvent event) {
    int eventType = -1;
    if (event is PointerDownEvent) eventType = Event_Type.MouseButtonPress;
    if (event is PointerUpEvent) eventType = Event_Type.MouseButtonRelease;
    if (event is PointerMoveEvent) eventType = Event_Type.MouseMove;

    if (eventType == -1) {
      print("Unhandled mouse event!");
      return;
    }

    final bool leftIsPressed = event.buttons == kPrimaryButton;
    final localPos = QPoint.ctor2(
        event.localPosition.dx.toInt(), event.localPosition.dy.toInt());
    final globalPos =
        QPoint.ctor2(event.position.dx.toInt(), event.position.dy.toInt());

    asFlutterView().onMouseEvent(eventType, localPos, globalPos, leftIsPressed);
  }

  void onGeometryChanged() {
    final state = widgetKey.currentState;
    if (state != null) {
      state.updateSize();
    }

    if (windowWidget != null) {
      final windowState = (windowWidget!.key as GlobalObjectKey).currentState;

      if (windowState != null) {
        (windowState as WindowWidgetState).onGeometryChanged();
      }
    }
  }

  void onChildAdded(KDDWBindingsCore.View? childView) {
    final state = widgetKey.currentState;

    final viewFlutter =
        KDDWBindingsFlutter.View.fromCache(childView!.thisCpp) as View_mixin;

    // print(
    //     "View_mixin::onChildAdded: this=${debugName}, child=${viewFlutter.debugName}, widget=${viewFlutter.flutterWidget}");

    childWidgets.add(viewFlutter.flutterWidget);

    if (state != null) {
      state.childrenChanged();
    }
  }

  void onChildRemoved(KDDWBindingsCore.View? childView) {
    final state = widgetKey.currentState;
    final viewFlutter =
        KDDWBindingsFlutter.View.fromCache(childView!.thisCpp) as View_mixin;
    childWidgets.remove(viewFlutter.flutterWidget);
    if (state != null) {
      state.childrenChanged();
    }
  }

  void onChildVisibilityChanged(KDDWBindingsCore.View? childView) {
    final state = widgetKey.currentState;
    if (state != null) {
      state.childrenChanged();
    }
  }

  List<Widget> visibleChildWidgets() {
    return childWidgets.where((w) {
      return !(w as PositionedWidget).kddwView.kddwView.isExplicitlyHidden();
    }).toList();
  }

  Widget createFlutterWidget() {
    return PositionedWidget(this, key: widgetKey);
  }
}
