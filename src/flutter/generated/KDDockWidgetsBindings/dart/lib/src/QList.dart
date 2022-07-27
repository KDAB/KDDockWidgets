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
final _finalizer_T_QObject_T_ =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_QList_T_QObject_T__Finalizer');
final _finalizer_T_QByteArray_T_ =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_QList_T_QByteArray_T__Finalizer');

class QList<T> {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, QList>();
  var _thisCpp = null;
  bool _needsAutoDelete = true;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete)
      newWeakPersistentHandle?.call(this, ptrvoid, 0, getFinalizer());
  }

  static bool isCached(var cppPointer) {
//tag=1024
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

//tag=1061
  factory QList.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QList.fromCppPointer(cppPointer, needsAutoDelete)) as QList<T>;
  }
  QList.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  QList.init() {}
//tag=1063
  String getCFunctionName(int id) {
    if (this is QList<QObject>) {
      switch (id) {
        case 324:
          return "c_QList_T_QObject_T___constructor";
          break;
        case 327:
          return "c_QList_T_QObject_T___append_QList_T";
          break;
        case 328:
          return "c_QList_T_QObject_T___append_QObject";
          break;
        case 329:
          return "c_QList_T_QObject_T___at_int";
          break;
        case 330:
          return "c_QList_T_QObject_T___back";
          break;
        case 331:
          return "c_QList_T_QObject_T___back";
          break;
        case 332:
          return "c_QList_T_QObject_T___clear";
          break;
        case 333:
          return "c_QList_T_QObject_T___constFirst";
          break;
        case 334:
          return "c_QList_T_QObject_T___constLast";
          break;
        case 335:
          return "c_QList_T_QObject_T___contains_QObject";
          break;
        case 336:
          return "c_QList_T_QObject_T___count";
          break;
        case 337:
          return "c_QList_T_QObject_T___count_QObject";
          break;
        case 338:
          return "c_QList_T_QObject_T___detach";
          break;
        case 339:
          return "c_QList_T_QObject_T___detachShared";
          break;
        case 342:
          return "c_QList_T_QObject_T___empty";
          break;
        case 343:
          return "c_QList_T_QObject_T___endsWith_QObject";
          break;
        case 344:
          return "c_QList_T_QObject_T___first";
          break;
        case 345:
          return "c_QList_T_QObject_T___first";
          break;
        case 346:
          return "c_QList_T_QObject_T___front";
          break;
        case 347:
          return "c_QList_T_QObject_T___front";
          break;
        case 348:
          return "c_QList_T_QObject_T___indexOf_QObject_int";
          break;
        case 349:
          return "c_QList_T_QObject_T___insert_int_QObject";
          break;
        case 350:
          return "c_QList_T_QObject_T___isDetached";
          break;
        case 351:
          return "c_QList_T_QObject_T___isEmpty";
          break;
        case 352:
          return "c_QList_T_QObject_T___isSharedWith_QList_T";
          break;
        case 353:
          return "c_QList_T_QObject_T___last";
          break;
        case 354:
          return "c_QList_T_QObject_T___last";
          break;
        case 355:
          return "c_QList_T_QObject_T___lastIndexOf_QObject_int";
          break;
        case 356:
          return "c_QList_T_QObject_T___length";
          break;
        case 357:
          return "c_QList_T_QObject_T___mid_int_int";
          break;
        case 358:
          return "c_QList_T_QObject_T___move_int_int";
          break;
        case 370:
          return "c_QList_T_QObject_T___pop_back";
          break;
        case 371:
          return "c_QList_T_QObject_T___pop_front";
          break;
        case 372:
          return "c_QList_T_QObject_T___prepend_QObject";
          break;
        case 373:
          return "c_QList_T_QObject_T___push_back_QObject";
          break;
        case 374:
          return "c_QList_T_QObject_T___push_front_QObject";
          break;
        case 375:
          return "c_QList_T_QObject_T___removeAll_QObject";
          break;
        case 376:
          return "c_QList_T_QObject_T___removeAt_int";
          break;
        case 377:
          return "c_QList_T_QObject_T___removeFirst";
          break;
        case 378:
          return "c_QList_T_QObject_T___removeLast";
          break;
        case 379:
          return "c_QList_T_QObject_T___removeOne_QObject";
          break;
        case 380:
          return "c_QList_T_QObject_T___replace_int_QObject";
          break;
        case 381:
          return "c_QList_T_QObject_T___reserve_int";
          break;
        case 382:
          return "c_QList_T_QObject_T___setSharable_bool";
          break;
        case 383:
          return "c_QList_T_QObject_T___size";
          break;
        case 384:
          return "c_QList_T_QObject_T___startsWith_QObject";
          break;
        case 386:
          return "c_QList_T_QObject_T___swapItemsAt_int_int";
          break;
        case 387:
          return "c_QList_T_QObject_T___takeAt_int";
          break;
        case 388:
          return "c_QList_T_QObject_T___takeFirst";
          break;
        case 389:
          return "c_QList_T_QObject_T___takeLast";
          break;
        case 390:
          return "c_QList_T_QObject_T___value_int";
          break;
        case 391:
          return "c_QList_T_QObject_T___value_int_QObject";
          break;
      }
    }
    if (this is QList<QByteArray>) {
      switch (id) {
        case 324:
          return "c_QList_T_QByteArray_T___constructor";
          break;
        case 327:
          return "c_QList_T_QByteArray_T___append_QList_T";
          break;
        case 328:
          return "c_QList_T_QByteArray_T___append_QByteArray";
          break;
        case 329:
          return "c_QList_T_QByteArray_T___at_int";
          break;
        case 330:
          return "c_QList_T_QByteArray_T___back";
          break;
        case 331:
          return "c_QList_T_QByteArray_T___back";
          break;
        case 332:
          return "c_QList_T_QByteArray_T___clear";
          break;
        case 333:
          return "c_QList_T_QByteArray_T___constFirst";
          break;
        case 334:
          return "c_QList_T_QByteArray_T___constLast";
          break;
        case 335:
          return "c_QList_T_QByteArray_T___contains_QByteArray";
          break;
        case 336:
          return "c_QList_T_QByteArray_T___count";
          break;
        case 337:
          return "c_QList_T_QByteArray_T___count_QByteArray";
          break;
        case 338:
          return "c_QList_T_QByteArray_T___detach";
          break;
        case 339:
          return "c_QList_T_QByteArray_T___detachShared";
          break;
        case 342:
          return "c_QList_T_QByteArray_T___empty";
          break;
        case 343:
          return "c_QList_T_QByteArray_T___endsWith_QByteArray";
          break;
        case 344:
          return "c_QList_T_QByteArray_T___first";
          break;
        case 345:
          return "c_QList_T_QByteArray_T___first";
          break;
        case 346:
          return "c_QList_T_QByteArray_T___front";
          break;
        case 347:
          return "c_QList_T_QByteArray_T___front";
          break;
        case 348:
          return "c_QList_T_QByteArray_T___indexOf_QByteArray_int";
          break;
        case 349:
          return "c_QList_T_QByteArray_T___insert_int_QByteArray";
          break;
        case 350:
          return "c_QList_T_QByteArray_T___isDetached";
          break;
        case 351:
          return "c_QList_T_QByteArray_T___isEmpty";
          break;
        case 352:
          return "c_QList_T_QByteArray_T___isSharedWith_QList_T";
          break;
        case 353:
          return "c_QList_T_QByteArray_T___last";
          break;
        case 354:
          return "c_QList_T_QByteArray_T___last";
          break;
        case 355:
          return "c_QList_T_QByteArray_T___lastIndexOf_QByteArray_int";
          break;
        case 356:
          return "c_QList_T_QByteArray_T___length";
          break;
        case 357:
          return "c_QList_T_QByteArray_T___mid_int_int";
          break;
        case 358:
          return "c_QList_T_QByteArray_T___move_int_int";
          break;
        case 370:
          return "c_QList_T_QByteArray_T___pop_back";
          break;
        case 371:
          return "c_QList_T_QByteArray_T___pop_front";
          break;
        case 372:
          return "c_QList_T_QByteArray_T___prepend_QByteArray";
          break;
        case 373:
          return "c_QList_T_QByteArray_T___push_back_QByteArray";
          break;
        case 374:
          return "c_QList_T_QByteArray_T___push_front_QByteArray";
          break;
        case 375:
          return "c_QList_T_QByteArray_T___removeAll_QByteArray";
          break;
        case 376:
          return "c_QList_T_QByteArray_T___removeAt_int";
          break;
        case 377:
          return "c_QList_T_QByteArray_T___removeFirst";
          break;
        case 378:
          return "c_QList_T_QByteArray_T___removeLast";
          break;
        case 379:
          return "c_QList_T_QByteArray_T___removeOne_QByteArray";
          break;
        case 380:
          return "c_QList_T_QByteArray_T___replace_int_QByteArray";
          break;
        case 381:
          return "c_QList_T_QByteArray_T___reserve_int";
          break;
        case 382:
          return "c_QList_T_QByteArray_T___setSharable_bool";
          break;
        case 383:
          return "c_QList_T_QByteArray_T___size";
          break;
        case 384:
          return "c_QList_T_QByteArray_T___startsWith_QByteArray";
          break;
        case 386:
          return "c_QList_T_QByteArray_T___swapItemsAt_int_int";
          break;
        case 387:
          return "c_QList_T_QByteArray_T___takeAt_int";
          break;
        case 388:
          return "c_QList_T_QByteArray_T___takeFirst";
          break;
        case 389:
          return "c_QList_T_QByteArray_T___takeLast";
          break;
        case 390:
          return "c_QList_T_QByteArray_T___value_int";
          break;
        case 391:
          return "c_QList_T_QByteArray_T___value_int_QByteArray";
          break;
      }
    }
    return "";
  }

