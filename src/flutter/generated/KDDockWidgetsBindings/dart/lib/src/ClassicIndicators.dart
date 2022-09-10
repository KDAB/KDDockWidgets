/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
  } //ClassicIndicators(KDDockWidgets::Controllers::DropArea * dropArea)
  ClassicIndicators(DropArea? dropArea) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__constructor_DropArea')
        .asFunction();
    thisCpp = func(dropArea == null ? ffi.nullptr : dropArea.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
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
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // geometryForRubberband(QRect localRect) const

  QRect geometryForRubberband(QRect localRect) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__geometryForRubberband_QRect')
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
            'c_KDDockWidgets__Controllers__ClassicIndicators__indicatorsVisibleChanged')
        .asFunction();
    func(thisCpp);
  }

  static void onHoveredFrameChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::onHoveredFrameChanged(KDDockWidgets::Controllers::Group * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onHoveredFrameChanged(Group.fromCppPointer(arg__1));
  } // onResize(QSize newSize)

  bool onResize(QSize newSize) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__onResize_QSize')
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
            'c_KDDockWidgets__Controllers__ClassicIndicators__raiseIndicators')
        .asFunction();
    func(thisCpp);
  } // rubberBandIsTopLevel() const

  bool rubberBandIsTopLevel() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__rubberBandIsTopLevel')
        .asFunction();
    return func(thisCpp) != 0;
  } // setDropLocation(KDDockWidgets::DropLocation arg__1)

  setDropLocation(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__setDropLocation_DropLocation')
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ClassicIndicators;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ClassicIndicators::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__ClassicIndicators__tr_char_char_int')
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
            'c_KDDockWidgets__Controllers__ClassicIndicators__updateWindowPosition')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__customEvent_QEvent";
      case 1598:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__dropIndicatorVisible_DropLocation";
      case 306:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__eventFilter_QObject_QEvent";
      case 1602:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__hover_impl_QPoint";
      case 1614:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__onHoveredFrameChanged_Group";
      case 1617:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__posForIndicator_DropLocation";
      case 890:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__setParentView_impl_View";
      case 1630:
        return "c_KDDockWidgets__Controllers__ClassicIndicators__updateVisibility";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 1598:
        return "dropIndicatorVisible";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 1602:
        return "hover_impl";
      case 1614:
        return "onHoveredFrameChanged";
      case 1617:
        return "posForIndicator";
      case 890:
        return "setParentView_impl";
      case 1630:
        return "updateVisibility";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__ClassicIndicators__registerVirtualMethodCallback')
        .asFunction();
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    const callbackExcept1598 = 0;
    final callback1598 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_FFI>(
            DropIndicatorOverlay.dropIndicatorVisible_calledFromC,
            callbackExcept1598);
    registerCallback(thisCpp, callback1598, 1598);
    const callbackExcept306 = 0;
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
    const callbackExcept307 = 0;
    final callback307 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept307);
    registerCallback(thisCpp, callback307, 307);
    const callbackExcept1602 = 0;
    final callback1602 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            ClassicIndicators.hover_impl_calledFromC, callbackExcept1602);
    registerCallback(thisCpp, callback1602, 1602);
    final callback1614 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            DropIndicatorOverlay.onHoveredFrameChanged_calledFromC);
    registerCallback(thisCpp, callback1614, 1614);
    final callback1617 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            ClassicIndicators.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback1617, 1617);
    final callback890 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback890, 890);
    final callback1630 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        ClassicIndicators.updateVisibility_calledFromC);
    registerCallback(thisCpp, callback1630, 1630);
  }
}
