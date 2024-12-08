/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/widgets.dart';
import 'package:KDDockWidgets/KDDockWidgets.dart';

class DockWidget extends StatefulWidget {
  final DockItem dockItem;
  DockWidget(this.dockItem, {Key? key}) : super(key: key) {}

  @override
  State<DockWidget> createState() {
    return DockWidgetState(dockItem);
  }
}

class DockWidgetState extends State<DockWidget> {
  final DockItem dockItem;
  DockWidgetState(this.dockItem) {}

  void setGuestWidget(Widget w) {
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    if (dockItem.guestWidget == null) {
      return Container();
    } else {
      return dockItem.guestWidget!;
    }
  }
}
