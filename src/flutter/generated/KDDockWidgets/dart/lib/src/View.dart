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
        'c_KDDockWidgets__View_Finalizer');

class View {
//tag=1060
  static var s_dartInstanceByCppPtr = Map<int, View>();
  var _thisCpp = null;
  bool _needsAutoDelete = false;
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
  factory View.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        View.fromCppPointer(cppPointer, needsAutoDelete)) as View;
  }
  View.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  View.init() {}
//tag=1024

//tag=1027
// aboutToBeDestroyed() const
  bool aboutToBeDestroyed() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__aboutToBeDestroyed')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// activateWindow()
  activateWindow() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(602))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.activateWindow();
  }

//tag=1024
  static
//tag=1027
// boundedMaxSize(QSize min, QSize max)
      QSize boundedMaxSize(QSize min, QSize max) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_static_KDDockWidgets__View__boundedMaxSize_QSize_QSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(min == null ? ffi.nullptr : min.thisCpp,
        max == null ? ffi.nullptr : max.thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// close()
  bool close() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(604))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::close()! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.close();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// closeRootView()
  closeRootView() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__closeRootView')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// createPlatformWindow()
  createPlatformWindow() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(606))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.createPlatformWindow();
  }

//tag=1024
  static
//tag=1027
// equals(const KDDockWidgets::View * one, const KDDockWidgets::View * two)
      bool equals(View? one, View? two) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_static_KDDockWidgets__View__equals_View_View')
        .asFunction();
//tag=1029
    return func(one == null ? ffi.nullptr : one.thisCpp,
            two == null ? ffi.nullptr : two.thisCpp) !=
        0;
  }
//tag=1024

//tag=1027
// equals(const KDDockWidgets::View * other) const
  bool equals_2(View? other) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__View__equals_View')
        .asFunction();
//tag=1029
    return func(thisCpp, other == null ? ffi.nullptr : other.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// free()
  free() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__free')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// free_impl()
  free_impl() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(610))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::free_impl()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.free_impl();
  }
//tag=1024

//tag=1027
// freed() const
  bool freed() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__freed')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// geometry() const
  QRect geometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(612))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::geometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.geometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// globalGeometry() const
  QRect globalGeometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__globalGeometry')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// grabMouse()
  grabMouse() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(614))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.grabMouse();
  }

//tag=1024
  static
//tag=1027
// hardcodedMinimumSize()
      QSize hardcodedMinimumSize() {
//tag=1028
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__View__hardcodedMinimumSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func();
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// hasFocus() const
  bool hasFocus() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(617))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// height() const
  int height() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__height')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// hide()
  hide() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(619))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::hide()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.hide();
  }
//tag=1024

//tag=1027
// id() const
  QString id() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__id')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// inDtor() const
  bool inDtor() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__inDtor')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// init()
  init() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(622))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::init()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.init();
  }
//tag=1024

//tag=1027
// isActiveWindow() const
  bool isActiveWindow() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(623))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isMaximized() const
  bool isMaximized() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(624))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isMinimized() const
  bool isMinimized() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(625))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isNull() const
  bool isNull() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(626))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isNull() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isRootView() const
  bool isRootView() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(627))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isVisible() const
  bool isVisible() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(628))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// mapFromGlobal(QPoint arg__1) const
  QPoint mapFromGlobal(QPoint arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(629))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapFromGlobal(QPoint arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(arg__1));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// mapTo(KDDockWidgets::View * arg__1, QPoint arg__2) const
  QPoint mapTo(View? arg__1, QPoint arg__2) {
//tag=1028
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(630))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void> arg__2) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapTo(KDDockWidgets::View * arg__1, QPoint arg__2) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.mapTo(
        View.fromCppPointer(arg__1), QPoint.fromCppPointer(arg__2));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// mapToGlobal(QPoint arg__1) const
  QPoint mapToGlobal(QPoint arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(631))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapToGlobal(QPoint arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(arg__1));
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// maxSizeHint() const
  QSize maxSizeHint() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(632))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// maximumSize() const
  QSize maximumSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(633))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> maximumSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::maximumSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.maximumSize();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// minSize() const
  QSize minSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(634))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::minSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minSize();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// minimumHeight() const
  int minimumHeight() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(635))
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1035
  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minimumHeight();
    return result;
  }
//tag=1024

