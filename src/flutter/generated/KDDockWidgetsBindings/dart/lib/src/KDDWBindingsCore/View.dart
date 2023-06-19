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
            cFunctionSymbolName(921))
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
            cFunctionSymbolName(931))
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
            cFunctionSymbolName(933))
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
            cFunctionSymbolName(939))
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

  QRect geometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(940))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
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
            cFunctionSymbolName(941))
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
      QSize hardcodedMinimumSize() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__View__hardcodedMinimumSize')
        .asFunction();
    ffi.Pointer<void> result = func();
    return QSize.fromCppPointer(result, true);
  } // hasFocus() const

  bool hasFocus() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(944))
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
            cFunctionSymbolName(946))
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
            cFunctionSymbolName(948))
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
            cFunctionSymbolName(950))
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
            cFunctionSymbolName(951))
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
            cFunctionSymbolName(952))
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
            cFunctionSymbolName(953))
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
            cFunctionSymbolName(954))
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
            cFunctionSymbolName(955))
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
            cFunctionSymbolName(956))
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
  } // mapFromGlobal(QPoint arg__1) const

  QPoint mapFromGlobal(QPoint arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(957))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapFromGlobal(QPoint arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(arg__1));
    return result.thisCpp;
  } // mapTo(KDDockWidgets::Core::View * arg__1, QPoint arg__2) const

  QPoint mapTo(KDDWBindingsCore.View? arg__1, QPoint arg__2) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(958))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void> arg__2) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapTo(KDDockWidgets::Core::View * arg__1, QPoint arg__2) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(arg__1),
        QPoint.fromCppPointer(arg__2));
    return result.thisCpp;
  } // mapToGlobal(QPoint arg__1) const

  QPoint mapToGlobal(QPoint arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(959))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::mapToGlobal(QPoint arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(arg__1));
    return result.thisCpp;
  } // maxSizeHint() const

  QSize maxSizeHint() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(960))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
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

  QSize minSize() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(961))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
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
  } // move(QPoint arg__1)

  move(QPoint arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__move_QPoint')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // move(int x, int y)

  move_2(int x, int y) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(965))
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

  QRect normalGeometry() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(966))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
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
  } // onResize(QSize arg__1)

  bool onResize(QSize arg__1) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__onResize_QSize')
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp) != 0;
  } // onResize(int h, int w)

  bool onResize_2(int h, int w) {
    final bool_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(968))
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

  QPoint pos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__pos')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  } // raise()

  raise() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(970))
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
            cFunctionSymbolName(971))
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

  QRect rect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__rect')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  } // releaseKeyboard()

  releaseKeyboard() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(973))
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
            cFunctionSymbolName(974))
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
  } // resize(QSize arg__1)

  resize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__resize_QSize')
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
            cFunctionSymbolName(977))
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
            cFunctionSymbolName(978))
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
            cFunctionSymbolName(979))
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
  } // setGeometry(QRect arg__1)

  setGeometry(QRect arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(980))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  } // setHeight(int height)

  setHeight(int height) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(981))
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
  } // setMaximumSize(QSize sz)

  setMaximumSize(QSize sz) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(982))
        .asFunction();
    func(thisCpp, sz == null ? ffi.nullptr : sz.thisCpp);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  } // setMinimumSize(QSize arg__1)

  setMinimumSize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(983))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for View::setMinimumSize(QSize arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(arg__1));
  } // setMouseTracking(bool arg__1)

  setMouseTracking(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(984))
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
            cFunctionSymbolName(985))
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
  } // setSize(QSize arg__1)

  setSize(QSize arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__setSize_QSize')
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  } // setSize(int width, int height)

  setSize_2(int width, int height) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(987))
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
            cFunctionSymbolName(988))
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
            cFunctionSymbolName(989))
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
            cFunctionSymbolName(990))
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
            cFunctionSymbolName(991))
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
            cFunctionSymbolName(992))
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
            cFunctionSymbolName(993))
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
            cFunctionSymbolName(994))
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
            cFunctionSymbolName(995))
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
            cFunctionSymbolName(996))
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
            cFunctionSymbolName(997))
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

  QSize size() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__View__size')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QSize.fromCppPointer(result, true);
  } // update()

  update() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(999))
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
            cFunctionSymbolName(1000))
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
      case 921:
        return "c_KDDockWidgets__Core__View__activateWindow";
      case 931:
        return "c_KDDockWidgets__Core__View__close";
      case 933:
        return "c_KDDockWidgets__Core__View__createPlatformWindow";
      case 939:
        return "c_KDDockWidgets__Core__View__flags";
      case 940:
        return "c_KDDockWidgets__Core__View__geometry";
      case 941:
        return "c_KDDockWidgets__Core__View__grabMouse";
      case 944:
        return "c_KDDockWidgets__Core__View__hasFocus";
      case 946:
        return "c_KDDockWidgets__Core__View__hide";
      case 948:
        return "c_KDDockWidgets__Core__View__init";
      case 950:
        return "c_KDDockWidgets__Core__View__isActiveWindow";
      case 951:
        return "c_KDDockWidgets__Core__View__isExplicitlyHidden";
      case 952:
        return "c_KDDockWidgets__Core__View__isMaximized";
      case 953:
        return "c_KDDockWidgets__Core__View__isMinimized";
      case 954:
        return "c_KDDockWidgets__Core__View__isNull";
      case 955:
        return "c_KDDockWidgets__Core__View__isRootView";
      case 956:
        return "c_KDDockWidgets__Core__View__isVisible";
      case 957:
        return "c_KDDockWidgets__Core__View__mapFromGlobal_QPoint";
      case 958:
        return "c_KDDockWidgets__Core__View__mapTo_View_QPoint";
      case 959:
        return "c_KDDockWidgets__Core__View__mapToGlobal_QPoint";
      case 960:
        return "c_KDDockWidgets__Core__View__maxSizeHint";
      case 961:
        return "c_KDDockWidgets__Core__View__minSize";
      case 965:
        return "c_KDDockWidgets__Core__View__move_int_int";
      case 966:
        return "c_KDDockWidgets__Core__View__normalGeometry";
      case 968:
        return "c_KDDockWidgets__Core__View__onResize_int_int";
      case 970:
        return "c_KDDockWidgets__Core__View__raise";
      case 971:
        return "c_KDDockWidgets__Core__View__raiseAndActivate";
      case 973:
        return "c_KDDockWidgets__Core__View__releaseKeyboard";
      case 974:
        return "c_KDDockWidgets__Core__View__releaseMouse";
      case 977:
        return "c_KDDockWidgets__Core__View__setCursor_CursorShape";
      case 978:
        return "c_KDDockWidgets__Core__View__setFixedHeight_int";
      case 979:
        return "c_KDDockWidgets__Core__View__setFixedWidth_int";
      case 980:
        return "c_KDDockWidgets__Core__View__setGeometry_QRect";
      case 981:
        return "c_KDDockWidgets__Core__View__setHeight_int";
      case 982:
        return "c_KDDockWidgets__Core__View__setMaximumSize_QSize";
      case 983:
        return "c_KDDockWidgets__Core__View__setMinimumSize_QSize";
      case 984:
        return "c_KDDockWidgets__Core__View__setMouseTracking_bool";
      case 985:
        return "c_KDDockWidgets__Core__View__setParent_View";
      case 987:
        return "c_KDDockWidgets__Core__View__setSize_int_int";
      case 988:
        return "c_KDDockWidgets__Core__View__setViewName_QString";
      case 989:
        return "c_KDDockWidgets__Core__View__setVisible_bool";
      case 990:
        return "c_KDDockWidgets__Core__View__setWidth_int";
      case 991:
        return "c_KDDockWidgets__Core__View__setWindowOpacity_double";
      case 992:
        return "c_KDDockWidgets__Core__View__setWindowTitle_QString";
      case 993:
        return "c_KDDockWidgets__Core__View__setZOrder_int";
      case 994:
        return "c_KDDockWidgets__Core__View__show";
      case 995:
        return "c_KDDockWidgets__Core__View__showMaximized";
      case 996:
        return "c_KDDockWidgets__Core__View__showMinimized";
      case 997:
        return "c_KDDockWidgets__Core__View__showNormal";
      case 999:
        return "c_KDDockWidgets__Core__View__update";
      case 1000:
        return "c_KDDockWidgets__Core__View__viewName";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 921:
        return "activateWindow";
      case 931:
        return "close";
      case 933:
        return "createPlatformWindow";
      case 939:
        return "flags";
      case 940:
        return "geometry";
      case 941:
        return "grabMouse";
      case 944:
        return "hasFocus";
      case 946:
        return "hide";
      case 948:
        return "init";
      case 950:
        return "isActiveWindow";
      case 951:
        return "isExplicitlyHidden";
      case 952:
        return "isMaximized";
      case 953:
        return "isMinimized";
      case 954:
        return "isNull";
      case 955:
        return "isRootView";
      case 956:
        return "isVisible";
      case 957:
        return "mapFromGlobal";
      case 958:
        return "mapTo";
      case 959:
        return "mapToGlobal";
      case 960:
        return "maxSizeHint";
      case 961:
        return "minSize";
      case 965:
        return "move_2";
      case 966:
        return "normalGeometry";
      case 968:
        return "onResize_2";
      case 970:
        return "raise";
      case 971:
        return "raiseAndActivate";
      case 973:
        return "releaseKeyboard";
      case 974:
        return "releaseMouse";
      case 977:
        return "setCursor";
      case 978:
        return "setFixedHeight";
      case 979:
        return "setFixedWidth";
      case 980:
        return "setGeometry";
      case 981:
        return "setHeight";
      case 982:
        return "setMaximumSize";
      case 983:
        return "setMinimumSize";
      case 984:
        return "setMouseTracking";
      case 985:
        return "setParent";
      case 987:
        return "setSize_2";
      case 988:
        return "setViewName";
      case 989:
        return "setVisible";
      case 990:
        return "setWidth";
      case 991:
        return "setWindowOpacity";
      case 992:
        return "setWindowTitle";
      case 993:
        return "setZOrder";
      case 994:
        return "show";
      case 995:
        return "showMaximized";
      case 996:
        return "showMinimized";
      case 997:
        return "showNormal";
      case 999:
        return "update";
      case 1000:
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
    final callback921 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback921, 921);
    const callbackExcept931 = 0;
    final callback931 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.close_calledFromC, callbackExcept931);
    registerCallback(thisCpp, callback931, 931);
    final callback933 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback933, 933);
    const callbackExcept939 = 0;
    final callback939 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.flags_calledFromC, callbackExcept939);
    registerCallback(thisCpp, callback939, 939);
    final callback940 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.geometry_calledFromC);
    registerCallback(thisCpp, callback940, 940);
    final callback941 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback941, 941);
    const callbackExcept944 = 0;
    final callback944 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.hasFocus_calledFromC, callbackExcept944);
    registerCallback(thisCpp, callback944, 944);
    final callback946 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.hide_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback948 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback948, 948);
    const callbackExcept950 = 0;
    final callback950 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isActiveWindow_calledFromC, callbackExcept950);
    registerCallback(thisCpp, callback950, 950);
    const callbackExcept951 = 0;
    final callback951 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isExplicitlyHidden_calledFromC,
        callbackExcept951);
    registerCallback(thisCpp, callback951, 951);
    const callbackExcept952 = 0;
    final callback952 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isMaximized_calledFromC, callbackExcept952);
    registerCallback(thisCpp, callback952, 952);
    const callbackExcept953 = 0;
    final callback953 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isMinimized_calledFromC, callbackExcept953);
    registerCallback(thisCpp, callback953, 953);
    const callbackExcept954 = 0;
    final callback954 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept954);
    registerCallback(thisCpp, callback954, 954);
    const callbackExcept955 = 0;
    final callback955 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isRootView_calledFromC, callbackExcept955);
    registerCallback(thisCpp, callback955, 955);
    const callbackExcept956 = 0;
    final callback956 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isVisible_calledFromC, callbackExcept956);
    registerCallback(thisCpp, callback956, 956);
    final callback957 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    final callback958 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback958, 958);
    final callback959 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback960 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback960, 960);
    final callback961 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minSize_calledFromC);
    registerCallback(thisCpp, callback961, 961);
    final callback965 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.move_2_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    const callbackExcept968 = 0;
    final callback968 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept968);
    registerCallback(thisCpp, callback968, 968);
    final callback970 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.raise_calledFromC);
    registerCallback(thisCpp, callback970, 970);
    final callback971 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback971, 971);
    final callback973 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback973, 973);
    final callback974 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback974, 974);
    final callback977 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback977, 977);
    final callback978 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback978, 978);
    final callback979 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback979, 979);
    final callback980 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback980, 980);
    final callback981 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback982 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback982, 982);
    final callback983 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback983, 983);
    final callback984 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsCore.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback985 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setParent_calledFromC);
    registerCallback(thisCpp, callback985, 985);
    final callback987 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback987, 987);
    final callback988 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback988, 988);
    final callback989 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsCore.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback990 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback990, 990);
    final callback991 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsCore.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback991, 991);
    final callback992 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.show_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback995 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback996 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback996, 996);
    final callback997 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback997, 997);
    final callback999 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.update_calledFromC);
    registerCallback(thisCpp, callback999, 999);
    final callback1000 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.View.viewName_calledFromC);
    registerCallback(thisCpp, callback1000, 1000);
  }
}
