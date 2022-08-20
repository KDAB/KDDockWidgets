/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
            'c_KDDockWidgets__Platform_flutter__constructor')
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
          "Dart instance not found for Platform_flutter::createMainWindow(const QString & uniqueName, KDDockWidgets::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::View * parent, Qt::WindowFlags arg__5) const! (${thisCpp.address})");
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
          "Dart instance not found for Platform_flutter::createView(KDDockWidgets::Controller * controller, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createView(
        Controller.fromCppPointer(controller),
        parent: View.fromCppPointer(parent));
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
            'c_KDDockWidgets__Platform_flutter__init')
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
          "Dart instance not found for Platform_flutter::screenNumberFor(KDDockWidgets::View * arg__1) const! (${thisCpp.address})");
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
          "Dart instance not found for Platform_flutter::screenSizeFor(KDDockWidgets::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenSizeFor(View.fromCppPointer(arg__1));
    return result.thisCpp;
  }

  static void sendEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? arg__2) {
    var dartInstance =
        Platform.s_dartInstanceByCppPtr[thisCpp.address] as Platform_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform_flutter::sendEvent(KDDockWidgets::View * arg__1, QEvent * arg__2) const! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.sendEvent(
        View.fromCppPointer(arg__1), QEvent.fromCppPointer(arg__2));
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
          "Dart instance not found for Platform_flutter::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)! (${thisCpp.address})");
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
          "Dart instance not found for Platform_flutter::tests_createNonClosableView(KDDockWidgets::View * parent)! (${thisCpp.address})");
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
          "Dart instance not found for Platform_flutter::tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::View * parent)! (${thisCpp.address})");
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
            'c_KDDockWidgets__Platform_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 729:
        return "c_KDDockWidgets__Platform_flutter__applicationName";
      case 730:
        return "c_KDDockWidgets__Platform_flutter__createDefaultViewFactory";
      case 731:
        return "c_KDDockWidgets__Platform_flutter__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 732:
        return "c_KDDockWidgets__Platform_flutter__createView_Controller_View";
      case 733:
        return "c_KDDockWidgets__Platform_flutter__dumpManagedBacktrace";
      case 735:
        return "c_KDDockWidgets__Platform_flutter__hasActivePopup";
      case 736:
        return "c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint";
      case 737:
        return "c_KDDockWidgets__Platform_flutter__installMessageHandler";
      case 739:
        return "c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed";
      case 740:
        return "c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent";
      case 744:
        return "c_KDDockWidgets__Platform_flutter__name";
      case 745:
        return "c_KDDockWidgets__Platform_flutter__organizationName";
      case 746:
        return "c_KDDockWidgets__Platform_flutter__restoreMouseCursor";
      case 747:
        return "c_KDDockWidgets__Platform_flutter__screenNumberFor_View";
      case 748:
        return "c_KDDockWidgets__Platform_flutter__screenSizeFor_View";
      case 749:
        return "c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent";
      case 750:
        return "c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape";
      case 752:
        return "c_KDDockWidgets__Platform_flutter__startDragDistance_impl";
      case 753:
        return "c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View";
      case 754:
        return "c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View";
      case 755:
        return "c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View";
      case 757:
        return "c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl";
      case 759:
        return "c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl";
      case 760:
        return "c_KDDockWidgets__Platform_flutter__tests_wait_int";
      case 767:
        return "c_KDDockWidgets__Platform_flutter__ungrabMouse";
      case 768:
        return "c_KDDockWidgets__Platform_flutter__uninstallMessageHandler";
      case 769:
        return "c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 729:
        return "applicationName";
      case 730:
        return "createDefaultViewFactory";
      case 731:
        return "createMainWindow";
      case 732:
        return "createView";
      case 733:
        return "dumpManagedBacktrace";
      case 735:
        return "hasActivePopup";
      case 736:
        return "inDisallowedDragView";
      case 737:
        return "installMessageHandler";
      case 739:
        return "isLeftMouseButtonPressed";
      case 740:
        return "isProcessingAppQuitEvent";
      case 744:
        return "name";
      case 745:
        return "organizationName";
      case 746:
        return "restoreMouseCursor";
      case 747:
        return "screenNumberFor";
      case 748:
        return "screenSizeFor";
      case 749:
        return "sendEvent";
      case 750:
        return "setMouseCursor";
      case 752:
        return "startDragDistance_impl";
      case 753:
        return "tests_createFocusableView";
      case 754:
        return "tests_createNonClosableView";
      case 755:
        return "tests_createView";
      case 757:
        return "tests_deinitPlatform_impl";
      case 759:
        return "tests_initPlatform_impl";
      case 760:
        return "tests_wait";
      case 767:
        return "ungrabMouse";
      case 768:
        return "uninstallMessageHandler";
      case 769:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Platform_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback729 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.applicationName_calledFromC);
    registerCallback(thisCpp, callback729, 729);
    final callback730 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback730, 730);
    final callback731 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        Platform_flutter.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback731, 731);
    final callback732 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.createView_calledFromC);
    registerCallback(thisCpp, callback732, 732);
    final callback733 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    const callbackExcept735 = 0;
    final callback735 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.hasActivePopup_calledFromC, callbackExcept735);
    registerCallback(thisCpp, callback735, 735);
    const callbackExcept736 = 0;
    final callback736 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform_flutter.inDisallowedDragView_calledFromC,
            callbackExcept736);
    registerCallback(thisCpp, callback736, 736);
    final callback737 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback737, 737);
    const callbackExcept739 = 0;
    final callback739 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isLeftMouseButtonPressed_calledFromC,
        callbackExcept739);
    registerCallback(thisCpp, callback739, 739);
    const callbackExcept740 = 0;
    final callback740 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isProcessingAppQuitEvent_calledFromC,
        callbackExcept740);
    registerCallback(thisCpp, callback740, 740);
    final callback744 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform_flutter.name_calledFromC);
    registerCallback(thisCpp, callback744, 744);
    final callback745 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.organizationName_calledFromC);
    registerCallback(thisCpp, callback745, 745);
    final callback746 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback746, 746);
    const callbackExcept747 = 0;
    final callback747 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenNumberFor_calledFromC, callbackExcept747);
    registerCallback(thisCpp, callback747, 747);
    final callback748 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback748, 748);
    final callback749 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.sendEvent_calledFromC);
    registerCallback(thisCpp, callback749, 749);
    final callback750 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback750, 750);
    const callbackExcept752 = 0;
    final callback752 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Platform.startDragDistance_impl_calledFromC, callbackExcept752);
    registerCallback(thisCpp, callback752, 752);
    final callback753 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback753, 753);
    final callback754 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback754, 754);
    final callback755 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createView_calledFromC);
    registerCallback(thisCpp, callback755, 755);
    final callback757 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback757, 757);
    final callback759 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback759, 759);
    final callback760 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_wait_calledFromC);
    registerCallback(thisCpp, callback760, 760);
    final callback767 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback767, 767);
    final callback768 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback768, 768);
    const callbackExcept769 = 0;
    final callback769 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.usesFallbackMouseGrabber_calledFromC,
        callbackExcept769);
    registerCallback(thisCpp, callback769, 769);
  }
}
