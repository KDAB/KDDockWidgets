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

class DropArea extends KDDWBindingsCore.Layout {
  DropArea.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DropArea.init() : super.init() {}
  factory DropArea.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DropArea;
    }
    return DropArea.fromCppPointer(cppPointer, needsAutoDelete);
  } //DropArea(KDDockWidgets::Core::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
  DropArea(KDDWBindingsCore.View? parent, int options,
      {bool isMDIWrapper = false})
      : super.init() {
    final voidstar_Func_voidstar_int_bool func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__DropArea__constructor_View_MainWindowOptions_bool')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp, options,
        isMDIWrapper ? 1 : 0);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // addDockWidget(KDDockWidgets::Core::DockWidget * dw, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
  addDockWidget(KDDWBindingsCore.DockWidget? dw, int location,
      KDDWBindingsCore.DockWidget? relativeTo,
      {required InitialOption initialOption}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__addDockWidget_DockWidget_Location_DockWidget_InitialOption')
        .asFunction();
    func(
        thisCpp,
        dw == null ? ffi.nullptr : dw.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        initialOption == null ? ffi.nullptr : initialOption.thisCpp);
  } // addMultiSplitter(KDDockWidgets::Core::DropArea * splitter, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)

  addMultiSplitter(KDDWBindingsCore.DropArea? splitter, int location,
      {required KDDWBindingsCore.Group? relativeTo,
      required InitialOption option}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption')
        .asFunction();
    func(
        thisCpp,
        splitter == null ? ffi.nullptr : splitter.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        option == null ? ffi.nullptr : option.thisCpp);
  } // addWidget(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo, KDDockWidgets::InitialOption option)

  addWidget(KDDWBindingsCore.View? widget, int location,
      {required KDDWBindingsCore.Group? relativeTo,
      required InitialOption option}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__addWidget_View_Location_Group_InitialOption')
        .asFunction();
    func(
        thisCpp,
        widget == null ? ffi.nullptr : widget.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        option == null ? ffi.nullptr : option.thisCpp);
  } // availableSize() const

  QSize availableSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__availableSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // centralFrame() const

  Item centralFrame() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__centralFrame')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Item.fromCppPointer(result, false);
  } // centralGroup() const

  KDDWBindingsCore.Group centralGroup() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__centralGroup')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // containsDockWidget(KDDockWidgets::Core::DockWidget * arg__1) const

  bool containsDockWidget(KDDWBindingsCore.DockWidget? arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__containsDockWidget_DockWidget')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  }

  static // createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
      KDDWBindingsCore.Group createCentralFrame(int options) {
    final voidstar_Func_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__DropArea__createCentralFrame_MainWindowOptions')
        .asFunction();
    ffi.Pointer<void> result = func(options);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // currentDropLocation() const

  int currentDropLocation() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__currentDropLocation')
        .asFunction();
    return func(thisCpp);
  } // drop(KDDockWidgets::Core::View * droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Core::Group * relativeTo)

  bool drop(KDDWBindingsCore.View? droppedwindow, int location,
      KDDWBindingsCore.Group? relativeTo) {
    final bool_Func_voidstar_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__drop_View_Location_Group')
        .asFunction();
    return func(
            thisCpp,
            droppedwindow == null ? ffi.nullptr : droppedwindow.thisCpp,
            location,
            relativeTo == null ? ffi.nullptr : relativeTo.thisCpp) !=
        0;
  } // dropIndicatorOverlay() const

  DropIndicatorOverlay dropIndicatorOverlay() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__dropIndicatorOverlay')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropIndicatorOverlay.fromCppPointer(result, false);
  } // groupContainingPos(QPoint globalPos) const

  KDDWBindingsCore.Group groupContainingPos(QPoint globalPos) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__groupContainingPos_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // hasSingleFloatingFrame() const

  bool hasSingleFloatingFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__hasSingleFloatingFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasSingleFrame() const

  bool hasSingleFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__hasSingleFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMDIWrapper() const

  bool isMDIWrapper() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__isMDIWrapper')
        .asFunction();
    return func(thisCpp) != 0;
  } // layoutEqually()

  layoutEqually() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__layoutEqually')
        .asFunction();
    func(thisCpp);
  } // layoutParentContainerEqually(KDDockWidgets::Core::DockWidget * arg__1)

  layoutParentContainerEqually(KDDWBindingsCore.DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__layoutParentContainerEqually_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // mdiDockWidgetWrapper() const

  KDDWBindingsCore.DockWidget mdiDockWidgetWrapper() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__mdiDockWidgetWrapper')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DockWidget.fromCppPointer(result, false);
  } // removeHover()

  removeHover() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__removeHover')
        .asFunction();
    func(thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__DropArea__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateFloatingActions()

  updateFloatingActions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__updateFloatingActions')
        .asFunction();
    func(thisCpp);
  } // validateInputs(KDDockWidgets::Core::View * widget, KDDockWidgets::Location location, const KDDockWidgets::Core::Group * relativeToFrame, KDDockWidgets::InitialOption option) const

  bool validateInputs(KDDWBindingsCore.View? widget, int location,
      KDDWBindingsCore.Group? relativeToFrame, InitialOption option) {
    final bool_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__validateInputs_View_Location_Group_InitialOption')
        .asFunction();
    return func(
            thisCpp,
            widget == null ? ffi.nullptr : widget.thisCpp,
            location,
            relativeToFrame == null ? ffi.nullptr : relativeToFrame.thisCpp,
            option == null ? ffi.nullptr : option.thisCpp) !=
        0;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__DropArea__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 811:
        return "c_KDDockWidgets__Core__DropArea__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 811:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__DropArea__registerVirtualMethodCallback')
        .asFunction();
    final callback811 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback811, 811);
  }
}
