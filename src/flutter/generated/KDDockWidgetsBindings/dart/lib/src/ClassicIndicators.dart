/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;
final _finalizer =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_KDDockWidgets__Controllers__ClassicIndicators_Finalizer');

class ClassicIndicators {
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
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory ClassicIndicators.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
            ClassicIndicators.fromCppPointer(cppPointer, needsAutoDelete))
        as ClassicIndicators;
  }
  ClassicIndicators.fromCppPointer(var cppPointer,
      [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  ClassicIndicators.init() {} //ClassicIndicators(KDDockWidgets::Controllers::DropArea * dropArea)
  ClassicIndicators(DropArea? dropArea) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea')
        .asFunction();
    thisCpp = func(dropArea == null ? ffi.nullptr : dropArea.thisCpp);
    ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // geometryForRubberband(QRect localRect) const
  QRect geometryForRubberband(QRect localRect) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__geometryForRubberband_QRect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, localRect == null ? ffi.nullptr : localRect.thisCpp);
    return QRect.fromCppPointer(result, true);
  } // hover_impl(QPoint globalPos)

  int hover_impl(QPoint globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(789))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

  static int hover_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance =
        ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::hover_impl(QPoint globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover_impl(QPoint.fromCppPointer(globalPos));
    return result;
  } // indicatorsVisibleChanged()

  indicatorsVisibleChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged')
        .asFunction();
    func(thisCpp);
  } // onResize(QSize newSize)

  bool onResize(QSize newSize) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize')
        .asFunction();
    return func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp) != 0;
  } // posForIndicator(KDDockWidgets::DropLocation arg__1) const

  QPoint posForIndicator(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(792))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  } // raiseIndicators()

  raiseIndicators() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__raiseIndicators')
        .asFunction();
    func(thisCpp);
  } // rubberBandIsTopLevel() const

  bool rubberBandIsTopLevel() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__rubberBandIsTopLevel')
        .asFunction();
    return func(thisCpp) != 0;
  } // setDropLocation(KDDockWidgets::DropLocation arg__1)

  setDropLocation(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation')
        .asFunction();
    func(thisCpp, arg__1);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateVisibility()

  updateVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(797))
        .asFunction();
    func(thisCpp);
  }

  static void updateVisibility_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        ClassicIndicators.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::updateVisibility()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updateVisibility();
  } // updateWindowPosition()

  updateWindowPosition() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__updateWindowPosition')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 789:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint";
      case 792:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation";
      case 797:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 789:
        return "hover_impl";
      case 792:
        return "posForIndicator";
      case 797:
        return "updateVisibility";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept789 = 0;
    final callback789 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            ClassicIndicators.hover_impl_calledFromC, callbackExcept789);
    registerCallback(thisCpp, callback789, 789);
    final callback792 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            ClassicIndicators.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback792, 792);
    final callback797 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicators.updateVisibility_calledFromC);
    registerCallback(thisCpp, callback797, 797);
  }
}
