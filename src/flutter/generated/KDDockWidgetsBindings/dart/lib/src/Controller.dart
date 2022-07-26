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

class Controller extends QObject {
//tag=1064
  Controller.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Controller.init() : super.init() {}
//tag=1062
  factory Controller.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Controller;
    }
    return Controller.fromCppPointer(cppPointer, needsAutoDelete);
  }
//tag=1024

//tag=1027
// close()
  bool close() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__close')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1035
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Controller;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Controller::customEvent(QEvent * event)! (${thisCpp.address})");
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
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Controller;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Controller::event(QEvent * event)! (${thisCpp.address})");
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
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Controller;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Controller::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// geometry() const
  QRect geometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__geometry')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// height() const
  int height() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__height')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// inDtor() const
  bool inDtor() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__inDtor')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isVisible() const
  bool isVisible() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__isVisible')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// mapToGlobal(QPoint arg__1) const
  QPoint mapToGlobal(QPoint arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__mapToGlobal_QPoint')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// parentViewChanged(KDDockWidgets::View * parent)
  parentViewChanged(View? parent) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__parentViewChanged_View')
        .asFunction();
//tag=1030
    func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
  }

//tag=1077
  void onParentViewChanged(Function callback, {QObject? context}) {
    final SignalHandler func = _dylib
        .lookup<ffi.NativeFunction<SignalHandler_FFI>>(
            'c_KDDockWidgets__Controller__onParentViewChanged_View')
        .asFunction();
    final dartCallback =
        ffi.Pointer.fromFunction<ffi.Void Function(ffi.Pointer<void>)>(
            onParentViewChanged_callback);
    final callbackMethod = onParentViewChanged_callback;
    var handlers = signalHandlerersBySignal[callbackMethod] ?? [];
    handlers.add(callback);
    signalHandlerersBySignal[callbackMethod] = handlers;
    ffi.Pointer<void> contextPtr =
        context == null ? ffi.nullptr : context.thisCpp;
    func(thisCpp, contextPtr, dartCallback);
  }

  static void onParentViewChanged_callback(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Controller;
    final signalHandlers =
        dartInstance.signalHandlerersBySignal[onParentViewChanged_callback] ??
            [];
    for (var signalHandler in signalHandlers) {
      signalHandler();
    }
  }
//tag=1024

//tag=1027
// pos() const
  QPoint pos() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__pos')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// rect() const
  QRect rect() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__rect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// setParentView(KDDockWidgets::View * parent)
  setParentView(View? parent) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__setParentView_View')
        .asFunction();
//tag=1030
    func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
  }
//tag=1024

//tag=1027
// setParentView_impl(KDDockWidgets::View * parent)
  setParentView_impl(View? parent) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(690))
        .asFunction();
//tag=1030
    func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
  }

//tag=1035
  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Controller;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Controller::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  }
//tag=1024

//tag=1027
// setVisible(bool arg__1)
  setVisible(bool arg__1) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controller__setVisible_bool')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 ? 1 : 0);
  }
//tag=1024

//tag=1027
// show() const
  show() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__show')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// size() const
  QSize size() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__size')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
//tag=1028
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controller__tr_char_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// view() const
  View view() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__view')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return View.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// width() const
  int width() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__width')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// x() const
  int x() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__x')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// y() const
  int y() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__y')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controller__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 294:
        return "c_KDDockWidgets__Controller__customEvent_QEvent";
      case 305:
        return "c_KDDockWidgets__Controller__event_QEvent";
      case 306:
        return "c_KDDockWidgets__Controller__eventFilter_QObject_QEvent";
      case 690:
        return "c_KDDockWidgets__Controller__setParentView_impl_View";
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
      case 690:
        return "setParentView_impl";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controller__registerVirtualMethodCallback')
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
    final callback690 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback690, 690);
  }
}
