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
        'c_KDDockWidgets__Core__Platform_Finalizer');
final _finalizer = ffi.NativeFinalizer(_finalizerFunc.cast());

class Platform implements ffi.Finalizable {
  static var s_dartInstanceByCppPtr = Map<int, Platform>();
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

  factory Platform.fromCache(var cppPointer, [needsAutoDelete = false]) {
    return (s_dartInstanceByCppPtr[cppPointer.address] ??
        Platform.fromCppPointer(cppPointer, needsAutoDelete)) as Platform;
  }
  Platform.fromCppPointer(var cppPointer, [this._needsAutoDelete = false]) {
    thisCpp = cppPointer;
  }
  Platform.init() {}
  static int get s_logicalDpiFactorOverride {
    final int_Func_void func = _dylib
        .lookup<ffi.NativeFunction<int_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Platform___get_s_logicalDpiFactorOverride')
        .asFunction();
    return func();
  }

  static set s_logicalDpiFactorOverride(int s_logicalDpiFactorOverride_) {
    final void_Func_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__Core__Platform___set_s_logicalDpiFactorOverride_int')
        .asFunction();
    func(s_logicalDpiFactorOverride_);
  } //Platform()

  Platform() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Core__Platform__constructor')
        .asFunction();
    thisCpp = func();
    KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // applicationName() const
  QString applicationName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(516))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> applicationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::applicationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.applicationName();
    return result.thisCpp;
  } // createDefaultViewFactory()

  KDDWBindingsCore.ViewFactory createDefaultViewFactory() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(517))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.ViewFactory.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createDefaultViewFactory_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createDefaultViewFactory()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDefaultViewFactory();
    return result.thisCpp;
  } // createMainWindow(const QString & uniqueName, KDDockWidgets::Core::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags arg__5) const

  KDDWBindingsCore.MainWindow createMainWindow(
      String? uniqueName, CreateViewOptions arg__2,
      {int options =
          KDDockWidgets_MainWindowOption.MainWindowOption_HasCentralFrame,
      required KDDWBindingsCore.View? parent,
      int arg__5 = 0}) {
    final voidstar_Func_voidstar_voidstar_voidstar_int_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(518))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        uniqueName?.toNativeUtf8() ?? ffi.nullptr,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp,
        options,
        parent == null ? ffi.nullptr : parent.thisCpp,
        arg__5);
    return KDDWBindingsCore.MainWindow.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createMainWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? uniqueName,
      ffi.Pointer<void> arg__2,
      int options,
      ffi.Pointer<void>? parent,
      int arg__5) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createMainWindow(const QString & uniqueName, KDDockWidgets::Core::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags arg__5) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createMainWindow(
        QString.fromCppPointer(uniqueName).toDartString(),
        CreateViewOptions.fromCppPointer(arg__2),
        options: options,
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
        arg__5: arg__5);
    return result.thisCpp;
  } // createView(KDDockWidgets::Core::Controller * arg__1, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createView(KDDWBindingsCore.Controller? arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(519))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createView_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createView(KDDockWidgets::Core::Controller * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createView(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.Controller.fromCppPointer(arg__1),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // cursorPos() const

  QPoint cursorPos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(520))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> cursorPos_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::cursorPos() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.cursorPos();
    return result.thisCpp;
  } // dumpManagedBacktrace()

  dumpManagedBacktrace() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(521))
        .asFunction();
    func(thisCpp);
  }

  static void dumpManagedBacktrace_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::dumpManagedBacktrace()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.dumpManagedBacktrace();
  } // hasActivePopup() const

  bool hasActivePopup() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(523))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int hasActivePopup_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::hasActivePopup() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasActivePopup();
    return result ? 1 : 0;
  } // inDisallowedDragView(QPoint globalPos) const

  bool inDisallowedDragView(QPoint globalPos) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(524))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp) !=
        0;
  }

  static int inDisallowedDragView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::inDisallowedDragView(QPoint globalPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result =
        dartInstance.inDisallowedDragView(QPoint.fromCppPointer(globalPos));
    return result ? 1 : 0;
  } // installMessageHandler()

  installMessageHandler() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(525))
        .asFunction();
    func(thisCpp);
  }

  static void installMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::installMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.installMessageHandler();
  }

  static // instance()
      KDDWBindingsCore.Platform instance() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Platform__instance')
        .asFunction();
    ffi.Pointer<void> result = func();
    return KDDWBindingsCore.Platform.fromCppPointer(result, false);
  }

  static // isInitialized()
      bool isInitialized() {
    final bool_Func_void func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Platform__isInitialized')
        .asFunction();
    return func() != 0;
  } // isLeftMouseButtonPressed() const

  bool isLeftMouseButtonPressed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(528))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isLeftMouseButtonPressed_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::isLeftMouseButtonPressed() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isLeftMouseButtonPressed();
    return result ? 1 : 0;
  } // isProcessingAppQuitEvent() const

  bool isProcessingAppQuitEvent() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(529))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isProcessingAppQuitEvent_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::isProcessingAppQuitEvent() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isProcessingAppQuitEvent();
    return result ? 1 : 0;
  } // isQt() const

  bool isQt() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform__isQt')
        .asFunction();
    return func(thisCpp) != 0;
  } // isQtQuick() const

  bool isQtQuick() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform__isQtQuick')
        .asFunction();
    return func(thisCpp) != 0;
  } // isQtWidgets() const

  bool isQtWidgets() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform__isQtWidgets')
        .asFunction();
    return func(thisCpp) != 0;
  } // name() const

  String name() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            cFunctionSymbolName(533))
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }

  static ffi.Pointer<Utf8> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::name() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.name();
    return result.toNativeUtf8();
  } // onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)

  onFloatingWindowCreated(KDDWBindingsCore.FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(534))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onFloatingWindowCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onFloatingWindowCreated((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.FloatingWindow.fromCppPointer(arg__1));
  } // onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)

  onFloatingWindowDestroyed(KDDWBindingsCore.FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(535))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onFloatingWindowDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onFloatingWindowDestroyed(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.FloatingWindow.fromCppPointer(arg__1));
  } // onMainWindowCreated(KDDockWidgets::Core::MainWindow * arg__1)

  onMainWindowCreated(KDDWBindingsCore.MainWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(536))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onMainWindowCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onMainWindowCreated(KDDockWidgets::Core::MainWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onMainWindowCreated((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.MainWindow.fromCppPointer(arg__1));
  } // onMainWindowDestroyed(KDDockWidgets::Core::MainWindow * arg__1)

  onMainWindowDestroyed(KDDWBindingsCore.MainWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(537))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onMainWindowDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onMainWindowDestroyed(KDDockWidgets::Core::MainWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onMainWindowDestroyed((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.MainWindow.fromCppPointer(arg__1));
  } // pauseForDebugger()

  pauseForDebugger() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(538))
        .asFunction();
    func(thisCpp);
  }

  static void pauseForDebugger_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::pauseForDebugger()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.pauseForDebugger();
  } // restoreMouseCursor()

  restoreMouseCursor() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(539))
        .asFunction();
    func(thisCpp);
  }

  static void restoreMouseCursor_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::restoreMouseCursor()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.restoreMouseCursor();
  } // runDelayed(int ms, KDDockWidgets::Core::DelayedCall * c)

  runDelayed(int ms, KDDWBindingsCore.DelayedCall? c) {
    final void_Func_voidstar_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            cFunctionSymbolName(540))
        .asFunction();
    func(thisCpp, ms, c == null ? ffi.nullptr : c.thisCpp);
  }

  static void runDelayed_calledFromC(
      ffi.Pointer<void> thisCpp, int ms, ffi.Pointer<void>? c) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::runDelayed(int ms, KDDockWidgets::Core::DelayedCall * c)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.runDelayed(
        ms,
        (c == null || c.address == 0)
            ? null
            : KDDWBindingsCore.DelayedCall.fromCppPointer(c));
  } // screenNumberFor(KDDockWidgets::Core::View * arg__1) const

  int screenNumberFor(KDDWBindingsCore.View? arg__1) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(541))
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static int screenNumberFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::screenNumberFor(KDDockWidgets::Core::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenNumberFor(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(arg__1));
    return result;
  } // screenSizeFor(KDDockWidgets::Core::View * arg__1) const

  QSize screenSizeFor(KDDWBindingsCore.View? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(542))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> screenSizeFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::screenSizeFor(KDDockWidgets::Core::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenSizeFor(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(arg__1));
    return result.thisCpp;
  } // sendEvent(KDDockWidgets::Core::View * arg__1, KDDockWidgets::Event * arg__2) const

  sendEvent(KDDWBindingsCore.View? arg__1, Event? arg__2) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(543))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp);
  }

  static void sendEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? arg__2) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::sendEvent(KDDockWidgets::Core::View * arg__1, KDDockWidgets::Event * arg__2) const! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.sendEvent(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(arg__1),
        (arg__2 == null || arg__2.address == 0)
            ? null
            : Event.fromCppPointer(arg__2));
  } // setCursorPos(QPoint arg__1)

  setCursorPos(QPoint arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(544))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setCursorPos_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::setCursorPos(QPoint arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursorPos(QPoint.fromCppPointer(arg__1));
  } // setMouseCursor(Qt::CursorShape arg__1)

  setMouseCursor(int arg__1) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(545))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setMouseCursor_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::setMouseCursor(Qt::CursorShape arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseCursor(arg__1);
  } // startDragDistance() const

  int startDragDistance() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform__startDragDistance')
        .asFunction();
    return func(thisCpp);
  } // startDragDistance_impl() const

  int startDragDistance_impl() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(547))
        .asFunction();
    return func(thisCpp);
  }

  static int startDragDistance_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::startDragDistance_impl() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.startDragDistance_impl();
    return result;
  } // tests_createFocusableView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)

  KDDWBindingsCore.View tests_createFocusableView(CreateViewOptions arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(548))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> tests_createFocusableView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_createFocusableView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createFocusableView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // tests_createNonClosableView(KDDockWidgets::Core::View * parent)

  KDDWBindingsCore.View tests_createNonClosableView(
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(549))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> tests_createNonClosableView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_createNonClosableView(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createNonClosableView(
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // tests_createView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)

  KDDWBindingsCore.View tests_createView(CreateViewOptions arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(550))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return KDDWBindingsCore.View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> tests_createView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_createView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static // tests_deinitPlatform()
      tests_deinitPlatform() {
    final void_Func_void func = _dylib
        .lookup<ffi.NativeFunction<void_Func_void_FFI>>(
            'c_static_KDDockWidgets__Core__Platform__tests_deinitPlatform')
        .asFunction();
    func();
  } // tests_deinitPlatform_impl()

  tests_deinitPlatform_impl() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(552))
        .asFunction();
    func(thisCpp);
  }

  static void tests_deinitPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_deinitPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_deinitPlatform_impl();
  } // tests_initPlatform_impl()

  tests_initPlatform_impl() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(554))
        .asFunction();
    func(thisCpp);
  }

  static void tests_initPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_initPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_initPlatform_impl();
  } // ungrabMouse()

  ungrabMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(555))
        .asFunction();
    func(thisCpp);
  }

  static void ungrabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::ungrabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.ungrabMouse();
  } // uninstallMessageHandler()

  uninstallMessageHandler() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(556))
        .asFunction();
    func(thisCpp);
  }

  static void uninstallMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::uninstallMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.uninstallMessageHandler();
  } // usesFallbackMouseGrabber() const

  bool usesFallbackMouseGrabber() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(557))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int usesFallbackMouseGrabber_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::usesFallbackMouseGrabber() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.usesFallbackMouseGrabber();
    return result ? 1 : 0;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 516:
        return "c_KDDockWidgets__Core__Platform__applicationName";
      case 517:
        return "c_KDDockWidgets__Core__Platform__createDefaultViewFactory";
      case 518:
        return "c_KDDockWidgets__Core__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 519:
        return "c_KDDockWidgets__Core__Platform__createView_Controller_View";
      case 520:
        return "c_KDDockWidgets__Core__Platform__cursorPos";
      case 521:
        return "c_KDDockWidgets__Core__Platform__dumpManagedBacktrace";
      case 523:
        return "c_KDDockWidgets__Core__Platform__hasActivePopup";
      case 524:
        return "c_KDDockWidgets__Core__Platform__inDisallowedDragView_QPoint";
      case 525:
        return "c_KDDockWidgets__Core__Platform__installMessageHandler";
      case 528:
        return "c_KDDockWidgets__Core__Platform__isLeftMouseButtonPressed";
      case 529:
        return "c_KDDockWidgets__Core__Platform__isProcessingAppQuitEvent";
      case 533:
        return "c_KDDockWidgets__Core__Platform__name";
      case 534:
        return "c_KDDockWidgets__Core__Platform__onFloatingWindowCreated_FloatingWindow";
      case 535:
        return "c_KDDockWidgets__Core__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 536:
        return "c_KDDockWidgets__Core__Platform__onMainWindowCreated_MainWindow";
      case 537:
        return "c_KDDockWidgets__Core__Platform__onMainWindowDestroyed_MainWindow";
      case 538:
        return "c_KDDockWidgets__Core__Platform__pauseForDebugger";
      case 539:
        return "c_KDDockWidgets__Core__Platform__restoreMouseCursor";
      case 540:
        return "c_KDDockWidgets__Core__Platform__runDelayed_int_DelayedCall";
      case 541:
        return "c_KDDockWidgets__Core__Platform__screenNumberFor_View";
      case 542:
        return "c_KDDockWidgets__Core__Platform__screenSizeFor_View";
      case 543:
        return "c_KDDockWidgets__Core__Platform__sendEvent_View_Event";
      case 544:
        return "c_KDDockWidgets__Core__Platform__setCursorPos_QPoint";
      case 545:
        return "c_KDDockWidgets__Core__Platform__setMouseCursor_CursorShape";
      case 547:
        return "c_KDDockWidgets__Core__Platform__startDragDistance_impl";
      case 548:
        return "c_KDDockWidgets__Core__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 549:
        return "c_KDDockWidgets__Core__Platform__tests_createNonClosableView_View";
      case 550:
        return "c_KDDockWidgets__Core__Platform__tests_createView_CreateViewOptions_View";
      case 552:
        return "c_KDDockWidgets__Core__Platform__tests_deinitPlatform_impl";
      case 554:
        return "c_KDDockWidgets__Core__Platform__tests_initPlatform_impl";
      case 555:
        return "c_KDDockWidgets__Core__Platform__ungrabMouse";
      case 556:
        return "c_KDDockWidgets__Core__Platform__uninstallMessageHandler";
      case 557:
        return "c_KDDockWidgets__Core__Platform__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 516:
        return "applicationName";
      case 517:
        return "createDefaultViewFactory";
      case 518:
        return "createMainWindow";
      case 519:
        return "createView";
      case 520:
        return "cursorPos";
      case 521:
        return "dumpManagedBacktrace";
      case 523:
        return "hasActivePopup";
      case 524:
        return "inDisallowedDragView";
      case 525:
        return "installMessageHandler";
      case 528:
        return "isLeftMouseButtonPressed";
      case 529:
        return "isProcessingAppQuitEvent";
      case 533:
        return "name";
      case 534:
        return "onFloatingWindowCreated";
      case 535:
        return "onFloatingWindowDestroyed";
      case 536:
        return "onMainWindowCreated";
      case 537:
        return "onMainWindowDestroyed";
      case 538:
        return "pauseForDebugger";
      case 539:
        return "restoreMouseCursor";
      case 540:
        return "runDelayed";
      case 541:
        return "screenNumberFor";
      case 542:
        return "screenSizeFor";
      case 543:
        return "sendEvent";
      case 544:
        return "setCursorPos";
      case 545:
        return "setMouseCursor";
      case 547:
        return "startDragDistance_impl";
      case 548:
        return "tests_createFocusableView";
      case 549:
        return "tests_createNonClosableView";
      case 550:
        return "tests_createView";
      case 552:
        return "tests_deinitPlatform_impl";
      case 554:
        return "tests_initPlatform_impl";
      case 555:
        return "ungrabMouse";
      case 556:
        return "uninstallMessageHandler";
      case 557:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Core__Platform__registerVirtualMethodCallback')
        .asFunction();
    final callback516 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback516, 516);
    final callback517 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback517, 517);
    final callback518 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsCore.Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback518, 518);
    final callback519 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.createView_calledFromC);
    registerCallback(thisCpp, callback519, 519);
    final callback520 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback520, 520);
    final callback521 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback521, 521);
    const callbackExcept523 = 0;
    final callback523 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.hasActivePopup_calledFromC,
        callbackExcept523);
    registerCallback(thisCpp, callback523, 523);
    const callbackExcept524 = 0;
    final callback524 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.inDisallowedDragView_calledFromC,
            callbackExcept524);
    registerCallback(thisCpp, callback524, 524);
    final callback525 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback525, 525);
    const callbackExcept528 = 0;
    final callback528 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.isLeftMouseButtonPressed_calledFromC,
        callbackExcept528);
    registerCallback(thisCpp, callback528, 528);
    const callbackExcept529 = 0;
    final callback529 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.isProcessingAppQuitEvent_calledFromC,
        callbackExcept529);
    registerCallback(thisCpp, callback529, 529);
    final callback533 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.name_calledFromC);
    registerCallback(thisCpp, callback533, 533);
    final callback534 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback534, 534);
    final callback535 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback535, 535);
    final callback536 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onMainWindowCreated_calledFromC);
    registerCallback(thisCpp, callback536, 536);
    final callback537 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onMainWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback537, 537);
    final callback538 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.pauseForDebugger_calledFromC);
    registerCallback(thisCpp, callback538, 538);
    final callback539 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback539, 539);
    final callback540 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            KDDWBindingsCore.Platform.runDelayed_calledFromC);
    registerCallback(thisCpp, callback540, 540);
    const callbackExcept541 = 0;
    final callback541 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.screenNumberFor_calledFromC,
            callbackExcept541);
    registerCallback(thisCpp, callback541, 541);
    final callback542 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback542, 542);
    final callback543 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.sendEvent_calledFromC);
    registerCallback(thisCpp, callback543, 543);
    final callback544 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback544, 544);
    final callback545 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback545, 545);
    const callbackExcept547 = 0;
    final callback547 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.startDragDistance_impl_calledFromC,
        callbackExcept547);
    registerCallback(thisCpp, callback547, 547);
    final callback548 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback548, 548);
    final callback549 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback549, 549);
    final callback550 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback550, 550);
    final callback552 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback552, 552);
    final callback554 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback554, 554);
    final callback555 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback555, 555);
    final callback556 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback556, 556);
    const callbackExcept557 = 0;
    final callback557 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.usesFallbackMouseGrabber_calledFromC,
        callbackExcept557);
    registerCallback(thisCpp, callback557, 557);
  }
}
