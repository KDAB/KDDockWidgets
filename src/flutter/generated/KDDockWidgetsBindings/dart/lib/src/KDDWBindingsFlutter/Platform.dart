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

class Platform extends KDDWBindingsCore.Platform {
  Platform.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Platform.init() : super.init() {}
  factory Platform.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.Platform.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Platform;
    }
    return Platform.fromCppPointer(cppPointer, needsAutoDelete);
  } //Platform()
  Platform() : super.init() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__flutter__Platform__constructor')
        .asFunction();
    thisCpp = func();
    KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static ffi.Pointer<void> applicationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::applicationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.applicationName();
    return result.thisCpp;
  }

  static ffi.Pointer<void> createDefaultViewFactory_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createDefaultViewFactory()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDefaultViewFactory();
    return result.thisCpp;
  }

  static ffi.Pointer<void> createMainWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? uniqueName,
      ffi.Pointer<void> viewOpts,
      int options,
      ffi.Pointer<void>? parent,
      int flags) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createMainWindow(const QString & uniqueName, KDDockWidgets::Core::CreateViewOptions viewOpts, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags flags) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createMainWindow(
        QString.fromCppPointer(uniqueName).toDartString(),
        CreateViewOptions.fromCppPointer(viewOpts),
        options: options,
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
        arg__5: flags);
    return result.thisCpp;
  }

  static ffi.Pointer<void> createView_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createView(KDDockWidgets::Core::Controller * controller, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createView(
        (controller == null || controller.address == 0)
            ? null
            : KDDWBindingsCore.Controller.fromCppPointer(controller),
        parent: (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> cursorPos_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::cursorPos() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.cursorPos();
    return result.thisCpp;
  }

  static void dumpManagedBacktrace_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::dumpManagedBacktrace()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.dumpManagedBacktrace();
  }

  static int hasActivePopup_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::hasActivePopup() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasActivePopup();
    return result ? 1 : 0;
  }

  static int inDisallowedDragView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::inDisallowedDragView(KDDockWidgets::Point globalPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result =
        dartInstance.inDisallowedDragView(Point.fromCppPointer(globalPos));
    return result ? 1 : 0;
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Platform__init')
        .asFunction();
    func(thisCpp);
  }

  static void installMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::installMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.installMessageHandler();
  }

  static int isLeftMouseButtonPressed_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::isLeftMouseButtonPressed() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isLeftMouseButtonPressed();
    return result ? 1 : 0;
  }

  static int isProcessingAppQuitEvent_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::isProcessingAppQuitEvent() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isProcessingAppQuitEvent();
    return result ? 1 : 0;
  }

  static ffi.Pointer<Utf8> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::name() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.name();
    return result.toNativeUtf8();
  } // onDropIndicatorOverlayCreated(KDDockWidgets::flutter::IndicatorWindow * arg__1)

  onDropIndicatorOverlayCreated(KDDWBindingsFlutter.IndicatorWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(521))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onDropIndicatorOverlayCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onDropIndicatorOverlayCreated(KDDockWidgets::flutter::IndicatorWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onDropIndicatorOverlayCreated(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsFlutter.IndicatorWindow.fromCppPointer(arg__1));
  } // onDropIndicatorOverlayDestroyed(KDDockWidgets::flutter::IndicatorWindow * arg__1)

  onDropIndicatorOverlayDestroyed(KDDWBindingsFlutter.IndicatorWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(522))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onDropIndicatorOverlayDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onDropIndicatorOverlayDestroyed(KDDockWidgets::flutter::IndicatorWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onDropIndicatorOverlayDestroyed(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsFlutter.IndicatorWindow.fromCppPointer(arg__1));
  }

  static void onFloatingWindowCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onFloatingWindowCreated((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.FloatingWindow.fromCppPointer(arg__1));
  }

  static void onFloatingWindowDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onFloatingWindowDestroyed(
        (arg__1 == null || arg__1.address == 0)
            ? null
            : KDDWBindingsCore.FloatingWindow.fromCppPointer(arg__1));
  }

  static void onMainWindowCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onMainWindowCreated(KDDockWidgets::Core::MainWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onMainWindowCreated((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.MainWindow.fromCppPointer(arg__1));
  }

  static void onMainWindowDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onMainWindowDestroyed(KDDockWidgets::Core::MainWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onMainWindowDestroyed((arg__1 == null || arg__1.address == 0)
        ? null
        : KDDWBindingsCore.MainWindow.fromCppPointer(arg__1));
  } // pauseForDartDebugger()

  pauseForDartDebugger() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(523))
        .asFunction();
    func(thisCpp);
  }

  static void pauseForDartDebugger_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::pauseForDartDebugger()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.pauseForDartDebugger();
  }

  static void pauseForDebugger_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::pauseForDebugger()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.pauseForDebugger();
  }

  static // platformFlutter()
      KDDWBindingsFlutter.Platform platformFlutter() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__flutter__Platform__platformFlutter')
        .asFunction();
    ffi.Pointer<void> result = func();
    return KDDWBindingsFlutter.Platform.fromCppPointer(result, false);
  } // rebuildWindowOverlay()

  rebuildWindowOverlay() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(525))
        .asFunction();
    func(thisCpp);
  }

  static void rebuildWindowOverlay_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::rebuildWindowOverlay()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.rebuildWindowOverlay();
  }

  static void restoreMouseCursor_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::restoreMouseCursor()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.restoreMouseCursor();
  } // resumeCoRoutines()

  resumeCoRoutines() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Platform__resumeCoRoutines')
        .asFunction();
    func(thisCpp);
  }

  static void runDelayed_calledFromC(
      ffi.Pointer<void> thisCpp, int ms, ffi.Pointer<void>? c) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
  } // runTests()

  runTests() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Platform__runTests')
        .asFunction();
    func(thisCpp);
  } // scheduleResumeCoRoutines(int ms) const

  scheduleResumeCoRoutines(int ms) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(528))
        .asFunction();
    func(thisCpp, ms);
  }

  static void scheduleResumeCoRoutines_calledFromC(
      ffi.Pointer<void> thisCpp, int ms) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::scheduleResumeCoRoutines(int ms) const! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.scheduleResumeCoRoutines(ms);
  }

  static int screenNumberFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
  }

  static ffi.Pointer<void> screenSizeFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
  }

  static void sendEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? arg__2) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
  }

  static void setCursorPos_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::setCursorPos(KDDockWidgets::Point arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursorPos(Point.fromCppPointer(arg__1));
  }

  static void setMouseCursor_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::setMouseCursor(Qt::CursorShape arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseCursor(arg__1);
  }

  static int startDragDistance_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::startDragDistance_impl() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.startDragDistance_impl();
    return result;
  }

  static ffi.Pointer<void> tests_createFocusableView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
  }

  static ffi.Pointer<void> tests_createNonClosableView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
  }

  static ffi.Pointer<void> tests_createView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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

  static void tests_deinitPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_deinitPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_deinitPlatform_impl();
  }

  static void tests_initPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_initPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_initPlatform_impl();
  }

  static void ungrabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::ungrabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.ungrabMouse();
  }

  static void uninstallMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::uninstallMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.uninstallMessageHandler();
  }

  static int usesFallbackMouseGrabber_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
            'c_KDDockWidgets__flutter__Platform__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 470:
        return "c_KDDockWidgets__flutter__Platform__applicationName";
      case 471:
        return "c_KDDockWidgets__flutter__Platform__createDefaultViewFactory";
      case 472:
        return "c_KDDockWidgets__flutter__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 473:
        return "c_KDDockWidgets__flutter__Platform__createView_Controller_View";
      case 474:
        return "c_KDDockWidgets__flutter__Platform__cursorPos";
      case 475:
        return "c_KDDockWidgets__flutter__Platform__dumpManagedBacktrace";
      case 477:
        return "c_KDDockWidgets__flutter__Platform__hasActivePopup";
      case 478:
        return "c_KDDockWidgets__flutter__Platform__inDisallowedDragView_Point";
      case 479:
        return "c_KDDockWidgets__flutter__Platform__installMessageHandler";
      case 482:
        return "c_KDDockWidgets__flutter__Platform__isLeftMouseButtonPressed";
      case 483:
        return "c_KDDockWidgets__flutter__Platform__isProcessingAppQuitEvent";
      case 487:
        return "c_KDDockWidgets__flutter__Platform__name";
      case 521:
        return "c_KDDockWidgets__flutter__Platform__onDropIndicatorOverlayCreated_IndicatorWindow";
      case 522:
        return "c_KDDockWidgets__flutter__Platform__onDropIndicatorOverlayDestroyed_IndicatorWindow";
      case 488:
        return "c_KDDockWidgets__flutter__Platform__onFloatingWindowCreated_FloatingWindow";
      case 489:
        return "c_KDDockWidgets__flutter__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 490:
        return "c_KDDockWidgets__flutter__Platform__onMainWindowCreated_MainWindow";
      case 491:
        return "c_KDDockWidgets__flutter__Platform__onMainWindowDestroyed_MainWindow";
      case 523:
        return "c_KDDockWidgets__flutter__Platform__pauseForDartDebugger";
      case 492:
        return "c_KDDockWidgets__flutter__Platform__pauseForDebugger";
      case 525:
        return "c_KDDockWidgets__flutter__Platform__rebuildWindowOverlay";
      case 494:
        return "c_KDDockWidgets__flutter__Platform__restoreMouseCursor";
      case 495:
        return "c_KDDockWidgets__flutter__Platform__runDelayed_int_DelayedCall";
      case 528:
        return "c_KDDockWidgets__flutter__Platform__scheduleResumeCoRoutines_int";
      case 496:
        return "c_KDDockWidgets__flutter__Platform__screenNumberFor_View";
      case 497:
        return "c_KDDockWidgets__flutter__Platform__screenSizeFor_View";
      case 498:
        return "c_KDDockWidgets__flutter__Platform__sendEvent_View_Event";
      case 499:
        return "c_KDDockWidgets__flutter__Platform__setCursorPos_Point";
      case 500:
        return "c_KDDockWidgets__flutter__Platform__setMouseCursor_CursorShape";
      case 502:
        return "c_KDDockWidgets__flutter__Platform__startDragDistance_impl";
      case 503:
        return "c_KDDockWidgets__flutter__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 504:
        return "c_KDDockWidgets__flutter__Platform__tests_createNonClosableView_View";
      case 505:
        return "c_KDDockWidgets__flutter__Platform__tests_createView_CreateViewOptions_View";
      case 507:
        return "c_KDDockWidgets__flutter__Platform__tests_deinitPlatform_impl";
      case 509:
        return "c_KDDockWidgets__flutter__Platform__tests_initPlatform_impl";
      case 510:
        return "c_KDDockWidgets__flutter__Platform__ungrabMouse";
      case 511:
        return "c_KDDockWidgets__flutter__Platform__uninstallMessageHandler";
      case 512:
        return "c_KDDockWidgets__flutter__Platform__usesFallbackMouseGrabber";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 470:
        return "applicationName";
      case 471:
        return "createDefaultViewFactory";
      case 472:
        return "createMainWindow";
      case 473:
        return "createView";
      case 474:
        return "cursorPos";
      case 475:
        return "dumpManagedBacktrace";
      case 477:
        return "hasActivePopup";
      case 478:
        return "inDisallowedDragView";
      case 479:
        return "installMessageHandler";
      case 482:
        return "isLeftMouseButtonPressed";
      case 483:
        return "isProcessingAppQuitEvent";
      case 487:
        return "name";
      case 521:
        return "onDropIndicatorOverlayCreated";
      case 522:
        return "onDropIndicatorOverlayDestroyed";
      case 488:
        return "onFloatingWindowCreated";
      case 489:
        return "onFloatingWindowDestroyed";
      case 490:
        return "onMainWindowCreated";
      case 491:
        return "onMainWindowDestroyed";
      case 523:
        return "pauseForDartDebugger";
      case 492:
        return "pauseForDebugger";
      case 525:
        return "rebuildWindowOverlay";
      case 494:
        return "restoreMouseCursor";
      case 495:
        return "runDelayed";
      case 528:
        return "scheduleResumeCoRoutines";
      case 496:
        return "screenNumberFor";
      case 497:
        return "screenSizeFor";
      case 498:
        return "sendEvent";
      case 499:
        return "setCursorPos";
      case 500:
        return "setMouseCursor";
      case 502:
        return "startDragDistance_impl";
      case 503:
        return "tests_createFocusableView";
      case 504:
        return "tests_createNonClosableView";
      case 505:
        return "tests_createView";
      case 507:
        return "tests_deinitPlatform_impl";
      case 509:
        return "tests_initPlatform_impl";
      case 510:
        return "ungrabMouse";
      case 511:
        return "uninstallMessageHandler";
      case 512:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__Platform__registerVirtualMethodCallback')
        .asFunction();
    final callback470 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback470, 470);
    final callback471 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback471, 471);
    final callback472 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsFlutter.Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback472, 472);
    final callback473 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.createView_calledFromC);
    registerCallback(thisCpp, callback473, 473);
    final callback474 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback474, 474);
    final callback475 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback475, 475);
    const callbackExcept477 = 0;
    final callback477 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.hasActivePopup_calledFromC,
        callbackExcept477);
    registerCallback(thisCpp, callback477, 477);
    const callbackExcept478 = 0;
    final callback478 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.inDisallowedDragView_calledFromC,
            callbackExcept478);
    registerCallback(thisCpp, callback478, 478);
    final callback479 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback479, 479);
    const callbackExcept482 = 0;
    final callback482 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.isLeftMouseButtonPressed_calledFromC,
        callbackExcept482);
    registerCallback(thisCpp, callback482, 482);
    const callbackExcept483 = 0;
    final callback483 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.isProcessingAppQuitEvent_calledFromC,
        callbackExcept483);
    registerCallback(thisCpp, callback483, 483);
    final callback487 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.name_calledFromC);
    registerCallback(thisCpp, callback487, 487);
    final callback521 = ffi.Pointer.fromFunction<
            void_Func_voidstar_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.onDropIndicatorOverlayCreated_calledFromC);
    registerCallback(thisCpp, callback521, 521);
    final callback522 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter
                .Platform.onDropIndicatorOverlayDestroyed_calledFromC);
    registerCallback(thisCpp, callback522, 522);
    final callback488 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback488, 488);
    final callback489 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback489, 489);
    final callback490 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onMainWindowCreated_calledFromC);
    registerCallback(thisCpp, callback490, 490);
    final callback491 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onMainWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback491, 491);
    final callback523 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.pauseForDartDebugger_calledFromC);
    registerCallback(thisCpp, callback523, 523);
    final callback492 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.pauseForDebugger_calledFromC);
    registerCallback(thisCpp, callback492, 492);
    final callback525 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.rebuildWindowOverlay_calledFromC);
    registerCallback(thisCpp, callback525, 525);
    final callback494 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback494, 494);
    final callback495 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.runDelayed_calledFromC);
    registerCallback(thisCpp, callback495, 495);
    final callback528 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Platform.scheduleResumeCoRoutines_calledFromC);
    registerCallback(thisCpp, callback528, 528);
    const callbackExcept496 = 0;
    final callback496 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.screenNumberFor_calledFromC,
            callbackExcept496);
    registerCallback(thisCpp, callback496, 496);
    final callback497 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback497, 497);
    final callback498 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.sendEvent_calledFromC);
    registerCallback(thisCpp, callback498, 498);
    final callback499 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback499, 499);
    final callback500 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback500, 500);
    const callbackExcept502 = 0;
    final callback502 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.startDragDistance_impl_calledFromC,
        callbackExcept502);
    registerCallback(thisCpp, callback502, 502);
    final callback503 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback503, 503);
    final callback504 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback504, 504);
    final callback505 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback505, 505);
    final callback507 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback507, 507);
    final callback509 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback509, 509);
    final callback510 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback510, 510);
    final callback511 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback511, 511);
    const callbackExcept512 = 0;
    final callback512 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.usesFallbackMouseGrabber_calledFromC,
        callbackExcept512);
    registerCallback(thisCpp, callback512, 512);
  }
}
