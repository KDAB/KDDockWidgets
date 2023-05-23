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
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;
final _finalizer =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_KDDockWidgets__LayoutSaver_Finalizer');

class LayoutSaver {
  static var s_dartInstanceByCppPtr = Map<int, LayoutSaver>();
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

  factory LayoutSaver.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        LayoutSaver.fromCppPointer(cppPointer, needsAutoDelete)) as LayoutSaver;
  }
  LayoutSaver.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  LayoutSaver.init() {} //LayoutSaver()
  LayoutSaver() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__LayoutSaver__constructor')
        .asFunction();
    thisCpp = func();
    LayoutSaver.s_dartInstanceByCppPtr[thisCpp.address] = this;
  } // restoreFromFile(const QString & jsonFilename)
  bool restoreFromFile(String? jsonFilename) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__LayoutSaver__restoreFromFile_QString')
        .asFunction();
    return func(thisCpp, jsonFilename?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }

  static // restoreInProgress()
      bool restoreInProgress() {
    final bool_Func_void func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_void_FFI>>(
            'c_static_KDDockWidgets__LayoutSaver__restoreInProgress')
        .asFunction();
    return func() != 0;
  } // restoreLayout(const QByteArray & arg__1)

  bool restoreLayout(QByteArray? arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__LayoutSaver__restoreLayout_QByteArray')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // saveToFile(const QString & jsonFilename)

  bool saveToFile(String? jsonFilename) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__LayoutSaver__saveToFile_QString')
        .asFunction();
    return func(thisCpp, jsonFilename?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // serializeLayout() const

  QByteArray serializeLayout() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__LayoutSaver__serializeLayout')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QByteArray.fromCppPointer(result, true);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__LayoutSaver__destructor')
        .asFunction();
    func(thisCpp);
  }
}
