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
        'c_QByteArray_Finalizer');

class QByteArray {
  static var s_dartInstanceByCppPtr = Map<int, QByteArray>();
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
  } //QByteArray(const char * arg__1, int size)
  QByteArray.ctor2(String? arg__1, {int size = -1}) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_QByteArray__constructor_char_int')
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
  } // append(const char * s, int len)

  QByteArray append_3(String? s, int len) {
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__append_char_int')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  } // at(int i) const

  String at(int i) {
    final char_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__at_int')
        .asFunction();
    return String.fromCharCode(func(thisCpp, i));
  } // back() const

  String back() {
    final char_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_FFI>>(
            'c_QByteArray__back')
        .asFunction();
    return String.fromCharCode(func(thisCpp));
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
  } // chop(int n)

  chop(int n) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__chop_int')
        .asFunction();
    func(thisCpp, n);
  } // chopped(int len) const

  QByteArray chopped(int len) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__chopped_int')
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
  } // compare(const QByteArray & a) const

  int compare(QByteArray? a) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__compare_QByteArray')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  } // compare(const char * c) const

  int compare_2(String? c) {
    final int_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_FFI>>(
            'c_QByteArray__compare_char')
        .asFunction();
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr);
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
  } // contains(const QByteArray & a) const

  bool contains(QByteArray? a) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__contains_QByteArray')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp) != 0;
  } // contains(const char * a) const

  bool contains_2(String? a) {
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QByteArray__contains_char')
        .asFunction();
    return func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // count() const

  int count() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QByteArray__count')
        .asFunction();
    return func(thisCpp);
  } // count(const QByteArray & a) const

  int count_2(QByteArray? a) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__count_QByteArray')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  } // count(const char * a) const

  int count_3(String? a) {
    final int_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_FFI>>(
            'c_QByteArray__count_char')
        .asFunction();
    return func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr);
  } // detach()

  detach() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__detach')
        .asFunction();
    func(thisCpp);
  } // endsWith(const QByteArray & a) const

  bool endsWith(QByteArray? a) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__endsWith_QByteArray')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp) != 0;
  } // endsWith(const char * c) const

  bool endsWith_2(String? c) {
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QByteArray__endsWith_char')
        .asFunction();
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // expand(int i)

  expand(int i) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__expand_int')
        .asFunction();
    func(thisCpp, i);
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

  static // fromRawData(const char * arg__1, int size)
      QByteArray fromRawData(String? arg__1, int size) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QByteArray__fromRawData_char_int')
        .asFunction();
    ffi.Pointer<void> result =
        func(arg__1?.toNativeUtf8() ?? ffi.nullptr, size);
    return QByteArray.fromCppPointer(result, true);
  } // front() const

  String front() {
    final char_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_FFI>>(
            'c_QByteArray__front')
        .asFunction();
    return String.fromCharCode(func(thisCpp));
  } // indexOf(const QByteArray & a, int from) const

  int indexOf(QByteArray? a, {int from = 0}) {
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__indexOf_QByteArray_int')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp, from);
  } // indexOf(const char * c, int from) const

  int indexOf_2(String? c, {int from = 0}) {
    final int_Func_voidstar_string_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__indexOf_char_int')
        .asFunction();
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr, from);
  } // insert(int i, const QByteArray & a)

  QByteArray insert(int i, QByteArray? a) {
    final voidstar_Func_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_QByteArray__insert_int_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // insert(int i, const char * s)

  QByteArray insert_2(int i, String? s) {
    final voidstar_Func_voidstar_int_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_string_FFI>>(
            'c_QByteArray__insert_int_char')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // insert(int i, const char * s, int len)

  QByteArray insert_3(int i, String? s, int len) {
    final voidstar_Func_voidstar_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__insert_int_char_int')
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
  } // lastIndexOf(const QByteArray & a, int from) const

  int lastIndexOf(QByteArray? a, {int from = -1}) {
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__lastIndexOf_QByteArray_int')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp, from);
  } // lastIndexOf(const char * c, int from) const

  int lastIndexOf_2(String? c, {int from = -1}) {
    final int_Func_voidstar_string_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__lastIndexOf_char_int')
        .asFunction();
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr, from);
  } // left(int len) const

  QByteArray left(int len) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__left_int')
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
  } // mid(int index, int len) const

  QByteArray mid(int index, {int len = -1}) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__mid_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index, len);
    return QByteArray.fromCppPointer(result, true);
  } // nulTerminated() const

  QByteArray nulTerminated() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__nulTerminated')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
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
  } // prepend(const char * s, int len)

  QByteArray prepend_3(String? s, int len) {
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__prepend_char_int')
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
  } // push_back(const char * c)

  push_back_2(String? c) {
    final void_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_string_FFI>>(
            'c_QByteArray__push_back_char')
        .asFunction();
    func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr);
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
  } // remove(int index, int len)

  QByteArray remove(int index, int len) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__remove_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index, len);
    return QByteArray.fromCppPointer(result, false);
  } // repeated(int times) const

  QByteArray repeated(int times) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__repeated_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, times);
    return QByteArray.fromCppPointer(result, true);
  } // replace(const QByteArray & before, const QByteArray & after)

  QByteArray replace(QByteArray? before, QByteArray? after) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_QByteArray__replace_QByteArray_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before == null ? ffi.nullptr : before.thisCpp,
        after == null ? ffi.nullptr : after.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // replace(const QByteArray & before, const char * after)

  QByteArray replace_2(QByteArray? before, String? after) {
    final voidstar_Func_voidstar_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_string_FFI>>(
            'c_QByteArray__replace_QByteArray_char')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before == null ? ffi.nullptr : before.thisCpp,
        after?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // replace(const char * before, const QByteArray & after)

  QByteArray replace_3(String? before, QByteArray? after) {
    final voidstar_Func_voidstar_string_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_voidstar_FFI>>(
            'c_QByteArray__replace_char_QByteArray')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        after == null ? ffi.nullptr : after.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // replace(const char * before, const char * after)

  QByteArray replace_4(String? before, String? after) {
    final voidstar_Func_voidstar_string_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_string_FFI>>(
            'c_QByteArray__replace_char_char')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        after?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // replace(const char * before, int bsize, const char * after, int asize)

  QByteArray replace_5(String? before, int bsize, String? after, int asize) {
    final voidstar_Func_voidstar_string_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__replace_char_int_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        bsize,
        after?.toNativeUtf8() ?? ffi.nullptr,
        asize);
    return QByteArray.fromCppPointer(result, false);
  } // replace(int index, int len, const QByteArray & s)

  QByteArray replace_6(int index, int len, QByteArray? s) {
    final voidstar_Func_voidstar_int_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_FFI>>(
            'c_QByteArray__replace_int_int_QByteArray')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s == null ? ffi.nullptr : s.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  } // replace(int index, int len, const char * s)

  QByteArray replace_7(int index, int len, String? s) {
    final voidstar_Func_voidstar_int_int_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_string_FFI>>(
            'c_QByteArray__replace_int_int_char')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  } // replace(int index, int len, const char * s, int alen)

  QByteArray replace_8(int index, int len, String? s, int alen) {
    final voidstar_Func_voidstar_int_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__replace_int_int_char_int')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s?.toNativeUtf8() ?? ffi.nullptr, alen);
    return QByteArray.fromCppPointer(result, false);
  } // reserve(int size)

  reserve(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__reserve_int')
        .asFunction();
    func(thisCpp, size);
  } // resize(int size)

  resize(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__resize_int')
        .asFunction();
    func(thisCpp, size);
  } // right(int len) const

  QByteArray right(int len) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__right_int')
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
  } // squeeze()

  squeeze() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__squeeze')
        .asFunction();
    func(thisCpp);
  } // startsWith(const QByteArray & a) const

  bool startsWith(QByteArray? a) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__startsWith_QByteArray')
        .asFunction();
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp) != 0;
  } // startsWith(const char * c) const

  bool startsWith_2(String? c) {
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QByteArray__startsWith_char')
        .asFunction();
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // toBase64() const

  QByteArray toBase64() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toBase64')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // toHex() const

  QByteArray toHex() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toHex')
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
  } // truncate(int pos)

  truncate(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__truncate_int')
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
