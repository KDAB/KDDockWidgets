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
import '../../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class Stack extends KDDWBindingsCore.Controller {
  Stack.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Stack.init() : super.init() {}
  factory Stack.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Stack;
    }
    return Stack.fromCppPointer(cppPointer, needsAutoDelete);
  } // addDockWidget(KDDockWidgets::Core::DockWidget * arg__1)
  addDockWidget(KDDWBindingsCore.DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__addDockWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // contains(KDDockWidgets::Core::DockWidget * dw) const

  bool contains(KDDWBindingsCore.DockWidget? dw) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__contains_DockWidget')
        .asFunction();
    return func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp) != 0;
  } // group() const

  KDDWBindingsCore.Group group() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__group')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // insertDockWidget(KDDockWidgets::Core::DockWidget * dockwidget, int index)

  bool insertDockWidget(KDDWBindingsCore.DockWidget? dockwidget, int index) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__Stack__insertDockWidget_DockWidget_int')
        .asFunction();
    return func(thisCpp, dockwidget == null ? ffi.nullptr : dockwidget.thisCpp,
            index) !=
        0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1221))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMDI_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isMDI() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMDI();
    return result ? 1 : 0;
  } // isPositionDraggable(QPoint p) const

  bool isPositionDraggable(QPoint p) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1222))
        .asFunction();
    return func(thisCpp, p == null ? ffi.nullptr : p.thisCpp) != 0;
  }

  static int isPositionDraggable_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> p) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isPositionDraggable(QPoint p) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isPositionDraggable(QPoint.fromCppPointer(p));
    return result ? 1 : 0;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1224))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // numDockWidgets() const

  int numDockWidgets() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__numDockWidgets')
        .asFunction();
    return func(thisCpp);
  } // onMouseDoubleClick(QPoint localPos)

  bool onMouseDoubleClick(QPoint localPos) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__onMouseDoubleClick_QPoint')
        .asFunction();
    return func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp) !=
        0;
  } // setDocumentMode(bool arg__1)

  setDocumentMode(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__Stack__setDocumentMode_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  } // setTabBarAutoHide(bool arg__1)

  setTabBarAutoHide(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__Stack__setTabBarAutoHide_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // singleDockWidget() const

  KDDWBindingsCore.DockWidget singleDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1236))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DockWidget.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> singleDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::singleDockWidget() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.singleDockWidget();
    return result.thisCpp;
  } // tabBar() const

  KDDWBindingsCore.TabBar tabBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__tabBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.TabBar.fromCppPointer(result, false);
  } // tabBarAutoHide() const

  bool tabBarAutoHide() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__tabBarAutoHide')
        .asFunction();
    return func(thisCpp) != 0;
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__Stack__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Stack__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 1221:
        return "c_KDDockWidgets__Core__Stack__isMDI";
      case 1222:
        return "c_KDDockWidgets__Core__Stack__isPositionDraggable_QPoint";
      case 1224:
        return "c_KDDockWidgets__Core__Stack__isWindow";
      case 899:
        return "c_KDDockWidgets__Core__Stack__setParentView_impl_View";
      case 1236:
        return "c_KDDockWidgets__Core__Stack__singleDockWidget";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1221:
        return "isMDI";
      case 1222:
        return "isPositionDraggable";
      case 1224:
        return "isWindow";
      case 899:
        return "setParentView_impl";
      case 1236:
        return "singleDockWidget";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__Stack__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept1221 = 0;
    final callback1221 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Stack.isMDI_calledFromC, callbackExcept1221);
    registerCallback(thisCpp, callback1221, 1221);
    const callbackExcept1222 = 0;
    final callback1222 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Stack.isPositionDraggable_calledFromC,
            callbackExcept1222);
    registerCallback(thisCpp, callback1222, 1222);
    const callbackExcept1224 = 0;
    final callback1224 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Stack.isWindow_calledFromC, callbackExcept1224);
    registerCallback(thisCpp, callback1224, 1224);
    final callback899 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback899, 899);
    final callback1236 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Stack.singleDockWidget_calledFromC);
    registerCallback(thisCpp, callback1236, 1236);
  }
}
