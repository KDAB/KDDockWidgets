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

class TitleBar extends KDDWBindingsFlutter.View {
  TitleBar.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TitleBar.init() : super.init() {}
  factory TitleBar.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TitleBar;
    }
    return TitleBar.fromCppPointer(cppPointer, needsAutoDelete);
  } //TitleBar(KDDockWidgets::Core::TitleBar * controller, KDDockWidgets::Core::View * parent)
  TitleBar(KDDWBindingsCore.TitleBar? controller,
      {required KDDWBindingsCore.View? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__TitleBar__constructor_TitleBar_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  } // isCloseButtonEnabled() const

  bool isCloseButtonEnabled() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(966))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isCloseButtonEnabled_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isCloseButtonEnabled() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isCloseButtonEnabled();
    return result ? 1 : 0;
  } // isCloseButtonVisible() const

  bool isCloseButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(967))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isCloseButtonVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isCloseButtonVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isCloseButtonVisible();
    return result ? 1 : 0;
  }

  static int isExplicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isExplicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExplicitlyHidden();
    return result ? 1 : 0;
  } // isFloatButtonVisible() const

  bool isFloatButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(968))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isFloatButtonVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isFloatButtonVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isFloatButtonVisible();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isMounted_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isMounted() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMounted();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
        QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildVisibilityChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildVisibilityChanged(
        (childView == null || childView.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onGeometryChanged_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onGeometryChanged()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onGeometryChanged();
  }

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
    return result ? 1 : 0;
  } // onTitleBarChanged(const QString & arg__1)

  onTitleBarChanged(String? arg__1) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(971))
        .asFunction();
    func(thisCpp, arg__1?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void onTitleBarChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? arg__1) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::onTitleBarChanged(const QString & arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance
        .onTitleBarChanged(QString.fromCppPointer(arg__1).toDartString());
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void raiseChild_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::raiseChild(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseChild((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void raiseWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? rootView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::raiseWindow(KDDockWidgets::Core::View * rootView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseWindow((rootView == null || rootView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(rootView));
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setViewName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setViewName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setViewName(QString.fromCppPointer(name).toDartString());
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  static ffi.Pointer<void> viewName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar::viewName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.viewName();
    return result.thisCpp;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__TitleBar__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 840:
        return "c_KDDockWidgets__flutter__TitleBar__activateWindow";
      case 850:
        return "c_KDDockWidgets__flutter__TitleBar__close";
      case 852:
        return "c_KDDockWidgets__flutter__TitleBar__createPlatformWindow";
      case 858:
        return "c_KDDockWidgets__flutter__TitleBar__flags";
      case 859:
        return "c_KDDockWidgets__flutter__TitleBar__geometry";
      case 860:
        return "c_KDDockWidgets__flutter__TitleBar__grabMouse";
      case 863:
        return "c_KDDockWidgets__flutter__TitleBar__hasFocus";
      case 865:
        return "c_KDDockWidgets__flutter__TitleBar__hide";
      case 867:
        return "c_KDDockWidgets__flutter__TitleBar__init";
      case 869:
        return "c_KDDockWidgets__flutter__TitleBar__isActiveWindow";
      case 966:
        return "c_KDDockWidgets__flutter__TitleBar__isCloseButtonEnabled";
      case 967:
        return "c_KDDockWidgets__flutter__TitleBar__isCloseButtonVisible";
      case 870:
        return "c_KDDockWidgets__flutter__TitleBar__isExplicitlyHidden";
      case 968:
        return "c_KDDockWidgets__flutter__TitleBar__isFloatButtonVisible";
      case 871:
        return "c_KDDockWidgets__flutter__TitleBar__isMaximized";
      case 872:
        return "c_KDDockWidgets__flutter__TitleBar__isMinimized";
      case 942:
        return "c_KDDockWidgets__flutter__TitleBar__isMounted";
      case 873:
        return "c_KDDockWidgets__flutter__TitleBar__isNull";
      case 874:
        return "c_KDDockWidgets__flutter__TitleBar__isRootView";
      case 875:
        return "c_KDDockWidgets__flutter__TitleBar__isVisible";
      case 876:
        return "c_KDDockWidgets__flutter__TitleBar__mapFromGlobal_QPoint";
      case 877:
        return "c_KDDockWidgets__flutter__TitleBar__mapTo_View_QPoint";
      case 878:
        return "c_KDDockWidgets__flutter__TitleBar__mapToGlobal_QPoint";
      case 879:
        return "c_KDDockWidgets__flutter__TitleBar__maxSizeHint";
      case 880:
        return "c_KDDockWidgets__flutter__TitleBar__minSize";
      case 884:
        return "c_KDDockWidgets__flutter__TitleBar__move_int_int";
      case 885:
        return "c_KDDockWidgets__flutter__TitleBar__normalGeometry";
      case 945:
        return "c_KDDockWidgets__flutter__TitleBar__onChildAdded_View";
      case 946:
        return "c_KDDockWidgets__flutter__TitleBar__onChildRemoved_View";
      case 947:
        return "c_KDDockWidgets__flutter__TitleBar__onChildVisibilityChanged_View";
      case 949:
        return "c_KDDockWidgets__flutter__TitleBar__onGeometryChanged";
      case 951:
        return "c_KDDockWidgets__flutter__TitleBar__onRebuildRequested";
      case 887:
        return "c_KDDockWidgets__flutter__TitleBar__onResize_int_int";
      case 971:
        return "c_KDDockWidgets__flutter__TitleBar__onTitleBarChanged_QString";
      case 889:
        return "c_KDDockWidgets__flutter__TitleBar__raise";
      case 890:
        return "c_KDDockWidgets__flutter__TitleBar__raiseAndActivate";
      case 954:
        return "c_KDDockWidgets__flutter__TitleBar__raiseChild_View";
      case 955:
        return "c_KDDockWidgets__flutter__TitleBar__raiseWindow_View";
      case 892:
        return "c_KDDockWidgets__flutter__TitleBar__releaseKeyboard";
      case 893:
        return "c_KDDockWidgets__flutter__TitleBar__releaseMouse";
      case 896:
        return "c_KDDockWidgets__flutter__TitleBar__setCursor_CursorShape";
      case 897:
        return "c_KDDockWidgets__flutter__TitleBar__setFixedHeight_int";
      case 898:
        return "c_KDDockWidgets__flutter__TitleBar__setFixedWidth_int";
      case 899:
        return "c_KDDockWidgets__flutter__TitleBar__setGeometry_QRect";
      case 900:
        return "c_KDDockWidgets__flutter__TitleBar__setHeight_int";
      case 901:
        return "c_KDDockWidgets__flutter__TitleBar__setMaximumSize_QSize";
      case 902:
        return "c_KDDockWidgets__flutter__TitleBar__setMinimumSize_QSize";
      case 903:
        return "c_KDDockWidgets__flutter__TitleBar__setMouseTracking_bool";
      case 904:
        return "c_KDDockWidgets__flutter__TitleBar__setParent_View";
      case 906:
        return "c_KDDockWidgets__flutter__TitleBar__setSize_int_int";
      case 907:
        return "c_KDDockWidgets__flutter__TitleBar__setViewName_QString";
      case 908:
        return "c_KDDockWidgets__flutter__TitleBar__setVisible_bool";
      case 909:
        return "c_KDDockWidgets__flutter__TitleBar__setWidth_int";
      case 910:
        return "c_KDDockWidgets__flutter__TitleBar__setWindowOpacity_double";
      case 911:
        return "c_KDDockWidgets__flutter__TitleBar__setWindowTitle_QString";
      case 912:
        return "c_KDDockWidgets__flutter__TitleBar__setZOrder_int";
      case 913:
        return "c_KDDockWidgets__flutter__TitleBar__show";
      case 914:
        return "c_KDDockWidgets__flutter__TitleBar__showMaximized";
      case 915:
        return "c_KDDockWidgets__flutter__TitleBar__showMinimized";
      case 916:
        return "c_KDDockWidgets__flutter__TitleBar__showNormal";
      case 918:
        return "c_KDDockWidgets__flutter__TitleBar__update";
      case 919:
        return "c_KDDockWidgets__flutter__TitleBar__viewName";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 840:
        return "activateWindow";
      case 850:
        return "close";
      case 852:
        return "createPlatformWindow";
      case 858:
        return "flags";
      case 859:
        return "geometry";
      case 860:
        return "grabMouse";
      case 863:
        return "hasFocus";
      case 865:
        return "hide";
      case 867:
        return "init";
      case 869:
        return "isActiveWindow";
      case 966:
        return "isCloseButtonEnabled";
      case 967:
        return "isCloseButtonVisible";
      case 870:
        return "isExplicitlyHidden";
      case 968:
        return "isFloatButtonVisible";
      case 871:
        return "isMaximized";
      case 872:
        return "isMinimized";
      case 942:
        return "isMounted";
      case 873:
        return "isNull";
      case 874:
        return "isRootView";
      case 875:
        return "isVisible";
      case 876:
        return "mapFromGlobal";
      case 877:
        return "mapTo";
      case 878:
        return "mapToGlobal";
      case 879:
        return "maxSizeHint";
      case 880:
        return "minSize";
      case 884:
        return "move_2";
      case 885:
        return "normalGeometry";
      case 945:
        return "onChildAdded";
      case 946:
        return "onChildRemoved";
      case 947:
        return "onChildVisibilityChanged";
      case 949:
        return "onGeometryChanged";
      case 951:
        return "onRebuildRequested";
      case 887:
        return "onResize_2";
      case 971:
        return "onTitleBarChanged";
      case 889:
        return "raise";
      case 890:
        return "raiseAndActivate";
      case 954:
        return "raiseChild";
      case 955:
        return "raiseWindow";
      case 892:
        return "releaseKeyboard";
      case 893:
        return "releaseMouse";
      case 896:
        return "setCursor";
      case 897:
        return "setFixedHeight";
      case 898:
        return "setFixedWidth";
      case 899:
        return "setGeometry";
      case 900:
        return "setHeight";
      case 901:
        return "setMaximumSize";
      case 902:
        return "setMinimumSize";
      case 903:
        return "setMouseTracking";
      case 904:
        return "setParent";
      case 906:
        return "setSize_2";
      case 907:
        return "setViewName";
      case 908:
        return "setVisible";
      case 909:
        return "setWidth";
      case 910:
        return "setWindowOpacity";
      case 911:
        return "setWindowTitle";
      case 912:
        return "setZOrder";
      case 913:
        return "show";
      case 914:
        return "showMaximized";
      case 915:
        return "showMinimized";
      case 916:
        return "showNormal";
      case 918:
        return "update";
      case 919:
        return "viewName";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__TitleBar__registerVirtualMethodCallback')
        .asFunction();
    final callback840 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback840, 840);
    const callbackExcept850 = 0;
    final callback850 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept850);
    registerCallback(thisCpp, callback850, 850);
    final callback852 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback852, 852);
    const callbackExcept858 = 0;
    final callback858 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept858);
    registerCallback(thisCpp, callback858, 858);
    final callback859 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback859, 859);
    final callback860 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback860, 860);
    const callbackExcept863 = 0;
    final callback863 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept863);
    registerCallback(thisCpp, callback863, 863);
    final callback865 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback865, 865);
    final callback867 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TitleBar.init_calledFromC);
    registerCallback(thisCpp, callback867, 867);
    const callbackExcept869 = 0;
    final callback869 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept869);
    registerCallback(thisCpp, callback869, 869);
    const callbackExcept966 = 0;
    final callback966 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TitleBar.isCloseButtonEnabled_calledFromC,
        callbackExcept966);
    registerCallback(thisCpp, callback966, 966);
    const callbackExcept967 = 0;
    final callback967 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TitleBar.isCloseButtonVisible_calledFromC,
        callbackExcept967);
    registerCallback(thisCpp, callback967, 967);
    const callbackExcept870 = 0;
    final callback870 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept870);
    registerCallback(thisCpp, callback870, 870);
    const callbackExcept968 = 0;
    final callback968 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TitleBar.isFloatButtonVisible_calledFromC,
        callbackExcept968);
    registerCallback(thisCpp, callback968, 968);
    const callbackExcept871 = 0;
    final callback871 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept871);
    registerCallback(thisCpp, callback871, 871);
    const callbackExcept872 = 0;
    final callback872 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept872);
    registerCallback(thisCpp, callback872, 872);
    const callbackExcept942 = 0;
    final callback942 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMounted_calledFromC, callbackExcept942);
    registerCallback(thisCpp, callback942, 942);
    const callbackExcept873 = 0;
    final callback873 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept873);
    registerCallback(thisCpp, callback873, 873);
    const callbackExcept874 = 0;
    final callback874 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept874);
    registerCallback(thisCpp, callback874, 874);
    const callbackExcept875 = 0;
    final callback875 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept875);
    registerCallback(thisCpp, callback875, 875);
    final callback876 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback876, 876);
    final callback877 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback877, 877);
    final callback878 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback878, 878);
    final callback879 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback879, 879);
    final callback880 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback880, 880);
    final callback884 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback884, 884);
    final callback885 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback885, 885);
    final callback945 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback945, 945);
    final callback946 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback947 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback947, 947);
    final callback949 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback949, 949);
    final callback951 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback951, 951);
    const callbackExcept887 = 0;
    final callback887 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept887);
    registerCallback(thisCpp, callback887, 887);
    final callback971 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.TitleBar.onTitleBarChanged_calledFromC);
    registerCallback(thisCpp, callback971, 971);
    final callback889 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback889, 889);
    final callback890 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback890, 890);
    final callback954 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseChild_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback955 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseWindow_calledFromC);
    registerCallback(thisCpp, callback955, 955);
    final callback892 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback892, 892);
    final callback893 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback893, 893);
    final callback896 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback896, 896);
    final callback897 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback897, 897);
    final callback898 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback898, 898);
    final callback899 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback899, 899);
    final callback900 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    final callback901 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback901, 901);
    final callback902 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback902, 902);
    final callback903 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback903, 903);
    final callback904 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback904, 904);
    final callback906 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback906, 906);
    final callback907 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback908 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback908, 908);
    final callback909 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback910 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback911 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    final callback912 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    final callback913 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback913, 913);
    final callback914 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback914, 914);
    final callback915 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback915, 915);
    final callback916 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback918 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback918, 918);
    final callback919 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.viewName_calledFromC);
    registerCallback(thisCpp, callback919, 919);
  }
}
