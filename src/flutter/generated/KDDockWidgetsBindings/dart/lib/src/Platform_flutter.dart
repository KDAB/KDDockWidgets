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
            cFunctionSymbolName(714))
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
            cFunctionSymbolName(715))
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
            cFunctionSymbolName(716))
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
            cFunctionSymbolName(717))
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
            cFunctionSymbolName(718))
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
            cFunctionSymbolName(720))
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
            cFunctionSymbolName(721))
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
            cFunctionSymbolName(722))
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
            cFunctionSymbolName(723))
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
            cFunctionSymbolName(724))
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
            cFunctionSymbolName(725))
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
            cFunctionSymbolName(726))
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
            cFunctionSymbolName(727))
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
            cFunctionSymbolName(728))
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
            cFunctionSymbolName(729))
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
// tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
  View tests_createFocusableView(CreateViewOptions arg__1,
      {required View? parent}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(730))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> tests_createFocusableView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_createFocusableView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// tests_createNonClosableView(KDDockWidgets::View * parent)
  View tests_createNonClosableView({required View? parent}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(731))
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
// tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)
  View tests_createView(CreateViewOptions arg__1, {required View? parent}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(732))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> tests_createView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = Platform_flutter.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.tests_createView(
        CreateViewOptions.fromCppPointer(arg__1),
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
            cFunctionSymbolName(733))
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
            cFunctionSymbolName(734))
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
            cFunctionSymbolName(735))
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
            cFunctionSymbolName(736))
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
            cFunctionSymbolName(737))
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
            cFunctionSymbolName(738))
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
            cFunctionSymbolName(739))
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
            cFunctionSymbolName(740))
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
            cFunctionSymbolName(741))
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
            cFunctionSymbolName(742))
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
            cFunctionSymbolName(743))
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
            cFunctionSymbolName(744))
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
      case 714:
        return "c_KDDockWidgets__Platform_flutter__applicationName";
      case 715:
        return "c_KDDockWidgets__Platform_flutter__createDefaultViewFactory";
      case 716:
        return "c_KDDockWidgets__Platform_flutter__createView_Controller_View";
      case 717:
        return "c_KDDockWidgets__Platform_flutter__hasActivePopup";
      case 718:
        return "c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint";
      case 720:
        return "c_KDDockWidgets__Platform_flutter__installMessageHandler";
      case 721:
        return "c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed";
      case 722:
        return "c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent";
      case 723:
        return "c_KDDockWidgets__Platform_flutter__name";
      case 724:
        return "c_KDDockWidgets__Platform_flutter__organizationName";
      case 725:
        return "c_KDDockWidgets__Platform_flutter__restoreMouseCursor";
      case 726:
        return "c_KDDockWidgets__Platform_flutter__screenNumberFor_View";
      case 727:
        return "c_KDDockWidgets__Platform_flutter__screenSizeFor_View";
      case 728:
        return "c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent";
      case 729:
        return "c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape";
      case 730:
        return "c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View";
      case 731:
        return "c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View";
      case 732:
        return "c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View";
      case 733:
        return "c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl";
      case 734:
        return "c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl";
      case 735:
        return "c_KDDockWidgets__Platform_flutter__tests_wait_int";
      case 736:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_View_int";
      case 737:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForDeleted_QObject_int";
      case 738:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForEvent_View_Type_int";
      case 739:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForEvent_QObject_Type_int";
      case 740:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForResize_Controller_int";
      case 741:
        return "c_KDDockWidgets__Platform_flutter__tests_waitForResize_View_int";
      case 742:
        return "c_KDDockWidgets__Platform_flutter__ungrabMouse";
      case 743:
        return "c_KDDockWidgets__Platform_flutter__uninstallMessageHandler";
      case 744:
        return "c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 714:
        return "applicationName";
      case 715:
        return "createDefaultViewFactory";
      case 716:
        return "createView";
      case 717:
        return "hasActivePopup";
      case 718:
        return "inDisallowedDragView";
      case 720:
        return "installMessageHandler";
      case 721:
        return "isLeftMouseButtonPressed";
      case 722:
        return "isProcessingAppQuitEvent";
      case 723:
        return "name";
      case 724:
        return "organizationName";
      case 725:
        return "restoreMouseCursor";
      case 726:
        return "screenNumberFor";
      case 727:
        return "screenSizeFor";
      case 728:
        return "sendEvent";
      case 729:
        return "setMouseCursor";
      case 730:
        return "tests_createFocusableView";
      case 731:
        return "tests_createNonClosableView";
      case 732:
        return "tests_createView";
      case 733:
        return "tests_deinitPlatform_impl";
      case 734:
        return "tests_initPlatform_impl";
      case 735:
        return "tests_wait";
      case 736:
        return "tests_waitForDeleted";
      case 737:
        return "tests_waitForDeleted_2";
      case 738:
        return "tests_waitForEvent";
      case 739:
        return "tests_waitForEvent_2";
      case 740:
        return "tests_waitForResize";
      case 741:
        return "tests_waitForResize_2";
      case 742:
        return "ungrabMouse";
      case 743:
        return "uninstallMessageHandler";
      case 744:
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
    final callback714 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.applicationName_calledFromC);
    registerCallback(thisCpp, callback714, 714);
