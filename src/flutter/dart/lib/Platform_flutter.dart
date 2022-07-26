/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgetsBindings/src/Platform_flutter.dart'
    as KDDockWidgetBindings;

import 'package:KDDockWidgetsBindings/src/ViewFactory.dart'
    as KDDockWidgetBindings;

import 'ViewFactory_flutter.dart';

class Platform_flutter extends KDDockWidgetBindings.Platform_flutter {
  String name() {
    return "flutter";
  }

KDDockWidgetBindings.ViewFactory createDefaultViewFactory() {
  print("Dart foo!");
  return ViewFactory_flutter();
}

}
