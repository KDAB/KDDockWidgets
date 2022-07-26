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

class DropArea extends Layout {
//tag=1064
  DropArea.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DropArea.init() : super.init() {}
//tag=1062
  factory DropArea.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DropArea;
    }
    return DropArea.fromCppPointer(cppPointer, needsAutoDelete);
  }
//tag=1023
//DropArea(KDDockWidgets::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
  DropArea(View? parent, int options, {bool isMDIWrapper = false})
      : super.init() {
//tag=1075
    final voidstar_Func_voidstar_int_bool func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp, options,
        isMDIWrapper ? 1 : 0);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// availableSize() const
  QSize availableSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__availableSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1035
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::customEvent(QEvent * event)! (${thisCpp.address})");
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
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::event(QEvent * event)! (${thisCpp.address})");
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
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// hasSingleFloatingFrame() const
  bool hasSingleFloatingFrame() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// hasSingleFrame() const
  bool hasSingleFrame() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__hasSingleFrame')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isMDIWrapper() const
  bool isMDIWrapper() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__isMDIWrapper')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// layoutEqually()
  layoutEqually() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__layoutEqually')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// removeHover()
  removeHover() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__removeHover')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1035
  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  }

//tag=1024
  static
//tag=1027
// tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
//tag=1028
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// updateFloatingActions()
  updateFloatingActions() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__updateFloatingActions')
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 294:
        return "c_KDDockWidgets__Controllers__DropArea__customEvent_QEvent";
      case 305:
        return "c_KDDockWidgets__Controllers__DropArea__event_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__DropArea__eventFilter_QObject_QEvent";
      case 692:
        return "c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 294:
        return "customEvent";
      case 305:
        return "event";
      case 306:
        return "eventFilter";
      case 692:
        return "setParentView_impl";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback')
        .asFunction();

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
//tag=1021
    final callback692 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback692, 692);
  }
}
