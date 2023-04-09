/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class ViewFactory_flutter extends ViewFactory {
  ViewFactory_flutter.fromCppPointer(var cppPointer,
      [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  ViewFactory_flutter.init() : super.init() {}
  factory ViewFactory_flutter.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as ViewFactory_flutter;
    }
    return ViewFactory_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  } //ViewFactory_flutter()
  ViewFactory_flutter() : super.init() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__ViewFactory_flutter__constructor')
        .asFunction();
    thisCpp = func();
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static ffi.Pointer<void> createClassicIndicatorWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createClassicIndicatorWindow(KDDockWidgets::Core::ClassicIndicators * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance
        .createClassicIndicatorWindow(ClassicIndicators.fromCppPointer(arg__1));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? uniqueName,
      int arg__2,
      int arg__3,
      int arg__4) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> arg__2, QFlags<KDDockWidgets::LayoutSaverOption> arg__3, Qt::WindowFlags arg__4) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDockWidget(
        QString.fromCppPointer(uniqueName).toDartString(),
        options: arg__2,
        layoutSaverOptions: arg__3,
        windowFlags: arg__4);
    return result.thisCpp;
  }

  static ffi.Pointer<void> createDropArea_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createDropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDropArea(
        DropArea.fromCppPointer(arg__1), View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createFloatingWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1,
      ffi.Pointer<void>? parent,
      int windowFlags) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createFloatingWindow(KDDockWidgets::Core::FloatingWindow * arg__1, KDDockWidgets::Core::MainWindow * parent, Qt::WindowFlags windowFlags) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createFloatingWindow(
        FloatingWindow.fromCppPointer(arg__1),
        parent: MainWindow.fromCppPointer(parent),
        windowFlags: windowFlags);
    return result.thisCpp;
  }

  static ffi.Pointer<void> createGroup_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createGroup(KDDockWidgets::Core::Group * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createGroup(Group.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createRubberBand_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createRubberBand(KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createRubberBand(View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createSeparator_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createSeparator(KDDockWidgets::Core::Separator * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createSeparator(
        Separator.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createSideBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createSideBar(KDDockWidgets::Core::SideBar * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createSideBar(
        SideBar.fromCppPointer(arg__1), View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createStack_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createStack(KDDockWidgets::Core::Stack * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createStack(
        Stack.fromCppPointer(arg__1), View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createTabBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? tabBar, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createTabBar(KDDockWidgets::Core::TabBar * tabBar, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createTabBar(TabBar.fromCppPointer(tabBar),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> createTitleBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory_flutter::createTitleBar(KDDockWidgets::Core::TitleBar * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createTitleBar(
        TitleBar.fromCppPointer(arg__1), View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__ViewFactory_flutter__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__ViewFactory_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 675:
        return "c_KDDockWidgets__ViewFactory_flutter__createClassicIndicatorWindow_ClassicIndicators";
      case 676:
        return "c_KDDockWidgets__ViewFactory_flutter__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags";
      case 677:
        return "c_KDDockWidgets__ViewFactory_flutter__createDropArea_DropArea_View";
      case 678:
        return "c_KDDockWidgets__ViewFactory_flutter__createFloatingWindow_FloatingWindow_MainWindow_WindowFlags";
      case 679:
        return "c_KDDockWidgets__ViewFactory_flutter__createGroup_Group_View";
      case 680:
        return "c_KDDockWidgets__ViewFactory_flutter__createRubberBand_View";
      case 681:
        return "c_KDDockWidgets__ViewFactory_flutter__createSeparator_Separator_View";
      case 682:
        return "c_KDDockWidgets__ViewFactory_flutter__createSideBar_SideBar_View";
      case 683:
        return "c_KDDockWidgets__ViewFactory_flutter__createStack_Stack_View";
      case 684:
        return "c_KDDockWidgets__ViewFactory_flutter__createTabBar_TabBar_View";
      case 685:
        return "c_KDDockWidgets__ViewFactory_flutter__createTitleBar_TitleBar_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 675:
        return "createClassicIndicatorWindow";
      case 676:
        return "createDockWidget";
      case 677:
        return "createDropArea";
      case 678:
        return "createFloatingWindow";
      case 679:
        return "createGroup";
      case 680:
        return "createRubberBand";
      case 681:
        return "createSeparator";
      case 682:
        return "createSideBar";
      case 683:
        return "createStack";
      case 684:
        return "createTabBar";
      case 685:
        return "createTitleBar";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__ViewFactory_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback675 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createClassicIndicatorWindow_calledFromC);
    registerCallback(thisCpp, callback675, 675);
    final callback676 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>(
        ViewFactory_flutter.createDockWidget_calledFromC);
    registerCallback(thisCpp, callback676, 676);
    final callback677 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createDropArea_calledFromC);
    registerCallback(thisCpp, callback677, 677);
    final callback678 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_FFI>(
        ViewFactory_flutter.createFloatingWindow_calledFromC);
    registerCallback(thisCpp, callback678, 678);
    final callback679 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createGroup_calledFromC);
    registerCallback(thisCpp, callback679, 679);
    final callback680 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createRubberBand_calledFromC);
    registerCallback(thisCpp, callback680, 680);
    final callback681 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createSeparator_calledFromC);
    registerCallback(thisCpp, callback681, 681);
    final callback682 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createSideBar_calledFromC);
    registerCallback(thisCpp, callback682, 682);
    final callback683 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createStack_calledFromC);
    registerCallback(thisCpp, callback683, 683);
    final callback684 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createTabBar_calledFromC);
    registerCallback(thisCpp, callback684, 684);
    final callback685 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory_flutter.createTitleBar_calledFromC);
    registerCallback(thisCpp, callback685, 685);
  }
}
