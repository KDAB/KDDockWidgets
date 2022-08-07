/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/PositionedWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

class Group_flutter extends KDDockWidgetBindings.Group_flutter with View_mixin {
  Group_flutter(
      KDDockWidgetBindings.Group? group, KDDockWidgetBindings.View? parent)
      : super(group, parent: parent) {
    flutterWidget = PositionedWidget(this);
    print("Group_flutter CTOR");
  }
}
