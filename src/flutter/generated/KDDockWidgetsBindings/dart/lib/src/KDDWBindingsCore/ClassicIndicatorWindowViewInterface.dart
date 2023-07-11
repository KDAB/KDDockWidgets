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
            cFunctionSymbolName(1112))
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
            cFunctionSymbolName(1113))
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
            cFunctionSymbolName(1114))
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
            cFunctionSymbolName(1115))
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
            cFunctionSymbolName(1116))
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
            cFunctionSymbolName(1117))
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
            cFunctionSymbolName(1118))
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
            cFunctionSymbolName(1119))
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
            cFunctionSymbolName(1120))
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
            cFunctionSymbolName(1121))
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
      case 1112:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__hover_Point";
      case 1113:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__isWindow";
      case 1114:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__posForIndicator_DropLocation";
      case 1115:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__raise";
      case 1116:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__resize_Size";
      case 1117:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setGeometry_Rect";
      case 1118:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setObjectName_QString";
      case 1119:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__setVisible_bool";
      case 1120:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__updateIndicatorVisibility";
      case 1121:
        return "c_KDDockWidgets__Core__ClassicIndicatorWindowViewInterface__updatePositions";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1112:
        return "hover";
      case 1113:
        return "isWindow";
      case 1114:
        return "posForIndicator";
      case 1115:
        return "raise";
      case 1116:
        return "resize";
      case 1117:
        return "setGeometry";
      case 1118:
        return "setObjectName";
      case 1119:
        return "setVisible";
      case 1120:
        return "updateIndicatorVisibility";
      case 1121:
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
    const callbackExcept1112 = 0;
    final callback1112 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.hover_calledFromC,
            callbackExcept1112);
    registerCallback(thisCpp, callback1112, 1112);
    const callbackExcept1113 = 0;
    final callback1113 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore
            .ClassicIndicatorWindowViewInterface.isWindow_calledFromC,
        callbackExcept1113);
    registerCallback(thisCpp, callback1113, 1113);
    final callback1114 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.ClassicIndicatorWindowViewInterface
                .posForIndicator_calledFromC);
    registerCallback(thisCpp, callback1114, 1114);
    final callback1115 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.ClassicIndicatorWindowViewInterface.raise_calledFromC);
    registerCallback(thisCpp, callback1115, 1115);
    final callback1116 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.resize_calledFromC);
    registerCallback(thisCpp, callback1116, 1116);
    final callback1117 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.setGeometry_calledFromC);
    registerCallback(thisCpp, callback1117, 1117);
    final callback1118 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.setObjectName_calledFromC);
    registerCallback(thisCpp, callback1118, 1118);
    final callback1119 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsCore
                .ClassicIndicatorWindowViewInterface.setVisible_calledFromC);
    registerCallback(thisCpp, callback1119, 1119);
    final callback1120 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.ClassicIndicatorWindowViewInterface
            .updateIndicatorVisibility_calledFromC);
    registerCallback(thisCpp, callback1120, 1120);
    final callback1121 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore
            .ClassicIndicatorWindowViewInterface.updatePositions_calledFromC);
    registerCallback(thisCpp, callback1121, 1121);
  }
}
