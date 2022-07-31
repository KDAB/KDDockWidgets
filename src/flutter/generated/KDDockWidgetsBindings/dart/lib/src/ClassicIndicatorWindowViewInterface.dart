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
final _finalizer = _dylib.lookup<
        ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
    'c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface_Finalizer');

class ClassicIndicatorWindowViewInterface {
//tag=1060
  static var s_dartInstanceByCppPtr =
      Map<int, ClassicIndicatorWindowViewInterface>();
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
  factory ClassicIndicatorWindowViewInterface.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
            ClassicIndicatorWindowViewInterface.fromCppPointer(
                cppPointer, needsAutoDelete))
        as ClassicIndicatorWindowViewInterface;
  }
  ClassicIndicatorWindowViewInterface.fromCppPointer(var cppPointer,
      [this._needsAutoDelete = false]) {
//tag=1024
    thisCpp = cppPointer;
  }
//tag=1025
  ClassicIndicatorWindowViewInterface.init() {}
//tag=1023
//ClassicIndicatorWindowViewInterface()
  ClassicIndicatorWindowViewInterface() {
//tag=1075
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__constructor')
        .asFunction();
    thisCpp = func();
    ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// hover(QPoint arg__1)
  int hover(QPoint arg__1) {
//tag=1028
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(592))
        .asFunction();
//tag=1031
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static int hover_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::hover(QPoint arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.hover(QPoint.fromCppPointer(arg__1));
    return result;
  }
//tag=1024

//tag=1027
// isWindow() const
  bool isWindow() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(593))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// posForIndicator(KDDockWidgets::DropLocation arg__1) const
  QPoint posForIndicator(int arg__1) {
//tag=1028
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(594))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// raise()
  raise() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(595))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::raise()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.raise();
  }
//tag=1024

//tag=1027
// resize(QSize arg__1)
  resize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(596))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static void resize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::resize(QSize arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.resize(QSize.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1027
// setGeometry(QRect arg__1)
  setGeometry(QRect arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(597))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1027
// setObjectName(const QString & arg__1)
  setObjectName(String? arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(598))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

//tag=1035
  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setObjectName(const QString & arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setObjectName(QString.fromCppPointer(arg__1).toDartString());
  }
//tag=1024

//tag=1027
// setVisible(bool arg__1)
  setVisible(bool arg__1) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(599))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 ? 1 : 0);
  }

//tag=1035
  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setVisible(arg__1 != 0);
  }
//tag=1024

//tag=1027
// updatePositions()
  updatePositions() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(600))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void updatePositions_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::updatePositions()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.updatePositions();
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 592:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__hover_QPoint";
      case 593:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__isWindow";
      case 594:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation";
      case 595:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__raise";
      case 596:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__resize_QSize";
      case 597:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setGeometry_QRect";
      case 598:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setObjectName_QString";
      case 599:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__setVisible_bool";
      case 600:
        return "c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__updatePositions";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 592:
        return "hover";
      case 593:
        return "isWindow";
      case 594:
        return "posForIndicator";
      case 595:
        return "raise";
      case 596:
        return "resize";
      case 597:
        return "setGeometry";
      case 598:
        return "setObjectName";
      case 599:
        return "setVisible";
      case 600:
        return "updatePositions";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Views__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept592 = 0;
//tag=1021
    final callback592 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.hover_calledFromC,
            callbackExcept592);
    registerCallback(thisCpp, callback592, 592);
    const callbackExcept593 = 0;
//tag=1021
    final callback593 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        ClassicIndicatorWindowViewInterface.isWindow_calledFromC,
        callbackExcept593);
    registerCallback(thisCpp, callback593, 593);
//tag=1021
    final callback594 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            ClassicIndicatorWindowViewInterface.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback594, 594);
//tag=1021
    final callback595 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicatorWindowViewInterface.raise_calledFromC);
    registerCallback(thisCpp, callback595, 595);
//tag=1021
    final callback596 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.resize_calledFromC);
    registerCallback(thisCpp, callback596, 596);
//tag=1021
    final callback597 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.setGeometry_calledFromC);
    registerCallback(thisCpp, callback597, 597);
//tag=1021
    final callback598 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.setObjectName_calledFromC);
    registerCallback(thisCpp, callback598, 598);
//tag=1021
    final callback599 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            ClassicIndicatorWindowViewInterface.setVisible_calledFromC);
    registerCallback(thisCpp, callback599, 599);
//tag=1021
    final callback600 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicatorWindowViewInterface.updatePositions_calledFromC);
    registerCallback(thisCpp, callback600, 600);
  }
}
