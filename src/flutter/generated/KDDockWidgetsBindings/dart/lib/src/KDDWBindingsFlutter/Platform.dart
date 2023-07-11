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
            cFunctionSymbolName(179))
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
            cFunctionSymbolName(180))
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
            cFunctionSymbolName(181))
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
            cFunctionSymbolName(183))
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
            cFunctionSymbolName(186))
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

  static int supportsAeroSnap_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::supportsAeroSnap() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.supportsAeroSnap();
    return result ? 1 : 0;
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
      case 130:
        return "c_KDDockWidgets__flutter__Platform__applicationName";
      case 131:
        return "c_KDDockWidgets__flutter__Platform__createDefaultViewFactory";
      case 132:
        return "c_KDDockWidgets__flutter__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 133:
        return "c_KDDockWidgets__flutter__Platform__createView_Controller_View";
      case 134:
        return "c_KDDockWidgets__flutter__Platform__cursorPos";
      case 135:
        return "c_KDDockWidgets__flutter__Platform__dumpManagedBacktrace";
      case 137:
        return "c_KDDockWidgets__flutter__Platform__hasActivePopup";
      case 138:
        return "c_KDDockWidgets__flutter__Platform__inDisallowedDragView_Point";
      case 139:
        return "c_KDDockWidgets__flutter__Platform__installMessageHandler";
      case 142:
        return "c_KDDockWidgets__flutter__Platform__isLeftMouseButtonPressed";
      case 143:
        return "c_KDDockWidgets__flutter__Platform__isProcessingAppQuitEvent";
      case 147:
        return "c_KDDockWidgets__flutter__Platform__name";
      case 179:
        return "c_KDDockWidgets__flutter__Platform__onDropIndicatorOverlayCreated_IndicatorWindow";
      case 180:
        return "c_KDDockWidgets__flutter__Platform__onDropIndicatorOverlayDestroyed_IndicatorWindow";
      case 148:
        return "c_KDDockWidgets__flutter__Platform__onFloatingWindowCreated_FloatingWindow";
      case 149:
        return "c_KDDockWidgets__flutter__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 150:
        return "c_KDDockWidgets__flutter__Platform__onMainWindowCreated_MainWindow";
      case 151:
        return "c_KDDockWidgets__flutter__Platform__onMainWindowDestroyed_MainWindow";
      case 181:
        return "c_KDDockWidgets__flutter__Platform__pauseForDartDebugger";
      case 152:
        return "c_KDDockWidgets__flutter__Platform__pauseForDebugger";
      case 183:
        return "c_KDDockWidgets__flutter__Platform__rebuildWindowOverlay";
      case 153:
        return "c_KDDockWidgets__flutter__Platform__restoreMouseCursor";
      case 154:
        return "c_KDDockWidgets__flutter__Platform__runDelayed_int_DelayedCall";
      case 186:
        return "c_KDDockWidgets__flutter__Platform__scheduleResumeCoRoutines_int";
      case 155:
        return "c_KDDockWidgets__flutter__Platform__screenNumberFor_View";
      case 156:
        return "c_KDDockWidgets__flutter__Platform__screenSizeFor_View";
      case 157:
        return "c_KDDockWidgets__flutter__Platform__sendEvent_View_Event";
      case 158:
        return "c_KDDockWidgets__flutter__Platform__setCursorPos_Point";
      case 159:
        return "c_KDDockWidgets__flutter__Platform__setMouseCursor_CursorShape";
      case 161:
        return "c_KDDockWidgets__flutter__Platform__startDragDistance_impl";
      case 162:
        return "c_KDDockWidgets__flutter__Platform__supportsAeroSnap";
      case 163:
        return "c_KDDockWidgets__flutter__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 164:
        return "c_KDDockWidgets__flutter__Platform__tests_createNonClosableView_View";
      case 165:
        return "c_KDDockWidgets__flutter__Platform__tests_createView_CreateViewOptions_View";
      case 166:
        return "c_KDDockWidgets__flutter__Platform__tests_deinitPlatform_impl";
      case 167:
        return "c_KDDockWidgets__flutter__Platform__tests_initPlatform_impl";
      case 168:
        return "c_KDDockWidgets__flutter__Platform__ungrabMouse";
      case 169:
        return "c_KDDockWidgets__flutter__Platform__uninstallMessageHandler";
      case 170:
        return "c_KDDockWidgets__flutter__Platform__usesFallbackMouseGrabber";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 130:
        return "applicationName";
      case 131:
        return "createDefaultViewFactory";
      case 132:
        return "createMainWindow";
      case 133:
        return "createView";
      case 134:
        return "cursorPos";
      case 135:
        return "dumpManagedBacktrace";
      case 137:
        return "hasActivePopup";
      case 138:
        return "inDisallowedDragView";
      case 139:
        return "installMessageHandler";
      case 142:
        return "isLeftMouseButtonPressed";
      case 143:
        return "isProcessingAppQuitEvent";
      case 147:
        return "name";
      case 179:
        return "onDropIndicatorOverlayCreated";
      case 180:
        return "onDropIndicatorOverlayDestroyed";
      case 148:
        return "onFloatingWindowCreated";
      case 149:
        return "onFloatingWindowDestroyed";
      case 150:
        return "onMainWindowCreated";
      case 151:
        return "onMainWindowDestroyed";
      case 181:
        return "pauseForDartDebugger";
      case 152:
        return "pauseForDebugger";
      case 183:
        return "rebuildWindowOverlay";
      case 153:
        return "restoreMouseCursor";
      case 154:
        return "runDelayed";
      case 186:
        return "scheduleResumeCoRoutines";
      case 155:
        return "screenNumberFor";
      case 156:
        return "screenSizeFor";
      case 157:
        return "sendEvent";
      case 158:
        return "setCursorPos";
      case 159:
        return "setMouseCursor";
      case 161:
        return "startDragDistance_impl";
      case 162:
        return "supportsAeroSnap";
      case 163:
        return "tests_createFocusableView";
      case 164:
        return "tests_createNonClosableView";
      case 165:
        return "tests_createView";
      case 166:
        return "tests_deinitPlatform_impl";
      case 167:
        return "tests_initPlatform_impl";
      case 168:
        return "ungrabMouse";
      case 169:
        return "uninstallMessageHandler";
      case 170:
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
    final callback130 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback130, 130);
    final callback131 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback131, 131);
    final callback132 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsFlutter.Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback132, 132);
    final callback133 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.createView_calledFromC);
    registerCallback(thisCpp, callback133, 133);
    final callback134 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback134, 134);
    final callback135 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback135, 135);
    const callbackExcept137 = 0;
    final callback137 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.hasActivePopup_calledFromC,
        callbackExcept137);
    registerCallback(thisCpp, callback137, 137);
    const callbackExcept138 = 0;
    final callback138 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.inDisallowedDragView_calledFromC,
            callbackExcept138);
    registerCallback(thisCpp, callback138, 138);
    final callback139 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback139, 139);
    const callbackExcept142 = 0;
    final callback142 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.isLeftMouseButtonPressed_calledFromC,
        callbackExcept142);
    registerCallback(thisCpp, callback142, 142);
    const callbackExcept143 = 0;
    final callback143 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.isProcessingAppQuitEvent_calledFromC,
        callbackExcept143);
    registerCallback(thisCpp, callback143, 143);
    final callback147 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.name_calledFromC);
    registerCallback(thisCpp, callback147, 147);
    final callback179 = ffi.Pointer.fromFunction<
            void_Func_voidstar_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.onDropIndicatorOverlayCreated_calledFromC);
    registerCallback(thisCpp, callback179, 179);
    final callback180 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter
                .Platform.onDropIndicatorOverlayDestroyed_calledFromC);
    registerCallback(thisCpp, callback180, 180);
    final callback148 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback148, 148);
    final callback149 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback149, 149);
    final callback150 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onMainWindowCreated_calledFromC);
    registerCallback(thisCpp, callback150, 150);
    final callback151 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onMainWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback151, 151);
    final callback181 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.pauseForDartDebugger_calledFromC);
    registerCallback(thisCpp, callback181, 181);
    final callback152 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.pauseForDebugger_calledFromC);
    registerCallback(thisCpp, callback152, 152);
    final callback183 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.rebuildWindowOverlay_calledFromC);
    registerCallback(thisCpp, callback183, 183);
    final callback153 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback153, 153);
    final callback154 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.runDelayed_calledFromC);
    registerCallback(thisCpp, callback154, 154);
    final callback186 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Platform.scheduleResumeCoRoutines_calledFromC);
    registerCallback(thisCpp, callback186, 186);
    const callbackExcept155 = 0;
    final callback155 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.screenNumberFor_calledFromC,
            callbackExcept155);
    registerCallback(thisCpp, callback155, 155);
    final callback156 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback156, 156);
    final callback157 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.sendEvent_calledFromC);
    registerCallback(thisCpp, callback157, 157);
    final callback158 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback158, 158);
    final callback159 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback159, 159);
    const callbackExcept161 = 0;
    final callback161 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.startDragDistance_impl_calledFromC,
        callbackExcept161);
    registerCallback(thisCpp, callback161, 161);
    const callbackExcept162 = 0;
    final callback162 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.supportsAeroSnap_calledFromC,
        callbackExcept162);
    registerCallback(thisCpp, callback162, 162);
    final callback163 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback163, 163);
    final callback164 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback164, 164);
    final callback165 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback165, 165);
    final callback166 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback166, 166);
    final callback167 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback167, 167);
    final callback168 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback168, 168);
    final callback169 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback169, 169);
    const callbackExcept170 = 0;
    final callback170 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.usesFallbackMouseGrabber_calledFromC,
        callbackExcept170);
    registerCallback(thisCpp, callback170, 170);
  }
}
