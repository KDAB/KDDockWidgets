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
            cFunctionSymbolName(704))
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

//tag=1027
// asDropAreaController() const
  DropArea asDropAreaController() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__asDropAreaController')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// asLayout() const
  Layout asLayout() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__asLayout')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return Layout.fromCppPointer(result, false);
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
            cFunctionSymbolName(708))
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
// controller() const
  Controller controller() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__View__controller')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return Controller.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// createPlatformWindow()
  createPlatformWindow() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(711))
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
            cFunctionSymbolName(715))
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
            cFunctionSymbolName(717))
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
            cFunctionSymbolName(719))
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
            cFunctionSymbolName(722))
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
            cFunctionSymbolName(724))
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
            cFunctionSymbolName(727))
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
            cFunctionSymbolName(728))
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
            cFunctionSymbolName(729))
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
            cFunctionSymbolName(730))
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
            cFunctionSymbolName(731))
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
            cFunctionSymbolName(732))
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
            cFunctionSymbolName(733))
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
            cFunctionSymbolName(734))
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
            cFunctionSymbolName(735))
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
            cFunctionSymbolName(736))
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
            cFunctionSymbolName(737))
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
            cFunctionSymbolName(738))
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
            cFunctionSymbolName(739))
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
            cFunctionSymbolName(740))
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
            cFunctionSymbolName(741))
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
            cFunctionSymbolName(743))
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
            cFunctionSymbolName(744))
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
            cFunctionSymbolName(745))
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
            cFunctionSymbolName(746))
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
            cFunctionSymbolName(749))
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
            cFunctionSymbolName(750))
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
            cFunctionSymbolName(752))
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
            cFunctionSymbolName(753))
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
// setCursor(Qt::CursorShape arg__1)
  setCursor(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(757))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1);
  }

//tag=1035
  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setCursor(Qt::CursorShape arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setCursor(arg__1);
  }
//tag=1024

