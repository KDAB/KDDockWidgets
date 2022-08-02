/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ffi';

import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'DropArea_flutter.dart';
import 'View_flutter.dart';

class ViewFactory_flutter extends KDDockWidgetBindings.ViewFactory_flutter {
  ViewFactory_flutter() {
    print("Dart: Created ViewFactory_flutter");
  }

  @override
  KDDockWidgetBindings.View createDropArea(
      KDDockWidgetBindings.DropArea? controller,
      KDDockWidgetBindings.View? parent) {
    print("ViewFactory_flutter: Creating DropArea");
    var da = DropArea_flutter(controller, 0, parent);
    print("ViewFactory_flutter: Created DropArea");
    return da;
  }

  @override
  KDDockWidgetBindings.ClassicIndicatorWindowViewInterface
      createClassicIndicatorWindow(
          KDDockWidgetBindings.ClassicIndicators? indicators) {
    print("ViewFactory_flutter: createClassicIndicatorWindow");
    return KDDockWidgetBindings.ClassicIndicatorWindowViewInterface();
  }

  @override
  KDDockWidgetBindings.View createGroup(KDDockWidgetBindings.Group? arg__1,
      {required KDDockWidgetBindings.View? parent}) {
    print("ViewFactory_flutter: createGroup");
    // Something generic for now
    return View_flutter(null, 0, parent);
  }
}
