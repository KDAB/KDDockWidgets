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
  KDDockWidgetBindings.View createDropArea(
      KDDockWidgetBindings.DropArea? controller,
      KDDockWidgetBindings.View? parent) {
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
  KDDockWidgetBindings.View createGroup(KDDockWidgetBindings.Group? group,
      {required KDDockWidgetBindings.View? parent}) {
    print("ViewFactory: createGroup");
    return Group(group, parent);
  }

  @override
  KDDockWidgetBindings.View createTabBar(KDDockWidgetBindings.TabBar? tabBar,
      {required KDDockWidgetBindings.View? parent}) {
    print("ViewFactory: createTabBar");
    return TabBar(tabBar, parent);
  }

  @override
  KDDockWidgetBindings.View createTitleBar(
      KDDockWidgetBindings.TitleBar? controller,
      KDDockWidgetBindings.View? parent) {
    print("ViewFactory: createTitleBar");
    return TitleBar(controller, parent);
  }

  @override
  KDDockWidgetBindings.View createStack(
      KDDockWidgetBindings.Stack? stack, KDDockWidgetBindings.View? parent) {
    print("ViewFactory: createStack");
    return Stack(stack, parent);
  }

  @override
  KDDockWidgetBindings.View createSeparator(
      KDDockWidgetBindings.Separator? separator,
      {required KDDockWidgetBindings.View? parent}) {
    return Separator(separator, parent: parent);
  }

  @override
  KDDockWidgetBindings.View createDockWidget(String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0, int windowFlags = 0}) {
    return DockWidget(uniqueName,
        options: options, layoutSaverOptions: layoutSaverOptions);
  }

  @override
  KDDockWidgetBindings.View createFloatingWindow(
      KDDockWidgetBindings.FloatingWindow? controller,
      {required KDDockWidgetBindings.MainWindow? parent,
      int windowFlags = 0}) {
    // TODOm4: What to do with main window pointer
    return FloatingWindow(controller, null);
  }
}