//tag=1027
// minimumWidth() const
  int minimumWidth() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(636))
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1035
  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minimumWidth();
    return result;
  }
//tag=1024

//tag=1027
// move(QPoint arg__1)
  move(QPoint arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__View__move_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// move(int x, int y)
  move_2(int x, int y) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(638))
        .asFunction();
//tag=1030
    func(thisCpp, x, y);
  }

//tag=1035
  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.move_2(x, y);
  }
//tag=1024

//tag=1027
// normalGeometry() const
  QRect normalGeometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(639))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// objectName() const
  QString objectName() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(640))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::objectName() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.objectName();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// onResize(QSize newSize)
  bool onResize(QSize newSize) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(641))
        .asFunction();
//tag=1029
    return func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp) != 0;
  }

//tag=1035
  static int onResize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> newSize) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::onResize(QSize newSize)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.onResize(QSize.fromCppPointer(newSize));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// parentSize() const
  QSize parentSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__parentSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// pos() const
  QPoint pos() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__pos')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// raise()
  raise() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(644))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::raise()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.raise();
  }
//tag=1024

//tag=1027
// raiseAndActivate()
  raiseAndActivate() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(645))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.raiseAndActivate();
  }
//tag=1024

//tag=1027
// rect() const
  QRect rect() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__rect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// releaseKeyboard()
  releaseKeyboard() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(647))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.releaseKeyboard();
  }
//tag=1024

//tag=1027
// releaseMouse()
  releaseMouse() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(648))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.releaseMouse();
  }
//tag=1024

//tag=1027
// resize(QSize arg__1)
  resize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__View__resize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// resize(int w, int h)
  resize_2(int w, int h) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__View__resize_int_int')
        .asFunction();
//tag=1030
    func(thisCpp, w, h);
  }
//tag=1024

//tag=1027
// setAboutToBeDestroyed()
  setAboutToBeDestroyed() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__setAboutToBeDestroyed')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// setFixedHeight(int arg__1)
  setFixedHeight(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(652))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1035
  static void setFixedHeight_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setFixedHeight(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setFixedHeight(arg__1);
  }
//tag=1024

//tag=1027
// setFixedWidth(int arg__1)
  setFixedWidth(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(653))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1035
  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setFixedWidth(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setFixedWidth(arg__1);
  }
//tag=1024

//tag=1027
// setGeometry(QRect arg__1)
  setGeometry(QRect arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(654))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1027
// setHeight(int height)
  setHeight(int height) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(655))
        .asFunction();
//tag=1030
    func(thisCpp, height);
  }

//tag=1035
  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int height) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setHeight(int height)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setHeight(height);
  }
//tag=1024

//tag=1027
// setMaximumSize(QSize sz)
  setMaximumSize(QSize sz) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(656))
        .asFunction();
//tag=1030
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

//tag=1035
  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }
//tag=1024

//tag=1027
// setMinimumSize(QSize arg__1)
  setMinimumSize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(657))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMinimumSize(QSize arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMinimumSize(QSize.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1027
// setMouseTracking(bool arg__1)
  setMouseTracking(bool arg__1) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(658))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 ? 1 : 0);
  }

//tag=1035
  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMouseTracking(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMouseTracking(arg__1 != 0);
  }
//tag=1024

//tag=1027
// setObjectName(const QString & arg__1)
  setObjectName(String? arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(659))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

//tag=1035
  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setObjectName(const QString & arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setObjectName(QString.fromCppPointer(arg__1).toDartString());
  }
//tag=1024

//tag=1027
// setParent(KDDockWidgets::View * arg__1)
  setParent(View? arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(660))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setParent(KDDockWidgets::View * arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setParent(View.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1027
// setSize(QSize arg__1)
  setSize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__View__setSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// setSize(int width, int height)
  setSize_2(int width, int height) {
//tag=1028
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(662))
        .asFunction();
//tag=1030
    func(thisCpp, width, height);
  }

//tag=1035
  static void setSize_2_calledFromC(
      ffi.Pointer<void> thisCpp, int width, int height) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setSize(int width, int height)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setSize_2(width, height);
  }
//tag=1024

//tag=1027
// setVisible(bool arg__1)
  setVisible(bool arg__1) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(663))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 ? 1 : 0);
  }

//tag=1035
  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setVisible(arg__1 != 0);
  }
