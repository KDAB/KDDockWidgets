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

class FloatingWindow extends KDDWBindingsCore.Controller {
  FloatingWindow.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  FloatingWindow.init() : super.init() {}
  factory FloatingWindow.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as FloatingWindow;
    }
    return FloatingWindow.fromCppPointer(cppPointer, needsAutoDelete);
  } //FloatingWindow(KDDockWidgets::Core::Group * group, QRect suggestedGeometry, KDDockWidgets::Core::MainWindow * parent)
  FloatingWindow(KDDWBindingsCore.Group? group, QRect suggestedGeometry,
      {required KDDWBindingsCore.MainWindow? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__constructor_Group_QRect_MainWindow')
        .asFunction();
    thisCpp = func(
        group == null ? ffi.nullptr : group.thisCpp,
        suggestedGeometry == null ? ffi.nullptr : suggestedGeometry.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } //FloatingWindow(QRect suggestedGeometry, KDDockWidgets::Core::MainWindow * parent)
  FloatingWindow.ctor2(QRect suggestedGeometry,
      {required KDDWBindingsCore.MainWindow? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__constructor_QRect_MainWindow')
        .asFunction();
    thisCpp = func(
        suggestedGeometry == null ? ffi.nullptr : suggestedGeometry.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // activatedChanged()
  activatedChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__activatedChanged')
        .asFunction();
    func(thisCpp);
  } // addDockWidget(KDDockWidgets::Core::DockWidget * arg__1, KDDockWidgets::Location location, KDDockWidgets::Core::DockWidget * relativeTo, KDDockWidgets::InitialOption arg__4)

  addDockWidget(KDDWBindingsCore.DockWidget? arg__1, int location,
      KDDWBindingsCore.DockWidget? relativeTo,
      {required InitialOption arg__4}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption')
        .asFunction();
    func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        arg__4 == null ? ffi.nullptr : arg__4.thisCpp);
  } // allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const

  bool allDockWidgetsHave(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__allDockWidgetsHave_DockWidgetOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const

  bool allDockWidgetsHave_2(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__allDockWidgetsHave_LayoutSaverOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const

  bool anyDockWidgetsHas(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__anyDockWidgetsHas_DockWidgetOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const

  bool anyDockWidgetsHas_2(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__anyDockWidgetsHas_LayoutSaverOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyNonClosable() const

  bool anyNonClosable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__anyNonClosable')
        .asFunction();
    return func(thisCpp) != 0;
  } // anyNonDockable() const

  bool anyNonDockable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__anyNonDockable')
        .asFunction();
    return func(thisCpp) != 0;
  } // beingDeleted() const

  bool beingDeleted() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__beingDeleted')
        .asFunction();
    return func(thisCpp) != 0;
  } // dragRect() const

  QRect dragRect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__dragRect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // dropArea() const

  KDDWBindingsCore.DropArea dropArea() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__dropArea')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DropArea.fromCppPointer(result, false);
  }

  static // ensureRectIsOnScreen(QRect & geometry)
      ensureRectIsOnScreen(QRect? geometry) {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_static_KDDockWidgets__Core__FloatingWindow__ensureRectIsOnScreen_QRect')
        .asFunction();
    func(geometry == null ? ffi.nullptr : geometry.thisCpp);
  } // hasSingleDockWidget() const

  bool hasSingleDockWidget() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__hasSingleDockWidget')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasSingleFrame() const

  bool hasSingleFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__hasSingleFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // isInDragArea(QPoint globalPoint) const

  bool isInDragArea(QPoint globalPoint) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__isInDragArea_QPoint')
        .asFunction();
    return func(
            thisCpp, globalPoint == null ? ffi.nullptr : globalPoint.thisCpp) !=
        0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1599))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMDI_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::isMDI() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMDI();
    return result ? 1 : 0;
  } // isUtilityWindow() const

  bool isUtilityWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__isUtilityWindow')
        .asFunction();
    return func(thisCpp) != 0;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1602))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // layout() const

  KDDWBindingsCore.Layout layout() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__layout')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Layout.fromCppPointer(result, false);
  } // mainWindow() const

  KDDWBindingsCore.MainWindow mainWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__mainWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.MainWindow.fromCppPointer(result, false);
  } // maxSizeHint() const

  QSize maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__maxSizeHint')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // maybeCreateResizeHandler()

  maybeCreateResizeHandler() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__maybeCreateResizeHandler')
        .asFunction();
    func(thisCpp);
  } // multiSplitter() const

  KDDWBindingsCore.DropArea multiSplitter() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__multiSplitter')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DropArea.fromCppPointer(result, false);
  } // numDockWidgetsChanged()

  numDockWidgetsChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__numDockWidgetsChanged')
        .asFunction();
    func(thisCpp);
  } // numFramesChanged()

  numFramesChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__numFramesChanged')
        .asFunction();
    func(thisCpp);
  } // onFrameCountChanged(int count)

  onFrameCountChanged(int count) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__onFrameCountChanged_int')
        .asFunction();
    func(thisCpp, count);
  } // onVisibleFrameCountChanged(int count)

  onVisibleFrameCountChanged(int count) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__onVisibleFrameCountChanged_int')
        .asFunction();
    func(thisCpp, count);
  } // scheduleDeleteLater()

  scheduleDeleteLater() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__scheduleDeleteLater')
        .asFunction();
    func(thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  } // setSuggestedGeometry(QRect suggestedRect)

  setSuggestedGeometry(QRect suggestedRect) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__setSuggestedGeometry_QRect')
        .asFunction();
    func(thisCpp, suggestedRect == null ? ffi.nullptr : suggestedRect.thisCpp);
  } // singleDockWidget() const

  KDDWBindingsCore.DockWidget singleDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1621))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DockWidget.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> singleDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::singleDockWidget() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.singleDockWidget();
    return result.thisCpp;
  } // singleFrame() const

  KDDWBindingsCore.Group singleFrame() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__singleFrame')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // supportsMaximizeButton() const

  bool supportsMaximizeButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__supportsMaximizeButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // supportsMinimizeButton() const

  bool supportsMinimizeButton() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__supportsMinimizeButton')
        .asFunction();
    return func(thisCpp) != 0;
  } // titleBar() const

  KDDWBindingsCore.TitleBar titleBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__titleBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.TitleBar.fromCppPointer(result, false);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__FloatingWindow__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateSizeConstraints()

  updateSizeConstraints() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__updateSizeConstraints')
        .asFunction();
    func(thisCpp);
  } // updateTitleAndIcon()

  updateTitleAndIcon() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__updateTitleAndIcon')
        .asFunction();
    func(thisCpp);
  } // updateTitleBarVisibility()

  updateTitleBarVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__updateTitleBarVisibility')
        .asFunction();
    func(thisCpp);
  } // userType() const

  int userType() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__userType')
        .asFunction();
    return func(thisCpp);
  } // windowStateChanged()

  windowStateChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__windowStateChanged')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 1599:
        return "c_KDDockWidgets__Core__FloatingWindow__isMDI";
      case 1602:
        return "c_KDDockWidgets__Core__FloatingWindow__isWindow";
      case 900:
        return "c_KDDockWidgets__Core__FloatingWindow__setParentView_impl_View";
      case 1621:
        return "c_KDDockWidgets__Core__FloatingWindow__singleDockWidget";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 1599:
        return "isMDI";
      case 1602:
        return "isWindow";
      case 900:
        return "setParentView_impl";
      case 1621:
        return "singleDockWidget";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__FloatingWindow__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept1599 = 0;
    final callback1599 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.FloatingWindow.isMDI_calledFromC, callbackExcept1599);
    registerCallback(thisCpp, callback1599, 1599);
    const callbackExcept1602 = 0;
    final callback1602 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.FloatingWindow.isWindow_calledFromC,
        callbackExcept1602);
    registerCallback(thisCpp, callback1602, 1602);
    final callback900 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    final callback1621 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.FloatingWindow.singleDockWidget_calledFromC);
    registerCallback(thisCpp, callback1621, 1621);
  }
}
