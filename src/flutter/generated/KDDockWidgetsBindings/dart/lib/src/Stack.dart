/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

class Stack extends Controller {
  Stack.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Stack.init() : super.init() {}
  factory Stack.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Stack;
    }
    return Stack.fromCppPointer(cppPointer, needsAutoDelete);
  } // addDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)
  addDockWidget(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__addDockWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // contains(KDDockWidgets::Controllers::DockWidget * dw) const

  bool contains(DockWidget? dw) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__contains_DockWidget')
        .asFunction();
    return func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp) != 0;
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // group() const

  Group group() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__group')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // insertDockWidget(KDDockWidgets::Controllers::DockWidget * dockwidget, int index)

  bool insertDockWidget(DockWidget? dockwidget, int index) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__insertDockWidget_DockWidget_int')
        .asFunction();
    return func(thisCpp, dockwidget == null ? ffi.nullptr : dockwidget.thisCpp,
            index) !=
        0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1126))
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
            cFunctionSymbolName(1127))
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
            cFunctionSymbolName(1129))
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
            'c_KDDockWidgets__Controllers__Stack__numDockWidgets')
        .asFunction();
    return func(thisCpp);
  } // onMouseDoubleClick(QPoint localPos)

  bool onMouseDoubleClick(QPoint localPos) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__onMouseDoubleClick_QPoint')
        .asFunction();
    return func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp) !=
        0;
  } // setDocumentMode(bool arg__1)

  setDocumentMode(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__setDocumentMode_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // setTabBarAutoHide(bool arg__1)

  setTabBarAutoHide(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__setTabBarAutoHide_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // singleDockWidget() const

  DockWidget singleDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1141))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
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

  TabBar tabBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__tabBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TabBar.fromCppPointer(result, false);
  } // tabBarAutoHide() const

  bool tabBarAutoHide() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__tabBarAutoHide')
        .asFunction();
    return func(thisCpp) != 0;
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__Stack__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__Stack__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__Stack__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__Stack__eventFilter_QObject_QEvent";
      case 1126:
        return "c_KDDockWidgets__Controllers__Stack__isMDI";
      case 1127:
        return "c_KDDockWidgets__Controllers__Stack__isPositionDraggable_QPoint";
      case 1129:
        return "c_KDDockWidgets__Controllers__Stack__isWindow";
      case 826:
        return "c_KDDockWidgets__Controllers__Stack__setParentView_impl_View";
      case 1141:
        return "c_KDDockWidgets__Controllers__Stack__singleDockWidget";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 1126:
        return "isMDI";
      case 1127:
        return "isPositionDraggable";
      case 1129:
        return "isWindow";
      case 826:
        return "setParentView_impl";
      case 1141:
        return "singleDockWidget";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__Stack__registerVirtualMethodCallback')
        .asFunction();
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    const callbackExcept306 = 0;
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
    const callbackExcept307 = 0;
    final callback307 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept307);
    registerCallback(thisCpp, callback307, 307);
    const callbackExcept1126 = 0;
    final callback1126 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Stack.isMDI_calledFromC, callbackExcept1126);
    registerCallback(thisCpp, callback1126, 1126);
    const callbackExcept1127 = 0;
    final callback1127 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Stack.isPositionDraggable_calledFromC, callbackExcept1127);
    registerCallback(thisCpp, callback1127, 1127);
    const callbackExcept1129 = 0;
    final callback1129 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Stack.isWindow_calledFromC, callbackExcept1129);
    registerCallback(thisCpp, callback1129, 1129);
    final callback826 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback826, 826);
    final callback1141 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Stack.singleDockWidget_calledFromC);
    registerCallback(thisCpp, callback1141, 1141);
  }
}