//tag=1027
// setFixedHeight(int arg__1)
  setFixedHeight(int arg__1) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(758))
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
            cFunctionSymbolName(759))
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
            cFunctionSymbolName(760))
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
            cFunctionSymbolName(761))
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
            cFunctionSymbolName(762))
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
            cFunctionSymbolName(763))
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
            cFunctionSymbolName(764))
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
            cFunctionSymbolName(765))
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
            cFunctionSymbolName(766))
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
            cFunctionSymbolName(768))
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
            cFunctionSymbolName(769))
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
            cFunctionSymbolName(770))
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
            cFunctionSymbolName(771))
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
            cFunctionSymbolName(772))
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
            cFunctionSymbolName(773))
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
            cFunctionSymbolName(774))
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
            cFunctionSymbolName(775))
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
            cFunctionSymbolName(776))
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
            cFunctionSymbolName(777))
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
            cFunctionSymbolName(779))
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
            cFunctionSymbolName(780))
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
      case 704:
        return "c_KDDockWidgets__View__activateWindow";
      case 708:
        return "c_KDDockWidgets__View__close";
      case 711:
        return "c_KDDockWidgets__View__createPlatformWindow";
      case 715:
        return "c_KDDockWidgets__View__free_impl";
      case 717:
        return "c_KDDockWidgets__View__geometry";
      case 719:
        return "c_KDDockWidgets__View__grabMouse";
      case 722:
        return "c_KDDockWidgets__View__hasFocus";
      case 724:
        return "c_KDDockWidgets__View__hide";
      case 727:
        return "c_KDDockWidgets__View__init";
      case 728:
        return "c_KDDockWidgets__View__isActiveWindow";
      case 729:
        return "c_KDDockWidgets__View__isMaximized";
      case 730:
        return "c_KDDockWidgets__View__isMinimized";
      case 731:
        return "c_KDDockWidgets__View__isNull";
      case 732:
        return "c_KDDockWidgets__View__isRootView";
      case 733:
        return "c_KDDockWidgets__View__isVisible";
      case 734:
        return "c_KDDockWidgets__View__mapFromGlobal_QPoint";
      case 735:
        return "c_KDDockWidgets__View__mapTo_View_QPoint";
      case 736:
        return "c_KDDockWidgets__View__mapToGlobal_QPoint";
      case 737:
        return "c_KDDockWidgets__View__maxSizeHint";
      case 738:
        return "c_KDDockWidgets__View__maximumSize";
      case 739:
        return "c_KDDockWidgets__View__minSize";
      case 740:
        return "c_KDDockWidgets__View__minimumHeight";
      case 741:
        return "c_KDDockWidgets__View__minimumWidth";
      case 743:
        return "c_KDDockWidgets__View__move_int_int";
      case 744:
        return "c_KDDockWidgets__View__normalGeometry";
      case 745:
        return "c_KDDockWidgets__View__objectName";
      case 746:
        return "c_KDDockWidgets__View__onResize_QSize";
      case 749:
        return "c_KDDockWidgets__View__raise";
      case 750:
        return "c_KDDockWidgets__View__raiseAndActivate";
      case 752:
        return "c_KDDockWidgets__View__releaseKeyboard";
      case 753:
        return "c_KDDockWidgets__View__releaseMouse";
      case 757:
        return "c_KDDockWidgets__View__setCursor_CursorShape";
      case 758:
        return "c_KDDockWidgets__View__setFixedHeight_int";
      case 759:
        return "c_KDDockWidgets__View__setFixedWidth_int";
      case 760:
        return "c_KDDockWidgets__View__setGeometry_QRect";
      case 761:
        return "c_KDDockWidgets__View__setHeight_int";
      case 762:
        return "c_KDDockWidgets__View__setMaximumSize_QSize";
      case 763:
        return "c_KDDockWidgets__View__setMinimumSize_QSize";
      case 764:
        return "c_KDDockWidgets__View__setMouseTracking_bool";
      case 765:
        return "c_KDDockWidgets__View__setObjectName_QString";
      case 766:
        return "c_KDDockWidgets__View__setParent_View";
      case 768:
        return "c_KDDockWidgets__View__setSize_int_int";
      case 769:
        return "c_KDDockWidgets__View__setVisible_bool";
      case 770:
        return "c_KDDockWidgets__View__setWidth_int";
      case 771:
        return "c_KDDockWidgets__View__setWindowOpacity_double";
      case 772:
        return "c_KDDockWidgets__View__setWindowTitle_QString";
      case 773:
        return "c_KDDockWidgets__View__setZOrder_int";
      case 774:
        return "c_KDDockWidgets__View__show";
      case 775:
        return "c_KDDockWidgets__View__showMaximized";
      case 776:
        return "c_KDDockWidgets__View__showMinimized";
      case 777:
        return "c_KDDockWidgets__View__showNormal";
      case 779:
        return "c_KDDockWidgets__View__sizeHint";
      case 780:
        return "c_KDDockWidgets__View__update";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 704:
        return "activateWindow";
      case 708:
        return "close";
      case 711:
        return "createPlatformWindow";
      case 715:
        return "free_impl";
      case 717:
        return "geometry";
      case 719:
        return "grabMouse";
      case 722:
        return "hasFocus";
      case 724:
        return "hide";
      case 727:
        return "init";
      case 728:
        return "isActiveWindow";
      case 729:
        return "isMaximized";
      case 730:
        return "isMinimized";
      case 731:
        return "isNull";
      case 732:
        return "isRootView";
      case 733:
        return "isVisible";
      case 734:
        return "mapFromGlobal";
      case 735:
        return "mapTo";
      case 736:
        return "mapToGlobal";
      case 737:
        return "maxSizeHint";
      case 738:
        return "maximumSize";
      case 739:
        return "minSize";
      case 740:
        return "minimumHeight";
      case 741:
        return "minimumWidth";
      case 743:
        return "move_2";
      case 744:
        return "normalGeometry";
      case 745:
        return "objectName";
      case 746:
        return "onResize";
      case 749:
        return "raise";
      case 750:
        return "raiseAndActivate";
      case 752:
        return "releaseKeyboard";
      case 753:
        return "releaseMouse";
      case 757:
        return "setCursor";
      case 758:
        return "setFixedHeight";
      case 759:
        return "setFixedWidth";
      case 760:
        return "setGeometry";
      case 761:
        return "setHeight";
      case 762:
        return "setMaximumSize";
      case 763:
        return "setMinimumSize";
      case 764:
        return "setMouseTracking";
      case 765:
        return "setObjectName";
      case 766:
        return "setParent";
      case 768:
        return "setSize_2";
      case 769:
        return "setVisible";
      case 770:
        return "setWidth";
      case 771:
        return "setWindowOpacity";
      case 772:
        return "setWindowTitle";
      case 773:
        return "setZOrder";
      case 774:
        return "show";
      case 775:
        return "showMaximized";
      case 776:
        return "showMinimized";
      case 777:
        return "showNormal";
      case 779:
        return "sizeHint";
      case 780:
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
    final callback704 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback704, 704);
    const callbackExcept708 = 0;
//tag=1021
    final callback708 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.close_calledFromC, callbackExcept708);
    registerCallback(thisCpp, callback708, 708);
//tag=1021
    final callback711 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback711, 711);
//tag=1021
    final callback715 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.free_impl_calledFromC);
    registerCallback(thisCpp, callback715, 715);
//tag=1021
    final callback717 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.geometry_calledFromC);
    registerCallback(thisCpp, callback717, 717);
