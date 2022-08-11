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

class TitleBar extends Controller {
  TitleBar.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TitleBar.init() : super.init() {}
  factory TitleBar.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TitleBar;
    }
    return TitleBar.fromCppPointer(cppPointer, needsAutoDelete);
  } //TitleBar(KDDockWidgets::Controllers::FloatingWindow * parent)
  TitleBar(FloatingWindow? parent) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__constructor_FloatingWindow')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } //TitleBar(KDDockWidgets::Controllers::Group * parent)
  TitleBar.ctor2(Group? parent) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__constructor_Group')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // closeButtonEnabled() const
  bool closeButtonEnabled() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__closeButtonEnabled')
        .asFunction();
    return func(thisCpp) != 0;
  } // closeButtonEnabledChanged(bool arg__1)

  closeButtonEnabledChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__closeButtonEnabledChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // floatButtonToolTip() const

  QString floatButtonToolTip() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__floatButtonToolTip')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // floatButtonToolTipChanged(const QString & arg__1)

  floatButtonToolTipChanged(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__floatButtonToolTipChanged_QString')
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  } // floatButtonVisible() const

  bool floatButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__floatButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // floatButtonVisibleChanged(bool arg__1)

  floatButtonVisibleChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__floatButtonVisibleChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // floatingWindow() const

  FloatingWindow floatingWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__floatingWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return FloatingWindow.fromCppPointer(result, false);
  } // group() const

  Group group() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__group')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // hasIcon() const

  bool hasIcon() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__hasIcon')
        .asFunction();
    return func(thisCpp) != 0;
  } // iconChanged()

  iconChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__iconChanged')
        .asFunction();
    func(thisCpp);
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__init')
        .asFunction();
    func(thisCpp);
  } // isCloseButtonEnabled() const

  bool isCloseButtonEnabled() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isCloseButtonEnabled')
        .asFunction();
    return func(thisCpp) != 0;
  } // isCloseButtonVisible() const

  bool isCloseButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isCloseButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloatButtonVisible() const

  bool isFloatButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isFloatButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloating() const

  bool isFloating() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isFloating')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFocused() const

  bool isFocused() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isFocused')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFocusedChanged()

  isFocusedChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isFocusedChanged')
        .asFunction();
    func(thisCpp);
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1025))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMDI_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isMDI() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMDI();
    return result ? 1 : 0;
  } // isOverlayed() const

  bool isOverlayed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__isOverlayed')
        .asFunction();
    return func(thisCpp) != 0;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1028))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // minimizeButtonChanged(bool visible, bool enabled)

  minimizeButtonChanged(bool visible, bool enabled) {
    final void_Func_voidstar_bool_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__minimizeButtonChanged_bool_bool')
        .asFunction();
    func(thisCpp, visible ? 1 : 0, enabled ? 1 : 0);
  } // onAutoHideClicked()

  onAutoHideClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__onAutoHideClicked')
        .asFunction();
    func(thisCpp);
  } // onCloseClicked()

  onCloseClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__onCloseClicked')
        .asFunction();
    func(thisCpp);
  } // onDoubleClicked()

  bool onDoubleClicked() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__onDoubleClicked')
        .asFunction();
    return func(thisCpp) != 0;
  } // onFloatClicked()

  onFloatClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__onFloatClicked')
        .asFunction();
    func(thisCpp);
  } // onMaximizeClicked()

  onMaximizeClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__onMaximizeClicked')
        .asFunction();
    func(thisCpp);
  } // onMinimizeClicked()

  onMinimizeClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__onMinimizeClicked')
        .asFunction();
    func(thisCpp);
  } // setCloseButtonEnabled(bool arg__1)

  setCloseButtonEnabled(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__setCloseButtonEnabled_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // setFloatButtonToolTip(const QString & arg__1)

  setFloatButtonToolTip(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__setFloatButtonToolTip_QString')
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  } // setFloatButtonVisible(bool arg__1)

  setFloatButtonVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__setFloatButtonVisible_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // setTitle(const QString & title)

  setTitle(String? title) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__setTitle_QString')
        .asFunction();
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  } // supportsAutoHideButton() const

  bool supportsAutoHideButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__supportsAutoHideButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsFloatingButton() const

  bool supportsFloatingButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__supportsFloatingButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsMaximizeButton() const

  bool supportsMaximizeButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__supportsMaximizeButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsMinimizeButton() const

  bool supportsMinimizeButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__supportsMinimizeButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // tabBar() const

  TabBar tabBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__tabBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TabBar.fromCppPointer(result, false);
  } // title() const

  QString title() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__title')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // titleBarIsFocusable() const

  bool titleBarIsFocusable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__titleBarIsFocusable')
        .asFunction();
    return func(thisCpp) != 0;
  } // titleChanged()

  titleChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__titleChanged')
        .asFunction();
    func(thisCpp);
  } // toggleMaximized()

  toggleMaximized() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__toggleMaximized')
        .asFunction();
    func(thisCpp);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__TitleBar__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateAutoHideButton()

  updateAutoHideButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__updateAutoHideButton')
        .asFunction();
    func(thisCpp);
  } // updateButtons()

  updateButtons() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__updateButtons')
        .asFunction();
    func(thisCpp);
  } // updateCloseButton()

  updateCloseButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__updateCloseButton')
        .asFunction();
    func(thisCpp);
  } // updateFloatButton()

  updateFloatButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__updateFloatButton')
        .asFunction();
    func(thisCpp);
  } // updateMaximizeButton()

  updateMaximizeButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__updateMaximizeButton')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__TitleBar__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__TitleBar__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__TitleBar__eventFilter_QObject_QEvent";
      case 1025:
        return "c_KDDockWidgets__Controllers__TitleBar__isMDI";
      case 1028:
        return "c_KDDockWidgets__Controllers__TitleBar__isWindow";
      case 826:
        return "c_KDDockWidgets__Controllers__TitleBar__setParentView_impl_View";
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
      case 1025:
        return "isMDI";
      case 1028:
        return "isWindow";
      case 826:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__TitleBar__registerVirtualMethodCallback')
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
    const callbackExcept1025 = 0;
    final callback1025 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TitleBar.isMDI_calledFromC, callbackExcept1025);
    registerCallback(thisCpp, callback1025, 1025);
    const callbackExcept1028 = 0;
    final callback1028 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TitleBar.isWindow_calledFromC, callbackExcept1028);
    registerCallback(thisCpp, callback1028, 1028);
    final callback826 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback826, 826);
  }
}
