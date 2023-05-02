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
      ffi.Pointer<void> arg__2,
      int options,
      ffi.Pointer<void>? parent,
      int arg__5) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
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
          "Dart instance not found for Platform::inDisallowedDragView(QPoint globalPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result =
        dartInstance.inDisallowedDragView(QPoint.fromCppPointer(globalPos));
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

  static ffi.Pointer<void> organizationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::organizationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.organizationName();
    return result.thisCpp;
  } // pauseForDartDebugger()

  pauseForDartDebugger() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(767))
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

  static // platformFlutter()
      KDDWBindingsFlutter.Platform platformFlutter() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__flutter__Platform__platformFlutter')
        .asFunction();
    ffi.Pointer<void> result = func();
    return KDDWBindingsFlutter.Platform.fromCppPointer(result, false);
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
  } // runTests()

  runTests() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Platform__runTests')
        .asFunction();
    func(thisCpp);
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

  static void setCursorPos_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::setCursorPos(QPoint arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursorPos(QPoint.fromCppPointer(arg__1));
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

  static void tests_doubleClickOn_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> globalPos, ffi.Pointer<void>? receiver) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_doubleClickOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_doubleClickOn(
        QPoint.fromCppPointer(globalPos),
        (receiver == null || receiver.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(receiver));
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

  static void tests_wait_calledFromC(ffi.Pointer<void> thisCpp, int ms) {
    var dartInstance = KDDWBindingsCore
        .Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_wait(int ms)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_wait(ms);
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
      case 714:
        return "c_KDDockWidgets__flutter__Platform__applicationName";
      case 715:
        return "c_KDDockWidgets__flutter__Platform__createDefaultViewFactory";
      case 716:
        return "c_KDDockWidgets__flutter__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 717:
        return "c_KDDockWidgets__flutter__Platform__createView_Controller_View";
      case 718:
        return "c_KDDockWidgets__flutter__Platform__cursorPos";
      case 719:
        return "c_KDDockWidgets__flutter__Platform__dumpManagedBacktrace";
      case 721:
        return "c_KDDockWidgets__flutter__Platform__hasActivePopup";
      case 722:
        return "c_KDDockWidgets__flutter__Platform__inDisallowedDragView_QPoint";
      case 723:
        return "c_KDDockWidgets__flutter__Platform__installMessageHandler";
      case 725:
        return "c_KDDockWidgets__flutter__Platform__isLeftMouseButtonPressed";
      case 726:
        return "c_KDDockWidgets__flutter__Platform__isProcessingAppQuitEvent";
      case 730:
        return "c_KDDockWidgets__flutter__Platform__name";
      case 731:
        return "c_KDDockWidgets__flutter__Platform__onFloatingWindowCreated_FloatingWindow";
      case 732:
        return "c_KDDockWidgets__flutter__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 733:
        return "c_KDDockWidgets__flutter__Platform__organizationName";
      case 767:
        return "c_KDDockWidgets__flutter__Platform__pauseForDartDebugger";
      case 734:
        return "c_KDDockWidgets__flutter__Platform__restoreMouseCursor";
      case 735:
        return "c_KDDockWidgets__flutter__Platform__screenNumberFor_View";
      case 736:
        return "c_KDDockWidgets__flutter__Platform__screenSizeFor_View";
      case 737:
        return "c_KDDockWidgets__flutter__Platform__setCursorPos_QPoint";
      case 738:
        return "c_KDDockWidgets__flutter__Platform__setMouseCursor_CursorShape";
      case 740:
        return "c_KDDockWidgets__flutter__Platform__startDragDistance_impl";
      case 741:
        return "c_KDDockWidgets__flutter__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 742:
        return "c_KDDockWidgets__flutter__Platform__tests_createNonClosableView_View";
      case 743:
        return "c_KDDockWidgets__flutter__Platform__tests_createView_CreateViewOptions_View";
      case 745:
        return "c_KDDockWidgets__flutter__Platform__tests_deinitPlatform_impl";
      case 746:
        return "c_KDDockWidgets__flutter__Platform__tests_doubleClickOn_QPoint_View";
      case 748:
        return "c_KDDockWidgets__flutter__Platform__tests_initPlatform_impl";
      case 750:
        return "c_KDDockWidgets__flutter__Platform__tests_wait_int";
      case 757:
        return "c_KDDockWidgets__flutter__Platform__ungrabMouse";
      case 758:
        return "c_KDDockWidgets__flutter__Platform__uninstallMessageHandler";
      case 759:
        return "c_KDDockWidgets__flutter__Platform__usesFallbackMouseGrabber";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 714:
        return "applicationName";
      case 715:
        return "createDefaultViewFactory";
      case 716:
        return "createMainWindow";
      case 717:
        return "createView";
      case 718:
        return "cursorPos";
      case 719:
        return "dumpManagedBacktrace";
      case 721:
        return "hasActivePopup";
      case 722:
        return "inDisallowedDragView";
      case 723:
        return "installMessageHandler";
      case 725:
        return "isLeftMouseButtonPressed";
      case 726:
        return "isProcessingAppQuitEvent";
      case 730:
        return "name";
      case 731:
        return "onFloatingWindowCreated";
      case 732:
        return "onFloatingWindowDestroyed";
      case 733:
        return "organizationName";
      case 767:
        return "pauseForDartDebugger";
      case 734:
        return "restoreMouseCursor";
      case 735:
        return "screenNumberFor";
      case 736:
        return "screenSizeFor";
      case 737:
        return "setCursorPos";
      case 738:
        return "setMouseCursor";
      case 740:
        return "startDragDistance_impl";
      case 741:
        return "tests_createFocusableView";
      case 742:
        return "tests_createNonClosableView";
      case 743:
        return "tests_createView";
      case 745:
        return "tests_deinitPlatform_impl";
      case 746:
        return "tests_doubleClickOn";
      case 748:
        return "tests_initPlatform_impl";
      case 750:
        return "tests_wait";
      case 757:
        return "ungrabMouse";
      case 758:
        return "uninstallMessageHandler";
      case 759:
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
    final callback714 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback714, 714);
    final callback715 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback715, 715);
    final callback716 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsFlutter.Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback716, 716);
    final callback717 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.createView_calledFromC);
    registerCallback(thisCpp, callback717, 717);
    final callback718 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback718, 718);
    final callback719 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback719, 719);
    const callbackExcept721 = 0;
    final callback721 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.hasActivePopup_calledFromC,
        callbackExcept721);
    registerCallback(thisCpp, callback721, 721);
    const callbackExcept722 = 0;
    final callback722 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.inDisallowedDragView_calledFromC,
            callbackExcept722);
    registerCallback(thisCpp, callback722, 722);
    final callback723 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback723, 723);
    const callbackExcept725 = 0;
    final callback725 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.isLeftMouseButtonPressed_calledFromC,
        callbackExcept725);
    registerCallback(thisCpp, callback725, 725);
    const callbackExcept726 = 0;
    final callback726 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.isProcessingAppQuitEvent_calledFromC,
        callbackExcept726);
    registerCallback(thisCpp, callback726, 726);
    final callback730 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.name_calledFromC);
    registerCallback(thisCpp, callback730, 730);
    final callback731 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback731, 731);
    final callback732 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback732, 732);
    final callback733 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.organizationName_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    final callback767 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.pauseForDartDebugger_calledFromC);
    registerCallback(thisCpp, callback767, 767);
    final callback734 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback734, 734);
    const callbackExcept735 = 0;
    final callback735 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.screenNumberFor_calledFromC,
            callbackExcept735);
    registerCallback(thisCpp, callback735, 735);
    final callback736 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback736, 736);
    final callback737 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback737, 737);
    final callback738 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback738, 738);
    const callbackExcept740 = 0;
    final callback740 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.startDragDistance_impl_calledFromC,
        callbackExcept740);
    registerCallback(thisCpp, callback740, 740);
    final callback741 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback741, 741);
    final callback742 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback742, 742);
    final callback743 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback743, 743);
    final callback745 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback745, 745);
    final callback746 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_doubleClickOn_calledFromC);
    registerCallback(thisCpp, callback746, 746);
    final callback748 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback748, 748);
    final callback750 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.Platform.tests_wait_calledFromC);
    registerCallback(thisCpp, callback750, 750);
    final callback757 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback757, 757);
    final callback758 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback758, 758);
    const callbackExcept759 = 0;
    final callback759 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Platform.usesFallbackMouseGrabber_calledFromC,
        callbackExcept759);
    registerCallback(thisCpp, callback759, 759);
  }
}
