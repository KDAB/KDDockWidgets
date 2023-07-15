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
final _finalizerFunc =
    _dylib.lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(
        'c_KDDockWidgets__Core__View_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class View implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, View>();
  var _thisCpp = null;
  bool _needsAutoDelete = false;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete) _finalizer.attach(this, ptrvoid);
  }

  static bool isCached(var cppPointer) {
    return s_dartInstanceByCppPtr.containsKey(cppPointer.address);
  }

  factory View.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        View.fromCppPointer(cppPointer, needsAutoDelete)) as View;
  }
  View.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  View.init() {} //View(KDDockWidgets::Core::Controller * controller, KDDockWidgets::Core::ViewType arg__2)
  View(KDDWBindingsCore.Controller? controller, int arg__2) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__View__constructor_Controller_ViewType')
        .asFunction();
    thisCpp =
        func(controller == null ? ffi.nullptr : controller.thisCpp, arg__2);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // activateWindow()
  activateWindow() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(689))
        .asFunction();
    func(thisCpp);
  }

  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  } // asDockWidgetController() const

  KDDWBindingsCore.DockWidget asDockWidgetController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asDockWidgetController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DockWidget.fromCppPointer(result, false);
  } // asDropAreaController() const

  KDDWBindingsCore.DropArea asDropAreaController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asDropAreaController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DropArea.fromCppPointer(result, false);
  } // asFloatingWindowController() const

  KDDWBindingsCore.FloatingWindow asFloatingWindowController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asFloatingWindowController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.FloatingWindow.fromCppPointer(result, false);
  } // asGroupController() const

  KDDWBindingsCore.Group asGroupController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asGroupController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Group.fromCppPointer(result, false);
  } // asLayout() const

  KDDWBindingsCore.Layout asLayout() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asLayout')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Layout.fromCppPointer(result, false);
  } // asMainWindowController() const

  KDDWBindingsCore.MainWindow asMainWindowController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asMainWindowController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.MainWindow.fromCppPointer(result, false);
  } // asStackController() const

  KDDWBindingsCore.Stack asStackController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asStackController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Stack.fromCppPointer(result, false);
  } // asTabBarController() const

  KDDWBindingsCore.TabBar asTabBarController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asTabBarController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.TabBar.fromCppPointer(result, false);
  } // asTitleBarController() const

  KDDWBindingsCore.TitleBar asTitleBarController() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__asTitleBarController')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.TitleBar.fromCppPointer(result, false);
  } // close()

  bool close() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(699))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  } // controller() const

  KDDWBindingsCore.Controller controller() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__controller')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.Controller.fromCppPointer(result, false);
  } // createPlatformWindow()

  createPlatformWindow() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(701))
        .asFunction();
    func(thisCpp);
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  } // deliverViewEventToFilters(KDDockWidgets::Event * e)

  bool deliverViewEventToFilters(Event? e) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__deliverViewEventToFilters_Event')
        .asFunction();
    return func(thisCpp, e == null ? ffi.nullptr : e.thisCpp) != 0;
  } // dumpDebug()

  dumpDebug() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__dumpDebug')
        .asFunction();
    func(thisCpp);
  }

  static // equals(const KDDockWidgets::Core::View * one, const KDDockWidgets::Core::View * two)
      bool equals(KDDWBindingsCore.View? one, KDDWBindingsCore.View? two) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_static_KDDockWidgets__Core__View__equals_View_View')
        .asFunction();
    return func(one == null ? ffi.nullptr : one.thisCpp,
            two == null ? ffi.nullptr : two.thisCpp) !=
        0;
  } // equals(const KDDockWidgets::Core::View * other) const

  bool equals_2(KDDWBindingsCore.View? other) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__equals_View')
        .asFunction();
    return func(thisCpp, other == null ? ffi.nullptr : other.thisCpp) != 0;
  }

  static // firstParentOfType(KDDockWidgets::Core::View * view, KDDockWidgets::Core::ViewType arg__2)
      KDDWBindingsCore.Controller firstParentOfType(
          KDDWBindingsCore.View? view, int arg__2) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__View__firstParentOfType_View_ViewType')
        .asFunction();
    ffi.Pointer<void> result =
        func(view == null ? ffi.nullptr : view.thisCpp, arg__2);
    return KDDWBindingsCore.Controller.fromCppPointer(result, false);
  } // flags() const

  int flags() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(707))
        .asFunction();
    return func(thisCpp);
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  } // geometry() const

  Rect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(708))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  } // grabMouse()

  grabMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(709))
        .asFunction();
    func(thisCpp);
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static // hardcodedMinimumSize()
      Size hardcodedMinimumSize() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__View__hardcodedMinimumSize')
        .asFunction();
    ffi.Pointer<void> result = func();
    return Size.fromCppPointer(result, true);
  } // hasFocus() const

  bool hasFocus() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(712))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  } // height() const

  int height() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__height')
        .asFunction();
    return func(thisCpp);
  } // hide()

  hide() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(714))
        .asFunction();
    func(thisCpp);
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  } // inDtor() const

  bool inDtor() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__inDtor')
        .asFunction();
    return func(thisCpp) != 0;
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(716))
        .asFunction();
    func(thisCpp);
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  } // isActiveWindow() const

  bool isActiveWindow() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(718))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  } // isExplicitlyHidden() const

  bool isExplicitlyHidden() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(719))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isExplicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isExplicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExplicitlyHidden();
    return result ? 1 : 0;
  } // isMaximized() const

  bool isMaximized() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(720))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  } // isMinimized() const

  bool isMinimized() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(721))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  } // isNull() const

  bool isNull() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(722))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  } // isRootView() const

  bool isRootView() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(723))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  } // isVisible() const

  bool isVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(724))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  } // mapFromGlobal(KDDockWidgets::Point arg__1) const

  Point mapFromGlobal(Point arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(725))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapFromGlobal(KDDockWidgets::Point arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(Point.fromCppPointer(arg__1));
    return result.thisCpp;
  } // mapTo(KDDockWidgets::Core::View * arg__1, KDDockWidgets::Point arg__2) const

  Point mapTo(KDDWBindingsCore.View? arg__1, Point arg__2) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(726))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void> arg__2) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapTo(KDDockWidgets::Core::View * arg__1, KDDockWidgets::Point arg__2) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(arg__1),
        Point.fromCppPointer(arg__2));
    return result.thisCpp;
  } // mapToGlobal(KDDockWidgets::Point arg__1) const

  Point mapToGlobal(Point arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(727))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return Point.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapToGlobal(KDDockWidgets::Point arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(Point.fromCppPointer(arg__1));
    return result.thisCpp;
  } // maxSizeHint() const

  Size maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(728))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  } // minSize() const

  Size minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(729))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  } // minimumHeight() const

  int minimumHeight() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__minimumHeight')
        .asFunction();
    return func(thisCpp);
  } // minimumWidth() const

  int minimumWidth() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__minimumWidth')
        .asFunction();
    return func(thisCpp);
  } // move(KDDockWidgets::Point arg__1)

  move(Point arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__move_Point')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // move(int x, int y)

  move_2(int x, int y) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(733))
        .asFunction();
    func(thisCpp, x, y);
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  } // normalGeometry() const

  Rect normalGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(734))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  } // onResize(KDDockWidgets::Size arg__1)

  bool onResize(Size arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__onResize_Size')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // onResize(int h, int w)

  bool onResize_2(int h, int w) {
    final bool_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(736))
        .asFunction();
    return func(thisCpp, h, w) != 0;
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
    return result ? 1 : 0;
  } // pos() const

  Point pos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__pos')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Point.fromCppPointer(result, true);
  } // raise()

  raise() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(738))
        .asFunction();
    func(thisCpp);
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  } // raiseAndActivate()

  raiseAndActivate() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(739))
        .asFunction();
    func(thisCpp);
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  } // rect() const

  Rect rect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__rect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Rect.fromCppPointer(result, true);
  } // releaseKeyboard()

  releaseKeyboard() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(741))
        .asFunction();
    func(thisCpp);
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  } // releaseMouse()

  releaseMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(742))
        .asFunction();
    func(thisCpp);
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  } // resize(KDDockWidgets::Size arg__1)

  resize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__resize_Size')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // resize(int w, int h)

  resize_2(int w, int h) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__View__resize_int_int')
        .asFunction();
    func(thisCpp, w, h);
  } // setCursor(Qt::CursorShape arg__1)

  setCursor(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(745))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setCursor(Qt::CursorShape arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(arg__1);
  } // setFixedHeight(int arg__1)

  setFixedHeight(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(746))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setFixedHeight_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setFixedHeight(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(arg__1);
  } // setFixedWidth(int arg__1)

  setFixedWidth(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(747))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setFixedWidth(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(arg__1);
  } // setGeometry(KDDockWidgets::Rect arg__1)

  setGeometry(Rect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(748))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setGeometry(KDDockWidgets::Rect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(Rect.fromCppPointer(arg__1));
  } // setHeight(int height)

  setHeight(int height) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(749))
        .asFunction();
    func(thisCpp, height);
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int height) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setHeight(int height)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(height);
  } // setMaximumSize(KDDockWidgets::Size sz)

  setMaximumSize(Size sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(750))
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMaximumSize(KDDockWidgets::Size sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(Size.fromCppPointer(sz));
  } // setMinimumSize(KDDockWidgets::Size arg__1)

  setMinimumSize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(751))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMinimumSize(KDDockWidgets::Size arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(Size.fromCppPointer(arg__1));
  } // setMouseTracking(bool arg__1)

  setMouseTracking(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(752))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMouseTracking(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(arg__1 != 0);
  } // setParent(KDDockWidgets::Core::View * arg__1)

  setParent(KDDWBindingsCore.View? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(753))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setParent(KDDockWidgets::Core::View * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(arg__1));
  } // setSize(KDDockWidgets::Size arg__1)

  setSize(Size arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__setSize_Size')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setSize(int width, int height)

  setSize_2(int width, int height) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(755))
        .asFunction();
    func(thisCpp, width, height);
  }

  static void setSize_2_calledFromC(
      ffi.Pointer<void> thisCpp, int width, int height) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setSize(int width, int height)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(width, height);
  } // setViewName(const QString & arg__1)

  setViewName(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(756))
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setViewName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setViewName(const QString & arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setViewName(QString.fromCppPointer(arg__1).toDartString());
  } // setVisible(bool arg__1)

  setVisible(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(757))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setVisible(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(arg__1 != 0);
  } // setWidth(int width)

  setWidth(int width) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(758))
        .asFunction();
    func(thisCpp, width);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int width) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setWidth(int width)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(width);
  } // setWindowOpacity(double arg__1)

  setWindowOpacity(double arg__1) {
    final void_Func_voidstar_double func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Double_FFI>>(
            cFunctionSymbolName(759))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setWindowOpacity(double arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(arg__1);
  } // setWindowTitle(const QString & title)

  setWindowTitle(String? title) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(760))
        .asFunction();
    func(thisCpp, title?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  } // setZOrder(int arg__1)

  setZOrder(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(761))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setZOrder(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(arg__1);
  } // show()

  show() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(762))
        .asFunction();
    func(thisCpp);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  } // showMaximized()

  showMaximized() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(763))
        .asFunction();
    func(thisCpp);
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  } // showMinimized()

  showMinimized() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(764))
        .asFunction();
    func(thisCpp);
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  } // showNormal()

  showNormal() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(765))
        .asFunction();
    func(thisCpp);
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  } // size() const

  Size size() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__size')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return Size.fromCppPointer(result, true);
  } // update()

  update() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(767))
        .asFunction();
    func(thisCpp);
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print("Dart instance not found for View::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  } // viewName() const

  QString viewName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(768))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> viewName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::viewName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.viewName();
    return result.thisCpp;
  } // width() const

  int width() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__width')
        .asFunction();
    return func(thisCpp);
  } // x() const

  int x() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__x')
        .asFunction();
    return func(thisCpp);
  } // y() const

  int y() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__y')
        .asFunction();
    return func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 689:
        return "c_KDDockWidgets__Core__View__activateWindow";
      case 699:
        return "c_KDDockWidgets__Core__View__close";
      case 701:
        return "c_KDDockWidgets__Core__View__createPlatformWindow";
      case 707:
        return "c_KDDockWidgets__Core__View__flags";
      case 708:
        return "c_KDDockWidgets__Core__View__geometry";
      case 709:
        return "c_KDDockWidgets__Core__View__grabMouse";
      case 712:
        return "c_KDDockWidgets__Core__View__hasFocus";
      case 714:
        return "c_KDDockWidgets__Core__View__hide";
      case 716:
        return "c_KDDockWidgets__Core__View__init";
      case 718:
        return "c_KDDockWidgets__Core__View__isActiveWindow";
      case 719:
        return "c_KDDockWidgets__Core__View__isExplicitlyHidden";
      case 720:
        return "c_KDDockWidgets__Core__View__isMaximized";
      case 721:
        return "c_KDDockWidgets__Core__View__isMinimized";
      case 722:
        return "c_KDDockWidgets__Core__View__isNull";
      case 723:
        return "c_KDDockWidgets__Core__View__isRootView";
      case 724:
        return "c_KDDockWidgets__Core__View__isVisible";
      case 725:
        return "c_KDDockWidgets__Core__View__mapFromGlobal_Point";
      case 726:
        return "c_KDDockWidgets__Core__View__mapTo_View_Point";
      case 727:
        return "c_KDDockWidgets__Core__View__mapToGlobal_Point";
      case 728:
        return "c_KDDockWidgets__Core__View__maxSizeHint";
      case 729:
        return "c_KDDockWidgets__Core__View__minSize";
      case 733:
        return "c_KDDockWidgets__Core__View__move_int_int";
      case 734:
        return "c_KDDockWidgets__Core__View__normalGeometry";
      case 736:
        return "c_KDDockWidgets__Core__View__onResize_int_int";
      case 738:
        return "c_KDDockWidgets__Core__View__raise";
      case 739:
        return "c_KDDockWidgets__Core__View__raiseAndActivate";
      case 741:
        return "c_KDDockWidgets__Core__View__releaseKeyboard";
      case 742:
        return "c_KDDockWidgets__Core__View__releaseMouse";
      case 745:
        return "c_KDDockWidgets__Core__View__setCursor_CursorShape";
      case 746:
        return "c_KDDockWidgets__Core__View__setFixedHeight_int";
      case 747:
        return "c_KDDockWidgets__Core__View__setFixedWidth_int";
      case 748:
        return "c_KDDockWidgets__Core__View__setGeometry_Rect";
      case 749:
        return "c_KDDockWidgets__Core__View__setHeight_int";
      case 750:
        return "c_KDDockWidgets__Core__View__setMaximumSize_Size";
      case 751:
        return "c_KDDockWidgets__Core__View__setMinimumSize_Size";
      case 752:
        return "c_KDDockWidgets__Core__View__setMouseTracking_bool";
      case 753:
        return "c_KDDockWidgets__Core__View__setParent_View";
      case 755:
        return "c_KDDockWidgets__Core__View__setSize_int_int";
      case 756:
        return "c_KDDockWidgets__Core__View__setViewName_QString";
      case 757:
        return "c_KDDockWidgets__Core__View__setVisible_bool";
      case 758:
        return "c_KDDockWidgets__Core__View__setWidth_int";
      case 759:
        return "c_KDDockWidgets__Core__View__setWindowOpacity_double";
      case 760:
        return "c_KDDockWidgets__Core__View__setWindowTitle_QString";
      case 761:
        return "c_KDDockWidgets__Core__View__setZOrder_int";
      case 762:
        return "c_KDDockWidgets__Core__View__show";
      case 763:
        return "c_KDDockWidgets__Core__View__showMaximized";
      case 764:
        return "c_KDDockWidgets__Core__View__showMinimized";
      case 765:
        return "c_KDDockWidgets__Core__View__showNormal";
      case 767:
        return "c_KDDockWidgets__Core__View__update";
      case 768:
        return "c_KDDockWidgets__Core__View__viewName";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 689:
        return "activateWindow";
      case 699:
        return "close";
      case 701:
        return "createPlatformWindow";
      case 707:
        return "flags";
      case 708:
        return "geometry";
      case 709:
        return "grabMouse";
      case 712:
        return "hasFocus";
      case 714:
        return "hide";
      case 716:
        return "init";
      case 718:
        return "isActiveWindow";
      case 719:
        return "isExplicitlyHidden";
      case 720:
        return "isMaximized";
      case 721:
        return "isMinimized";
      case 722:
        return "isNull";
      case 723:
        return "isRootView";
      case 724:
        return "isVisible";
      case 725:
        return "mapFromGlobal";
      case 726:
        return "mapTo";
      case 727:
        return "mapToGlobal";
      case 728:
        return "maxSizeHint";
      case 729:
        return "minSize";
      case 733:
        return "move_2";
      case 734:
        return "normalGeometry";
      case 736:
        return "onResize_2";
      case 738:
        return "raise";
      case 739:
        return "raiseAndActivate";
      case 741:
        return "releaseKeyboard";
      case 742:
        return "releaseMouse";
      case 745:
        return "setCursor";
      case 746:
        return "setFixedHeight";
      case 747:
        return "setFixedWidth";
      case 748:
        return "setGeometry";
      case 749:
        return "setHeight";
      case 750:
        return "setMaximumSize";
      case 751:
        return "setMinimumSize";
      case 752:
        return "setMouseTracking";
      case 753:
        return "setParent";
      case 755:
        return "setSize_2";
      case 756:
        return "setViewName";
      case 757:
        return "setVisible";
      case 758:
        return "setWidth";
      case 759:
        return "setWindowOpacity";
      case 760:
        return "setWindowTitle";
      case 761:
        return "setZOrder";
      case 762:
        return "show";
      case 763:
        return "showMaximized";
      case 764:
        return "showMinimized";
      case 765:
        return "showNormal";
      case 767:
        return "update";
      case 768:
        return "viewName";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__View__registerVirtualMethodCallback')
        .asFunction();
    final callback689 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback689, 689);
    const callbackExcept699 = 0;
    final callback699 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.close_calledFromC, callbackExcept699);
    registerCallback(thisCpp, callback699, 699);
    final callback701 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback701, 701);
    const callbackExcept707 = 0;
    final callback707 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.flags_calledFromC, callbackExcept707);
    registerCallback(thisCpp, callback707, 707);
    final callback708 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.geometry_calledFromC);
    registerCallback(thisCpp, callback708, 708);
    final callback709 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback709, 709);
    const callbackExcept712 = 0;
    final callback712 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.hasFocus_calledFromC, callbackExcept712);
    registerCallback(thisCpp, callback712, 712);
    final callback714 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.hide_calledFromC);
    registerCallback(thisCpp, callback714, 714);
    final callback716 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback716, 716);
    const callbackExcept718 = 0;
    final callback718 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isActiveWindow_calledFromC, callbackExcept718);
    registerCallback(thisCpp, callback718, 718);
    const callbackExcept719 = 0;
    final callback719 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isExplicitlyHidden_calledFromC,
        callbackExcept719);
    registerCallback(thisCpp, callback719, 719);
    const callbackExcept720 = 0;
    final callback720 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isMaximized_calledFromC, callbackExcept720);
    registerCallback(thisCpp, callback720, 720);
    const callbackExcept721 = 0;
    final callback721 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isMinimized_calledFromC, callbackExcept721);
    registerCallback(thisCpp, callback721, 721);
    const callbackExcept722 = 0;
    final callback722 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept722);
    registerCallback(thisCpp, callback722, 722);
    const callbackExcept723 = 0;
    final callback723 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isRootView_calledFromC, callbackExcept723);
    registerCallback(thisCpp, callback723, 723);
    const callbackExcept724 = 0;
    final callback724 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isVisible_calledFromC, callbackExcept724);
    registerCallback(thisCpp, callback724, 724);
    final callback725 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback725, 725);
    final callback726 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback726, 726);
    final callback727 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback727, 727);
    final callback728 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback728, 728);
    final callback729 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minSize_calledFromC);
    registerCallback(thisCpp, callback729, 729);
    final callback733 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.move_2_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    final callback734 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback734, 734);
    const callbackExcept736 = 0;
    final callback736 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept736);
    registerCallback(thisCpp, callback736, 736);
    final callback738 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.raise_calledFromC);
    registerCallback(thisCpp, callback738, 738);
    final callback739 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback739, 739);
    final callback741 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback741, 741);
    final callback742 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback742, 742);
    final callback745 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback745, 745);
    final callback746 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback746, 746);
    final callback747 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback747, 747);
    final callback748 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback748, 748);
    final callback749 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback749, 749);
    final callback750 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback750, 750);
    final callback751 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback751, 751);
    final callback752 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsCore.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback752, 752);
    final callback753 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setParent_calledFromC);
    registerCallback(thisCpp, callback753, 753);
    final callback755 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback755, 755);
    final callback756 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback756, 756);
    final callback757 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsCore.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback757, 757);
    final callback758 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback758, 758);
    final callback759 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsCore.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback759, 759);
    final callback760 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback760, 760);
    final callback761 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback761, 761);
    final callback762 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.show_calledFromC);
    registerCallback(thisCpp, callback762, 762);
    final callback763 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback763, 763);
    final callback764 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback764, 764);
    final callback765 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback765, 765);
    final callback767 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.update_calledFromC);
    registerCallback(thisCpp, callback767, 767);
    final callback768 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.viewName_calledFromC);
    registerCallback(thisCpp, callback768, 768);
  }
}
