/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/models/Separator.dart';
import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';

import 'PositionedWidget.dart';

class SeparatorWidget extends PositionedWidget {
  final Separator separator;
  SeparatorWidget(this.separator, {Key? key}) : super(separator, key: key);

  @override
  State<PositionedWidget> createState() {
    return SeparatorWidgetState(separator);
  }
}

class SeparatorWidgetState extends PositionedWidgetState {
  final Separator separator;
  SeparatorWidgetState(this.separator) : super(separator) {
    separator.changed.connect(() {
      setState(() {});
    });
  }

  @override
  Widget buildContents(BuildContext ctx) {
    // This simply wraps the default widget into a MouseRegion, so we can
    // react to mouse events
    final defaultContainer = Container(color: Colors.blue);

    return Listener(
      onPointerDown: (event) {
        separator.onMousePress();
      },
      onPointerUp: (event) {
        separator.onMouseReleased();
      },
      onPointerMove: (event) {
        if (event.buttons != kPrimaryButton) return;

        // final renderBox = (separatorView.m_parent as View_mixin)
        //     .widgetKey
        //     .currentContext
        //     ?.findRenderObject() as RenderBox;

        // TODO
        var renderBox = ctx.findRenderObject() as RenderBox;

        // The event is in coord space of the Separator. KDDW needs the position in
        // the coord space of the DropArea (m_parent) instead:

        var trans = renderBox.getTransformTo(null); // local to global
        trans.invert(); // global to local
        final localPos = event.transformed(trans).localPosition;

        print("local ${localPos} ${event.localPosition}");

        separator.onMouseMove(event.localPosition);
      },
      child: MouseRegion(
          child: defaultContainer,
          cursor: separator.isVertical
              ? SystemMouseCursors.resizeDown
              : SystemMouseCursors.resizeLeft),
    );
  }
}
