/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:flutter/material.dart' hide View;

class DockWidget extends KDDWBindingsFlutter.DockWidget with View_mixin {
  Widget? guestwidget;
  DockWidget(String? uniqueName, {int options = 0, int layoutSaverOptions = 0})
      : super(uniqueName,
            options: options, layoutSaverOptions: layoutSaverOptions) {
    m_fillsParent = true;
    initMixin(this, color: Colors.pink, debugName: "DockWidget");
  }

  void setGuestWidget(Widget w) {
    guestwidget = w;
    if (widgetKey.currentState != null) {
      (widgetKey.currentState as DockWidgetPositionedWidgetState)
          .setGuestWidget(w);
    }
  }

  Widget createFlutterWidget() {
    return DockWidgetWidget(kddwView, this, key: widgetKey);
  }
}

class DockWidgetWidget extends PositionedWidget {
  final DockWidget DockWidgetView;
  DockWidgetWidget(var kddwView, this.DockWidgetView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return DockWidgetPositionedWidgetState(kddwView, DockWidgetView);
  }
}

class DockWidgetPositionedWidgetState extends PositionedWidgetState {
  final DockWidget DockWidgetView;
  Widget? guestWidget;

  DockWidgetPositionedWidgetState(var kddwView, this.DockWidgetView)
      : super(kddwView) {
    guestWidget = DockWidgetView.guestwidget;
  }

  void setGuestWidget(Widget w) {
    setState(() {
      guestWidget = w;
    });
  }

  @override
  Widget buildContents(BuildContext ctx) {
    if (guestWidget == null) {
      return Container();
    } else {
      return guestWidget!;
    }
  }
}
