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
final _finalizer_T_QString_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_QString_T__Finalizer');
final _finalizer_T_QString_T_ =
    ffi.NativeFinalizer(_finalizer_T_QString_T_Func.cast());
final _finalizer_T_unsigned_int_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_unsigned_int_T__Finalizer');
final _finalizer_T_unsigned_int_T_ =
    ffi.NativeFinalizer(_finalizer_T_unsigned_int_T_Func.cast());
final _finalizer_T_QObject_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_QObject_T__Finalizer');
final _finalizer_T_QObject_T_ =
    ffi.NativeFinalizer(_finalizer_T_QObject_T_Func.cast());
final _finalizer_T_QByteArray_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_QByteArray_T__Finalizer');
final _finalizer_T_QByteArray_T_ =
    ffi.NativeFinalizer(_finalizer_T_QByteArray_T_Func.cast());
final _finalizer_T_DockWidget_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_DockWidget_T__Finalizer');
final _finalizer_T_DockWidget_T_ =
    ffi.NativeFinalizer(_finalizer_T_DockWidget_T_Func.cast());
final _finalizer_T_FloatingWindow_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_FloatingWindow_T__Finalizer');
final _finalizer_T_FloatingWindow_T_ =
    ffi.NativeFinalizer(_finalizer_T_FloatingWindow_T_Func.cast());
final _finalizer_T_Group_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_Group_T__Finalizer');
final _finalizer_T_Group_T_ =
    ffi.NativeFinalizer(_finalizer_T_Group_T_Func.cast());
final _finalizer_T_Layout_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_Layout_T__Finalizer');
final _finalizer_T_Layout_T_ =
    ffi.NativeFinalizer(_finalizer_T_Layout_T_Func.cast());
final _finalizer_T_MainWindow_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_MainWindow_T__Finalizer');
final _finalizer_T_MainWindow_T_ =
    ffi.NativeFinalizer(_finalizer_T_MainWindow_T_Func.cast());
final _finalizer_T_int_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_int_T__Finalizer');
final _finalizer_T_int_T_ = ffi.NativeFinalizer(_finalizer_T_int_T_Func.cast());
final _finalizer_T_Item_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_Item_T__Finalizer');
final _finalizer_T_Item_T_ =
    ffi.NativeFinalizer(_finalizer_T_Item_T_Func.cast());
final _finalizer_T_Separator_T_Func =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_QList_T_Separator_T__Finalizer');
final _finalizer_T_Separator_T_ =
    ffi.NativeFinalizer(_finalizer_T_Separator_T_Func.cast());