//tag=1065
  dynamic getFinalizer() {
    if (this is QList<QObject>) {
      return _finalizer_T_QObject_T_;
    }
    if (this is QList<QByteArray>) {
      return _finalizer_T_QByteArray_T_;
    }
    print("ERROR: Couldn't find finalizer for" + this.runtimeType.toString());
  }

//tag=1023
//QList<T>()
  QList() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            '${getCFunctionName(324)}')
        .asFunction();
    thisCpp = func();
    QList.s_dartInstanceByCppPtr[thisCpp.address] = this;
  }
//tag=1024

//tag=1027
// append(const QList<T > & t)
  append(QList? t) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            '${getCFunctionName(327)}')
        .asFunction();
//tag=1030
    func(thisCpp, t == null ? ffi.nullptr : t.thisCpp);
  }
//tag=1024

//tag=1027
// append(const T & t)
  append_2(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(328)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(328)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
  }
//tag=1024

//tag=1027
// at(int i) const
  T at(int i) {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(329)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(329)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// back()
  T back() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(330)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(330)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// clear()
  clear() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(332)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// constFirst() const
  T constFirst() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(333)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(333)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// constLast() const
  T constLast() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(334)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(334)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// contains(const T & t) const
  bool contains(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(335)}')
          .asFunction();
//tag=1029
      return func(
              thisCpp,
              (t as QByteArray) == null
                  ? ffi.nullptr
                  : (t as QByteArray).thisCpp) !=
          0;
    }
