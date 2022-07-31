/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1052
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

//tag=1051
var _dylib = Library.instance().dylib;

class Item extends QObject {
//tag=1064
  Item.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Item.init() : super.init() {}
//tag=1062
  factory Item.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Item;
    }
    return Item.fromCppPointer(cppPointer, needsAutoDelete);
  }
//tag=1024
  static
//tag=1025
      int get separatorThickness {
//tag=1028
    final int_Func_void func = _dylib
        .lookup<ffi.NativeFunction<int_Func_void_FFI>>(
            'c_static_Layouting__Item___get_separatorThickness')
        .asFunction();
//tag=1031
    return func();
  }

//tag=1024
  static
//tag=1026
      set separatorThickness(int separatorThickness_) {
//tag=1028
    final void_Func_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int32_FFI>>(
            'c_static_Layouting__Item___set_separatorThickness_int')
        .asFunction();
//tag=1030
    func(separatorThickness_);
  }

//tag=1024
  static
//tag=1025
      bool get s_silenceSanityChecks {
//tag=1028
    final bool_Func_void func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_void_FFI>>(
            'c_static_Layouting__Item___get_s_silenceSanityChecks')
        .asFunction();
//tag=1029
    return func() != 0;
  }

//tag=1024
  static
//tag=1026
      set s_silenceSanityChecks(bool s_silenceSanityChecks_) {
//tag=1028
    final void_Func_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int8_FFI>>(
            'c_static_Layouting__Item___set_s_silenceSanityChecks_bool')
        .asFunction();
//tag=1030
    func(s_silenceSanityChecks_ ? 1 : 0);
  }

//tag=1023
//Item(KDDockWidgets::View * hostWidget)
  Item(View? hostWidget) : super.init() {
//tag=1075
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__constructor_View')
        .asFunction();
    thisCpp = func(hostWidget == null ? ffi.nullptr : hostWidget.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1027
// checkSanity()
  bool checkSanity() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(589))
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }

//tag=1035
  static int checkSanity_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::checkSanity()! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.checkSanity();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }
//tag=1024

//tag=1027
// dumpLayout(int level)
  dumpLayout({int level = 0}) {
//tag=1028
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(596))
        .asFunction();
//tag=1030
    func(thisCpp, level);
  }

//tag=1035
  static void dumpLayout_calledFromC(ffi.Pointer<void> thisCpp, int level) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::dumpLayout(int level)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.dumpLayout(level: level);
  }
//tag=1024

//tag=1035
  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// geometry() const
  QRect geometry() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__geometry')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// guestView() const
  View guestView() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__guestView')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return View.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// height() const
  int height() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__height')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// hostView() const
  View hostView() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__hostView')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return View.fromCppPointer(result, false);
  }
//tag=1024

//tag=1027
// isBeingInserted() const
  bool isBeingInserted() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isBeingInserted')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isContainer() const
  bool isContainer() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isContainer')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isMDI() const
  bool isMDI() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isMDI')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isPlaceholder() const
  bool isPlaceholder() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isPlaceholder')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isRoot() const
  bool isRoot() {
//tag=1028
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isRoot')
        .asFunction();
//tag=1029
    return func(thisCpp) != 0;
  }
//tag=1024

//tag=1027
// isVisible(bool excludeBeingInserted) const
  bool isVisible({bool excludeBeingInserted = false}) {
//tag=1028
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(613))
        .asFunction();
//tag=1029
    return func(thisCpp, excludeBeingInserted ? 1 : 0) != 0;
  }

//tag=1035
  static int isVisible_calledFromC(
      ffi.Pointer<void> thisCpp, int excludeBeingInserted) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::isVisible(bool excludeBeingInserted) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result =
        dartInstance.isVisible(excludeBeingInserted: excludeBeingInserted != 0);
    return result ? 1 : 0;
  }
//tag=1024

