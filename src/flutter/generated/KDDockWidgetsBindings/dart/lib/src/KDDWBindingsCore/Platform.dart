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
final _finalizer =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_KDDockWidgets__Core__Platform_Finalizer');

class Platform {
  static var s_dartInstanceByCppPtr = Map<int, Platform>();
  var _thisCpp = null;
  bool _needsAutoDelete = false;
  get thisCpp => _thisCpp;
  set thisCpp(var ptr) {
    _thisCpp = ptr;
    ffi.Pointer<ffi.Void> ptrvoid = ptr.cast<ffi.Void>();
    if (_needsAutoDelete)
      newWeakPersistentHandle?.call(this, ptrvoid, 0, _finalizer);
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
  int get m_numWarningsEmitted {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform___get_m_numWarningsEmitted')
        .asFunction();
    return func(thisCpp);
  }

  set m_numWarningsEmitted(int m_numWarningsEmitted_) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Core__Platform___set_m_numWarningsEmitted_int')
        .asFunction();
    func(thisCpp, m_numWarningsEmitted_);
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
            cFunctionSymbolName(697))
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
            cFunctionSymbolName(698))
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
            cFunctionSymbolName(699))
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
        parent: KDDWBindingsCore.View.fromCppPointer(parent),
        arg__5: arg__5);
    return result.thisCpp;
  } // createView(KDDockWidgets::Core::Controller * arg__1, KDDockWidgets::Core::View * parent) const

  KDDWBindingsCore.View createView(KDDWBindingsCore.Controller? arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(700))
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
        KDDWBindingsCore.Controller.fromCppPointer(arg__1),
        parent: KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // cursorPos() const

  QPoint cursorPos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(701))
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
            cFunctionSymbolName(702))
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
            cFunctionSymbolName(704))
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
            cFunctionSymbolName(705))
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
            cFunctionSymbolName(706))
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
  } // isLeftMouseButtonPressed() const

  bool isLeftMouseButtonPressed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(708))
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
            cFunctionSymbolName(709))
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
            cFunctionSymbolName(713))
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
            cFunctionSymbolName(714))
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
    dartInstance.onFloatingWindowCreated(
        KDDWBindingsCore.FloatingWindow.fromCppPointer(arg__1));
  } // onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)

  onFloatingWindowDestroyed(KDDWBindingsCore.FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(715))
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
        KDDWBindingsCore.FloatingWindow.fromCppPointer(arg__1));
  } // organizationName() const

  QString organizationName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(716))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> organizationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::organizationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.organizationName();
    return result.thisCpp;
  } // restoreMouseCursor()

  restoreMouseCursor() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(717))
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
  } // screenNumberFor(KDDockWidgets::Core::View * arg__1) const

  int screenNumberFor(KDDWBindingsCore.View? arg__1) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(718))
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
    final result = dartInstance
        .screenNumberFor(KDDWBindingsCore.View.fromCppPointer(arg__1));
    return result;
  } // screenSizeFor(KDDockWidgets::Core::View * arg__1) const

  QSize screenSizeFor(KDDWBindingsCore.View? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(719))
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
    final result = dartInstance
        .screenSizeFor(KDDWBindingsCore.View.fromCppPointer(arg__1));
    return result.thisCpp;
  } // setCursorPos(QPoint arg__1)

  setCursorPos(QPoint arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(720))
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
            cFunctionSymbolName(721))
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
            cFunctionSymbolName(723))
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
            cFunctionSymbolName(724))
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
        parent: KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // tests_createNonClosableView(KDDockWidgets::Core::View * parent)

  KDDWBindingsCore.View tests_createNonClosableView(
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(725))
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
        parent: KDDWBindingsCore.View.fromCppPointer(parent));
    return result.thisCpp;
  } // tests_createView(KDDockWidgets::Core::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)

  KDDWBindingsCore.View tests_createView(CreateViewOptions arg__1,
      {required KDDWBindingsCore.View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(726))
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
        parent: KDDWBindingsCore.View.fromCppPointer(parent));
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
            cFunctionSymbolName(728))
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
  } // tests_doubleClickOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)

  tests_doubleClickOn(QPoint globalPos, KDDWBindingsCore.View? receiver) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(729))
        .asFunction();
    func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp,
        receiver == null ? ffi.nullptr : receiver.thisCpp);
  }

  static void tests_doubleClickOn_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> globalPos, ffi.Pointer<void>? receiver) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_doubleClickOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_doubleClickOn(QPoint.fromCppPointer(globalPos),
        KDDWBindingsCore.View.fromCppPointer(receiver));
  } // tests_initPlatform_impl()

  tests_initPlatform_impl() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(731))
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
  } // tests_pressOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)

  tests_pressOn(QPoint globalPos, KDDWBindingsCore.View? receiver) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Core__Platform__tests_pressOn_QPoint_View')
        .asFunction();
    func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp,
        receiver == null ? ffi.nullptr : receiver.thisCpp);
  } // tests_wait(int ms)

  tests_wait(int ms) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(733))
        .asFunction();
    func(thisCpp, ms);
  }

  static void tests_wait_calledFromC(ffi.Pointer<void> thisCpp, int ms) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_wait(int ms)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_wait(ms);
  } // tests_waitForDeleted(KDDockWidgets::Core::View * arg__1, int timeout) const

  bool tests_waitForDeleted(KDDWBindingsCore.View? arg__1,
      {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(734))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForDeleted_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForDeleted(KDDockWidgets::Core::View * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForDeleted(
        KDDWBindingsCore.View.fromCppPointer(arg__1),
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForDeleted(QObject * arg__1, int timeout) const

  bool tests_waitForDeleted_2(QObject? arg__1, {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(735))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForDeleted_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForDeleted(QObject * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForDeleted_2(
        QObject.fromCppPointer(arg__1),
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForEvent(KDDockWidgets::Core::View * arg__1, Event::Type type, int timeout) const

  bool tests_waitForEvent(KDDWBindingsCore.View? arg__1, int type,
      {int timeout = 5000}) {
    final bool_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(736))
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, type,
            timeout) !=
        0;
  }

  static int tests_waitForEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, int type, int timeout) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForEvent(KDDockWidgets::Core::View * arg__1, Event::Type type, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForEvent(
        KDDWBindingsCore.View.fromCppPointer(arg__1), type,
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForEvent(QObject * w, Event::Type type, int timeout) const

  bool tests_waitForEvent_2(QObject? w, int type, {int timeout = 5000}) {
    final bool_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(737))
        .asFunction();
    return func(thisCpp, w == null ? ffi.nullptr : w.thisCpp, type, timeout) !=
        0;
  }

  static int tests_waitForEvent_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? w, int type, int timeout) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForEvent(QObject * w, Event::Type type, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForEvent_2(
        QObject.fromCppPointer(w), type,
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForResize(KDDockWidgets::Core::Controller * arg__1, int timeout) const

  bool tests_waitForResize(KDDWBindingsCore.Controller? arg__1,
      {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(738))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForResize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForResize(KDDockWidgets::Core::Controller * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForResize(
        KDDWBindingsCore.Controller.fromCppPointer(arg__1),
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForResize(KDDockWidgets::Core::View * arg__1, int timeout) const

  bool tests_waitForResize_2(KDDWBindingsCore.View? arg__1,
      {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(739))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForResize_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance =
        KDDWBindingsCore.Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForResize(KDDockWidgets::Core::View * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForResize_2(
        KDDWBindingsCore.View.fromCppPointer(arg__1),
        timeout: timeout);
    return result ? 1 : 0;
  } // ungrabMouse()

  ungrabMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(740))
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
            cFunctionSymbolName(741))
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
            cFunctionSymbolName(742))
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
      case 697:
        return "c_KDDockWidgets__Core__Platform__applicationName";
      case 698:
        return "c_KDDockWidgets__Core__Platform__createDefaultViewFactory";
      case 699:
        return "c_KDDockWidgets__Core__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 700:
        return "c_KDDockWidgets__Core__Platform__createView_Controller_View";
      case 701:
        return "c_KDDockWidgets__Core__Platform__cursorPos";
      case 702:
        return "c_KDDockWidgets__Core__Platform__dumpManagedBacktrace";
      case 704:
        return "c_KDDockWidgets__Core__Platform__hasActivePopup";
      case 705:
        return "c_KDDockWidgets__Core__Platform__inDisallowedDragView_QPoint";
      case 706:
        return "c_KDDockWidgets__Core__Platform__installMessageHandler";
      case 708:
        return "c_KDDockWidgets__Core__Platform__isLeftMouseButtonPressed";
      case 709:
        return "c_KDDockWidgets__Core__Platform__isProcessingAppQuitEvent";
      case 713:
        return "c_KDDockWidgets__Core__Platform__name";
      case 714:
        return "c_KDDockWidgets__Core__Platform__onFloatingWindowCreated_FloatingWindow";
      case 715:
        return "c_KDDockWidgets__Core__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 716:
        return "c_KDDockWidgets__Core__Platform__organizationName";
      case 717:
        return "c_KDDockWidgets__Core__Platform__restoreMouseCursor";
      case 718:
        return "c_KDDockWidgets__Core__Platform__screenNumberFor_View";
      case 719:
        return "c_KDDockWidgets__Core__Platform__screenSizeFor_View";
      case 720:
        return "c_KDDockWidgets__Core__Platform__setCursorPos_QPoint";
      case 721:
        return "c_KDDockWidgets__Core__Platform__setMouseCursor_CursorShape";
      case 723:
        return "c_KDDockWidgets__Core__Platform__startDragDistance_impl";
      case 724:
        return "c_KDDockWidgets__Core__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 725:
        return "c_KDDockWidgets__Core__Platform__tests_createNonClosableView_View";
      case 726:
        return "c_KDDockWidgets__Core__Platform__tests_createView_CreateViewOptions_View";
      case 728:
        return "c_KDDockWidgets__Core__Platform__tests_deinitPlatform_impl";
      case 729:
        return "c_KDDockWidgets__Core__Platform__tests_doubleClickOn_QPoint_View";
      case 731:
        return "c_KDDockWidgets__Core__Platform__tests_initPlatform_impl";
      case 733:
        return "c_KDDockWidgets__Core__Platform__tests_wait_int";
      case 734:
        return "c_KDDockWidgets__Core__Platform__tests_waitForDeleted_View_int";
      case 735:
        return "c_KDDockWidgets__Core__Platform__tests_waitForDeleted_QObject_int";
      case 736:
        return "c_KDDockWidgets__Core__Platform__tests_waitForEvent_View_Type_int";
      case 737:
        return "c_KDDockWidgets__Core__Platform__tests_waitForEvent_QObject_Type_int";
      case 738:
        return "c_KDDockWidgets__Core__Platform__tests_waitForResize_Controller_int";
      case 739:
        return "c_KDDockWidgets__Core__Platform__tests_waitForResize_View_int";
      case 740:
        return "c_KDDockWidgets__Core__Platform__ungrabMouse";
      case 741:
        return "c_KDDockWidgets__Core__Platform__uninstallMessageHandler";
      case 742:
        return "c_KDDockWidgets__Core__Platform__usesFallbackMouseGrabber";
    }
    return "";
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
      case 734:
        return "tests_waitForDeleted";
      case 735:
        return "tests_waitForDeleted_2";
      case 736:
        return "tests_waitForEvent";
      case 737:
        return "tests_waitForEvent_2";
      case 738:
        return "tests_waitForResize";
      case 739:
        return "tests_waitForResize_2";
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
            'c_KDDockWidgets__Core__Platform__registerVirtualMethodCallback')
        .asFunction();
    final callback697 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback697, 697);
    final callback698 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback698, 698);
    final callback699 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        KDDWBindingsCore.Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback699, 699);
    final callback700 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.createView_calledFromC);
    registerCallback(thisCpp, callback700, 700);
    final callback701 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback701, 701);
    final callback702 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback702, 702);
    const callbackExcept704 = 0;
    final callback704 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.hasActivePopup_calledFromC,
        callbackExcept704);
    registerCallback(thisCpp, callback704, 704);
    const callbackExcept705 = 0;
    final callback705 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.inDisallowedDragView_calledFromC,
            callbackExcept705);
    registerCallback(thisCpp, callback705, 705);
    final callback706 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback706, 706);
    const callbackExcept708 = 0;
    final callback708 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.isLeftMouseButtonPressed_calledFromC,
        callbackExcept708);
    registerCallback(thisCpp, callback708, 708);
    const callbackExcept709 = 0;
    final callback709 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.isProcessingAppQuitEvent_calledFromC,
        callbackExcept709);
    registerCallback(thisCpp, callback709, 709);
    final callback713 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.name_calledFromC);
    registerCallback(thisCpp, callback713, 713);
    final callback714 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback714, 714);
    final callback715 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback715, 715);
    final callback716 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.organizationName_calledFromC);
    registerCallback(thisCpp, callback716, 716);
    final callback717 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback717, 717);
    const callbackExcept718 = 0;
    final callback718 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.screenNumberFor_calledFromC,
            callbackExcept718);
    registerCallback(thisCpp, callback718, 718);
    final callback719 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback719, 719);
    final callback720 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback720, 720);
    final callback721 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback721, 721);
    const callbackExcept723 = 0;
    final callback723 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.startDragDistance_impl_calledFromC,
        callbackExcept723);
    registerCallback(thisCpp, callback723, 723);
    final callback724 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback724, 724);
    final callback725 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback725, 725);
    final callback726 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback726, 726);
    final callback728 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback728, 728);
    final callback729 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsCore.Platform.tests_doubleClickOn_calledFromC);
    registerCallback(thisCpp, callback729, 729);
    final callback731 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback731, 731);
    final callback733 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.tests_wait_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    const callbackExcept734 = 0;
    final callback734 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.tests_waitForDeleted_calledFromC,
            callbackExcept734);
    registerCallback(thisCpp, callback734, 734);
    const callbackExcept735 = 0;
    final callback735 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.tests_waitForDeleted_2_calledFromC,
            callbackExcept735);
    registerCallback(thisCpp, callback735, 735);
    const callbackExcept736 = 0;
    final callback736 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        KDDWBindingsCore.Platform.tests_waitForEvent_calledFromC,
        callbackExcept736);
    registerCallback(thisCpp, callback736, 736);
    const callbackExcept737 = 0;
    final callback737 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        KDDWBindingsCore.Platform.tests_waitForEvent_2_calledFromC,
        callbackExcept737);
    registerCallback(thisCpp, callback737, 737);
    const callbackExcept738 = 0;
    final callback738 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.tests_waitForResize_calledFromC,
            callbackExcept738);
    registerCallback(thisCpp, callback738, 738);
    const callbackExcept739 = 0;
    final callback739 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            KDDWBindingsCore.Platform.tests_waitForResize_2_calledFromC,
            callbackExcept739);
    registerCallback(thisCpp, callback739, 739);
    final callback740 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback740, 740);
    final callback741 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback741, 741);
    const callbackExcept742 = 0;
    final callback742 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.Platform.usesFallbackMouseGrabber_calledFromC,
        callbackExcept742);
    registerCallback(thisCpp, callback742, 742);
  }
}
