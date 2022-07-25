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
        'c_QByteArray_Finalizer');

class QByteArray {
//tag=1060
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
//tag=1024
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

//tag=1061
  factory QByteArray.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QByteArray.fromCppPointer(cppPointer, needsAutoDelete)) as QByteArray;
  }
  QByteArray.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  QByteArray.init() {}
//tag=1023
//QByteArray()
  QByteArray() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QByteArray__constructor')
        .asFunction();
    thisCpp = func();
    QByteArray.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1023
//QByteArray(const char * arg__1, int size)
  QByteArray.ctor2(String? arg__1, {int size = -1}) {
//tag=1075
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_QByteArray__constructor_char_int')
        .asFunction();
    thisCpp = func(arg__1?.toNativeUtf8() ?? ffi.nullptr, size);
    QByteArray.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1024

//tag=1027
// append(const QByteArray & a)
  QByteArray append_1(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__append_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// append(const char * s)
  QByteArray append_2(String? s) {
//tag=1028
    final voidstar_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_FFI>>(
            'c_QByteArray__append_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// append(const char * s, int len)
  QByteArray append_3(String? s, int len) {
//tag=1028
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__append_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// at(int i) const
  String at(int i) {
//tag=1028
    final char_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__at_int')
        .asFunction();
//tag=1031
    return String.fromCharCode(func(thisCpp, i));
  }
//tag=1024

//tag=1027
// back() const
  String back() {
//tag=1028
    final char_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_FFI>>(
            'c_QByteArray__back')
        .asFunction();
//tag=1031
    return String.fromCharCode(func(thisCpp));
  }
//tag=1024

//tag=1027
// capacity() const
  int capacity() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QByteArray__capacity')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// cbegin() const
  String cbegin() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__cbegin')
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }
//tag=1024

//tag=1027
// cend() const
  String cend() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__cend')
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }
//tag=1024

//tag=1027
// chop(int n)
  chop(int n) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__chop_int')
        .asFunction();
//tag=1030
    func(thisCpp, n);
  }
//tag=1024

//tag=1027
// chopped(int len) const
  QByteArray chopped(int len) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__chopped_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, len);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// clear()
  clear() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__clear')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// compare(const QByteArray & a) const
  int compare(QByteArray? a) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__compare_QByteArray')
        .asFunction();
//tag=1031
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  }
//tag=1024

//tag=1027
// compare(const char * c) const
  int compare_2(String? c) {
//tag=1028
    final int_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_FFI>>(
            'c_QByteArray__compare_char')
        .asFunction();
//tag=1031
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// constBegin() const
  String constBegin() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__constBegin')
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }
//tag=1024

//tag=1027
// constData() const
  String constData() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__constData')
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }
//tag=1024

//tag=1027
// constEnd() const
  String constEnd() {
//tag=1028
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            'c_QByteArray__constEnd')
        .asFunction();
//tag=1032
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }
//tag=1024

//tag=1027
// contains(const QByteArray & a) const
  bool contains_1(QByteArray? a) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__contains_QByteArray')
        .asFunction();
//tag=1029
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// contains(const char * a) const
  bool contains_2(String? a) {
//tag=1028
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QByteArray__contains_char')
        .asFunction();
//tag=1029
    return func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// count() const
  int count() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QByteArray__count')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// count(const QByteArray & a) const
  int count_2(QByteArray? a) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__count_QByteArray')
        .asFunction();
//tag=1031
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  }
//tag=1024

