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

class DropArea extends Layout {
  DropArea.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DropArea.init() : super.init() {}
  factory DropArea.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DropArea;
    }
    return DropArea.fromCppPointer(cppPointer, needsAutoDelete);
  } //DropArea(KDDockWidgets::View * parent, QFlags<KDDockWidgets::MainWindowOption> options, bool isMDIWrapper)
  DropArea(View? parent, int options, {bool isMDIWrapper = false})
      : super.init() {
    final voidstar_Func_voidstar_int_bool func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__constructor_View_MainWindowOptions_bool')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp, options,
        isMDIWrapper ? 1 : 0);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // addMultiSplitter(KDDockWidgets::Controllers::DropArea * splitter, KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo, KDDockWidgets::InitialOption option)
  addMultiSplitter(DropArea? splitter, int location,
      {required Group? relativeTo, required InitialOption option}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__addMultiSplitter_DropArea_Location_Group_InitialOption')
        .asFunction();
    func(
        thisCpp,
        splitter == null ? ffi.nullptr : splitter.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        option == null ? ffi.nullptr : option.thisCpp);
  } // addWidget(KDDockWidgets::View * widget, KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo, KDDockWidgets::InitialOption option)

  addWidget(View? widget, int location,
      {required Group? relativeTo, required InitialOption option}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__addWidget_View_Location_Group_InitialOption')
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
            'c_KDDockWidgets__Controllers__DropArea__availableSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // centralFrame() const

  Item centralFrame() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__centralFrame')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Item.fromCppPointer(result, false);
  }

  static // createCentralFrame(QFlags<KDDockWidgets::MainWindowOption> options)
      Group createCentralFrame(int options) {
    final voidstar_Func_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__DropArea__createCentralFrame_MainWindowOptions')
        .asFunction();
    ffi.Pointer<void> result = func(options);
    return Group.fromCppPointer(result, false);
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  } // drop(KDDockWidgets::View * droppedwindow, KDDockWidgets::Location location, KDDockWidgets::Controllers::Group * relativeTo)

  bool drop(View? droppedwindow, int location, Group? relativeTo) {
    final bool_Func_voidstar_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__drop_View_Location_Group')
        .asFunction();
    return func(
            thisCpp,
            droppedwindow == null ? ffi.nullptr : droppedwindow.thisCpp,
            location,
            relativeTo == null ? ffi.nullptr : relativeTo.thisCpp) !=
        0;
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // groupContainingPos(QPoint globalPos) const

  Group groupContainingPos(QPoint globalPos) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__groupContainingPos_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
    return Group.fromCppPointer(result, false);
  } // groups() const

  QList groups() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__groups')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QList<Group>.fromCppPointer(result, true);
  } // hasSingleFloatingFrame() const

  bool hasSingleFloatingFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__hasSingleFloatingFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasSingleFrame() const

  bool hasSingleFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__hasSingleFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMDIWrapper() const

  bool isMDIWrapper() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__isMDIWrapper')
        .asFunction();
    return func(thisCpp) != 0;
  } // layoutEqually()

  layoutEqually() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__layoutEqually')
        .asFunction();
    func(thisCpp);
  } // removeHover()

  removeHover() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__removeHover')
        .asFunction();
    func(thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__DropArea__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateFloatingActions()

  updateFloatingActions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__updateFloatingActions')
        .asFunction();
    func(thisCpp);
  } // validateInputs(KDDockWidgets::View * widget, KDDockWidgets::Location location, const KDDockWidgets::Controllers::Group * relativeToFrame, KDDockWidgets::InitialOption option) const

  bool validateInputs(View? widget, int location, Group? relativeToFrame,
      InitialOption option) {
    final bool_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__validateInputs_View_Location_Group_InitialOption')
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
            'c_KDDockWidgets__Controllers__DropArea__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__DropArea__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__DropArea__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__DropArea__eventFilter_QObject_QEvent";
      case 838:
        return "c_KDDockWidgets__Controllers__DropArea__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 838:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__DropArea__registerVirtualMethodCallback')
        .asFunction();
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
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
    final callback838 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback838, 838);
  }
}
