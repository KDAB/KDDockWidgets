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
        'c_QPoint_Finalizer');

class QPoint {
  static var s_dartInstanceByCppPtr = Map<int, QPoint>();
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

  factory QPoint.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QPoint.fromCppPointer(cppPointer, needsAutoDelete)) as QPoint;
  }
  QPoint.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  QPoint.init() {} //QPoint()
  QPoint() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QPoint__constructor')
        .asFunction();
    thisCpp = func();
    QPoint.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QPoint(int xpos, int ypos)
  QPoint.ctor2(int xpos, int ypos) {
    final voidstar_Func_int_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_ffi_Int32_FFI>>(
            'c_QPoint__constructor_int_int')
        .asFunction();
    thisCpp = func(xpos, ypos);
    QPoint.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
  static // dotProduct(const QPoint & p1, const QPoint & p2)
      int dotProduct(QPoint? p1, QPoint? p2) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_static_QPoint__dotProduct_QPoint_QPoint')
        .asFunction();
    return func(p1 == null ? ffi.nullptr : p1.thisCpp,
        p2 == null ? ffi.nullptr : p2.thisCpp);
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QPoint__isNull')
        .asFunction();
    return func(thisCpp) != 0;
  } // manhattanLength() const

  int manhattanLength() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QPoint__manhattanLength')
        .asFunction();
    return func(thisCpp);
  } // setX(int x)

  setX(int x) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QPoint__setX_int')
        .asFunction();
    func(thisCpp, x);
  } // setY(int y)

  setY(int y) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QPoint__setY_int')
        .asFunction();
    func(thisCpp, y);
  } // transposed() const

  QPoint transposed() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QPoint__transposed')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // x() const

  int x() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QPoint__x')
        .asFunction();
    return func(thisCpp);
  } // y() const

  int y() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QPoint__y')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QPoint__destructor')
        .asFunction();
    func(thisCpp);
  }
}