//tag=1028
    if (this is QList<QObject>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(335)}')
          .asFunction();
//tag=1029
      return func(thisCpp,
              (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp) !=
          0;
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// count() const
  int count() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(336)}')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// count(const T & t) const
  int count_2(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final int_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(337)}')
          .asFunction();
//tag=1031
      return func(thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final int_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(337)}')
          .asFunction();
//tag=1031
      return func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// detach()
  detach() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(338)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// detachShared()
  detachShared() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(339)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// detach_helper()
  detach_helper() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(340)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// detach_helper(int alloc)
  detach_helper_2(int alloc) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(341)}')
        .asFunction();
//tag=1030
    func(thisCpp, alloc);
  }
//tag=1024

//tag=1027
// empty() const
  bool empty() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            '${getCFunctionName(342)}')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// endsWith(const T & t) const
  bool endsWith(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(343)}')
          .asFunction();
//tag=1029
      return func(
              thisCpp,
              (t as QByteArray) == null
                  ? ffi.nullptr
                  : (t as QByteArray).thisCpp) !=
          0;
    }
//tag=1028
    if (this is QList<QObject>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(343)}')
          .asFunction();
//tag=1029
      return func(thisCpp,
              (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp) !=
          0;
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// first()
  T first() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(344)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(344)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// front()
  T front() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(346)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(346)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// indexOf(const T & t, int from) const
  int indexOf(T t, {int from = 0}) {
//tag=1028
    if (this is QList<QByteArray>) {
      final int_Func_voidstar_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(348)}')
          .asFunction();
//tag=1031
      return func(
          thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp,
          from);
    }
//tag=1028
    if (this is QList<QObject>) {
      final int_Func_voidstar_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(348)}')
          .asFunction();
//tag=1031
      return func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp, from);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// insert(int i, const T & t)
  insert(int i, T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final void_Func_voidstar_int_voidstar func = _dylib
          .lookup<
                  ffi.NativeFunction<
                      void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
              '${getCFunctionName(349)}')
          .asFunction();
