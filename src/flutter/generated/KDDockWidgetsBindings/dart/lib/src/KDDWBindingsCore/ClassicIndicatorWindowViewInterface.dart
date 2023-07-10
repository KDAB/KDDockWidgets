/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import '../TypeHelpers.dart';
import '../../Bindings.dart';
import '../../Bindings_KDDWBindingsCore.dart' as KDDWBindingsCore;
import '../../Bindings_KDDWBindingsFlutter.dart' as KDDWBindingsFlutter;
import '../../LibraryLoader.dart';

var _dylib = Library.instance().dylib;
final _finalizerFunc =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class ClassicIndicatorWindowViewInterface implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr =
      Map<int, ClassicIndicatorWindowViewInterface>();
  var _thisCpp = null;
  bool _needsAutoDelete = false;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete) _finalizer.attach(this, ptrvoid);
  }

  static bool isCached(var cppPointer) {
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory ClassicIndicatorWindowViewInterface.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
            ClassicIndicatorWindowViewInterface.fromCppPointer(
                cppPointer, needsAutoDelete))
        as ClassicIndicatorWindowViewInterface;
  }
  ClassicIndicatorWindowViewInterface.fromCppPointer(var cppPointer,
      [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  ClassicIndicatorWindowViewInterface.init() {} //ClassicIndicatorWindowViewInterface()
  ClassicIndicatorWindowViewInterface() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__constructor')
        .asFunction();
    thisCpp = func();
    KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // hover(KDDockWidgets::Point arg__1)
  int hover(Point arg__1) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1456))
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static int hover_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::hover(KDDockWidgets::Point arg__1)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover(Point.fromCppPointer(arg__1));
    return result;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1457))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // posForIndicator(KDDockWidgets::DropLocation arg__1) const

  Point posForIndicator(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1458))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  } // raise()

  raise() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1459))
        .asFunction();
    func(thisCpp);
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  } // resize(KDDockWidgets::Size arg__1)

  resize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1460))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void resize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::resize(KDDockWidgets::Size arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.resize(Size.fromCppPointer(arg__1));
  } // setGeometry(KDDockWidgets::Rect arg__1)

  setGeometry(Rect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1461))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setGeometry(KDDockWidgets::Rect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(Rect.fromCppPointer(arg__1));
  } // setObjectName(const QString & arg__1)

  setObjectName(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1462))
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setObjectName(const QString & arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(arg__1).toDartString());
  } // setVisible(bool arg__1)

  setVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(1463))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(arg__1 != 0);
  } // updateIndicatorVisibility()

  updateIndicatorVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1464))
        .asFunction();
    func(thisCpp);
  }

  static void updateIndicatorVisibility_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::updateIndicatorVisibility()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updateIndicatorVisibility();
  } // updatePositions()

  updatePositions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1465))
        .asFunction();
    func(thisCpp);
  }

  static void updatePositions_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::updatePositions()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updatePositions();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 1456:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__hover_Point";
      case 1457:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__isWindow";
      case 1458:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation";
      case 1459:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__raise";
      case 1460:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__resize_Size";
      case 1461:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setGeometry_Rect";
      case 1462:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setObjectName_QString";
      case 1463:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setVisible_bool";
      case 1464:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__updateIndicatorVisibility";
      case 1465:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__updatePositions";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1456:
        return "hover";
      case 1457:
        return "isWindow";
      case 1458:
        return "posForIndicator";
      case 1459:
        return "raise";
      case 1460:
        return "resize";
      case 1461:
        return "setGeometry";
      case 1462:
        return "setObjectName";
      case 1463:
        return "setVisible";
      case 1464:
        return "updateIndicatorVisibility";
      case 1465:
        return "updatePositions";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept1456 = 0;
    final callback1456 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.hover_calledFromC,
            callbackExcept1456);
    registerCallback(thisCpp, callback1456, 1456);
    const callbackExcept1457 = 0;
    final callback1457 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore
            .ClassicIndicatorWindowViewInterface.isWindow_calledFromC,
        callbackExcept1457);
    registerCallback(thisCpp, callback1457, 1457);
    final callback1458 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.ClassicIndicatorWindowViewInterface
                .posForIndicator_calledFromC);
    registerCallback(thisCpp, callback1458, 1458);
    final callback1459 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.ClassicIndicatorWindowViewInterface.raise_calledFromC);
    registerCallback(thisCpp, callback1459, 1459);
    final callback1460 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.resize_calledFromC);
    registerCallback(thisCpp, callback1460, 1460);
    final callback1461 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.setGeometry_calledFromC);
    registerCallback(thisCpp, callback1461, 1461);
    final callback1462 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.setObjectName_calledFromC);
    registerCallback(thisCpp, callback1462, 1462);
    final callback1463 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.setVisible_calledFromC);
    registerCallback(thisCpp, callback1463, 1463);
    final callback1464 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.ClassicIndicatorWindowViewInterface
            .updateIndicatorVisibility_calledFromC);
    registerCallback(thisCpp, callback1464, 1464);
    final callback1465 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore
            .ClassicIndicatorWindowViewInterface.updatePositions_calledFromC);
    registerCallback(thisCpp, callback1465, 1465);
  }
}
