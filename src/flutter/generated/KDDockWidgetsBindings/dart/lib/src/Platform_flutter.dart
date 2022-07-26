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
            cFunctionSymbolName(622))
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
// createDefaultViewFactory()
  ViewFactory createDefaultViewFactory() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(623))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return ViewFactory.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> createDefaultViewFactory_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::createDefaultViewFactory()! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.createDefaultViewFactory();
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
            cFunctionSymbolName(624))
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
            cFunctionSymbolName(625))
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
            cFunctionSymbolName(626))
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
            cFunctionSymbolName(628))
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
            cFunctionSymbolName(629))
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
            cFunctionSymbolName(630))
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
            cFunctionSymbolName(631))
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
            cFunctionSymbolName(632))
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
            cFunctionSymbolName(633))
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
            cFunctionSymbolName(634))
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
            cFunctionSymbolName(635))
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
            cFunctionSymbolName(636))
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
            cFunctionSymbolName(637))
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
            cFunctionSymbolName(638))
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
            cFunctionSymbolName(639))
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
            cFunctionSymbolName(640))
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
            cFunctionSymbolName(641))
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
            cFunctionSymbolName(642))
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
            cFunctionSymbolName(643))
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
            cFunctionSymbolName(644))
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
            cFunctionSymbolName(645))
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
            cFunctionSymbolName(646))
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
            cFunctionSymbolName(647))
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
            cFunctionSymbolName(648))
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
            cFunctionSymbolName(649))
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
            cFunctionSymbolName(650))
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
      case 622:
        return "c_KDDockWidgets__Platform_flutter__applicationName";
      case 623:
        return "c_KDDockWidgets__Platform_flutter__createDefaultViewFactory";
      case 624:
        return "c_KDDockWidgets__Platform_flutter__createView_Controller_View";
      case 625:
        return "c_KDDockWidgets__Platform_flutter__hasActivePopup";
      case 626:
        return "c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint";
      case 628:
        return "c_KDDockWidgets__Platform_flutter__installMessageHandler";
      case 629:
        return "c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed";
      case 630:
        return "c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent";
      case 631:
        return "c_KDDockWidgets__Platform_flutter__name";
      case 632:
        return "c_KDDockWidgets__Platform_flutter__organizationName";
      case 633:
        return "c_KDDockWidgets__Platform_flutter__restoreMouseCursor";
      case 634:
        return "c_KDDockWidgets__Platform_flutter__screenNumberFor_View";
      case 635:
        return "c_KDDockWidgets__Platform_flutter__screenSizeFor_View";
      case 636:
        return "c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent";
      case 637:
        return "c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape";
      case 638:
        return "c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View";
      case 639:
        return "c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl";
      case 640:
        return "c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl";
      case 641:
        return "c_KDDockWidgets__Platform_flutter__tests_wait_int";
      case 642:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_View_int";
      case 643:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_QObject_int";
      case 644:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForEvent_View_Type_int";
      case 645:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForEvent_QObject_Type_int";
      case 646:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForResize_Controller_int";
      case 647:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForResize_View_int";
      case 648:
        return "c_KDDockWidgets__Platform_flutter__ungrabMouse";
      case 649:
        return "c_KDDockWidgets__Platform_flutter__uninstallMessageHandler";
      case 650:
        return "c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 622:
        return "applicationName";
      case 623:
        return "createDefaultViewFactory";
      case 624:
        return "createView";
      case 625:
        return "hasActivePopup";
      case 626:
        return "inDisallowedDragView";
      case 628:
        return "installMessageHandler";
      case 629:
        return "isLeftMouseButtonPressed";
      case 630:
        return "isProcessingAppQuitEvent";
      case 631:
        return "name";
      case 632:
        return "organizationName";
      case 633:
        return "restoreMouseCursor";
      case 634:
        return "screenNumberFor";
      case 635:
        return "screenSizeFor";
      case 636:
        return "sendEvent";
      case 637:
        return "setMouseCursor";
      case 638:
        return "tests_createNonClosableView";
      case 639:
        return "tests_deinitPlatform_impl";
      case 640:
        return "tests_initPlatform_impl";
      case 641:
        return "tests_wait";
      case 642:
        return "tests_waitForDeleted";
      case 643:
        return "tests_waitForDeleted_2";
      case 644:
        return "tests_waitForEvent";
      case 645:
        return "tests_waitForEvent_2";
      case 646:
        return "tests_waitForResize";
      case 647:
        return "tests_waitForResize_2";
      case 648:
        return "ungrabMouse";
      case 649:
        return "uninstallMessageHandler";
      case 650:
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
    final callback622 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.applicationName_calledFromC);
    registerCallback(thisCpp, callback622, 622);