//tag=1024

//tag=1027
// setWidth(int width)
  setWidth(int width) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(664))
        .asFunction();
//tag=1030
    func(thisCpp, width);
  }

//tag=1035
  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int width) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setWidth(int width)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setWidth(width);
  }
//tag=1024

//tag=1027
// setWindowOpacity(double arg__1)
  setWindowOpacity(double arg__1) {
//tag=1028
    final void_Func_voidstar_double func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Double_FFI>>(
            cFunctionSymbolName(665))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1035
  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setWindowOpacity(double arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setWindowOpacity(arg__1);
  }
//tag=1024

//tag=1027
// setWindowTitle(const QString & title)
  setWindowTitle(String? title) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(666))
        .asFunction();
//tag=1030
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  }

//tag=1035
  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }
//tag=1024

//tag=1027
// setZOrder(int arg__1)
  setZOrder(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(667))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1035
  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setZOrder(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setZOrder(arg__1);
  }
//tag=1024

//tag=1027
// show()
  show() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(668))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::show()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.show();
  }
//tag=1024

//tag=1027
// showMaximized()
  showMaximized() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(669))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.showMaximized();
  }
//tag=1024

//tag=1027
// showMinimized()
  showMinimized() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(670))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.showMinimized();
  }
//tag=1024

//tag=1027
// showNormal()
  showNormal() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(671))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::showNormal()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.showNormal();
  }
//tag=1024

//tag=1027
// size() const
  QSize size() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__size')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// sizeHint() const
  QSize sizeHint() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(673))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// update()
  update() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(674))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::update()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.update();
  }
//tag=1024

