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
        'c_QString_Finalizer');

class QString {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, QString>();
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
  factory QString.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QString.fromCppPointer(cppPointer, needsAutoDelete)) as QString;
  }
  QString.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  QString.init() {}
//tag=1023
//QString()
  QString() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QString__constructor')
        .asFunction();
    thisCpp = func();
    QString.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1024

//tag=1027
// append(const QString & s)
  QString append(String? s) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QString__append_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// arg(const QString & a, int fieldWidth) const
  QString arg(String? a, {int fieldWidth = 0}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QString__arg_QString_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr, fieldWidth);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2) const
  QString arg_2(String? a1, String? a2) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_QString__arg_QString_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3) const
  QString arg_3(String? a1, String? a2, String? a3) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_voidstar_FFI>>(
            'c_QString__arg_QString_QString_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr, a3?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4) const
  QString arg_4(String? a1, String? a2, String? a3, String? a4) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_FFI>>(
            'c_QString__arg_QString_QString_QString_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr,
        a3?.toNativeUtf8() ?? ffi.nullptr,
        a4?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5) const
  QString arg_5(String? a1, String? a2, String? a3, String? a4, String? a5) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar
        func = _dylib
            .lookup<
                    ffi.NativeFunction<
                        voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_FFI>>(
                'c_QString__arg_QString_QString_QString_QString_QString')
            .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr,
        a3?.toNativeUtf8() ?? ffi.nullptr,
        a4?.toNativeUtf8() ?? ffi.nullptr,
        a5?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6) const
  QString arg_6(
      String? a1, String? a2, String? a3, String? a4, String? a5, String? a6) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar
        func = _dylib
            .lookup<
                    ffi.NativeFunction<
                        voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_FFI>>(
                'c_QString__arg_QString_QString_QString_QString_QString_QString')
            .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr,
        a3?.toNativeUtf8() ?? ffi.nullptr,
        a4?.toNativeUtf8() ?? ffi.nullptr,
        a5?.toNativeUtf8() ?? ffi.nullptr,
        a6?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7) const
  QString arg_7(String? a1, String? a2, String? a3, String? a4, String? a5,
      String? a6, String? a7) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar
        func = _dylib
            .lookup<
                    ffi.NativeFunction<
                        voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_FFI>>(
                'c_QString__arg_QString_QString_QString_QString_QString_QString_QString')
            .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr,
        a3?.toNativeUtf8() ?? ffi.nullptr,
        a4?.toNativeUtf8() ?? ffi.nullptr,
        a5?.toNativeUtf8() ?? ffi.nullptr,
        a6?.toNativeUtf8() ?? ffi.nullptr,
        a7?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8) const
  QString arg_8(String? a1, String? a2, String? a3, String? a4, String? a5,
      String? a6, String? a7, String? a8) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar
        func = _dylib
            .lookup<
                    ffi.NativeFunction<
                        voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_FFI>>(
                'c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString')
            .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr,
        a3?.toNativeUtf8() ?? ffi.nullptr,
        a4?.toNativeUtf8() ?? ffi.nullptr,
        a5?.toNativeUtf8() ?? ffi.nullptr,
        a6?.toNativeUtf8() ?? ffi.nullptr,
        a7?.toNativeUtf8() ?? ffi.nullptr,
        a8?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(const QString & a1, const QString & a2, const QString & a3, const QString & a4, const QString & a5, const QString & a6, const QString & a7, const QString & a8, const QString & a9) const
  QString arg_9(String? a1, String? a2, String? a3, String? a4, String? a5,
      String? a6, String? a7, String? a8, String? a9) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar
        func = _dylib
            .lookup<
                    ffi.NativeFunction<
                        voidstar_Func_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_voidstar_FFI>>(
                'c_QString__arg_QString_QString_QString_QString_QString_QString_QString_QString_QString')
            .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        a1?.toNativeUtf8() ?? ffi.nullptr,
        a2?.toNativeUtf8() ?? ffi.nullptr,
        a3?.toNativeUtf8() ?? ffi.nullptr,
        a4?.toNativeUtf8() ?? ffi.nullptr,
        a5?.toNativeUtf8() ?? ffi.nullptr,
        a6?.toNativeUtf8() ?? ffi.nullptr,
        a7?.toNativeUtf8() ?? ffi.nullptr,
        a8?.toNativeUtf8() ?? ffi.nullptr,
        a9?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// arg(int a, int fieldWidth, int base) const
  QString arg_10(int a, {int fieldWidth = 0, int base = 10}) {
//tag=1028
    final voidstar_Func_voidstar_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__arg_int_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, a, fieldWidth, base);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// asprintf(const char * format)
      QString asprintf(String? format) {
//tag=1028
    final voidstar_Func_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_FFI>>(
            'c_static_QString__asprintf_char')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(format?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// capacity() const
  int capacity() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QString__capacity')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// chop(int n)
  chop(int n) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__chop_int')
        .asFunction();
//tag=1030
    func(thisCpp, n);
  }
//tag=1024

//tag=1027
// chopped(int n) const
  QString chopped(int n) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__chopped_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// clear()
  clear() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>('c_QString__clear')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// compare(const QString & s) const
  int compare(String? s) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__compare_QString')
        .asFunction();
//tag=1031
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }

//tag=1024
  static
//tag=1027
// compare(const QString & s1, const QString & s2)
      int compare_2(String? s1, String? s2) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_static_QString__compare_QString_QString')
        .asFunction();
//tag=1031
    return func(
        s1?.toNativeUtf8() ?? ffi.nullptr, s2?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// contains(const QString & s) const
  bool contains(String? s) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__contains_QString')
        .asFunction();
//tag=1029
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// count() const
  int count() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QString__count')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// count(const QString & s) const
  int count_2(String? s) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__count_QString')
        .asFunction();
//tag=1031
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// detach()
  detach() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>('c_QString__detach')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// endsWith(const QString & s) const
  bool endsWith(String? s) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__endsWith_QString')
        .asFunction();
//tag=1029
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// expand(int i)
  expand(int i) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__expand_int')
        .asFunction();
//tag=1030
    func(thisCpp, i);
  }

//tag=1024
  static
//tag=1027
// fromLatin1(const QByteArray & str)
      QString fromLatin1(QByteArray? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__fromLatin1_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str == null ? ffi.nullptr : str.thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromLatin1(const char * str, int size)
      QString fromLatin1_2(String? str, {int size = -1}) {
//tag=1028
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromLatin1_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromLocal8Bit(const QByteArray & str)
      QString fromLocal8Bit(QByteArray? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__fromLocal8Bit_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str == null ? ffi.nullptr : str.thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromLocal8Bit(const char * str, int size)
      QString fromLocal8Bit_2(String? str, {int size = -1}) {
//tag=1028
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromLocal8Bit_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromLocal8Bit_helper(const char * arg__1, int size)
      QString fromLocal8Bit_helper(String? arg__1, int size) {
//tag=1028
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromLocal8Bit_helper_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(arg__1?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromUtf8(const QByteArray & str)
      QString fromUtf8(QByteArray? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__fromUtf8_QByteArray')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str == null ? ffi.nullptr : str.thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromUtf8(const char * str, int size)
      QString fromUtf8_2(String? str, {int size = -1}) {
//tag=1028
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromUtf8_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// fromUtf8_helper(const char * str, int size)
      QString fromUtf8_helper(String? str, int size) {
//tag=1028
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromUtf8_helper_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// indexOf(const QString & s, int from) const
  int indexOf(String? s, {int from = 0}) {
//tag=1028
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QString__indexOf_QString_int')
        .asFunction();
//tag=1031
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, from);
  }
//tag=1024

//tag=1027
// insert(int i, const QString & s)
  QString insert(int i, String? s) {
//tag=1028
    final voidstar_Func_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_QString__insert_int_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// isDetached() const
  bool isDetached() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isDetached')
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
            'c_QString__isEmpty')
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
            'c_QString__isLower')
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
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QString__isNull')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isRightToLeft() const
  bool isRightToLeft() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isRightToLeft')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isSharedWith(const QString & other) const
  bool isSharedWith(String? other) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__isSharedWith_QString')
        .asFunction();
//tag=1029
    return func(thisCpp, other?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// isSimpleText() const
  bool isSimpleText() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isSimpleText')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isUpper() const
  bool isUpper() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isUpper')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isValidUtf16() const
  bool isValidUtf16() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isValidUtf16')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// lastIndexOf(const QString & s, int from) const
  int lastIndexOf(String? s, {int from = -1}) {
//tag=1028
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QString__lastIndexOf_QString_int')
        .asFunction();
//tag=1031
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, from);
  }
//tag=1024

//tag=1027
// left(int n) const
  QString left(int n) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__left_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// leftJustified(int width) const
  QString leftJustified(int width) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__leftJustified_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, width);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// length() const
  int length() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QString__length')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// localeAwareCompare(const QString & s) const
  int localeAwareCompare(String? s) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__localeAwareCompare_QString')
        .asFunction();
//tag=1031
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }

//tag=1024
  static
//tag=1027
// localeAwareCompare(const QString & s1, const QString & s2)
      int localeAwareCompare_2(String? s1, String? s2) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_static_QString__localeAwareCompare_QString_QString')
        .asFunction();
//tag=1031
    return func(
        s1?.toNativeUtf8() ?? ffi.nullptr, s2?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// mid(int position, int n) const
  QString mid(int position, {int n = -1}) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__mid_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, position, n);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// number(int arg__1, int base)
      QString number(int arg__1, {int base = 10}) {
//tag=1028
    final voidstar_Func_int_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_ffi_Int32_FFI>>(
            'c_static_QString__number_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(arg__1, base);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// prepend(const QString & s)
  QString prepend(String? s) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QString__prepend_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// push_back(const QString & s)
  push_back(String? s) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QString__push_back_QString')
        .asFunction();
//tag=1030
    func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// push_front(const QString & s)
  push_front(String? s) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QString__push_front_QString')
        .asFunction();
//tag=1030
    func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }
//tag=1024

//tag=1027
// remove(const QString & s)
  QString remove(String? s) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QString__remove_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// remove(int i, int len)
  QString remove_2(int i, int len) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__remove_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, i, len);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// repeated(int times) const
  QString repeated(int times) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__repeated_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, times);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// replace(const QString & before, const QString & after)
  QString replace(String? before, String? after) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_QString__replace_QString_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        after?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// replace(int i, int len, const QString & after)
  QString replace_2(int i, int len, String? after) {
//tag=1028
    final voidstar_Func_voidstar_int_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_FFI>>(
            'c_QString__replace_int_int_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, i, len, after?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// reserve(int size)
  reserve(int size) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__reserve_int')
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
            'c_QString__resize_int')
        .asFunction();
//tag=1030
    func(thisCpp, size);
  }
//tag=1024

//tag=1027
// right(int n) const
  QString right(int n) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__right_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// rightJustified(int width) const
  QString rightJustified(int width) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__rightJustified_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, width);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// section(const QString & in_sep, int start, int end) const
  QString section(String? in_sep, int start, {int end = -1}) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__section_QString_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, in_sep?.toNativeUtf8() ?? ffi.nullptr, start, end);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// setNum(int arg__1, int base)
  QString setNum(int arg__1, {int base = 10}) {
//tag=1028
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__setNum_int_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, arg__1, base);
    return QString.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// shrink_to_fit()
  shrink_to_fit() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QString__shrink_to_fit')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// simplified()
  QString simplified() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__simplified')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// simplified_helper(QString & str)
      QString simplified_helper(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__simplified_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// simplified_helper(const QString & str)
      QString simplified_helper_2(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__simplified_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// size() const
  int size() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QString__size')
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
            'c_QString__squeeze')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// startsWith(const QString & s) const
  bool startsWith(String? s) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__startsWith_QString')
        .asFunction();
//tag=1029
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }
//tag=1024

//tag=1027
// toCaseFolded()
  QString toCaseFolded() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toCaseFolded')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toCaseFolded_helper(QString & str)
      QString toCaseFolded_helper(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toCaseFolded_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toCaseFolded_helper(const QString & str)
      QString toCaseFolded_helper_2(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toCaseFolded_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toHtmlEscaped() const
  QString toHtmlEscaped() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toHtmlEscaped')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toLatin1()
  QByteArray toLatin1() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toLatin1')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toLatin1_helper(const QString & arg__1)
      QByteArray toLatin1_helper(String? arg__1) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLatin1_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toLatin1_helper_inplace(QString & arg__1)
      QByteArray toLatin1_helper_inplace(String? arg__1) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLatin1_helper_inplace_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toLocal8Bit()
  QByteArray toLocal8Bit() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toLocal8Bit')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toLower()
  QString toLower() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toLower')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toLower_helper(QString & str)
      QString toLower_helper(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLower_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toLower_helper(const QString & str)
      QString toLower_helper_2(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLower_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toUpper()
  QString toUpper() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toUpper')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toUpper_helper(QString & str)
      QString toUpper_helper(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toUpper_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toUpper_helper(const QString & str)
      QString toUpper_helper_2(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toUpper_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// toUtf8()
  QByteArray toUtf8() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toUtf8')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// toUtf8_helper(const QString & arg__1)
      QByteArray toUtf8_helper(String? arg__1) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toUtf8_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// trimmed()
  QString trimmed() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__trimmed')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// trimmed_helper(QString & str)
      QString trimmed_helper(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__trimmed_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// trimmed_helper(const QString & str)
      QString trimmed_helper_2(String? str) {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__trimmed_helper_QString')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// truncate(int pos)
  truncate(int pos) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__truncate_int')
        .asFunction();
//tag=1030
    func(thisCpp, pos);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QString__destructor')
        .asFunction();
    func(thisCpp);
  }

  String toDartString() {
    return toUtf8().constData();
  }
}
