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

class Layout extends Controller {
//tag=1064
  Layout.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Layout.init() : super.init() {}
//tag=1062
  factory Layout.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Layout;
    }
    return Layout.fromCppPointer(cppPointer, needsAutoDelete);
  }
//tag=1023
//Layout(KDDockWidgets::Type arg__1, KDDockWidgets::View * arg__2)
  Layout(int arg__1, View? arg__2) : super.init() {
//tag=1075
    final voidstar_Func_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__constructor_Type_View')
        .asFunction();
    thisCpp = func(arg__1, arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// asDropArea() const
  DropArea asDropArea() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__asDropArea')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// checkSanity() const
  bool checkSanity() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__checkSanity')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// clearLayout()
  clearLayout() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__clearLayout')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// count() const
  int count() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__count')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1035
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Layout;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Layout::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }
//tag=1024

//tag=1027
// dumpLayout() const
  dumpLayout() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__dumpLayout')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1035
  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Layout;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Layout::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Layout;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Layout::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// isInMainWindow(bool honourNesting) const
  bool isInMainWindow({bool honourNesting = false}) {
//tag=1028
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool')
        .asFunction();
//tag=1029
    return func(thisCpp, honourNesting ? 1 : 0) != 0;
  }
//tag=1024

//tag=1027
// layoutHeight() const
  int layoutHeight() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutHeight')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// layoutMaximumSizeHint() const
  QSize layoutMaximumSizeHint() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// layoutMinimumSize() const
  QSize layoutMinimumSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutMinimumSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// layoutSize() const
  QSize layoutSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// layoutWidth() const
  int layoutWidth() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutWidth')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// onResize(QSize newSize)
  bool onResize(QSize newSize) {
//tag=1028
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__onResize_QSize')
        .asFunction();
//tag=1029
    return func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp) != 0;
  }
//tag=1024

//tag=1027
// placeholderCount() const
  int placeholderCount() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__placeholderCount')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// setLayoutMinimumSize(QSize arg__1)
  setLayoutMinimumSize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// setLayoutSize(QSize arg__1)
  setLayoutSize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1035
  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Layout;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Layout::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  }
//tag=1024

//tag=1027
// updateSizeConstraints()
  updateSizeConstraints() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__updateSizeConstraints')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// viewAboutToBeDeleted()
  viewAboutToBeDeleted() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// visibleCount() const
  int visibleCount() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__visibleCount')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__Layout__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__Layout__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__Layout__eventFilter_QObject_QEvent";
      case 695:
        return "c_KDDockWidgets__Controllers__Layout__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 695:
        return "setParentView_impl";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    const callbackExcept306 = 0;
//tag=1021
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
    const callbackExcept307 = 0;
//tag=1021
    final callback307 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept307);
    registerCallback(thisCpp, callback307, 307);
//tag=1021
    final callback695 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback695, 695);
  }
}
