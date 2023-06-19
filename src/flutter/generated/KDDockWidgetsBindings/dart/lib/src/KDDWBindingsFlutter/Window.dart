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
            cFunctionSymbolName(585))
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
            cFunctionSymbolName(586))
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
            cFunctionSymbolName(587))
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
            cFunctionSymbolName(588))
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
            cFunctionSymbolName(590))
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
            cFunctionSymbolName(591))
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
            cFunctionSymbolName(592))
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
            cFunctionSymbolName(593))
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
            cFunctionSymbolName(594))
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
            cFunctionSymbolName(595))
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
            cFunctionSymbolName(596))
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
            cFunctionSymbolName(597))
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
            cFunctionSymbolName(598))
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
            cFunctionSymbolName(599))
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
            cFunctionSymbolName(600))
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
            cFunctionSymbolName(601))
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
      case 585:
        return "c_KDDockWidgets__flutter__Window__destroy";
      case 586:
        return "c_KDDockWidgets__flutter__Window__frameGeometry";
      case 587:
        return "c_KDDockWidgets__flutter__Window__fromNativePixels_QPoint";
      case 588:
        return "c_KDDockWidgets__flutter__Window__geometry";
      case 590:
        return "c_KDDockWidgets__flutter__Window__isActive";
      case 591:
        return "c_KDDockWidgets__flutter__Window__isFullScreen";
      case 592:
        return "c_KDDockWidgets__flutter__Window__isVisible";
      case 593:
        return "c_KDDockWidgets__flutter__Window__mapFromGlobal_QPoint";
      case 594:
        return "c_KDDockWidgets__flutter__Window__mapToGlobal_QPoint";
      case 595:
        return "c_KDDockWidgets__flutter__Window__maxSize";
      case 596:
        return "c_KDDockWidgets__flutter__Window__minSize";
      case 597:
        return "c_KDDockWidgets__flutter__Window__resize_int_int";
      case 598:
        return "c_KDDockWidgets__flutter__Window__setFramePosition_QPoint";
      case 599:
        return "c_KDDockWidgets__flutter__Window__setGeometry_QRect";
      case 600:
        return "c_KDDockWidgets__flutter__Window__setVisible_bool";
      case 601:
        return "c_KDDockWidgets__flutter__Window__supportsHonouringLayoutMinSize";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 585:
        return "destroy";
      case 586:
        return "frameGeometry";
      case 587:
        return "fromNativePixels";
      case 588:
        return "geometry";
      case 590:
        return "isActive";
      case 591:
        return "isFullScreen";
      case 592:
        return "isVisible";
      case 593:
        return "mapFromGlobal";
      case 594:
        return "mapToGlobal";
      case 595:
        return "maxSize";
      case 596:
        return "minSize";
      case 597:
        return "resize";
      case 598:
        return "setFramePosition";
      case 599:
        return "setGeometry";
      case 600:
        return "setVisible";
      case 601:
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
    final callback585 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.destroy_calledFromC);
    registerCallback(thisCpp, callback585, 585);
    final callback586 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.frameGeometry_calledFromC);
    registerCallback(thisCpp, callback586, 586);
    final callback587 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.fromNativePixels_calledFromC);
    registerCallback(thisCpp, callback587, 587);
    final callback588 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.geometry_calledFromC);
    registerCallback(thisCpp, callback588, 588);
    const callbackExcept590 = 0;
    final callback590 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.isActive_calledFromC, callbackExcept590);
    registerCallback(thisCpp, callback590, 590);
    const callbackExcept591 = 0;
    final callback591 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.isFullScreen_calledFromC, callbackExcept591);
    registerCallback(thisCpp, callback591, 591);
    const callbackExcept592 = 0;
    final callback592 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.isVisible_calledFromC, callbackExcept592);
    registerCallback(thisCpp, callback592, 592);
    final callback593 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback593, 593);
    final callback594 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback594, 594);
    final callback595 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.maxSize_calledFromC);
    registerCallback(thisCpp, callback595, 595);
    final callback596 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.minSize_calledFromC);
    registerCallback(thisCpp, callback596, 596);
    final callback597 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Window.resize_calledFromC);
    registerCallback(thisCpp, callback597, 597);
    final callback598 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.setFramePosition_calledFromC);
    registerCallback(thisCpp, callback598, 598);
    final callback599 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Window.setGeometry_calledFromC);
    registerCallback(thisCpp, callback599, 599);
    final callback600 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.Window.setVisible_calledFromC);
    registerCallback(thisCpp, callback600, 600);
    const callbackExcept601 = 0;
    final callback601 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Window.supportsHonouringLayoutMinSize_calledFromC,
        callbackExcept601);
    registerCallback(thisCpp, callback601, 601);
  }
}
