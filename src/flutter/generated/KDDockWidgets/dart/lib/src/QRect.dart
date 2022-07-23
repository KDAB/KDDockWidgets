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
        'c_QRect_Finalizer');

class QRect {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, QRect>();
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
  factory QRect.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QRect.fromCppPointer(cppPointer, needsAutoDelete)) as QRect;
  }
  QRect.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  QRect.init() {}
//tag=1023
//QRect()
  QRect() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QRect__constructor')
        .asFunction();
    thisCpp = func();
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1023
//QRect(const QPoint & topleft, const QPoint & bottomright)
  QRect.ctor2(QPoint? topleft, QPoint? bottomright) {
//tag=1075
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__constructor_QPoint_QPoint')
        .asFunction();
    thisCpp = func(topleft == null ? ffi.nullptr : topleft.thisCpp,
        bottomright == null ? ffi.nullptr : bottomright.thisCpp);
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1023
//QRect(const QPoint & topleft, const QSize & size)
  QRect.ctor3(QPoint? topleft, QSize? size) {
//tag=1075
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__constructor_QPoint_QSize')
        .asFunction();
    thisCpp = func(topleft == null ? ffi.nullptr : topleft.thisCpp,
        size == null ? ffi.nullptr : size.thisCpp);
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1023
//QRect(int left, int top, int width, int height)
  QRect.ctor4(int left, int top, int width, int height) {
//tag=1075
    final voidstar_Func_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__constructor_int_int_int_int')
        .asFunction();
    thisCpp = func(left, top, width, height);
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1024

//tag=1027
// adjust(int x1, int y1, int x2, int y2)
  adjust(int x1, int y1, int x2, int y2) {
//tag=1028
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__adjust_int_int_int_int')
        .asFunction();
//tag=1030
    func(thisCpp, x1, y1, x2, y2);
  }
//tag=1024

//tag=1027
// adjusted(int x1, int y1, int x2, int y2) const
  QRect adjusted(int x1, int y1, int x2, int y2) {
//tag=1028
    final voidstar_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__adjusted_int_int_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, x1, y1, x2, y2);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// bottom() const
  int bottom() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__bottom')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// bottomLeft() const
  QPoint bottomLeft() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__bottomLeft')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// bottomRight() const
  QPoint bottomRight() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__bottomRight')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// center() const
  QPoint center() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__center')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// contains(const QPoint & p, bool proper) const
  bool contains(QPoint? p, {bool proper = false}) {
//tag=1028
    final bool_Func_voidstar_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int8_FFI>>(
            'c_QRect__contains_QPoint_bool')
        .asFunction();
//tag=1029
    return func(thisCpp, p == null ? ffi.nullptr : p.thisCpp, proper ? 1 : 0) !=
        0;
  }
//tag=1024

//tag=1027
// contains(const QRect & r, bool proper) const
  bool contains_2(QRect? r, {bool proper = false}) {
//tag=1028
    final bool_Func_voidstar_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int8_FFI>>(
            'c_QRect__contains_QRect_bool')
        .asFunction();
//tag=1029
    return func(thisCpp, r == null ? ffi.nullptr : r.thisCpp, proper ? 1 : 0) !=
        0;
  }
//tag=1024

//tag=1027
// contains(int x, int y) const
  bool contains_3(int x, int y) {
//tag=1028
    final bool_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__contains_int_int')
        .asFunction();
//tag=1029
    return func(thisCpp, x, y) != 0;
  }
//tag=1024

//tag=1027
// contains(int x, int y, bool proper) const
  bool contains_4(int x, int y, bool proper) {
//tag=1028
    final bool_Func_voidstar_int_int_bool func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int8_FFI>>(
            'c_QRect__contains_int_int_bool')
        .asFunction();
//tag=1029
    return func(thisCpp, x, y, proper ? 1 : 0) != 0;
  }
//tag=1024

//tag=1027
// height() const
  int height() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__height')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// intersected(const QRect & other) const
  QRect intersected(QRect? other) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__intersected_QRect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, other == null ? ffi.nullptr : other.thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// intersects(const QRect & r) const
  bool intersects(QRect? r) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QRect__intersects_QRect')
        .asFunction();
//tag=1029
    return func(thisCpp, r == null ? ffi.nullptr : r.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isEmpty() const
  bool isEmpty() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QRect__isEmpty')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isNull() const
  bool isNull() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QRect__isNull')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isValid() const
  bool isValid() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QRect__isValid')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// left() const
  int left() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__left')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// moveBottom(int pos)
  moveBottom(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveBottom_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// moveBottomLeft(const QPoint & p)
  moveBottomLeft(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveBottomLeft_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// moveBottomRight(const QPoint & p)
  moveBottomRight(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveBottomRight_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// moveCenter(const QPoint & p)
  moveCenter(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveCenter_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// moveLeft(int pos)
  moveLeft(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveLeft_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// moveRight(int pos)
  moveRight(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveRight_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// moveTo(const QPoint & p)
  moveTo(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveTo_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// moveTo(int x, int t)
  moveTo_2(int x, int t) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__moveTo_int_int')
        .asFunction();
//tag=1030
    func(thisCpp, x, t);
  }
//tag=1024

//tag=1027
// moveTop(int pos)
  moveTop(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveTop_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// moveTopLeft(const QPoint & p)
  moveTopLeft(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveTopLeft_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// moveTopRight(const QPoint & p)
  moveTopRight(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveTopRight_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// normalized() const
  QRect normalized() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__normalized')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// right() const
  int right() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__right')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// setBottom(int pos)
  setBottom(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setBottom_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// setBottomLeft(const QPoint & p)
  setBottomLeft(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setBottomLeft_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// setBottomRight(const QPoint & p)
  setBottomRight(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setBottomRight_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// setCoords(int x1, int y1, int x2, int y2)
  setCoords(int x1, int y1, int x2, int y2) {
//tag=1028
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__setCoords_int_int_int_int')
        .asFunction();
//tag=1030
    func(thisCpp, x1, y1, x2, y2);
  }
//tag=1024

//tag=1027
// setHeight(int h)
  setHeight(int h) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setHeight_int')
        .asFunction();
//tag=1030
    func(thisCpp, h);
  }
//tag=1024

//tag=1027
// setLeft(int pos)
  setLeft(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setLeft_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// setRect(int x, int y, int w, int h)
  setRect(int x, int y, int w, int h) {
//tag=1028
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__setRect_int_int_int_int')
        .asFunction();
//tag=1030
    func(thisCpp, x, y, w, h);
  }
//tag=1024

//tag=1027
// setRight(int pos)
  setRight(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setRight_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// setSize(const QSize & s)
  setSize(QSize? s) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, s == null ? ffi.nullptr : s.thisCpp);
  }
//tag=1024

//tag=1027
// setTop(int pos)
  setTop(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setTop_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }
//tag=1024

//tag=1027
// setTopLeft(const QPoint & p)
  setTopLeft(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setTopLeft_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// setTopRight(const QPoint & p)
  setTopRight(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setTopRight_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// setWidth(int w)
  setWidth(int w) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setWidth_int')
        .asFunction();
//tag=1030
    func(thisCpp, w);
  }
//tag=1024

//tag=1027
// setX(int x)
  setX(int x) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setX_int')
        .asFunction();
//tag=1030
    func(thisCpp, x);
  }
//tag=1024

//tag=1027
// setY(int y)
  setY(int y) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setY_int')
        .asFunction();
//tag=1030
    func(thisCpp, y);
  }
//tag=1024

//tag=1027
// size() const
  QSize size() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>('c_QRect__size')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// top() const
  int top() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__top')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// topLeft() const
  QPoint topLeft() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__topLeft')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// topRight() const
  QPoint topRight() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__topRight')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// translate(const QPoint & p)
  translate(QPoint? p) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__translate_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  }
//tag=1024

//tag=1027
// translate(int dx, int dy)
  translate_2(int dx, int dy) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__translate_int_int')
        .asFunction();
//tag=1030
    func(thisCpp, dx, dy);
  }
//tag=1024

//tag=1027
// translated(const QPoint & p) const
  QRect translated(QPoint? p) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__translated_QPoint')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// translated(int dx, int dy) const
  QRect translated_2(int dx, int dy) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__translated_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, dx, dy);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// transposed() const
  QRect transposed() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__transposed')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// united(const QRect & other) const
  QRect united(QRect? other) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__united_QRect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, other == null ? ffi.nullptr : other.thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// width() const
  int width() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__width')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// x() const
  int x() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__x')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// y() const
  int y() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__y')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QRect__destructor')
        .asFunction();
    func(thisCpp);
  }
}
