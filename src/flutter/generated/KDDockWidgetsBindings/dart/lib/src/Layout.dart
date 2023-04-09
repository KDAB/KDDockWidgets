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

class Layout extends Controller {
  Layout.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Layout.init() : super.init() {}
  factory Layout.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Layout;
    }
    return Layout.fromCppPointer(cppPointer, needsAutoDelete);
  } //Layout(KDDockWidgets::ViewType arg__1, KDDockWidgets::Core::View * arg__2)
  Layout(int arg__1, View? arg__2) : super.init() {
    final voidstar_Func_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__constructor_Type_View')
        .asFunction();
    thisCpp = func(arg__1, arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // asDropArea() const
  DropArea asDropArea() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__asDropArea')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return DropArea.fromCppPointer(result, false);
  } // checkSanity() const

  bool checkSanity() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__checkSanity')
        .asFunction();
    return func(thisCpp) != 0;
  } // clearLayout()

  clearLayout() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__clearLayout')
        .asFunction();
    func(thisCpp);
  } // containsFrame(const KDDockWidgets::Core::Group * arg__1) const

  bool containsFrame(Group? arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__containsFrame_Group')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // containsItem(const Layouting::Item * arg__1) const

  bool containsItem(Item? arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__containsItem_Item')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // count() const

  int count() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__count')
        .asFunction();
    return func(thisCpp);
  } // dumpLayout() const

  dumpLayout() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__dumpLayout')
        .asFunction();
    func(thisCpp);
  } // floatingWindow() const

  FloatingWindow floatingWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__floatingWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return FloatingWindow.fromCppPointer(result, false);
  } // groups() const

  QList groups() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__groups')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QList<Group>.fromCppPointer(result, true);
  } // groupsFrom(KDDockWidgets::Core::View * groupOrMultiSplitter) const

  QList groupsFrom(View? groupOrMultiSplitter) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__groupsFrom_View')
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        groupOrMultiSplitter == null
            ? ffi.nullptr
            : groupOrMultiSplitter.thisCpp);
    return QList<Group>.fromCppPointer(result, true);
  } // isInMainWindow(bool honourNesting) const

  bool isInMainWindow({bool honourNesting = false}) {
    final bool_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__isInMainWindow_bool')
        .asFunction();
    return func(thisCpp, honourNesting ? 1 : 0) != 0;
  } // itemForFrame(const KDDockWidgets::Core::Group * group) const

  Item itemForFrame(Group? group) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__itemForFrame_Group')
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, group == null ? ffi.nullptr : group.thisCpp);
    return Item.fromCppPointer(result, false);
  } // layoutHeight() const

  int layoutHeight() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutHeight')
        .asFunction();
    return func(thisCpp);
  } // layoutMaximumSizeHint() const

  QSize layoutMaximumSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutMaximumSizeHint')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // layoutMinimumSize() const

  QSize layoutMinimumSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutMinimumSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // layoutSize() const

  QSize layoutSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutSize')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // layoutWidth() const

  int layoutWidth() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__layoutWidth')
        .asFunction();
    return func(thisCpp);
  } // mainWindow(bool honourNesting) const

  MainWindow mainWindow({bool honourNesting = false}) {
    final voidstar_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int8_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__mainWindow_bool')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, honourNesting ? 1 : 0);
    return MainWindow.fromCppPointer(result, false);
  } // onResize(QSize newSize)

  bool onResize(QSize newSize) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__onResize_QSize')
        .asFunction();
    return func(thisCpp, newSize == null ? ffi.nullptr : newSize.thisCpp) != 0;
  } // placeholderCount() const

  int placeholderCount() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__placeholderCount')
        .asFunction();
    return func(thisCpp);
  } // removeItem(Layouting::Item * item)

  removeItem(Item? item) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__removeItem_Item')
        .asFunction();
    func(thisCpp, item == null ? ffi.nullptr : item.thisCpp);
  } // restorePlaceholder(KDDockWidgets::Core::DockWidget * dw, Layouting::Item * arg__2, int tabIndex)

  restorePlaceholder(DockWidget? dw, Item? arg__2, int tabIndex) {
    final void_Func_voidstar_voidstar_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    void_Func_voidstar_voidstar_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__restorePlaceholder_DockWidget_Item_int')
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp, tabIndex);
  } // setLayoutMinimumSize(QSize arg__1)

  setLayoutMinimumSize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__setLayoutMinimumSize_QSize')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setLayoutSize(QSize arg__1)

  setLayoutSize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__setLayoutSize_QSize')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setParentView_impl_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as Layout;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Layout::setParentView_impl(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParentView_impl(View.fromCppPointer(parent));
  } // unrefOldPlaceholders(const QList<KDDockWidgets::Core::Group* > & groupsBeingAdded) const

  unrefOldPlaceholders(QList? groupsBeingAdded) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__unrefOldPlaceholders_QList_Group')
        .asFunction();
    func(thisCpp,
        groupsBeingAdded == null ? ffi.nullptr : groupsBeingAdded.thisCpp);
  } // updateSizeConstraints()

  updateSizeConstraints() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__updateSizeConstraints')
        .asFunction();
    func(thisCpp);
  } // viewAboutToBeDeleted()

  viewAboutToBeDeleted() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__viewAboutToBeDeleted')
        .asFunction();
    func(thisCpp);
  } // visibleCount() const

  int visibleCount() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__visibleCount')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 881:
        return "c_KDDockWidgets__Controllers__Layout__setParentView_impl_View";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 881:
        return "setParentView_impl";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Controllers__Layout__registerVirtualMethodCallback')
        .asFunction();
    final callback881 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Controller.setParentView_impl_calledFromC);
    registerCallback(thisCpp, callback881, 881);
  }
}
