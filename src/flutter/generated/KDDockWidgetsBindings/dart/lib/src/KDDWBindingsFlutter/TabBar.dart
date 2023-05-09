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

class TabBar extends KDDWBindingsFlutter.View {
  TabBar.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TabBar.init() : super.init() {}
  factory TabBar.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TabBar;
    }
    return TabBar.fromCppPointer(cppPointer, needsAutoDelete);
  } //TabBar(KDDockWidgets::Core::TabBar * controller, KDDockWidgets::Core::View * parent)
  TabBar(KDDWBindingsCore.TabBar? controller,
      {required KDDWBindingsCore.View? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__TabBar__constructor_TabBar_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print("Dart instance not found for TabBar::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print("Dart instance not found for TabBar::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isExpicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isExpicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExpicitlyHidden();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
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
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  } // moveTabTo(int from, int to)

  moveTabTo(int from, int to) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(1060))
        .asFunction();
    func(thisCpp, from, to);
  }

  static void moveTabTo_calledFromC(
      ffi.Pointer<void> thisCpp, int from, int to) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::moveTabTo(int from, int to)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.moveTabTo(from, to);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildVisibilityChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildVisibilityChanged(
        (childView == null || childView.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(childView));
  } // onRebuildRequested()

  onRebuildRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1061))
        .asFunction();
    func(thisCpp);
  }

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onResize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(w, h);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  } // rectForTab(int index) const

  QRect rectForTab(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1062))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> rectForTab_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::rectForTab(int index) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.rectForTab(index);
    return result.thisCpp;
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  } // removeDockWidget(KDDockWidgets::Core::DockWidget * dw)

  removeDockWidget(KDDWBindingsCore.DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1063))
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  }

  static void removeDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? dw) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.removeDockWidget((dw == null || dw.address == 0)
        ? null
        : KDDWBindingsCore.DockWidget.fromCppPointer(dw));
  } // renameTab(int index, const QString & name)

  renameTab(int index, String? name) {
    final void_Func_voidstar_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            cFunctionSymbolName(1064))
        .asFunction();
    func(thisCpp, index, name?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void renameTab_calledFromC(
      ffi.Pointer<void> thisCpp, int index, ffi.Pointer<void>? name) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::renameTab(int index, const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.renameTab(index, QString.fromCppPointer(name).toDartString());
  } // setCurrentIndex(int index)

  setCurrentIndex(int index) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1065))
        .asFunction();
    func(thisCpp, index);
  }

  static void setCurrentIndex_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setCurrentIndex(int index)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCurrentIndex(index);
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print("Dart instance not found for TabBar::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  } // tabAt(QPoint localPos) const

  int tabAt(QPoint localPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1068))
        .asFunction();
    return func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp);
  }

  static int tabAt_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPos) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::tabAt(QPoint localPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tabAt(QPoint.fromCppPointer(localPos));
    return result;
  } // text(int index) const

  QString text(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(1069))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> text_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::text(int index) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.text(index);
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__TabBar__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 913:
        return "c_KDDockWidgets__flutter__TabBar__activateWindow";
      case 924:
        return "c_KDDockWidgets__flutter__TabBar__close";
      case 927:
        return "c_KDDockWidgets__flutter__TabBar__createPlatformWindow";
      case 933:
        return "c_KDDockWidgets__flutter__TabBar__flags";
      case 935:
        return "c_KDDockWidgets__flutter__TabBar__free_impl";
      case 937:
        return "c_KDDockWidgets__flutter__TabBar__geometry";
      case 939:
        return "c_KDDockWidgets__flutter__TabBar__grabMouse";
      case 942:
        return "c_KDDockWidgets__flutter__TabBar__hasFocus";
      case 944:
        return "c_KDDockWidgets__flutter__TabBar__hide";
      case 947:
        return "c_KDDockWidgets__flutter__TabBar__init";
      case 949:
        return "c_KDDockWidgets__flutter__TabBar__isActiveWindow";
      case 950:
        return "c_KDDockWidgets__flutter__TabBar__isExpicitlyHidden";
      case 951:
        return "c_KDDockWidgets__flutter__TabBar__isMaximized";
      case 952:
        return "c_KDDockWidgets__flutter__TabBar__isMinimized";
      case 953:
        return "c_KDDockWidgets__flutter__TabBar__isNull";
      case 954:
        return "c_KDDockWidgets__flutter__TabBar__isRootView";
      case 955:
        return "c_KDDockWidgets__flutter__TabBar__isVisible";
      case 956:
        return "c_KDDockWidgets__flutter__TabBar__mapFromGlobal_QPoint";
      case 957:
        return "c_KDDockWidgets__flutter__TabBar__mapTo_View_QPoint";
      case 958:
        return "c_KDDockWidgets__flutter__TabBar__mapToGlobal_QPoint";
      case 959:
        return "c_KDDockWidgets__flutter__TabBar__maxSizeHint";
      case 960:
        return "c_KDDockWidgets__flutter__TabBar__minSize";
      case 961:
        return "c_KDDockWidgets__flutter__TabBar__minimumHeight";
      case 962:
        return "c_KDDockWidgets__flutter__TabBar__minimumWidth";
      case 964:
        return "c_KDDockWidgets__flutter__TabBar__move_int_int";
      case 1060:
        return "c_KDDockWidgets__flutter__TabBar__moveTabTo_int_int";
      case 965:
        return "c_KDDockWidgets__flutter__TabBar__normalGeometry";
      case 966:
        return "c_KDDockWidgets__flutter__TabBar__objectName";
      case 1034:
        return "c_KDDockWidgets__flutter__TabBar__onChildAdded_View";
      case 1035:
        return "c_KDDockWidgets__flutter__TabBar__onChildRemoved_View";
      case 1036:
        return "c_KDDockWidgets__flutter__TabBar__onChildVisibilityChanged_View";
      case 1061:
        return "c_KDDockWidgets__flutter__TabBar__onRebuildRequested";
      case 968:
        return "c_KDDockWidgets__flutter__TabBar__onResize_int_int";
      case 971:
        return "c_KDDockWidgets__flutter__TabBar__raise";
      case 972:
        return "c_KDDockWidgets__flutter__TabBar__raiseAndActivate";
      case 1062:
        return "c_KDDockWidgets__flutter__TabBar__rectForTab_int";
      case 974:
        return "c_KDDockWidgets__flutter__TabBar__releaseKeyboard";
      case 975:
        return "c_KDDockWidgets__flutter__TabBar__releaseMouse";
      case 1063:
        return "c_KDDockWidgets__flutter__TabBar__removeDockWidget_DockWidget";
      case 1064:
        return "c_KDDockWidgets__flutter__TabBar__renameTab_int_QString";
      case 1065:
        return "c_KDDockWidgets__flutter__TabBar__setCurrentIndex_int";
      case 979:
        return "c_KDDockWidgets__flutter__TabBar__setCursor_CursorShape";
      case 980:
        return "c_KDDockWidgets__flutter__TabBar__setFixedHeight_int";
      case 981:
        return "c_KDDockWidgets__flutter__TabBar__setFixedWidth_int";
      case 982:
        return "c_KDDockWidgets__flutter__TabBar__setGeometry_QRect";
      case 983:
        return "c_KDDockWidgets__flutter__TabBar__setHeight_int";
      case 984:
        return "c_KDDockWidgets__flutter__TabBar__setMaximumSize_QSize";
      case 985:
        return "c_KDDockWidgets__flutter__TabBar__setMinimumSize_QSize";
      case 986:
        return "c_KDDockWidgets__flutter__TabBar__setMouseTracking_bool";
      case 987:
        return "c_KDDockWidgets__flutter__TabBar__setObjectName_QString";
      case 988:
        return "c_KDDockWidgets__flutter__TabBar__setParent_View";
      case 990:
        return "c_KDDockWidgets__flutter__TabBar__setSize_int_int";
      case 991:
        return "c_KDDockWidgets__flutter__TabBar__setVisible_bool";
      case 992:
        return "c_KDDockWidgets__flutter__TabBar__setWidth_int";
      case 993:
        return "c_KDDockWidgets__flutter__TabBar__setWindowOpacity_double";
      case 994:
        return "c_KDDockWidgets__flutter__TabBar__setWindowTitle_QString";
      case 995:
        return "c_KDDockWidgets__flutter__TabBar__setZOrder_int";
      case 996:
        return "c_KDDockWidgets__flutter__TabBar__show";
      case 997:
        return "c_KDDockWidgets__flutter__TabBar__showMaximized";
      case 998:
        return "c_KDDockWidgets__flutter__TabBar__showMinimized";
      case 999:
        return "c_KDDockWidgets__flutter__TabBar__showNormal";
      case 1001:
        return "c_KDDockWidgets__flutter__TabBar__sizeHint";
      case 1068:
        return "c_KDDockWidgets__flutter__TabBar__tabAt_QPoint";
      case 1069:
        return "c_KDDockWidgets__flutter__TabBar__text_int";
      case 1003:
        return "c_KDDockWidgets__flutter__TabBar__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 913:
        return "activateWindow";
      case 924:
        return "close";
      case 927:
        return "createPlatformWindow";
      case 933:
        return "flags";
      case 935:
        return "free_impl";
      case 937:
        return "geometry";
      case 939:
        return "grabMouse";
      case 942:
        return "hasFocus";
      case 944:
        return "hide";
      case 947:
        return "init";
      case 949:
        return "isActiveWindow";
      case 950:
        return "isExpicitlyHidden";
      case 951:
        return "isMaximized";
      case 952:
        return "isMinimized";
      case 953:
        return "isNull";
      case 954:
        return "isRootView";
      case 955:
        return "isVisible";
      case 956:
        return "mapFromGlobal";
      case 957:
        return "mapTo";
      case 958:
        return "mapToGlobal";
      case 959:
        return "maxSizeHint";
      case 960:
        return "minSize";
      case 961:
        return "minimumHeight";
      case 962:
        return "minimumWidth";
      case 964:
        return "move_2";
      case 1060:
        return "moveTabTo";
      case 965:
        return "normalGeometry";
      case 966:
        return "objectName";
      case 1034:
        return "onChildAdded";
      case 1035:
        return "onChildRemoved";
      case 1036:
        return "onChildVisibilityChanged";
      case 1061:
        return "onRebuildRequested";
      case 968:
        return "onResize_2";
      case 971:
        return "raise";
      case 972:
        return "raiseAndActivate";
      case 1062:
        return "rectForTab";
      case 974:
        return "releaseKeyboard";
      case 975:
        return "releaseMouse";
      case 1063:
        return "removeDockWidget";
      case 1064:
        return "renameTab";
      case 1065:
        return "setCurrentIndex";
      case 979:
        return "setCursor";
      case 980:
        return "setFixedHeight";
      case 981:
        return "setFixedWidth";
      case 982:
        return "setGeometry";
      case 983:
        return "setHeight";
      case 984:
        return "setMaximumSize";
      case 985:
        return "setMinimumSize";
      case 986:
        return "setMouseTracking";
      case 987:
        return "setObjectName";
      case 988:
        return "setParent";
      case 990:
        return "setSize_2";
      case 991:
        return "setVisible";
      case 992:
        return "setWidth";
      case 993:
        return "setWindowOpacity";
      case 994:
        return "setWindowTitle";
      case 995:
        return "setZOrder";
      case 996:
        return "show";
      case 997:
        return "showMaximized";
      case 998:
        return "showMinimized";
      case 999:
        return "showNormal";
      case 1001:
        return "sizeHint";
      case 1068:
        return "tabAt";
      case 1069:
        return "text";
      case 1003:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__TabBar__registerVirtualMethodCallback')
        .asFunction();
    final callback913 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback913, 913);
    const callbackExcept924 = 0;
    final callback924 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept924);
    registerCallback(thisCpp, callback924, 924);
    final callback927 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback927, 927);
    const callbackExcept933 = 0;
    final callback933 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept933);
    registerCallback(thisCpp, callback933, 933);
    final callback935 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.free_impl_calledFromC);
    registerCallback(thisCpp, callback935, 935);
    final callback937 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback937, 937);
    final callback939 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback939, 939);
    const callbackExcept942 = 0;
    final callback942 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept942);
    registerCallback(thisCpp, callback942, 942);
    final callback944 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback944, 944);
    final callback947 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TabBar.init_calledFromC);
    registerCallback(thisCpp, callback947, 947);
    const callbackExcept949 = 0;
    final callback949 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept949);
    registerCallback(thisCpp, callback949, 949);
    const callbackExcept950 = 0;
    final callback950 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExpicitlyHidden_calledFromC,
        callbackExcept950);
    registerCallback(thisCpp, callback950, 950);
    const callbackExcept951 = 0;
    final callback951 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept951);
    registerCallback(thisCpp, callback951, 951);
    const callbackExcept952 = 0;
    final callback952 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept952);
    registerCallback(thisCpp, callback952, 952);
    const callbackExcept953 = 0;
    final callback953 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept953);
    registerCallback(thisCpp, callback953, 953);
    const callbackExcept954 = 0;
    final callback954 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept954);
    registerCallback(thisCpp, callback954, 954);
    const callbackExcept955 = 0;
    final callback955 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept955);
    registerCallback(thisCpp, callback955, 955);
    final callback956 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback956, 956);
    final callback957 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    final callback958 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback958, 958);
    final callback959 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback960 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback960, 960);
    const callbackExcept961 = 0;
    final callback961 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept961);
    registerCallback(thisCpp, callback961, 961);
    const callbackExcept962 = 0;
    final callback962 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept962);
    registerCallback(thisCpp, callback962, 962);
    final callback964 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback964, 964);
    final callback1060 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.moveTabTo_calledFromC);
    registerCallback(thisCpp, callback1060, 1060);
    final callback965 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback1034 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1034, 1034);
    final callback1035 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1035, 1035);
    final callback1036 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback1036, 1036);
    final callback1061 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TabBar.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback1061, 1061);
    const callbackExcept968 = 0;
    final callback968 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.onResize_2_calledFromC, callbackExcept968);
    registerCallback(thisCpp, callback968, 968);
    final callback971 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback971, 971);
    final callback972 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback972, 972);
    final callback1062 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.rectForTab_calledFromC);
    registerCallback(thisCpp, callback1062, 1062);
    final callback974 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback974, 974);
    final callback975 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback975, 975);
    final callback1063 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.TabBar.removeDockWidget_calledFromC);
    registerCallback(thisCpp, callback1063, 1063);
    final callback1064 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            KDDWBindingsFlutter.TabBar.renameTab_calledFromC);
    registerCallback(thisCpp, callback1064, 1064);
    final callback1065 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.setCurrentIndex_calledFromC);
    registerCallback(thisCpp, callback1065, 1065);
    final callback979 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback979, 979);
    final callback980 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback980, 980);
    final callback981 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback982 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback982, 982);
    final callback983 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback983, 983);
    final callback984 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback985 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback985, 985);
    final callback986 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback986, 986);
    final callback987 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback987, 987);
    final callback988 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback988, 988);
    final callback990 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback990, 990);
    final callback991 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback991, 991);
    final callback992 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback995 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback996 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback996, 996);
    final callback997 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback997, 997);
    final callback998 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback998, 998);
    final callback999 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback999, 999);
    final callback1001 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback1001, 1001);
    const callbackExcept1068 = 0;
    final callback1068 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.TabBar.tabAt_calledFromC, callbackExcept1068);
    registerCallback(thisCpp, callback1068, 1068);
    final callback1069 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.text_calledFromC);
    registerCallback(thisCpp, callback1069, 1069);
    final callback1003 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback1003, 1003);
  }
}
