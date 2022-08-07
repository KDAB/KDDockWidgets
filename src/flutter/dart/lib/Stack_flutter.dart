/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_mixin.dart';

import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

class Stack_flutter extends KDDockWidgetBindings.Stack_flutter with View_mixin {
  Stack_flutter(
      KDDockWidgetBindings.Stack? stack, KDDockWidgetBindings.View? parent)
      : super(stack, parent: parent) {
    print("Stack_flutter CTOR");
  }
}
