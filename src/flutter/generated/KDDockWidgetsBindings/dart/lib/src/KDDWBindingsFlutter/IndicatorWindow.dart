/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import '../TypeHelpers.dart';
import '../../Bindings.dart';
import '../../Bindings_KDDWBindingsCore.dart' as KDDWBindingsCore;
import '../../Bindings_KDDWBindingsFlutter.dart' as KDDWBindingsFlutter;
import '../../LibraryLoader.dart';
import '../../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class IndicatorWindow extends KDDWBindingsFlutter.View {
  IndicatorWindow.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  IndicatorWindow.init() : super.init() {}
  factory IndicatorWindow.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as IndicatorWindow;
    }
    return IndicatorWindow.fromCppPointer(cppPointer, needsAutoDelete);
  } //IndicatorWindow(KDDockWidgets::Core::ClassicDropIndicatorOverlay * arg__1, KDDockWidgets::Core::View * parent)
  IndicatorWindow(KDDWBindingsCore.ClassicDropIndicatorOverlay? arg__1,
      KDDWBindingsCore.View? parent)
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__constructor_ClassicDropIndicatorOverlay_View')
        .asFunction();
    thisCpp = func(arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // activateWindow()
  activateWindow() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(922))
        .asFunction();
    func(thisCpp);
  }

  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  } // close()

  bool close() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(933))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  } // createPlatformWindow()

  createPlatformWindow() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(936))
        .asFunction();
    func(thisCpp);
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  } // flags() const

  int flags() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(943))
        .asFunction();
    return func(thisCpp);
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  } // geometry() const

  QRect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(946))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  } // grabMouse()

  grabMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(948))
        .asFunction();
    func(thisCpp);
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  } // hasFocus() const

  bool hasFocus() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(951))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  } // hide()

  hide() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(953))
        .asFunction();
    func(thisCpp);
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  } // hover(QPoint globalPos)

  int hover(QPoint globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1783))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

  static int hover_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::hover(QPoint globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover(QPoint.fromCppPointer(globalPos));
    return result;
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(956))
        .asFunction();
    func(thisCpp);
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  } // isActiveWindow() const

  bool isActiveWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(958))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  } // isExplicitlyHidden() const

  bool isExplicitlyHidden() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(959))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isExplicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isExplicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExplicitlyHidden();
    return result ? 1 : 0;
  } // isMaximized() const

  bool isMaximized() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(960))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  } // isMinimized() const

  bool isMinimized() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(961))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(962))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  } // isRootView() const

  bool isRootView() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(963))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  } // isVisible() const

  bool isVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(964))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  } // isWindow() const

  bool isWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(1784))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isWindow();
    return result ? 1 : 0;
  } // mapFromGlobal(QPoint globalPt) const

  QPoint mapFromGlobal(QPoint globalPt) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(965))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, globalPt == null ? ffi.nullptr : globalPt.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  } // mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const

  QPoint mapTo(KDDWBindingsCore.View? parent, QPoint pos) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(966))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp,
        pos == null ? ffi.nullptr : pos.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
        QPoint.fromCppPointer(pos));
    return result.thisCpp;
  } // mapToGlobal(QPoint localPt) const

  QPoint mapToGlobal(QPoint localPt) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(967))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, localPt == null ? ffi.nullptr : localPt.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  } // maxSizeHint() const

  QSize maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(968))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  } // minSize() const

  QSize minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(969))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  } // minimumHeight() const

  int minimumHeight() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(970))
        .asFunction();
    return func(thisCpp);
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  } // minimumWidth() const

  int minimumWidth() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(971))
        .asFunction();
    return func(thisCpp);
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  } // move(int x, int y)

  move_2(int x, int y) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(973))
        .asFunction();
    func(thisCpp, x, y);
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  } // normalGeometry() const

  QRect normalGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(974))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  } // objectName() const

  QString objectName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(975))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  } // onChildAdded(KDDockWidgets::Core::View * childView)

  onChildAdded(KDDWBindingsCore.View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1044))
        .asFunction();
    func(thisCpp, childView == null ? ffi.nullptr : childView.thisCpp);
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  } // onChildRemoved(KDDockWidgets::Core::View * childView)

  onChildRemoved(KDDWBindingsCore.View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1045))
        .asFunction();
    func(thisCpp, childView == null ? ffi.nullptr : childView.thisCpp);
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  } // onChildVisibilityChanged(KDDockWidgets::Core::View * childView)

  onChildVisibilityChanged(KDDWBindingsCore.View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1046))
        .asFunction();
    func(thisCpp, childView == null ? ffi.nullptr : childView.thisCpp);
  }

  static void onChildVisibilityChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildVisibilityChanged(
        (childView == null || childView.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(childView));
  } // onGeometryChanged()

  onGeometryChanged() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1048))
        .asFunction();
    func(thisCpp);
  }

  static void onGeometryChanged_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::onGeometryChanged()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onGeometryChanged();
  } // onResize(int h, int w)

  bool onResize_2(int h, int w) {
    final bool_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(977))
        .asFunction();
    return func(thisCpp, h, w) != 0;
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
    return result ? 1 : 0;
  } // posForIndicator(KDDockWidgets::DropLocation arg__1) const

  QPoint posForIndicator(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1785))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> posForIndicator_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::posForIndicator(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.posForIndicator(arg__1);
    return result.thisCpp;
  } // raise()

  raise() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1786))
        .asFunction();
    func(thisCpp);
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  } // raiseAndActivate()

  raiseAndActivate() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(981))
        .asFunction();
    func(thisCpp);
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  } // releaseKeyboard()

  releaseKeyboard() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(983))
        .asFunction();
    func(thisCpp);
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  } // releaseMouse()

  releaseMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(984))
        .asFunction();
    func(thisCpp);
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  } // resize(QSize arg__1)

  resize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1787))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void resize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::resize(QSize arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.resize(QSize.fromCppPointer(arg__1));
  } // setCursor(Qt::CursorShape shape)

  setCursor(int shape) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(988))
        .asFunction();
    func(thisCpp, shape);
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  } // setFixedHeight(int h)

  setFixedHeight(int h) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(989))
        .asFunction();
    func(thisCpp, h);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  } // setFixedWidth(int w)

  setFixedWidth(int w) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(990))
        .asFunction();
    func(thisCpp, w);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  } // setGeometry(QRect arg__1)

  setGeometry(QRect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1788))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  } // setHeight(int h)

  setHeight(int h) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(992))
        .asFunction();
    func(thisCpp, h);
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  } // setMaximumSize(QSize sz)

  setMaximumSize(QSize sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(993))
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  } // setMinimumSize(QSize sz)

  setMinimumSize(QSize sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(994))
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  } // setMouseTracking(bool enable)

  setMouseTracking(bool enable) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(995))
        .asFunction();
    func(thisCpp, enable ? 1 : 0);
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  } // setObjectName(const QString & arg__1)

  setObjectName(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1789))
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setObjectName(const QString & arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(arg__1).toDartString());
  } // setParent(KDDockWidgets::Core::View * parent)

  setParent(KDDWBindingsCore.View? parent) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(997))
        .asFunction();
    func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  } // setSize(int w, int h)

  setSize_2(int w, int h) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(999))
        .asFunction();
    func(thisCpp, w, h);
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  } // setVisible(bool arg__1)

  setVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(1790))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(arg__1 != 0);
  } // setWidth(int w)

  setWidth(int w) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1001))
        .asFunction();
    func(thisCpp, w);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  } // setWindowOpacity(double v)

  setWindowOpacity(double v) {
    final void_Func_voidstar_double func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Double_FFI>>(
            cFunctionSymbolName(1002))
        .asFunction();
    func(thisCpp, v);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  } // setWindowTitle(const QString & title)

  setWindowTitle(String? title) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1003))
        .asFunction();
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  } // setZOrder(int z)

  setZOrder(int z) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1004))
        .asFunction();
    func(thisCpp, z);
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  } // show()

  show() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1005))
        .asFunction();
    func(thisCpp);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  } // showMaximized()

  showMaximized() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1006))
        .asFunction();
    func(thisCpp);
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  } // showMinimized()

  showMinimized() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1007))
        .asFunction();
    func(thisCpp);
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  } // showNormal()

  showNormal() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1008))
        .asFunction();
    func(thisCpp);
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  } // sizeHint() const

  QSize sizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(1010))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  } // update()

  update() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1012))
        .asFunction();
    func(thisCpp);
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  } // updatePositions()

  updatePositions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1791))
        .asFunction();
    func(thisCpp);
  }

  static void updatePositions_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::updatePositions()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updatePositions();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 922:
        return "c_KDDockWidgets__flutter__IndicatorWindow__activateWindow";
      case 933:
        return "c_KDDockWidgets__flutter__IndicatorWindow__close";
      case 936:
        return "c_KDDockWidgets__flutter__IndicatorWindow__createPlatformWindow";
      case 943:
        return "c_KDDockWidgets__flutter__IndicatorWindow__flags";
      case 946:
        return "c_KDDockWidgets__flutter__IndicatorWindow__geometry";
      case 948:
        return "c_KDDockWidgets__flutter__IndicatorWindow__grabMouse";
      case 951:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hasFocus";
      case 953:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hide";
      case 1783:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hover_QPoint";
      case 956:
        return "c_KDDockWidgets__flutter__IndicatorWindow__init";
      case 958:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isActiveWindow";
      case 959:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isExplicitlyHidden";
      case 960:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMaximized";
      case 961:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMinimized";
      case 962:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isNull";
      case 963:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isRootView";
      case 964:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isVisible";
      case 1784:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isWindow";
      case 965:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapFromGlobal_QPoint";
      case 966:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapTo_View_QPoint";
      case 967:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapToGlobal_QPoint";
      case 968:
        return "c_KDDockWidgets__flutter__IndicatorWindow__maxSizeHint";
      case 969:
        return "c_KDDockWidgets__flutter__IndicatorWindow__minSize";
      case 970:
        return "c_KDDockWidgets__flutter__IndicatorWindow__minimumHeight";
      case 971:
        return "c_KDDockWidgets__flutter__IndicatorWindow__minimumWidth";
      case 973:
        return "c_KDDockWidgets__flutter__IndicatorWindow__move_int_int";
      case 974:
        return "c_KDDockWidgets__flutter__IndicatorWindow__normalGeometry";
      case 975:
        return "c_KDDockWidgets__flutter__IndicatorWindow__objectName";
      case 1044:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildAdded_View";
      case 1045:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildRemoved_View";
      case 1046:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildVisibilityChanged_View";
      case 1048:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onGeometryChanged";
      case 977:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onResize_int_int";
      case 1785:
        return "c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_DropLocation";
      case 1786:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raise";
      case 981:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseAndActivate";
      case 983:
        return "c_KDDockWidgets__flutter__IndicatorWindow__releaseKeyboard";
      case 984:
        return "c_KDDockWidgets__flutter__IndicatorWindow__releaseMouse";
      case 1787:
        return "c_KDDockWidgets__flutter__IndicatorWindow__resize_QSize";
      case 988:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setCursor_CursorShape";
      case 989:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setFixedHeight_int";
      case 990:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setFixedWidth_int";
      case 1788:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setGeometry_QRect";
      case 992:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setHeight_int";
      case 993:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMaximumSize_QSize";
      case 994:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMinimumSize_QSize";
      case 995:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMouseTracking_bool";
      case 1789:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setObjectName_QString";
      case 997:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setParent_View";
      case 999:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setSize_int_int";
      case 1790:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setVisible_bool";
      case 1001:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWidth_int";
      case 1002:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWindowOpacity_double";
      case 1003:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWindowTitle_QString";
      case 1004:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setZOrder_int";
      case 1005:
        return "c_KDDockWidgets__flutter__IndicatorWindow__show";
      case 1006:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showMaximized";
      case 1007:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showMinimized";
      case 1008:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showNormal";
      case 1010:
        return "c_KDDockWidgets__flutter__IndicatorWindow__sizeHint";
      case 1012:
        return "c_KDDockWidgets__flutter__IndicatorWindow__update";
      case 1791:
        return "c_KDDockWidgets__flutter__IndicatorWindow__updatePositions";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 922:
        return "activateWindow";
      case 933:
        return "close";
      case 936:
        return "createPlatformWindow";
      case 943:
        return "flags";
      case 946:
        return "geometry";
      case 948:
        return "grabMouse";
      case 951:
        return "hasFocus";
      case 953:
        return "hide";
      case 1783:
        return "hover";
      case 956:
        return "init";
      case 958:
        return "isActiveWindow";
      case 959:
        return "isExplicitlyHidden";
      case 960:
        return "isMaximized";
      case 961:
        return "isMinimized";
      case 962:
        return "isNull";
      case 963:
        return "isRootView";
      case 964:
        return "isVisible";
      case 1784:
        return "isWindow";
      case 965:
        return "mapFromGlobal";
      case 966:
        return "mapTo";
      case 967:
        return "mapToGlobal";
      case 968:
        return "maxSizeHint";
      case 969:
        return "minSize";
      case 970:
        return "minimumHeight";
      case 971:
        return "minimumWidth";
      case 973:
        return "move_2";
      case 974:
        return "normalGeometry";
      case 975:
        return "objectName";
      case 1044:
        return "onChildAdded";
      case 1045:
        return "onChildRemoved";
      case 1046:
        return "onChildVisibilityChanged";
      case 1048:
        return "onGeometryChanged";
      case 977:
        return "onResize_2";
      case 1785:
        return "posForIndicator";
      case 1786:
        return "raise";
      case 981:
        return "raiseAndActivate";
      case 983:
        return "releaseKeyboard";
      case 984:
        return "releaseMouse";
      case 1787:
        return "resize";
      case 988:
        return "setCursor";
      case 989:
        return "setFixedHeight";
      case 990:
        return "setFixedWidth";
      case 1788:
        return "setGeometry";
      case 992:
        return "setHeight";
      case 993:
        return "setMaximumSize";
      case 994:
        return "setMinimumSize";
      case 995:
        return "setMouseTracking";
      case 1789:
        return "setObjectName";
      case 997:
        return "setParent";
      case 999:
        return "setSize_2";
      case 1790:
        return "setVisible";
      case 1001:
        return "setWidth";
      case 1002:
        return "setWindowOpacity";
      case 1003:
        return "setWindowTitle";
      case 1004:
        return "setZOrder";
      case 1005:
        return "show";
      case 1006:
        return "showMaximized";
      case 1007:
        return "showMinimized";
      case 1008:
        return "showNormal";
      case 1010:
        return "sizeHint";
      case 1012:
        return "update";
      case 1791:
        return "updatePositions";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__registerVirtualMethodCallback')
        .asFunction();
    final callback922 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback922, 922);
    const callbackExcept933 = 0;
    final callback933 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept933);
    registerCallback(thisCpp, callback933, 933);
    final callback936 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback936, 936);
    const callbackExcept943 = 0;
    final callback943 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept943);
    registerCallback(thisCpp, callback943, 943);
    final callback946 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback948 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback948, 948);
    const callbackExcept951 = 0;
    final callback951 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept951);
    registerCallback(thisCpp, callback951, 951);
    final callback953 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback953, 953);
    final callback956 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback956, 956);
    const callbackExcept958 = 0;
    final callback958 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept958);
    registerCallback(thisCpp, callback958, 958);
    const callbackExcept959 = 0;
    final callback959 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept959);
    registerCallback(thisCpp, callback959, 959);
    const callbackExcept960 = 0;
    final callback960 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept960);
    registerCallback(thisCpp, callback960, 960);
    const callbackExcept961 = 0;
    final callback961 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept961);
    registerCallback(thisCpp, callback961, 961);
    const callbackExcept962 = 0;
    final callback962 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept962);
    registerCallback(thisCpp, callback962, 962);
    const callbackExcept963 = 0;
    final callback963 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept963);
    registerCallback(thisCpp, callback963, 963);
    const callbackExcept964 = 0;
    final callback964 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept964);
    registerCallback(thisCpp, callback964, 964);
    final callback965 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback967 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback969 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback969, 969);
    const callbackExcept970 = 0;
    final callback970 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept970);
    registerCallback(thisCpp, callback970, 970);
    const callbackExcept971 = 0;
    final callback971 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept971);
    registerCallback(thisCpp, callback971, 971);
    final callback973 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback973, 973);
    final callback974 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback974, 974);
    final callback975 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback975, 975);
    final callback1044 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1044, 1044);
    final callback1045 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1045, 1045);
    final callback1046 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback1046, 1046);
    final callback1048 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback1048, 1048);
    const callbackExcept977 = 0;
    final callback977 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept977);
    registerCallback(thisCpp, callback977, 977);
    final callback981 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback983 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback983, 983);
    final callback984 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback988 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback988, 988);
    final callback989 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback990 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback990, 990);
    final callback992 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback995 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback997 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback997, 997);
    final callback999 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback999, 999);
    final callback1001 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback1001, 1001);
    final callback1002 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback1002, 1002);
    final callback1003 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback1003, 1003);
    final callback1004 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback1004, 1004);
    final callback1005 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
    final callback1006 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback1006, 1006);
    final callback1007 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback1007, 1007);
    final callback1008 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback1008, 1008);
    final callback1010 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback1010, 1010);
    final callback1012 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback1012, 1012);
  }
}
