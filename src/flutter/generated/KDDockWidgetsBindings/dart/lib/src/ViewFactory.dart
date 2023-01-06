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

class ViewFactory extends QObject {
  ViewFactory.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  ViewFactory.init() : super.init() {}
  factory ViewFactory.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (QObject.isCached(cppPointer)) {
      var instance = QObject.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as ViewFactory;
    }
    return ViewFactory.fromCppPointer(cppPointer, needsAutoDelete);
  } //ViewFactory()
  ViewFactory() : super.init() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__ViewFactory__constructor')
        .asFunction();
    thisCpp = func();
    QObject.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const
  ClassicIndicatorWindowViewInterface createClassicIndicatorWindow(
      ClassicIndicators? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(689))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return ClassicIndicatorWindowViewInterface.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createClassicIndicatorWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createClassicIndicatorWindow(KDDockWidgets::Controllers::ClassicIndicators * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance
        .createClassicIndicatorWindow(ClassicIndicators.fromCppPointer(arg__1));
    return result.thisCpp;
  } // createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const

  View createDockWidget(String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0, int windowFlags = 0}) {
    final voidstar_Func_voidstar_voidstar_int_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(690))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        uniqueName?.toNativeUtf8() ?? ffi.nullptr,
        options,
        layoutSaverOptions,
        windowFlags);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? uniqueName,
      int options,
      int layoutSaverOptions,
      int windowFlags) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createDockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions, Qt::WindowFlags windowFlags) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDockWidget(
        QString.fromCppPointer(uniqueName).toDartString(),
        options: options,
        layoutSaverOptions: layoutSaverOptions,
        windowFlags: windowFlags);
    return result.thisCpp;
  } // createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const

  View createDropArea(DropArea? arg__1, View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(691))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createDropArea_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createDropArea(KDDockWidgets::Controllers::DropArea * arg__1, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDropArea(
        DropArea.fromCppPointer(arg__1), View.fromCppPointer(parent));
    return result.thisCpp;
  } // createFloatingWindow(KDDockWidgets::Controllers::FloatingWindow * controller, KDDockWidgets::Controllers::MainWindow * parent, Qt::WindowFlags windowFlags) const

  View createFloatingWindow(FloatingWindow? controller,
      {required MainWindow? parent, int windowFlags = 0}) {
    final voidstar_Func_voidstar_voidstar_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(692))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp,
        windowFlags);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createFloatingWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller,
      ffi.Pointer<void>? parent,
      int windowFlags) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createFloatingWindow(KDDockWidgets::Controllers::FloatingWindow * controller, KDDockWidgets::Controllers::MainWindow * parent, Qt::WindowFlags windowFlags) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createFloatingWindow(
        FloatingWindow.fromCppPointer(controller),
        parent: MainWindow.fromCppPointer(parent),
        windowFlags: windowFlags);
    return result.thisCpp;
  } // createGroup(KDDockWidgets::Controllers::Group * arg__1, KDDockWidgets::View * parent) const

  View createGroup(Group? arg__1, {required View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(693))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createGroup_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createGroup(KDDockWidgets::Controllers::Group * arg__1, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createGroup(Group.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  } // createRubberBand(KDDockWidgets::View * parent) const

  View createRubberBand(View? parent) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(694))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createRubberBand_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createRubberBand(KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createRubberBand(View.fromCppPointer(parent));
    return result.thisCpp;
  } // createSeparator(KDDockWidgets::Controllers::Separator * arg__1, KDDockWidgets::View * parent) const

  View createSeparator(Separator? arg__1, {required View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(695))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createSeparator_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createSeparator(KDDockWidgets::Controllers::Separator * arg__1, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createSeparator(
        Separator.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  } // createSideBar(KDDockWidgets::Controllers::SideBar * arg__1, KDDockWidgets::View * parent) const

  View createSideBar(SideBar? arg__1, View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(696))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createSideBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createSideBar(KDDockWidgets::Controllers::SideBar * arg__1, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createSideBar(
        SideBar.fromCppPointer(arg__1), View.fromCppPointer(parent));
    return result.thisCpp;
  } // createStack(KDDockWidgets::Controllers::Stack * stack, KDDockWidgets::View * parent) const

  View createStack(Stack? stack, View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(697))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        stack == null ? ffi.nullptr : stack.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createStack_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? stack, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createStack(KDDockWidgets::Controllers::Stack * stack, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createStack(
        Stack.fromCppPointer(stack), View.fromCppPointer(parent));
    return result.thisCpp;
  } // createTabBar(KDDockWidgets::Controllers::TabBar * tabBar, KDDockWidgets::View * parent) const

  View createTabBar(TabBar? tabBar, {required View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(698))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        tabBar == null ? ffi.nullptr : tabBar.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createTabBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? tabBar, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createTabBar(KDDockWidgets::Controllers::TabBar * tabBar, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createTabBar(TabBar.fromCppPointer(tabBar),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  } // createTitleBar(KDDockWidgets::Controllers::TitleBar * controller, KDDockWidgets::View * parent) const

  View createTitleBar(TitleBar? controller, View? parent) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(699))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createTitleBar_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? controller, ffi.Pointer<void>? parent) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::createTitleBar(KDDockWidgets::Controllers::TitleBar * controller, KDDockWidgets::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createTitleBar(
        TitleBar.fromCppPointer(controller), View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static void customEvent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::customEvent(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.customEvent(QEvent.fromCppPointer(event));
  }

  static int event_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::event(QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.event(QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static int eventFilter_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? watched, ffi.Pointer<void>? event) {
    var dartInstance =
        QObject.s_dartInstanceByCppPtr[thisCpp.address] as ViewFactory;
    if (dartInstance == null) {
      print(
          "Dart instance not found for ViewFactory::eventFilter(QObject * watched, QEvent * event)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.eventFilter(
        QObject.fromCppPointer(watched), QEvent.fromCppPointer(event));
    return result ? 1 : 0;
  }

  static // tr(const char * s, const char * c, int n)
      QString tr(String? s, String? c, int n) {
    final voidstar_Func_string_string_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_string_string_ffi_Int32_FFI>>(
            'c_static_KDDockWidgets__ViewFactory__tr_char_char_int')
        .asFunction();
    ffi.Pointer<void> result = func(
        s?.toNativeUtf8() ?? ffi.nullptr, c?.toNativeUtf8() ?? ffi.nullptr, n);
    return QString.fromCppPointer(result, true);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__ViewFactory__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 689:
        return "c_KDDockWidgets__ViewFactory__createClassicIndicatorWindow_ClassicIndicators";
      case 690:
        return "c_KDDockWidgets__ViewFactory__createDockWidget_QString_DockWidgetOptions_LayoutSaverOptions_WindowFlags";
      case 691:
        return "c_KDDockWidgets__ViewFactory__createDropArea_DropArea_View";
      case 692:
        return "c_KDDockWidgets__ViewFactory__createFloatingWindow_FloatingWindow_MainWindow_WindowFlags";
      case 693:
        return "c_KDDockWidgets__ViewFactory__createGroup_Group_View";
      case 694:
        return "c_KDDockWidgets__ViewFactory__createRubberBand_View";
      case 695:
        return "c_KDDockWidgets__ViewFactory__createSeparator_Separator_View";
      case 696:
        return "c_KDDockWidgets__ViewFactory__createSideBar_SideBar_View";
      case 697:
        return "c_KDDockWidgets__ViewFactory__createStack_Stack_View";
      case 698:
        return "c_KDDockWidgets__ViewFactory__createTabBar_TabBar_View";
      case 699:
        return "c_KDDockWidgets__ViewFactory__createTitleBar_TitleBar_View";
      case 295:
        return "c_KDDockWidgets__ViewFactory__customEvent_QEvent";
      case 306:
        return "c_KDDockWidgets__ViewFactory__event_QEvent";
      case 307:
        return "c_KDDockWidgets__ViewFactory__eventFilter_QObject_QEvent";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 689:
        return "createClassicIndicatorWindow";
      case 690:
        return "createDockWidget";
      case 691:
        return "createDropArea";
      case 692:
        return "createFloatingWindow";
      case 693:
        return "createGroup";
      case 694:
        return "createRubberBand";
      case 695:
        return "createSeparator";
      case 696:
        return "createSideBar";
      case 697:
        return "createStack";
      case 698:
        return "createTabBar";
      case 699:
        return "createTitleBar";
      case 295:
        return "customEvent";
      case 306:
        return "event";
      case 307:
        return "eventFilter";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__ViewFactory__registerVirtualMethodCallback')
        .asFunction();
    final callback689 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            ViewFactory.createClassicIndicatorWindow_calledFromC);
    registerCallback(thisCpp, callback689, 689);
    final callback690 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_ffi_Int32_FFI>(
        ViewFactory.createDockWidget_calledFromC);
    registerCallback(thisCpp, callback690, 690);
    final callback691 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createDropArea_calledFromC);
    registerCallback(thisCpp, callback691, 691);
    final callback692 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_FFI>(
        ViewFactory.createFloatingWindow_calledFromC);
    registerCallback(thisCpp, callback692, 692);
    final callback693 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createGroup_calledFromC);
    registerCallback(thisCpp, callback693, 693);
    final callback694 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            ViewFactory.createRubberBand_calledFromC);
    registerCallback(thisCpp, callback694, 694);
    final callback695 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createSeparator_calledFromC);
    registerCallback(thisCpp, callback695, 695);
    final callback696 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createSideBar_calledFromC);
    registerCallback(thisCpp, callback696, 696);
    final callback697 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createStack_calledFromC);
    registerCallback(thisCpp, callback697, 697);
    final callback698 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createTabBar_calledFromC);
    registerCallback(thisCpp, callback698, 698);
    final callback699 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            ViewFactory.createTitleBar_calledFromC);
    registerCallback(thisCpp, callback699, 699);
    final callback295 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            QObject.customEvent_calledFromC);
    registerCallback(thisCpp, callback295, 295);
    const callbackExcept306 = 0;
    final callback306 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            QObject.event_calledFromC, callbackExcept306);
    registerCallback(thisCpp, callback306, 306);
    const callbackExcept307 = 0;
    final callback307 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_voidstar_FFI>(
            QObject.eventFilter_calledFromC, callbackExcept307);
    registerCallback(thisCpp, callback307, 307);
  }
}
