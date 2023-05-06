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
        'c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface_Finalizer');

class ClassicIndicatorWindowViewInterface {
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
    ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // hover(QPoint arg__1)
  int hover(QPoint arg__1) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1746))
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static int hover_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::hover(QPoint arg__1)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover(QPoint.fromCppPointer(arg__1));
    return result;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1747))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // posForIndicator(KDDockWidgets::DropLocation arg__1) const

  QPoint posForIndicator(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1748))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
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
            cFunctionSymbolName(1749))
        .asFunction();
    func(thisCpp);
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  } // resize(QSize arg__1)

  resize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1750))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void resize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::resize(QSize arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.resize(QSize.fromCppPointer(arg__1));
  } // setGeometry(QRect arg__1)

  setGeometry(QRect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1751))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  } // setObjectName(const QString & arg__1)

  setObjectName(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1752))
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
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
            cFunctionSymbolName(1753))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicatorWindowViewInterface::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(arg__1 != 0);
  } // updatePositions()

  updatePositions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1754))
        .asFunction();
    func(thisCpp);
  }

  static void updatePositions_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = ClassicIndicatorWindowViewInterface
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
      case 1746:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__hover_QPoint";
      case 1747:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__isWindow";
      case 1748:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation";
      case 1749:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__raise";
      case 1750:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__resize_QSize";
      case 1751:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setGeometry_QRect";
      case 1752:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setObjectName_QString";
      case 1753:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setVisible_bool";
      case 1754:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__updatePositions";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1746:
        return "hover";
      case 1747:
        return "isWindow";
      case 1748:
        return "posForIndicator";
      case 1749:
        return "raise";
      case 1750:
        return "resize";
      case 1751:
        return "setGeometry";
      case 1752:
        return "setObjectName";
      case 1753:
        return "setVisible";
      case 1754:
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
    const callbackExcept1746 = 0;
    final callback1746 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.hover_calledFromC,
            callbackExcept1746);
    registerCallback(thisCpp, callback1746, 1746);
    const callbackExcept1747 = 0;
    final callback1747 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        ClassicIndicatorWindowViewInterface.isWindow_calledFromC,
        callbackExcept1747);
    registerCallback(thisCpp, callback1747, 1747);
    final callback1748 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            ClassicIndicatorWindowViewInterface.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback1748, 1748);
    final callback1749 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicatorWindowViewInterface.raise_calledFromC);
    registerCallback(thisCpp, callback1749, 1749);
    final callback1750 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.resize_calledFromC);
    registerCallback(thisCpp, callback1750, 1750);
    final callback1751 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.setGeometry_calledFromC);
    registerCallback(thisCpp, callback1751, 1751);
    final callback1752 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            ClassicIndicatorWindowViewInterface.setObjectName_calledFromC);
    registerCallback(thisCpp, callback1752, 1752);
    final callback1753 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            ClassicIndicatorWindowViewInterface.setVisible_calledFromC);
    registerCallback(thisCpp, callback1753, 1753);
    final callback1754 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicatorWindowViewInterface.updatePositions_calledFromC);
    registerCallback(thisCpp, callback1754, 1754);
  }
}
