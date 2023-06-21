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
        'c_KDDockWidgets__flutter__Window_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class Window implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, Window>();
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

  factory Window.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        Window.fromCppPointer(cppPointer, needsAutoDelete)) as Window;
  }
  Window.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  Window.init() {} // destroy()
  destroy() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(501))
        .asFunction();
    func(thisCpp);
  }

  static void destroy_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::destroy()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.destroy();
  } // frameGeometry() const

  QRect frameGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(502))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> frameGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::frameGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.frameGeometry();
    return result.thisCpp;
  } // fromNativePixels(QPoint arg__1) const

  QPoint fromNativePixels(QPoint arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(503))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> fromNativePixels_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::fromNativePixels(QPoint arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.fromNativePixels(QPoint.fromCppPointer(arg__1));
    return result.thisCpp;
  } // geometry() const

  QRect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(504))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  } // isActive() const

  bool isActive() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(506))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isActive_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::isActive() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActive();
    return result ? 1 : 0;
  } // isFullScreen() const

  bool isFullScreen() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(507))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isFullScreen_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::isFullScreen() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isFullScreen();
    return result ? 1 : 0;
  } // isVisible() const

  bool isVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(508))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  } // mapFromGlobal(QPoint globalPos) const

  QPoint mapFromGlobal(QPoint globalPos) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(509))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::mapFromGlobal(QPoint globalPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPos));
    return result.thisCpp;
  } // mapToGlobal(QPoint localPos) const

  QPoint mapToGlobal(QPoint localPos) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(510))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPos) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::mapToGlobal(QPoint localPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPos));
    return result.thisCpp;
  } // maxSize() const

  QSize maxSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(511))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> maxSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::maxSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSize();
    return result.thisCpp;
  } // minSize() const

  QSize minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(512))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  } // resize(int width, int height)

  resize(int width, int height) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(513))
        .asFunction();
    func(thisCpp, width, height);
  }

  static void resize_calledFromC(
      ffi.Pointer<void> thisCpp, int width, int height) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::resize(int width, int height)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.resize(width, height);
  } // setFramePosition(QPoint targetPos)

  setFramePosition(QPoint targetPos) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(514))
        .asFunction();
    func(thisCpp, targetPos == null ? ffi.nullptr : targetPos.thisCpp);
  }

  static void setFramePosition_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> targetPos) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::setFramePosition(QPoint targetPos)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFramePosition(QPoint.fromCppPointer(targetPos));
  } // setGeometry(QRect arg__1)

  setGeometry(QRect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(515))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  } // setVisible(bool arg__1)

  setVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(516))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(arg__1 != 0);
  } // supportsHonouringLayoutMinSize() const

  bool supportsHonouringLayoutMinSize() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(517))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int supportsHonouringLayoutMinSize_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsFlutter.Window.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Window::supportsHonouringLayoutMinSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.supportsHonouringLayoutMinSize();
    return result ? 1 : 0;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Window__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 501:
        return "c_KDDockWidgets__flutter__Window__destroy";
      case 502:
        return "c_KDDockWidgets__flutter__Window__frameGeometry";
      case 503:
        return "c_KDDockWidgets__flutter__Window__fromNativePixels_QPoint";
      case 504:
        return "c_KDDockWidgets__flutter__Window__geometry";
      case 506:
        return "c_KDDockWidgets__flutter__Window__isActive";
      case 507:
        return "c_KDDockWidgets__flutter__Window__isFullScreen";
      case 508:
        return "c_KDDockWidgets__flutter__Window__isVisible";
      case 509:
        return "c_KDDockWidgets__flutter__Window__mapFromGlobal_QPoint";
      case 510:
        return "c_KDDockWidgets__flutter__Window__mapToGlobal_QPoint";
      case 511:
        return "c_KDDockWidgets__flutter__Window__maxSize";
      case 512:
        return "c_KDDockWidgets__flutter__Window__minSize";
      case 513:
        return "c_KDDockWidgets__flutter__Window__resize_int_int";
      case 514:
        return "c_KDDockWidgets__flutter__Window__setFramePosition_QPoint";
      case 515:
        return "c_KDDockWidgets__flutter__Window__setGeometry_QRect";
      case 516:
        return "c_KDDockWidgets__flutter__Window__setVisible_bool";
      case 517:
        return "c_KDDockWidgets__flutter__Window__supportsHonouringLayoutMinSize";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 501:
        return "destroy";
      case 502:
        return "frameGeometry";
      case 503:
        return "fromNativePixels";
      case 504:
        return "geometry";
      case 506:
        return "isActive";
      case 507:
        return "isFullScreen";
      case 508:
        return "isVisible";
      case 509:
        return "mapFromGlobal";
      case 510:
        return "mapToGlobal";
      case 511:
        return "maxSize";
      case 512:
        return "minSize";
      case 513:
        return "resize";
      case 514:
        return "setFramePosition";
      case 515:
        return "setGeometry";
      case 516:
        return "setVisible";
      case 517:
        return "supportsHonouringLayoutMinSize";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__Window__registerVirtualMethodCallback')
        .asFunction();
    final callback501 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.destroy_calledFromC);
    registerCallback(thisCpp, callback501, 501);
    final callback502 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.frameGeometry_calledFromC);
    registerCallback(thisCpp, callback502, 502);
    final callback503 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.fromNativePixels_calledFromC);
    registerCallback(thisCpp, callback503, 503);
    final callback504 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.geometry_calledFromC);
    registerCallback(thisCpp, callback504, 504);
    const callbackExcept506 = 0;
    final callback506 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.isActive_calledFromC, callbackExcept506);
    registerCallback(thisCpp, callback506, 506);
    const callbackExcept507 = 0;
    final callback507 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.isFullScreen_calledFromC, callbackExcept507);
    registerCallback(thisCpp, callback507, 507);
    const callbackExcept508 = 0;
    final callback508 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.isVisible_calledFromC, callbackExcept508);
    registerCallback(thisCpp, callback508, 508);
    final callback509 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback509, 509);
    final callback510 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback510, 510);
    final callback511 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.maxSize_calledFromC);
    registerCallback(thisCpp, callback511, 511);
    final callback512 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.minSize_calledFromC);
    registerCallback(thisCpp, callback512, 512);
    final callback513 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Window.resize_calledFromC);
    registerCallback(thisCpp, callback513, 513);
    final callback514 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.setFramePosition_calledFromC);
    registerCallback(thisCpp, callback514, 514);
    final callback515 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.setGeometry_calledFromC);
    registerCallback(thisCpp, callback515, 515);
    final callback516 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.Window.setVisible_calledFromC);
    registerCallback(thisCpp, callback516, 516);
    const callbackExcept517 = 0;
    final callback517 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.supportsHonouringLayoutMinSize_calledFromC,
        callbackExcept517);
    registerCallback(thisCpp, callback517, 517);
  }
}
