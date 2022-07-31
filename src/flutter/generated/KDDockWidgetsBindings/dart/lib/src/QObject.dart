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
final _finalizer =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_QObject_Finalizer');

class QObject {
  Map<Function, List<Function>> signalHandlerersBySignal = {};

//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, QObject>();
  var _thisCpp = null;
  bool _needsAutoDelete = false;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete)
      newWeakPersistentHandle?.call(this, ptrvoid, 0, _finalizer);
  }

  static bool isCached(var cppPointer) {
//tag=1024
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

//tag=1061
  factory QObject.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QObject.fromCppPointer(cppPointer, needsAutoDelete)) as QObject;
  }
  QObject.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  QObject.init() {}
//tag=1023
//QObject(QObject * parent)
  QObject({required QObject? parent}) {
//tag=1075
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QObject__constructor_QObject')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// blockSignals(bool b)
  bool blockSignals(bool b) {
//tag=1028
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            'c_QObject__blockSignals_bool')
        .asFunction();
//tag=1029
    return func(thisCpp, b ? 1 : 0) != 0;
  }
//tag=1024

//tag=1027
// children() const
  QList children() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QObject__children')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QList<QObject>.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// customEvent(QEvent * event)
  customEvent(QEvent? event) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(295))
        .asFunction();
//tag=1030
    func(thisCpp, event == null ? ffi.nullptr : event.thisCpp);
  }

//tag=1035
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for QObject::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }
//tag=1024

//tag=1027
// deleteLater()
  deleteLater() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QObject__deleteLater')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// destroyed(QObject * arg__1)
  destroyed({required QObject? arg__1}) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QObject__destroyed_QObject')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// disconnect(const QObject * receiver, const char * member) const
  bool disconnect(QObject? receiver, {String? member}) {
//tag=1028
    final bool_Func_voidstar_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_string_FFI>>(
            'c_QObject__disconnect_QObject_char')
        .asFunction();
//tag=1029
    return func(thisCpp, receiver == null ? ffi.nullptr : receiver.thisCpp,
            member?.toNativeUtf8() ?? ffi.nullptr) !=
        0;
  }

//tag=1024
  static
//tag=1027
// disconnect(const QObject * sender, const char * signal, const QObject * receiver, const char * member)
      bool disconnect_2(
          QObject? sender, String? signal, QObject? receiver, String? member) {
//tag=1028
    final bool_Func_voidstar_string_voidstar_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_string_voidstar_string_FFI>>(
            'c_static_QObject__disconnect_QObject_char_QObject_char')
        .asFunction();
//tag=1029
    return func(
            sender == null ? ffi.nullptr : sender.thisCpp,
            signal?.toNativeUtf8() ?? ffi.nullptr,
            receiver == null ? ffi.nullptr : receiver.thisCpp,
            member?.toNativeUtf8() ?? ffi.nullptr) !=
        0;
  }
//tag=1024

//tag=1027
// disconnect(const char * signal, const QObject * receiver, const char * member) const
  bool disconnect_3(
      {String? signal, required QObject? receiver, String? member}) {
//tag=1028
    final bool_Func_voidstar_string_voidstar_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_string_voidstar_string_FFI>>(
            'c_QObject__disconnect_char_QObject_char')
        .asFunction();
//tag=1029
    return func(
            thisCpp,
            signal?.toNativeUtf8() ?? ffi.nullptr,
            receiver == null ? ffi.nullptr : receiver.thisCpp,
            member?.toNativeUtf8() ?? ffi.nullptr) !=
        0;
  }
//tag=1024

//tag=1027
// dumpObjectInfo()
  dumpObjectInfo() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QObject__dumpObjectInfo')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// dumpObjectTree()
  dumpObjectTree() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QObject__dumpObjectTree')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// dynamicPropertyNames() const
  QList dynamicPropertyNames() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QObject__dynamicPropertyNames')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QList<QByteArray>.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// event(QEvent * event)
  bool event(QEvent? event) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(306))
        .asFunction();
//tag=1029
    return func(thisCpp, event == null ? ffi.nullptr : event.thisCpp) != 0;
  }

//tag=1035
  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for QObject::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// eventFilter(QObject * watched, QEvent * event)
  bool eventFilter(QObject? watched, QEvent? event) {
//tag=1028
    final bool_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(307))
        .asFunction();
//tag=1029
    return func(thisCpp, watched == null ? ffi.nullptr : watched.thisCpp,
            event == null ? ffi.nullptr : event.thisCpp) !=
        0;
  }

//tag=1035
  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for QObject::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// inherits(const char * classname) const
  bool inherits(String? classname) {
//tag=1028
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QObject__inherits_char')
        .asFunction();
//tag=1029
    return func(thisCpp, classname?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// installEventFilter(QObject * filterObj)
  installEventFilter(QObject? filterObj) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QObject__installEventFilter_QObject')
        .asFunction();
//tag=1030
    func(thisCpp, filterObj == null ? ffi.nullptr : filterObj.thisCpp);
  }
//tag=1024

//tag=1027
// isWidgetType() const
  bool isWidgetType() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QObject__isWidgetType')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isWindowType() const
  bool isWindowType() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QObject__isWindowType')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// killTimer(int id)
  killTimer(int id) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QObject__killTimer_int')
        .asFunction();
//tag=1030
    func(thisCpp, id);
  }
//tag=1024

//tag=1027
// objectName() const
  QString objectName() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QObject__objectName')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// parent() const
  QObject parent() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QObject__parent')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QObject.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// receivers(const char * signal) const
  int receivers(String? signal) {
//tag=1028
    final int_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_FFI>>(
            'c_QObject__receivers_char')
        .asFunction();
//tag=1031
    return func(thisCpp, signal?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// removeEventFilter(QObject * obj)
  removeEventFilter(QObject? obj) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QObject__removeEventFilter_QObject')
        .asFunction();
//tag=1030
    func(thisCpp, obj == null ? ffi.nullptr : obj.thisCpp);
  }
//tag=1024

//tag=1027
// sender() const
  QObject sender() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QObject__sender')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QObject.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// senderSignalIndex() const
  int senderSignalIndex() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QObject__senderSignalIndex')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// setObjectName(const QString & name)
  setObjectName(String? name) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QObject__setObjectName_QString')
        .asFunction();
//tag=1030
    func(thisCpp, name?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// setParent(QObject * parent)
  setParent(QObject? parent) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QObject__setParent_QObject')
        .asFunction();
//tag=1030
    func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
  }
//tag=1024

//tag=1027
// signalsBlocked() const
  bool signalsBlocked() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QObject__signalsBlocked')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// startTimer(int interval)
  int startTimer(int interval) {
//tag=1028
    final int_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
            'c_QObject__startTimer_int')
        .asFunction();
//tag=1031
    return func(thisCpp, interval);
  }

//tag=1024
  static
//tag=1027
// tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
//tag=1028
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_QObject__tr_char_char_int')
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
            'c_QObject__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_QObject__customEvent_QEvent";
      case 306:
        return "c_QObject__event_QEvent";
      case 307:
        return "c_QObject__eventFilter_QObject_QEvent";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_QObject__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    const callbackExcept306 = 0;
//tag=1021
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
    const callbackExcept307 = 0;
//tag=1021
    final callback307 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept307);
    registerCallback(thisCpp, callback307, 307);
  }
}
