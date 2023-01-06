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
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class DockWidget extends Controller {
  DockWidget.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DockWidget.init() : super.init() {}
  factory DockWidget.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DockWidget;
    }
    return DockWidget.fromCppPointer(cppPointer, needsAutoDelete);
  } //DockWidget(KDDockWidgets::View * view, const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
  DockWidget(View? view, String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0})
      : super.init() {
    final voidstar_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__constructor_View_QString_DockWidgetOptions_LayoutSaverOptions')
        .asFunction();
    thisCpp = func(view == null ? ffi.nullptr : view.thisCpp,
        uniqueName?.toNativeUtf8() ?? ffi.nullptr, options, layoutSaverOptions);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // aboutToDelete(KDDockWidgets::Controllers::DockWidget * arg__1)
  aboutToDelete(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__aboutToDelete_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // aboutToDeleteOnClose()

  aboutToDeleteOnClose() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__aboutToDeleteOnClose')
        .asFunction();
    func(thisCpp);
  } // actualTitleBarChanged()

  actualTitleBarChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__actualTitleBarChanged')
        .asFunction();
    func(thisCpp);
  } // addDockWidgetAsTab(KDDockWidgets::Controllers::DockWidget * other, KDDockWidgets::InitialOption initialOption)

  addDockWidgetAsTab(DockWidget? other,
      {required InitialOption initialOption}) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__addDockWidgetAsTab_DockWidget_InitialOption')
        .asFunction();
    func(thisCpp, other == null ? ffi.nullptr : other.thisCpp,
        initialOption == null ? ffi.nullptr : initialOption.thisCpp);
  } // addDockWidgetToContainingWindow(KDDockWidgets::Controllers::DockWidget * other, KDDockWidgets::Location location, KDDockWidgets::Controllers::DockWidget * relativeTo, KDDockWidgets::InitialOption initialOption)

  addDockWidgetToContainingWindow(DockWidget? other, int location,
      {required DockWidget? relativeTo, required InitialOption initialOption}) {
    final void_Func_voidstar_voidstar_int_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__addDockWidgetToContainingWindow_DockWidget_Location_DockWidget_InitialOption')
        .asFunction();
    func(
        thisCpp,
        other == null ? ffi.nullptr : other.thisCpp,
        location,
        relativeTo == null ? ffi.nullptr : relativeTo.thisCpp,
        initialOption == null ? ffi.nullptr : initialOption.thisCpp);
  }

  static // byName(const QString & uniqueName)
      DockWidget byName(String? uniqueName) {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_static_KDDockWidgets__Controllers__DockWidget__byName_QString')
        .asFunction();
    ffi.Pointer<void> result = func(uniqueName?.toNativeUtf8() ?? ffi.nullptr);
    return DockWidget.fromCppPointer(result, false);
  } // currentTabIndex() const

  int currentTabIndex() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__currentTabIndex')
        .asFunction();
    return func(thisCpp);
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // floatingWindow() const

  FloatingWindow floatingWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__floatingWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return FloatingWindow.fromCppPointer(result, false);
  } // forceClose()

  forceClose() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__forceClose')
        .asFunction();
    func(thisCpp);
  } // groupGeometry() const

  QRect groupGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__groupGeometry')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // guestViewChanged()

  guestViewChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__guestViewChanged')
        .asFunction();
    func(thisCpp);
  } // hasPreviousDockedLocation() const

  bool hasPreviousDockedLocation() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__hasPreviousDockedLocation')
        .asFunction();
    return func(thisCpp) != 0;
  } // iconChanged()

  iconChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__iconChanged')
        .asFunction();
    func(thisCpp);
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__init')
        .asFunction();
    func(thisCpp);
  } // isCurrentTab() const

  bool isCurrentTab() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isCurrentTab')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloating() const

  bool isFloating() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isFloating')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloatingChanged(bool arg__1)

  isFloatingChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isFloatingChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // isFocused() const

  bool isFocused() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isFocused')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFocusedChanged(bool arg__1)

  isFocusedChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isFocusedChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // isInMainWindow() const

  bool isInMainWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isInMainWindow')
        .asFunction();
    return func(thisCpp) != 0;
  } // isInSideBar() const

  bool isInSideBar() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isInSideBar')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMainWindow() const

  bool isMainWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isMainWindow')
        .asFunction();
    return func(thisCpp) != 0;
  } // isOpen() const

  bool isOpen() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isOpen')
        .asFunction();
    return func(thisCpp) != 0;
  } // isOverlayed() const

  bool isOverlayed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isOverlayed')
        .asFunction();
    return func(thisCpp) != 0;
  } // isOverlayedChanged(bool arg__1)

  isOverlayedChanged(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isOverlayedChanged_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // isPersistentCentralDockWidget() const

  bool isPersistentCentralDockWidget() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isPersistentCentralDockWidget')
        .asFunction();
    return func(thisCpp) != 0;
  } // isTabbed() const

  bool isTabbed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__isTabbed')
        .asFunction();
    return func(thisCpp) != 0;
  } // lastOverlayedSize() const

  QSize lastOverlayedSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__lastOverlayedSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // layoutSaverOptions() const

  int layoutSaverOptions() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__layoutSaverOptions')
        .asFunction();
    return func(thisCpp);
  } // mainWindow() const

  MainWindow mainWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__mainWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return MainWindow.fromCppPointer(result, false);
  } // moveToSideBar()

  moveToSideBar() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__moveToSideBar')
        .asFunction();
    func(thisCpp);
  } // onResize(QSize newSize)

  onResize(QSize newSize) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__onResize_QSize')
        .asFunction();
    func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp);
  } // open()

  open() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__open')
        .asFunction();
    func(thisCpp);
  } // options() const

  int options() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__options')
        .asFunction();
    return func(thisCpp);
  } // optionsChanged(QFlags<KDDockWidgets::DockWidgetOption> arg__1)

  optionsChanged(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__optionsChanged_DockWidgetOptions')
        .asFunction();
    func(thisCpp, arg__1);
  } // raise()

  raise() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__raise')
        .asFunction();
    func(thisCpp);
  } // removedFromSideBar()

  removedFromSideBar() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__removedFromSideBar')
        .asFunction();
    func(thisCpp);
  } // setAffinityName(const QString & name)

  setAffinityName(String? name) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setAffinityName_QString')
        .asFunction();
    func(thisCpp, name?.toNativeUtf8() ?? ffi.nullptr);
  } // setAsCurrentTab()

  setAsCurrentTab() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setAsCurrentTab')
        .asFunction();
    func(thisCpp);
  } // setFloating(bool floats)

  bool setFloating(bool floats) {
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setFloating_bool')
        .asFunction();
    return func(thisCpp, floats ? 1 : 0) != 0;
  } // setFloatingGeometry(QRect geo)

  setFloatingGeometry(QRect geo) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setFloatingGeometry_QRect')
        .asFunction();
    func(thisCpp, geo == null ? ffi.nullptr : geo.thisCpp);
  } // setMDIPosition(QPoint pos)

  setMDIPosition(QPoint pos) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setMDIPosition_QPoint')
        .asFunction();
    func(thisCpp, pos == null ? ffi.nullptr : pos.thisCpp);
  } // setMDISize(QSize size)

  setMDISize(QSize size) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setMDISize_QSize')
        .asFunction();
    func(thisCpp, size == null ? ffi.nullptr : size.thisCpp);
  } // setMDIZ(int z)

  setMDIZ(int z) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setMDIZ_int')
        .asFunction();
    func(thisCpp, z);
  } // setOptions(QFlags<KDDockWidgets::DockWidgetOption> arg__1)

  setOptions(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setOptions_DockWidgetOptions')
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // setTitle(const QString & title)

  setTitle(String? title) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setTitle_QString')
        .asFunction();
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  } // setUserType(int userType)

  setUserType(int userType) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__setUserType_int')
        .asFunction();
    func(thisCpp, userType);
  } // show()

  show_2() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__show')
        .asFunction();
    func(thisCpp);
  } // skipsRestore() const

  bool skipsRestore() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__skipsRestore')
        .asFunction();
    return func(thisCpp) != 0;
  } // tabIndex() const

  int tabIndex() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__tabIndex')
        .asFunction();
    return func(thisCpp);
  } // title() const

  QString title() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__title')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // titleBar() const

  TitleBar titleBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__titleBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TitleBar.fromCppPointer(result, false);
  } // titleChanged(const QString & title)

  titleChanged(String? title) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__titleChanged_QString')
        .asFunction();
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__DockWidget__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // uniqueName() const

  QString uniqueName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__uniqueName')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // userType() const

  int userType() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__userType')
        .asFunction();
    return func(thisCpp);
  } // windowActiveAboutToChange(bool activated)

  windowActiveAboutToChange(bool activated) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__windowActiveAboutToChange_bool')
        .asFunction();
    func(thisCpp, activated ? 1 : 0);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__DockWidget__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__Controllers__DockWidget__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__DockWidget__eventFilter_QObject_QEvent";
      case 891:
        return "c_KDDockWidgets__Controllers__DockWidget__setParentView_impl_View";
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
      case 891:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__DockWidget__registerVirtualMethodCallback')
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
    final callback891 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            DockWidget.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback891, 891);
  }
}
