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
import '../Bindings_KDDWBindingsCore.dart' as KDDWBindingsCore;
import '../Bindings_KDDWBindingsFlutter.dart' as KDDWBindingsFlutter;
import '../LibraryLoader.dart';

var _dylib = Library.instance().dylib;
final _finalizerFunc =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_KDDockWidgets__Rect_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class Rect implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, Rect>();
  var _thisCpp = null;
  bool _needsAutoDelete = true;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete) _finalizer.attach(this, ptrvoid);
  }

  static bool isCached(var cppPointer) {
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory Rect.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        Rect.fromCppPointer(cppPointer, needsAutoDelete)) as Rect;
  }
  Rect.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  Rect.init() {} //Rect()
  Rect() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Rect__constructor')
        .asFunction();
    thisCpp = func();
    Rect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //Rect(KDDockWidgets::Point pos, KDDockWidgets::Size size)
  Rect.ctor2(Point pos, Size size) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__constructor_Point_Size')
        .asFunction();
    thisCpp = func(pos == null ? ffi.nullptr : pos.thisCpp,
        size == null ? ffi.nullptr : size.thisCpp);
    Rect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //Rect(int x, int y, int width, int height)
  Rect.ctor3(int x, int y, int width, int height) {
    final voidstar_Func_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__constructor_int_int_int_int')
        .asFunction();
    thisCpp = func(x, y, width, height);
    Rect.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // adjust(int arg__1, int arg__2, int arg__3, int arg__4) const
  adjust(int arg__1, int arg__2, int arg__3, int arg__4) {
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__adjust_int_int_int_int')
        .asFunction();
    func(thisCpp, arg__1, arg__2, arg__3, arg__4);
  } // adjusted(int arg__1, int arg__2, int arg__3, int arg__4) const

  Rect adjusted(int arg__1, int arg__2, int arg__3, int arg__4) {
    final voidstar_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__adjusted_int_int_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1, arg__2, arg__3, arg__4);
    return Rect.fromCppPointer(result, true);
  } // bottom() const

  int bottom() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__bottom')
        .asFunction();
    return func(thisCpp);
  } // bottomLeft() const

  Point bottomLeft() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__bottomLeft')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // bottomRight() const

  Point bottomRight() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__bottomRight')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // center() const

  Point center() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__center')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // contains(KDDockWidgets::Point pt) const

  bool contains(Point pt) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__contains_Point')
        .asFunction();
    return func(thisCpp, pt == null ? ffi.nullptr : pt.thisCpp) != 0;
  } // contains(KDDockWidgets::Rect arg__1) const

  bool contains_2(Rect arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__contains_Rect')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // height() const

  int height() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__height')
        .asFunction();
    return func(thisCpp);
  } // intersected(KDDockWidgets::Rect arg__1) const

  Rect intersected(Rect arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__intersected_Rect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Rect.fromCppPointer(result, true);
  } // intersects(KDDockWidgets::Rect arg__1) const

  bool intersects(Rect arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__intersects_Rect')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__isEmpty')
        .asFunction();
    return func(thisCpp) != 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__isNull')
        .asFunction();
    return func(thisCpp) != 0;
  } // isValid() const

  bool isValid() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__isValid')
        .asFunction();
    return func(thisCpp) != 0;
  } // left() const

  int left() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__left')
        .asFunction();
    return func(thisCpp);
  } // moveBottom(int arg__1)

  moveBottom(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__moveBottom_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // moveCenter(KDDockWidgets::Point arg__1)

  moveCenter(Point arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__moveCenter_Point')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // moveLeft(int x)

  moveLeft(int x) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__moveLeft_int')
        .asFunction();
    func(thisCpp, x);
  } // moveRight(int arg__1)

  moveRight(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__moveRight_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // moveTo(KDDockWidgets::Point arg__1)

  moveTo(Point arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__moveTo_Point')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // moveTo(int arg__1, int arg__2)

  moveTo_2(int arg__1, int arg__2) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__moveTo_int_int')
        .asFunction();
    func(thisCpp, arg__1, arg__2);
  } // moveTop(int y)

  moveTop(int y) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__moveTop_int')
        .asFunction();
    func(thisCpp, y);
  } // moveTopLeft(KDDockWidgets::Point pt)

  moveTopLeft(Point pt) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__moveTopLeft_Point')
        .asFunction();
    func(thisCpp, pt == null ? ffi.nullptr : pt.thisCpp);
  } // pos() const

  Point pos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__pos')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // right() const

  int right() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__right')
        .asFunction();
    return func(thisCpp);
  } // setBottom(int arg__1)

  setBottom(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setBottom_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // setHeight(int h)

  setHeight(int h) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setHeight_int')
        .asFunction();
    func(thisCpp, h);
  } // setLeft(int x)

  setLeft(int x) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setLeft_int')
        .asFunction();
    func(thisCpp, x);
  } // setRight(int r)

  setRight(int r) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setRight_int')
        .asFunction();
    func(thisCpp, r);
  } // setSize(KDDockWidgets::Size sz)

  setSize(Size sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__setSize_Size')
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  } // setTop(int arg__1)

  setTop(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setTop_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // setTopLeft(KDDockWidgets::Point arg__1)

  setTopLeft(Point arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__setTopLeft_Point')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setWidth(int w)

  setWidth(int w) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setWidth_int')
        .asFunction();
    func(thisCpp, w);
  } // setX(int arg__1)

  setX(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setX_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // setY(int arg__1)

  setY(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Rect__setY_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // size() const

  Size size() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__size')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  } // top() const

  int top() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__top')
        .asFunction();
    return func(thisCpp);
  } // topLeft() const

  Point topLeft() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__topLeft')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // topRight() const

  Point topRight() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__topRight')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // translate(KDDockWidgets::Point arg__1)

  translate(Point arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__translate_Point')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // width() const

  int width() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__width')
        .asFunction();
    return func(thisCpp);
  } // x() const

  int x() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__x')
        .asFunction();
    return func(thisCpp);
  } // y() const

  int y() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__y')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Rect__destructor')
        .asFunction();
    func(thisCpp);
  }
}
