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

class Group extends Controller {
  Group.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Group.init() : super.init() {}
  factory Group.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Group;
    }
    return Group.fromCppPointer(cppPointer, needsAutoDelete);
  } //Group(KDDockWidgets::View * parent)
  Group({required View? parent}) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__constructor_View')
        .asFunction();
    thisCpp = func(parent == null ? ffi.nullptr : parent.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // actualTitleBar() const
  TitleBar actualTitleBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__actualTitleBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TitleBar.fromCppPointer(result, false);
  } // actualTitleBarChanged()

  actualTitleBarChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__actualTitleBarChanged')
        .asFunction();
    func(thisCpp);
  } // addTab(KDDockWidgets::Controllers::DockWidget * arg__1, KDDockWidgets::InitialOption arg__2)

  addTab(DockWidget? arg__1, {required InitialOption arg__2}) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__addTab_DockWidget_InitialOption')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
  } // addTab(KDDockWidgets::Controllers::FloatingWindow * floatingWindow, KDDockWidgets::InitialOption arg__2)

  addTab_2(FloatingWindow? floatingWindow, {required InitialOption arg__2}) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__addTab_FloatingWindow_InitialOption')
        .asFunction();
    func(thisCpp, floatingWindow == null ? ffi.nullptr : floatingWindow.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
  } // addTab(KDDockWidgets::Controllers::Group * arg__1, KDDockWidgets::InitialOption arg__2)

  addTab_3(Group? arg__1, {required InitialOption arg__2}) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__addTab_Group_InitialOption')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
  } // allDockWidgetsHave(KDDockWidgets::DockWidgetOption arg__1) const

  bool allDockWidgetsHave(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__allDockWidgetsHave_DockWidgetOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // allDockWidgetsHave(KDDockWidgets::LayoutSaverOption arg__1) const

  bool allDockWidgetsHave_2(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__allDockWidgetsHave_LayoutSaverOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // alwaysShowsTabs() const

  bool alwaysShowsTabs() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__alwaysShowsTabs')
        .asFunction();
    return func(thisCpp) != 0;
  } // anyDockWidgetsHas(KDDockWidgets::DockWidgetOption arg__1) const

  bool anyDockWidgetsHas(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__anyDockWidgetsHas_DockWidgetOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyDockWidgetsHas(KDDockWidgets::LayoutSaverOption arg__1) const

  bool anyDockWidgetsHas_2(int arg__1) {
    final bool_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__anyDockWidgetsHas_LayoutSaverOption')
        .asFunction();
    return func(thisCpp, arg__1) != 0;
  } // anyNonClosable() const

  bool anyNonClosable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__anyNonClosable')
        .asFunction();
    return func(thisCpp) != 0;
  } // anyNonDockable() const

  bool anyNonDockable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__anyNonDockable')
        .asFunction();
    return func(thisCpp) != 0;
  } // beingDeletedLater() const

  bool beingDeletedLater() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__beingDeletedLater')
        .asFunction();
    return func(thisCpp) != 0;
  } // biggestDockWidgetMaxSize() const

  QSize biggestDockWidgetMaxSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__biggestDockWidgetMaxSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // containsDockWidget(KDDockWidgets::Controllers::DockWidget * w) const

  bool containsDockWidget(DockWidget? w) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__containsDockWidget_DockWidget')
        .asFunction();
    return func(thisCpp, w == null ? ffi.nullptr : w.thisCpp) != 0;
  } // containsMouse(QPoint globalPos) const

  bool containsMouse(QPoint globalPos) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__containsMouse_QPoint')
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp) !=
        0;
  } // currentDockWidget() const

  DockWidget currentDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__currentDockWidget')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
  } // currentIndex() const

  int currentIndex() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__currentIndex')
        .asFunction();
    return func(thisCpp);
  } // currentTabIndex() const

  int currentTabIndex() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__currentTabIndex')
        .asFunction();
    return func(thisCpp);
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }

  static // dbg_numFrames()
      int dbg_numFrames() {
    final int_Func_void func = _dylib
        .lookup<ffi.NativeFunction<int_Func_void_FFI>>(
            'c_static_KDDockWidgets__Controllers__Group__dbg_numFrames')
        .asFunction();
    return func();
  } // detachTab(KDDockWidgets::Controllers::DockWidget * arg__1)

  FloatingWindow detachTab(DockWidget? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__detachTab_DockWidget')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return FloatingWindow.fromCppPointer(result, false);
  } // dockWidgetAt(int index) const

  DockWidget dockWidgetAt(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__dockWidgetAt_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return DockWidget.fromCppPointer(result, false);
  } // dockWidgetCount() const

  int dockWidgetCount() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__dockWidgetCount')
        .asFunction();
    return func(thisCpp);
  } // dockWidgetsMinSize() const

  QSize dockWidgetsMinSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__dockWidgetsMinSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // dragRect() const

  QRect dragRect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1353))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> dragRect_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::dragRect() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.dragRect();
    return result.thisCpp;
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // floatingWindow() const

  FloatingWindow floatingWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__floatingWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return FloatingWindow.fromCppPointer(result, false);
  } // focusedWidgetChanged()

  focusedWidgetChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__focusedWidgetChanged')
        .asFunction();
    func(thisCpp);
  } // focusedWidgetChangedCallback()

  focusedWidgetChangedCallback() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1356))
        .asFunction();
    func(thisCpp);
  }

  static void focusedWidgetChangedCallback_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::focusedWidgetChangedCallback()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.focusedWidgetChangedCallback();
  } // hasNestedMDIDockWidgets() const

  bool hasNestedMDIDockWidgets() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__hasNestedMDIDockWidgets')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasSingleDockWidget() const

  bool hasSingleDockWidget() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__hasSingleDockWidget')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasTabsVisible() const

  bool hasTabsVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__hasTabsVisible')
        .asFunction();
    return func(thisCpp) != 0;
  } // hasTabsVisibleChanged()

  hasTabsVisibleChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__hasTabsVisibleChanged')
        .asFunction();
    func(thisCpp);
  } // indexOfDockWidget(const KDDockWidgets::Controllers::DockWidget * arg__1)

  int indexOfDockWidget(DockWidget? arg__1) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__indexOfDockWidget_DockWidget')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // insertDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1, int index)

  insertDockWidget(DockWidget? arg__1, int index) {
    final void_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__insertDockWidget_DockWidget_int')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, index);
  } // insertWidget(KDDockWidgets::Controllers::DockWidget * arg__1, int index, KDDockWidgets::InitialOption arg__3)

  insertWidget(DockWidget? arg__1, int index, {required InitialOption arg__3}) {
    final void_Func_voidstar_voidstar_int_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__insertWidget_DockWidget_int_InitialOption')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, index,
        arg__3 == null ? ffi.nullptr : arg__3.thisCpp);
  } // isCentralFrame() const

  bool isCentralFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isCentralFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // isDockable() const

  bool isDockable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isDockable')
        .asFunction();
    return func(thisCpp) != 0;
  } // isEmpty() const

  bool isEmpty() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isEmpty')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFloating() const

  bool isFloating() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isFloating')
        .asFunction();
    return func(thisCpp) != 0;
  } // isFocusedChanged()

  isFocusedChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isFocusedChanged')
        .asFunction();
    func(thisCpp);
  } // isFocusedChangedCallback()

  isFocusedChangedCallback() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1373))
        .asFunction();
    func(thisCpp);
  }

  static void isFocusedChangedCallback_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isFocusedChangedCallback()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.isFocusedChangedCallback();
  } // isInFloatingWindow() const

  bool isInFloatingWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isInFloatingWindow')
        .asFunction();
    return func(thisCpp) != 0;
  } // isInMainWindow() const

  bool isInMainWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isInMainWindow')
        .asFunction();
    return func(thisCpp) != 0;
  } // isInMainWindowChanged()

  isInMainWindowChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isInMainWindowChanged')
        .asFunction();
    func(thisCpp);
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isMDI')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMDIChanged()

  isMDIChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isMDIChanged')
        .asFunction();
    func(thisCpp);
  } // isMDIWrapper() const

  bool isMDIWrapper() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isMDIWrapper')
        .asFunction();
    return func(thisCpp) != 0;
  } // isOverlayed() const

  bool isOverlayed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isOverlayed')
        .asFunction();
    return func(thisCpp) != 0;
  } // isTheOnlyFrame() const

  bool isTheOnlyFrame() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__isTheOnlyFrame')
        .asFunction();
    return func(thisCpp) != 0;
  } // layoutItem() const

  Item layoutItem() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__layoutItem')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Item.fromCppPointer(result, false);
  } // mdiDockWidgetWrapper() const

  DockWidget mdiDockWidgetWrapper() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__mdiDockWidgetWrapper')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
  } // mdiDropAreaWrapper() const

  DropArea mdiDropAreaWrapper() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__mdiDropAreaWrapper')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  } // mdiFrame() const

  Group mdiFrame() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__mdiFrame')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // nonContentsHeight() const

  int nonContentsHeight() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__nonContentsHeight')
        .asFunction();
    return func(thisCpp);
  } // numDockWidgetsChanged()

  numDockWidgetsChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__numDockWidgetsChanged')
        .asFunction();
    func(thisCpp);
  } // onCurrentTabChanged(int index)

  onCurrentTabChanged(int index) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__onCurrentTabChanged_int')
        .asFunction();
    func(thisCpp, index);
  } // onDockWidgetCountChanged()

  onDockWidgetCountChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__onDockWidgetCountChanged')
        .asFunction();
    func(thisCpp);
  } // onDockWidgetHidden(KDDockWidgets::Controllers::DockWidget * w)

  onDockWidgetHidden(DockWidget? w) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__onDockWidgetHidden_DockWidget')
        .asFunction();
    func(thisCpp, w == null ? ffi.nullptr : w.thisCpp);
  } // onDockWidgetShown(KDDockWidgets::Controllers::DockWidget * w)

  onDockWidgetShown(DockWidget? w) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__onDockWidgetShown_DockWidget')
        .asFunction();
    func(thisCpp, w == null ? ffi.nullptr : w.thisCpp);
  } // onDockWidgetTitleChanged()

  onDockWidgetTitleChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__onDockWidgetTitleChanged')
        .asFunction();
    func(thisCpp);
  } // removeWidget(KDDockWidgets::Controllers::DockWidget * arg__1)

  removeWidget(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__removeWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // renameTab(int index, const QString & arg__2)

  renameTab(int index, String? arg__2) {
    final void_Func_voidstar_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__renameTab_int_QString')
        .asFunction();
    func(thisCpp, index, arg__2?.toNativeUtf8() ?? ffi.nullptr);
  } // restoreToPreviousPosition()

  restoreToPreviousPosition() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__restoreToPreviousPosition')
        .asFunction();
    func(thisCpp);
  } // scheduleDeleteLater()

  scheduleDeleteLater() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__scheduleDeleteLater')
        .asFunction();
    func(thisCpp);
  } // setCurrentDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)

  setCurrentDockWidget(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__setCurrentDockWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setCurrentTabIndex(int index)

  setCurrentTabIndex(int index) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Group__setCurrentTabIndex_int')
        .asFunction();
    func(thisCpp, index);
  } // setLayout(KDDockWidgets::Controllers::Layout * arg__1)

  setLayout(Layout? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__setLayout_Layout')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setLayoutItem(Layouting::Item * item)

  setLayoutItem(Item? item) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__setLayoutItem_Item')
        .asFunction();
    func(thisCpp, item == null ? ffi.nullptr : item.thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // stack() const

  Stack stack() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__stack')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Stack.fromCppPointer(result, false);
  } // tabBar() const

  TabBar tabBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__tabBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TabBar.fromCppPointer(result, false);
  } // title() const

  QString title() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__title')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  } // titleBar() const

  TitleBar titleBar() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__titleBar')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return TitleBar.fromCppPointer(result, false);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__Group__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // unoverlay()

  unoverlay() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__unoverlay')
        .asFunction();
    func(thisCpp);
  } // updateFloatingActions()

  updateFloatingActions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__updateFloatingActions')
        .asFunction();
    func(thisCpp);
  } // updateTitleAndIcon()

  updateTitleAndIcon() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__updateTitleAndIcon')
        .asFunction();
    func(thisCpp);
  } // updateTitleBarVisibility()

  updateTitleBarVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__updateTitleBarVisibility')
        .asFunction();
    func(thisCpp);
  } // userType() const

  int userType() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__userType')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Group__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__Group__customEvent_QEvent";
      case 1353:
        return "c_KDDockWidgets__Controllers__Group__dragRect";
      case 306:
        return "c_KDDockWidgets__Controllers__Group__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__Group__eventFilter_QObject_QEvent";
      case 1356:
        return "c_KDDockWidgets__Controllers__Group__focusedWidgetChangedCallback";
      case 1373:
        return "c_KDDockWidgets__Controllers__Group__isFocusedChangedCallback";
      case 826:
        return "c_KDDockWidgets__Controllers__Group__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 1353:
        return "dragRect";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 1356:
        return "focusedWidgetChangedCallback";
      case 1373:
        return "isFocusedChangedCallback";
      case 826:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__Group__registerVirtualMethodCallback')
        .asFunction();
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    final callback1353 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Group.dragRect_calledFromC);
    registerCallback(thisCpp, callback1353, 1353);
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
    final callback1356 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Group.focusedWidgetChangedCallback_calledFromC);
    registerCallback(thisCpp, callback1356, 1356);
    final callback1373 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Group.isFocusedChangedCallback_calledFromC);
    registerCallback(thisCpp, callback1373, 1373);
    final callback826 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Group.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback826, 826);
  }
}
