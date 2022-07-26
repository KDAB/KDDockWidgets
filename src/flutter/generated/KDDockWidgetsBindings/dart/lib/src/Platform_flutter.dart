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
        'c_KDDockWidgets__Platform_flutter_Finalizer');

class Platform_flutter {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, Platform_flutter>();
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
  factory Platform_flutter.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
            Platform_flutter.fromCppPointer(cppPointer, needsAutoDelete))
        as Platform_flutter;
  }
  Platform_flutter.fromCppPointer(var cppPointer,
      [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  Platform_flutter.init() {}
//tag=1023
//Platform_flutter()
  Platform_flutter() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Platform_flutter__constructor')
        .asFunction();
    thisCpp = func();
    Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// applicationName() const
  QString applicationName() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(591))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> applicationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::applicationName() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.applicationName();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const
  View createView(Controller? controller, {required View? parent}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(592))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> createView_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller, ffi.Pointer<void>? parent) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.createView(
        Controller.fromCppPointer(controller),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// hasActivePopup() const
  bool hasActivePopup() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(593))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int hasActivePopup_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::hasActivePopup() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.hasActivePopup();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// inDisallowedDragView(QPoint globalPos) const
  bool inDisallowedDragView(QPoint globalPos) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(594))
        .asFunction();
//tag=1029
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp) !=
        0;
  }

//tag=1035
  static int inDisallowedDragView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::inDisallowedDragView(QPoint globalPos) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result =
        dartInstance.inDisallowedDragView(QPoint.fromCppPointer(globalPos));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// init()
  init() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform_flutter__init')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// installMessageHandler()
  installMessageHandler() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(596))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void installMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::installMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.installMessageHandler();
  }
//tag=1024

//tag=1027
// isLeftMouseButtonPressed() const
  bool isLeftMouseButtonPressed() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(597))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isLeftMouseButtonPressed_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::isLeftMouseButtonPressed() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isLeftMouseButtonPressed();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isProcessingAppQuitEvent() const
  bool isProcessingAppQuitEvent() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(598))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isProcessingAppQuitEvent_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::isProcessingAppQuitEvent() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isProcessingAppQuitEvent();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// name() const
  String name() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            cFunctionSymbolName(599))
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }

//tag=1035
  static ffi.Pointer<Utf8> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::name() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.name();
    return result.toNativeUtf8();
  }
//tag=1024

//tag=1027
// organizationName() const
  QString organizationName() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(600))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> organizationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::organizationName() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.organizationName();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// restoreMouseCursor()
  restoreMouseCursor() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(601))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void restoreMouseCursor_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::restoreMouseCursor()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.restoreMouseCursor();
  }
//tag=1024

//tag=1027
// screenNumberFor(KDDockWidgets::View * arg__1) const
  int screenNumberFor(View? arg__1) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(602))
        .asFunction();
//tag=1031
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static int screenNumberFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::screenNumberFor(KDDockWidgets::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.screenNumberFor(View.fromCppPointer(arg__1));
    return result;
  }
//tag=1024

//tag=1027
// screenSizeFor(KDDockWidgets::View * arg__1) const
  QSize screenSizeFor(View? arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(603))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> screenSizeFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::screenSizeFor(KDDockWidgets::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.screenSizeFor(View.fromCppPointer(arg__1));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const
  sendEvent(View? arg__1, QEvent? arg__2) {
//tag=1028
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(604))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
  }

//tag=1035
  static void sendEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? arg__2) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.sendEvent(
        View.fromCppPointer(arg__1), QEvent.fromCppPointer(arg__2));
  }
//tag=1024

//tag=1027
// setMouseCursor(Qt::CursorShape arg__1)
  setMouseCursor(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(605))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1035
  static void setMouseCursor_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::setMouseCursor(Qt::CursorShape arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMouseCursor(arg__1);
  }
//tag=1024

//tag=1027
// tests_createNonClosableView(KDDockWidgets::View * parent)
  View tests_createNonClosableView({required View? parent}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(606))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> tests_createNonClosableView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_createNonClosableView(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_createNonClosableView(
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// tests_deinitPlatform_impl()
  tests_deinitPlatform_impl() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(607))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void tests_deinitPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_deinitPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.tests_deinitPlatform_impl();
  }
//tag=1024

//tag=1027
// tests_initPlatform_impl()
  tests_initPlatform_impl() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(608))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void tests_initPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_initPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.tests_initPlatform_impl();
  }
//tag=1024

//tag=1027
// tests_wait(int ms)
  tests_wait(int ms) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(609))
        .asFunction();
//tag=1030
    func(thisCpp, ms);
  }

//tag=1035
  static void tests_wait_calledFromC(ffi.Pointer<void> thisCpp, int ms) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_wait(int ms)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.tests_wait(ms);
  }