//tag=1030
      func(thisCpp, i,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final void_Func_voidstar_int_voidstar func = _dylib
          .lookup<
                  ffi.NativeFunction<
                      void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
              '${getCFunctionName(349)}')
          .asFunction();
//tag=1030
      func(thisCpp, i,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
  }
//tag=1024

//tag=1027
// isDetached() const
  bool isDetached() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            '${getCFunctionName(350)}')
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
            '${getCFunctionName(351)}')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isSharedWith(const QList<T > & other) const
  bool isSharedWith(QList? other) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            '${getCFunctionName(352)}')
        .asFunction();
//tag=1029
    return func(thisCpp, other == null ? ffi.nullptr : other.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// last()
  T last() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(353)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(353)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// lastIndexOf(const T & t, int from) const
  int lastIndexOf(T t, {int from = -1}) {
//tag=1028
    if (this is QList<QByteArray>) {
      final int_Func_voidstar_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(355)}')
          .asFunction();
//tag=1031
      return func(
          thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp,
          from);
    }
//tag=1028
    if (this is QList<QObject>) {
      final int_Func_voidstar_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(355)}')
          .asFunction();
//tag=1031
      return func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp, from);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// length() const
  int length() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(356)}')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// move(int from, int to)
  move(int from, int to) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            '${getCFunctionName(358)}')
        .asFunction();
//tag=1030
    func(thisCpp, from, to);
  }
//tag=1024

//tag=1027
// pop_back()
  pop_back() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(370)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// pop_front()
  pop_front() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(371)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// prepend(const T & t)
  prepend(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(372)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(372)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
  }
//tag=1024

//tag=1027
// push_back(const T & t)
  push_back(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
  }
//tag=1024

//tag=1027
// push_front(const T & t)
  push_front(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(374)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final void_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(374)}')
          .asFunction();
//tag=1030
      func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
  }
//tag=1024

//tag=1027
// removeAll(const T & t)
  int removeAll(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final int_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(375)}')
          .asFunction();
//tag=1031
      return func(thisCpp,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final int_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(375)}')
          .asFunction();
//tag=1031
      return func(thisCpp,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// removeAt(int i)
  removeAt(int i) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(376)}')
        .asFunction();
//tag=1030
    func(thisCpp, i);
  }