//tag=1021
    final callback719 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback719, 719);
    const callbackExcept722 = 0;
//tag=1021
    final callback722 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.hasFocus_calledFromC, callbackExcept722);
    registerCallback(thisCpp, callback722, 722);
//tag=1021
    final callback724 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.hide_calledFromC);
    registerCallback(thisCpp, callback724, 724);
//tag=1021
    final callback727 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.init_calledFromC);
    registerCallback(thisCpp, callback727, 727);
    const callbackExcept728 = 0;
//tag=1021
    final callback728 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isActiveWindow_calledFromC, callbackExcept728);
    registerCallback(thisCpp, callback728, 728);
    const callbackExcept729 = 0;
//tag=1021
    final callback729 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isMaximized_calledFromC, callbackExcept729);
    registerCallback(thisCpp, callback729, 729);
    const callbackExcept730 = 0;
//tag=1021
    final callback730 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isMinimized_calledFromC, callbackExcept730);
    registerCallback(thisCpp, callback730, 730);
    const callbackExcept731 = 0;
//tag=1021
    final callback731 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept731);
    registerCallback(thisCpp, callback731, 731);
    const callbackExcept732 = 0;
//tag=1021
    final callback732 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isRootView_calledFromC, callbackExcept732);
    registerCallback(thisCpp, callback732, 732);
    const callbackExcept733 = 0;
//tag=1021
    final callback733 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isVisible_calledFromC, callbackExcept733);
    registerCallback(thisCpp, callback733, 733);
//tag=1021
    final callback734 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback734, 734);
//tag=1021
    final callback735 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View.mapTo_calledFromC);
    registerCallback(thisCpp, callback735, 735);
//tag=1021
    final callback736 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback736, 736);
//tag=1021
    final callback737 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback737, 737);
//tag=1021
    final callback738 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.maximumSize_calledFromC);
    registerCallback(thisCpp, callback738, 738);
//tag=1021
    final callback739 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.minSize_calledFromC);
    registerCallback(thisCpp, callback739, 739);
    const callbackExcept740 = 0;
//tag=1021
    final callback740 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept740);
    registerCallback(thisCpp, callback740, 740);
    const callbackExcept741 = 0;
//tag=1021
    final callback741 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept741);
    registerCallback(thisCpp, callback741, 741);
//tag=1021
    final callback743 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View.move_2_calledFromC);
    registerCallback(thisCpp, callback743, 743);
//tag=1021
    final callback744 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback744, 744);
//tag=1021
    final callback745 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.objectName_calledFromC);
    registerCallback(thisCpp, callback745, 745);
    const callbackExcept746 = 0;
//tag=1021
    final callback746 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            View.onResize_calledFromC, callbackExcept746);
    registerCallback(thisCpp, callback746, 746);
//tag=1021
    final callback749 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.raise_calledFromC);
    registerCallback(thisCpp, callback749, 749);
//tag=1021
    final callback750 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback750, 750);
//tag=1021
    final callback752 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback752, 752);
//tag=1021
    final callback753 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback753, 753);
//tag=1021
    final callback757 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setCursor_calledFromC);
    registerCallback(thisCpp, callback757, 757);
//tag=1021
    final callback758 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback758, 758);
//tag=1021
    final callback759 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback759, 759);
//tag=1021
    final callback760 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback760, 760);
//tag=1021
    final callback761 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setHeight_calledFromC);
    registerCallback(thisCpp, callback761, 761);
//tag=1021
    final callback762 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback762, 762);
//tag=1021
    final callback763 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback763, 763);
//tag=1021
    final callback764 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback764, 764);
//tag=1021
    final callback765 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback765, 765);
//tag=1021
    final callback766 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setParent_calledFromC);
    registerCallback(thisCpp, callback766, 766);
//tag=1021
    final callback768 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback768, 768);
//tag=1021
    final callback769 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View.setVisible_calledFromC);
    registerCallback(thisCpp, callback769, 769);
//tag=1021
    final callback770 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setWidth_calledFromC);
    registerCallback(thisCpp, callback770, 770);
//tag=1021
    final callback771 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback771, 771);
//tag=1021
    final callback772 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback772, 772);
//tag=1021
    final callback773 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback773, 773);
//tag=1021
    final callback774 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.show_calledFromC);
    registerCallback(thisCpp, callback774, 774);
//tag=1021
    final callback775 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback775, 775);
//tag=1021
    final callback776 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback776, 776);
//tag=1021
    final callback777 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.showNormal_calledFromC);
    registerCallback(thisCpp, callback777, 777);
//tag=1021
    final callback779 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback779, 779);
//tag=1021
    final callback780 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.update_calledFromC);
    registerCallback(thisCpp, callback780, 780);
  }
}
