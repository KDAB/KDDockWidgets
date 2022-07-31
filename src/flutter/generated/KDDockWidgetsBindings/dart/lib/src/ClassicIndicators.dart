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
        'c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer');

class ClassicIndicators {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, ClassicIndicators>();
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
  factory ClassicIndicators.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
            ClassicIndicators.fromCppPointer(cppPointer, needsAutoDelete))
        as ClassicIndicators;
  }
  ClassicIndicators.fromCppPointer(var cppPointer,
      [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  ClassicIndicators.init() {}
//tag=1023
//ClassicIndicators(KDDockWidgets::Controllers::DropArea * dropArea)
  ClassicIndicators(DropArea? dropArea) {
//tag=1075
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea')
        .asFunction();
    thisCpp = func(dropArea == null ? ffi.nullptr : dropArea.thisCpp);
    ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// geometryForRubberband(QRect localRect) const
  QRect geometryForRubberband(QRect localRect) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__geometryForRubberband_QRect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, localRect == null ? ffi.nullptr : localRect.thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// hover_impl(QPoint globalPos)
  int hover_impl(QPoint globalPos) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(672))
        .asFunction();
//tag=1031
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

//tag=1035
  static int hover_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance =
        ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::hover_impl(QPoint globalPos)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.hover_impl(QPoint.fromCppPointer(globalPos));
    return result;
  }
//tag=1024

//tag=1027
// indicatorsVisibleChanged()
  indicatorsVisibleChanged() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// onResize(QSize newSize)
  bool onResize(QSize newSize) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize')
        .asFunction();
//tag=1029
    return func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
  QPoint posForIndicator(int arg__1) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(675))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// raiseIndicators()
  raiseIndicators() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__raiseIndicators')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// rubberBandIsTopLevel() const
  bool rubberBandIsTopLevel() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__rubberBandIsTopLevel')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// setDropLocation(KDDockWidgets::DropLocation arg__1)
  setDropLocation(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1024
  static
//tag=1027
// tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
//tag=1028
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// updateVisibility()
  updateVisibility() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(680))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void updateVisibility_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::updateVisibility()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.updateVisibility();
  }
//tag=1024

//tag=1027
// updateWindowPosition()
  updateWindowPosition() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__updateWindowPosition')
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 672:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint";
      case 675:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation";
      case 680:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 672:
        return "hover_impl";
      case 675:
        return "posForIndicator";
      case 680:
        return "updateVisibility";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept672 = 0;
//tag=1021
    final callback672 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            ClassicIndicators.hover_impl_calledFromC, callbackExcept672);
    registerCallback(thisCpp, callback672, 672);
//tag=1021
    final callback675 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            ClassicIndicators.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback675, 675);
//tag=1021
    final callback680 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicators.updateVisibility_calledFromC);
    registerCallback(thisCpp, callback680, 680);
  }
}
