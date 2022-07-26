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
        'c_KDDockWidgets__Config_Finalizer');

class Config {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, Config>();
  var _thisCpp = null;
  bool _needsAutoDelete = true;
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
  factory Config.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        Config.fromCppPointer(cppPointer, needsAutoDelete)) as Config;
  }
  Config.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  Config.init() {}
//tag=1024

//tag=1027
// absoluteWidgetMaxSize() const
  QSize absoluteWidgetMaxSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__absoluteWidgetMaxSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// absoluteWidgetMinSize() const
  QSize absoluteWidgetMinSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__absoluteWidgetMinSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// draggedWindowOpacity() const
  double draggedWindowOpacity() {
//tag=1028
    final double_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<double_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__draggedWindowOpacity')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// dropIndicatorsInhibited() const
  bool dropIndicatorsInhibited() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__dropIndicatorsInhibited')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// mdiPopupThreshold() const
  int mdiPopupThreshold() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__mdiPopupThreshold')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1024
  static
//tag=1027
// self()
      Config self() {
//tag=1028
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__Config__self')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func();
    return Config.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// separatorThickness() const
  int separatorThickness() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__separatorThickness')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// setAbsoluteWidgetMaxSize(QSize size)
  setAbsoluteWidgetMaxSize(QSize size) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Config__setAbsoluteWidgetMaxSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, size == null ? ffi.nullptr : size.thisCpp);
  }
//tag=1024

//tag=1027
// setAbsoluteWidgetMinSize(QSize size)
  setAbsoluteWidgetMinSize(QSize size) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Config__setAbsoluteWidgetMinSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, size == null ? ffi.nullptr : size.thisCpp);
  }
//tag=1024

//tag=1027
// setDraggedWindowOpacity(qreal opacity)
  setDraggedWindowOpacity(double opacity) {
//tag=1028
    final void_Func_voidstar_double func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Double_FFI>>(
            'c_KDDockWidgets__Config__setDraggedWindowOpacity_qreal')
        .asFunction();
//tag=1030
    func(thisCpp, opacity);
  }
//tag=1024

//tag=1027
// setDropIndicatorsInhibited(bool inhibit) const
  setDropIndicatorsInhibited(bool inhibit) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Config__setDropIndicatorsInhibited_bool')
        .asFunction();
//tag=1030
    func(thisCpp, inhibit ? 1 : 0);
  }
//tag=1024

//tag=1027
// setMDIPopupThreshold(int arg__1)
  setMDIPopupThreshold(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Config__setMDIPopupThreshold_int')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }
//tag=1024

//tag=1027
// setSeparatorThickness(int value)
  setSeparatorThickness(int value) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Config__setSeparatorThickness_int')
        .asFunction();
//tag=1030
    func(thisCpp, value);
  }
//tag=1024

//tag=1027
// setStartDragDistance(int arg__1)
  setStartDragDistance(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Config__setStartDragDistance_int')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }
//tag=1024

//tag=1027
// startDragDistance() const
  int startDragDistance() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__startDragDistance')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Config__destructor')
        .asFunction();
    func(thisCpp);
  }
}
