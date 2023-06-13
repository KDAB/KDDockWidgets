/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:developer';

import 'package:KDDockWidgets/MainWindow.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgets/View.dart';
import 'package:KDDockWidgets/WindowOverlayWidget.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;
import 'package:KDDockWidgetsBindings/Bindings.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;
import 'ViewFactory.dart';

class Platform extends KDDWBindingsFlutter.Platform {
  late final WindowOverlayWidget windowOverlayWidget;

  var floatingWindows = <KDDWBindingsCore.FloatingWindow>[];
  var mainWindows = <KDDWBindingsCore.MainWindow>[];
  var indicatorWindows = <KDDWBindingsFlutter.IndicatorWindow>[];

  @override
  @pragma("vm:entry-point")
  String name() {
    return "flutter";
  }

  static Platform plat() {
    var p = KDDWBindingsFlutter.Platform.platformFlutter();

    return KDDWBindingsFlutter.Platform.fromCache(p.thisCpp) as Platform;
  }

  @override
  @pragma("vm:entry-point")
  KDDWBindingsCore.ViewFactory createDefaultViewFactory() {
    return ViewFactory();
  }

  @override
  @pragma("vm:entry-point")
  KDDWBindingsCore.View tests_createView(
      KDDockWidgetBindings.CreateViewOptions opts,
      {required KDDWBindingsCore.View? parent}) {
    final view = View(null, 0, parent);

    view.setSizeHint(opts.getSizeHint());
    view.setMinimumSize(opts.getMinSize());
    view.setMaximumSize(opts.getMaxSize());
    view.setVisible(opts.isVisible);

    return view;
  }

  @override
  @pragma("vm:entry-point")
  KDDWBindingsCore.View createView(KDDWBindingsCore.Controller? controller,
      {required KDDWBindingsCore.View? parent}) {
    return GenericView(controller, parent);
  }

  @override
  @pragma("vm:entry-point")
  KDDWBindingsCore.MainWindow createMainWindow(
      String? uniqueName, CreateViewOptions viewOpts,
      {int options =
          KDDockWidgets_MainWindowOption.MainWindowOption_HasCentralFrame,
      required KDDWBindingsCore.View? parent,
      int arg__5 = 0}) {
    final parentView =
        parent == null ? null : (parent as KDDWBindingsFlutter.MainWindow);
    var mw = MainWindow(uniqueName,
        parent: parentView, flags: arg__5, options: options);

    mw.resize(viewOpts.getSize());

    return mw.m_controller;
  }

  @override
  @pragma("vm:entry-point")
  onFloatingWindowCreated(KDDWBindingsCore.FloatingWindow? fw) {
    floatingWindows.add(fw!);
    rebuildWindowOverlay();
  }

  @override
  @pragma("vm:entry-point")
  onFloatingWindowDestroyed(KDDWBindingsCore.FloatingWindow? fw) {
    final oldSize = floatingWindows.length;
    floatingWindows.removeWhere((it) => it.thisCpp == fw!.thisCpp);
    // kddw emits windowDestroyed twice, one when it's scheduled and one in dtor
    // so only rebuild if list length actually changed
    if (oldSize != floatingWindows.length) {
      rebuildWindowOverlay();
    }
  }

  @override
  @pragma("vm:entry-point")
  onMainWindowCreated(KDDWBindingsCore.MainWindow? mw) {
    mainWindows.add(mw!);
    rebuildWindowOverlay();
  }

  @override
  @pragma("vm:entry-point")
  onMainWindowDestroyed(KDDWBindingsCore.MainWindow? mw) {
    final oldSize = mainWindows.length;
    mainWindows.removeWhere((it) => it.thisCpp == mw!.thisCpp);
    if (oldSize != mainWindows.length) rebuildWindowOverlay();
  }

  @override
  @pragma("vm:entry-point")
  onDropIndicatorOverlayCreated(KDDWBindingsFlutter.IndicatorWindow? w) {
    indicatorWindows.add(w!);
    rebuildWindowOverlay();
  }

  @override
  @pragma("vm:entry-point")
  onDropIndicatorOverlayDestroyed(KDDWBindingsFlutter.IndicatorWindow? w) {
    final oldSize = indicatorWindows.length;
    indicatorWindows.removeWhere((it) => it.thisCpp == w!.thisCpp);
    if (oldSize != indicatorWindows.length) rebuildWindowOverlay();
  }

  void raiseFloatingWindow(KDDWBindingsCore.FloatingWindow fw) {
    final int oldSize = floatingWindows.length;

    floatingWindows.removeWhere((it) => it.thisCpp == fw.thisCpp);
    if (oldSize == floatingWindows.length) {
      print("raiseFloatingWindow: Failed to find floating window");
    } else {
      floatingWindows.add(fw);
      rebuildWindowOverlay();
    }
  }

  @override
  @pragma("vm:entry-point")
  void rebuildWindowOverlay() {
    WindowOverlayWidget.globalKey().currentState?.onWindowCountChanged();
  }

  @override
  @pragma("vm:entry-point")
  void dumpManagedBacktrace() {
    print(StackTrace.current);
  }

  @override
  @pragma("vm:entry-point")
  void pauseForDartDebugger() {
    print("pauseForDartDebugger");
    debugger();
  }

  @override
  @pragma("vm:entry-point")
  void runDelayed(int ms, KDDWBindingsCore.DelayedCall? c) {
    if (c != null)
      Future.delayed(Duration(milliseconds: ms), () {
        c.call();
        c.release();
      });
  }
}

class GenericView extends KDDWBindingsFlutter.View with View_mixin {
  GenericView(
      KDDWBindingsCore.Controller? controller, KDDWBindingsCore.View? parent)
      : super(controller, 0, parent) {
    m_fillsParent = true;
    initMixin(this, debugName: "GenericView", parent: parent);
  }
}