//tag=1027
// width() const
  int width() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__width')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// windowGeometry() const
  QRect windowGeometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__windowGeometry')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// x() const
  int x() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__x')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// y() const
  int y() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__y')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 602:
        return "c_KDDockWidgets__View__activateWindow";
      case 604:
        return "c_KDDockWidgets__View__close";
      case 606:
        return "c_KDDockWidgets__View__createPlatformWindow";
      case 610:
        return "c_KDDockWidgets__View__free_impl";
      case 612:
        return "c_KDDockWidgets__View__geometry";
      case 614:
        return "c_KDDockWidgets__View__grabMouse";
      case 617:
        return "c_KDDockWidgets__View__hasFocus";
      case 619:
        return "c_KDDockWidgets__View__hide";
      case 622:
        return "c_KDDockWidgets__View__init";
      case 623:
        return "c_KDDockWidgets__View__isActiveWindow";
      case 624:
        return "c_KDDockWidgets__View__isMaximized";
      case 625:
        return "c_KDDockWidgets__View__isMinimized";
      case 626:
        return "c_KDDockWidgets__View__isNull";
      case 627:
        return "c_KDDockWidgets__View__isRootView";
      case 628:
        return "c_KDDockWidgets__View__isVisible";
      case 629:
        return "c_KDDockWidgets__View__mapFromGlobal_QPoint";
      case 630:
        return "c_KDDockWidgets__View__mapTo_View_QPoint";
      case 631:
        return "c_KDDockWidgets__View__mapToGlobal_QPoint";
      case 632:
        return "c_KDDockWidgets__View__maxSizeHint";
      case 633:
        return "c_KDDockWidgets__View__maximumSize";
      case 634:
        return "c_KDDockWidgets__View__minSize";
      case 635:
        return "c_KDDockWidgets__View__minimumHeight";
      case 636:
        return "c_KDDockWidgets__View__minimumWidth";
      case 638:
        return "c_KDDockWidgets__View__move_int_int";
      case 639:
        return "c_KDDockWidgets__View__normalGeometry";
      case 640:
        return "c_KDDockWidgets__View__objectName";
      case 641:
        return "c_KDDockWidgets__View__onResize_QSize";
      case 644:
        return "c_KDDockWidgets__View__raise";
      case 645:
        return "c_KDDockWidgets__View__raiseAndActivate";
      case 647:
        return "c_KDDockWidgets__View__releaseKeyboard";
      case 648:
        return "c_KDDockWidgets__View__releaseMouse";
      case 652:
        return "c_KDDockWidgets__View__setFixedHeight_int";
      case 653:
        return "c_KDDockWidgets__View__setFixedWidth_int";
      case 654:
        return "c_KDDockWidgets__View__setGeometry_QRect";
      case 655:
        return "c_KDDockWidgets__View__setHeight_int";
      case 656:
        return "c_KDDockWidgets__View__setMaximumSize_QSize";
      case 657:
        return "c_KDDockWidgets__View__setMinimumSize_QSize";
      case 658:
        return "c_KDDockWidgets__View__setMouseTracking_bool";
      case 659:
        return "c_KDDockWidgets__View__setObjectName_QString";
      case 660:
        return "c_KDDockWidgets__View__setParent_View";
      case 662:
        return "c_KDDockWidgets__View__setSize_int_int";
      case 663:
        return "c_KDDockWidgets__View__setVisible_bool";
      case 664:
        return "c_KDDockWidgets__View__setWidth_int";
      case 665:
        return "c_KDDockWidgets__View__setWindowOpacity_double";
      case 666:
        return "c_KDDockWidgets__View__setWindowTitle_QString";
      case 667:
        return "c_KDDockWidgets__View__setZOrder_int";
      case 668:
        return "c_KDDockWidgets__View__show";
      case 669:
        return "c_KDDockWidgets__View__showMaximized";
      case 670:
        return "c_KDDockWidgets__View__showMinimized";
      case 671:
        return "c_KDDockWidgets__View__showNormal";
      case 673:
        return "c_KDDockWidgets__View__sizeHint";
      case 674:
        return "c_KDDockWidgets__View__update";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 602:
        return "activateWindow";
      case 604:
        return "close";
      case 606:
        return "createPlatformWindow";
      case 610:
        return "free_impl";
      case 612:
        return "geometry";
      case 614:
        return "grabMouse";
      case 617:
        return "hasFocus";
      case 619:
        return "hide";
      case 622:
        return "init";
      case 623:
        return "isActiveWindow";
      case 624:
        return "isMaximized";
      case 625:
        return "isMinimized";
      case 626:
        return "isNull";
      case 627:
        return "isRootView";
      case 628:
        return "isVisible";
      case 629:
        return "mapFromGlobal";
      case 630:
        return "mapTo";
      case 631:
        return "mapToGlobal";
      case 632:
        return "maxSizeHint";
      case 633:
        return "maximumSize";
      case 634:
        return "minSize";
      case 635:
        return "minimumHeight";
      case 636:
        return "minimumWidth";
      case 638:
        return "move_2";
      case 639:
        return "normalGeometry";
      case 640:
        return "objectName";
      case 641:
        return "onResize";
      case 644:
        return "raise";
      case 645:
        return "raiseAndActivate";
      case 647:
        return "releaseKeyboard";
      case 648:
        return "releaseMouse";
      case 652:
        return "setFixedHeight";
      case 653:
        return "setFixedWidth";
      case 654:
        return "setGeometry";
      case 655:
        return "setHeight";
      case 656:
        return "setMaximumSize";
      case 657:
        return "setMinimumSize";
      case 658:
        return "setMouseTracking";
      case 659:
        return "setObjectName";
      case 660:
        return "setParent";
      case 662:
        return "setSize_2";
      case 663:
        return "setVisible";
      case 664:
        return "setWidth";
      case 665:
        return "setWindowOpacity";
      case 666:
        return "setWindowTitle";
      case 667:
        return "setZOrder";
      case 668:
        return "show";
      case 669:
        return "showMaximized";
      case 670:
        return "showMinimized";
      case 671:
        return "showNormal";
      case 673:
        return "sizeHint";
      case 674:
        return "update";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__View__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback602 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback602, 602);
    const callbackExcept604 = 0;
//tag=1021
    final callback604 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.close_calledFromC, callbackExcept604);
    registerCallback(thisCpp, callback604, 604);
//tag=1021
    final callback606 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback606, 606);
//tag=1021
    final callback610 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.free_impl_calledFromC);
    registerCallback(thisCpp, callback610, 610);
//tag=1021
    final callback612 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.geometry_calledFromC);
    registerCallback(thisCpp, callback612, 612);
//tag=1021
    final callback614 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback614, 614);
    const callbackExcept617 = 0;
//tag=1021
    final callback617 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.hasFocus_calledFromC, callbackExcept617);
    registerCallback(thisCpp, callback617, 617);
//tag=1021
    final callback619 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.hide_calledFromC);
    registerCallback(thisCpp, callback619, 619);
