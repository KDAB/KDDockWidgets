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
        'c_QRect_Finalizer');

class QRect {
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
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory QRect.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QRect.fromCppPointer(cppPointer, needsAutoDelete)) as QRect;
  }
  QRect.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  QRect.init() {} //QRect()
  QRect() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QRect__constructor')
        .asFunction();
    thisCpp = func();
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QRect(const QPoint & topleft, const QPoint & bottomright)
  QRect.ctor2(QPoint? topleft, QPoint? bottomright) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__constructor_QPoint_QPoint')
        .asFunction();
    thisCpp = func(topleft == null ? ffi.nullptr : topleft.thisCpp,
        bottomright == null ? ffi.nullptr : bottomright.thisCpp);
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QRect(const QPoint & topleft, const QSize & size)
  QRect.ctor3(QPoint? topleft, QSize? size) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__constructor_QPoint_QSize')
        .asFunction();
    thisCpp = func(topleft == null ? ffi.nullptr : topleft.thisCpp,
        size == null ? ffi.nullptr : size.thisCpp);
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QRect(int left, int top, int width, int height)
  QRect.ctor4(int left, int top, int width, int height) {
    final voidstar_Func_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__constructor_int_int_int_int')
        .asFunction();
    thisCpp = func(left, top, width, height);
    QRect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // adjust(int x1, int y1, int x2, int y2)
  adjust(int x1, int y1, int x2, int y2) {
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__adjust_int_int_int_int')
        .asFunction();
    func(thisCpp, x1, y1, x2, y2);
  } // adjusted(int x1, int y1, int x2, int y2) const

  QRect adjusted(int x1, int y1, int x2, int y2) {
    final voidstar_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__adjusted_int_int_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, x1, y1, x2, y2);
    return QRect.fromCppPointer(result, true);
  } // bottom() const

  int bottom() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__bottom')
        .asFunction();
    return func(thisCpp);
  } // bottomLeft() const

  QPoint bottomLeft() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__bottomLeft')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // bottomRight() const

  QPoint bottomRight() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__bottomRight')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // center() const

  QPoint center() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__center')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // contains(const QPoint & p, bool proper) const

  bool contains(QPoint? p, {bool proper = false}) {
    final bool_Func_voidstar_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int8_FFI>>(
            'c_QRect__contains_QPoint_bool')
        .asFunction();
    return func(thisCpp, p == null ? ffi.nullptr : p.thisCpp, proper ? 1 : 0) !=
        0;
  } // contains(const QRect & r, bool proper) const

  bool contains_2(QRect? r, {bool proper = false}) {
    final bool_Func_voidstar_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int8_FFI>>(
            'c_QRect__contains_QRect_bool')
        .asFunction();
    return func(thisCpp, r == null ? ffi.nullptr : r.thisCpp, proper ? 1 : 0) !=
        0;
  } // contains(int x, int y) const

  bool contains_3(int x, int y) {
    final bool_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__contains_int_int')
        .asFunction();
    return func(thisCpp, x, y) != 0;
  } // contains(int x, int y, bool proper) const

  bool contains_4(int x, int y, bool proper) {
    final bool_Func_voidstar_int_int_bool func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int8_FFI>>(
            'c_QRect__contains_int_int_bool')
        .asFunction();
    return func(thisCpp, x, y, proper ? 1 : 0) != 0;
  } // height() const

  int height() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__height')
        .asFunction();
    return func(thisCpp);
  } // intersected(const QRect & other) const

  QRect intersected(QRect? other) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__intersected_QRect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, other == null ? ffi.nullptr : other.thisCpp);
    return QRect.fromCppPointer(result, true);
  } // intersects(const QRect & r) const

  bool intersects(QRect? r) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QRect__intersects_QRect')
        .asFunction();
    return func(thisCpp, r == null ? ffi.nullptr : r.thisCpp) != 0;
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QRect__isEmpty')
        .asFunction();
    return func(thisCpp) != 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QRect__isNull')
        .asFunction();
    return func(thisCpp) != 0;
  } // isValid() const

  bool isValid() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QRect__isValid')
        .asFunction();
    return func(thisCpp) != 0;
  } // left() const

  int left() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__left')
        .asFunction();
    return func(thisCpp);
  } // moveBottom(int pos)

  moveBottom(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveBottom_int')
        .asFunction();
    func(thisCpp, pos);
  } // moveBottomLeft(const QPoint & p)

  moveBottomLeft(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveBottomLeft_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // moveBottomRight(const QPoint & p)

  moveBottomRight(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveBottomRight_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // moveCenter(const QPoint & p)

  moveCenter(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveCenter_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // moveLeft(int pos)

  moveLeft(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveLeft_int')
        .asFunction();
    func(thisCpp, pos);
  } // moveRight(int pos)

  moveRight(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveRight_int')
        .asFunction();
    func(thisCpp, pos);
  } // moveTo(const QPoint & p)

  moveTo(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveTo_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // moveTo(int x, int t)

  moveTo_2(int x, int t) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__moveTo_int_int')
        .asFunction();
    func(thisCpp, x, t);
  } // moveTop(int pos)

  moveTop(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__moveTop_int')
        .asFunction();
    func(thisCpp, pos);
  } // moveTopLeft(const QPoint & p)

  moveTopLeft(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveTopLeft_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // moveTopRight(const QPoint & p)

  moveTopRight(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__moveTopRight_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // normalized() const

  QRect normalized() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__normalized')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // right() const

  int right() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__right')
        .asFunction();
    return func(thisCpp);
  } // setBottom(int pos)

  setBottom(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setBottom_int')
        .asFunction();
    func(thisCpp, pos);
  } // setBottomLeft(const QPoint & p)

  setBottomLeft(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setBottomLeft_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // setBottomRight(const QPoint & p)

  setBottomRight(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setBottomRight_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // setCoords(int x1, int y1, int x2, int y2)

  setCoords(int x1, int y1, int x2, int y2) {
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__setCoords_int_int_int_int')
        .asFunction();
    func(thisCpp, x1, y1, x2, y2);
  } // setHeight(int h)

  setHeight(int h) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setHeight_int')
        .asFunction();
    func(thisCpp, h);
  } // setLeft(int pos)

  setLeft(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setLeft_int')
        .asFunction();
    func(thisCpp, pos);
  } // setRect(int x, int y, int w, int h)

  setRect(int x, int y, int w, int h) {
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__setRect_int_int_int_int')
        .asFunction();
    func(thisCpp, x, y, w, h);
  } // setRight(int pos)

  setRight(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setRight_int')
        .asFunction();
    func(thisCpp, pos);
  } // setSize(const QSize & s)

  setSize(QSize? s) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setSize_QSize')
        .asFunction();
    func(thisCpp, s == null ? ffi.nullptr : s.thisCpp);
  } // setTop(int pos)

  setTop(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setTop_int')
        .asFunction();
    func(thisCpp, pos);
  } // setTopLeft(const QPoint & p)

  setTopLeft(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setTopLeft_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // setTopRight(const QPoint & p)

  setTopRight(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__setTopRight_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // setWidth(int w)

  setWidth(int w) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setWidth_int')
        .asFunction();
    func(thisCpp, w);
  } // setX(int x)

  setX(int x) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setX_int')
        .asFunction();
    func(thisCpp, x);
  } // setY(int y)

  setY(int y) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QRect__setY_int')
        .asFunction();
    func(thisCpp, y);
  } // size() const

  QSize size() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>('c_QRect__size')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // top() const

  int top() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__top')
        .asFunction();
    return func(thisCpp);
  } // topLeft() const

  QPoint topLeft() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__topLeft')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // topRight() const

  QPoint topRight() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__topRight')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // translate(const QPoint & p)

  translate(QPoint? p) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QRect__translate_QPoint')
        .asFunction();
    func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
  } // translate(int dx, int dy)

  translate_2(int dx, int dy) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__translate_int_int')
        .asFunction();
    func(thisCpp, dx, dy);
  } // translated(const QPoint & p) const

  QRect translated(QPoint? p) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__translated_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, p == null ? ffi.nullptr : p.thisCpp);
    return QRect.fromCppPointer(result, true);
  } // translated(int dx, int dy) const

  QRect translated_2(int dx, int dy) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QRect__translated_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, dx, dy);
    return QRect.fromCppPointer(result, true);
  } // transposed() const

  QRect transposed() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QRect__transposed')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // united(const QRect & other) const

  QRect united(QRect? other) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QRect__united_QRect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, other == null ? ffi.nullptr : other.thisCpp);
    return QRect.fromCppPointer(result, true);
  } // width() const

  int width() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__width')
        .asFunction();
    return func(thisCpp);
  } // x() const

  int x() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__x')
        .asFunction();
    return func(thisCpp);
  } // y() const

  int y() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QRect__y')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QRect__destructor')
        .asFunction();
    func(thisCpp);
  }
}
