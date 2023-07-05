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

var _dylib = Library.instance().dylib;

class DropIndicatorOverlay extends KDDWBindingsCore.Controller {
  DropIndicatorOverlay.fromCppPointer(var cppPointer,
      [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DropIndicatorOverlay.init() : super.init() {}
  factory DropIndicatorOverlay.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    if (KDDWBindingsCore.Object.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.Object.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DropIndicatorOverlay;
    }
    return DropIndicatorOverlay.fromCppPointer(cppPointer, needsAutoDelete);
  } //DropIndicatorOverlay(KDDockWidgets::Core::DropArea * dropArea)
  DropIndicatorOverlay(KDDWBindingsCore.DropArea? dropArea) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__constructor_DropArea')
        .asFunction();
    thisCpp = func(dropArea == null ? ffi.nullptr : dropArea.thisCpp);
    KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } //DropIndicatorOverlay(KDDockWidgets::Core::DropArea * dropArea, KDDockWidgets::Core::View * view)
  DropIndicatorOverlay.ctor2(
      KDDWBindingsCore.DropArea? dropArea, KDDWBindingsCore.View? view)
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__constructor_DropArea_View')
        .asFunction();
    thisCpp = func(dropArea == null ? ffi.nullptr : dropArea.thisCpp,
        view == null ? ffi.nullptr : view.thisCpp);
    KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // currentDropLocation() const
  int currentDropLocation() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__currentDropLocation')
        .asFunction();
    return func(thisCpp);
  } // dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const

  bool dropIndicatorVisible(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1494))
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  }

  static int dropIndicatorVisible_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::dropIndicatorVisible(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.dropIndicatorVisible(arg__1);
    return result ? 1 : 0;
  } // hover(QPoint globalPos)

  int hover(QPoint globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__hover_QPoint')
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  } // hover_impl(QPoint globalPos)

  int hover_impl(QPoint globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1498))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

  static int hover_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::hover_impl(QPoint globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover_impl(QPoint.fromCppPointer(globalPos));
    return result;
  } // hoveredGroup() const

  KDDWBindingsCore.Group hoveredGroup() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__hoveredGroup')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // hoveredGroupRect() const

  QRect hoveredGroupRect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__hoveredGroupRect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // isHovered() const

  bool isHovered() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__isHovered')
        .asFunction();
    return func(thisCpp) != 0;
  }

  static // multisplitterLocationFor(KDDockWidgets::DropLocation arg__1)
      int multisplitterLocationFor(int arg__1) {
    final int_Func_int func = _dylib
        .lookup<ffi.NativeFunction<int_Func_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__DropIndicatorOverlay__multisplitterLocationFor_DropLocation')
        .asFunction();
    return func(arg__1);
  } // onGroupDestroyed()

  onGroupDestroyed() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__onGroupDestroyed')
        .asFunction();
    func(thisCpp);
  } // onHoveredGroupChanged(KDDockWidgets::Core::Group * arg__1)

  onHoveredGroupChanged(KDDWBindingsCore.Group? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1508))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onHoveredGroupChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::onHoveredGroupChanged(KDDockWidgets::Core::Group * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onHoveredGroupChanged((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.Group.fromCppPointer(arg__1));
  } // posForIndicator(KDDockWidgets::DropLocation arg__1) const

  QPoint posForIndicator(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1510))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  } // removeHover()

  removeHover() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__removeHover')
        .asFunction();
    func(thisCpp);
  } // setCurrentDropLocation(KDDockWidgets::DropLocation arg__1)

  setCurrentDropLocation(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1513))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setCurrentDropLocation_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::setCurrentDropLocation(KDDockWidgets::DropLocation arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCurrentDropLocation(arg__1);
  } // setHoveredGroup(KDDockWidgets::Core::Group * arg__1)

  setHoveredGroup(KDDWBindingsCore.Group? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__setHoveredGroup_Group')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setHoveredGroupRect(QRect arg__1)

  setHoveredGroupRect(QRect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__setHoveredGroupRect_QRect')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  } // setWindowBeingDragged(bool arg__1)

  setWindowBeingDragged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__setWindowBeingDragged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // updateVisibility()

  updateVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1522))
        .asFunction();
    func(thisCpp);
  }

  static void updateVisibility_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as DropIndicatorOverlay;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropIndicatorOverlay::updateVisibility()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updateVisibility();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 1494:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__dropIndicatorVisible_DropLocation";
      case 1498:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__hover_impl_QPoint";
      case 1508:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__onHoveredGroupChanged_Group";
      case 1510:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__posForIndicator_DropLocation";
      case 1513:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__setCurrentDropLocation_DropLocation";
      case 814:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__setParentView_impl_View";
      case 1522:
        return "c_KDDockWidgets__Core__DropIndicatorOverlay__updateVisibility";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1494:
        return "dropIndicatorVisible";
      case 1498:
        return "hover_impl";
      case 1508:
        return "onHoveredGroupChanged";
      case 1510:
        return "posForIndicator";
      case 1513:
        return "setCurrentDropLocation";
      case 814:
        return "setParentView_impl";
      case 1522:
        return "updateVisibility";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__DropIndicatorOverlay__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept1494 = 0;
    final callback1494 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_FFI>(
            DropIndicatorOverlay.dropIndicatorVisible_calledFromC,
            callbackExcept1494);
    registerCallback(thisCpp, callback1494, 1494);
    const callbackExcept1498 = 0;
    final callback1498 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            DropIndicatorOverlay.hover_impl_calledFromC, callbackExcept1498);
    registerCallback(thisCpp, callback1498, 1498);
    final callback1508 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            DropIndicatorOverlay.onHoveredGroupChanged_calledFromC);
    registerCallback(thisCpp, callback1508, 1508);
    final callback1510 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            DropIndicatorOverlay.posForIndicator_calledFromC);
    registerCallback(thisCpp, callback1510, 1510);
    final callback1513 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            DropIndicatorOverlay.setCurrentDropLocation_calledFromC);
    registerCallback(thisCpp, callback1513, 1513);
    final callback814 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback814, 814);
    final callback1522 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        DropIndicatorOverlay.updateVisibility_calledFromC);
    registerCallback(thisCpp, callback1522, 1522);
  }
}