//tag=1024

//tag=1027
// tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const
  bool tests_waitForDeleted(View? arg__1, int timeout) {
//tag=1028
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(610))
        .asFunction();
//tag=1029
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

//tag=1035
  static int tests_waitForDeleted_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_waitForDeleted(KDDockWidgets::View * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result =
        dartInstance.tests_waitForDeleted(View.fromCppPointer(arg__1), timeout);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// tests_waitForDeleted(QObject * arg__1, int timeout) const
  bool tests_waitForDeleted_2(QObject? arg__1, int timeout) {
//tag=1028
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(611))
        .asFunction();
//tag=1029
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

//tag=1035
  static int tests_waitForDeleted_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_waitForDeleted(QObject * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_waitForDeleted_2(
        QObject.fromCppPointer(arg__1), timeout);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int timeout) const
  bool tests_waitForEvent(View? arg__1, int type, int timeout) {
//tag=1028
    final bool_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(612))
        .asFunction();
//tag=1029
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, type,
            timeout) !=
        0;
  }

//tag=1035
  static int tests_waitForEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, int type, int timeout) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_waitForEvent(KDDockWidgets::View * arg__1, QEvent::Type type, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_waitForEvent(
        View.fromCppPointer(arg__1), type, timeout);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const
  bool tests_waitForEvent_2(QObject? w, int type, int timeout) {
//tag=1028
    final bool_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(613))
        .asFunction();
//tag=1029
    return func(thisCpp, w == null ? ffi.nullptr : w.thisCpp, type, timeout) !=
        0;
  }

//tag=1035
  static int tests_waitForEvent_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? w, int type, int timeout) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_waitForEvent(QObject * w, QEvent::Type type, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_waitForEvent_2(
        QObject.fromCppPointer(w), type, timeout);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout) const
  bool tests_waitForResize(Controller? arg__1, int timeout) {
//tag=1028
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(614))
        .asFunction();
//tag=1029
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

//tag=1035
  static int tests_waitForResize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_waitForResize(KDDockWidgets::Controller * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_waitForResize(
        Controller.fromCppPointer(arg__1), timeout);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const
  bool tests_waitForResize_2(View? arg__1, int timeout) {
//tag=1028
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(615))
        .asFunction();
//tag=1029
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

//tag=1035
  static int tests_waitForResize_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_waitForResize(KDDockWidgets::View * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_waitForResize_2(
        View.fromCppPointer(arg__1), timeout);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// ungrabMouse()
  ungrabMouse() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(616))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void ungrabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::ungrabMouse()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.ungrabMouse();
  }
//tag=1024

//tag=1027
// uninstallMessageHandler()
  uninstallMessageHandler() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(617))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void uninstallMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::uninstallMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.uninstallMessageHandler();
  }
//tag=1024

//tag=1027
// usesFallbackMouseGrabber() const
  bool usesFallbackMouseGrabber() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(618))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int usesFallbackMouseGrabber_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::usesFallbackMouseGrabber() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.usesFallbackMouseGrabber();
    return result ? 1 : 0;
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 591:
        return "c_KDDockWidgets__Platform_flutter__applicationName";
      case 592:
        return "c_KDDockWidgets__Platform_flutter__createView_Controller_View";
      case 593:
        return "c_KDDockWidgets__Platform_flutter__hasActivePopup";
      case 594:
        return "c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint";
      case 596:
        return "c_KDDockWidgets__Platform_flutter__installMessageHandler";
      case 597:
        return "c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed";
      case 598:
        return "c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent";
      case 599:
        return "c_KDDockWidgets__Platform_flutter__name";
      case 600:
        return "c_KDDockWidgets__Platform_flutter__organizationName";
      case 601:
        return "c_KDDockWidgets__Platform_flutter__restoreMouseCursor";
      case 602:
        return "c_KDDockWidgets__Platform_flutter__screenNumberFor_View";
      case 603:
        return "c_KDDockWidgets__Platform_flutter__screenSizeFor_View";
      case 604:
        return "c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent";
      case 605:
        return "c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape";
      case 606:
        return "c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View";
      case 607:
        return "c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl";
      case 608:
        return "c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl";
      case 609:
        return "c_KDDockWidgets__Platform_flutter__tests_wait_int";
      case 610:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_View_int";
      case 611:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_QObject_int";
      case 612:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForEvent_View_Type_int";
      case 613:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForEvent_QObject_Type_int";
      case 614:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForResize_Controller_int";
      case 615:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForResize_View_int";
      case 616:
        return "c_KDDockWidgets__Platform_flutter__ungrabMouse";
      case 617:
        return "c_KDDockWidgets__Platform_flutter__uninstallMessageHandler";
      case 618:
        return "c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 591:
        return "applicationName";
      case 592:
        return "createView";
      case 593:
        return "hasActivePopup";
      case 594:
        return "inDisallowedDragView";
      case 596:
        return "installMessageHandler";
      case 597:
        return "isLeftMouseButtonPressed";
      case 598:
        return "isProcessingAppQuitEvent";
      case 599:
        return "name";
      case 600:
        return "organizationName";
      case 601:
        return "restoreMouseCursor";
      case 602:
        return "screenNumberFor";
      case 603:
        return "screenSizeFor";
      case 604:
        return "sendEvent";
      case 605:
        return "setMouseCursor";
      case 606:
        return "tests_createNonClosableView";
      case 607:
        return "tests_deinitPlatform_impl";
      case 608:
        return "tests_initPlatform_impl";
      case 609:
        return "tests_wait";
      case 610:
        return "tests_waitForDeleted";
      case 611:
        return "tests_waitForDeleted_2";
      case 612:
        return "tests_waitForEvent";
      case 613:
        return "tests_waitForEvent_2";
      case 614:
        return "tests_waitForResize";
      case 615:
        return "tests_waitForResize_2";
      case 616:
        return "ungrabMouse";
      case 617:
        return "uninstallMessageHandler";
      case 618:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback591 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.applicationName_calledFromC);
    registerCallback(thisCpp, callback591, 591);
