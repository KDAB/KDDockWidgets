/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'package:flutter/gestures.dart';

import 'package:flutter/material.dart' hide View;

class TitleBar extends KDDWBindingsFlutter.TitleBar with View_mixin {
  TitleBar(KDDWBindingsCore.TitleBar? titleBar, KDDWBindingsCore.View? parent)
      : super(titleBar, parent: parent) {
    m_fillsParent = true;
    initMixin(this, debugName: "TitleBar", parent: parent);
  }

  @override
  void onTitleBarChanged(String? newTitle) {
    widgetState<TitleBarPositionedWidgetState>()?.title = newTitle!;
  }

  Widget createFlutterWidget() {
    return TitleBarWidget(kddwView, this, key: widgetKey);
  }
}

class TitleBarWidget extends PositionedWidget {
  final TitleBar TitleBarView;
  TitleBarWidget(var kddwView, this.TitleBarView, {Key? key})
      : super(kddwView, key: key);

  @override
  State<PositionedWidget> createState() {
    return TitleBarPositionedWidgetState(kddwView, TitleBarView);
  }
}

class TitleBarPositionedWidgetState extends PositionedWidgetState {
  final TitleBar titleBarView;
  String? _title;
  set title(String newTitle) {
    if (_title != newTitle) {
      setState(() {
        _title = newTitle;
      });
    }
  }

  TitleBarPositionedWidgetState(var kddwView, this.titleBarView)
      : super(kddwView);

  @override
  Widget buildContents(BuildContext ctx) {
    final contents = SizedBox(
        height: 30,
        child: Container(
            padding: EdgeInsets.fromLTRB(8, 3, 5, 0),
            color: Color(0xffF6E8EA),
            child: Row(
              children: [
                Expanded(
                  child: Text(
                    titleBarView.asTitleBarController().title().toDartString(),
                    style: TextStyle(fontWeight: FontWeight.bold, fontSize: 15),
                  ),
                ),
                TextButton(
                  style: TextButton.styleFrom(
                    minimumSize: Size.zero,
                    padding: EdgeInsets.fromLTRB(4, 0, 4, 0),
                    foregroundColor: Colors.black,
                  ),
                  onPressed: () {
                    titleBarView.asTitleBarController().onFloatClicked();
                  },
                  child: Icon(Icons.square_outlined),
                ),
                TextButton(
                  style: TextButton.styleFrom(
                    minimumSize: Size.zero,
                    padding: EdgeInsets.fromLTRB(4, 0, 4, 0),
                    foregroundColor: Colors.black,
                  ),
                  onPressed: () {
                    titleBarView.asTitleBarController().onCloseClicked();
                  },
                  child: Icon(Icons.close),
                ),
              ],
            )));

    return Listener(
        onPointerDown: (event) {
          kddwView.onFlutterMouseEvent(event);
        },
        onPointerUp: (event) {
          kddwView.onFlutterMouseEvent(event);
        },
        onPointerMove: (event) {
          if (event.buttons != kPrimaryButton) return;
          kddwView.onFlutterMouseEvent(event);
        },
        child: contents);
  }
}