//tag=1021
    final callback623 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback623, 623);
//tag=1021
    final callback624 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.createView_calledFromC);
    registerCallback(thisCpp, callback624, 624);
    const callbackExcept625 = 0;
//tag=1021
    final callback625 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.hasActivePopup_calledFromC, callbackExcept625);
    registerCallback(thisCpp, callback625, 625);
    const callbackExcept626 = 0;
//tag=1021
    final callback626 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform_flutter.inDisallowedDragView_calledFromC,
            callbackExcept626);
    registerCallback(thisCpp, callback626, 626);
//tag=1021
    final callback628 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback628, 628);
    const callbackExcept629 = 0;
//tag=1021
    final callback629 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isLeftMouseButtonPressed_calledFromC,
        callbackExcept629);
    registerCallback(thisCpp, callback629, 629);
    const callbackExcept630 = 0;
//tag=1021
    final callback630 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isProcessingAppQuitEvent_calledFromC,
        callbackExcept630);
    registerCallback(thisCpp, callback630, 630);
//tag=1021
    final callback631 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform_flutter.name_calledFromC);
    registerCallback(thisCpp, callback631, 631);
//tag=1021
    final callback632 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.organizationName_calledFromC);
    registerCallback(thisCpp, callback632, 632);
//tag=1021
    final callback633 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback633, 633);
    const callbackExcept634 = 0;
//tag=1021
    final callback634 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenNumberFor_calledFromC, callbackExcept634);
    registerCallback(thisCpp, callback634, 634);
//tag=1021
    final callback635 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback635, 635);
//tag=1021
    final callback636 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.sendEvent_calledFromC);
    registerCallback(thisCpp, callback636, 636);
//tag=1021
    final callback637 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback637, 637);
//tag=1021
    final callback638 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback638, 638);
//tag=1021
    final callback639 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback639, 639);
//tag=1021
    final callback640 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback640, 640);
//tag=1021
    final callback641 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_wait_calledFromC);
    registerCallback(thisCpp, callback641, 641);
    const callbackExcept642 = 0;
//tag=1021
    final callback642 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForDeleted_calledFromC,
            callbackExcept642);
    registerCallback(thisCpp, callback642, 642);
    const callbackExcept643 = 0;
//tag=1021
    final callback643 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForDeleted_2_calledFromC,
            callbackExcept643);
    registerCallback(thisCpp, callback643, 643);
    const callbackExcept644 = 0;
//tag=1021
    final callback644 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform_flutter.tests_waitForEvent_calledFromC, callbackExcept644);
    registerCallback(thisCpp, callback644, 644);
    const callbackExcept645 = 0;
//tag=1021
    final callback645 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform_flutter.tests_waitForEvent_2_calledFromC, callbackExcept645);
    registerCallback(thisCpp, callback645, 645);
    const callbackExcept646 = 0;
//tag=1021
    final callback646 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForResize_calledFromC,
            callbackExcept646);
    registerCallback(thisCpp, callback646, 646);
    const callbackExcept647 = 0;
//tag=1021
    final callback647 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForResize_2_calledFromC,
            callbackExcept647);
    registerCallback(thisCpp, callback647, 647);
//tag=1021
    final callback648 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback648, 648);
//tag=1021
    final callback649 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback649, 649);
    const callbackExcept650 = 0;
//tag=1021
    final callback650 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.usesFallbackMouseGrabber_calledFromC,
        callbackExcept650);
    registerCallback(thisCpp, callback650, 650);
  }
}
