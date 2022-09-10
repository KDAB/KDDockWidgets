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

class TabBar_flutter extends View_flutter {
  TabBar_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TabBar_flutter.init() : super.init() {}
  factory TabBar_flutter.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (View.isCached(cppPointer)) {
      var instance = View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TabBar_flutter;
    }
    return TabBar_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  } //TabBar_flutter(KDDockWidgets::Controllers::TabBar * controller, KDDockWidgets::View * parent)
  TabBar_flutter(TabBar? controller, {required View? parent}) : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Views__TabBar_flutter__constructor_TabBar_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        View.fromCppPointer(parent), QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  } // moveTabTo(int from, int to)

  moveTabTo(int from, int to) {
    final void_Func_voidstar_int_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            cFunctionSymbolName(984))
        .asFunction();
    func(thisCpp, from, to);
  }

  static void moveTabTo_calledFromC(
      ffi.Pointer<void> thisCpp, int from, int to) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::moveTabTo(int from, int to)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.moveTabTo(from, to);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::onChildAdded(KDDockWidgets::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded(View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::onChildRemoved(KDDockWidgets::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved(View.fromCppPointer(childView));
  } // onRebuildRequested()

  onRebuildRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(985))
        .asFunction();
    func(thisCpp);
  }

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::onResize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(w, h);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  } // rectForTab(int index) const

  QRect rectForTab(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(986))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> rectForTab_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::rectForTab(int index) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.rectForTab(index);
    return result.thisCpp;
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  } // removeDockWidget(KDDockWidgets::Controllers::DockWidget * dw)

  removeDockWidget(DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(987))
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  }

  static void removeDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? dw) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::removeDockWidget(KDDockWidgets::Controllers::DockWidget * dw)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.removeDockWidget(DockWidget.fromCppPointer(dw));
  } // renameTab(int index, const QString & name)

  renameTab(int index, String? name) {
    final void_Func_voidstar_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            cFunctionSymbolName(988))
        .asFunction();
    func(thisCpp, index, name?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void renameTab_calledFromC(
      ffi.Pointer<void> thisCpp, int index, ffi.Pointer<void>? name) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::renameTab(int index, const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.renameTab(index, QString.fromCppPointer(name).toDartString());
  } // setCurrentIndex(int index)

  setCurrentIndex(int index) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(989))
        .asFunction();
    func(thisCpp, index);
  }

  static void setCurrentIndex_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setCurrentIndex(int index)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCurrentIndex(index);
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setParent(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent(View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  } // tabAt(QPoint localPos) const

  int tabAt(QPoint localPos) {
    final int_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(991))
        .asFunction();
    return func(thisCpp, localPos == null ? ffi.nullptr : localPos.thisCpp);
  }

  static int tabAt_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPos) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::tabAt(QPoint localPos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.tabAt(QPoint.fromCppPointer(localPos));
    return result;
  } // text(int index) const

  QString text(int index) {
    final voidstar_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(992))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp, index);
    return QString.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> text_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::text(int index) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.text(index);
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__TabBar_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 843:
        return "c_KDDockWidgets__Views__TabBar_flutter__activateWindow";
      case 854:
        return "c_KDDockWidgets__Views__TabBar_flutter__close";
      case 857:
        return "c_KDDockWidgets__Views__TabBar_flutter__createPlatformWindow";
      case 862:
        return "c_KDDockWidgets__Views__TabBar_flutter__flags";
      case 864:
        return "c_KDDockWidgets__Views__TabBar_flutter__free_impl";
      case 866:
        return "c_KDDockWidgets__Views__TabBar_flutter__geometry";
      case 868:
        return "c_KDDockWidgets__Views__TabBar_flutter__grabMouse";
      case 871:
        return "c_KDDockWidgets__Views__TabBar_flutter__hasFocus";
      case 873:
        return "c_KDDockWidgets__Views__TabBar_flutter__hide";
      case 876:
        return "c_KDDockWidgets__Views__TabBar_flutter__init";
      case 878:
        return "c_KDDockWidgets__Views__TabBar_flutter__isActiveWindow";
      case 879:
        return "c_KDDockWidgets__Views__TabBar_flutter__isMaximized";
      case 880:
        return "c_KDDockWidgets__Views__TabBar_flutter__isMinimized";
      case 881:
        return "c_KDDockWidgets__Views__TabBar_flutter__isNull";
      case 882:
        return "c_KDDockWidgets__Views__TabBar_flutter__isRootView";
      case 883:
        return "c_KDDockWidgets__Views__TabBar_flutter__isVisible";
      case 884:
        return "c_KDDockWidgets__Views__TabBar_flutter__mapFromGlobal_QPoint";
      case 885:
        return "c_KDDockWidgets__Views__TabBar_flutter__mapTo_View_QPoint";
      case 886:
        return "c_KDDockWidgets__Views__TabBar_flutter__mapToGlobal_QPoint";
      case 887:
        return "c_KDDockWidgets__Views__TabBar_flutter__maxSizeHint";
      case 888:
        return "c_KDDockWidgets__Views__TabBar_flutter__minSize";
      case 889:
        return "c_KDDockWidgets__Views__TabBar_flutter__minimumHeight";
      case 890:
        return "c_KDDockWidgets__Views__TabBar_flutter__minimumWidth";
      case 892:
        return "c_KDDockWidgets__Views__TabBar_flutter__move_int_int";
      case 984:
        return "c_KDDockWidgets__Views__TabBar_flutter__moveTabTo_int_int";
      case 893:
        return "c_KDDockWidgets__Views__TabBar_flutter__normalGeometry";
      case 894:
        return "c_KDDockWidgets__Views__TabBar_flutter__objectName";
      case 961:
        return "c_KDDockWidgets__Views__TabBar_flutter__onChildAdded_View";
      case 962:
        return "c_KDDockWidgets__Views__TabBar_flutter__onChildRemoved_View";
      case 985:
        return "c_KDDockWidgets__Views__TabBar_flutter__onRebuildRequested";
      case 896:
        return "c_KDDockWidgets__Views__TabBar_flutter__onResize_int_int";
      case 899:
        return "c_KDDockWidgets__Views__TabBar_flutter__raise";
      case 900:
        return "c_KDDockWidgets__Views__TabBar_flutter__raiseAndActivate";
      case 986:
        return "c_KDDockWidgets__Views__TabBar_flutter__rectForTab_int";
      case 902:
        return "c_KDDockWidgets__Views__TabBar_flutter__releaseKeyboard";
      case 903:
        return "c_KDDockWidgets__Views__TabBar_flutter__releaseMouse";
      case 987:
        return "c_KDDockWidgets__Views__TabBar_flutter__removeDockWidget_DockWidget";
      case 988:
        return "c_KDDockWidgets__Views__TabBar_flutter__renameTab_int_QString";
      case 989:
        return "c_KDDockWidgets__Views__TabBar_flutter__setCurrentIndex_int";
      case 907:
        return "c_KDDockWidgets__Views__TabBar_flutter__setCursor_CursorShape";
      case 908:
        return "c_KDDockWidgets__Views__TabBar_flutter__setFixedHeight_int";
      case 909:
        return "c_KDDockWidgets__Views__TabBar_flutter__setFixedWidth_int";
      case 910:
        return "c_KDDockWidgets__Views__TabBar_flutter__setGeometry_QRect";
      case 911:
        return "c_KDDockWidgets__Views__TabBar_flutter__setHeight_int";
      case 912:
        return "c_KDDockWidgets__Views__TabBar_flutter__setMaximumSize_QSize";
      case 913:
        return "c_KDDockWidgets__Views__TabBar_flutter__setMinimumSize_QSize";
      case 914:
        return "c_KDDockWidgets__Views__TabBar_flutter__setMouseTracking_bool";
      case 915:
        return "c_KDDockWidgets__Views__TabBar_flutter__setObjectName_QString";
      case 916:
        return "c_KDDockWidgets__Views__TabBar_flutter__setParent_View";
      case 918:
        return "c_KDDockWidgets__Views__TabBar_flutter__setSize_int_int";
      case 919:
        return "c_KDDockWidgets__Views__TabBar_flutter__setVisible_bool";
      case 920:
        return "c_KDDockWidgets__Views__TabBar_flutter__setWidth_int";
      case 921:
        return "c_KDDockWidgets__Views__TabBar_flutter__setWindowOpacity_double";
      case 922:
        return "c_KDDockWidgets__Views__TabBar_flutter__setWindowTitle_QString";
      case 923:
        return "c_KDDockWidgets__Views__TabBar_flutter__setZOrder_int";
      case 924:
        return "c_KDDockWidgets__Views__TabBar_flutter__show";
      case 925:
        return "c_KDDockWidgets__Views__TabBar_flutter__showMaximized";
      case 926:
        return "c_KDDockWidgets__Views__TabBar_flutter__showMinimized";
      case 927:
        return "c_KDDockWidgets__Views__TabBar_flutter__showNormal";
      case 929:
        return "c_KDDockWidgets__Views__TabBar_flutter__sizeHint";
      case 991:
        return "c_KDDockWidgets__Views__TabBar_flutter__tabAt_QPoint";
      case 992:
        return "c_KDDockWidgets__Views__TabBar_flutter__text_int";
      case 931:
        return "c_KDDockWidgets__Views__TabBar_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 843:
        return "activateWindow";
      case 854:
        return "close";
      case 857:
        return "createPlatformWindow";
      case 862:
        return "flags";
      case 864:
        return "free_impl";
      case 866:
        return "geometry";
      case 868:
        return "grabMouse";
      case 871:
        return "hasFocus";
      case 873:
        return "hide";
      case 876:
        return "init";
      case 878:
        return "isActiveWindow";
      case 879:
        return "isMaximized";
      case 880:
        return "isMinimized";
      case 881:
        return "isNull";
      case 882:
        return "isRootView";
      case 883:
        return "isVisible";
      case 884:
        return "mapFromGlobal";
      case 885:
        return "mapTo";
      case 886:
        return "mapToGlobal";
      case 887:
        return "maxSizeHint";
      case 888:
        return "minSize";
      case 889:
        return "minimumHeight";
      case 890:
        return "minimumWidth";
      case 892:
        return "move_2";
      case 984:
        return "moveTabTo";
      case 893:
        return "normalGeometry";
      case 894:
        return "objectName";
      case 961:
        return "onChildAdded";
      case 962:
        return "onChildRemoved";
      case 985:
        return "onRebuildRequested";
      case 896:
        return "onResize_2";
      case 899:
        return "raise";
      case 900:
        return "raiseAndActivate";
      case 986:
        return "rectForTab";
      case 902:
        return "releaseKeyboard";
      case 903:
        return "releaseMouse";
      case 987:
        return "removeDockWidget";
      case 988:
        return "renameTab";
      case 989:
        return "setCurrentIndex";
      case 907:
        return "setCursor";
      case 908:
        return "setFixedHeight";
      case 909:
        return "setFixedWidth";
      case 910:
        return "setGeometry";
      case 911:
        return "setHeight";
      case 912:
        return "setMaximumSize";
      case 913:
        return "setMinimumSize";
      case 914:
        return "setMouseTracking";
      case 915:
        return "setObjectName";
      case 916:
        return "setParent";
      case 918:
        return "setSize_2";
      case 919:
        return "setVisible";
      case 920:
        return "setWidth";
      case 921:
        return "setWindowOpacity";
      case 922:
        return "setWindowTitle";
      case 923:
        return "setZOrder";
      case 924:
        return "show";
      case 925:
        return "showMaximized";
      case 926:
        return "showMinimized";
      case 927:
        return "showNormal";
      case 929:
        return "sizeHint";
      case 991:
        return "tabAt";
      case 992:
        return "text";
      case 931:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Views__TabBar_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback843 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback843, 843);
    const callbackExcept854 = 0;
    final callback854 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept854);
    registerCallback(thisCpp, callback854, 854);
    final callback857 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback857, 857);
    const callbackExcept862 = 0;
    final callback862 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept862);
    registerCallback(thisCpp, callback862, 862);
    final callback864 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback864, 864);
    final callback866 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback866, 866);
    final callback868 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback868, 868);
    const callbackExcept871 = 0;
    final callback871 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept871);
    registerCallback(thisCpp, callback871, 871);
    final callback873 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback873, 873);
    final callback876 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        TabBar_flutter.init_calledFromC);
    registerCallback(thisCpp, callback876, 876);
    const callbackExcept878 = 0;
    final callback878 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept878);
    registerCallback(thisCpp, callback878, 878);
    const callbackExcept879 = 0;
    final callback879 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept879);
    registerCallback(thisCpp, callback879, 879);
    const callbackExcept880 = 0;
    final callback880 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept880);
    registerCallback(thisCpp, callback880, 880);
    const callbackExcept881 = 0;
    final callback881 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept881);
    registerCallback(thisCpp, callback881, 881);
    const callbackExcept882 = 0;
    final callback882 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept882);
    registerCallback(thisCpp, callback882, 882);
    const callbackExcept883 = 0;
    final callback883 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept883);
    registerCallback(thisCpp, callback883, 883);
    final callback884 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback884, 884);
    final callback885 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback885, 885);
    final callback886 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback886, 886);
    final callback887 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback887, 887);
    final callback888 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback888, 888);
    const callbackExcept889 = 0;
    final callback889 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept889);
    registerCallback(thisCpp, callback889, 889);
    const callbackExcept890 = 0;
    final callback890 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept890);
    registerCallback(thisCpp, callback890, 890);
    final callback892 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback892, 892);
    final callback984 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            TabBar_flutter.moveTabTo_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback893 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback893, 893);
    final callback894 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback894, 894);
    final callback961 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback961, 961);
    final callback962 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback962, 962);
    final callback985 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        TabBar_flutter.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback985, 985);
    const callbackExcept896 = 0;
    final callback896 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.onResize_2_calledFromC, callbackExcept896);
    registerCallback(thisCpp, callback896, 896);
    final callback899 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback899, 899);
    final callback900 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    final callback986 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            TabBar_flutter.rectForTab_calledFromC);
    registerCallback(thisCpp, callback986, 986);
    final callback902 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback902, 902);
    final callback903 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback903, 903);
    final callback987 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            TabBar_flutter.removeDockWidget_calledFromC);
    registerCallback(thisCpp, callback987, 987);
    final callback988 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            TabBar_flutter.renameTab_calledFromC);
    registerCallback(thisCpp, callback988, 988);
    final callback989 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            TabBar_flutter.setCurrentIndex_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback907 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback908 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback908, 908);
    final callback909 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback910 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback911 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    final callback912 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    final callback913 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback913, 913);
    final callback914 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback914, 914);
    final callback915 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback915, 915);
    final callback916 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback918 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback918, 918);
    final callback919 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback919, 919);
    final callback920 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback920, 920);
    final callback921 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback921, 921);
    final callback922 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback922, 922);
    final callback923 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback923, 923);
    final callback924 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback924, 924);
    final callback925 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback925, 925);
    final callback926 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback926, 926);
    final callback927 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback927, 927);
    final callback929 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback929, 929);
    const callbackExcept991 = 0;
    final callback991 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            TabBar_flutter.tabAt_calledFromC, callbackExcept991);
    registerCallback(thisCpp, callback991, 991);
    final callback992 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            TabBar_flutter.text_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback931 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback931, 931);
  }
}