//tag=1021
    final callback715 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback715, 715);
//tag=1021
    final callback716 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.createView_calledFromC);
    registerCallback(thisCpp, callback716, 716);
    const callbackExcept717 = 0;
//tag=1021
    final callback717 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.hasActivePopup_calledFromC, callbackExcept717);
    registerCallback(thisCpp, callback717, 717);
    const callbackExcept718 = 0;
//tag=1021
    final callback718 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform_flutter.inDisallowedDragView_calledFromC,
            callbackExcept718);
    registerCallback(thisCpp, callback718, 718);
//tag=1021
    final callback720 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback720, 720);
    const callbackExcept721 = 0;
//tag=1021
    final callback721 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isLeftMouseButtonPressed_calledFromC,
        callbackExcept721);
    registerCallback(thisCpp, callback721, 721);
    const callbackExcept722 = 0;
//tag=1021
    final callback722 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isProcessingAppQuitEvent_calledFromC,
        callbackExcept722);
    registerCallback(thisCpp, callback722, 722);
//tag=1021
    final callback723 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform_flutter.name_calledFromC);
    registerCallback(thisCpp, callback723, 723);
//tag=1021
    final callback724 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.organizationName_calledFromC);
    registerCallback(thisCpp, callback724, 724);
//tag=1021
    final callback725 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback725, 725);
    const callbackExcept726 = 0;
//tag=1021
    final callback726 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenNumberFor_calledFromC, callbackExcept726);
    registerCallback(thisCpp, callback726, 726);
//tag=1021
    final callback727 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback727, 727);
//tag=1021
    final callback728 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.sendEvent_calledFromC);
    registerCallback(thisCpp, callback728, 728);
//tag=1021
    final callback729 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback729, 729);
//tag=1021
    final callback730 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback730, 730);
//tag=1021
    final callback731 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback731, 731);
//tag=1021
    final callback732 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createView_calledFromC);
    registerCallback(thisCpp, callback732, 732);
//tag=1021
    final callback733 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback733, 733);
//tag=1021
    final callback734 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback734, 734);
//tag=1021
    final callback735 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_wait_calledFromC);
    registerCallback(thisCpp, callback735, 735);
    const callbackExcept736 = 0;
//tag=1021
    final callback736 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForDeleted_calledFromC,
            callbackExcept736);
    registerCallback(thisCpp, callback736, 736);
    const callbackExcept737 = 0;
//tag=1021
    final callback737 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForDeleted_2_calledFromC,
            callbackExcept737);
    registerCallback(thisCpp, callback737, 737);
    const callbackExcept738 = 0;
//tag=1021
    final callback738 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform_flutter.tests_waitForEvent_calledFromC, callbackExcept738);
    registerCallback(thisCpp, callback738, 738);
    const callbackExcept739 = 0;
//tag=1021
    final callback739 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform_flutter.tests_waitForEvent_2_calledFromC, callbackExcept739);
    registerCallback(thisCpp, callback739, 739);
    const callbackExcept740 = 0;
//tag=1021
    final callback740 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForResize_calledFromC,
            callbackExcept740);
    registerCallback(thisCpp, callback740, 740);
    const callbackExcept741 = 0;
//tag=1021
    final callback741 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_waitForResize_2_calledFromC,
            callbackExcept741);
    registerCallback(thisCpp, callback741, 741);
//tag=1021
    final callback742 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback742, 742);
//tag=1021
    final callback743 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback743, 743);
    const callbackExcept744 = 0;
//tag=1021
    final callback744 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.usesFallbackMouseGrabber_calledFromC,
        callbackExcept744);
    registerCallback(thisCpp, callback744, 744);
  }
}
