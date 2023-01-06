/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
        'c_QSize_Finalizer');

class QSize {
  static var s_dartInstanceByCppPtr = Map<int, QSize>();
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

  factory QSize.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QSize.fromCppPointer(cppPointer, needsAutoDelete)) as QSize;
  }
  QSize.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  QSize.init() {} //QSize()
  QSize() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QSize__constructor')
        .asFunction();
    thisCpp = func();
    QSize.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QSize(int w, int h)
  QSize.ctor2(int w, int h) {
    final voidstar_Func_int_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_ffi_Int32_FFI>>(
            'c_QSize__constructor_int_int')
        .asFunction();
    thisCpp = func(w, h);
    QSize.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // boundedTo(const QSize & arg__1) const
  QSize boundedTo(QSize? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QSize__boundedTo_QSize')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QSize.fromCppPointer(result, true);
  } // expandedTo(const QSize & arg__1) const

  QSize expandedTo(QSize? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QSize__expandedTo_QSize')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QSize.fromCppPointer(result, true);
  } // height() const

  int height() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QSize__height')
        .asFunction();
    return func(thisCpp);
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QSize__isEmpty')
        .asFunction();
    return func(thisCpp) != 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QSize__isNull')
        .asFunction();
    return func(thisCpp) != 0;
  } // isValid() const

  bool isValid() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QSize__isValid')
        .asFunction();
    return func(thisCpp) != 0;
  } // setHeight(int h)

  setHeight(int h) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QSize__setHeight_int')
        .asFunction();
    func(thisCpp, h);
  } // setWidth(int w)

  setWidth(int w) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QSize__setWidth_int')
        .asFunction();
    func(thisCpp, w);
  } // transpose()

  transpose() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QSize__transpose')
        .asFunction();
    func(thisCpp);
  } // transposed() const

  QSize transposed() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QSize__transposed')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // width() const

  int width() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QSize__width')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QSize__destructor')
        .asFunction();
    func(thisCpp);
  }
}
