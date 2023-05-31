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
import '../../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class TitleBar extends KDDWBindingsCore.Controller {
  TitleBar.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TitleBar.init() : super.init() {}
  factory TitleBar.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TitleBar;
    }
    return TitleBar.fromCppPointer(cppPointer, needsAutoDelete);
  } //TitleBar(KDDockWidgets::Core::FloatingWindow * parent)
  TitleBar(KDDWBindingsCore.FloatingWindow? parent) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__constructor_FloatingWindow')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } //TitleBar(KDDockWidgets::Core::Group * parent)
  TitleBar.ctor2(KDDWBindingsCore.Group? parent) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__constructor_Group')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // closeButtonEnabled() const
  bool closeButtonEnabled() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__closeButtonEnabled')
        .asFunction();
    return func(thisCpp) != 0;
  } // closeButtonEnabledChanged(bool arg__1)

  closeButtonEnabledChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__closeButtonEnabledChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // floatButtonToolTip() const

  QString floatButtonToolTip() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__floatButtonToolTip')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // floatButtonToolTipChanged(const QString & arg__1)

  floatButtonToolTipChanged(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__floatButtonToolTipChanged_QString')
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  } // floatButtonVisible() const

  bool floatButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__floatButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // floatButtonVisibleChanged(bool arg__1)

  floatButtonVisibleChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__floatButtonVisibleChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // floatingWindow() const

  KDDWBindingsCore.FloatingWindow floatingWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__floatingWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false);
  } // group() const

  KDDWBindingsCore.Group group() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__group')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // hasIcon() const

  bool hasIcon() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__hasIcon')
        .asFunction();
    return func(thisCpp) != 0;
  } // iconChanged()

  iconChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__iconChanged')
        .asFunction();
    func(thisCpp);
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__init')
        .asFunction();
    func(thisCpp);
  } // isCloseButtonEnabled() const

  bool isCloseButtonEnabled() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__isCloseButtonEnabled')
        .asFunction();
    return func(thisCpp) != 0;
  } // isCloseButtonVisible() const

  bool isCloseButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__isCloseButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloatButtonVisible() const

  bool isFloatButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__isFloatButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloating() const

  bool isFloating() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__isFloating')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFocused() const

  bool isFocused() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__isFocused')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFocusedChanged()

  isFocusedChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__isFocusedChanged')
        .asFunction();
    func(thisCpp);
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1154))
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
            'c_KDDockWidgets__Core__TitleBar__isOverlayed')
        .asFunction();
    return func(thisCpp) != 0;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1157))
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
  } // mainWindow() const

  KDDWBindingsCore.MainWindow mainWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__mainWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.MainWindow.fromCppPointer(result, false);
  } // maximizeButtonVisible() const

  bool maximizeButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__maximizeButtonVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // minimizeButtonChanged(bool visible, bool enabled)

  minimizeButtonChanged(bool visible, bool enabled) {
    final void_Func_voidstar_bool_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__minimizeButtonChanged_bool_bool')
        .asFunction();
    func(thisCpp, visible ? 1 : 0, enabled ? 1 : 0);
  } // numDockWidgetsChanged()

  numDockWidgetsChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__numDockWidgetsChanged')
        .asFunction();
    func(thisCpp);
  } // onAutoHideClicked()

  onAutoHideClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__onAutoHideClicked')
        .asFunction();
    func(thisCpp);
  } // onCloseClicked()

  onCloseClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__onCloseClicked')
        .asFunction();
    func(thisCpp);
  } // onDoubleClicked()

  bool onDoubleClicked() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__onDoubleClicked')
        .asFunction();
    return func(thisCpp) != 0;
  } // onFloatClicked()

  onFloatClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__onFloatClicked')
        .asFunction();
    func(thisCpp);
  } // onMaximizeClicked()

  onMaximizeClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__onMaximizeClicked')
        .asFunction();
    func(thisCpp);
  } // onMinimizeClicked()

  onMinimizeClicked() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__onMinimizeClicked')
        .asFunction();
    func(thisCpp);
  } // setCloseButtonEnabled(bool arg__1)

  setCloseButtonEnabled(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__setCloseButtonEnabled_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // setFloatButtonToolTip(const QString & arg__1)

  setFloatButtonToolTip(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__setFloatButtonToolTip_QString')
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  } // setFloatButtonVisible(bool arg__1)

  setFloatButtonVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__setFloatButtonVisible_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  } // setTitle(const QString & title)

  setTitle(String? title) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__setTitle_QString')
        .asFunction();
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  } // singleDockWidget() const

  KDDWBindingsCore.DockWidget singleDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1179))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DockWidget.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> singleDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::singleDockWidget() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.singleDockWidget();
    return result.thisCpp;
  } // supportsAutoHideButton() const

  bool supportsAutoHideButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__supportsAutoHideButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsFloatingButton() const

  bool supportsFloatingButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__supportsFloatingButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsMaximizeButton() const

  bool supportsMaximizeButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__supportsMaximizeButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsMinimizeButton() const

  bool supportsMinimizeButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__supportsMinimizeButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // tabBar() const

  KDDWBindingsCore.TabBar tabBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__tabBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.TabBar.fromCppPointer(result, false);
  } // title() const

  QString title() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__title')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // titleBarIsFocusable() const

  bool titleBarIsFocusable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__titleBarIsFocusable')
        .asFunction();
    return func(thisCpp) != 0;
  } // titleChanged()

  titleChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__titleChanged')
        .asFunction();
    func(thisCpp);
  } // toggleMaximized()

  toggleMaximized() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__toggleMaximized')
        .asFunction();
    func(thisCpp);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__TitleBar__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateAutoHideButton()

  updateAutoHideButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__updateAutoHideButton')
        .asFunction();
    func(thisCpp);
  } // updateButtons()

  updateButtons() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__updateButtons')
        .asFunction();
    func(thisCpp);
  } // updateCloseButton()

  updateCloseButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__updateCloseButton')
        .asFunction();
    func(thisCpp);
  } // updateFloatButton()

  updateFloatButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__updateFloatButton')
        .asFunction();
    func(thisCpp);
  } // updateMaximizeButton()

  updateMaximizeButton() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__updateMaximizeButton')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 1154:
        return "c_KDDockWidgets__Core__TitleBar__isMDI";
      case 1157:
        return "c_KDDockWidgets__Core__TitleBar__isWindow";
      case 908:
        return "c_KDDockWidgets__Core__TitleBar__setParentView_impl_View";
      case 1179:
        return "c_KDDockWidgets__Core__TitleBar__singleDockWidget";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1154:
        return "isMDI";
      case 1157:
        return "isWindow";
      case 908:
        return "setParentView_impl";
      case 1179:
        return "singleDockWidget";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__TitleBar__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept1154 = 0;
    final callback1154 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.TitleBar.isMDI_calledFromC, callbackExcept1154);
    registerCallback(thisCpp, callback1154, 1154);
    const callbackExcept1157 = 0;
    final callback1157 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.TitleBar.isWindow_calledFromC, callbackExcept1157);
    registerCallback(thisCpp, callback1157, 1157);
    final callback908 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback908, 908);
    final callback1179 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.TitleBar.singleDockWidget_calledFromC);
    registerCallback(thisCpp, callback1179, 1179);
  }
}
