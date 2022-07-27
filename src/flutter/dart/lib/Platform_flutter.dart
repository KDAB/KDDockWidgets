/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_flutter.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

import 'ViewFactory_flutter.dart';

class Platform_flutter extends KDDockWidgetBindings.Platform_flutter {
  String name() {
    return "flutter";
  }

  KDDockWidgetBindings.ViewFactory createDefaultViewFactory() {
    return ViewFactory_flutter();
  }

  KDDockWidgetBindings.View tests_createView(
      KDDockWidgetBindings.CreateViewOptions opts,
      {required KDDockWidgetBindings.View? parent}) {
    return View_flutter(null, 0, parent as View_flutter);
  }
}
