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
import '../Bindings_KDDWBindingsCore.dart' as KDDWBindingsCore;
import '../Bindings_KDDWBindingsFlutter.dart' as KDDWBindingsFlutter;
import '../LibraryLoader.dart';

var _dylib = Library.instance().dylib;

class Item extends KDDWBindingsCore.Object {
  Item.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Item.init() : super.init() {}
  factory Item.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.Object.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.Object.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Item;
    }
    return Item.fromCppPointer(cppPointer, needsAutoDelete);
  }
  static int get separatorThickness {
    final int_Func_void func = _dylib
        .lookup<ffi.NativeFunction<int_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Item___get_separatorThickness')
        .asFunction();
    return func();
  }

  static set separatorThickness(int separatorThickness_) {
    final void_Func_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__Item___set_separatorThickness_int')
        .asFunction();
    func(separatorThickness_);
  }

  static bool get s_silenceSanityChecks {
    final bool_Func_void func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Item___get_s_silenceSanityChecks')
        .asFunction();
    return func() != 0;
  }

  static set s_silenceSanityChecks(bool s_silenceSanityChecks_) {
    final void_Func_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int8_FFI>>(
            'c_static_KDDockWidgets__Core__Item___set_s_silenceSanityChecks_bool')
        .asFunction();
    func(s_silenceSanityChecks_ ? 1 : 0);
  }

  bool get m_isContainer {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item___get_m_isContainer')
        .asFunction();
    return func(thisCpp) != 0;
  }

  bool get m_isSettingGuest {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item___get_m_isSettingGuest')
        .asFunction();
    return func(thisCpp) != 0;
  }

  set m_isSettingGuest(bool m_isSettingGuest_) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__Item___set_m_isSettingGuest_bool')
        .asFunction();
    func(thisCpp, m_isSettingGuest_ ? 1 : 0);
  }

  bool get m_inDtor {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item___get_m_inDtor')
        .asFunction();
    return func(thisCpp) != 0;
  }

  set m_inDtor(bool m_inDtor_) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__Item___set_m_inDtor_bool')
        .asFunction();
    func(thisCpp, m_inDtor_ ? 1 : 0);
  } //Item(KDDockWidgets::Core::View * hostWidget)

  Item(KDDWBindingsCore.View? hostWidget) : super.init() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__constructor_View')
        .asFunction();
    thisCpp = func(hostWidget == null ? ffi.nullptr : hostWidget.thisCpp);
    KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // asGroupController() const
  KDDWBindingsCore.Group asGroupController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__asGroupController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // checkSanity()

  bool checkSanity() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(255))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int checkSanity_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
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
            cFunctionSymbolName(256))
        .asFunction();
    func(thisCpp, level);
  }

  static void dumpLayout_calledFromC(ffi.Pointer<void> thisCpp, int level) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::dumpLayout(int level)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.dumpLayout(level: level);
  } // geometry() const

  Rect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__geometry')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
  } // guestView() const

  KDDWBindingsCore.View guestView() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__guestView')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  } // height() const

  int height() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__height')
        .asFunction();
    return func(thisCpp);
  } // hostView() const

  KDDWBindingsCore.View hostView() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__hostView')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  } // isBeingInserted() const

  bool isBeingInserted() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__isBeingInserted')
        .asFunction();
    return func(thisCpp) != 0;
  } // isContainer() const

  bool isContainer() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__isContainer')
        .asFunction();
    return func(thisCpp) != 0;
  } // isMDI() const

  bool isMDI() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__isMDI')
        .asFunction();
    return func(thisCpp) != 0;
  } // isPlaceholder() const

  bool isPlaceholder() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__isPlaceholder')
        .asFunction();
    return func(thisCpp) != 0;
  } // isRoot() const

  bool isRoot() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__isRoot')
        .asFunction();
    return func(thisCpp) != 0;
  } // isVisible(bool excludeBeingInserted) const

  bool isVisible({bool excludeBeingInserted = false}) {
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(266))
        .asFunction();
    return func(thisCpp, excludeBeingInserted ? 1 : 0) != 0;
  }

  static int isVisible_calledFromC(
      ffi.Pointer<void> thisCpp, int excludeBeingInserted) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::isVisible(bool excludeBeingInserted) const! (${thisCpp.address})");
      throw Error();
    }
    final result =
        dartInstance.isVisible(excludeBeingInserted: excludeBeingInserted != 0);
    return result ? 1 : 0;
  } // mapFromParent(KDDockWidgets::Point arg__1) const

  Point mapFromParent(Point arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__mapFromParent_Point')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Point.fromCppPointer(result, true);
  } // mapFromRoot(KDDockWidgets::Point arg__1) const

  Point mapFromRoot(Point arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__mapFromRoot_Point')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Point.fromCppPointer(result, true);
  } // mapFromRoot(KDDockWidgets::Rect arg__1) const

  Rect mapFromRoot_2(Rect arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__mapFromRoot_Rect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Rect.fromCppPointer(result, true);
  } // mapToRoot(KDDockWidgets::Point arg__1) const

  Point mapToRoot(Point arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__mapToRoot_Point')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Point.fromCppPointer(result, true);
  } // mapToRoot(KDDockWidgets::Rect arg__1) const

  Rect mapToRoot_2(Rect arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__mapToRoot_Rect')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Rect.fromCppPointer(result, true);
  } // maxSizeHint() const

  Size maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(272))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  } // minSize() const

  Size minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(273))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  } // missingSize() const

  Size missingSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__missingSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  } // onWidgetDestroyed()

  onWidgetDestroyed() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__onWidgetDestroyed')
        .asFunction();
    func(thisCpp);
  } // onWidgetLayoutRequested()

  onWidgetLayoutRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__onWidgetLayoutRequested')
        .asFunction();
    func(thisCpp);
  } // pos() const

  Point pos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__pos')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // rect() const

  Rect rect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__rect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
  } // ref()

  ref() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__ref')
        .asFunction();
    func(thisCpp);
  } // refCount() const

  int refCount() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__refCount')
        .asFunction();
    return func(thisCpp);
  } // restore(KDDockWidgets::Core::View * guestView)

  restore(KDDWBindingsCore.View? guestView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__restore_View')
        .asFunction();
    func(thisCpp, guestView == null ? ffi.nullptr : guestView.thisCpp);
  } // setBeingInserted(bool arg__1)

  setBeingInserted(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Core__Item__setBeingInserted_bool')
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  } // setGeometry(KDDockWidgets::Rect rect)

  setGeometry(Rect rect) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__setGeometry_Rect')
        .asFunction();
    func(thisCpp, rect == null ? ffi.nullptr : rect.thisCpp);
  } // setGeometry_recursive(KDDockWidgets::Rect rect)

  setGeometry_recursive(Rect rect) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(287))
        .asFunction();
    func(thisCpp, rect == null ? ffi.nullptr : rect.thisCpp);
  }

  static void setGeometry_recursive_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> rect) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setGeometry_recursive(KDDockWidgets::Rect rect)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry_recursive(Rect.fromCppPointer(rect));
  } // setGuestView(KDDockWidgets::Core::View * arg__1)

  setGuestView(KDDWBindingsCore.View? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__setGuestView_View')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setHostView(KDDockWidgets::Core::View * arg__1)

  setHostView(KDDWBindingsCore.View? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(289))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setHostView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setHostView(KDDockWidgets::Core::View * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHostView((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(arg__1));
  } // setIsVisible(bool arg__1)

  setIsVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(290))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setIsVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Item::setIsVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setIsVisible(arg__1 != 0);
  } // setMaxSizeHint(KDDockWidgets::Size arg__1)

  setMaxSizeHint(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__setMaxSizeHint_Size')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setMinSize(KDDockWidgets::Size arg__1)

  setMinSize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__setMinSize_Size')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setPos(KDDockWidgets::Point arg__1)

  setPos(Point arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__setPos_Point')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setSize(KDDockWidgets::Size arg__1)

  setSize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__setSize_Size')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // size() const

  Size size() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__size')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  } // turnIntoPlaceholder()

  turnIntoPlaceholder() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__turnIntoPlaceholder')
        .asFunction();
    func(thisCpp);
  } // unref()

  unref() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__unref')
        .asFunction();
    func(thisCpp);
  } // updateObjectName()

  updateObjectName() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__updateObjectName')
        .asFunction();
    func(thisCpp);
  } // updateWidgetGeometries()

  updateWidgetGeometries() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(302))
        .asFunction();
    func(thisCpp);
  }

  static void updateWidgetGeometries_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
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
            cFunctionSymbolName(303))
        .asFunction();
    return func(thisCpp);
  }

  static int visibleCount_recursive_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Object.s_dartInstanceByCppPtr[thisCpp.address] as Item;
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
            'c_KDDockWidgets__Core__Item__width')
        .asFunction();
    return func(thisCpp);
  } // x() const

  int x() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__x')
        .asFunction();
    return func(thisCpp);
  } // y() const

  int y() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__y')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Item__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 255:
        return "c_KDDockWidgets__Core__Item__checkSanity";
      case 256:
        return "c_KDDockWidgets__Core__Item__dumpLayout_int";
      case 266:
        return "c_KDDockWidgets__Core__Item__isVisible_bool";
      case 272:
        return "c_KDDockWidgets__Core__Item__maxSizeHint";
      case 273:
        return "c_KDDockWidgets__Core__Item__minSize";
      case 287:
        return "c_KDDockWidgets__Core__Item__setGeometry_recursive_Rect";
      case 289:
        return "c_KDDockWidgets__Core__Item__setHostView_View";
      case 290:
        return "c_KDDockWidgets__Core__Item__setIsVisible_bool";
      case 302:
        return "c_KDDockWidgets__Core__Item__updateWidgetGeometries";
      case 303:
        return "c_KDDockWidgets__Core__Item__visibleCount_recursive";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 255:
        return "checkSanity";
      case 256:
        return "dumpLayout";
      case 266:
        return "isVisible";
      case 272:
        return "maxSizeHint";
      case 273:
        return "minSize";
      case 287:
        return "setGeometry_recursive";
      case 289:
        return "setHostView";
      case 290:
        return "setIsVisible";
      case 302:
        return "updateWidgetGeometries";
      case 303:
        return "visibleCount_recursive";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__Item__registerVirtualMethodCallback')
        .asFunction();
    const callbackExcept255 = 0;
    final callback255 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Item.checkSanity_calledFromC, callbackExcept255);
    registerCallback(thisCpp, callback255, 255);
    final callback256 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Item.dumpLayout_calledFromC);
    registerCallback(thisCpp, callback256, 256);
    const callbackExcept266 = 0;
    final callback266 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int8_FFI>(
            Item.isVisible_calledFromC, callbackExcept266);
    registerCallback(thisCpp, callback266, 266);
    final callback272 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Item.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback272, 272);
    final callback273 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Item.minSize_calledFromC);
    registerCallback(thisCpp, callback273, 273);
    final callback287 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Item.setGeometry_recursive_calledFromC);
    registerCallback(thisCpp, callback287, 287);
    final callback289 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Item.setHostView_calledFromC);
    registerCallback(thisCpp, callback289, 289);
    final callback290 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            Item.setIsVisible_calledFromC);
    registerCallback(thisCpp, callback290, 290);
    final callback302 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Item.updateWidgetGeometries_calledFromC);
    registerCallback(thisCpp, callback302, 302);
    const callbackExcept303 = 0;
    final callback303 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Item.visibleCount_recursive_calledFromC, callbackExcept303);
    registerCallback(thisCpp, callback303, 303);
  }
}
