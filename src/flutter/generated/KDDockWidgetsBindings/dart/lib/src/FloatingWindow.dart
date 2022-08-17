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

class FloatingWindow extends Controller {
  FloatingWindow.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  FloatingWindow.init() : super.init() {}
  factory FloatingWindow.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as FloatingWindow;
    }
    return FloatingWindow.fromCppPointer(cppPointer, needsAutoDelete);
  } //FloatingWindow(KDDockWidgets::Controllers::Group * group, QRect suggestedGeometry)
  FloatingWindow(Group? group, QRect suggestedGeometry) : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__constructor_Group_QRect')
        .asFunction();
    thisCpp = func(group == null ? ffi.nullptr : group.thisCpp,
        suggestedGeometry == null ? ffi.nullptr : suggestedGeometry.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } //FloatingWindow(QRect suggestedGeometry)
  FloatingWindow.ctor2(QRect suggestedGeometry) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__constructor_QRect')
        .asFunction();
    thisCpp = func(
        suggestedGeometry == null ? ffi.nullptr : suggestedGeometry.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // activatedChanged()
  activatedChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__activatedChanged')
        .asFunction();
    func(thisCpp);
  } // addDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo, KDDockWidgets::InitialOption arg__4)

  addDockWidget(DockWidget? arg__1, int location, DockWidget? relativeTo,
      {required InitialOption arg__4}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption')
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
            'c_KDDockWidgets__Controllers__FloatingWindow__allDockWidgetsHave_DockWidgetOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const

  bool allDockWidgetsHave_2(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__allDockWidgetsHave_LayoutSaverOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const

  bool anyDockWidgetsHas(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__anyDockWidgetsHas_DockWidgetOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const

  bool anyDockWidgetsHas_2(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__anyDockWidgetsHas_LayoutSaverOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyNonClosable() const

  bool anyNonClosable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__anyNonClosable')
        .asFunction();
    return func(thisCpp) != 0;
  } // anyNonDockable() const

  bool anyNonDockable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__anyNonDockable')
        .asFunction();
    return func(thisCpp) != 0;
  } // beingDeleted() const

  bool beingDeleted() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__beingDeleted')
        .asFunction();
    return func(thisCpp) != 0;
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  } // dragRect() const

  QRect dragRect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__dragRect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // dropArea() const

  DropArea dropArea() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__dropArea')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  }

  static // ensureRectIsOnScreen(QRect & geometry)
      ensureRectIsOnScreen(QRect? geometry) {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_static_KDDockWidgets__Controllers__FloatingWindow__ensureRectIsOnScreen_QRect')
        .asFunction();
    func(geometry == null ? ffi.nullptr : geometry.thisCpp);
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // hasSingleDockWidget() const

  bool hasSingleDockWidget() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__hasSingleDockWidget')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasSingleFrame() const

  bool hasSingleFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__hasSingleFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // isInDragArea(QPoint globalPoint) const

  bool isInDragArea(QPoint globalPoint) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__isInDragArea_QPoint')
        .asFunction();
    return func(
            thisCpp, globalPoint == null ? ffi.nullptr : globalPoint.thisCpp) !=
        0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1430))
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
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1432))
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

  Layout layout() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__layout')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Layout.fromCppPointer(result, false);
  } // maxSizeHint() const

  QSize maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__maxSizeHint')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // maybeCreateResizeHandler()

  maybeCreateResizeHandler() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__maybeCreateResizeHandler')
        .asFunction();
    func(thisCpp);
  } // multiSplitter() const

  DropArea multiSplitter() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__multiSplitter')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  } // numFramesChanged()

  numFramesChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__numFramesChanged')
        .asFunction();
    func(thisCpp);
  } // onFrameCountChanged(int count)

  onFrameCountChanged(int count) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__onFrameCountChanged_int')
        .asFunction();
    func(thisCpp, count);
  } // onVisibleFrameCountChanged(int count)

  onVisibleFrameCountChanged(int count) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__onVisibleFrameCountChanged_int')
        .asFunction();
    func(thisCpp, count);
  } // scheduleDeleteLater()

  scheduleDeleteLater() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__scheduleDeleteLater')
        .asFunction();
    func(thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as FloatingWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for FloatingWindow::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // setSuggestedGeometry(QRect suggestedRect)

  setSuggestedGeometry(QRect suggestedRect) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__setSuggestedGeometry_QRect')
        .asFunction();
    func(thisCpp, suggestedRect == null ? ffi.nullptr : suggestedRect.thisCpp);
  } // singleDockWidget() const

  DockWidget singleDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1449))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
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

  Group singleFrame() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__singleFrame')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // titleBar() const

  TitleBar titleBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__titleBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TitleBar.fromCppPointer(result, false);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__FloatingWindow__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // updateSizeConstraints()

  updateSizeConstraints() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__updateSizeConstraints')
        .asFunction();
    func(thisCpp);
  } // updateTitleAndIcon()

  updateTitleAndIcon() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__updateTitleAndIcon')
        .asFunction();
    func(thisCpp);
  } // updateTitleBarVisibility()

  updateTitleBarVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__updateTitleBarVisibility')
        .asFunction();
    func(thisCpp);
  } // userType() const

  int userType() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__userType')
        .asFunction();
    return func(thisCpp);
  } // windowStateChanged()

  windowStateChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__windowStateChanged')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__FloatingWindow__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__FloatingWindow__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__FloatingWindow__eventFilter_QObject_QEvent";
      case 1430:
        return "c_KDDockWidgets__Controllers__FloatingWindow__isMDI";
      case 1432:
        return "c_KDDockWidgets__Controllers__FloatingWindow__isWindow";
      case 826:
        return "c_KDDockWidgets__Controllers__FloatingWindow__setParentView_impl_View";
      case 1449:
        return "c_KDDockWidgets__Controllers__FloatingWindow__singleDockWidget";
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
      case 1430:
        return "isMDI";
      case 1432:
        return "isWindow";
      case 826:
        return "setParentView_impl";
      case 1449:
        return "singleDockWidget";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__FloatingWindow__registerVirtualMethodCallback')
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
    const callbackExcept1430 = 0;
    final callback1430 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        FloatingWindow.isMDI_calledFromC, callbackExcept1430);
    registerCallback(thisCpp, callback1430, 1430);
    const callbackExcept1432 = 0;
    final callback1432 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        FloatingWindow.isWindow_calledFromC, callbackExcept1432);
    registerCallback(thisCpp, callback1432, 1432);
    final callback826 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback826, 826);
    final callback1449 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        FloatingWindow.singleDockWidget_calledFromC);
    registerCallback(thisCpp, callback1449, 1449);
  }
}
