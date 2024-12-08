/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/KDDockWidgets.dart';

import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';

class TitleBarWidget extends StatefulWidget {
  final TitleBar titlebar;
  TitleBarWidget(this.titlebar, {Key? key}) : super(key: key);

  @override
  State<TitleBarWidget> createState() {
    return TitleBarState(titlebar);
  }
}

class TitleBarState extends State<TitleBarWidget> {
  final TitleBar titlebar;
  TitleBarState(this.titlebar);

  Widget buildContents(BuildContext ctx) {
    const double vPadding = 4;
    const double iconVPadding = 4;
    const double maxIconHeight = 26;
    final ButtonStyle style = IconButton.styleFrom(
      foregroundColor: Theme.of(context).colorScheme.onSurfaceVariant,
      minimumSize: const Size(26, maxIconHeight),
      maximumSize: const Size(26, maxIconHeight),
      padding: const EdgeInsets.all(iconVPadding),
      iconSize: 22,
    );

    final contents = SizedBox(
      height: maxIconHeight + (2 * vPadding) + (2 * iconVPadding),
      child: Container(
        color: Colors.transparent, // for hit testing
        padding: const EdgeInsets.only(
            top: vPadding, bottom: vPadding, left: 16, right: 4),
        child: Row(
          children: [
            Expanded(
              child: Text(
                titlebar.title,
                style: Theme.of(context).textTheme.bodyMedium,
              ),
            ),
            IconButton(
              onPressed: () {
                titlebar.onFloatClicked();
              },
              style: style,
              icon: const Icon(
                Icons.filter_none,
              ),
            ),
            IconButton(
              onPressed: () {
                titlebar.onCloseClicked();
              },
              style: style,
              icon: const Icon(
                Icons.close,
              ),
            ),
          ],
        ),
      ),
    );

    return Listener(
        onPointerDown: (event) {
          titlebar.onMouseEvent(event);
        },
        onPointerUp: (event) {
          titlebar.onMouseEvent(event);
        },
        onPointerMove: (event) {
          if (event.buttons != kPrimaryButton) return;
          titlebar.onMouseEvent(event);
        },
        child: contents);
  }

  @override
  Widget build(BuildContext context) {
    return buildContents(context);
  }
}
