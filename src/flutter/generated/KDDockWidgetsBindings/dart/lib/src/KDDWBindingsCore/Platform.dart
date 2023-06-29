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
            cFunctionSymbolName(649))
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
            cFunctionSymbolName(650))
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
            cFunctionSymbolName(651))
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
            cFunctionSymbolName(652))
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
            cFunctionSymbolName(653))
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
            cFunctionSymbolName(654))
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
            cFunctionSymbolName(656))
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
            cFunctionSymbolName(657))
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
            cFunctionSymbolName(658))
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
            cFunctionSymbolName(661))
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
            cFunctionSymbolName(662))
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
            cFunctionSymbolName(666))
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
            cFunctionSymbolName(667))
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
            cFunctionSymbolName(668))
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
            cFunctionSymbolName(669))
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
            cFunctionSymbolName(670))
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
            cFunctionSymbolName(671))
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
            cFunctionSymbolName(672))
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
            cFunctionSymbolName(673))
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
            cFunctionSymbolName(674))
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
            cFunctionSymbolName(675))
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
            cFunctionSymbolName(676))
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
            cFunctionSymbolName(677))
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
            cFunctionSymbolName(678))
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
            cFunctionSymbolName(680))
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
            cFunctionSymbolName(681))
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
            cFunctionSymbolName(682))
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
            cFunctionSymbolName(683))
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
            cFunctionSymbolName(685))
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
            cFunctionSymbolName(687))
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
            cFunctionSymbolName(688))
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
            cFunctionSymbolName(689))
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
            cFunctionSymbolName(690))
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
      case 649:
        return "c_KDDockWidgets__Core__Platform__applicationName";
      case 650:
        return "c_KDDockWidgets__Core__Platform__createDefaultViewFactory";
      case 651:
        return "c_KDDockWidgets__Core__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 652:
        return "c_KDDockWidgets__Core__Platform__createView_Controller_View";
      case 653:
        return "c_KDDockWidgets__Core__Platform__cursorPos";
      case 654:
        return "c_KDDockWidgets__Core__Platform__dumpManagedBacktrace";
      case 656:
        return "c_KDDockWidgets__Core__Platform__hasActivePopup";
      case 657:
        return "c_KDDockWidgets__Core__Platform__inDisallowedDragView_QPoint";
      case 658:
        return "c_KDDockWidgets__Core__Platform__installMessageHandler";
      case 661:
        return "c_KDDockWidgets__Core__Platform__isLeftMouseButtonPressed";
      case 662:
        return "c_KDDockWidgets__Core__Platform__isProcessingAppQuitEvent";
      case 666:
        return "c_KDDockWidgets__Core__Platform__name";
      case 667:
        return "c_KDDockWidgets__Core__Platform__onFloatingWindowCreated_FloatingWindow";
      case 668:
        return "c_KDDockWidgets__Core__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 669:
        return "c_KDDockWidgets__Core__Platform__onMainWindowCreated_MainWindow";
      case 670:
        return "c_KDDockWidgets__Core__Platform__onMainWindowDestroyed_MainWindow";
      case 671:
        return "c_KDDockWidgets__Core__Platform__pauseForDebugger";
      case 672:
        return "c_KDDockWidgets__Core__Platform__restoreMouseCursor";
      case 673:
        return "c_KDDockWidgets__Core__Platform__runDelayed_int_DelayedCall";
      case 674:
        return "c_KDDockWidgets__Core__Platform__screenNumberFor_View";
      case 675:
        return "c_KDDockWidgets__Core__Platform__screenSizeFor_View";
      case 676:
        return "c_KDDockWidgets__Core__Platform__sendEvent_View_Event";
      case 677:
        return "c_KDDockWidgets__Core__Platform__setCursorPos_QPoint";
      case 678:
        return "c_KDDockWidgets__Core__Platform__setMouseCursor_CursorShape";
      case 680:
        return "c_KDDockWidgets__Core__Platform__startDragDistance_impl";
      case 681:
        return "c_KDDockWidgets__Core__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 682:
        return "c_KDDockWidgets__Core__Platform__tests_createNonClosableView_View";
      case 683:
        return "c_KDDockWidgets__Core__Platform__tests_createView_CreateViewOptions_View";
      case 685:
        return "c_KDDockWidgets__Core__Platform__tests_deinitPlatform_impl";
      case 687:
        return "c_KDDockWidgets__Core__Platform__tests_initPlatform_impl";
      case 688:
        return "c_KDDockWidgets__Core__Platform__ungrabMouse";
      case 689:
        return "c_KDDockWidgets__Core__Platform__uninstallMessageHandler";
      case 690:
        return "c_KDDockWidgets__Core__Platform__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 649:
        return "applicationName";
      case 650:
        return "createDefaultViewFactory";
      case 651:
        return "createMainWindow";
      case 652:
        return "createView";
      case 653:
        return "cursorPos";
      case 654:
        return "dumpManagedBacktrace";
      case 656:
        return "hasActivePopup";
      case 657:
        return "inDisallowedDragView";
      case 658:
        return "installMessageHandler";
      case 661:
        return "isLeftMouseButtonPressed";
      case 662:
        return "isProcessingAppQuitEvent";
      case 666:
        return "name";
      case 667:
        return "onFloatingWindowCreated";
      case 668:
        return "onFloatingWindowDestroyed";
      case 669:
        return "onMainWindowCreated";
      case 670:
        return "onMainWindowDestroyed";
      case 671:
        return "pauseForDebugger";
      case 672:
        return "restoreMouseCursor";
      case 673:
        return "runDelayed";
      case 674:
        return "screenNumberFor";
      case 675:
        return "screenSizeFor";
      case 676:
        return "sendEvent";
      case 677:
        return "setCursorPos";
      case 678:
        return "setMouseCursor";
      case 680:
        return "startDragDistance_impl";
      case 681:
        return "tests_createFocusableView";
      case 682:
        return "tests_createNonClosableView";
      case 683:
        return "tests_createView";
      case 685:
        return "tests_deinitPlatform_impl";
      case 687:
        return "tests_initPlatform_impl";
      case 688:
        return "ungrabMouse";
      case 689:
        return "uninstallMessageHandler";
      case 690:
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
    final callback649 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback649, 649);
    final callback650 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback650, 650);
    final callback651 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsCore.Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback651, 651);
    final callback652 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.createView_calledFromC);
    registerCallback(thisCpp, callback652, 652);
    final callback653 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback653, 653);
    final callback654 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback654, 654);
    const callbackExcept656 = 0;
    final callback656 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.hasActivePopup_calledFromC,
        callbackExcept656);
    registerCallback(thisCpp, callback656, 656);
    const callbackExcept657 = 0;
    final callback657 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.inDisallowedDragView_calledFromC,
            callbackExcept657);
    registerCallback(thisCpp, callback657, 657);
    final callback658 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback658, 658);
    const callbackExcept661 = 0;
    final callback661 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.isLeftMouseButtonPressed_calledFromC,
        callbackExcept661);
    registerCallback(thisCpp, callback661, 661);
    const callbackExcept662 = 0;
    final callback662 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.isProcessingAppQuitEvent_calledFromC,
        callbackExcept662);
    registerCallback(thisCpp, callback662, 662);
    final callback666 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.name_calledFromC);
    registerCallback(thisCpp, callback666, 666);
    final callback667 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback667, 667);
    final callback668 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback668, 668);
    final callback669 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onMainWindowCreated_calledFromC);
    registerCallback(thisCpp, callback669, 669);
    final callback670 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onMainWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback670, 670);
    final callback671 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.pauseForDebugger_calledFromC);
    registerCallback(thisCpp, callback671, 671);
    final callback672 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback672, 672);
    final callback673 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            KDDWBindingsCore.Platform.runDelayed_calledFromC);
    registerCallback(thisCpp, callback673, 673);
    const callbackExcept674 = 0;
    final callback674 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.screenNumberFor_calledFromC,
            callbackExcept674);
    registerCallback(thisCpp, callback674, 674);
    final callback675 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback675, 675);
    final callback676 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.sendEvent_calledFromC);
    registerCallback(thisCpp, callback676, 676);
    final callback677 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback677, 677);
    final callback678 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback678, 678);
    const callbackExcept680 = 0;
    final callback680 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.startDragDistance_impl_calledFromC,
        callbackExcept680);
    registerCallback(thisCpp, callback680, 680);
    final callback681 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback681, 681);
    final callback682 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback682, 682);
    final callback683 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback683, 683);
    final callback685 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback685, 685);
    final callback687 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback687, 687);
    final callback688 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback688, 688);
    final callback689 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback689, 689);
    const callbackExcept690 = 0;
    final callback690 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.usesFallbackMouseGrabber_calledFromC,
        callbackExcept690);
    registerCallback(thisCpp, callback690, 690);
  }
}
