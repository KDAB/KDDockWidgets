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

class DockRegistry extends QObject {
  DockRegistry.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DockRegistry.init() : super.init() {}
  factory DockRegistry.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DockRegistry;
    }
    return DockRegistry.fromCppPointer(cppPointer, needsAutoDelete);
  } // checkSanityAll(bool dumpDebug)
  checkSanityAll({bool dumpDebug = false}) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__DockRegistry__checkSanityAll_bool')
        .asFunction();
    func(thisCpp, dumpDebug ? 1 : 0);
  } // clear()

  clear() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__clear')
        .asFunction();
    func(thisCpp);
  } // containsDockWidget(const QString & uniqueName) const

  bool containsDockWidget(String? uniqueName) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__containsDockWidget_QString')
        .asFunction();
    return func(thisCpp, uniqueName?.toNativeUtf8() ?? ffi.nullptr) != 0;
  } // containsMainWindow(const QString & uniqueName) const

  bool containsMainWindow(String? uniqueName) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__containsMainWindow_QString')
        .asFunction();
    return func(thisCpp, uniqueName?.toNativeUtf8() ?? ffi.nullptr) != 0;
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockRegistry;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockRegistry::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  } // dockByName(const QString & arg__1) const

  DockWidget dockByName(String? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__dockByName_QString')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return DockWidget.fromCppPointer(result, false);
  } // dropIndicatorsInhibitedChanged(bool inhibited)

  dropIndicatorsInhibitedChanged(bool inhibited) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__DockRegistry__dropIndicatorsInhibitedChanged_bool')
        .asFunction();
    func(thisCpp, inhibited ? 1 : 0);
  } // ensureAllFloatingWidgetsAreMorphed()

  ensureAllFloatingWidgetsAreMorphed() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__ensureAllFloatingWidgetsAreMorphed')
        .asFunction();
    func(thisCpp);
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockRegistry;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockRegistry::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as DockRegistry;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockRegistry::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // focusedDockWidget() const

  DockWidget focusedDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__focusedDockWidget')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
  } // groupInMDIResize() const

  Group groupInMDIResize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__groupInMDIResize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // groupInMDIResizeChanged()

  groupInMDIResizeChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__groupInMDIResizeChanged')
        .asFunction();
    func(thisCpp);
  } // groups() const

  QList groups() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__groups')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QList<Group>.fromCppPointer(result, true);
  } // hasFloatingWindows() const

  bool hasFloatingWindows() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__hasFloatingWindows')
        .asFunction();
    return func(thisCpp) != 0;
  } // isEmpty(bool excludeBeingDeleted) const

  bool isEmpty({bool excludeBeingDeleted = false}) {
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__DockRegistry__isEmpty_bool')
        .asFunction();
    return func(thisCpp, excludeBeingDeleted ? 1 : 0) != 0;
  } // isSane() const

  bool isSane() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__isSane')
        .asFunction();
    return func(thisCpp) != 0;
  } // itemIsInMainWindow(const Layouting::Item * arg__1) const

  bool itemIsInMainWindow(Item? arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__itemIsInMainWindow_Item')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // layoutForItem(const Layouting::Item * arg__1) const

  Layout layoutForItem(Item? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__layoutForItem_Item')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Layout.fromCppPointer(result, false);
  } // mainWindowByName(const QString & arg__1) const

  MainWindow mainWindowByName(String? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__mainWindowByName_QString')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
    return MainWindow.fromCppPointer(result, false);
  } // maybeDelete()

  maybeDelete() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__maybeDelete')
        .asFunction();
    func(thisCpp);
  } // registerDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)

  registerDockWidget(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__registerDockWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // registerFloatingWindow(KDDockWidgets::Controllers::FloatingWindow * arg__1)

  registerFloatingWindow(FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__registerFloatingWindow_FloatingWindow')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // registerGroup(KDDockWidgets::Controllers::Group * arg__1)

  registerGroup(Group? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__registerGroup_Group')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // registerLayout(KDDockWidgets::Controllers::Layout * arg__1)

  registerLayout(Layout? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__registerLayout_Layout')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // registerMainWindow(KDDockWidgets::Controllers::MainWindow * arg__1)

  registerMainWindow(MainWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__registerMainWindow_MainWindow')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static // self()
      DockRegistry self() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__DockRegistry__self')
        .asFunction();
    ffi.Pointer<void> result = func();
    return DockRegistry.fromCppPointer(result, false);
  } // setFocusedDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)

  setFocusedDockWidget(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__setFocusedDockWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // sideBarForDockWidget(const KDDockWidgets::Controllers::DockWidget * arg__1) const

  SideBar sideBarForDockWidget(DockWidget? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__sideBarForDockWidget_DockWidget')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return SideBar.fromCppPointer(result, false);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__DockRegistry__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // unregisterDockWidget(KDDockWidgets::Controllers::DockWidget * arg__1)

  unregisterDockWidget(DockWidget? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__unregisterDockWidget_DockWidget')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // unregisterFloatingWindow(KDDockWidgets::Controllers::FloatingWindow * arg__1)

  unregisterFloatingWindow(FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__unregisterFloatingWindow_FloatingWindow')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // unregisterGroup(KDDockWidgets::Controllers::Group * arg__1)

  unregisterGroup(Group? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__unregisterGroup_Group')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // unregisterLayout(KDDockWidgets::Controllers::Layout * arg__1)

  unregisterLayout(Layout? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__unregisterLayout_Layout')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // unregisterMainWindow(KDDockWidgets::Controllers::MainWindow * arg__1)

  unregisterMainWindow(MainWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__unregisterMainWindow_MainWindow')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__DockRegistry__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__DockRegistry__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__DockRegistry__event_QEvent";
      case 307:
        return "c_KDDockWidgets__DockRegistry__eventFilter_QObject_QEvent";
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
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__DockRegistry__registerVirtualMethodCallback')
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
  }
}
