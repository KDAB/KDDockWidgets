/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ffi';

import 'package:KDDockWidgets/FloatingWindow.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'DockWidget.dart';
import 'DropArea.dart';
import 'Group.dart';
import 'Separator.dart';
import 'Stack.dart';
import 'TitleBar.dart';
import 'TabBar.dart';

class ViewFactory extends KDDockWidgetBindings.ViewFactory_flutter {
  ViewFactory() {
    print("Dart: Created ViewFactory_flutter");
  }

  @override
  KDDWBindingsCore.View createDropArea(
      KDDWBindingsCore.DropArea? controller, KDDWBindingsCore.View? parent) {
    print("ViewFactory: Creating DropArea");
    var da = DropArea(
        controller, KDDockWidgetBindings.Core_ViewType.DropArea, parent);
    print("ViewFactory: Created DropArea");
    return da;
  }

  @override
  KDDockWidgetBindings.ClassicIndicatorWindowViewInterface
      createClassicIndicatorWindow(
          KDDockWidgetBindings.ClassicIndicators? indicators) {
    print("ViewFactory: createClassicIndicatorWindow");
    return KDDockWidgetBindings.ClassicIndicatorWindowViewInterface();
  }

  @override
  KDDWBindingsCore.View createGroup(KDDWBindingsCore.Group? group,
      {required KDDWBindingsCore.View? parent}) {
    print("ViewFactory: createGroup");
    return Group(group, parent);
  }

  @override
  KDDWBindingsCore.View createTabBar(KDDWBindingsCore.TabBar? tabBar,
      {required KDDWBindingsCore.View? parent}) {
    print("ViewFactory: createTabBar");
    return TabBar(tabBar, parent);
  }

  @override
  KDDWBindingsCore.View createTitleBar(
      KDDWBindingsCore.TitleBar? controller, KDDWBindingsCore.View? parent) {
    print("ViewFactory: createTitleBar");
    return TitleBar(controller, parent);
  }

  @override
  KDDWBindingsCore.View createStack(
      KDDWBindingsCore.Stack? stack, KDDWBindingsCore.View? parent) {
    print("ViewFactory: createStack");
    return Stack(stack, parent);
  }

  @override
  KDDWBindingsCore.View createSeparator(KDDWBindingsCore.Separator? separator,
      {required KDDWBindingsCore.View? parent}) {
    return Separator(separator, parent: parent);
  }

  @override
  KDDWBindingsCore.View createDockWidget(String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0, int windowFlags = 0}) {
    return DockWidget(uniqueName,
        options: options, layoutSaverOptions: layoutSaverOptions);
  }

  @override
  KDDWBindingsCore.View createFloatingWindow(
      KDDWBindingsCore.FloatingWindow? controller,
      {required KDDWBindingsCore.MainWindow? parent,
      int windowFlags = 0}) {
    // TODOm4: What to do with main window pointer
    return FloatingWindow(controller, null);
  }
}
