/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/Platform_flutter.dart';
import 'package:KDDockWidgetsBindings/src/Config.dart' as KDDockWidgetBindings;

void f(Function(int x, int y)? f) {
  if (f != null) f(0, 0);
}

void main(List<String> args) {
  var p = Platform_flutter();

  var config = KDDockWidgetBindings.Config.self();
  print("Config.separatorThickness: ${config.separatorThickness()}");

  print("Platform.name: " + p.name());
}