//tag=1027
// mapFromParent(QPoint arg__1) const
  QPoint mapFromParent(QPoint arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapFromParent_QPoint')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// mapFromRoot(QPoint arg__1) const
  QPoint mapFromRoot(QPoint arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapFromRoot_QPoint')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// mapFromRoot(QRect arg__1) const
  QRect mapFromRoot_2(QRect arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapFromRoot_QRect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// mapToRoot(QPoint arg__1) const
  QPoint mapToRoot(QPoint arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapToRoot_QPoint')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// mapToRoot(QRect arg__1) const
  QRect mapToRoot_2(QRect arg__1) {
//tag=1028
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapToRoot_QRect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// maxSizeHint() const
  QSize maxSizeHint() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(622))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// minSize() const
  QSize minSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(623))
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1035
  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::minSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minSize();
    return result.thisCpp;
  }
//tag=1024

//tag=1027
// missingSize() const
  QSize missingSize() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__missingSize')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// onWidgetDestroyed()
  onWidgetDestroyed() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__onWidgetDestroyed')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// onWidgetLayoutRequested()
  onWidgetLayoutRequested() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__onWidgetLayoutRequested')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// pos() const
  QPoint pos() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__pos')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// rect() const
  QRect rect() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__rect')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// ref()
  ref() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__ref')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// refCount() const
  int refCount() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__refCount')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// restore(KDDockWidgets::View * guestView)
  restore(View? guestView) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__restore_View')
        .asFunction();
//tag=1030
    func(thisCpp, guestView == null ? ffi.nullptr : guestView.thisCpp);
  }
//tag=1024

//tag=1027
// setBeingInserted(bool arg__1)
  setBeingInserted(bool arg__1) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_Layouting__Item__setBeingInserted_bool')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 ? 1 : 0);
  }
//tag=1024

//tag=1027
// setGeometry(QRect rect)
  setGeometry(QRect rect) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setGeometry_QRect')
        .asFunction();
//tag=1030
    func(thisCpp, rect == null ? ffi.nullptr : rect.thisCpp);
  }
//tag=1024

//tag=1027
// setGeometry_recursive(QRect rect)
  setGeometry_recursive(QRect rect) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(640))
        .asFunction();
//tag=1030
    func(thisCpp, rect == null ? ffi.nullptr : rect.thisCpp);
  }

//tag=1035
  static void setGeometry_recursive_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> rect) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setGeometry_recursive(QRect rect)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setGeometry_recursive(QRect.fromCppPointer(rect));
  }
//tag=1024

//tag=1027
// setGuestView(KDDockWidgets::View * arg__1)
  setGuestView(View? arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setGuestView_View')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// setHostView(KDDockWidgets::View * arg__1)
  setHostView(View? arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(642))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

//tag=1035
  static void setHostView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setHostView(KDDockWidgets::View * arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setHostView(View.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1027
// setIsVisible(bool arg__1)
  setIsVisible(bool arg__1) {
//tag=1028
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(643))
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 ? 1 : 0);
  }

//tag=1035
  static void setIsVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setIsVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setIsVisible(arg__1 != 0);
  }
//tag=1024

//tag=1027
// setMaxSizeHint(QSize arg__1)
  setMaxSizeHint(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setMaxSizeHint_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// setMinSize(QSize arg__1)
  setMinSize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setMinSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// setPos(QPoint arg__1)
  setPos(QPoint arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setPos_QPoint')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// setSize(QSize arg__1)
  setSize(QSize arg__1) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setSize_QSize')
        .asFunction();
//tag=1030
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }
//tag=1024

//tag=1027
// size() const
  QSize size() {
//tag=1028
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__size')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

//tag=1024
  static
//tag=1027
// tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
//tag=1028
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_Layouting__Item__tr_char_char_int')
        .asFunction();
//tag=1033
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }
//tag=1024

//tag=1027
// turnIntoPlaceholder()
  turnIntoPlaceholder() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__turnIntoPlaceholder')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// unref()
  unref() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__unref')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// updateObjectName()
  updateObjectName() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__updateObjectName')
        .asFunction();
//tag=1030
    func(thisCpp);
  }
