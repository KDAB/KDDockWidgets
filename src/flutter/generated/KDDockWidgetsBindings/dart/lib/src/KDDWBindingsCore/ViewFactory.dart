/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import '../TypeHelpers.dart';
import '../../Bindings.dart';
import '../../Bindings_KDDWBindingsCore.dart' as KDDWBindingsCore;
import '../../Bindings_KDDWBindingsFlutter.dart' as KDDWBindingsFlutter;
import '../../LibraryLoader.dart';

var _dylib = Library.instance().dylib;

class ViewFactory extends KDDWBindingsCore.Object {
  ViewFactory.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  ViewFactory.init() : super.init() {}
  factory ViewFactory.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.Object.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.Object.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as ViewFactory;
    }
    return ViewFactory.fromCppPointer(cppPointer, needsAutoDelete);
  } //ViewFactory()
  ViewFactory() : super.init() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Core__ViewFactory__constructor')
        .asFunction();
    thisCpp = func();
    KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // createClassicIndicatorWindow(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent) const
  KDDWBindingsCore.ClassicIndicatorWindowViewInterface
      createClassicIndicatorWindow(
          KDDWBindingsCore.ClassicDropIndicatorOverlay? arg__1,
          {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(622))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.ClassicIndicatorWindowViewInterface.fromCppPointer(
        result, false);
  }

  static ffi.Pointer<void> createClassicIndicatorWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createClassicIndicatorWindow(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.ClassicDropIndicatorOverlay.fromCppPointer(
                arg__1),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const

  KDDWBindingsCore.View createDockWidget(String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0, int windowFlags = 0}) {
    final voidstar_Func_voidstar_voidstar_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(623))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        uniqueName?.toNativeUtf8() ?? ffi.nullptr,
        options,
        layoutSaverOptions,
        windowFlags);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? uniqueName,
      int options,
      int layoutSaverOptions,
      int windowFlags) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDockWidget(
        QString.fromCppPointer(uniqueName).toDartString(),
        options: options,
        layoutSaverOptions: layoutSaverOptions,
        windowFlags: windowFlags);
    return result.thisCpp;
  } // createDropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createDropArea(
      KDDWBindingsCore.DropArea? arg__1, KDDWBindingsCore.View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(624))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createDropArea_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createDropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDropArea(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.DropArea.fromCppPointer(arg__1),
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createFloatingWindow(KDDockWidgets::Core::FloatingWindow * controller, KDDockWidgets::Core::MainWindow * parent, Qt::WindowFlags windowFlags) const

  KDDWBindingsCore.View createFloatingWindow(
      KDDWBindingsCore.FloatingWindow? controller,
      {required KDDWBindingsCore.MainWindow? parent,
      int windowFlags = 0}) {
    final voidstar_Func_voidstar_voidstar_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(625))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp,
        windowFlags);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createFloatingWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller,
      ffi.Pointer<void>? parent,
      int windowFlags) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createFloatingWindow(KDDockWidgets::Core::FloatingWindow * controller, KDDockWidgets::Core::MainWindow * parent, Qt::WindowFlags windowFlags) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createFloatingWindow(
        (controller == null || controller.address == 0)
            ? null
            : KDDWBindingsCore.FloatingWindow.fromCppPointer(controller),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.MainWindow.fromCppPointer(parent),
        windowFlags: windowFlags);
    return result.thisCpp;
  } // createGroup(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createGroup(KDDWBindingsCore.Group? arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(626))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createGroup_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createGroup(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createGroup(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.Group.fromCppPointer(arg__1),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createRubberBand(KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createRubberBand(KDDWBindingsCore.View? parent) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(627))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createRubberBand_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createRubberBand(KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createRubberBand(
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createSeparator(KDDockWidgets::Core::Separator * arg__1, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createSeparator(KDDWBindingsCore.Separator? arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(628))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createSeparator_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createSeparator(KDDockWidgets::Core::Separator * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createSeparator(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.Separator.fromCppPointer(arg__1),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createSideBar(KDDockWidgets::Core::SideBar * arg__1, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createSideBar(
      KDDWBindingsCore.SideBar? arg__1, KDDWBindingsCore.View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(629))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createSideBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createSideBar(KDDockWidgets::Core::SideBar * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createSideBar(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.SideBar.fromCppPointer(arg__1),
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createStack(KDDockWidgets::Core::Stack * stack, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createStack(
      KDDWBindingsCore.Stack? stack, KDDWBindingsCore.View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(630))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        stack == null ? ffi.nullptr : stack.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createStack_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? stack, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createStack(KDDockWidgets::Core::Stack * stack, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createStack(
        (stack == null || stack.address == 0)
            ? null
            : KDDWBindingsCore.Stack.fromCppPointer(stack),
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createTabBar(KDDockWidgets::Core::TabBar * tabBar, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createTabBar(KDDWBindingsCore.TabBar? tabBar,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(631))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        tabBar == null ? ffi.nullptr : tabBar.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createTabBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? tabBar, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createTabBar(KDDockWidgets::Core::TabBar * tabBar, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createTabBar(
        (tabBar == null || tabBar.address == 0)
            ? null
            : KDDWBindingsCore.TabBar.fromCppPointer(tabBar),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // createTitleBar(KDDockWidgets::Core::TitleBar * controller, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createTitleBar(
      KDDWBindingsCore.TitleBar? controller, KDDWBindingsCore.View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(632))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createTitleBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createTitleBar(KDDockWidgets::Core::TitleBar * controller, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createTitleBar(
        (controller == null || controller.address == 0)
            ? null
            : KDDWBindingsCore.TitleBar.fromCppPointer(controller),
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ViewFactory__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 622:
        return "c_KDDockWidgets__Core__ViewFactory__createClassicIndicatorWindow_ClassicDropIndicatorOverlay_View";
      case 623:
        return "c_KDDockWidgets__Core__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags";
      case 624:
        return "c_KDDockWidgets__Core__ViewFactory__createDropArea_DropArea_View";
      case 625:
        return "c_KDDockWidgets__Core__ViewFactory__createFloatingWindow_FloatingWindow_MainWindow_WindowFlags";
      case 626:
        return "c_KDDockWidgets__Core__ViewFactory__createGroup_Group_View";
      case 627:
        return "c_KDDockWidgets__Core__ViewFactory__createRubberBand_View";
      case 628:
        return "c_KDDockWidgets__Core__ViewFactory__createSeparator_Separator_View";
      case 629:
        return "c_KDDockWidgets__Core__ViewFactory__createSideBar_SideBar_View";
      case 630:
        return "c_KDDockWidgets__Core__ViewFactory__createStack_Stack_View";
      case 631:
        return "c_KDDockWidgets__Core__ViewFactory__createTabBar_TabBar_View";
      case 632:
        return "c_KDDockWidgets__Core__ViewFactory__createTitleBar_TitleBar_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 622:
        return "createClassicIndicatorWindow";
      case 623:
        return "createDockWidget";
      case 624:
        return "createDropArea";
      case 625:
        return "createFloatingWindow";
      case 626:
        return "createGroup";
      case 627:
        return "createRubberBand";
      case 628:
        return "createSeparator";
      case 629:
        return "createSideBar";
      case 630:
        return "createStack";
      case 631:
        return "createTabBar";
      case 632:
        return "createTitleBar";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__ViewFactory__registerVirtualMethodCallback')
        .asFunction();
    final callback622 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_FFI>(
        KDDWBindingsCore.ViewFactory.createClassicIndicatorWindow_calledFromC);
    registerCallback(thisCpp, callback622, 622);
    final callback623 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>(
        KDDWBindingsCore.ViewFactory.createDockWidget_calledFromC);
    registerCallback(thisCpp, callback623, 623);
    final callback624 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createDropArea_calledFromC);
    registerCallback(thisCpp, callback624, 624);
    final callback625 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_FFI>(
        KDDWBindingsCore.ViewFactory.createFloatingWindow_calledFromC);
    registerCallback(thisCpp, callback625, 625);
    final callback626 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createGroup_calledFromC);
    registerCallback(thisCpp, callback626, 626);
    final callback627 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createRubberBand_calledFromC);
    registerCallback(thisCpp, callback627, 627);
    final callback628 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createSeparator_calledFromC);
    registerCallback(thisCpp, callback628, 628);
    final callback629 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createSideBar_calledFromC);
    registerCallback(thisCpp, callback629, 629);
    final callback630 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createStack_calledFromC);
    registerCallback(thisCpp, callback630, 630);
    final callback631 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createTabBar_calledFromC);
    registerCallback(thisCpp, callback631, 631);
    final callback632 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.ViewFactory.createTitleBar_calledFromC);
    registerCallback(thisCpp, callback632, 632);
  }
}