//tag=1024

//tag=1027
// removeFirst()
  removeFirst() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(377)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// removeLast()
  removeLast() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(378)}')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// removeOne(const T & t)
  bool removeOne(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(379)}')
          .asFunction();
//tag=1029
      return func(
              thisCpp,
              (t as QByteArray) == null
                  ? ffi.nullptr
                  : (t as QByteArray).thisCpp) !=
          0;
    }
//tag=1028
    if (this is QList<QObject>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(379)}')
          .asFunction();
//tag=1029
      return func(thisCpp,
              (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp) !=
          0;
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// replace(int i, const T & t)
  replace(int i, T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final void_Func_voidstar_int_voidstar func = _dylib
          .lookup<
                  ffi.NativeFunction<
                      void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
              '${getCFunctionName(380)}')
          .asFunction();
//tag=1030
      func(thisCpp, i,
          (t as QByteArray) == null ? ffi.nullptr : (t as QByteArray).thisCpp);
    }
//tag=1028
    if (this is QList<QObject>) {
      final void_Func_voidstar_int_voidstar func = _dylib
          .lookup<
                  ffi.NativeFunction<
                      void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
              '${getCFunctionName(380)}')
          .asFunction();
//tag=1030
      func(thisCpp, i,
          (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp);
    }
  }
//tag=1024

//tag=1027
// reserve(int size)
  reserve(int size) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(381)}')
        .asFunction();
//tag=1030
    func(thisCpp, size);
  }
//tag=1024

//tag=1027
// setSharable(bool sharable)
  setSharable(bool sharable) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            '${getCFunctionName(382)}')
        .asFunction();
//tag=1030
    func(thisCpp, sharable ? 1 : 0);
  }
//tag=1024

//tag=1027
// size() const
  int size() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(383)}')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// startsWith(const T & t) const
  bool startsWith(T t) {
//tag=1028
    if (this is QList<QByteArray>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(384)}')
          .asFunction();
//tag=1029
      return func(
              thisCpp,
              (t as QByteArray) == null
                  ? ffi.nullptr
                  : (t as QByteArray).thisCpp) !=
          0;
    }
//tag=1028
    if (this is QList<QObject>) {
      final bool_Func_voidstar_voidstar func = _dylib
          .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
              '${getCFunctionName(384)}')
          .asFunction();
//tag=1029
      return func(thisCpp,
              (t as QObject) == null ? ffi.nullptr : (t as QObject).thisCpp) !=
          0;
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// swapItemsAt(int i, int j)
  swapItemsAt(int i, int j) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            '${getCFunctionName(386)}')
        .asFunction();
//tag=1030
    func(thisCpp, i, j);
  }
//tag=1024

//tag=1027
// takeAt(int i)
  T takeAt(int i) {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(387)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(387)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// takeFirst()
  T takeFirst() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(388)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(388)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// takeLast()
  T takeLast() {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(389)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(389)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// value(int i) const
  T value(int i) {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(390)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(390)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }
//tag=1024

//tag=1027
// value(int i, const T & defaultValue) const
  T value_2(int i, T defaultValue) {
//tag=1028
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int_voidstar func = _dylib
          .lookup<
                  ffi.NativeFunction<
                      voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
              '${getCFunctionName(391)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(
          thisCpp,
          i,
          (defaultValue as QByteArray) == null
              ? ffi.nullptr
              : (defaultValue as QByteArray).thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
//tag=1028
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int_voidstar func = _dylib
          .lookup<
                  ffi.NativeFunction<
                      voidstar_Func_voidstar_ffi_Int32_voidstar_FFI>>(
              '${getCFunctionName(391)}')
          .asFunction();
//tag=1033
      ffi.Pointer<void> result = func(
          thisCpp,
          i,
          (defaultValue as QObject) == null
              ? ffi.nullptr
              : (defaultValue as QObject).thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(-2)}')
        .asFunction();
    func(thisCpp);
  }
}
