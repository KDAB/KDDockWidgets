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
        'c_QByteArray_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class QByteArray implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, QByteArray>();
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

  factory QByteArray.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QByteArray.fromCppPointer(cppPointer, needsAutoDelete)) as QByteArray;
  }
  QByteArray.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  QByteArray.init() {} //QByteArray()
  QByteArray() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QByteArray__constructor')
        .asFunction();
    thisCpp = func();
    QByteArray.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QByteArray(const char * arg__1, qsizetype size)
  QByteArray.ctor2(String? arg__1, {int size = -1}) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_QByteArray__constructor_char_qsizetype')
        .asFunction();
    thisCpp = func(arg__1?.toNativeUtf8() ?? ffi.nullptr, size);
    QByteArray.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // append(const QByteArray & a)
  QByteArray append(QByteArray? a) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__append_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // append(const char * s)

  QByteArray append_2(String? s) {
    final voidstar_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_FFI>>(
            'c_QByteArray__append_char')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // append(const char * s, qsizetype len)

  QByteArray append_3(String? s, int len) {
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__append_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  } // at(qsizetype i) const

  String at(int i) {
    final char_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__at_qsizetype')
        .asFunction();
    return String.fromCharCode(func(thisCpp, i));
  } // capacity() const

  int capacity() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QByteArray__capacity')
        .asFunction();
    return func(thisCpp);
  } // cbegin() const

  String cbegin() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__cbegin')
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  } // cend() const

  String cend() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__cend')
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  } // chop(qsizetype n)

  chop(int n) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__chop_qsizetype')
        .asFunction();
    func(thisCpp, n);
  } // chopped(qsizetype len) const

  QByteArray chopped(int len) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__chopped_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, len);
    return QByteArray.fromCppPointer(result, true);
  } // clear()

  clear() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__clear')
        .asFunction();
    func(thisCpp);
  } // constBegin() const

  String constBegin() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__constBegin')
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  } // constData() const

  String constData() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__constData')
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  } // constEnd() const

  String constEnd() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__constEnd')
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  } // detach()

  detach() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__detach')
        .asFunction();
    func(thisCpp);
  } // expand(qsizetype i)

  expand(int i) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__expand_qsizetype')
        .asFunction();
    func(thisCpp, i);
  } // first(qsizetype n) const

  QByteArray first(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__first_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QByteArray.fromCppPointer(result, true);
  }

  static // fromBase64(const QByteArray & base64)
      QByteArray fromBase64(QByteArray? base64) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__fromBase64_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(base64 == null ? ffi.nullptr : base64.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // fromHex(const QByteArray & hexEncoded)
      QByteArray fromHex(QByteArray? hexEncoded) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__fromHex_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(hexEncoded == null ? ffi.nullptr : hexEncoded.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // fromRawData(const char * data, qsizetype size)
      QByteArray fromRawData(String? data, int size) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QByteArray__fromRawData_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(data?.toNativeUtf8() ?? ffi.nullptr, size);
    return QByteArray.fromCppPointer(result, true);
  } // insert(qsizetype i, const QByteArray & data)

  QByteArray insert(int i, QByteArray? data) {
    final voidstar_Func_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_QByteArray__insert_qsizetype_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, data == null ? ffi.nullptr : data.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // insert(qsizetype i, const char * s)

  QByteArray insert_2(int i, String? s) {
    final voidstar_Func_voidstar_int_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_string_FFI>>(
            'c_QByteArray__insert_qsizetype_char')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // insert(qsizetype i, const char * s, qsizetype len)

  QByteArray insert_3(int i, String? s, int len) {
    final voidstar_Func_voidstar_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__insert_qsizetype_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  } // isDetached() const

  bool isDetached() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isDetached')
        .asFunction();
    return func(thisCpp) != 0;
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isEmpty')
        .asFunction();
    return func(thisCpp) != 0;
  } // isLower() const

  bool isLower() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isLower')
        .asFunction();
    return func(thisCpp) != 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isNull')
        .asFunction();
    return func(thisCpp) != 0;
  } // isSharedWith(const QByteArray & other) const

  bool isSharedWith(QByteArray? other) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__isSharedWith_QByteArray')
        .asFunction();
    return func(thisCpp, other == null ? ffi.nullptr : other.thisCpp) != 0;
  } // isUpper() const

  bool isUpper() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isUpper')
        .asFunction();
    return func(thisCpp) != 0;
  } // isValidUtf8() const

  bool isValidUtf8() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isValidUtf8')
        .asFunction();
    return func(thisCpp) != 0;
  } // last(qsizetype n) const

  QByteArray last(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__last_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QByteArray.fromCppPointer(result, true);
  } // left(qsizetype len) const

  QByteArray left(int len) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__left_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, len);
    return QByteArray.fromCppPointer(result, true);
  } // length() const

  int length() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QByteArray__length')
        .asFunction();
    return func(thisCpp);
  } // mid(qsizetype index, qsizetype len) const

  QByteArray mid(int index, {int len = -1}) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__mid_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index, len);
    return QByteArray.fromCppPointer(result, true);
  }

  static // number(int arg__1, int base)
      QByteArray number(int arg__1, {int base = 10}) {
    final voidstar_Func_int_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_ffi_Int32_FFI>>(
            'c_static_QByteArray__number_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(arg__1, base);
    return QByteArray.fromCppPointer(result, true);
  } // prepend(const QByteArray & a)

  QByteArray prepend(QByteArray? a) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__prepend_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // prepend(const char * s)

  QByteArray prepend_2(String? s) {
    final voidstar_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_FFI>>(
            'c_QByteArray__prepend_char')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // prepend(const char * s, qsizetype len)

  QByteArray prepend_3(String? s, int len) {
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__prepend_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  } // push_back(const QByteArray & a)

  push_back(QByteArray? a) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__push_back_QByteArray')
        .asFunction();
    func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  } // push_back(const char * s)

  push_back_2(String? s) {
    final void_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_string_FFI>>(
            'c_QByteArray__push_back_char')
        .asFunction();
    func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  } // push_front(const QByteArray & a)

  push_front(QByteArray? a) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__push_front_QByteArray')
        .asFunction();
    func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  } // push_front(const char * c)

  push_front_2(String? c) {
    final void_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_string_FFI>>(
            'c_QByteArray__push_front_char')
        .asFunction();
    func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr);
  } // reallocGrowData(qsizetype n)

  reallocGrowData(int n) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__reallocGrowData_qsizetype')
        .asFunction();
    func(thisCpp, n);
  } // remove(qsizetype index, qsizetype len)

  QByteArray remove(int index, int len) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__remove_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index, len);
    return QByteArray.fromCppPointer(result, false);
  } // removeAt(qsizetype pos)

  QByteArray removeAt(int pos) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__removeAt_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, pos);
    return QByteArray.fromCppPointer(result, false);
  } // removeFirst()

  QByteArray removeFirst() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__removeFirst')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // removeLast()

  QByteArray removeLast() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__removeLast')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // repeated(qsizetype times) const

  QByteArray repeated(int times) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__repeated_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, times);
    return QByteArray.fromCppPointer(result, true);
  } // replace(const char * before, qsizetype bsize, const char * after, qsizetype asize)

  QByteArray replace(String? before, int bsize, String? after, int asize) {
    final voidstar_Func_voidstar_string_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__replace_char_qsizetype_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        bsize,
        after?.toNativeUtf8() ?? ffi.nullptr,
        asize);
    return QByteArray.fromCppPointer(result, false);
  } // replace(qsizetype index, qsizetype len, const char * s, qsizetype alen)

  QByteArray replace_2(int index, int len, String? s, int alen) {
    final voidstar_Func_voidstar_int_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__replace_qsizetype_qsizetype_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s?.toNativeUtf8() ?? ffi.nullptr, alen);
    return QByteArray.fromCppPointer(result, false);
  } // reserve(qsizetype size)

  reserve(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__reserve_qsizetype')
        .asFunction();
    func(thisCpp, size);
  } // resize(qsizetype size)

  resize(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__resize_qsizetype')
        .asFunction();
    func(thisCpp, size);
  } // right(qsizetype len) const

  QByteArray right(int len) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__right_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, len);
    return QByteArray.fromCppPointer(result, true);
  } // setNum(int arg__1, int base)

  QByteArray setNum(int arg__1, {int base = 10}) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__setNum_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1, base);
    return QByteArray.fromCppPointer(result, false);
  } // setRawData(const char * a, qsizetype n)

  QByteArray setRawData(String? a, int n) {
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__setRawData_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr, n);
    return QByteArray.fromCppPointer(result, false);
  } // shrink_to_fit()

  shrink_to_fit() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__shrink_to_fit')
        .asFunction();
    func(thisCpp);
  } // simplified()

  QByteArray simplified() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__simplified')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // simplified_helper(QByteArray & a)
      QByteArray simplified_helper(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__simplified_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // simplified_helper(const QByteArray & a)
      QByteArray simplified_helper_2(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__simplified_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // size() const

  int size() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QByteArray__size')
        .asFunction();
    return func(thisCpp);
  } // sliced(qsizetype pos) const

  QByteArray sliced(int pos) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__sliced_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, pos);
    return QByteArray.fromCppPointer(result, true);
  } // sliced(qsizetype pos, qsizetype n) const

  QByteArray sliced_2(int pos, int n) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__sliced_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, pos, n);
    return QByteArray.fromCppPointer(result, true);
  } // squeeze()

  squeeze() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__squeeze')
        .asFunction();
    func(thisCpp);
  } // toBase64() const

  QByteArray toBase64() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toBase64')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // toLower()

  QByteArray toLower() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toLower')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toLower_helper(QByteArray & a)
      QByteArray toLower_helper(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toLower_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toLower_helper(const QByteArray & a)
      QByteArray toLower_helper_2(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toLower_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // toUpper()

  QByteArray toUpper() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toUpper')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toUpper_helper(QByteArray & a)
      QByteArray toUpper_helper(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toUpper_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toUpper_helper(const QByteArray & a)
      QByteArray toUpper_helper_2(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toUpper_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // trimmed()

  QByteArray trimmed() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__trimmed')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // trimmed_helper(QByteArray & a)
      QByteArray trimmed_helper(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__trimmed_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // trimmed_helper(const QByteArray & a)
      QByteArray trimmed_helper_2(QByteArray? a) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__trimmed_helper_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // truncate(qsizetype pos)

  truncate(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__truncate_qsizetype')
        .asFunction();
    func(thisCpp, pos);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__destructor')
        .asFunction();
    func(thisCpp);
  }
}
