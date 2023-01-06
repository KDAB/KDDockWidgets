/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
        'c_KDDockWidgets__Screen_Finalizer');

class Screen {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, Screen>();
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
  factory Screen.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        Screen.fromCppPointer(cppPointer, needsAutoDelete)) as Screen;
  }
  Screen.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  Screen.init() {}
//tag=1023
//Screen()
  Screen() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Screen__constructor')
        .asFunction();
    thisCpp = func();
    Screen.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// availableGeometry() const
  QRect availableGeometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(617))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> availableGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::availableGeometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.availableGeometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// availableSize() const
  QSize availableSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(618))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> availableSize_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::availableSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.availableSize();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// devicePixelRatio() const
  double devicePixelRatio() {
//tag=1028
    final double_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<double_Func_voidstar_FFI>>(
            cFunctionSymbolName(619))
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1035
  static double devicePixelRatio_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::devicePixelRatio() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.devicePixelRatio();
    return result;
  }
//tag=1024

//tag=1027
// geometry() const
  QRect geometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(620))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::geometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.geometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// name() const
  QString name() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(621))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::name() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.name();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// size() const
  QSize size() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(622))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> size_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::size() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.size();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// virtualGeometry() const
  QRect virtualGeometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(623))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> virtualGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::virtualGeometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.virtualGeometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// virtualSize() const
  QSize virtualSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(624))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> virtualSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Screen.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Screen::virtualSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.virtualSize();
    return result.thisCpp;
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Screen__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 617:
        return "c_KDDockWidgets__Screen__availableGeometry";
      case 618:
        return "c_KDDockWidgets__Screen__availableSize";
      case 619:
        return "c_KDDockWidgets__Screen__devicePixelRatio";
      case 620:
        return "c_KDDockWidgets__Screen__geometry";
      case 621:
        return "c_KDDockWidgets__Screen__name";
      case 622:
        return "c_KDDockWidgets__Screen__size";
      case 623:
        return "c_KDDockWidgets__Screen__virtualGeometry";
      case 624:
        return "c_KDDockWidgets__Screen__virtualSize";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 617:
        return "availableGeometry";
      case 618:
        return "availableSize";
      case 619:
        return "devicePixelRatio";
      case 620:
        return "geometry";
      case 621:
        return "name";
      case 622:
        return "size";
      case 623:
        return "virtualGeometry";
      case 624:
        return "virtualSize";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Screen__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback617 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.availableGeometry_calledFromC);
    registerCallback(thisCpp, callback617, 617);
//tag=1021
    final callback618 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.availableSize_calledFromC);
    registerCallback(thisCpp, callback618, 618);
//tag=1021
    final callback619 = ffi.Pointer.fromFunction<double_Func_voidstar_FFI>(
        Screen.devicePixelRatio_calledFromC);
    registerCallback(thisCpp, callback619, 619);
//tag=1021
    final callback620 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.geometry_calledFromC);
    registerCallback(thisCpp, callback620, 620);
//tag=1021
    final callback621 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.name_calledFromC);
    registerCallback(thisCpp, callback621, 621);
//tag=1021
    final callback622 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.size_calledFromC);
    registerCallback(thisCpp, callback622, 622);
//tag=1021
    final callback623 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.virtualGeometry_calledFromC);
    registerCallback(thisCpp, callback623, 623);
//tag=1021
    final callback624 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Screen.virtualSize_calledFromC);
    registerCallback(thisCpp, callback624, 624);
  }
}