//tag=1021
    final callback592 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.createView_calledFromC);
    registerCallback(thisCpp, callback592, 592);
    const callbackExcept593 = 0;
//tag=1021
    final callback593 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.hasActivePopup_calledFromC, callbackExcept593);
    registerCallback(thisCpp, callback593, 593);
    const callbackExcept594 = 0;
//tag=1021
    final callback594 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform_flutter.inDisallowedDragView_calledFromC,
            callbackExcept594);
    registerCallback(thisCpp, callback594, 594);
//tag=1021
    final callback596 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback596, 596);
    const callbackExcept597 = 0;
//tag=1021
    final callback597 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isLeftMouseButtonPressed_calledFromC,
        callbackExcept597);
    registerCallback(thisCpp, callback597, 597);
    const callbackExcept598 = 0;
//tag=1021
    final callback598 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isProcessingAppQuitEvent_calledFromC,
        callbackExcept598);
    registerCallback(thisCpp, callback598, 598);
//tag=1021
    final callback599 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform_flutter.name_calledFromC);
    registerCallback(thisCpp, callback599, 599);
//tag=1021
    final callback600 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.organizationName_calledFromC);
    registerCallback(thisCpp, callback600, 600);
//tag=1021
    final callback601 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback601, 601);
    const callbackExcept602 = 0;
//tag=1021
    final callback602 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenNumberFor_calledFromC, callbackExcept602);
    registerCallback(thisCpp, callback602, 602);
//tag=1021
    final callback603 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback603, 603);
//tag=1021
    final callback604 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.sendEvent_calledFromC);
    registerCallback(thisCpp, callback604, 604);
//tag=1021
    final callback605 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback605, 605);
//tag=1021
    final callback606 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback606, 606);
//tag=1021
    final callback607 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback607, 607);
//tag=1021
    final callback608 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback608, 608);
//tag=1021
    final callback609 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_wait_calledFromC);
    registerCallback(thisCpp, callback609, 609);
    const callbackExcept610 = 0;
//tag=1021
    final callback610 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForDeleted_calledFromC,
            callbackExcept610);
    registerCallback(thisCpp, callback610, 610);
    const callbackExcept611 = 0;
//tag=1021
    final callback611 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForDeleted_2_calledFromC,
            callbackExcept611);
    registerCallback(thisCpp, callback611, 611);
    const callbackExcept612 = 0;
//tag=1021
    final callback612 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform_flutter.tests_waitForEvent_calledFromC, callbackExcept612);
    registerCallback(thisCpp, callback612, 612);
    const callbackExcept613 = 0;
//tag=1021
    final callback613 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform_flutter.tests_waitForEvent_2_calledFromC, callbackExcept613);
    registerCallback(thisCpp, callback613, 613);
    const callbackExcept614 = 0;
//tag=1021
    final callback614 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForResize_calledFromC,
            callbackExcept614);
    registerCallback(thisCpp, callback614, 614);
    const callbackExcept615 = 0;
//tag=1021
    final callback615 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForResize_2_calledFromC,
            callbackExcept615);
    registerCallback(thisCpp, callback615, 615);
//tag=1021
    final callback616 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback616, 616);
//tag=1021
    final callback617 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback617, 617);
    const callbackExcept618 = 0;
//tag=1021
    final callback618 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.usesFallbackMouseGrabber_calledFromC,
        callbackExcept618);
    registerCallback(thisCpp, callback618, 618);
  }
}
