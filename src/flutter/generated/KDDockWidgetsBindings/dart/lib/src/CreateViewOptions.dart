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
        'c_KDDockWidgets__CreateViewOptions_Finalizer');

class CreateViewOptions {
  static var s_dartInstanceByCppPtr = Map<int, CreateViewOptions>();
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
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory CreateViewOptions.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
            CreateViewOptions.fromCppPointer(cppPointer, needsAutoDelete))
        as CreateViewOptions;
  }
  CreateViewOptions.fromCppPointer(var cppPointer,
      [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  CreateViewOptions.init() {}
  bool get isVisible {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__CreateViewOptions___get_isVisible')
        .asFunction();
    return func(thisCpp) != 0;
  }

  set isVisible(bool isVisible_) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__CreateViewOptions___set_isVisible_bool')
        .asFunction();
    func(thisCpp, isVisible_ ? 1 : 0);
  }

  bool get createWindow {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__CreateViewOptions___get_createWindow')
        .asFunction();
    return func(thisCpp) != 0;
  }

  set createWindow(bool createWindow_) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__CreateViewOptions___set_createWindow_bool')
        .asFunction();
    func(thisCpp, createWindow_ ? 1 : 0);
  } //CreateViewOptions()

  CreateViewOptions() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__CreateViewOptions__constructor')
        .asFunction();
    thisCpp = func();
    CreateViewOptions.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__CreateViewOptions__destructor')
        .asFunction();
    func(thisCpp);
  }
}
