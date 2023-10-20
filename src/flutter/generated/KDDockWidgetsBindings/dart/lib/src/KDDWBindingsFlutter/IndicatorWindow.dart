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
  }
  String getFinalizerName() {
    return "c_KDDockWidgets__flutter__IndicatorWindow_Finalizer";
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
            cFunctionSymbolName(342))
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
            cFunctionSymbolName(352))
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
            cFunctionSymbolName(354))
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
            cFunctionSymbolName(360))
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

  Rect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(361))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
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
            cFunctionSymbolName(362))
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
            cFunctionSymbolName(365))
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
            cFunctionSymbolName(367))
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
  } // hover(KDDockWidgets::Point globalPos)

  int hover(Point globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1115))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

  static int hover_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::hover(KDDockWidgets::Point globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover(Point.fromCppPointer(globalPos));
    return result;
  } // hover_flutter(KDDockWidgets::Point globalPos)

  int hover_flutter(Point globalPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1126))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp);
  }

  static int hover_flutter_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::hover_flutter(KDDockWidgets::Point globalPos)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hover_flutter(Point.fromCppPointer(globalPos));
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
            cFunctionSymbolName(369))
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
            cFunctionSymbolName(371))
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
            cFunctionSymbolName(372))
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
            cFunctionSymbolName(373))
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
            cFunctionSymbolName(374))
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
            cFunctionSymbolName(444))
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
            cFunctionSymbolName(375))
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
            cFunctionSymbolName(376))
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
            cFunctionSymbolName(377))
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
            cFunctionSymbolName(1116))
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
  } // mapFromGlobal(KDDockWidgets::Point globalPt) const

  Point mapFromGlobal(Point globalPt) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(378))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, globalPt == null ? ffi.nullptr : globalPt.thisCpp);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::mapFromGlobal(KDDockWidgets::Point globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(Point.fromCppPointer(globalPt));
    return result.thisCpp;
  } // mapTo(KDDockWidgets::Core::View * parent, KDDockWidgets::Point pos) const

  Point mapTo(KDDWBindingsCore.View? parent, Point pos) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi
                .NativeFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(379))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp,
        pos == null ? ffi.nullptr : pos.thisCpp);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::mapTo(KDDockWidgets::Core::View * parent, KDDockWidgets::Point pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
        Point.fromCppPointer(pos));
    return result.thisCpp;
  } // mapToGlobal(KDDockWidgets::Point localPt) const

  Point mapToGlobal(Point localPt) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(380))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, localPt == null ? ffi.nullptr : localPt.thisCpp);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::mapToGlobal(KDDockWidgets::Point localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(Point.fromCppPointer(localPt));
    return result.thisCpp;
  } // maxSizeHint() const

  Size maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(381))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
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

  Size minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(382))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
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
            cFunctionSymbolName(386))
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

  Rect normalGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(387))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
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
            cFunctionSymbolName(447))
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
            cFunctionSymbolName(448))
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
            cFunctionSymbolName(449))
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
            cFunctionSymbolName(451))
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
            cFunctionSymbolName(453))
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
            cFunctionSymbolName(389))
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

  Point posForIndicator(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1117))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return Point.fromCppPointer(result, true);
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

  Point posForIndicator_flutter(int arg__1) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1130))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, arg__1);
    return Point.fromCppPointer(result, true);
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
            cFunctionSymbolName(1118))
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
            cFunctionSymbolName(392))
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
            cFunctionSymbolName(456))
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
            cFunctionSymbolName(457))
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
            cFunctionSymbolName(394))
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
            cFunctionSymbolName(395))
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
  } // resize(KDDockWidgets::Size arg__1)

  resize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1119))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void resize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::resize(KDDockWidgets::Size arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.resize(Size.fromCppPointer(arg__1));
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
            cFunctionSymbolName(398))
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
            cFunctionSymbolName(399))
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
            cFunctionSymbolName(400))
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
  } // setGeometry(KDDockWidgets::Rect arg__1)

  setGeometry(Rect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1120))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setGeometry(KDDockWidgets::Rect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(Rect.fromCppPointer(arg__1));
  } // setHeight(int h)

  setHeight(int h) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(402))
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
  } // setMaximumSize(KDDockWidgets::Size sz)

  setMaximumSize(Size sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(403))
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setMaximumSize(KDDockWidgets::Size sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(Size.fromCppPointer(sz));
  } // setMinimumSize(KDDockWidgets::Size sz)

  setMinimumSize(Size sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(404))
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::setMinimumSize(KDDockWidgets::Size sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(Size.fromCppPointer(sz));
  } // setMouseTracking(bool enable)

  setMouseTracking(bool enable) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(405))
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
            cFunctionSymbolName(1121))
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
            cFunctionSymbolName(406))
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
            cFunctionSymbolName(408))
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
            cFunctionSymbolName(409))
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
            cFunctionSymbolName(1122))
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
            cFunctionSymbolName(411))
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
            cFunctionSymbolName(412))
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
            cFunctionSymbolName(413))
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
            cFunctionSymbolName(414))
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
            cFunctionSymbolName(415))
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
            cFunctionSymbolName(416))
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
            cFunctionSymbolName(417))
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
            cFunctionSymbolName(418))
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
            cFunctionSymbolName(420))
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
  } // updateIndicatorVisibility()

  updateIndicatorVisibility() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1123))
        .asFunction();
    func(thisCpp);
  }

  static void updateIndicatorVisibility_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore.ClassicIndicatorWindowViewInterface
        .s_dartInstanceByCppPtr[thisCpp.address] as IndicatorWindow;
    if (dartInstance == null) {
      print(
          "Dart instance not found for IndicatorWindow::updateIndicatorVisibility()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.updateIndicatorVisibility();
  } // updatePositions()

  updatePositions() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1124))
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
            cFunctionSymbolName(1134))
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
            cFunctionSymbolName(421))
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
      case 342:
        return "c_KDDockWidgets__flutter__IndicatorWindow__activateWindow";
      case 352:
        return "c_KDDockWidgets__flutter__IndicatorWindow__close";
      case 354:
        return "c_KDDockWidgets__flutter__IndicatorWindow__createPlatformWindow";
      case 360:
        return "c_KDDockWidgets__flutter__IndicatorWindow__flags";
      case 361:
        return "c_KDDockWidgets__flutter__IndicatorWindow__geometry";
      case 362:
        return "c_KDDockWidgets__flutter__IndicatorWindow__grabMouse";
      case 365:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hasFocus";
      case 367:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hide";
      case 1115:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hover_Point";
      case 1126:
        return "c_KDDockWidgets__flutter__IndicatorWindow__hover_flutter_Point";
      case 369:
        return "c_KDDockWidgets__flutter__IndicatorWindow__init";
      case 371:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isActiveWindow";
      case 372:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isExplicitlyHidden";
      case 373:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMaximized";
      case 374:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMinimized";
      case 444:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isMounted";
      case 375:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isNull";
      case 376:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isRootView";
      case 377:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isVisible";
      case 1116:
        return "c_KDDockWidgets__flutter__IndicatorWindow__isWindow";
      case 378:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapFromGlobal_Point";
      case 379:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapTo_View_Point";
      case 380:
        return "c_KDDockWidgets__flutter__IndicatorWindow__mapToGlobal_Point";
      case 381:
        return "c_KDDockWidgets__flutter__IndicatorWindow__maxSizeHint";
      case 382:
        return "c_KDDockWidgets__flutter__IndicatorWindow__minSize";
      case 386:
        return "c_KDDockWidgets__flutter__IndicatorWindow__move_int_int";
      case 387:
        return "c_KDDockWidgets__flutter__IndicatorWindow__normalGeometry";
      case 447:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildAdded_View";
      case 448:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildRemoved_View";
      case 449:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onChildVisibilityChanged_View";
      case 451:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onGeometryChanged";
      case 453:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onRebuildRequested";
      case 389:
        return "c_KDDockWidgets__flutter__IndicatorWindow__onResize_int_int";
      case 1117:
        return "c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_DropLocation";
      case 1130:
        return "c_KDDockWidgets__flutter__IndicatorWindow__posForIndicator_flutter_DropLocation";
      case 1118:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raise";
      case 392:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseAndActivate";
      case 456:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseChild_View";
      case 457:
        return "c_KDDockWidgets__flutter__IndicatorWindow__raiseWindow_View";
      case 394:
        return "c_KDDockWidgets__flutter__IndicatorWindow__releaseKeyboard";
      case 395:
        return "c_KDDockWidgets__flutter__IndicatorWindow__releaseMouse";
      case 1119:
        return "c_KDDockWidgets__flutter__IndicatorWindow__resize_Size";
      case 398:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setCursor_CursorShape";
      case 399:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setFixedHeight_int";
      case 400:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setFixedWidth_int";
      case 1120:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setGeometry_Rect";
      case 402:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setHeight_int";
      case 403:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMaximumSize_Size";
      case 404:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMinimumSize_Size";
      case 405:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setMouseTracking_bool";
      case 1121:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setObjectName_QString";
      case 406:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setParent_View";
      case 408:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setSize_int_int";
      case 409:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setViewName_QString";
      case 1122:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setVisible_bool";
      case 411:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWidth_int";
      case 412:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWindowOpacity_double";
      case 413:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setWindowTitle_QString";
      case 414:
        return "c_KDDockWidgets__flutter__IndicatorWindow__setZOrder_int";
      case 415:
        return "c_KDDockWidgets__flutter__IndicatorWindow__show";
      case 416:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showMaximized";
      case 417:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showMinimized";
      case 418:
        return "c_KDDockWidgets__flutter__IndicatorWindow__showNormal";
      case 420:
        return "c_KDDockWidgets__flutter__IndicatorWindow__update";
      case 1123:
        return "c_KDDockWidgets__flutter__IndicatorWindow__updateIndicatorVisibility";
      case 1124:
        return "c_KDDockWidgets__flutter__IndicatorWindow__updatePositions";
      case 1134:
        return "c_KDDockWidgets__flutter__IndicatorWindow__updatePositions_flutter_int_int_Group_int";
      case 421:
        return "c_KDDockWidgets__flutter__IndicatorWindow__viewName";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 342:
        return "activateWindow";
      case 352:
        return "close";
      case 354:
        return "createPlatformWindow";
      case 360:
        return "flags";
      case 361:
        return "geometry";
      case 362:
        return "grabMouse";
      case 365:
        return "hasFocus";
      case 367:
        return "hide";
      case 1115:
        return "hover";
      case 1126:
        return "hover_flutter";
      case 369:
        return "init";
      case 371:
        return "isActiveWindow";
      case 372:
        return "isExplicitlyHidden";
      case 373:
        return "isMaximized";
      case 374:
        return "isMinimized";
      case 444:
        return "isMounted";
      case 375:
        return "isNull";
      case 376:
        return "isRootView";
      case 377:
        return "isVisible";
      case 1116:
        return "isWindow";
      case 378:
        return "mapFromGlobal";
      case 379:
        return "mapTo";
      case 380:
        return "mapToGlobal";
      case 381:
        return "maxSizeHint";
      case 382:
        return "minSize";
      case 386:
        return "move_2";
      case 387:
        return "normalGeometry";
      case 447:
        return "onChildAdded";
      case 448:
        return "onChildRemoved";
      case 449:
        return "onChildVisibilityChanged";
      case 451:
        return "onGeometryChanged";
      case 453:
        return "onRebuildRequested";
      case 389:
        return "onResize_2";
      case 1117:
        return "posForIndicator";
      case 1130:
        return "posForIndicator_flutter";
      case 1118:
        return "raise";
      case 392:
        return "raiseAndActivate";
      case 456:
        return "raiseChild";
      case 457:
        return "raiseWindow";
      case 394:
        return "releaseKeyboard";
      case 395:
        return "releaseMouse";
      case 1119:
        return "resize";
      case 398:
        return "setCursor";
      case 399:
        return "setFixedHeight";
      case 400:
        return "setFixedWidth";
      case 1120:
        return "setGeometry";
      case 402:
        return "setHeight";
      case 403:
        return "setMaximumSize";
      case 404:
        return "setMinimumSize";
      case 405:
        return "setMouseTracking";
      case 1121:
        return "setObjectName";
      case 406:
        return "setParent";
      case 408:
        return "setSize_2";
      case 409:
        return "setViewName";
      case 1122:
        return "setVisible";
      case 411:
        return "setWidth";
      case 412:
        return "setWindowOpacity";
      case 413:
        return "setWindowTitle";
      case 414:
        return "setZOrder";
      case 415:
        return "show";
      case 416:
        return "showMaximized";
      case 417:
        return "showMinimized";
      case 418:
        return "showNormal";
      case 420:
        return "update";
      case 1123:
        return "updateIndicatorVisibility";
      case 1124:
        return "updatePositions";
      case 1134:
        return "updatePositions_flutter";
      case 421:
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
    final callback342 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback342, 342);
    const callbackExcept352 = 0;
    final callback352 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept352);
    registerCallback(thisCpp, callback352, 352);
    final callback354 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback354, 354);
    const callbackExcept360 = 0;
    final callback360 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept360);
    registerCallback(thisCpp, callback360, 360);
    final callback361 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback361, 361);
    final callback362 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback362, 362);
    const callbackExcept365 = 0;
    final callback365 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept365);
    registerCallback(thisCpp, callback365, 365);
    final callback367 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback367, 367);
    const callbackExcept1126 = 0;
    final callback1126 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.IndicatorWindow.hover_flutter_calledFromC,
            callbackExcept1126);
    registerCallback(thisCpp, callback1126, 1126);
    final callback369 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback369, 369);
    const callbackExcept371 = 0;
    final callback371 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept371);
    registerCallback(thisCpp, callback371, 371);
    const callbackExcept372 = 0;
    final callback372 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept372);
    registerCallback(thisCpp, callback372, 372);
    const callbackExcept373 = 0;
    final callback373 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept373);
    registerCallback(thisCpp, callback373, 373);
    const callbackExcept374 = 0;
    final callback374 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept374);
    registerCallback(thisCpp, callback374, 374);
    const callbackExcept444 = 0;
    final callback444 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMounted_calledFromC, callbackExcept444);
    registerCallback(thisCpp, callback444, 444);
    const callbackExcept375 = 0;
    final callback375 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept375);
    registerCallback(thisCpp, callback375, 375);
    const callbackExcept376 = 0;
    final callback376 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept376);
    registerCallback(thisCpp, callback376, 376);
    const callbackExcept377 = 0;
    final callback377 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept377);
    registerCallback(thisCpp, callback377, 377);
    final callback378 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback378, 378);
    final callback379 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback379, 379);
    final callback380 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback380, 380);
    final callback381 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback381, 381);
    final callback382 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback382, 382);
    final callback386 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback386, 386);
    final callback387 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback387, 387);
    final callback447 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback447, 447);
    final callback448 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback448, 448);
    final callback449 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback449, 449);
    final callback451 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback451, 451);
    final callback453 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback453, 453);
    const callbackExcept389 = 0;
    final callback389 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept389);
    registerCallback(thisCpp, callback389, 389);
    final callback1130 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter
                .IndicatorWindow.posForIndicator_flutter_calledFromC);
    registerCallback(thisCpp, callback1130, 1130);
    final callback392 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback392, 392);
    final callback456 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseChild_calledFromC);
    registerCallback(thisCpp, callback456, 456);
    final callback457 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseWindow_calledFromC);
    registerCallback(thisCpp, callback457, 457);
    final callback394 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback394, 394);
    final callback395 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback395, 395);
    final callback398 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback398, 398);
    final callback399 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback399, 399);
    final callback400 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback400, 400);
    final callback402 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback402, 402);
    final callback403 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback403, 403);
    final callback404 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback404, 404);
    final callback405 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback405, 405);
    final callback406 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback406, 406);
    final callback408 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback408, 408);
    final callback409 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback409, 409);
    final callback411 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback411, 411);
    final callback412 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback412, 412);
    final callback413 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback413, 413);
    final callback414 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback414, 414);
    final callback415 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback415, 415);
    final callback416 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback416, 416);
    final callback417 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback417, 417);
    final callback418 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback418, 418);
    final callback420 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback420, 420);
    const callbackExcept1134 = 0;
    final callback1134 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_ffi_Int32_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsFlutter.IndicatorWindow.updatePositions_flutter_calledFromC,
        callbackExcept1134);
    registerCallback(thisCpp, callback1134, 1134);
    final callback421 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.viewName_calledFromC);
    registerCallback(thisCpp, callback421, 421);
  }
}
