/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1052
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

//tag=1051
var _dylib = Library.instance().dylib;

class ViewFactory extends QObject {
//tag=1064
  ViewFactory.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  ViewFactory.init() : super.init() {}
//tag=1062
  factory ViewFactory.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as ViewFactory;
    }
    return ViewFactory.fromCppPointer(cppPointer, needsAutoDelete);
  }
//tag=1023
//ViewFactory()
  ViewFactory() : super.init() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__ViewFactory__constructor')
        .asFunction();
    thisCpp = func();
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// createRubberBand(KDDockWidgets::View * parent) const
  View createRubberBand(View? parent) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(589))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> createRubberBand_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createRubberBand(KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.createRubberBand(View.fromCppPointer(parent));
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }
//tag=1024

//tag=1035
  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

//tag=1024
  static
//tag=1027
// tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
//tag=1028
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__ViewFactory__tr_char_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__ViewFactory__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 589:
        return "c_KDDockWidgets__ViewFactory__createRubberBand_View";
      case 294:
        return "c_KDDockWidgets__ViewFactory__customEvent_QEvent";
      case 305:
        return "c_KDDockWidgets__ViewFactory__event_QEvent";
      case 306:
        return "c_KDDockWidgets__ViewFactory__eventFilter_QObject_QEvent";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 589:
        return "createRubberBand";
      case 294:
        return "customEvent";
      case 305:
        return "event";
      case 306:
        return "eventFilter";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback589 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            ViewFactory.createRubberBand_calledFromC);
    registerCallback(thisCpp, callback589, 589);
//tag=1021
    final callback294 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback294, 294);
    const callbackExcept305 = 0;
//tag=1021
    final callback305 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept305);
    registerCallback(thisCpp, callback305, 305);
    const callbackExcept306 = 0;
//tag=1021
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
  }
}
