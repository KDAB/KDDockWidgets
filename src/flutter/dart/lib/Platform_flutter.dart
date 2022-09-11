/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/View_flutter.dart';
import 'package:KDDockWidgets/WindowOverlayWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

import 'ViewFactory_flutter.dart';

class Platform_flutter extends KDDockWidgetBindings.Platform_flutter {
  late final WindowOverlayWidget windowOverlayWidget;

  var floatingWindows = <KDDockWidgetBindings.FloatingWindow>[];

  @override
  String name() {
    return "flutter";
  }

  static Platform_flutter plat() {
    var p = KDDockWidgetBindings.Platform_flutter.platformFlutter();

    return KDDockWidgetBindings.Platform_flutter.fromCache(p.thisCpp)
        as Platform_flutter;
  }

  @override
  KDDockWidgetBindings.ViewFactory createDefaultViewFactory() {
    return ViewFactory_flutter();
  }

  @override
  KDDockWidgetBindings.View tests_createView(
      KDDockWidgetBindings.CreateViewOptions opts,
      {required KDDockWidgetBindings.View? parent}) {
    return View_flutter(null, 0, parent as View_flutter);
  }

  @override
  KDDockWidgetBindings.View createView(
      KDDockWidgetBindings.Controller? controller,
      {required KDDockWidgetBindings.View? parent}) {
    print("Platform_flutter: createView");
    return KDDockWidgetBindings.View_flutter(controller, 0, parent);
  }

  @override
  onFloatingWindowCreated(KDDockWidgetBindings.FloatingWindow? fw) {
    floatingWindows.add(fw!);
    rebuildWindowOverlay();
  }

  @override
  onFloatingWindowDestroyed(KDDockWidgetBindings.FloatingWindow? fw) {
    floatingWindows.remove(fw!);
    rebuildWindowOverlay();
  }

  void rebuildWindowOverlay() {
    final state = WindowOverlayWidget.globalKey().currentState;
    if (state != null) {
      state.onFloatingWindowCountChanged();
    }
  }

  @override
  void dumpManagedBacktrace() {
    print(StackTrace.current);
  }
}
