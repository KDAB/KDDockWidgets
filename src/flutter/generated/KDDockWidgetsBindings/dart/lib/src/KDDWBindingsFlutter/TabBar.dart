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
            cFunctionSymbolName(1069))
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
  }

  static void onGeometryChanged_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onGeometryChanged()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onGeometryChanged();
  } // onRebuildRequested()

  onRebuildRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1072))
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

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
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
            cFunctionSymbolName(1073))
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
            cFunctionSymbolName(1074))
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
            cFunctionSymbolName(1075))
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
            cFunctionSymbolName(1076))
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
            cFunctionSymbolName(1079))
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
            cFunctionSymbolName(1080))
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
      case 915:
        return "c_KDDockWidgets__flutter__TabBar__activateWindow";
      case 926:
        return "c_KDDockWidgets__flutter__TabBar__close";
      case 929:
        return "c_KDDockWidgets__flutter__TabBar__createPlatformWindow";
      case 936:
        return "c_KDDockWidgets__flutter__TabBar__flags";
      case 939:
        return "c_KDDockWidgets__flutter__TabBar__geometry";
      case 941:
        return "c_KDDockWidgets__flutter__TabBar__grabMouse";
      case 944:
        return "c_KDDockWidgets__flutter__TabBar__hasFocus";
      case 946:
        return "c_KDDockWidgets__flutter__TabBar__hide";
      case 949:
        return "c_KDDockWidgets__flutter__TabBar__init";
      case 951:
        return "c_KDDockWidgets__flutter__TabBar__isActiveWindow";
      case 952:
        return "c_KDDockWidgets__flutter__TabBar__isExpicitlyHidden";
      case 953:
        return "c_KDDockWidgets__flutter__TabBar__isMaximized";
      case 954:
        return "c_KDDockWidgets__flutter__TabBar__isMinimized";
      case 955:
        return "c_KDDockWidgets__flutter__TabBar__isNull";
      case 956:
        return "c_KDDockWidgets__flutter__TabBar__isRootView";
      case 957:
        return "c_KDDockWidgets__flutter__TabBar__isVisible";
      case 958:
        return "c_KDDockWidgets__flutter__TabBar__mapFromGlobal_QPoint";
      case 959:
        return "c_KDDockWidgets__flutter__TabBar__mapTo_View_QPoint";
      case 960:
        return "c_KDDockWidgets__flutter__TabBar__mapToGlobal_QPoint";
      case 961:
        return "c_KDDockWidgets__flutter__TabBar__maxSizeHint";
      case 962:
        return "c_KDDockWidgets__flutter__TabBar__minSize";
      case 963:
        return "c_KDDockWidgets__flutter__TabBar__minimumHeight";
      case 964:
        return "c_KDDockWidgets__flutter__TabBar__minimumWidth";
      case 966:
        return "c_KDDockWidgets__flutter__TabBar__move_int_int";
      case 1069:
        return "c_KDDockWidgets__flutter__TabBar__moveTabTo_int_int";
      case 967:
        return "c_KDDockWidgets__flutter__TabBar__normalGeometry";
      case 968:
        return "c_KDDockWidgets__flutter__TabBar__objectName";
      case 1037:
        return "c_KDDockWidgets__flutter__TabBar__onChildAdded_View";
      case 1038:
        return "c_KDDockWidgets__flutter__TabBar__onChildRemoved_View";
      case 1039:
        return "c_KDDockWidgets__flutter__TabBar__onChildVisibilityChanged_View";
      case 1041:
        return "c_KDDockWidgets__flutter__TabBar__onGeometryChanged";
      case 1072:
        return "c_KDDockWidgets__flutter__TabBar__onRebuildRequested";
      case 970:
        return "c_KDDockWidgets__flutter__TabBar__onResize_int_int";
      case 973:
        return "c_KDDockWidgets__flutter__TabBar__raise";
      case 974:
        return "c_KDDockWidgets__flutter__TabBar__raiseAndActivate";
      case 1073:
        return "c_KDDockWidgets__flutter__TabBar__rectForTab_int";
      case 976:
        return "c_KDDockWidgets__flutter__TabBar__releaseKeyboard";
      case 977:
        return "c_KDDockWidgets__flutter__TabBar__releaseMouse";
      case 1074:
        return "c_KDDockWidgets__flutter__TabBar__removeDockWidget_DockWidget";
      case 1075:
        return "c_KDDockWidgets__flutter__TabBar__renameTab_int_QString";
      case 1076:
        return "c_KDDockWidgets__flutter__TabBar__setCurrentIndex_int";
      case 981:
        return "c_KDDockWidgets__flutter__TabBar__setCursor_CursorShape";
      case 982:
        return "c_KDDockWidgets__flutter__TabBar__setFixedHeight_int";
      case 983:
        return "c_KDDockWidgets__flutter__TabBar__setFixedWidth_int";
      case 984:
        return "c_KDDockWidgets__flutter__TabBar__setGeometry_QRect";
      case 985:
        return "c_KDDockWidgets__flutter__TabBar__setHeight_int";
      case 986:
        return "c_KDDockWidgets__flutter__TabBar__setMaximumSize_QSize";
      case 987:
        return "c_KDDockWidgets__flutter__TabBar__setMinimumSize_QSize";
      case 988:
        return "c_KDDockWidgets__flutter__TabBar__setMouseTracking_bool";
      case 989:
        return "c_KDDockWidgets__flutter__TabBar__setObjectName_QString";
      case 990:
        return "c_KDDockWidgets__flutter__TabBar__setParent_View";
      case 992:
        return "c_KDDockWidgets__flutter__TabBar__setSize_int_int";
      case 993:
        return "c_KDDockWidgets__flutter__TabBar__setVisible_bool";
      case 994:
        return "c_KDDockWidgets__flutter__TabBar__setWidth_int";
      case 995:
        return "c_KDDockWidgets__flutter__TabBar__setWindowOpacity_double";
      case 996:
        return "c_KDDockWidgets__flutter__TabBar__setWindowTitle_QString";
      case 997:
        return "c_KDDockWidgets__flutter__TabBar__setZOrder_int";
      case 998:
        return "c_KDDockWidgets__flutter__TabBar__show";
      case 999:
        return "c_KDDockWidgets__flutter__TabBar__showMaximized";
      case 1000:
        return "c_KDDockWidgets__flutter__TabBar__showMinimized";
      case 1001:
        return "c_KDDockWidgets__flutter__TabBar__showNormal";
      case 1003:
        return "c_KDDockWidgets__flutter__TabBar__sizeHint";
      case 1079:
        return "c_KDDockWidgets__flutter__TabBar__tabAt_QPoint";
      case 1080:
        return "c_KDDockWidgets__flutter__TabBar__text_int";
      case 1005:
        return "c_KDDockWidgets__flutter__TabBar__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 915:
        return "activateWindow";
      case 926:
        return "close";
      case 929:
        return "createPlatformWindow";
      case 936:
        return "flags";
      case 939:
        return "geometry";
      case 941:
        return "grabMouse";
      case 944:
        return "hasFocus";
      case 946:
        return "hide";
      case 949:
        return "init";
      case 951:
        return "isActiveWindow";
      case 952:
        return "isExpicitlyHidden";
      case 953:
        return "isMaximized";
      case 954:
        return "isMinimized";
      case 955:
        return "isNull";
      case 956:
        return "isRootView";
      case 957:
        return "isVisible";
      case 958:
        return "mapFromGlobal";
      case 959:
        return "mapTo";
      case 960:
        return "mapToGlobal";
      case 961:
        return "maxSizeHint";
      case 962:
        return "minSize";
      case 963:
        return "minimumHeight";
      case 964:
        return "minimumWidth";
      case 966:
        return "move_2";
      case 1069:
        return "moveTabTo";
      case 967:
        return "normalGeometry";
      case 968:
        return "objectName";
      case 1037:
        return "onChildAdded";
      case 1038:
        return "onChildRemoved";
      case 1039:
        return "onChildVisibilityChanged";
      case 1041:
        return "onGeometryChanged";
      case 1072:
        return "onRebuildRequested";
      case 970:
        return "onResize_2";
      case 973:
        return "raise";
      case 974:
        return "raiseAndActivate";
      case 1073:
        return "rectForTab";
      case 976:
        return "releaseKeyboard";
      case 977:
        return "releaseMouse";
      case 1074:
        return "removeDockWidget";
      case 1075:
        return "renameTab";
      case 1076:
        return "setCurrentIndex";
      case 981:
        return "setCursor";
      case 982:
        return "setFixedHeight";
      case 983:
        return "setFixedWidth";
      case 984:
        return "setGeometry";
      case 985:
        return "setHeight";
      case 986:
        return "setMaximumSize";
      case 987:
        return "setMinimumSize";
      case 988:
        return "setMouseTracking";
      case 989:
        return "setObjectName";
      case 990:
        return "setParent";
      case 992:
        return "setSize_2";
      case 993:
        return "setVisible";
      case 994:
        return "setWidth";
      case 995:
        return "setWindowOpacity";
      case 996:
        return "setWindowTitle";
      case 997:
        return "setZOrder";
      case 998:
        return "show";
      case 999:
        return "showMaximized";
      case 1000:
        return "showMinimized";
      case 1001:
        return "showNormal";
      case 1003:
        return "sizeHint";
      case 1079:
        return "tabAt";
      case 1080:
        return "text";
      case 1005:
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
    final callback915 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback915, 915);
    const callbackExcept926 = 0;
    final callback926 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept926);
    registerCallback(thisCpp, callback926, 926);
    final callback929 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback929, 929);
    const callbackExcept936 = 0;
    final callback936 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept936);
    registerCallback(thisCpp, callback936, 936);
    final callback939 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback939, 939);
    final callback941 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback941, 941);
    const callbackExcept944 = 0;
    final callback944 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept944);
    registerCallback(thisCpp, callback944, 944);
    final callback946 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback949 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TabBar.init_calledFromC);
    registerCallback(thisCpp, callback949, 949);
    const callbackExcept951 = 0;
    final callback951 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept951);
    registerCallback(thisCpp, callback951, 951);
    const callbackExcept952 = 0;
    final callback952 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExpicitlyHidden_calledFromC,
        callbackExcept952);
    registerCallback(thisCpp, callback952, 952);
    const callbackExcept953 = 0;
    final callback953 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept953);
    registerCallback(thisCpp, callback953, 953);
    const callbackExcept954 = 0;
    final callback954 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept954);
    registerCallback(thisCpp, callback954, 954);
    const callbackExcept955 = 0;
    final callback955 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept955);
    registerCallback(thisCpp, callback955, 955);
    const callbackExcept956 = 0;
    final callback956 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept956);
    registerCallback(thisCpp, callback956, 956);
    const callbackExcept957 = 0;
    final callback957 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept957);
    registerCallback(thisCpp, callback957, 957);
    final callback958 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback958, 958);
    final callback959 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback960 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback960, 960);
    final callback961 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback961, 961);
    final callback962 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback962, 962);
    const callbackExcept963 = 0;
    final callback963 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept963);
    registerCallback(thisCpp, callback963, 963);
    const callbackExcept964 = 0;
    final callback964 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept964);
    registerCallback(thisCpp, callback964, 964);
    final callback966 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback1069 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.moveTabTo_calledFromC);
    registerCallback(thisCpp, callback1069, 1069);
    final callback967 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback1037 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1037, 1037);
    final callback1038 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1038, 1038);
    final callback1039 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback1039, 1039);
    final callback1041 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback1041, 1041);
    final callback1072 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.TabBar.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback1072, 1072);
    const callbackExcept970 = 0;
    final callback970 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept970);
    registerCallback(thisCpp, callback970, 970);
    final callback973 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback973, 973);
    final callback974 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback974, 974);
    final callback1073 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.rectForTab_calledFromC);
    registerCallback(thisCpp, callback1073, 1073);
    final callback976 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback976, 976);
    final callback977 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback977, 977);
    final callback1074 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.TabBar.removeDockWidget_calledFromC);
    registerCallback(thisCpp, callback1074, 1074);
    final callback1075 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            KDDWBindingsFlutter.TabBar.renameTab_calledFromC);
    registerCallback(thisCpp, callback1075, 1075);
    final callback1076 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.setCurrentIndex_calledFromC);
    registerCallback(thisCpp, callback1076, 1076);
    final callback981 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback982 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback982, 982);
    final callback983 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback983, 983);
    final callback984 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback985 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback985, 985);
    final callback986 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback986, 986);
    final callback987 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback987, 987);
    final callback988 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback988, 988);
    final callback989 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback990 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback990, 990);
    final callback992 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback995 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback996 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback996, 996);
    final callback997 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback997, 997);
    final callback998 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback998, 998);
    final callback999 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback999, 999);
    final callback1000 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback1000, 1000);
    final callback1001 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback1001, 1001);
    final callback1003 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback1003, 1003);
    const callbackExcept1079 = 0;
    final callback1079 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.TabBar.tabAt_calledFromC, callbackExcept1079);
    registerCallback(thisCpp, callback1079, 1079);
    final callback1080 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.TabBar.text_calledFromC);
    registerCallback(thisCpp, callback1080, 1080);
    final callback1005 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
  }
}