//tag=1024

//tag=1027
// updateWidgetGeometries()
  updateWidgetGeometries() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(657))
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1035
  static void updateWidgetGeometries_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::updateWidgetGeometries()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.updateWidgetGeometries();
  }
//tag=1024

//tag=1027
// visibleCount_recursive() const
  int visibleCount_recursive() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(658))
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1035
  static int visibleCount_recursive_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::visibleCount_recursive() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.visibleCount_recursive();
    return result;
  }
//tag=1024

//tag=1027
// width() const
  int width() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__width')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// x() const
  int x() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__x')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }
//tag=1024

//tag=1027
// y() const
  int y() {
//tag=1028
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__y')
        .asFunction();
//tag=1031
    return func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 589:
        return "c_Layouting__Item__checkSanity";
      case 295:
        return "c_Layouting__Item__customEvent_QEvent";
      case 596:
        return "c_Layouting__Item__dumpLayout_int";
      case 306:
        return "c_Layouting__Item__event_QEvent";
      case 307:
        return "c_Layouting__Item__eventFilter_QObject_QEvent";
      case 613:
        return "c_Layouting__Item__isVisible_bool";
      case 622:
        return "c_Layouting__Item__maxSizeHint";
      case 623:
        return "c_Layouting__Item__minSize";
      case 640:
        return "c_Layouting__Item__setGeometry_recursive_QRect";
      case 642:
        return "c_Layouting__Item__setHostView_View";
      case 643:
        return "c_Layouting__Item__setIsVisible_bool";
      case 657:
        return "c_Layouting__Item__updateWidgetGeometries";
      case 658:
        return "c_Layouting__Item__visibleCount_recursive";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 589:
        return "checkSanity";
      case 295:
        return "customEvent";
      case 596:
        return "dumpLayout";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
      case 613:
        return "isVisible";
      case 622:
        return "maxSizeHint";
      case 623:
        return "minSize";
      case 640:
        return "setGeometry_recursive";
      case 642:
        return "setHostView";
      case 643:
        return "setIsVisible";
      case 657:
        return "updateWidgetGeometries";
      case 658:
        return "visibleCount_recursive";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_Layouting__Item__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept589 = 0;
//tag=1021
    final callback589 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Item.checkSanity_calledFromC, callbackExcept589);
    registerCallback(thisCpp, callback589, 589);
//tag=1021
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
//tag=1021
    final callback596 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Item.dumpLayout_calledFromC);
    registerCallback(thisCpp, callback596, 596);
    const callbackExcept306 = 0;
//tag=1021
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
    const callbackExcept307 = 0;
//tag=1021
    final callback307 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept307);
    registerCallback(thisCpp, callback307, 307);
    const callbackExcept613 = 0;
//tag=1021
    final callback613 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int8_FFI>(
            Item.isVisible_calledFromC, callbackExcept613);
    registerCallback(thisCpp, callback613, 613);
//tag=1021
    final callback622 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Item.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback622, 622);
//tag=1021
    final callback623 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Item.minSize_calledFromC);
    registerCallback(thisCpp, callback623, 623);
//tag=1021
    final callback640 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Item.setGeometry_recursive_calledFromC);
    registerCallback(thisCpp, callback640, 640);
//tag=1021
    final callback642 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Item.setHostView_calledFromC);
    registerCallback(thisCpp, callback642, 642);
//tag=1021
    final callback643 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            Item.setIsVisible_calledFromC);
    registerCallback(thisCpp, callback643, 643);
//tag=1021
    final callback657 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Item.updateWidgetGeometries_calledFromC);
    registerCallback(thisCpp, callback657, 657);
    const callbackExcept658 = 0;
//tag=1021
    final callback658 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Item.visibleCount_recursive_calledFromC, callbackExcept658);
    registerCallback(thisCpp, callback658, 658);
  }
}
