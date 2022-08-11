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

class TabBar extends Controller {
  TabBar.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TabBar.init() : super.init() {}
  factory TabBar.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TabBar;
    }
    return TabBar.fromCppPointer(cppPointer, needsAutoDelete);
  } //TabBar(KDDockWidgets::Controllers::Stack * tabWidget)
  TabBar({required Stack? tabWidget}) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__constructor_Stack')
        .asFunction();
    thisCpp = func(tabWidget == null ? ffi.nullptr : tabWidget.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // currentDockWidget() const
  DockWidget currentDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__currentDockWidget')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  } // dockWidgetAt(QPoint localPos) const

  DockWidget dockWidgetAt(QPoint localPos) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__dockWidgetAt_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp);
    return DockWidget.fromCppPointer(result, false);
  } // dockWidgetAt(int index) const

  DockWidget dockWidgetAt_2(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__dockWidgetAt_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return DockWidget.fromCppPointer(result, false);
  } // dragCanStart(QPoint pressPos, QPoint pos) const

  bool dragCanStart(QPoint pressPos, QPoint pos) {
    final bool_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1089))
        .asFunction();
    return func(thisCpp, pressPos == null ? ffi.nullptr : pressPos.thisCpp,
            pos == null ? ffi.nullptr : pos.thisCpp) !=
        0;
  }

  static int dragCanStart_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> pressPos, ffi.Pointer<void> pos) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::dragCanStart(QPoint pressPos, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.dragCanStart(
        QPoint.fromCppPointer(pressPos), QPoint.fromCppPointer(pos));
    return result ? 1 : 0;
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  } // group() const

  Group group() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__group')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // hasSingleDockWidget() const

  bool hasSingleDockWidget() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__hasSingleDockWidget')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1096))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMDI_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isMDI() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMDI();
    return result ? 1 : 0;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1098))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // moveTabTo(int from, int to)

  moveTabTo(int from, int to) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__moveTabTo_int_int')
        .asFunction();
    func(thisCpp, from, to);
  } // numDockWidgets() const

  int numDockWidgets() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__numDockWidgets')
        .asFunction();
    return func(thisCpp);
  } // onMouseDoubleClick(QPoint localPos)

  onMouseDoubleClick(QPoint localPos) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__onMouseDoubleClick_QPoint')
        .asFunction();
    func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp);
  } // onMousePress(QPoint localPos)

  onMousePress(QPoint localPos) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__onMousePress_QPoint')
        .asFunction();
    func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp);
  } // rectForTab(int index) const

  QRect rectForTab(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__rectForTab_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return QRect.fromCppPointer(result, true);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setParentView_impl(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // singleDockWidget() const

  DockWidget singleDockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1111))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DockWidget.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> singleDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::singleDockWidget() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.singleDockWidget();
    return result.thisCpp;
  } // stack() const

  Stack stack() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__stack')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Stack.fromCppPointer(result, false);
  } // tabsAreMovable() const

  bool tabsAreMovable() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__tabsAreMovable')
        .asFunction();
    return func(thisCpp) != 0;
  } // text(int index) const

  QString text(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__text_int')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return QString.fromCppPointer(result, true);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Controllers__TabBar__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 295:
        return "c_KDDockWidgets__Controllers__TabBar__customEvent_QEvent";
      case 1089:
        return "c_KDDockWidgets__Controllers__TabBar__dragCanStart_QPoint_QPoint";
      case 306:
        return "c_KDDockWidgets__Controllers__TabBar__event_QEvent";
      case 307:
        return "c_KDDockWidgets__Controllers__TabBar__eventFilter_QObject_QEvent";
      case 1096:
        return "c_KDDockWidgets__Controllers__TabBar__isMDI";
      case 1098:
        return "c_KDDockWidgets__Controllers__TabBar__isWindow";
      case 826:
        return "c_KDDockWidgets__Controllers__TabBar__setParentView_impl_View";
      case 1111:
        return "c_KDDockWidgets__Controllers__TabBar__singleDockWidget";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 295:
        return "customEvent";
      case 1089:
        return "dragCanStart";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 1096:
        return "isMDI";
      case 1098:
        return "isWindow";
      case 826:
        return "setParentView_impl";
      case 1111:
        return "singleDockWidget";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__TabBar__registerVirtualMethodCallback')
        .asFunction();
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    const callbackExcept1089 = 0;
    final callback1089 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            TabBar.dragCanStart_calledFromC, callbackExcept1089);
    registerCallback(thisCpp, callback1089, 1089);
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
    const callbackExcept1096 = 0;
    final callback1096 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TabBar.isMDI_calledFromC, callbackExcept1096);
    registerCallback(thisCpp, callback1096, 1096);
    const callbackExcept1098 = 0;
    final callback1098 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TabBar.isWindow_calledFromC, callbackExcept1098);
    registerCallback(thisCpp, callback1098, 1098);
    final callback826 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback826, 826);
    final callback1111 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        TabBar.singleDockWidget_calledFromC);
    registerCallback(thisCpp, callback1111, 1111);
  }
}
