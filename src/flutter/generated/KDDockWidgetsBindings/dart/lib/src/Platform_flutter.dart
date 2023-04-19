/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

var _dylib = Library.instance().dylib;

class Platform_flutter extends Platform {
  Platform_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Platform_flutter.init() : super.init() {}
  factory Platform_flutter.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    if (Platform.isCached(cppPointer)) {
      var instance = Platform.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Platform_flutter;
    }
    return Platform_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  } //Platform_flutter()
  Platform_flutter() : super.init() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__flutter__Platform_flutter__constructor')
        .asFunction();
    thisCpp = func();
    Platform.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static ffi.Pointer<void> applicationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::applicationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.applicationName();
    return result.thisCpp;
  }

  static ffi.Pointer<void> createDefaultViewFactory_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::createDefaultViewFactory()! (${thisCpp.address})");
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
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::createMainWindow(const QString & uniqueName, KDDockWidgets::Core::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags arg__5) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createMainWindow(
        QString.fromCppPointer(uniqueName).toDartString(),
        CreateViewOptions.fromCppPointer(arg__2),
        options: options,
        parent: View.fromCppPointer(parent),
        arg__5: arg__5);
    return result.thisCpp;
  }

  static ffi.Pointer<void> createView_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller, ffi.Pointer<void>? parent) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::createView(KDDockWidgets::Core::Controller * controller, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createView(
        Controller.fromCppPointer(controller),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> cursorPos_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::cursorPos() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.cursorPos();
    return result.thisCpp;
  }

  static void dumpManagedBacktrace_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::dumpManagedBacktrace()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.dumpManagedBacktrace();
  }

  static int hasActivePopup_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::hasActivePopup() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasActivePopup();
    return result ? 1 : 0;
  }

  static int inDisallowedDragView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::inDisallowedDragView(QPoint globalPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result =
        dartInstance.inDisallowedDragView(QPoint.fromCppPointer(globalPos));
    return result ? 1 : 0;
  } // init()

  init() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Platform_flutter__init')
        .asFunction();
    func(thisCpp);
  }

  static void installMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::installMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.installMessageHandler();
  }

  static int isLeftMouseButtonPressed_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::isLeftMouseButtonPressed() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isLeftMouseButtonPressed();
    return result ? 1 : 0;
  }

  static int isProcessingAppQuitEvent_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::isProcessingAppQuitEvent() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isProcessingAppQuitEvent();
    return result ? 1 : 0;
  }

  static ffi.Pointer<Utf8> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::name() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.name();
    return result.toNativeUtf8();
  }

  static void onFloatingWindowCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onFloatingWindowCreated(FloatingWindow.fromCppPointer(arg__1));
  }

  static void onFloatingWindowDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance
        .onFloatingWindowDestroyed(FloatingWindow.fromCppPointer(arg__1));
  }

  static ffi.Pointer<void> organizationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::organizationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.organizationName();
    return result.thisCpp;
  }

  static // platformFlutter()
      Platform_flutter platformFlutter() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__flutter__Platform_flutter__platformFlutter')
        .asFunction();
    ffi.Pointer<void> result = func();
    return Platform_flutter.fromCppPointer(result, false);
  }

  static void restoreMouseCursor_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::restoreMouseCursor()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.restoreMouseCursor();
  }

  static int screenNumberFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::screenNumberFor(KDDockWidgets::Core::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenNumberFor(View.fromCppPointer(arg__1));
    return result;
  }

  static ffi.Pointer<void> screenSizeFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::screenSizeFor(KDDockWidgets::Core::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenSizeFor(View.fromCppPointer(arg__1));
    return result.thisCpp;
  }

  static void setCursorPos_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::setCursorPos(QPoint arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursorPos(QPoint.fromCppPointer(arg__1));
  }

  static void setMouseCursor_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::setMouseCursor(Qt::CursorShape arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseCursor(arg__1);
  }

  static int startDragDistance_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::startDragDistance_impl() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.startDragDistance_impl();
    return result;
  }

  static ffi.Pointer<void> tests_createFocusableView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_createFocusableView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createFocusableView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> tests_createNonClosableView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_createNonClosableView(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createNonClosableView(
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static ffi.Pointer<void> tests_createView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_createView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static void tests_deinitPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_deinitPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_deinitPlatform_impl();
  }

  static void tests_doubleClickOn_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> globalPos, ffi.Pointer<void>? receiver) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_doubleClickOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_doubleClickOn(
        QPoint.fromCppPointer(globalPos), View.fromCppPointer(receiver));
  }

  static void tests_initPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_initPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_initPlatform_impl();
  }

  static void tests_wait_calledFromC(ffi.Pointer<void> thisCpp, int ms) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::tests_wait(int ms)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_wait(ms);
  }

  static void ungrabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::ungrabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.ungrabMouse();
  }

  static void uninstallMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::uninstallMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.uninstallMessageHandler();
  }

  static int usesFallbackMouseGrabber_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::usesFallbackMouseGrabber() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.usesFallbackMouseGrabber();
    return result ? 1 : 0;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Platform_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 697:
        return "c_KDDockWidgets__flutter__Platform_flutter__applicationName";
      case 698:
        return "c_KDDockWidgets__flutter__Platform_flutter__createDefaultViewFactory";
      case 699:
        return "c_KDDockWidgets__flutter__Platform_flutter__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 700:
        return "c_KDDockWidgets__flutter__Platform_flutter__createView_Controller_View";
      case 701:
        return "c_KDDockWidgets__flutter__Platform_flutter__cursorPos";
      case 702:
        return "c_KDDockWidgets__flutter__Platform_flutter__dumpManagedBacktrace";
      case 704:
        return "c_KDDockWidgets__flutter__Platform_flutter__hasActivePopup";
      case 705:
        return "c_KDDockWidgets__flutter__Platform_flutter__inDisallowedDragView_QPoint";
      case 706:
        return "c_KDDockWidgets__flutter__Platform_flutter__installMessageHandler";
      case 708:
        return "c_KDDockWidgets__flutter__Platform_flutter__isLeftMouseButtonPressed";
      case 709:
        return "c_KDDockWidgets__flutter__Platform_flutter__isProcessingAppQuitEvent";
      case 713:
        return "c_KDDockWidgets__flutter__Platform_flutter__name";
      case 714:
        return "c_KDDockWidgets__flutter__Platform_flutter__onFloatingWindowCreated_FloatingWindow";
      case 715:
        return "c_KDDockWidgets__flutter__Platform_flutter__onFloatingWindowDestroyed_FloatingWindow";
      case 716:
        return "c_KDDockWidgets__flutter__Platform_flutter__organizationName";
      case 717:
        return "c_KDDockWidgets__flutter__Platform_flutter__restoreMouseCursor";
      case 718:
        return "c_KDDockWidgets__flutter__Platform_flutter__screenNumberFor_View";
      case 719:
        return "c_KDDockWidgets__flutter__Platform_flutter__screenSizeFor_View";
      case 720:
        return "c_KDDockWidgets__flutter__Platform_flutter__setCursorPos_QPoint";
      case 721:
        return "c_KDDockWidgets__flutter__Platform_flutter__setMouseCursor_CursorShape";
      case 723:
        return "c_KDDockWidgets__flutter__Platform_flutter__startDragDistance_impl";
      case 724:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_createFocusableView_CreateViewOptions_View";
      case 725:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_createNonClosableView_View";
      case 726:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_createView_CreateViewOptions_View";
      case 728:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_deinitPlatform_impl";
      case 729:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_doubleClickOn_QPoint_View";
      case 731:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_initPlatform_impl";
      case 733:
        return "c_KDDockWidgets__flutter__Platform_flutter__tests_wait_int";
      case 740:
        return "c_KDDockWidgets__flutter__Platform_flutter__ungrabMouse";
      case 741:
        return "c_KDDockWidgets__flutter__Platform_flutter__uninstallMessageHandler";
      case 742:
        return "c_KDDockWidgets__flutter__Platform_flutter__usesFallbackMouseGrabber";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 697:
        return "applicationName";
      case 698:
        return "createDefaultViewFactory";
      case 699:
        return "createMainWindow";
      case 700:
        return "createView";
      case 701:
        return "cursorPos";
      case 702:
        return "dumpManagedBacktrace";
      case 704:
        return "hasActivePopup";
      case 705:
        return "inDisallowedDragView";
      case 706:
        return "installMessageHandler";
      case 708:
        return "isLeftMouseButtonPressed";
      case 709:
        return "isProcessingAppQuitEvent";
      case 713:
        return "name";
      case 714:
        return "onFloatingWindowCreated";
      case 715:
        return "onFloatingWindowDestroyed";
      case 716:
        return "organizationName";
      case 717:
        return "restoreMouseCursor";
      case 718:
        return "screenNumberFor";
      case 719:
        return "screenSizeFor";
      case 720:
        return "setCursorPos";
      case 721:
        return "setMouseCursor";
      case 723:
        return "startDragDistance_impl";
      case 724:
        return "tests_createFocusableView";
      case 725:
        return "tests_createNonClosableView";
      case 726:
        return "tests_createView";
      case 728:
        return "tests_deinitPlatform_impl";
      case 729:
        return "tests_doubleClickOn";
      case 731:
        return "tests_initPlatform_impl";
      case 733:
        return "tests_wait";
      case 740:
        return "ungrabMouse";
      case 741:
        return "uninstallMessageHandler";
      case 742:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__Platform_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback697 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.applicationName_calledFromC);
    registerCallback(thisCpp, callback697, 697);
    final callback698 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback698, 698);
    final callback699 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        Platform_flutter.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback699, 699);
    final callback700 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.createView_calledFromC);
    registerCallback(thisCpp, callback700, 700);
    final callback701 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.cursorPos_calledFromC);
    registerCallback(thisCpp, callback701, 701);
    final callback702 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback702, 702);
    const callbackExcept704 = 0;
    final callback704 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.hasActivePopup_calledFromC, callbackExcept704);
    registerCallback(thisCpp, callback704, 704);
    const callbackExcept705 = 0;
    final callback705 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform_flutter.inDisallowedDragView_calledFromC,
            callbackExcept705);
    registerCallback(thisCpp, callback705, 705);
    final callback706 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback706, 706);
    const callbackExcept708 = 0;
    final callback708 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isLeftMouseButtonPressed_calledFromC,
        callbackExcept708);
    registerCallback(thisCpp, callback708, 708);
    const callbackExcept709 = 0;
    final callback709 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isProcessingAppQuitEvent_calledFromC,
        callbackExcept709);
    registerCallback(thisCpp, callback709, 709);
    final callback713 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform_flutter.name_calledFromC);
    registerCallback(thisCpp, callback713, 713);
    final callback714 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Platform_flutter.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback714, 714);
    final callback715 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Platform_flutter.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback715, 715);
    final callback716 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.organizationName_calledFromC);
    registerCallback(thisCpp, callback716, 716);
    final callback717 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback717, 717);
    const callbackExcept718 = 0;
    final callback718 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenNumberFor_calledFromC, callbackExcept718);
    registerCallback(thisCpp, callback718, 718);
    final callback719 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback719, 719);
    final callback720 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Platform_flutter.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback720, 720);
    final callback721 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback721, 721);
    const callbackExcept723 = 0;
    final callback723 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Platform.startDragDistance_impl_calledFromC, callbackExcept723);
    registerCallback(thisCpp, callback723, 723);
    final callback724 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback724, 724);
    final callback725 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback725, 725);
    final callback726 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createView_calledFromC);
    registerCallback(thisCpp, callback726, 726);
    final callback728 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback728, 728);
    final callback729 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform.tests_doubleClickOn_calledFromC);
    registerCallback(thisCpp, callback729, 729);
    final callback731 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback731, 731);
    final callback733 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_wait_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    final callback740 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback740, 740);
    final callback741 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback741, 741);
    const callbackExcept742 = 0;
    final callback742 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.usesFallbackMouseGrabber_calledFromC,
        callbackExcept742);
    registerCallback(thisCpp, callback742, 742);
  }
}