//tag=1021
    final callback622 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.init_calledFromC);
    registerCallback(thisCpp, callback622, 622);
    const callbackExcept623 = 0;
//tag=1021
    final callback623 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isActiveWindow_calledFromC, callbackExcept623);
    registerCallback(thisCpp, callback623, 623);
    const callbackExcept624 = 0;
//tag=1021
    final callback624 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isMaximized_calledFromC, callbackExcept624);
    registerCallback(thisCpp, callback624, 624);
    const callbackExcept625 = 0;
//tag=1021
    final callback625 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isMinimized_calledFromC, callbackExcept625);
    registerCallback(thisCpp, callback625, 625);
    const callbackExcept626 = 0;
//tag=1021
    final callback626 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept626);
    registerCallback(thisCpp, callback626, 626);
    const callbackExcept627 = 0;
//tag=1021
    final callback627 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isRootView_calledFromC, callbackExcept627);
    registerCallback(thisCpp, callback627, 627);
    const callbackExcept628 = 0;
//tag=1021
    final callback628 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isVisible_calledFromC, callbackExcept628);
    registerCallback(thisCpp, callback628, 628);
//tag=1021
    final callback629 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback629, 629);
//tag=1021
    final callback630 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View.mapTo_calledFromC);
    registerCallback(thisCpp, callback630, 630);
//tag=1021
    final callback631 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback631, 631);
//tag=1021
    final callback632 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback632, 632);
//tag=1021
    final callback633 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.maximumSize_calledFromC);
    registerCallback(thisCpp, callback633, 633);
//tag=1021
    final callback634 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.minSize_calledFromC);
    registerCallback(thisCpp, callback634, 634);
    const callbackExcept635 = 0;
//tag=1021
    final callback635 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept635);
    registerCallback(thisCpp, callback635, 635);
    const callbackExcept636 = 0;
//tag=1021
    final callback636 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept636);
    registerCallback(thisCpp, callback636, 636);
//tag=1021
    final callback638 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View.move_2_calledFromC);
    registerCallback(thisCpp, callback638, 638);
//tag=1021
    final callback639 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback639, 639);
//tag=1021
    final callback640 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.objectName_calledFromC);
    registerCallback(thisCpp, callback640, 640);
    const callbackExcept641 = 0;
//tag=1021
    final callback641 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            View.onResize_calledFromC, callbackExcept641);
    registerCallback(thisCpp, callback641, 641);
//tag=1021
    final callback644 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.raise_calledFromC);
    registerCallback(thisCpp, callback644, 644);
//tag=1021
    final callback645 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback645, 645);
//tag=1021
    final callback647 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback647, 647);
//tag=1021
    final callback648 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback648, 648);
//tag=1021
    final callback652 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback652, 652);
//tag=1021
    final callback653 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback653, 653);
//tag=1021
    final callback654 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback654, 654);
//tag=1021
    final callback655 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setHeight_calledFromC);
    registerCallback(thisCpp, callback655, 655);
//tag=1021
    final callback656 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback656, 656);
//tag=1021
    final callback657 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback657, 657);
//tag=1021
    final callback658 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback658, 658);
//tag=1021
    final callback659 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback659, 659);
//tag=1021
    final callback660 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setParent_calledFromC);
    registerCallback(thisCpp, callback660, 660);
//tag=1021
    final callback662 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback662, 662);
//tag=1021
    final callback663 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View.setVisible_calledFromC);
    registerCallback(thisCpp, callback663, 663);
//tag=1021
    final callback664 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setWidth_calledFromC);
    registerCallback(thisCpp, callback664, 664);
//tag=1021
    final callback665 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback665, 665);
//tag=1021
    final callback666 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback666, 666);
//tag=1021
    final callback667 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback667, 667);
//tag=1021
    final callback668 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.show_calledFromC);
    registerCallback(thisCpp, callback668, 668);
//tag=1021
    final callback669 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback669, 669);
//tag=1021
    final callback670 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback670, 670);
//tag=1021
    final callback671 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.showNormal_calledFromC);
    registerCallback(thisCpp, callback671, 671);
//tag=1021
    final callback673 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback673, 673);
//tag=1021
    final callback674 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.update_calledFromC);
    registerCallback(thisCpp, callback674, 674);
  }
}