class QList<T> implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, QList>();
  var _thisCpp = null;
  bool _needsAutoDelete = true;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete) getFinalizer().attach(this, ptrvoid);
  }

  static bool isCached(var cppPointer) {
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory QList.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        QList.fromCppPointer(cppPointer, needsAutoDelete)) as QList<T>;
  }
  QList.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  QList.init() {}
  String getCFunctionName(int id) {
    if (this is QList<QString>) {
      switch (id) {
        case 314:
          return "c_QList_T_QString_T___constructor";
          break;
        case 315:
          return "c_QList_T_QString_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_QString_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_QString_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_QString_T___back";
          break;
        case 320:
          return "c_QList_T_QString_T___back";
          break;
        case 321:
          return "c_QList_T_QString_T___capacity";
          break;
        case 322:
          return "c_QList_T_QString_T___clear";
          break;
        case 324:
          return "c_QList_T_QString_T___constFirst";
          break;
        case 325:
          return "c_QList_T_QString_T___constLast";
          break;
        case 326:
          return "c_QList_T_QString_T___count";
          break;
        case 329:
          return "c_QList_T_QString_T___detach";
          break;
        case 330:
          return "c_QList_T_QString_T___empty";
          break;
        case 331:
          return "c_QList_T_QString_T___first";
          break;
        case 332:
          return "c_QList_T_QString_T___first";
          break;
        case 333:
          return "c_QList_T_QString_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_QString_T___front";
          break;
        case 337:
          return "c_QList_T_QString_T___front";
          break;
        case 338:
          return "c_QList_T_QString_T___isDetached";
          break;
        case 339:
          return "c_QList_T_QString_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_QString_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_QString_T___last";
          break;
        case 342:
          return "c_QList_T_QString_T___last";
          break;
        case 343:
          return "c_QList_T_QString_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_QString_T___length";
          break;
        case 345:
          return "c_QList_T_QString_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_QString_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_QString_T___pop_back";
          break;
        case 358:
          return "c_QList_T_QString_T___pop_front";
          break;
        case 359:
          return "c_QList_T_QString_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_QString_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_QString_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_QString_T___removeLast";
          break;
        case 363:
          return "c_QList_T_QString_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_QString_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_QString_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_QString_T___size";
          break;
        case 368:
          return "c_QList_T_QString_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_QString_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_QString_T___squeeze";
          break;
        case 372:
          return "c_QList_T_QString_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_QString_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_QString_T___toList";
          break;
        case 375:
          return "c_QList_T_QString_T___toVector";
          break;
        case 376:
          return "c_QList_T_QString_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<int>) {
      switch (id) {
        case 314:
          return "c_QList_T_unsigned_int_T___constructor";
          break;
        case 315:
          return "c_QList_T_unsigned_int_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_unsigned_int_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_unsigned_int_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_unsigned_int_T___back";
          break;
        case 320:
          return "c_QList_T_unsigned_int_T___back";
          break;
        case 321:
          return "c_QList_T_unsigned_int_T___capacity";
          break;
        case 322:
          return "c_QList_T_unsigned_int_T___clear";
          break;
        case 324:
          return "c_QList_T_unsigned_int_T___constFirst";
          break;
        case 325:
          return "c_QList_T_unsigned_int_T___constLast";
          break;
        case 326:
          return "c_QList_T_unsigned_int_T___count";
          break;
        case 329:
          return "c_QList_T_unsigned_int_T___detach";
          break;
        case 330:
          return "c_QList_T_unsigned_int_T___empty";
          break;
        case 331:
          return "c_QList_T_unsigned_int_T___first";
          break;
        case 332:
          return "c_QList_T_unsigned_int_T___first";
          break;
        case 333:
          return "c_QList_T_unsigned_int_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_unsigned_int_T___front";
          break;
        case 337:
          return "c_QList_T_unsigned_int_T___front";
          break;
        case 338:
          return "c_QList_T_unsigned_int_T___isDetached";
          break;
        case 339:
          return "c_QList_T_unsigned_int_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_unsigned_int_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_unsigned_int_T___last";
          break;
        case 342:
          return "c_QList_T_unsigned_int_T___last";
          break;
        case 343:
          return "c_QList_T_unsigned_int_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_unsigned_int_T___length";
          break;
        case 345:
          return "c_QList_T_unsigned_int_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_unsigned_int_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_unsigned_int_T___pop_back";
          break;
        case 358:
          return "c_QList_T_unsigned_int_T___pop_front";
          break;
        case 359:
          return "c_QList_T_unsigned_int_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_unsigned_int_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_unsigned_int_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_unsigned_int_T___removeLast";
          break;
        case 363:
          return "c_QList_T_unsigned_int_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_unsigned_int_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_unsigned_int_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_unsigned_int_T___size";
          break;
        case 368:
          return "c_QList_T_unsigned_int_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_unsigned_int_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_unsigned_int_T___squeeze";
          break;
        case 372:
          return "c_QList_T_unsigned_int_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_unsigned_int_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_unsigned_int_T___toList";
          break;
        case 375:
          return "c_QList_T_unsigned_int_T___toVector";
          break;
        case 376:
          return "c_QList_T_unsigned_int_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<QObject>) {
      switch (id) {
        case 314:
          return "c_QList_T_QObject_T___constructor";
          break;
        case 315:
          return "c_QList_T_QObject_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_QObject_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_QObject_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_QObject_T___back";
          break;
        case 320:
          return "c_QList_T_QObject_T___back";
          break;
        case 321:
          return "c_QList_T_QObject_T___capacity";
          break;
        case 322:
          return "c_QList_T_QObject_T___clear";
          break;
        case 324:
          return "c_QList_T_QObject_T___constFirst";
          break;
        case 325:
          return "c_QList_T_QObject_T___constLast";
          break;
        case 326:
          return "c_QList_T_QObject_T___count";
          break;
        case 329:
          return "c_QList_T_QObject_T___detach";
          break;
        case 330:
          return "c_QList_T_QObject_T___empty";
          break;
        case 331:
          return "c_QList_T_QObject_T___first";
          break;
        case 332:
          return "c_QList_T_QObject_T___first";
          break;
        case 333:
          return "c_QList_T_QObject_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_QObject_T___front";
          break;
        case 337:
          return "c_QList_T_QObject_T___front";
          break;
        case 338:
          return "c_QList_T_QObject_T___isDetached";
          break;
        case 339:
          return "c_QList_T_QObject_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_QObject_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_QObject_T___last";
          break;
        case 342:
          return "c_QList_T_QObject_T___last";
          break;
        case 343:
          return "c_QList_T_QObject_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_QObject_T___length";
          break;
        case 345:
          return "c_QList_T_QObject_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_QObject_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_QObject_T___pop_back";
          break;
        case 358:
          return "c_QList_T_QObject_T___pop_front";
          break;
        case 359:
          return "c_QList_T_QObject_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_QObject_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_QObject_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_QObject_T___removeLast";
          break;
        case 363:
          return "c_QList_T_QObject_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_QObject_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_QObject_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_QObject_T___size";
          break;
        case 368:
          return "c_QList_T_QObject_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_QObject_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_QObject_T___squeeze";
          break;
        case 372:
          return "c_QList_T_QObject_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_QObject_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_QObject_T___toList";
          break;
        case 375:
          return "c_QList_T_QObject_T___toVector";
          break;
        case 376:
          return "c_QList_T_QObject_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<QByteArray>) {
      switch (id) {
        case 314:
          return "c_QList_T_QByteArray_T___constructor";
          break;
        case 315:
          return "c_QList_T_QByteArray_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_QByteArray_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_QByteArray_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_QByteArray_T___back";
          break;
        case 320:
          return "c_QList_T_QByteArray_T___back";
          break;
        case 321:
          return "c_QList_T_QByteArray_T___capacity";
          break;
        case 322:
          return "c_QList_T_QByteArray_T___clear";
          break;
        case 324:
          return "c_QList_T_QByteArray_T___constFirst";
          break;
        case 325:
          return "c_QList_T_QByteArray_T___constLast";
          break;
        case 326:
          return "c_QList_T_QByteArray_T___count";
          break;
        case 329:
          return "c_QList_T_QByteArray_T___detach";
          break;
        case 330:
          return "c_QList_T_QByteArray_T___empty";
          break;
        case 331:
          return "c_QList_T_QByteArray_T___first";
          break;
        case 332:
          return "c_QList_T_QByteArray_T___first";
          break;
        case 333:
          return "c_QList_T_QByteArray_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_QByteArray_T___front";
          break;
        case 337:
          return "c_QList_T_QByteArray_T___front";
          break;
        case 338:
          return "c_QList_T_QByteArray_T___isDetached";
          break;
        case 339:
          return "c_QList_T_QByteArray_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_QByteArray_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_QByteArray_T___last";
          break;
        case 342:
          return "c_QList_T_QByteArray_T___last";
          break;
        case 343:
          return "c_QList_T_QByteArray_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_QByteArray_T___length";
          break;
        case 345:
          return "c_QList_T_QByteArray_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_QByteArray_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_QByteArray_T___pop_back";
          break;
        case 358:
          return "c_QList_T_QByteArray_T___pop_front";
          break;
        case 359:
          return "c_QList_T_QByteArray_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_QByteArray_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_QByteArray_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_QByteArray_T___removeLast";
          break;
        case 363:
          return "c_QList_T_QByteArray_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_QByteArray_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_QByteArray_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_QByteArray_T___size";
          break;
        case 368:
          return "c_QList_T_QByteArray_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_QByteArray_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_QByteArray_T___squeeze";
          break;
        case 372:
          return "c_QList_T_QByteArray_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_QByteArray_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_QByteArray_T___toList";
          break;
        case 375:
          return "c_QList_T_QByteArray_T___toVector";
          break;
        case 376:
          return "c_QList_T_QByteArray_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      switch (id) {
        case 314:
          return "c_QList_T_DockWidget_T___constructor";
          break;
        case 315:
          return "c_QList_T_DockWidget_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_DockWidget_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_DockWidget_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_DockWidget_T___back";
          break;
        case 320:
          return "c_QList_T_DockWidget_T___back";
          break;
        case 321:
          return "c_QList_T_DockWidget_T___capacity";
          break;
        case 322:
          return "c_QList_T_DockWidget_T___clear";
          break;
        case 324:
          return "c_QList_T_DockWidget_T___constFirst";
          break;
        case 325:
          return "c_QList_T_DockWidget_T___constLast";
          break;
        case 326:
          return "c_QList_T_DockWidget_T___count";
          break;
        case 329:
          return "c_QList_T_DockWidget_T___detach";
          break;
        case 330:
          return "c_QList_T_DockWidget_T___empty";
          break;
        case 331:
          return "c_QList_T_DockWidget_T___first";
          break;
        case 332:
          return "c_QList_T_DockWidget_T___first";
          break;
        case 333:
          return "c_QList_T_DockWidget_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_DockWidget_T___front";
          break;
        case 337:
          return "c_QList_T_DockWidget_T___front";
          break;
        case 338:
          return "c_QList_T_DockWidget_T___isDetached";
          break;
        case 339:
          return "c_QList_T_DockWidget_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_DockWidget_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_DockWidget_T___last";
          break;
        case 342:
          return "c_QList_T_DockWidget_T___last";
          break;
        case 343:
          return "c_QList_T_DockWidget_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_DockWidget_T___length";
          break;
        case 345:
          return "c_QList_T_DockWidget_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_DockWidget_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_DockWidget_T___pop_back";
          break;
        case 358:
          return "c_QList_T_DockWidget_T___pop_front";
          break;
        case 359:
          return "c_QList_T_DockWidget_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_DockWidget_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_DockWidget_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_DockWidget_T___removeLast";
          break;
        case 363:
          return "c_QList_T_DockWidget_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_DockWidget_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_DockWidget_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_DockWidget_T___size";
          break;
        case 368:
          return "c_QList_T_DockWidget_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_DockWidget_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_DockWidget_T___squeeze";
          break;
        case 372:
          return "c_QList_T_DockWidget_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_DockWidget_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_DockWidget_T___toList";
          break;
        case 375:
          return "c_QList_T_DockWidget_T___toVector";
          break;
        case 376:
          return "c_QList_T_DockWidget_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      switch (id) {
        case 314:
          return "c_QList_T_FloatingWindow_T___constructor";
          break;
        case 315:
          return "c_QList_T_FloatingWindow_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_FloatingWindow_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_FloatingWindow_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_FloatingWindow_T___back";
          break;
        case 320:
          return "c_QList_T_FloatingWindow_T___back";
          break;
        case 321:
          return "c_QList_T_FloatingWindow_T___capacity";
          break;
        case 322:
          return "c_QList_T_FloatingWindow_T___clear";
          break;
        case 324:
          return "c_QList_T_FloatingWindow_T___constFirst";
          break;
        case 325:
          return "c_QList_T_FloatingWindow_T___constLast";
          break;
        case 326:
          return "c_QList_T_FloatingWindow_T___count";
          break;
        case 329:
          return "c_QList_T_FloatingWindow_T___detach";
          break;
        case 330:
          return "c_QList_T_FloatingWindow_T___empty";
          break;
        case 331:
          return "c_QList_T_FloatingWindow_T___first";
          break;
        case 332:
          return "c_QList_T_FloatingWindow_T___first";
          break;
        case 333:
          return "c_QList_T_FloatingWindow_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_FloatingWindow_T___front";
          break;
        case 337:
          return "c_QList_T_FloatingWindow_T___front";
          break;
        case 338:
          return "c_QList_T_FloatingWindow_T___isDetached";
          break;
        case 339:
          return "c_QList_T_FloatingWindow_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_FloatingWindow_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_FloatingWindow_T___last";
          break;
        case 342:
          return "c_QList_T_FloatingWindow_T___last";
          break;
        case 343:
          return "c_QList_T_FloatingWindow_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_FloatingWindow_T___length";
          break;
        case 345:
          return "c_QList_T_FloatingWindow_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_FloatingWindow_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_FloatingWindow_T___pop_back";
          break;
        case 358:
          return "c_QList_T_FloatingWindow_T___pop_front";
          break;
        case 359:
          return "c_QList_T_FloatingWindow_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_FloatingWindow_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_FloatingWindow_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_FloatingWindow_T___removeLast";
          break;
        case 363:
          return "c_QList_T_FloatingWindow_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_FloatingWindow_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_FloatingWindow_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_FloatingWindow_T___size";
          break;
        case 368:
          return "c_QList_T_FloatingWindow_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_FloatingWindow_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_FloatingWindow_T___squeeze";
          break;
        case 372:
          return "c_QList_T_FloatingWindow_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_FloatingWindow_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_FloatingWindow_T___toList";
          break;
        case 375:
          return "c_QList_T_FloatingWindow_T___toVector";
          break;
        case 376:
          return "c_QList_T_FloatingWindow_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      switch (id) {
        case 314:
          return "c_QList_T_Group_T___constructor";
          break;
        case 315:
          return "c_QList_T_Group_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_Group_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_Group_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_Group_T___back";
          break;
        case 320:
          return "c_QList_T_Group_T___back";
          break;
        case 321:
          return "c_QList_T_Group_T___capacity";
          break;
        case 322:
          return "c_QList_T_Group_T___clear";
          break;
        case 324:
          return "c_QList_T_Group_T___constFirst";
          break;
        case 325:
          return "c_QList_T_Group_T___constLast";
          break;
        case 326:
          return "c_QList_T_Group_T___count";
          break;
        case 329:
          return "c_QList_T_Group_T___detach";
          break;
        case 330:
          return "c_QList_T_Group_T___empty";
          break;
        case 331:
          return "c_QList_T_Group_T___first";
          break;
        case 332:
          return "c_QList_T_Group_T___first";
          break;
        case 333:
          return "c_QList_T_Group_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_Group_T___front";
          break;
        case 337:
          return "c_QList_T_Group_T___front";
          break;
        case 338:
          return "c_QList_T_Group_T___isDetached";
          break;
        case 339:
          return "c_QList_T_Group_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_Group_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_Group_T___last";
          break;
        case 342:
          return "c_QList_T_Group_T___last";
          break;
        case 343:
          return "c_QList_T_Group_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_Group_T___length";
          break;
        case 345:
          return "c_QList_T_Group_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_Group_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_Group_T___pop_back";
          break;
        case 358:
          return "c_QList_T_Group_T___pop_front";
          break;
        case 359:
          return "c_QList_T_Group_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_Group_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_Group_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_Group_T___removeLast";
          break;
        case 363:
          return "c_QList_T_Group_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_Group_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_Group_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_Group_T___size";
          break;
        case 368:
          return "c_QList_T_Group_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_Group_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_Group_T___squeeze";
          break;
        case 372:
          return "c_QList_T_Group_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_Group_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_Group_T___toList";
          break;
        case 375:
          return "c_QList_T_Group_T___toVector";
          break;
        case 376:
          return "c_QList_T_Group_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      switch (id) {
        case 314:
          return "c_QList_T_Layout_T___constructor";
          break;
        case 315:
          return "c_QList_T_Layout_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_Layout_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_Layout_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_Layout_T___back";
          break;
        case 320:
          return "c_QList_T_Layout_T___back";
          break;
        case 321:
          return "c_QList_T_Layout_T___capacity";
          break;
        case 322:
          return "c_QList_T_Layout_T___clear";
          break;
        case 324:
          return "c_QList_T_Layout_T___constFirst";
          break;
        case 325:
          return "c_QList_T_Layout_T___constLast";
          break;
        case 326:
          return "c_QList_T_Layout_T___count";
          break;
        case 329:
          return "c_QList_T_Layout_T___detach";
          break;
        case 330:
          return "c_QList_T_Layout_T___empty";
          break;
        case 331:
          return "c_QList_T_Layout_T___first";
          break;
        case 332:
          return "c_QList_T_Layout_T___first";
          break;
        case 333:
          return "c_QList_T_Layout_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_Layout_T___front";
          break;
        case 337:
          return "c_QList_T_Layout_T___front";
          break;
        case 338:
          return "c_QList_T_Layout_T___isDetached";
          break;
        case 339:
          return "c_QList_T_Layout_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_Layout_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_Layout_T___last";
          break;
        case 342:
          return "c_QList_T_Layout_T___last";
          break;
        case 343:
          return "c_QList_T_Layout_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_Layout_T___length";
          break;
        case 345:
          return "c_QList_T_Layout_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_Layout_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_Layout_T___pop_back";
          break;
        case 358:
          return "c_QList_T_Layout_T___pop_front";
          break;
        case 359:
          return "c_QList_T_Layout_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_Layout_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_Layout_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_Layout_T___removeLast";
          break;
        case 363:
          return "c_QList_T_Layout_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_Layout_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_Layout_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_Layout_T___size";
          break;
        case 368:
          return "c_QList_T_Layout_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_Layout_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_Layout_T___squeeze";
          break;
        case 372:
          return "c_QList_T_Layout_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_Layout_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_Layout_T___toList";
          break;
        case 375:
          return "c_QList_T_Layout_T___toVector";
          break;
        case 376:
          return "c_QList_T_Layout_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      switch (id) {
        case 314:
          return "c_QList_T_MainWindow_T___constructor";
          break;
        case 315:
          return "c_QList_T_MainWindow_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_MainWindow_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_MainWindow_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_MainWindow_T___back";
          break;
        case 320:
          return "c_QList_T_MainWindow_T___back";
          break;
        case 321:
          return "c_QList_T_MainWindow_T___capacity";
          break;
        case 322:
          return "c_QList_T_MainWindow_T___clear";
          break;
        case 324:
          return "c_QList_T_MainWindow_T___constFirst";
          break;
        case 325:
          return "c_QList_T_MainWindow_T___constLast";
          break;
        case 326:
          return "c_QList_T_MainWindow_T___count";
          break;
        case 329:
          return "c_QList_T_MainWindow_T___detach";
          break;
        case 330:
          return "c_QList_T_MainWindow_T___empty";
          break;
        case 331:
          return "c_QList_T_MainWindow_T___first";
          break;
        case 332:
          return "c_QList_T_MainWindow_T___first";
          break;
        case 333:
          return "c_QList_T_MainWindow_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_MainWindow_T___front";
          break;
        case 337:
          return "c_QList_T_MainWindow_T___front";
          break;
        case 338:
          return "c_QList_T_MainWindow_T___isDetached";
          break;
        case 339:
          return "c_QList_T_MainWindow_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_MainWindow_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_MainWindow_T___last";
          break;
        case 342:
          return "c_QList_T_MainWindow_T___last";
          break;
        case 343:
          return "c_QList_T_MainWindow_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_MainWindow_T___length";
          break;
        case 345:
          return "c_QList_T_MainWindow_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_MainWindow_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_MainWindow_T___pop_back";
          break;
        case 358:
          return "c_QList_T_MainWindow_T___pop_front";
          break;
        case 359:
          return "c_QList_T_MainWindow_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_MainWindow_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_MainWindow_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_MainWindow_T___removeLast";
          break;
        case 363:
          return "c_QList_T_MainWindow_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_MainWindow_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_MainWindow_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_MainWindow_T___size";
          break;
        case 368:
          return "c_QList_T_MainWindow_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_MainWindow_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_MainWindow_T___squeeze";
          break;
        case 372:
          return "c_QList_T_MainWindow_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_MainWindow_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_MainWindow_T___toList";
          break;
        case 375:
          return "c_QList_T_MainWindow_T___toVector";
          break;
        case 376:
          return "c_QList_T_MainWindow_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<int>) {
      switch (id) {
        case 314:
          return "c_QList_T_int_T___constructor";
          break;
        case 315:
          return "c_QList_T_int_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_int_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_int_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_int_T___back";
          break;
        case 320:
          return "c_QList_T_int_T___back";
          break;
        case 321:
          return "c_QList_T_int_T___capacity";
          break;
        case 322:
          return "c_QList_T_int_T___clear";
          break;
        case 324:
          return "c_QList_T_int_T___constFirst";
          break;
        case 325:
          return "c_QList_T_int_T___constLast";
          break;
        case 326:
          return "c_QList_T_int_T___count";
          break;
        case 329:
          return "c_QList_T_int_T___detach";
          break;
        case 330:
          return "c_QList_T_int_T___empty";
          break;
        case 331:
          return "c_QList_T_int_T___first";
          break;
        case 332:
          return "c_QList_T_int_T___first";
          break;
        case 333:
          return "c_QList_T_int_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_int_T___front";
          break;
        case 337:
          return "c_QList_T_int_T___front";
          break;
        case 338:
          return "c_QList_T_int_T___isDetached";
          break;
        case 339:
          return "c_QList_T_int_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_int_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_int_T___last";
          break;
        case 342:
          return "c_QList_T_int_T___last";
          break;
        case 343:
          return "c_QList_T_int_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_int_T___length";
          break;
        case 345:
          return "c_QList_T_int_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_int_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_int_T___pop_back";
          break;
        case 358:
          return "c_QList_T_int_T___pop_front";
          break;
        case 359:
          return "c_QList_T_int_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_int_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_int_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_int_T___removeLast";
          break;
        case 363:
          return "c_QList_T_int_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_int_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_int_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_int_T___size";
          break;
        case 368:
          return "c_QList_T_int_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_int_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_int_T___squeeze";
          break;
        case 372:
          return "c_QList_T_int_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_int_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_int_T___toList";
          break;
        case 375:
          return "c_QList_T_int_T___toVector";
          break;
        case 376:
          return "c_QList_T_int_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<Item>) {
      switch (id) {
        case 314:
          return "c_QList_T_Item_T___constructor";
          break;
        case 315:
          return "c_QList_T_Item_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_Item_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_Item_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_Item_T___back";
          break;
        case 320:
          return "c_QList_T_Item_T___back";
          break;
        case 321:
          return "c_QList_T_Item_T___capacity";
          break;
        case 322:
          return "c_QList_T_Item_T___clear";
          break;
        case 324:
          return "c_QList_T_Item_T___constFirst";
          break;
        case 325:
          return "c_QList_T_Item_T___constLast";
          break;
        case 326:
          return "c_QList_T_Item_T___count";
          break;
        case 329:
          return "c_QList_T_Item_T___detach";
          break;
        case 330:
          return "c_QList_T_Item_T___empty";
          break;
        case 331:
          return "c_QList_T_Item_T___first";
          break;
        case 332:
          return "c_QList_T_Item_T___first";
          break;
        case 333:
          return "c_QList_T_Item_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_Item_T___front";
          break;
        case 337:
          return "c_QList_T_Item_T___front";
          break;
        case 338:
          return "c_QList_T_Item_T___isDetached";
          break;
        case 339:
          return "c_QList_T_Item_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_Item_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_Item_T___last";
          break;
        case 342:
          return "c_QList_T_Item_T___last";
          break;
        case 343:
          return "c_QList_T_Item_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_Item_T___length";
          break;
        case 345:
          return "c_QList_T_Item_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_Item_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_Item_T___pop_back";
          break;
        case 358:
          return "c_QList_T_Item_T___pop_front";
          break;
        case 359:
          return "c_QList_T_Item_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_Item_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_Item_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_Item_T___removeLast";
          break;
        case 363:
          return "c_QList_T_Item_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_Item_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_Item_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_Item_T___size";
          break;
        case 368:
          return "c_QList_T_Item_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_Item_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_Item_T___squeeze";
          break;
        case 372:
          return "c_QList_T_Item_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_Item_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_Item_T___toList";
          break;
        case 375:
          return "c_QList_T_Item_T___toVector";
          break;
        case 376:
          return "c_QList_T_Item_T___value_qsizetype";
          break;
      }
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      switch (id) {
        case 314:
          return "c_QList_T_Separator_T___constructor";
          break;
        case 315:
          return "c_QList_T_Separator_T___constructor_qsizetype";
          break;
        case 317:
          return "c_QList_T_Separator_T___append_QList_T";
          break;
        case 318:
          return "c_QList_T_Separator_T___at_qsizetype";
          break;
        case 319:
          return "c_QList_T_Separator_T___back";
          break;
        case 320:
          return "c_QList_T_Separator_T___back";
          break;
        case 321:
          return "c_QList_T_Separator_T___capacity";
          break;
        case 322:
          return "c_QList_T_Separator_T___clear";
          break;
        case 324:
          return "c_QList_T_Separator_T___constFirst";
          break;
        case 325:
          return "c_QList_T_Separator_T___constLast";
          break;
        case 326:
          return "c_QList_T_Separator_T___count";
          break;
        case 329:
          return "c_QList_T_Separator_T___detach";
          break;
        case 330:
          return "c_QList_T_Separator_T___empty";
          break;
        case 331:
          return "c_QList_T_Separator_T___first";
          break;
        case 332:
          return "c_QList_T_Separator_T___first";
          break;
        case 333:
          return "c_QList_T_Separator_T___first_qsizetype";
          break;
        case 336:
          return "c_QList_T_Separator_T___front";
          break;
        case 337:
          return "c_QList_T_Separator_T___front";
          break;
        case 338:
          return "c_QList_T_Separator_T___isDetached";
          break;
        case 339:
          return "c_QList_T_Separator_T___isEmpty";
          break;
        case 340:
          return "c_QList_T_Separator_T___isSharedWith_QList_T";
          break;
        case 341:
          return "c_QList_T_Separator_T___last";
          break;
        case 342:
          return "c_QList_T_Separator_T___last";
          break;
        case 343:
          return "c_QList_T_Separator_T___last_qsizetype";
          break;
        case 344:
          return "c_QList_T_Separator_T___length";
          break;
        case 345:
          return "c_QList_T_Separator_T___mid_qsizetype_qsizetype";
          break;
        case 346:
          return "c_QList_T_Separator_T___move_qsizetype_qsizetype";
          break;
        case 357:
          return "c_QList_T_Separator_T___pop_back";
          break;
        case 358:
          return "c_QList_T_Separator_T___pop_front";
          break;
        case 359:
          return "c_QList_T_Separator_T___remove_qsizetype_qsizetype";
          break;
        case 360:
          return "c_QList_T_Separator_T___removeAt_qsizetype";
          break;
        case 361:
          return "c_QList_T_Separator_T___removeFirst";
          break;
        case 362:
          return "c_QList_T_Separator_T___removeLast";
          break;
        case 363:
          return "c_QList_T_Separator_T___reserve_qsizetype";
          break;
        case 364:
          return "c_QList_T_Separator_T___resize_qsizetype";
          break;
        case 366:
          return "c_QList_T_Separator_T___shrink_to_fit";
          break;
        case 367:
          return "c_QList_T_Separator_T___size";
          break;
        case 368:
          return "c_QList_T_Separator_T___sliced_qsizetype";
          break;
        case 369:
          return "c_QList_T_Separator_T___sliced_qsizetype_qsizetype";
          break;
        case 370:
          return "c_QList_T_Separator_T___squeeze";
          break;
        case 372:
          return "c_QList_T_Separator_T___swapItemsAt_qsizetype_qsizetype";
          break;
        case 373:
          return "c_QList_T_Separator_T___takeAt_qsizetype";
          break;
        case 374:
          return "c_QList_T_Separator_T___toList";
          break;
        case 375:
          return "c_QList_T_Separator_T___toVector";
          break;
        case 376:
          return "c_QList_T_Separator_T___value_qsizetype";
          break;
      }
    }
    return "";
  }

  dynamic getFinalizer() {
    if (this is QList<QString>) {
      return _finalizer_T_QString_T_;
    }
    if (this is QList<int>) {
      return _finalizer_T_unsigned_int_T_;
    }
    if (this is QList<QObject>) {
      return _finalizer_T_QObject_T_;
    }
    if (this is QList<QByteArray>) {
      return _finalizer_T_QByteArray_T_;
    }
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      return _finalizer_T_DockWidget_T_;
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      return _finalizer_T_FloatingWindow_T_;
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      return _finalizer_T_Group_T_;
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      return _finalizer_T_Layout_T_;
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      return _finalizer_T_MainWindow_T_;
    }
    if (this is QList<int>) {
      return _finalizer_T_int_T_;
    }
    if (this is QList<Item>) {
      return _finalizer_T_Item_T_;
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      return _finalizer_T_Separator_T_;
    }
    print("ERROR: Couldn't find finalizer for" + this.runtimeType.toString());
  } //QList<T>()

  QList() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            '${getCFunctionName(314)}')
        .asFunction();
    thisCpp = func();
    QList.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } //QList<T>(qsizetype size)
  QList.ctor2(int size) {
    final voidstar_Func_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_FFI>>(
            '${getCFunctionName(315)}')
        .asFunction();
    thisCpp = func(size);
    QList.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // append(const QList<T > & l)
  append(QList? l) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            '${getCFunctionName(317)}')
        .asFunction();
    func(thisCpp, l == null ? ffi.nullptr : l.thisCpp);
  } // at(qsizetype i) const

  T at(int i) {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      return (func(thisCpp, i) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(318)}')
          .asFunction();
      return (func(thisCpp, i) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // back()

  T back() {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(319)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // capacity() const

  int capacity() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(321)}')
        .asFunction();
    return func(thisCpp);
  } // clear()

  clear() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(322)}')
        .asFunction();
    func(thisCpp);
  } // constFirst() const

  T constFirst() {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(324)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // constLast() const

  T constLast() {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(325)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // count() const

  int count() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(326)}')
        .asFunction();
    return func(thisCpp);
  } // detach()

  detach() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(329)}')
        .asFunction();
    func(thisCpp);
  } // empty() const

  bool empty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            '${getCFunctionName(330)}')
        .asFunction();
    return func(thisCpp) != 0;
  } // first()

  T first() {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(331)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // front()

  T front() {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(336)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // isDetached() const

  bool isDetached() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            '${getCFunctionName(338)}')
        .asFunction();
    return func(thisCpp) != 0;
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            '${getCFunctionName(339)}')
        .asFunction();
    return func(thisCpp) != 0;
  } // isSharedWith(const QList<T > & other) const

  bool isSharedWith(QList? other) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            '${getCFunctionName(340)}')
        .asFunction();
    return func(thisCpp, other == null ? ffi.nullptr : other.thisCpp) != 0;
  } // last()

  T last() {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
              '${getCFunctionName(341)}')
          .asFunction();
      return (func(thisCpp) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // length() const

  int length() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(344)}')
        .asFunction();
    return func(thisCpp);
  } // move(qsizetype from, qsizetype to)

  move(int from, int to) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            '${getCFunctionName(346)}')
        .asFunction();
    func(thisCpp, from, to);
  } // pop_back()

  pop_back() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(357)}')
        .asFunction();
    func(thisCpp);
  } // pop_front()

  pop_front() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(358)}')
        .asFunction();
    func(thisCpp);
  } // remove(qsizetype i, qsizetype n)

  remove(int i, {int n = 1}) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            '${getCFunctionName(359)}')
        .asFunction();
    func(thisCpp, i, n);
  } // removeAt(qsizetype i)

  removeAt(int i) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(360)}')
        .asFunction();
    func(thisCpp, i);
  } // removeFirst()

  removeFirst() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(361)}')
        .asFunction();
    func(thisCpp);
  } // removeLast()

  removeLast() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(362)}')
        .asFunction();
    func(thisCpp);
  } // reserve(qsizetype size)

  reserve(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(363)}')
        .asFunction();
    func(thisCpp, size);
  } // resize(qsizetype size)

  resize(int size) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(364)}')
        .asFunction();
    func(thisCpp, size);
  } // resize_internal(qsizetype i)

  resize_internal(int i) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            '${getCFunctionName(365)}')
        .asFunction();
    func(thisCpp, i);
  } // shrink_to_fit()

  shrink_to_fit() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(366)}')
        .asFunction();
    func(thisCpp);
  } // size() const

  int size() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            '${getCFunctionName(367)}')
        .asFunction();
    return func(thisCpp);
  } // squeeze()

  squeeze() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(370)}')
        .asFunction();
    func(thisCpp);
  } // swapItemsAt(qsizetype i, qsizetype j)

  swapItemsAt(int i, int j) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            '${getCFunctionName(372)}')
        .asFunction();
    func(thisCpp, i, j);
  } // takeAt(qsizetype i)

  T takeAt(int i) {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      return (func(thisCpp, i) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(373)}')
          .asFunction();
      return (func(thisCpp, i) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  } // value(qsizetype i) const

  T value(int i) {
    if (this is QList<KDDWBindingsCore.DockWidget>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.DockWidget.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Separator>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Separator.fromCppPointer(result, false) as T);
    }
    if (this is QList<QByteArray>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QByteArray.fromCppPointer(result, true) as T);
    }
    if (this is QList<QString>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QString.fromCppPointer(result, true) as T);
    }
    if (this is QList<KDDWBindingsCore.FloatingWindow>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false)
          as T);
    }
    if (this is QList<KDDWBindingsCore.Group>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Group.fromCppPointer(result, false) as T);
    }
    if (this is QList<Item>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (Item.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.Layout>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.Layout.fromCppPointer(result, false) as T);
    }
    if (this is QList<KDDWBindingsCore.MainWindow>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (KDDWBindingsCore.MainWindow.fromCppPointer(result, false) as T);
    }
    if (this is QList<QObject>) {
      final voidstar_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      ffi.Pointer<void> result = func(thisCpp, i);
      return (QObject.fromCppPointer(result, false) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      return (func(thisCpp, i) as T);
    }
    if (this is QList<int>) {
      final int_Func_voidstar_int func = _dylib
          .lookup<ffi.NativeFunction<int_Func_voidstar_ffi_Int32_FFI>>(
              '${getCFunctionName(376)}')
          .asFunction();
      return (func(thisCpp, i) as T);
    }
    print(
        "Unreachable, but required, due to null safety we need to return something");
    throw Error();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            '${getCFunctionName(-2)}')
        .asFunction();
    func(thisCpp);
  }
}
