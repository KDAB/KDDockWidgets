/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/widgets/PositionedWidget.dart';
import 'package:KDDockWidgets/models/GeometryItem.dart';

import 'package:flutter/gestures.dart';
import 'package:flutter/material.dart';

class RubberBandWidget extends PositionedWidget {
  final GeometryItem geometryItem;
  RubberBandWidget(this.geometryItem, Key key) : super(geometryItem, key: key);

  @override
  State<PositionedWidget> createState() {
    return RubberBandWidgetState(geometryItem);
  }
}

class RubberBandWidgetState extends PositionedWidgetState {
  final GeometryItem geometryItem;
  RubberBandWidgetState(this.geometryItem) : super(geometryItem);

  @override
  Widget buildContents(BuildContext ctx) {
    return Container(
      decoration: new BoxDecoration(
          borderRadius: new BorderRadius.circular(1.0),
          color: Color(0x555ca1c5),
          border: Border.all(
            color: Color.fromARGB(255, 39, 77, 97),
            width: 2,
          )),
    );
  }
}
