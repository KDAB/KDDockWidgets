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
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class ClassicIndicators extends DropIndicatorOverlay {
  ClassicIndicators.fromCppPointer(var cppPointer,
      [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  ClassicIndicators.init() : super.init() {}
  factory ClassicIndicators.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as ClassicIndicators;
    }
    return ClassicIndicators.fromCppPointer(cppPointer, needsAutoDelete);
  } //ClassicIndicators(KDDockWidgets::Core::DropArea * dropArea)
  ClassicIndicators(DropArea? dropArea) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__constructor_DropArea')
        .asFunction();
    thisCpp = func(dropArea == null ? ffi.nullptr : dropArea.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static int dropIndicatorVisible_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.dropIndicatorVisible(arg__1);
    return result ? 1 : 0;
  } // geometryForRubberband(QRect localRect) const

  QRect geometryForRubberband(QRect localRect) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__geometryForRubberband_QRect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, localRect == null ? ffi.nullptr : localRect.thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static int hover_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::hover_impl(QPoint globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover_impl(QPoint.fromCppPointer(globalPos));
    return result;
  } // indicatorsVisibleChanged()

  indicatorsVisibleChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__indicatorsVisibleChanged')
        .asFunction();
    func(thisCpp);
  }

  static void onHoveredFrameChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::onHoveredFrameChanged(KDDockWidgets::Core::Group * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onHoveredFrameChanged(Group.fromCppPointer(arg__1));
  } // onResize(QSize newSize)

  bool onResize(QSize newSize) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__onResize_QSize')
        .asFunction();
    return func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp) != 0;
  }

  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  } // raiseIndicators()

  raiseIndicators() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__raiseIndicators')
        .asFunction();
    func(thisCpp);
  } // rubberBandIsTopLevel() const

  bool rubberBandIsTopLevel() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__rubberBandIsTopLevel')
        .asFunction();
    return func(thisCpp) != 0;
  } // setDropLocation(KDDockWidgets::DropLocation arg__1)

  setDropLocation(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__setDropLocation_DropLocation')
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__ClassicIndicators__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

  static void updateVisibility_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::updateVisibility()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updateVisibility();
  } // updateWindowPosition()

  updateWindowPosition() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__updateWindowPosition')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 1586:
        return "c_KDDockWidgets__Core__ClassicIndicators__dropIndicatorVisible_DropLocation";
      case 1590:
        return "c_KDDockWidgets__Core__ClassicIndicators__hover_impl_QPoint";
      case 1602:
        return "c_KDDockWidgets__Core__ClassicIndicators__onHoveredFrameChanged_Group";
      case 1605:
        return "c_KDDockWidgets__Core__ClassicIndicators__posForIndicator_DropLocation";
      case 871:
        return "c_KDDockWidgets__Core__ClassicIndicators__setParentView_impl_View";
      case 1618:
        return "c_KDDockWidgets__Core__ClassicIndicators__updateVisibility";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1586:
        return "dropIndicatorVisible";
      case 1590:
        return "hover_impl";
      case 1602:
        return "onHoveredFrameChanged";
      case 1605:
        return "posForIndicator";
      case 871:
        return "setParentView_impl";
      case 1618:
        return "updateVisibility";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__ClassicIndicators__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept1586 = 0;
    final callback1586 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_FFI>(
            DropIndicatorOverlay.dropIndicatorVisible_calledFromC,
            callbackExcept1586);
    registerCallback(thisCpp, callback1586, 1586);
    const callbackExcept1590 = 0;
    final callback1590 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            ClassicIndicators.hover_impl_calledFromC, callbackExcept1590);
    registerCallback(thisCpp, callback1590, 1590);
    final callback1602 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            DropIndicatorOverlay.onHoveredFrameChanged_calledFromC);
    registerCallback(thisCpp, callback1602, 1602);
    final callback1605 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            ClassicIndicators.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback1605, 1605);
    final callback871 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback871, 871);
    final callback1618 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicators.updateVisibility_calledFromC);
    registerCallback(thisCpp, callback1618, 1618);
  }
}
