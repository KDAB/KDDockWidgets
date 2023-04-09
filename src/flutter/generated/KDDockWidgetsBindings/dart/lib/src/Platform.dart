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
final _finalizer =
    _dylib.lookup<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>(
        'c_KDDockWidgets__Platform_Finalizer');

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
            'c_KDDockWidgets__Platform___get_m_numWarningsEmitted')
        .asFunction();
    return func(thisCpp);
  }

  set m_numWarningsEmitted(int m_numWarningsEmitted_) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Platform___set_m_numWarningsEmitted_int')
        .asFunction();
    func(thisCpp, m_numWarningsEmitted_);
  } //Platform()

  Platform() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_KDDockWidgets__Platform__constructor')
        .asFunction();
    thisCpp = func();
    Platform.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  } // applicationName() const
  QString applicationName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(715))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> applicationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::applicationName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.applicationName();
    return result.thisCpp;
  } // createDefaultViewFactory()

  ViewFactory createDefaultViewFactory() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(716))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return ViewFactory.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createDefaultViewFactory_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createDefaultViewFactory()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createDefaultViewFactory();
    return result.thisCpp;
  } // createMainWindow(const QString & uniqueName, KDDockWidgets::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags arg__5) const

  MainWindow createMainWindow(String? uniqueName, CreateViewOptions arg__2,
      {int options =
          KDDockWidgets_MainWindowOption.MainWindowOption_HasCentralFrame,
      required View? parent,
      int arg__5 = 0}) {
    final voidstar_Func_voidstar_voidstar_voidstar_int_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(717))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        uniqueName?.toNativeUtf8() ?? ffi.nullptr,
        arg__2 == null ? ffi.nullptr : arg__2.thisCpp,
        options,
        parent == null ? ffi.nullptr : parent.thisCpp,
        arg__5);
    return MainWindow.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createMainWindow_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? uniqueName,
      ffi.Pointer<void> arg__2,
      int options,
      ffi.Pointer<void>? parent,
      int arg__5) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createMainWindow(const QString & uniqueName, KDDockWidgets::CreateViewOptions arg__2, QFlags<KDDockWidgets::MainWindowOption> options, KDDockWidgets::Core::View * parent, Qt::WindowFlags arg__5) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createMainWindow(
        QString.fromCppPointer(uniqueName).toDartString(),
        CreateViewOptions.fromCppPointer(arg__2),
        options: options,
        parent: View.fromCppPointer(parent),
        arg__5: arg__5);
    return result.thisCpp;
  } // createView(Core::Controller * arg__1, KDDockWidgets::Core::View * parent) const

  View createView(Controller? arg__1, {required View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(718))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> createView_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, ffi.Pointer<void>? parent) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::createView(Core::Controller * arg__1, KDDockWidgets::Core::View * parent) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.createView(Controller.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  } // cursorPos() const

  QPoint cursorPos() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(719))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QPoint.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> cursorPos_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(720))
        .asFunction();
    func(thisCpp);
  }

  static void dumpManagedBacktrace_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(722))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int hasActivePopup_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(723))
        .asFunction();
    return func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp) !=
        0;
  }

  static int inDisallowedDragView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPos) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(724))
        .asFunction();
    func(thisCpp);
  }

  static void installMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::installMessageHandler()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.installMessageHandler();
  }

  static // instance()
      Platform instance() {
    final voidstar_Func_void func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_void_FFI>>(
            'c_static_KDDockWidgets__Platform__instance')
        .asFunction();
    ffi.Pointer<void> result = func();
    return Platform.fromCppPointer(result, false);
  } // isLeftMouseButtonPressed() const

  bool isLeftMouseButtonPressed() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(726))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isLeftMouseButtonPressed_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(727))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isProcessingAppQuitEvent_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            'c_KDDockWidgets__Platform__isQt')
        .asFunction();
    return func(thisCpp) != 0;
  } // isQtQuick() const

  bool isQtQuick() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform__isQtQuick')
        .asFunction();
    return func(thisCpp) != 0;
  } // isQtWidgets() const

  bool isQtWidgets() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Platform__isQtWidgets')
        .asFunction();
    return func(thisCpp) != 0;
  } // name() const

  String name() {
    final string_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<string_Func_voidstar_FFI>>(
            cFunctionSymbolName(731))
        .asFunction();
    ffi.Pointer<Utf8> result = func(thisCpp);
    return result.toDartString();
  }

  static ffi.Pointer<Utf8> name_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::name() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.name();
    return result.toNativeUtf8();
  } // onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)

  onFloatingWindowCreated(FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(732))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onFloatingWindowCreated_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onFloatingWindowCreated(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onFloatingWindowCreated(FloatingWindow.fromCppPointer(arg__1));
  } // onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)

  onFloatingWindowDestroyed(FloatingWindow? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(733))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void onFloatingWindowDestroyed_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::onFloatingWindowDestroyed(KDDockWidgets::Core::FloatingWindow * arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance
        .onFloatingWindowDestroyed(FloatingWindow.fromCppPointer(arg__1));
  } // organizationName() const

  QString organizationName() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(734))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> organizationName_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(735))
        .asFunction();
    func(thisCpp);
  }

  static void restoreMouseCursor_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::restoreMouseCursor()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.restoreMouseCursor();
  } // screenNumberFor(KDDockWidgets::Core::View * arg__1) const

  int screenNumberFor(View? arg__1) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(736))
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static int screenNumberFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::screenNumberFor(KDDockWidgets::Core::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenNumberFor(View.fromCppPointer(arg__1));
    return result;
  } // screenSizeFor(KDDockWidgets::Core::View * arg__1) const

  QSize screenSizeFor(View? arg__1) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(737))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
    return QSize.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> screenSizeFor_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::screenSizeFor(KDDockWidgets::Core::View * arg__1) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.screenSizeFor(View.fromCppPointer(arg__1));
    return result.thisCpp;
  } // setCursorPos(QPoint arg__1)

  setCursorPos(QPoint arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(738))
        .asFunction();
    func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp);
  }

  static void setCursorPos_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(739))
        .asFunction();
    func(thisCpp, arg__1);
  }

  static void setMouseCursor_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            'c_KDDockWidgets__Platform__startDragDistance')
        .asFunction();
    return func(thisCpp);
  } // startDragDistance_impl() const

  int startDragDistance_impl() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(741))
        .asFunction();
    return func(thisCpp);
  }

  static int startDragDistance_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::startDragDistance_impl() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.startDragDistance_impl();
    return result;
  } // tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)

  View tests_createFocusableView(CreateViewOptions arg__1,
      {required View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(742))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> tests_createFocusableView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_createFocusableView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createFocusableView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  } // tests_createNonClosableView(KDDockWidgets::Core::View * parent)

  View tests_createNonClosableView({required View? parent}) {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(743))
        .asFunction();
    ffi.Pointer<void> result =
        func(thisCpp, parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> tests_createNonClosableView_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_createNonClosableView(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createNonClosableView(
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  } // tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)

  View tests_createView(CreateViewOptions arg__1, {required View? parent}) {
    final voidstar_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(744))
        .asFunction();
    ffi.Pointer<void> result = func(
        thisCpp,
        arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    return View.fromCppPointer(result, false);
  }

  static ffi.Pointer<void> tests_createView_calledFromC(
      ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> arg__1,
      ffi.Pointer<void>? parent) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_createView(KDDockWidgets::CreateViewOptions arg__1, KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_createView(
        CreateViewOptions.fromCppPointer(arg__1),
        parent: View.fromCppPointer(parent));
    return result.thisCpp;
  }

  static // tests_deinitPlatform()
      tests_deinitPlatform() {
    final void_Func_void func = _dylib
        .lookup<ffi.NativeFunction<void_Func_void_FFI>>(
            'c_static_KDDockWidgets__Platform__tests_deinitPlatform')
        .asFunction();
    func();
  } // tests_deinitPlatform_impl()

  tests_deinitPlatform_impl() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(746))
        .asFunction();
    func(thisCpp);
  }

  static void tests_deinitPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_deinitPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_deinitPlatform_impl();
  } // tests_doubleClickOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)

  tests_doubleClickOn(QPoint globalPos, View? receiver) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(747))
        .asFunction();
    func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp,
        receiver == null ? ffi.nullptr : receiver.thisCpp);
  }

  static void tests_doubleClickOn_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void> globalPos, ffi.Pointer<void>? receiver) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_doubleClickOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_doubleClickOn(
        QPoint.fromCppPointer(globalPos), View.fromCppPointer(receiver));
  } // tests_initPlatform_impl()

  tests_initPlatform_impl() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(749))
        .asFunction();
    func(thisCpp);
  }

  static void tests_initPlatform_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_initPlatform_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_initPlatform_impl();
  } // tests_pressOn(QPoint globalPos, KDDockWidgets::Core::View * receiver)

  tests_pressOn(QPoint globalPos, View? receiver) {
    final void_Func_voidstar_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Platform__tests_pressOn_QPoint_View')
        .asFunction();
    func(thisCpp, globalPos == null ? ffi.nullptr : globalPos.thisCpp,
        receiver == null ? ffi.nullptr : receiver.thisCpp);
  } // tests_wait(int ms)

  tests_wait(int ms) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(751))
        .asFunction();
    func(thisCpp, ms);
  }

  static void tests_wait_calledFromC(ffi.Pointer<void> thisCpp, int ms) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_wait(int ms)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.tests_wait(ms);
  } // tests_waitForDeleted(KDDockWidgets::Core::View * arg__1, int timeout) const

  bool tests_waitForDeleted(View? arg__1, {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(752))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForDeleted_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForDeleted(KDDockWidgets::Core::View * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance
        .tests_waitForDeleted(View.fromCppPointer(arg__1), timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForDeleted(QObject * arg__1, int timeout) const

  bool tests_waitForDeleted_2(QObject? arg__1, {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(753))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForDeleted_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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

  bool tests_waitForEvent(View? arg__1, int type, {int timeout = 5000}) {
    final bool_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(754))
        .asFunction();
    return func(thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, type,
            timeout) !=
        0;
  }

  static int tests_waitForEvent_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? arg__1, int type, int timeout) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForEvent(KDDockWidgets::Core::View * arg__1, Event::Type type, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForEvent(
        View.fromCppPointer(arg__1), type,
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForEvent(QObject * w, Event::Type type, int timeout) const

  bool tests_waitForEvent_2(QObject? w, int type, {int timeout = 5000}) {
    final bool_Func_voidstar_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(755))
        .asFunction();
    return func(thisCpp, w == null ? ffi.nullptr : w.thisCpp, type, timeout) !=
        0;
  }

  static int tests_waitForEvent_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? w, int type, int timeout) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForEvent(QObject * w, Event::Type type, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForEvent_2(
        QObject.fromCppPointer(w), type,
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForResize(Core::Controller * arg__1, int timeout) const

  bool tests_waitForResize(Controller? arg__1, {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(756))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForResize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForResize(Core::Controller * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tests_waitForResize(
        Controller.fromCppPointer(arg__1),
        timeout: timeout);
    return result ? 1 : 0;
  } // tests_waitForResize(KDDockWidgets::Core::View * arg__1, int timeout) const

  bool tests_waitForResize_2(View? arg__1, {int timeout = 2000}) {
    final bool_Func_voidstar_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(757))
        .asFunction();
    return func(
            thisCpp, arg__1 == null ? ffi.nullptr : arg__1.thisCpp, timeout) !=
        0;
  }

  static int tests_waitForResize_2_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1, int timeout) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
    if (dartInstance == null) {
      print(
          "Dart instance not found for Platform::tests_waitForResize(KDDockWidgets::Core::View * arg__1, int timeout) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance
        .tests_waitForResize_2(View.fromCppPointer(arg__1), timeout: timeout);
    return result ? 1 : 0;
  } // ungrabMouse()

  ungrabMouse() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(758))
        .asFunction();
    func(thisCpp);
  }

  static void ungrabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(759))
        .asFunction();
    func(thisCpp);
  }

  static void uninstallMessageHandler_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            cFunctionSymbolName(760))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int usesFallbackMouseGrabber_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = Platform.s_dartInstanceByCppPtr[thisCpp.address];
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
            'c_KDDockWidgets__Platform__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 715:
        return "c_KDDockWidgets__Platform__applicationName";
      case 716:
        return "c_KDDockWidgets__Platform__createDefaultViewFactory";
      case 717:
        return "c_KDDockWidgets__Platform__createMainWindow_QString_CreateViewOptions_MainWindowOptions_View_WindowFlags";
      case 718:
        return "c_KDDockWidgets__Platform__createView_Controller_View";
      case 719:
        return "c_KDDockWidgets__Platform__cursorPos";
      case 720:
        return "c_KDDockWidgets__Platform__dumpManagedBacktrace";
      case 722:
        return "c_KDDockWidgets__Platform__hasActivePopup";
      case 723:
        return "c_KDDockWidgets__Platform__inDisallowedDragView_QPoint";
      case 724:
        return "c_KDDockWidgets__Platform__installMessageHandler";
      case 726:
        return "c_KDDockWidgets__Platform__isLeftMouseButtonPressed";
      case 727:
        return "c_KDDockWidgets__Platform__isProcessingAppQuitEvent";
      case 731:
        return "c_KDDockWidgets__Platform__name";
      case 732:
        return "c_KDDockWidgets__Platform__onFloatingWindowCreated_FloatingWindow";
      case 733:
        return "c_KDDockWidgets__Platform__onFloatingWindowDestroyed_FloatingWindow";
      case 734:
        return "c_KDDockWidgets__Platform__organizationName";
      case 735:
        return "c_KDDockWidgets__Platform__restoreMouseCursor";
      case 736:
        return "c_KDDockWidgets__Platform__screenNumberFor_View";
      case 737:
        return "c_KDDockWidgets__Platform__screenSizeFor_View";
      case 738:
        return "c_KDDockWidgets__Platform__setCursorPos_QPoint";
      case 739:
        return "c_KDDockWidgets__Platform__setMouseCursor_CursorShape";
      case 741:
        return "c_KDDockWidgets__Platform__startDragDistance_impl";
      case 742:
        return "c_KDDockWidgets__Platform__tests_createFocusableView_CreateViewOptions_View";
      case 743:
        return "c_KDDockWidgets__Platform__tests_createNonClosableView_View";
      case 744:
        return "c_KDDockWidgets__Platform__tests_createView_CreateViewOptions_View";
      case 746:
        return "c_KDDockWidgets__Platform__tests_deinitPlatform_impl";
      case 747:
        return "c_KDDockWidgets__Platform__tests_doubleClickOn_QPoint_View";
      case 749:
        return "c_KDDockWidgets__Platform__tests_initPlatform_impl";
      case 751:
        return "c_KDDockWidgets__Platform__tests_wait_int";
      case 752:
        return "c_KDDockWidgets__Platform__tests_waitForDeleted_View_int";
      case 753:
        return "c_KDDockWidgets__Platform__tests_waitForDeleted_QObject_int";
      case 754:
        return "c_KDDockWidgets__Platform__tests_waitForEvent_View_Type_int";
      case 755:
        return "c_KDDockWidgets__Platform__tests_waitForEvent_QObject_Type_int";
      case 756:
        return "c_KDDockWidgets__Platform__tests_waitForResize_Controller_int";
      case 757:
        return "c_KDDockWidgets__Platform__tests_waitForResize_View_int";
      case 758:
        return "c_KDDockWidgets__Platform__ungrabMouse";
      case 759:
        return "c_KDDockWidgets__Platform__uninstallMessageHandler";
      case 760:
        return "c_KDDockWidgets__Platform__usesFallbackMouseGrabber";
    }
    return "";
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 715:
        return "applicationName";
      case 716:
        return "createDefaultViewFactory";
      case 717:
        return "createMainWindow";
      case 718:
        return "createView";
      case 719:
        return "cursorPos";
      case 720:
        return "dumpManagedBacktrace";
      case 722:
        return "hasActivePopup";
      case 723:
        return "inDisallowedDragView";
      case 724:
        return "installMessageHandler";
      case 726:
        return "isLeftMouseButtonPressed";
      case 727:
        return "isProcessingAppQuitEvent";
      case 731:
        return "name";
      case 732:
        return "onFloatingWindowCreated";
      case 733:
        return "onFloatingWindowDestroyed";
      case 734:
        return "organizationName";
      case 735:
        return "restoreMouseCursor";
      case 736:
        return "screenNumberFor";
      case 737:
        return "screenSizeFor";
      case 738:
        return "setCursorPos";
      case 739:
        return "setMouseCursor";
      case 741:
        return "startDragDistance_impl";
      case 742:
        return "tests_createFocusableView";
      case 743:
        return "tests_createNonClosableView";
      case 744:
        return "tests_createView";
      case 746:
        return "tests_deinitPlatform_impl";
      case 747:
        return "tests_doubleClickOn";
      case 749:
        return "tests_initPlatform_impl";
      case 751:
        return "tests_wait";
      case 752:
        return "tests_waitForDeleted";
      case 753:
        return "tests_waitForDeleted_2";
      case 754:
        return "tests_waitForEvent";
      case 755:
        return "tests_waitForEvent_2";
      case 756:
        return "tests_waitForResize";
      case 757:
        return "tests_waitForResize_2";
      case 758:
        return "ungrabMouse";
      case 759:
        return "uninstallMessageHandler";
      case 760:
        return "usesFallbackMouseGrabber";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Platform__registerVirtualMethodCallback')
        .asFunction();
    final callback715 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.applicationName_calledFromC);
    registerCallback(thisCpp, callback715, 715);
    final callback716 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.createDefaultViewFactory_calledFromC);
    registerCallback(thisCpp, callback716, 716);
    final callback717 = ffi.Pointer.fromFunction<
            voidstar_Func_voidstar_voidstar_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>(
        Platform.createMainWindow_calledFromC);
    registerCallback(thisCpp, callback717, 717);
    final callback718 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform.createView_calledFromC);
    registerCallback(thisCpp, callback718, 718);
    final callback719 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.cursorPos_calledFromC);
    registerCallback(thisCpp, callback719, 719);
    final callback720 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.dumpManagedBacktrace_calledFromC);
    registerCallback(thisCpp, callback720, 720);
    const callbackExcept722 = 0;
    final callback722 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.hasActivePopup_calledFromC, callbackExcept722);
    registerCallback(thisCpp, callback722, 722);
    const callbackExcept723 = 0;
    final callback723 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Platform.inDisallowedDragView_calledFromC, callbackExcept723);
    registerCallback(thisCpp, callback723, 723);
    final callback724 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.installMessageHandler_calledFromC);
    registerCallback(thisCpp, callback724, 724);
    const callbackExcept726 = 0;
    final callback726 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.isLeftMouseButtonPressed_calledFromC, callbackExcept726);
    registerCallback(thisCpp, callback726, 726);
    const callbackExcept727 = 0;
    final callback727 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.isProcessingAppQuitEvent_calledFromC, callbackExcept727);
    registerCallback(thisCpp, callback727, 727);
    final callback731 = ffi.Pointer.fromFunction<string_Func_voidstar_FFI>(
        Platform.name_calledFromC);
    registerCallback(thisCpp, callback731, 731);
    final callback732 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Platform.onFloatingWindowCreated_calledFromC);
    registerCallback(thisCpp, callback732, 732);
    final callback733 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Platform.onFloatingWindowDestroyed_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    final callback734 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        Platform.organizationName_calledFromC);
    registerCallback(thisCpp, callback734, 734);
    final callback735 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.restoreMouseCursor_calledFromC);
    registerCallback(thisCpp, callback735, 735);
    const callbackExcept736 = 0;
    final callback736 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            Platform.screenNumberFor_calledFromC, callbackExcept736);
    registerCallback(thisCpp, callback736, 736);
    final callback737 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform.screenSizeFor_calledFromC);
    registerCallback(thisCpp, callback737, 737);
    final callback738 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            Platform.setCursorPos_calledFromC);
    registerCallback(thisCpp, callback738, 738);
    final callback739 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform.setMouseCursor_calledFromC);
    registerCallback(thisCpp, callback739, 739);
    const callbackExcept741 = 0;
    final callback741 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Platform.startDragDistance_impl_calledFromC, callbackExcept741);
    registerCallback(thisCpp, callback741, 741);
    final callback742 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform.tests_createFocusableView_calledFromC);
    registerCallback(thisCpp, callback742, 742);
    final callback743 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            Platform.tests_createNonClosableView_calledFromC);
    registerCallback(thisCpp, callback743, 743);
    final callback744 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            Platform.tests_createView_calledFromC);
    registerCallback(thisCpp, callback744, 744);
    final callback746 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.tests_deinitPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback746, 746);
    final callback747 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_voidstar_FFI>(
            Platform.tests_doubleClickOn_calledFromC);
    registerCallback(thisCpp, callback747, 747);
    final callback749 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.tests_initPlatform_impl_calledFromC);
    registerCallback(thisCpp, callback749, 749);
    final callback751 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Platform.tests_wait_calledFromC);
    registerCallback(thisCpp, callback751, 751);
    const callbackExcept752 = 0;
    final callback752 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform.tests_waitForDeleted_calledFromC, callbackExcept752);
    registerCallback(thisCpp, callback752, 752);
    const callbackExcept753 = 0;
    final callback753 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform.tests_waitForDeleted_2_calledFromC, callbackExcept753);
    registerCallback(thisCpp, callback753, 753);
    const callbackExcept754 = 0;
    final callback754 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform.tests_waitForEvent_calledFromC, callbackExcept754);
    registerCallback(thisCpp, callback754, 754);
    const callbackExcept755 = 0;
    final callback755 = ffi.Pointer.fromFunction<
            bool_Func_voidstar_voidstar_ffi_Int32_ffi_Int32_FFI>(
        Platform.tests_waitForEvent_2_calledFromC, callbackExcept755);
    registerCallback(thisCpp, callback755, 755);
    const callbackExcept756 = 0;
    final callback756 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform.tests_waitForResize_calledFromC, callbackExcept756);
    registerCallback(thisCpp, callback756, 756);
    const callbackExcept757 = 0;
    final callback757 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_ffi_Int32_FFI>(
            Platform.tests_waitForResize_2_calledFromC, callbackExcept757);
    registerCallback(thisCpp, callback757, 757);
    final callback758 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.ungrabMouse_calledFromC);
    registerCallback(thisCpp, callback758, 758);
    final callback759 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Platform.uninstallMessageHandler_calledFromC);
    registerCallback(thisCpp, callback759, 759);
    const callbackExcept760 = 0;
    final callback760 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        Platform.usesFallbackMouseGrabber_calledFromC, callbackExcept760);
    registerCallback(thisCpp, callback760, 760);
  }
}
