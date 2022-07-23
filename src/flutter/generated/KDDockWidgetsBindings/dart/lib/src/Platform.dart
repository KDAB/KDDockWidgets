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
        'c_KDDockWidgets__Platform_Finalizer');

class Platform {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, Platform>();
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
  factory Platform.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        Platform.fromCppPointer(cppPointer, needsAutoDelete)) as Platform;
  }
  Platform.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  Platform.init() {}
//tag=1023
//Platform()
  Platform() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Platform__constructor')
        .asFunction();
    thisCpp = func();
    Platform.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// applicationName() const
  QString applicationName() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(680))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> applicationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::applicationName() const! (${thisCpp.address})");
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
            cFunctionSymbolName(681))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return ViewFactory.fromCppPointer(result, false);
  }

//tag=1035
  static ffi.Pointer<void> createDefaultViewFactory_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createDefaultViewFactory()! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.createDefaultViewFactory();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// hasActivePopup() const
  bool hasActivePopup() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(682))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int hasActivePopup_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::hasActivePopup() const! (${thisCpp.address})");
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
            cFunctionSymbolName(683))
        .asFunction();
//tag=1029
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp) !=
        0;
  }

//tag=1035
  static int inDisallowedDragView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::inDisallowedDragView(QPoint globalPos) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result =
        dartInstance.inDisallowedDragView(QPoint.fromCppPointer(globalPos));
    return result ? 1 : 0;
  }

//tag=1024
  static
//tag=1027
// instance()
      Platform instance() {
//tag=1028
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__Platform__instance')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func();
    return Platform.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// isLeftMouseButtonPressed() const
  bool isLeftMouseButtonPressed() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(685))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isLeftMouseButtonPressed_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::isLeftMouseButtonPressed() const! (${thisCpp.address})");
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
            cFunctionSymbolName(686))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isProcessingAppQuitEvent_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::isProcessingAppQuitEvent() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isProcessingAppQuitEvent();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isQtQuick() const
  bool isQtQuick() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform__isQtQuick')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isQtWidgets() const
  bool isQtWidgets() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform__isQtWidgets')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// name() const
  String name() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            cFunctionSymbolName(689))
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }

//tag=1035
  static ffi.Pointer<Utf8> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::name() const! (${thisCpp.address})");
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
            cFunctionSymbolName(690))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> organizationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::organizationName() const! (${thisCpp.address})");
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
            cFunctionSymbolName(691))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void restoreMouseCursor_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::restoreMouseCursor()! (${thisCpp.address})");
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
            cFunctionSymbolName(692))
        .asFunction();
//tag=1031
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static int screenNumberFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::screenNumberFor(KDDockWidgets::View * arg__1) const! (${thisCpp.address})");
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
            cFunctionSymbolName(693))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> screenSizeFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::screenSizeFor(KDDockWidgets::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.screenSizeFor(View.fromCppPointer(arg__1));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// startDragDistance() const
  int startDragDistance() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform__startDragDistance')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// startDragDistance_impl() const
  int startDragDistance_impl() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(695))
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1035
  static int startDragDistance_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::startDragDistance_impl() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.startDragDistance_impl();
    return result;
  }
//tag=1024

//tag=1027
// ungrabMouse()
  ungrabMouse() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(696))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void ungrabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::ungrabMouse()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.ungrabMouse();
  }
//tag=1024

//tag=1027
// usesFallbackMouseGrabber() const
  bool usesFallbackMouseGrabber() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(697))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int usesFallbackMouseGrabber_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::usesFallbackMouseGrabber() const! (${thisCpp.address})");
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
            'c_KDDockWidgets__Platform__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 680:
        return "c_KDDockWidgets__Platform__applicationName";
      case 681:
        return "c_KDDockWidgets__Platform__createDefaultViewFactory";
      case 682:
        return "c_KDDockWidgets__Platform__hasActivePopup";
      case 683:
        return "c_KDDockWidgets__Platform__inDisallowedDragView_QPoint";
      case 685:
        return "c_KDDockWidgets__Platform__isLeftMouseButtonPressed";
      case 686:
        return "c_KDDockWidgets__Platform__isProcessingAppQuitEvent";
      case 689:
        return "c_KDDockWidgets__Platform__name";
      case 690:
        return "c_KDDockWidgets__Platform__organizationName";
      case 691:
        return "c_KDDockWidgets__Platform__restoreMouseCursor";
      case 692:
        return "c_KDDockWidgets__Platform__screenNumberFor_View";
      case 693:
        return "c_KDDockWidgets__Platform__screenSizeFor_View";
      case 695:
        return "c_KDDockWidgets__Platform__startDragDistance_impl";
      case 696:
        return "c_KDDockWidgets__Platform__ungrabMouse";
      case 697:
        return "c_KDDockWidgets__Platform__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 680:
        return "applicationName";
      case 681:
        return "createDefaultViewFactory";
      case 682:
        return "hasActivePopup";
      case 683:
        return "inDisallowedDragView";
      case 685:
        return "isLeftMouseButtonPressed";
      case 686:
        return "isProcessingAppQuitEvent";
      case 689:
        return "name";
      case 690:
        return "organizationName";
      case 691:
        return "restoreMouseCursor";
      case 692:
        return "screenNumberFor";
      case 693:
        return "screenSizeFor";
      case 695:
        return "startDragDistance_impl";
      case 696:
        return "ungrabMouse";
      case 697:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Platform__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback680 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback680, 680);
//tag=1021
    final callback681 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback681, 681);
    const callbackExcept682 = 0;
//tag=1021
    final callback682 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.hasActivePopup_calledFromC, callbackExcept682);
    registerCallback(thisCpp, callback682, 682);
    const callbackExcept683 = 0;
//tag=1021
    final callback683 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform.inDisallowedDragView_calledFromC, callbackExcept683);
    registerCallback(thisCpp, callback683, 683);
    const callbackExcept685 = 0;
//tag=1021
    final callback685 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.isLeftMouseButtonPressed_calledFromC, callbackExcept685);
    registerCallback(thisCpp, callback685, 685);
    const callbackExcept686 = 0;
//tag=1021
    final callback686 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.isProcessingAppQuitEvent_calledFromC, callbackExcept686);
    registerCallback(thisCpp, callback686, 686);
//tag=1021
    final callback689 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform.name_calledFromC);
    registerCallback(thisCpp, callback689, 689);
//tag=1021
    final callback690 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.organizationName_calledFromC);
    registerCallback(thisCpp, callback690, 690);
//tag=1021
    final callback691 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback691, 691);
    const callbackExcept692 = 0;
//tag=1021
    final callback692 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform.screenNumberFor_calledFromC, callbackExcept692);
    registerCallback(thisCpp, callback692, 692);
//tag=1021
    final callback693 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback693, 693);
    const callbackExcept695 = 0;
//tag=1021
    final callback695 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Platform.startDragDistance_impl_calledFromC, callbackExcept695);
    registerCallback(thisCpp, callback695, 695);
//tag=1021
    final callback696 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback696, 696);
    const callbackExcept697 = 0;
//tag=1021
    final callback697 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.usesFallbackMouseGrabber_calledFromC, callbackExcept697);
    registerCallback(thisCpp, callback697, 697);
  }
}
