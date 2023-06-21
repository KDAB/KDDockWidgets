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
        'c_QString_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class QString implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, QString>();
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

  factory QString.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QString.fromCppPointer(cppPointer, needsAutoDelete)) as QString;
  }
  QString.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  QString.init() {} //QString()
  QString() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_QString__constructor')
        .asFunction();
    thisCpp = func();
    QString.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // append(const QString & s)
  QString append(String? s) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QString__append_QString')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  } // arg(const QString & a, int fieldWidth) const

  QString arg(String? a, {int fieldWidth = 0}) {
    final voidstar_Func_voidstar_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QString__arg_QString_int')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, a?.toNativeUtf8() ?? ffi.nullptr, fieldWidth);
    return QString.fromCppPointer(result, true);
  } // arg(int a, int fieldWidth, int base) const

  QString arg_2(int a, {int fieldWidth = 0, int base = 10}) {
    final voidstar_Func_voidstar_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__arg_int_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, a, fieldWidth, base);
    return QString.fromCppPointer(result, true);
  }

  static // asprintf(const char * format)
      QString asprintf(String? format) {
    final voidstar_Func_string func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_FFI>>(
            'c_static_QString__asprintf_char')
        .asFunction();
    ffi.Pointer<void> result = func(format?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  } // capacity() const

  int capacity() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_QString__capacity')
        .asFunction();
    return func(thisCpp);
  } // chop(qsizetype n)

  chop(int n) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__chop_qsizetype')
        .asFunction();
    func(thisCpp, n);
  } // chopped(qsizetype n) const

  QString chopped(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__chopped_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  } // clear()

  clear() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>('c_QString__clear')
        .asFunction();
    func(thisCpp);
  } // compare(const QString & s) const

  int compare(String? s) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__compare_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }

  static // compare(const QString & s1, const QString & s2)
      int compare_2(String? s1, String? s2) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_static_QString__compare_QString_QString')
        .asFunction();
    return func(
        s1?.toNativeUtf8() ?? ffi.nullptr, s2?.toNativeUtf8() ?? ffi.nullptr);
  } // contains(const QString & s) const

  bool contains(String? s) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__contains_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // count(const QString & s) const

  int count(String? s) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__count_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  } // detach()

  detach() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>('c_QString__detach')
        .asFunction();
    func(thisCpp);
  } // endsWith(const QString & s) const

  bool endsWith(String? s) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__endsWith_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // first(qsizetype n) const

  QString first(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__first_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  }

  static // fromLatin1(const char * str, qsizetype size)
      QString fromLatin1(String? str, int size) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromLatin1_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }

  static // fromLocal8Bit(const char * str, qsizetype size)
      QString fromLocal8Bit(String? str, int size) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromLocal8Bit_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  }

  static // fromUtf8(const char * utf8, qsizetype size)
      QString fromUtf8(String? utf8, int size) {
    final voidstar_Func_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_ffi_Int32_FFI>>(
            'c_static_QString__fromUtf8_char_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(utf8?.toNativeUtf8() ?? ffi.nullptr, size);
    return QString.fromCppPointer(result, true);
  } // indexOf(const QString & s, qsizetype from) const

  int indexOf(String? s, {int from = 0}) {
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QString__indexOf_QString_qsizetype')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, from);
  } // insert(qsizetype i, const QString & s)

  QString insert(int i, String? s) {
    final voidstar_Func_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_QString__insert_qsizetype_QString')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  } // isDetached() const

  bool isDetached() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isDetached')
        .asFunction();
    return func(thisCpp) != 0;
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isEmpty')
        .asFunction();
    return func(thisCpp) != 0;
  } // isLower() const

  bool isLower() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isLower')
        .asFunction();
    return func(thisCpp) != 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>('c_QString__isNull')
        .asFunction();
    return func(thisCpp) != 0;
  } // isRightToLeft() const

  bool isRightToLeft() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isRightToLeft')
        .asFunction();
    return func(thisCpp) != 0;
  } // isSharedWith(const QString & other) const

  bool isSharedWith(String? other) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__isSharedWith_QString')
        .asFunction();
    return func(thisCpp, other?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // isSimpleText() const

  bool isSimpleText() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isSimpleText')
        .asFunction();
    return func(thisCpp) != 0;
  } // isUpper() const

  bool isUpper() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isUpper')
        .asFunction();
    return func(thisCpp) != 0;
  } // isValidUtf16() const

  bool isValidUtf16() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_QString__isValidUtf16')
        .asFunction();
    return func(thisCpp) != 0;
  } // last(qsizetype n) const

  QString last(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__last_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  } // lastIndexOf(const QString & s) const

  int lastIndexOf(String? s) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__lastIndexOf_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  } // lastIndexOf(const QString & s, qsizetype from) const

  int lastIndexOf_2(String? s, int from) {
    final int_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_QString__lastIndexOf_QString_qsizetype')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr, from);
  } // left(qsizetype n) const

  QString left(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__left_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  } // leftJustified(qsizetype width) const

  QString leftJustified(int width) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__leftJustified_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, width);
    return QString.fromCppPointer(result, true);
  } // length() const

  int length() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QString__length')
        .asFunction();
    return func(thisCpp);
  } // localeAwareCompare(const QString & s) const

  int localeAwareCompare(String? s) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_QString__localeAwareCompare_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  }

  static // localeAwareCompare(const QString & s1, const QString & s2)
      int localeAwareCompare_2(String? s1, String? s2) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_static_QString__localeAwareCompare_QString_QString')
        .asFunction();
    return func(
        s1?.toNativeUtf8() ?? ffi.nullptr, s2?.toNativeUtf8() ?? ffi.nullptr);
  } // mid(qsizetype position, qsizetype n) const

  QString mid(int position, {int n = -1}) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__mid_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, position, n);
    return QString.fromCppPointer(result, true);
  }

  static // number(int arg__1, int base)
      QString number(int arg__1, {int base = 10}) {
    final voidstar_Func_int_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_ffi_Int32_FFI>>(
            'c_static_QString__number_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(arg__1, base);
    return QString.fromCppPointer(result, true);
  } // prepend(const QString & s)

  QString prepend(String? s) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QString__prepend_QString')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  } // push_back(const QString & s)

  push_back(String? s) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QString__push_back_QString')
        .asFunction();
    func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  } // push_front(const QString & s)

  push_front(String? s) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_QString__push_front_QString')
        .asFunction();
    func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
  } // reallocGrowData(qsizetype n)

  reallocGrowData(int n) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__reallocGrowData_qsizetype')
        .asFunction();
    func(thisCpp, n);
  } // remove(const QString & s)

  QString remove(String? s) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_QString__remove_QString')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  } // remove(qsizetype i, qsizetype len)

  QString remove_2(int i, int len) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__remove_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, i, len);
    return QString.fromCppPointer(result, false);
  } // removeAt(qsizetype pos)

  QString removeAt(int pos) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__removeAt_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, pos);
    return QString.fromCppPointer(result, false);
  } // removeFirst()

  QString removeFirst() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__removeFirst')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, false);
  } // removeLast()

  QString removeLast() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__removeLast')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, false);
  } // repeated(qsizetype times) const

  QString repeated(int times) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__repeated_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, times);
    return QString.fromCppPointer(result, true);
  } // replace(const QString & before, const QString & after)

  QString replace(String? before, String? after) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_QString__replace_QString_QString')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        before?.toNativeUtf8() ?? ffi.nullptr,
        after?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  } // replace(qsizetype i, qsizetype len, const QString & after)

  QString replace_2(int i, int len, String? after) {
    final voidstar_Func_voidstar_int_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_FFI>>(
            'c_QString__replace_qsizetype_qsizetype_QString')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, i, len, after?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, false);
  } // reserve(qsizetype size)

  reserve(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__reserve_qsizetype')
        .asFunction();
    func(thisCpp, size);
  } // resize(qsizetype size)

  resize(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__resize_qsizetype')
        .asFunction();
    func(thisCpp, size);
  } // right(qsizetype n) const

  QString right(int n) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__right_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, n);
    return QString.fromCppPointer(result, true);
  } // rightJustified(qsizetype width) const

  QString rightJustified(int width) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__rightJustified_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, width);
    return QString.fromCppPointer(result, true);
  } // section(const QString & in_sep, qsizetype start, qsizetype end) const

  QString section(String? in_sep, int start, {int end = -1}) {
    final voidstar_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__section_QString_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, in_sep?.toNativeUtf8() ?? ffi.nullptr, start, end);
    return QString.fromCppPointer(result, true);
  } // setNum(int arg__1, int base)

  QString setNum(int arg__1, {int base = 10}) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__setNum_int_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1, base);
    return QString.fromCppPointer(result, false);
  } // shrink_to_fit()

  shrink_to_fit() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QString__shrink_to_fit')
        .asFunction();
    func(thisCpp);
  } // simplified()

  QString simplified() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__simplified')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static // simplified_helper(QString & str)
      QString simplified_helper(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__simplified_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

  static // simplified_helper(const QString & str)
      QString simplified_helper_2(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__simplified_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  } // size() const

  int size() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>('c_QString__size')
        .asFunction();
    return func(thisCpp);
  } // sliced(qsizetype pos) const

  QString sliced(int pos) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__sliced_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, pos);
    return QString.fromCppPointer(result, true);
  } // sliced(qsizetype pos, qsizetype n) const

  QString sliced_2(int pos, int n) {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_QString__sliced_qsizetype_qsizetype')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, pos, n);
    return QString.fromCppPointer(result, true);
  } // squeeze()

  squeeze() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_QString__squeeze')
        .asFunction();
    func(thisCpp);
  } // startsWith(const QString & s) const

  bool startsWith(String? s) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_QString__startsWith_QString')
        .asFunction();
    return func(thisCpp, s?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // toCaseFolded()

  QString toCaseFolded() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toCaseFolded')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static // toCaseFolded_helper(QString & str)
      QString toCaseFolded_helper(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toCaseFolded_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

  static // toCaseFolded_helper(const QString & str)
      QString toCaseFolded_helper_2(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toCaseFolded_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  } // toHtmlEscaped() const

  QString toHtmlEscaped() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toHtmlEscaped')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // toLatin1()

  QByteArray toLatin1() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toLatin1')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toLatin1_helper(const QString & arg__1)
      QByteArray toLatin1_helper(String? arg__1) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLatin1_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toLatin1_helper_inplace(QString & arg__1)
      QByteArray toLatin1_helper_inplace(String? arg__1) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLatin1_helper_inplace_QString')
        .asFunction();
    ffi.Pointer<void> result = func(arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, true);
  } // toLocal8Bit()

  QByteArray toLocal8Bit() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toLocal8Bit')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  } // toLower()

  QString toLower() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toLower')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static // toLower_helper(QString & str)
      QString toLower_helper(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLower_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

  static // toLower_helper(const QString & str)
      QString toLower_helper_2(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toLower_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  } // toUpper()

  QString toUpper() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toUpper')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static // toUpper_helper(QString & str)
      QString toUpper_helper(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toUpper_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

  static // toUpper_helper(const QString & str)
      QString toUpper_helper_2(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toUpper_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  } // toUtf8()

  QByteArray toUtf8() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__toUtf8')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  static // toUtf8_helper(const QString & arg__1)
      QByteArray toUtf8_helper(String? arg__1) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__toUtf8_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return QByteArray.fromCppPointer(result, true);
  } // trimmed()

  QString trimmed() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_QString__trimmed')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static // trimmed_helper(QString & str)
      QString trimmed_helper(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__trimmed_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  }

  static // trimmed_helper(const QString & str)
      QString trimmed_helper_2(String? str) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_QString__trimmed_helper_QString')
        .asFunction();
    ffi.Pointer<void> result = func(str?.toNativeUtf8() ?? ffi.nullptr);
    return QString.fromCppPointer(result, true);
  } // truncate(qsizetype pos)

  truncate(int pos) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_QString__truncate_qsizetype')
        .asFunction();
    func(thisCpp, pos);
  }

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
