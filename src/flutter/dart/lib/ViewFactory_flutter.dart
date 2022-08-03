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
    var da = DropArea_flutter(
        controller, KDDockWidgetBindings.KDDockWidgets_Type.DropArea, parent);
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
  KDDockWidgetBindings.View createGroup(KDDockWidgetBindings.Group? group,
      {required KDDockWidgetBindings.View? parent}) {
    print("ViewFactory_flutter: createGroup");
    // Something generic for now
    return View_flutter(
        group, KDDockWidgetBindings.KDDockWidgets_Type.Frame, parent);
  }

  @override
  KDDockWidgetBindings.View createTabBar(KDDockWidgetBindings.TabBar? tabBar,
      {required KDDockWidgetBindings.View? parent}) {
    // Something generic for now
    print("ViewFactory_flutter: createTabBar");
    return View_flutter(
        tabBar, KDDockWidgetBindings.KDDockWidgets_Type.TabBar, parent);
  }

  @override
  KDDockWidgetBindings.View createTitleBar(
      KDDockWidgetBindings.TitleBar? controller,
      KDDockWidgetBindings.View? parent) {
    // Something generic for now
    print("ViewFactory_flutter: createTitleBar");
    return View_flutter(
        controller, KDDockWidgetBindings.KDDockWidgets_Type.TitleBar, parent);
  }

  @override
  KDDockWidgetBindings.View createStack(
      KDDockWidgetBindings.Stack? stack, KDDockWidgetBindings.View? parent) {
    // Something generic for now
    print("ViewFactory_flutter: createStack");
    return View_flutter(
        stack, KDDockWidgetBindings.KDDockWidgets_Type.Stack, parent);
  }
}
