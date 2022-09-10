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

class MainWindow extends Controller {
  MainWindow.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  MainWindow.init() : super.init() {}
  factory MainWindow.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as MainWindow;
    }
    return MainWindow.fromCppPointer(cppPointer, needsAutoDelete);
  } //MainWindow(KDDockWidgets::View * view, const QString & uniqueName, QFlags<KDDockWidgets::MainWindowOption> options)
  MainWindow(View? view, String? uniqueName, int options) : super.init() {
    final voidstar_Func_voidstar_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__constructor_View_QString_MainWindowOptions')
        .asFunction();
    thisCpp = func(view == null ? ffi.nullptr : view.thisCpp,
        uniqueName?.toNativeUtf8() ?? ffi.nullptr, options);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // addDockWidget(KDDockWidgets::Controllers::DockWidget * dockWidget, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)
  addDockWidget(DockWidget? dockWidget, int location,
      {required DockWidget? relativeTo, required InitialOption initialOption}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__addDockWidget_DockWidget_Location_DockWidget_InitialOption')
        .asFunction();
    func(
        thisCpp,
        dockWidget == null ? ffi.nullptr : dockWidget.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        initialOption == null ? ffi.nullptr : initialOption.thisCpp);
  } // addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget * dockwidget)

  addDockWidgetAsTab(DockWidget? dockwidget) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__addDockWidgetAsTab_DockWidget')
        .asFunction();
    func(thisCpp, dockwidget == null ? ffi.nullptr : dockwidget.thisCpp);
  } // anySideBarIsVisible() const

  bool anySideBarIsVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__anySideBarIsVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // centralAreaGeometry() const

  QRect centralAreaGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__centralAreaGeometry')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // clearSideBarOverlay(bool deleteFrame)

  clearSideBarOverlay({bool deleteFrame = true}) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__clearSideBarOverlay_bool')
        .asFunction();
    func(thisCpp, deleteFrame ? 1 : 0);
  } // closeDockWidgets(bool force)

  bool closeDockWidgets({bool force = false}) {
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__closeDockWidgets_bool')
        .asFunction();
    return func(thisCpp, force ? 1 : 0) != 0;
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as MainWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for MainWindow::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  } // dropArea() const

  DropArea dropArea() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__dropArea')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as MainWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for MainWindow::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as MainWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for MainWindow::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // groupCountChanged(int arg__1)

  groupCountChanged(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__groupCountChanged_int')
        .asFunction();
    func(thisCpp, arg__1);
  } // init(const QString & name)

  init(String? name) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__init_QString')
        .asFunction();
    func(thisCpp, name?.toNativeUtf8() ?? ffi.nullptr);
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__isMDI')
        .asFunction();
    return func(thisCpp) != 0;
  } // layout() const

  Layout layout() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__layout')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Layout.fromCppPointer(result, false);
  } // layoutEqually()

  layoutEqually() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__layoutEqually')
        .asFunction();
    func(thisCpp);
  } // layoutParentContainerEqually(KDDockWidgets::Controllers::DockWidget * dockWidget)

  layoutParentContainerEqually(DockWidget? dockWidget) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__layoutParentContainerEqually_DockWidget')
        .asFunction();
    func(thisCpp, dockWidget == null ? ffi.nullptr : dockWidget.thisCpp);
  } // moveToSideBar(KDDockWidgets::Controllers::DockWidget * dw)

  moveToSideBar(DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__moveToSideBar_DockWidget')
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  } // multiSplitter() const

  DropArea multiSplitter() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__multiSplitter')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  } // options() const

  int options() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__options')
        .asFunction();
    return func(thisCpp);
  } // overlayMargin() const

  int overlayMargin() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__overlayMargin')
        .asFunction();
    return func(thisCpp);
  } // overlayMarginChanged(int margin)

  overlayMarginChanged(int margin) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__overlayMarginChanged_int')
        .asFunction();
    func(thisCpp, margin);
  } // overlayOnSideBar(KDDockWidgets::Controllers::DockWidget * dw)

  overlayOnSideBar(DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__overlayOnSideBar_DockWidget')
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  } // overlayedDockWidget() const

  DockWidget overlayedDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__overlayedDockWidget')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
  } // restoreFromSideBar(KDDockWidgets::Controllers::DockWidget * dw)

  restoreFromSideBar(DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__restoreFromSideBar_DockWidget')
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  } // setContentsMargins(int l, int t, int r, int b)

  setContentsMargins(int l, int t, int r, int b) {
    final void_Func_voidstar_int_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__setContentsMargins_int_int_int_int')
        .asFunction();
    func(thisCpp, l, t, r, b);
  } // setOverlayMargin(int margin)

  setOverlayMargin(int margin) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__setOverlayMargin_int')
        .asFunction();
    func(thisCpp, margin);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as MainWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for MainWindow::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // setUniqueName(const QString & uniqueName)

  setUniqueName(String? uniqueName) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__setUniqueName_QString')
        .asFunction();
    func(thisCpp, uniqueName?.toNativeUtf8() ?? ffi.nullptr);
  } // sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget * dw) const

  SideBar sideBarForDockWidget(DockWidget? dw) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__sideBarForDockWidget_DockWidget')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
    return SideBar.fromCppPointer(result, false);
  } // toggleOverlayOnSideBar(KDDockWidgets::Controllers::DockWidget * dw)

  toggleOverlayOnSideBar(DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__toggleOverlayOnSideBar_DockWidget')
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__MainWindow__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // uniqueName() const

  QString uniqueName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__uniqueName')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // uniqueNameChanged()

  uniqueNameChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__uniqueNameChanged')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__MainWindow__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__MainWindow__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__MainWindow__eventFilter_QObject_QEvent";
      case 888:
        return "c_KDDockWidgets__Controllers__MainWindow__setParentView_impl_View";
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
      case 888:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__MainWindow__registerVirtualMethodCallback')
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
    final callback888 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback888, 888);
  }
}
