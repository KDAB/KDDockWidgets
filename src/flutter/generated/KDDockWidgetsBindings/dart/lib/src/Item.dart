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

class Item extends QObject {
  Item.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Item.init() : super.init() {}
  factory Item.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Item;
    }
    return Item.fromCppPointer(cppPointer, needsAutoDelete);
  }
  static int get separatorThickness {
    final int_Func_void func = _dylib
        .lookup<ffi.NativeFunction<int_Func_void_FFI>>(
            'c_static_Layouting__Item___get_separatorThickness')
        .asFunction();
    return func();
  }

  static set separatorThickness(int separatorThickness_) {
    final void_Func_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int32_FFI>>(
            'c_static_Layouting__Item___set_separatorThickness_int')
        .asFunction();
    func(separatorThickness_);
  }

  static bool get s_silenceSanityChecks {
    final bool_Func_void func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_void_FFI>>(
            'c_static_Layouting__Item___get_s_silenceSanityChecks')
        .asFunction();
    return func() != 0;
  }

  static set s_silenceSanityChecks(bool s_silenceSanityChecks_) {
    final void_Func_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int8_FFI>>(
            'c_static_Layouting__Item___set_s_silenceSanityChecks_bool')
        .asFunction();
    func(s_silenceSanityChecks_ ? 1 : 0);
  } //Item(KDDockWidgets::View * hostWidget)

  Item(View? hostWidget) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__constructor_View')
        .asFunction();
    thisCpp = func(hostWidget == null ? ffi.nullptr : hostWidget.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // asGroupController() const
  Group asGroupController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__asGroupController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Group.fromCppPointer(result, false);
  } // checkSanity()

  bool checkSanity() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(576))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int checkSanity_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::checkSanity()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.checkSanity();
    return result ? 1 : 0;
  } // dumpLayout(int level)

  dumpLayout({int level = 0}) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(583))
        .asFunction();
    func(thisCpp, level);
  }

  static void dumpLayout_calledFromC(ffi.Pointer<void> thisCpp, int level) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::dumpLayout(int level)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.dumpLayout(level: level);
  } // geometry() const

  QRect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__geometry')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // guestView() const

  View guestView() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__guestView')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return View.fromCppPointer(result, false);
  } // height() const

  int height() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__height')
        .asFunction();
    return func(thisCpp);
  } // hostView() const

  View hostView() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__hostView')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return View.fromCppPointer(result, false);
  } // isBeingInserted() const

  bool isBeingInserted() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isBeingInserted')
        .asFunction();
    return func(thisCpp) != 0;
  } // isContainer() const

  bool isContainer() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isContainer')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isMDI')
        .asFunction();
    return func(thisCpp) != 0;
  } // isPlaceholder() const

  bool isPlaceholder() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isPlaceholder')
        .asFunction();
    return func(thisCpp) != 0;
  } // isRoot() const

  bool isRoot() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_Layouting__Item__isRoot')
        .asFunction();
    return func(thisCpp) != 0;
  } // isVisible(bool excludeBeingInserted) const

  bool isVisible({bool excludeBeingInserted = false}) {
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(600))
        .asFunction();
    return func(thisCpp, excludeBeingInserted ? 1 : 0) != 0;
  }

  static int isVisible_calledFromC(
      ffi.Pointer<void> thisCpp, int excludeBeingInserted) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::isVisible(bool excludeBeingInserted) const! (${thisCpp.address})");
      throw Error();
    }
    final result =
        dartInstance.isVisible(excludeBeingInserted: excludeBeingInserted != 0);
    return result ? 1 : 0;
  } // mapFromParent(QPoint arg__1) const

  QPoint mapFromParent(QPoint arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapFromParent_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // mapFromRoot(QPoint arg__1) const

  QPoint mapFromRoot(QPoint arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapFromRoot_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // mapFromRoot(QRect arg__1) const

  QRect mapFromRoot_2(QRect arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapFromRoot_QRect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QRect.fromCppPointer(result, true);
  } // mapToRoot(QPoint arg__1) const

  QPoint mapToRoot(QPoint arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapToRoot_QPoint')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // mapToRoot(QRect arg__1) const

  QRect mapToRoot_2(QRect arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__mapToRoot_QRect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QRect.fromCppPointer(result, true);
  } // maxSizeHint() const

  QSize maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(609))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  } // minSize() const

  QSize minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(610))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  } // missingSize() const

  QSize missingSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__missingSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // onWidgetDestroyed()

  onWidgetDestroyed() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__onWidgetDestroyed')
        .asFunction();
    func(thisCpp);
  } // onWidgetLayoutRequested()

  onWidgetLayoutRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__onWidgetLayoutRequested')
        .asFunction();
    func(thisCpp);
  } // pos() const

  QPoint pos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__pos')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // rect() const

  QRect rect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__rect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // ref()

  ref() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__ref')
        .asFunction();
    func(thisCpp);
  } // refCount() const

  int refCount() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__refCount')
        .asFunction();
    return func(thisCpp);
  } // restore(KDDockWidgets::View * guestView)

  restore(View? guestView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__restore_View')
        .asFunction();
    func(thisCpp, guestView == null ? ffi.nullptr : guestView.thisCpp);
  } // setBeingInserted(bool arg__1)

  setBeingInserted(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_Layouting__Item__setBeingInserted_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // setGeometry(QRect rect)

  setGeometry(QRect rect) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setGeometry_QRect')
        .asFunction();
    func(thisCpp, rect == null ? ffi.nullptr : rect.thisCpp);
  } // setGeometry_recursive(QRect rect)

  setGeometry_recursive(QRect rect) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(627))
        .asFunction();
    func(thisCpp, rect == null ? ffi.nullptr : rect.thisCpp);
  }

  static void setGeometry_recursive_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> rect) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setGeometry_recursive(QRect rect)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry_recursive(QRect.fromCppPointer(rect));
  } // setGuestView(KDDockWidgets::View * arg__1)

  setGuestView(View? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setGuestView_View')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setHostView(KDDockWidgets::View * arg__1)

  setHostView(View? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(629))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setHostView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setHostView(KDDockWidgets::View * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHostView(View.fromCppPointer(arg__1));
  } // setIsVisible(bool arg__1)

  setIsVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(630))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setIsVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setIsVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setIsVisible(arg__1 != 0);
  } // setMaxSizeHint(QSize arg__1)

  setMaxSizeHint(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setMaxSizeHint_QSize')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setMinSize(QSize arg__1)

  setMinSize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setMinSize_QSize')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setPos(QPoint arg__1)

  setPos(QPoint arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setPos_QPoint')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setSize(QSize arg__1)

  setSize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_Layouting__Item__setSize_QSize')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // size() const

  QSize size() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_Layouting__Item__size')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_Layouting__Item__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  } // turnIntoPlaceholder()

  turnIntoPlaceholder() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__turnIntoPlaceholder')
        .asFunction();
    func(thisCpp);
  } // unref()

  unref() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__unref')
        .asFunction();
    func(thisCpp);
  } // updateObjectName()

  updateObjectName() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__updateObjectName')
        .asFunction();
    func(thisCpp);
  } // updateWidgetGeometries()

  updateWidgetGeometries() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(644))
        .asFunction();
    func(thisCpp);
  }

  static void updateWidgetGeometries_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::updateWidgetGeometries()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updateWidgetGeometries();
  } // visibleCount_recursive() const

  int visibleCount_recursive() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(645))
        .asFunction();
    return func(thisCpp);
  }

  static int visibleCount_recursive_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = QObject.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::visibleCount_recursive() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.visibleCount_recursive();
    return result;
  } // width() const

  int width() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__width')
        .asFunction();
    return func(thisCpp);
  } // x() const

  int x() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__x')
        .asFunction();
    return func(thisCpp);
  } // y() const

  int y() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_Layouting__Item__y')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_Layouting__Item__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 576:
        return "c_Layouting__Item__checkSanity";
      case 583:
        return "c_Layouting__Item__dumpLayout_int";
      case 600:
        return "c_Layouting__Item__isVisible_bool";
      case 609:
        return "c_Layouting__Item__maxSizeHint";
      case 610:
        return "c_Layouting__Item__minSize";
      case 627:
        return "c_Layouting__Item__setGeometry_recursive_QRect";
      case 629:
        return "c_Layouting__Item__setHostView_View";
      case 630:
        return "c_Layouting__Item__setIsVisible_bool";
      case 644:
        return "c_Layouting__Item__updateWidgetGeometries";
      case 645:
        return "c_Layouting__Item__visibleCount_recursive";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 576:
        return "checkSanity";
      case 583:
        return "dumpLayout";
      case 600:
        return "isVisible";
      case 609:
        return "maxSizeHint";
      case 610:
        return "minSize";
      case 627:
        return "setGeometry_recursive";
      case 629:
        return "setHostView";
      case 630:
        return "setIsVisible";
      case 644:
        return "updateWidgetGeometries";
      case 645:
        return "visibleCount_recursive";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_Layouting__Item__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept576 = 0;
    final callback576 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Item.checkSanity_calledFromC, callbackExcept576);
    registerCallback(thisCpp, callback576, 576);
    final callback583 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Item.dumpLayout_calledFromC);
    registerCallback(thisCpp, callback583, 583);
    const callbackExcept600 = 0;
    final callback600 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int8_FFI>(
            Item.isVisible_calledFromC, callbackExcept600);
    registerCallback(thisCpp, callback600, 600);
    final callback609 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Item.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback609, 609);
    final callback610 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Item.minSize_calledFromC);
    registerCallback(thisCpp, callback610, 610);
    final callback627 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Item.setGeometry_recursive_calledFromC);
    registerCallback(thisCpp, callback627, 627);
    final callback629 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Item.setHostView_calledFromC);
    registerCallback(thisCpp, callback629, 629);
    final callback630 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            Item.setIsVisible_calledFromC);
    registerCallback(thisCpp, callback630, 630);
    final callback644 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Item.updateWidgetGeometries_calledFromC);
    registerCallback(thisCpp, callback644, 644);
    const callbackExcept645 = 0;
    final callback645 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Item.visibleCount_recursive_calledFromC, callbackExcept645);
    registerCallback(thisCpp, callback645, 645);
  }
}
