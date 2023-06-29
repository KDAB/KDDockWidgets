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
            cFunctionSymbolName(840))
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
            cFunctionSymbolName(850))
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
            cFunctionSymbolName(852))
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
            cFunctionSymbolName(858))
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
            cFunctionSymbolName(859))
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
            cFunctionSymbolName(860))
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
            cFunctionSymbolName(863))
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
            cFunctionSymbolName(865))
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
            cFunctionSymbolName(1670))
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
  } // hover_flutter(QPoint globalPos)

  int hover_flutter(QPoint globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1680))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

  static int hover_flutter_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::hover_flutter(QPoint globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover_flutter(QPoint.fromCppPointer(globalPos));
    return result;
  } // hoveredGroup() const

  KDDWBindingsCore.Group hoveredGroup() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__hoveredGroup')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(867))
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
            cFunctionSymbolName(869))
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
            cFunctionSymbolName(870))
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
            cFunctionSymbolName(871))
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
            cFunctionSymbolName(872))
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
  } // isMounted() const

  bool isMounted() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(942))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMounted_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::isMounted() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMounted();
    return result ? 1 : 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(873))
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
            cFunctionSymbolName(874))
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
            cFunctionSymbolName(875))
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
            cFunctionSymbolName(1671))
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
            cFunctionSymbolName(876))
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
            cFunctionSymbolName(877))
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
            cFunctionSymbolName(878))
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
            cFunctionSymbolName(879))
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
            cFunctionSymbolName(880))
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
  } // move(int x, int y)

  move_2(int x, int y) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(884))
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
            cFunctionSymbolName(885))
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
  } // onChildAdded(KDDockWidgets::Core::View * childView)

  onChildAdded(KDDWBindingsCore.View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(945))
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
            cFunctionSymbolName(946))
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
            cFunctionSymbolName(947))
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
            cFunctionSymbolName(949))
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
  } // onRebuildRequested()

  onRebuildRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(951))
        .asFunction();
    func(thisCpp);
  }

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
  } // onResize(int h, int w)

  bool onResize_2(int h, int w) {
    final bool_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(887))
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
            cFunctionSymbolName(1672))
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
  } // posForIndicator_flutter(KDDockWidgets::DropLocation arg__1) const

  QPoint posForIndicator_flutter(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1684))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> posForIndicator_flutter_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::posForIndicator_flutter(KDDockWidgets::DropLocation arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.posForIndicator_flutter(arg__1);
    return result.thisCpp;
  } // raise()

  raise() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1673))
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
            cFunctionSymbolName(890))
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
  } // raiseChild(KDDockWidgets::Core::View * childView)

  raiseChild(KDDWBindingsCore.View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(954))
        .asFunction();
    func(thisCpp, childView == null ? ffi.nullptr : childView.thisCpp);
  }

  static void raiseChild_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::raiseChild(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseChild((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  } // raiseWindow(KDDockWidgets::Core::View * rootView)

  raiseWindow(KDDWBindingsCore.View? rootView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(955))
        .asFunction();
    func(thisCpp, rootView == null ? ffi.nullptr : rootView.thisCpp);
  }

  static void raiseWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? rootView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::raiseWindow(KDDockWidgets::Core::View * rootView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseWindow((rootView == null || rootView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(rootView));
  } // releaseKeyboard()

  releaseKeyboard() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(892))
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
            cFunctionSymbolName(893))
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
            cFunctionSymbolName(1674))
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
  } // rubberBand() const

  KDDWBindingsCore.View rubberBand() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__rubberBand')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  } // setCursor(Qt::CursorShape shape)

  setCursor(int shape) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(896))
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
            cFunctionSymbolName(897))
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
            cFunctionSymbolName(898))
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
            cFunctionSymbolName(1675))
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
            cFunctionSymbolName(900))
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
            cFunctionSymbolName(901))
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
            cFunctionSymbolName(902))
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
            cFunctionSymbolName(903))
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
            cFunctionSymbolName(1676))
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
            cFunctionSymbolName(904))
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
            cFunctionSymbolName(906))
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
  } // setViewName(const QString & name)

  setViewName(String? name) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(907))
        .asFunction();
    func(thisCpp, name?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setViewName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setViewName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setViewName(QString.fromCppPointer(name).toDartString());
  } // setVisible(bool arg__1)

  setVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(1677))
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
            cFunctionSymbolName(909))
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
            cFunctionSymbolName(910))
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
            cFunctionSymbolName(911))
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
            cFunctionSymbolName(912))
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
            cFunctionSymbolName(913))
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
            cFunctionSymbolName(914))
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
            cFunctionSymbolName(915))
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
            cFunctionSymbolName(916))
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
  } // update()

  update() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(918))
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
            cFunctionSymbolName(1678))
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
  } // updatePositions_flutter(int overlayWidth, int overlayHeight, KDDockWidgets::Core::Group * hoveredGroup, int visibleLocations)

  bool updatePositions_flutter(int overlayWidth, int overlayHeight,
      KDDWBindingsCore.Group? hoveredGroup, int visibleLocations) {
    final bool_Func_voidstar_int_int_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1688))
        .asFunction();
    return func(
            thisCpp,
            overlayWidth,
            overlayHeight,
            hoveredGroup == null ? ffi.nullptr : hoveredGroup.thisCpp,
            visibleLocations) !=
        0;
  }

  static int updatePositions_flutter_calledFromC(
      ffi.Pointer<void> thisCpp,
      int overlayWidth,
      int overlayHeight,
      ffi.Pointer<void>? hoveredGroup,
      int visibleLocations) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::updatePositions_flutter(int overlayWidth, int overlayHeight, KDDockWidgets::Core::Group * hoveredGroup, int visibleLocations)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.updatePositions_flutter(
        overlayWidth,
        overlayHeight,
        (hoveredGroup == null || hoveredGroup.address == 0)
            ? null
            : KDDWBindingsCore.Group.fromCppPointer(hoveredGroup),
        visibleLocations);
    return result ? 1 : 0;
  } // viewName() const

  QString viewName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(919))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> viewName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::viewName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.viewName();
    return result.thisCpp;
  } // visibleDropIndicatorLocations() const

  int visibleDropIndicatorLocations() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__visibleDropIndicatorLocations')
        .asFunction();
    return func(thisCpp);
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
      case 840:
        return "c_KDDockWidgets__flutter__IndicatorWindow__activateWindow";
      case 850:
        return "c_KDDockWidgets__flutter__IndicatorWindow__close";
      case 852:
        return "c_KDDockWidgets__flutter__IndicatorWindow__createPlatformWindow";
      case 858:
        return "c_KDDockWidgets__flutter__IndicatorWindow__flags";
      case 859:
        return "c_KDDockWidgets__flutter__IndicatorWindow__geometry";
      case 860:
        return "c_KDDockWidgets__flutter__IndicatorWindow__grabMouse";
      case 863:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hasFocus";
      case 865:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hide";
      case 1670:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hover_QPoint";
      case 1680:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hover_flutter_QPoint";
      case 867:
        return "c_KDDockWidgets__flutter__IndicatorWindow__init";
      case 869:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isActiveWindow";
      case 870:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isExplicitlyHidden";
      case 871:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMaximized";
      case 872:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMinimized";
      case 942:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMounted";
      case 873:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isNull";
      case 874:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isRootView";
      case 875:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isVisible";
      case 1671:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isWindow";
      case 876:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapFromGlobal_QPoint";
      case 877:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapTo_View_QPoint";
      case 878:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapToGlobal_QPoint";
      case 879:
        return "c_KDDockWidgets__flutter__IndicatorWindow__maxSizeHint";
      case 880:
        return "c_KDDockWidgets__flutter__IndicatorWindow__minSize";
      case 884:
        return "c_KDDockWidgets__flutter__IndicatorWindow__move_int_int";
      case 885:
        return "c_KDDockWidgets__flutter__IndicatorWindow__normalGeometry";
      case 945:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildAdded_View";
      case 946:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildRemoved_View";
      case 947:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildVisibilityChanged_View";
      case 949:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onGeometryChanged";
      case 951:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onRebuildRequested";
      case 887:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onResize_int_int";
      case 1672:
        return "c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_DropLocation";
      case 1684:
        return "c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_flutter_DropLocation";
      case 1673:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raise";
      case 890:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseAndActivate";
      case 954:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseChild_View";
      case 955:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseWindow_View";
      case 892:
        return "c_KDDockWidgets__flutter__IndicatorWindow__releaseKeyboard";
      case 893:
        return "c_KDDockWidgets__flutter__IndicatorWindow__releaseMouse";
      case 1674:
        return "c_KDDockWidgets__flutter__IndicatorWindow__resize_QSize";
      case 896:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setCursor_CursorShape";
      case 897:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setFixedHeight_int";
      case 898:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setFixedWidth_int";
      case 1675:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setGeometry_QRect";
      case 900:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setHeight_int";
      case 901:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMaximumSize_QSize";
      case 902:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMinimumSize_QSize";
      case 903:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMouseTracking_bool";
      case 1676:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setObjectName_QString";
      case 904:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setParent_View";
      case 906:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setSize_int_int";
      case 907:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setViewName_QString";
      case 1677:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setVisible_bool";
      case 909:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWidth_int";
      case 910:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWindowOpacity_double";
      case 911:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWindowTitle_QString";
      case 912:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setZOrder_int";
      case 913:
        return "c_KDDockWidgets__flutter__IndicatorWindow__show";
      case 914:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showMaximized";
      case 915:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showMinimized";
      case 916:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showNormal";
      case 918:
        return "c_KDDockWidgets__flutter__IndicatorWindow__update";
      case 1678:
        return "c_KDDockWidgets__flutter__IndicatorWindow__updatePositions";
      case 1688:
        return "c_KDDockWidgets__flutter__IndicatorWindow__updatePositions_flutter_int_int_Group_int";
      case 919:
        return "c_KDDockWidgets__flutter__IndicatorWindow__viewName";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 840:
        return "activateWindow";
      case 850:
        return "close";
      case 852:
        return "createPlatformWindow";
      case 858:
        return "flags";
      case 859:
        return "geometry";
      case 860:
        return "grabMouse";
      case 863:
        return "hasFocus";
      case 865:
        return "hide";
      case 1670:
        return "hover";
      case 1680:
        return "hover_flutter";
      case 867:
        return "init";
      case 869:
        return "isActiveWindow";
      case 870:
        return "isExplicitlyHidden";
      case 871:
        return "isMaximized";
      case 872:
        return "isMinimized";
      case 942:
        return "isMounted";
      case 873:
        return "isNull";
      case 874:
        return "isRootView";
      case 875:
        return "isVisible";
      case 1671:
        return "isWindow";
      case 876:
        return "mapFromGlobal";
      case 877:
        return "mapTo";
      case 878:
        return "mapToGlobal";
      case 879:
        return "maxSizeHint";
      case 880:
        return "minSize";
      case 884:
        return "move_2";
      case 885:
        return "normalGeometry";
      case 945:
        return "onChildAdded";
      case 946:
        return "onChildRemoved";
      case 947:
        return "onChildVisibilityChanged";
      case 949:
        return "onGeometryChanged";
      case 951:
        return "onRebuildRequested";
      case 887:
        return "onResize_2";
      case 1672:
        return "posForIndicator";
      case 1684:
        return "posForIndicator_flutter";
      case 1673:
        return "raise";
      case 890:
        return "raiseAndActivate";
      case 954:
        return "raiseChild";
      case 955:
        return "raiseWindow";
      case 892:
        return "releaseKeyboard";
      case 893:
        return "releaseMouse";
      case 1674:
        return "resize";
      case 896:
        return "setCursor";
      case 897:
        return "setFixedHeight";
      case 898:
        return "setFixedWidth";
      case 1675:
        return "setGeometry";
      case 900:
        return "setHeight";
      case 901:
        return "setMaximumSize";
      case 902:
        return "setMinimumSize";
      case 903:
        return "setMouseTracking";
      case 1676:
        return "setObjectName";
      case 904:
        return "setParent";
      case 906:
        return "setSize_2";
      case 907:
        return "setViewName";
      case 1677:
        return "setVisible";
      case 909:
        return "setWidth";
      case 910:
        return "setWindowOpacity";
      case 911:
        return "setWindowTitle";
      case 912:
        return "setZOrder";
      case 913:
        return "show";
      case 914:
        return "showMaximized";
      case 915:
        return "showMinimized";
      case 916:
        return "showNormal";
      case 918:
        return "update";
      case 1678:
        return "updatePositions";
      case 1688:
        return "updatePositions_flutter";
      case 919:
        return "viewName";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__IndicatorWindow__registerVirtualMethodCallback')
        .asFunction();
    final callback840 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback840, 840);
    const callbackExcept850 = 0;
    final callback850 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept850);
    registerCallback(thisCpp, callback850, 850);
    final callback852 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback852, 852);
    const callbackExcept858 = 0;
    final callback858 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept858);
    registerCallback(thisCpp, callback858, 858);
    final callback859 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback859, 859);
    final callback860 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback860, 860);
    const callbackExcept863 = 0;
    final callback863 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept863);
    registerCallback(thisCpp, callback863, 863);
    final callback865 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback865, 865);
    const callbackExcept1680 = 0;
    final callback1680 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.IndicatorWindow.hover_flutter_calledFromC,
            callbackExcept1680);
    registerCallback(thisCpp, callback1680, 1680);
    final callback867 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback867, 867);
    const callbackExcept869 = 0;
    final callback869 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept869);
    registerCallback(thisCpp, callback869, 869);
    const callbackExcept870 = 0;
    final callback870 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept870);
    registerCallback(thisCpp, callback870, 870);
    const callbackExcept871 = 0;
    final callback871 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept871);
    registerCallback(thisCpp, callback871, 871);
    const callbackExcept872 = 0;
    final callback872 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept872);
    registerCallback(thisCpp, callback872, 872);
    const callbackExcept942 = 0;
    final callback942 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMounted_calledFromC, callbackExcept942);
    registerCallback(thisCpp, callback942, 942);
    const callbackExcept873 = 0;
    final callback873 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept873);
    registerCallback(thisCpp, callback873, 873);
    const callbackExcept874 = 0;
    final callback874 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept874);
    registerCallback(thisCpp, callback874, 874);
    const callbackExcept875 = 0;
    final callback875 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept875);
    registerCallback(thisCpp, callback875, 875);
    final callback876 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback876, 876);
    final callback877 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback877, 877);
    final callback878 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback878, 878);
    final callback879 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback879, 879);
    final callback880 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback880, 880);
    final callback884 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback884, 884);
    final callback885 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback885, 885);
    final callback945 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback945, 945);
    final callback946 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback947 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback947, 947);
    final callback949 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback949, 949);
    final callback951 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback951, 951);
    const callbackExcept887 = 0;
    final callback887 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept887);
    registerCallback(thisCpp, callback887, 887);
    final callback1684 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter
                .IndicatorWindow.posForIndicator_flutter_calledFromC);
    registerCallback(thisCpp, callback1684, 1684);
    final callback890 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback890, 890);
    final callback954 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseChild_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback955 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseWindow_calledFromC);
    registerCallback(thisCpp, callback955, 955);
    final callback892 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback892, 892);
    final callback893 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback893, 893);
    final callback896 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback896, 896);
    final callback897 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback897, 897);
    final callback898 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback898, 898);
    final callback900 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    final callback901 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback901, 901);
    final callback902 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback902, 902);
    final callback903 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback903, 903);
    final callback904 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback904, 904);
    final callback906 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback906, 906);
    final callback907 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback909 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback910 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback911 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    final callback912 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    final callback913 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback913, 913);
    final callback914 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback914, 914);
    final callback915 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback915, 915);
    final callback916 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback918 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback918, 918);
    const callbackExcept1688 = 0;
    final callback1688 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsFlutter.IndicatorWindow.updatePositions_flutter_calledFromC,
        callbackExcept1688);
    registerCallback(thisCpp, callback1688, 1688);
    final callback919 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.viewName_calledFromC);
    registerCallback(thisCpp, callback919, 919);
  }
}
