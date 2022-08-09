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
      case 727:
        return "c_KDDockWidgets__Platform_flutter__applicationName";
      case 728:
        return "c_KDDockWidgets__Platform_flutter__createDefaultViewFactory";
      case 729:
        return "c_KDDockWidgets__Platform_flutter__createView_Controller_View";
      case 730:
        return "c_KDDockWidgets__Platform_flutter__dumpManagedBacktrace";
      case 732:
        return "c_KDDockWidgets__Platform_flutter__hasActivePopup";
      case 733:
        return "c_KDDockWidgets__Platform_flutter__inDisallowedDragView_QPoint";
      case 734:
        return "c_KDDockWidgets__Platform_flutter__installMessageHandler";
      case 736:
        return "c_KDDockWidgets__Platform_flutter__isLeftMouseButtonPressed";
      case 737:
        return "c_KDDockWidgets__Platform_flutter__isProcessingAppQuitEvent";
      case 740:
        return "c_KDDockWidgets__Platform_flutter__name";
      case 741:
        return "c_KDDockWidgets__Platform_flutter__organizationName";
      case 742:
        return "c_KDDockWidgets__Platform_flutter__restoreMouseCursor";
      case 743:
        return "c_KDDockWidgets__Platform_flutter__screenNumberFor_View";
      case 744:
        return "c_KDDockWidgets__Platform_flutter__screenSizeFor_View";
      case 745:
        return "c_KDDockWidgets__Platform_flutter__sendEvent_View_QEvent";
      case 746:
        return "c_KDDockWidgets__Platform_flutter__setMouseCursor_CursorShape";
      case 748:
        return "c_KDDockWidgets__Platform_flutter__startDragDistance_impl";
      case 749:
        return "c_KDDockWidgets__Platform_flutter__tests_createFocusableView_CreateViewOptions_View";
      case 750:
        return "c_KDDockWidgets__Platform_flutter__tests_createNonClosableView_View";
      case 751:
        return "c_KDDockWidgets__Platform_flutter__tests_createView_CreateViewOptions_View";
      case 753:
        return "c_KDDockWidgets__Platform_flutter__tests_deinitPlatform_impl";
      case 755:
        return "c_KDDockWidgets__Platform_flutter__tests_initPlatform_impl";
      case 756:
        return "c_KDDockWidgets__Platform_flutter__tests_wait_int";
      case 763:
        return "c_KDDockWidgets__Platform_flutter__ungrabMouse";
      case 764:
        return "c_KDDockWidgets__Platform_flutter__uninstallMessageHandler";
      case 765:
        return "c_KDDockWidgets__Platform_flutter__usesFallbackMouseGrabber";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 727:
        return "applicationName";
      case 728:
        return "createDefaultViewFactory";
      case 729:
        return "createView";
      case 730:
        return "dumpManagedBacktrace";
      case 732:
        return "hasActivePopup";
      case 733:
        return "inDisallowedDragView";
      case 734:
        return "installMessageHandler";
      case 736:
        return "isLeftMouseButtonPressed";
      case 737:
        return "isProcessingAppQuitEvent";
      case 740:
        return "name";
      case 741:
        return "organizationName";
      case 742:
        return "restoreMouseCursor";
      case 743:
        return "screenNumberFor";
      case 744:
        return "screenSizeFor";
      case 745:
        return "sendEvent";
      case 746:
        return "setMouseCursor";
      case 748:
        return "startDragDistance_impl";
      case 749:
        return "tests_createFocusableView";
      case 750:
        return "tests_createNonClosableView";
      case 751:
        return "tests_createView";
      case 753:
        return "tests_deinitPlatform_impl";
      case 755:
        return "tests_initPlatform_impl";
      case 756:
        return "tests_wait";
      case 763:
        return "ungrabMouse";
      case 764:
        return "uninstallMessageHandler";
      case 765:
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
    final callback727 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.applicationName_calledFromC);
    registerCallback(thisCpp, callback727, 727);
    final callback728 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback728, 728);
    final callback729 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.createView_calledFromC);
    registerCallback(thisCpp, callback729, 729);
    final callback730 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback730, 730);
    const callbackExcept732 = 0;
    final callback732 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.hasActivePopup_calledFromC, callbackExcept732);
    registerCallback(thisCpp, callback732, 732);
    const callbackExcept733 = 0;
    final callback733 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform_flutter.inDisallowedDragView_calledFromC,
            callbackExcept733);
    registerCallback(thisCpp, callback733, 733);
    final callback734 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback734, 734);
    const callbackExcept736 = 0;
    final callback736 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isLeftMouseButtonPressed_calledFromC,
        callbackExcept736);
    registerCallback(thisCpp, callback736, 736);
    const callbackExcept737 = 0;
    final callback737 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.isProcessingAppQuitEvent_calledFromC,
        callbackExcept737);
    registerCallback(thisCpp, callback737, 737);
    final callback740 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform_flutter.name_calledFromC);
    registerCallback(thisCpp, callback740, 740);
    final callback741 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform_flutter.organizationName_calledFromC);
    registerCallback(thisCpp, callback741, 741);
    final callback742 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback742, 742);
    const callbackExcept743 = 0;
    final callback743 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenNumberFor_calledFromC, callbackExcept743);
    registerCallback(thisCpp, callback743, 743);
    final callback744 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback744, 744);
    final callback745 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.sendEvent_calledFromC);
    registerCallback(thisCpp, callback745, 745);
    final callback746 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback746, 746);
    const callbackExcept748 = 0;
    final callback748 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Platform.startDragDistance_impl_calledFromC, callbackExcept748);
    registerCallback(thisCpp, callback748, 748);
    final callback749 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback749, 749);
    final callback750 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback750, 750);
    final callback751 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform_flutter.tests_createView_calledFromC);
    registerCallback(thisCpp, callback751, 751);
    final callback753 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback753, 753);
    final callback755 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback755, 755);
    final callback756 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform_flutter.tests_wait_calledFromC);
    registerCallback(thisCpp, callback756, 756);
    final callback763 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback763, 763);
    final callback764 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform_flutter.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback764, 764);
    const callbackExcept765 = 0;
    final callback765 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform_flutter.usesFallbackMouseGrabber_calledFromC,
        callbackExcept765);
    registerCallback(thisCpp, callback765, 765);
  }
}