//tag=1027
// count(const char * a) const
  int count_3(String? a) {
//tag=1028
    final int_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_FFI>>(
            'c_QByteArray__count_char')
        .asFunction();
//tag=1031
    return func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// detach()
  detach() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__detach')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// endsWith(const QByteArray & a) const
  bool endsWith_1(QByteArray? a) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__endsWith_QByteArray')
        .asFunction();
//tag=1029
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// endsWith(const char * c) const
  bool endsWith_2(String? c) {
//tag=1028
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QByteArray__endsWith_char')
        .asFunction();
//tag=1029
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// expand(int i)
  expand(int i) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__expand_int')
        .asFunction();
//tag=1030
    func(thisCpp, i);
  }

//tag=1024
  static
//tag=1027
// fromBase64(const QByteArray & base64)
      QByteArray fromBase64(QByteArray? base64) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__fromBase64_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(base64 == null ? ffi.nullptr : base64.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromHex(const QByteArray & hexEncoded)
      QByteArray fromHex(QByteArray? hexEncoded) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__fromHex_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(hexEncoded == null ? ffi.nullptr : hexEncoded.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromRawData(const char * arg__1, int size)
      QByteArray fromRawData(String? arg__1, int size) {
//tag=1028
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QByteArray__fromRawData_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(arg__1?.toNativeUtf8() ?? ffi.nullptr, size);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// front() const
  String front() {
//tag=1028
    final char_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<char_Func_voidstar_FFI>>(
            'c_QByteArray__front')
        .asFunction();
//tag=1031
    return String.fromCharCode(func(thisCpp));
  }
//tag=1024

//tag=1027
// indexOf(const QByteArray & a, int from) const
  int indexOf_1(QByteArray? a, {int from = 0}) {
//tag=1028
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__indexOf_QByteArray_int')
        .asFunction();
//tag=1031
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp, from);
  }
//tag=1024

//tag=1027
// indexOf(const char * c, int from) const
  int indexOf_2(String? c, {int from = 0}) {
//tag=1028
    final int_Func_voidstar_string_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__indexOf_char_int')
        .asFunction();
//tag=1031
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr, from);
  }
//tag=1024

//tag=1027
// insert(int i, const QByteArray & a)
  QByteArray insert_1(int i, QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_QByteArray__insert_int_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, i, a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// insert(int i, const char * s)
  QByteArray insert_2(int i, String? s) {
//tag=1028
    final voidstar_Func_voidstar_int_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_string_FFI>>(
            'c_QByteArray__insert_int_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// insert(int i, const char * s, int len)
  QByteArray insert_3(int i, String? s, int len) {
//tag=1028
    final voidstar_Func_voidstar_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__insert_int_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// isDetached() const
  bool isDetached() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isDetached')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isEmpty() const
  bool isEmpty() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isEmpty')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isLower() const
  bool isLower() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isLower')
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
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isNull')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isSharedWith(const QByteArray & other) const
  bool isSharedWith(QByteArray? other) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__isSharedWith_QByteArray')
        .asFunction();
//tag=1029
    return func(thisCpp, other == null ? ffi.nullptr : other.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isUpper() const
  bool isUpper() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QByteArray__isUpper')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// lastIndexOf(const QByteArray & a, int from) const
  int lastIndexOf_1(QByteArray? a, {int from = -1}) {
//tag=1028
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__lastIndexOf_QByteArray_int')
        .asFunction();
//tag=1031
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp, from);
  }
//tag=1024

//tag=1027
// lastIndexOf(const char * c, int from) const
  int lastIndexOf_2(String? c, {int from = -1}) {
//tag=1028
    final int_Func_voidstar_string_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__lastIndexOf_char_int')
        .asFunction();
//tag=1031
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr, from);
  }
//tag=1024

//tag=1027
// left(int len) const
  QByteArray left(int len) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__left_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, len);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// length() const
  int length() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QByteArray__length')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// mid(int index, int len) const
  QByteArray mid(int index, {int len = -1}) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__mid_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, index, len);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// nulTerminated() const
  QByteArray nulTerminated() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__nulTerminated')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// number(int arg__1, int base)
      QByteArray number_1(int arg__1, {int base = 10}) {
//tag=1028
    final voidstar_Func_int_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_ffi_Int32_FFI>>(
            'c_static_QByteArray__number_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(arg__1, base);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// prepend(const QByteArray & a)
  QByteArray prepend_1(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__prepend_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// prepend(const char * s)
  QByteArray prepend_2(String? s) {
//tag=1028
    final voidstar_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_FFI>>(
            'c_QByteArray__prepend_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// prepend(const char * s, int len)
  QByteArray prepend_3(String? s, int len) {
//tag=1028
    final voidstar_Func_voidstar_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_FFI>>(
            'c_QByteArray__prepend_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, len);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// push_back(const QByteArray & a)
  push_back_1(QByteArray? a) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__push_back_QByteArray')
        .asFunction();
//tag=1030
    func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  }
//tag=1024

//tag=1027
// push_back(const char * c)
  push_back_2(String? c) {
//tag=1028
    final void_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_string_FFI>>(
            'c_QByteArray__push_back_char')
        .asFunction();
//tag=1030
    func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// push_front(const QByteArray & a)
  push_front_1(QByteArray? a) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__push_front_QByteArray')
        .asFunction();
//tag=1030
    func(thisCpp, a == null ? ffi.nullptr : a.thisCpp);
  }
//tag=1024

//tag=1027
// push_front(const char * c)
  push_front_2(String? c) {
//tag=1028
    final void_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_string_FFI>>(
            'c_QByteArray__push_front_char')
        .asFunction();
//tag=1030
    func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// remove(int index, int len)
  QByteArray remove(int index, int len) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__remove_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, index, len);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// repeated(int times) const
  QByteArray repeated(int times) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__repeated_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, times);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// replace(const QByteArray & before, const char * after)
  QByteArray replace_2(QByteArray? before, String? after) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_string_FFI>>(
            'c_QByteArray__replace_QByteArray_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        before == null ? ffi.nullptr : before.thisCpp,
        after?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(const char * before, const QByteArray & after)
  QByteArray replace_3(String? before, QByteArray? after) {
//tag=1028
    final voidstar_Func_voidstar_string_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_voidstar_FFI>>(
            'c_QByteArray__replace_char_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        after == null ? ffi.nullptr : after.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(const char * before, const char * after)
  QByteArray replace_4(String? before, String? after) {
//tag=1028
    final voidstar_Func_voidstar_string_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_string_string_FFI>>(
            'c_QByteArray__replace_char_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        after?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(const char * before, int bsize, const char * after, int asize)
  QByteArray replace_5(String? before, int bsize, String? after, int asize) {
//tag=1028
    final voidstar_Func_voidstar_string_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_string_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__replace_char_int_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        bsize,
        after?.toNativeUtf8() ?? ffi.nullptr,
        asize);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(int index, int len, const QByteArray & s)
  QByteArray replace_6(int index, int len, QByteArray? s) {
//tag=1028
    final voidstar_Func_voidstar_int_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_FFI>>(
            'c_QByteArray__replace_int_int_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s == null ? ffi.nullptr : s.thisCpp);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(int index, int len, const char * s)
  QByteArray replace_7(int index, int len, String? s) {
//tag=1028
    final voidstar_Func_voidstar_int_int_string func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_string_FFI>>(
            'c_QByteArray__replace_int_int_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(int index, int len, const char * s, int alen)
  QByteArray replace_8(int index, int len, String? s, int alen) {
//tag=1028
    final voidstar_Func_voidstar_int_int_string_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_string_ffi_Int32_FFI>>(
            'c_QByteArray__replace_int_int_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, index, len, s?.toNativeUtf8() ?? ffi.nullptr, alen);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// reserve(int size)
  reserve(int size) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__reserve_int')
        .asFunction();
//tag=1030
    func(thisCpp, size);
  }
//tag=1024

//tag=1027
// resize(int size)
  resize(int size) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__resize_int')
        .asFunction();
//tag=1030
    func(thisCpp, size);
  }
//tag=1024

//tag=1027
// right(int len) const
  QByteArray right(int len) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__right_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, len);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// setNum(int arg__1, int base)
  QByteArray setNum_2(int arg__1, {int base = 10}) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QByteArray__setNum_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, arg__1, base);
    return QByteArray.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// shrink_to_fit()
  shrink_to_fit() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__shrink_to_fit')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// simplified()
  QByteArray simplified() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__simplified')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// simplified_helper(QByteArray & a)
      QByteArray simplified_helper(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__simplified_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// simplified_helper(const QByteArray & a)
      QByteArray simplified_helper_2(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__simplified_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// size() const
  int size() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QByteArray__size')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// squeeze()
  squeeze() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__squeeze')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// startsWith(const QByteArray & a) const
  bool startsWith_1(QByteArray? a) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QByteArray__startsWith_QByteArray')
        .asFunction();
//tag=1029
    return func(thisCpp, a == null ? ffi.nullptr : a.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// startsWith(const char * c) const
  bool startsWith_2(String? c) {
//tag=1028
    final bool_Func_voidstar_string func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_string_FFI>>(
            'c_QByteArray__startsWith_char')
        .asFunction();
//tag=1029
    return func(thisCpp, c?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// toBase64() const
  QByteArray toBase64() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toBase64')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toHex() const
  QByteArray toHex() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toHex')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toLower()
  QByteArray toLower() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toLower')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toLower_helper(QByteArray & a)
      QByteArray toLower_helper(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toLower_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toLower_helper(const QByteArray & a)
      QByteArray toLower_helper_2(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toLower_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toUpper()
  QByteArray toUpper() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__toUpper')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toUpper_helper(QByteArray & a)
      QByteArray toUpper_helper(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toUpper_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toUpper_helper(const QByteArray & a)
      QByteArray toUpper_helper_2(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__toUpper_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// trimmed()
  QByteArray trimmed() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QByteArray__trimmed')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// trimmed_helper(QByteArray & a)
      QByteArray trimmed_helper(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__trimmed_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// trimmed_helper(const QByteArray & a)
      QByteArray trimmed_helper_2(QByteArray? a) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QByteArray__trimmed_helper_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(a == null ? ffi.nullptr : a.thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// truncate(int pos)
  truncate(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QByteArray__truncate_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QByteArray__destructor')
        .asFunction();
    func(thisCpp);
  }
}
