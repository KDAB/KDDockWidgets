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

class Separator extends KDDWBindingsCore.Controller {
  Separator.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Separator.init() : super.init() {}
  factory Separator.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.Object.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.Object.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Separator;
    }
    return Separator.fromCppPointer(cppPointer, needsAutoDelete);
  } //Separator(KDDockWidgets::Core::View * host)
  Separator(KDDWBindingsCore.View? host) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__constructor_View')
        .asFunction();
    thisCpp = func(host == null ? ffi.nullptr : host.thisCpp);
    KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // isBeingDragged() const
  bool isBeingDragged() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__isBeingDragged')
        .asFunction();
    return func(thisCpp) != 0;
  }

  static // isResizing()
      bool isResizing() {
    final bool_Func_void func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Separator__isResizing')
        .asFunction();
    return func() != 0;
  } // isVertical() const

  bool isVertical() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__isVertical')
        .asFunction();
    return func(thisCpp) != 0;
  } // move(int p)

  move(int p) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__Separator__move_int')
        .asFunction();
    func(thisCpp, p);
  }

  static // numSeparators()
      int numSeparators() {
    final int_Func_void func = _dylib
        .lookup<ffi.NativeFunction<int_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Separator__numSeparators')
        .asFunction();
    return func();
  } // onMouseDoubleClick()

  onMouseDoubleClick() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__onMouseDoubleClick')
        .asFunction();
    func(thisCpp);
  } // onMouseMove(KDDockWidgets::Point pos)

  onMouseMove(Point pos) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__onMouseMove_Point')
        .asFunction();
    func(thisCpp, pos == null ? ffi.nullptr : pos.thisCpp);
  } // onMousePress()

  onMousePress() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__onMousePress')
        .asFunction();
    func(thisCpp);
  } // onMouseReleased()

  onMouseReleased() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__onMouseReleased')
        .asFunction();
    func(thisCpp);
  } // position() const

  int position() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__position')
        .asFunction();
    return func(thisCpp);
  } // setGeometry(KDDockWidgets::Rect r)

  setGeometry(Rect r) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__setGeometry_Rect')
        .asFunction();
    func(thisCpp, r == null ? ffi.nullptr : r.thisCpp);
  } // setGeometry(int pos, int pos2, int length)

  setGeometry_2(int pos, int pos2, int length) {
    final void_Func_voidstar_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__Separator__setGeometry_int_int_int')
        .asFunction();
    func(thisCpp, pos, pos2, length);
  } // setLazyPosition(int arg__1)

  setLazyPosition(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__Separator__setLazyPosition_int')
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Object.s_dartInstanceByCppPtr[thisCpp.address] as Separator;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Separator::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  } // usesLazyResize() const

  bool usesLazyResize() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__usesLazyResize')
        .asFunction();
    return func(thisCpp) != 0;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Separator__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 332:
        return "c_KDDockWidgets__Core__Separator__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 332:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__Separator__registerVirtualMethodCallback')
        .asFunction();
    final callback332 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback332, 332);
  }
}
