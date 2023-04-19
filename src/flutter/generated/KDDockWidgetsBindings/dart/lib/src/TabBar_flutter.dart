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
  } //TabBar_flutter(KDDockWidgets::Core::TabBar * controller, KDDockWidgets::Core::View * parent)
  TabBar_flutter(TabBar? controller, {required View? parent}) : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__TabBar_flutter__constructor_TabBar_View')
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
          "Dart instance not found for TabBar_flutter::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
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
            cFunctionSymbolName(1027))
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
          "Dart instance not found for TabBar_flutter::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
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
          "Dart instance not found for TabBar_flutter::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved(View.fromCppPointer(childView));
  } // onRebuildRequested()

  onRebuildRequested() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            cFunctionSymbolName(1028))
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
            cFunctionSymbolName(1029))
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
  } // removeDockWidget(KDDockWidgets::Core::DockWidget * dw)

  removeDockWidget(DockWidget? dw) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1030))
        .asFunction();
    func(thisCpp, dw == null ? ffi.nullptr : dw.thisCpp);
  }

  static void removeDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? dw) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TabBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TabBar_flutter::removeDockWidget(KDDockWidgets::Core::DockWidget * dw)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.removeDockWidget(DockWidget.fromCppPointer(dw));
  } // renameTab(int index, const QString & name)

  renameTab(int index, String? name) {
    final void_Func_voidstar_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            cFunctionSymbolName(1031))
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
            cFunctionSymbolName(1032))
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
          "Dart instance not found for TabBar_flutter::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
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
            cFunctionSymbolName(1034))
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
            cFunctionSymbolName(1035))
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
            'c_KDDockWidgets__flutter__TabBar_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 886:
        return "c_KDDockWidgets__flutter__TabBar_flutter__activateWindow";
      case 897:
        return "c_KDDockWidgets__flutter__TabBar_flutter__close";
      case 900:
        return "c_KDDockWidgets__flutter__TabBar_flutter__createPlatformWindow";
      case 905:
        return "c_KDDockWidgets__flutter__TabBar_flutter__flags";
      case 907:
        return "c_KDDockWidgets__flutter__TabBar_flutter__free_impl";
      case 909:
        return "c_KDDockWidgets__flutter__TabBar_flutter__geometry";
      case 911:
        return "c_KDDockWidgets__flutter__TabBar_flutter__grabMouse";
      case 914:
        return "c_KDDockWidgets__flutter__TabBar_flutter__hasFocus";
      case 916:
        return "c_KDDockWidgets__flutter__TabBar_flutter__hide";
      case 919:
        return "c_KDDockWidgets__flutter__TabBar_flutter__init";
      case 921:
        return "c_KDDockWidgets__flutter__TabBar_flutter__isActiveWindow";
      case 922:
        return "c_KDDockWidgets__flutter__TabBar_flutter__isMaximized";
      case 923:
        return "c_KDDockWidgets__flutter__TabBar_flutter__isMinimized";
      case 924:
        return "c_KDDockWidgets__flutter__TabBar_flutter__isNull";
      case 925:
        return "c_KDDockWidgets__flutter__TabBar_flutter__isRootView";
      case 926:
        return "c_KDDockWidgets__flutter__TabBar_flutter__isVisible";
      case 927:
        return "c_KDDockWidgets__flutter__TabBar_flutter__mapFromGlobal_QPoint";
      case 928:
        return "c_KDDockWidgets__flutter__TabBar_flutter__mapTo_View_QPoint";
      case 929:
        return "c_KDDockWidgets__flutter__TabBar_flutter__mapToGlobal_QPoint";
      case 930:
        return "c_KDDockWidgets__flutter__TabBar_flutter__maxSizeHint";
      case 931:
        return "c_KDDockWidgets__flutter__TabBar_flutter__minSize";
      case 932:
        return "c_KDDockWidgets__flutter__TabBar_flutter__minimumHeight";
      case 933:
        return "c_KDDockWidgets__flutter__TabBar_flutter__minimumWidth";
      case 935:
        return "c_KDDockWidgets__flutter__TabBar_flutter__move_int_int";
      case 1027:
        return "c_KDDockWidgets__flutter__TabBar_flutter__moveTabTo_int_int";
      case 936:
        return "c_KDDockWidgets__flutter__TabBar_flutter__normalGeometry";
      case 937:
        return "c_KDDockWidgets__flutter__TabBar_flutter__objectName";
      case 1004:
        return "c_KDDockWidgets__flutter__TabBar_flutter__onChildAdded_View";
      case 1005:
        return "c_KDDockWidgets__flutter__TabBar_flutter__onChildRemoved_View";
      case 1028:
        return "c_KDDockWidgets__flutter__TabBar_flutter__onRebuildRequested";
      case 939:
        return "c_KDDockWidgets__flutter__TabBar_flutter__onResize_int_int";
      case 942:
        return "c_KDDockWidgets__flutter__TabBar_flutter__raise";
      case 943:
        return "c_KDDockWidgets__flutter__TabBar_flutter__raiseAndActivate";
      case 1029:
        return "c_KDDockWidgets__flutter__TabBar_flutter__rectForTab_int";
      case 945:
        return "c_KDDockWidgets__flutter__TabBar_flutter__releaseKeyboard";
      case 946:
        return "c_KDDockWidgets__flutter__TabBar_flutter__releaseMouse";
      case 1030:
        return "c_KDDockWidgets__flutter__TabBar_flutter__removeDockWidget_DockWidget";
      case 1031:
        return "c_KDDockWidgets__flutter__TabBar_flutter__renameTab_int_QString";
      case 1032:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setCurrentIndex_int";
      case 950:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setCursor_CursorShape";
      case 951:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setFixedHeight_int";
      case 952:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setFixedWidth_int";
      case 953:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setGeometry_QRect";
      case 954:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setHeight_int";
      case 955:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setMaximumSize_QSize";
      case 956:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setMinimumSize_QSize";
      case 957:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setMouseTracking_bool";
      case 958:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setObjectName_QString";
      case 959:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setParent_View";
      case 961:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setSize_int_int";
      case 962:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setVisible_bool";
      case 963:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setWidth_int";
      case 964:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setWindowOpacity_double";
      case 965:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setWindowTitle_QString";
      case 966:
        return "c_KDDockWidgets__flutter__TabBar_flutter__setZOrder_int";
      case 967:
        return "c_KDDockWidgets__flutter__TabBar_flutter__show";
      case 968:
        return "c_KDDockWidgets__flutter__TabBar_flutter__showMaximized";
      case 969:
        return "c_KDDockWidgets__flutter__TabBar_flutter__showMinimized";
      case 970:
        return "c_KDDockWidgets__flutter__TabBar_flutter__showNormal";
      case 972:
        return "c_KDDockWidgets__flutter__TabBar_flutter__sizeHint";
      case 1034:
        return "c_KDDockWidgets__flutter__TabBar_flutter__tabAt_QPoint";
      case 1035:
        return "c_KDDockWidgets__flutter__TabBar_flutter__text_int";
      case 974:
        return "c_KDDockWidgets__flutter__TabBar_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 886:
        return "activateWindow";
      case 897:
        return "close";
      case 900:
        return "createPlatformWindow";
      case 905:
        return "flags";
      case 907:
        return "free_impl";
      case 909:
        return "geometry";
      case 911:
        return "grabMouse";
      case 914:
        return "hasFocus";
      case 916:
        return "hide";
      case 919:
        return "init";
      case 921:
        return "isActiveWindow";
      case 922:
        return "isMaximized";
      case 923:
        return "isMinimized";
      case 924:
        return "isNull";
      case 925:
        return "isRootView";
      case 926:
        return "isVisible";
      case 927:
        return "mapFromGlobal";
      case 928:
        return "mapTo";
      case 929:
        return "mapToGlobal";
      case 930:
        return "maxSizeHint";
      case 931:
        return "minSize";
      case 932:
        return "minimumHeight";
      case 933:
        return "minimumWidth";
      case 935:
        return "move_2";
      case 1027:
        return "moveTabTo";
      case 936:
        return "normalGeometry";
      case 937:
        return "objectName";
      case 1004:
        return "onChildAdded";
      case 1005:
        return "onChildRemoved";
      case 1028:
        return "onRebuildRequested";
      case 939:
        return "onResize_2";
      case 942:
        return "raise";
      case 943:
        return "raiseAndActivate";
      case 1029:
        return "rectForTab";
      case 945:
        return "releaseKeyboard";
      case 946:
        return "releaseMouse";
      case 1030:
        return "removeDockWidget";
      case 1031:
        return "renameTab";
      case 1032:
        return "setCurrentIndex";
      case 950:
        return "setCursor";
      case 951:
        return "setFixedHeight";
      case 952:
        return "setFixedWidth";
      case 953:
        return "setGeometry";
      case 954:
        return "setHeight";
      case 955:
        return "setMaximumSize";
      case 956:
        return "setMinimumSize";
      case 957:
        return "setMouseTracking";
      case 958:
        return "setObjectName";
      case 959:
        return "setParent";
      case 961:
        return "setSize_2";
      case 962:
        return "setVisible";
      case 963:
        return "setWidth";
      case 964:
        return "setWindowOpacity";
      case 965:
        return "setWindowTitle";
      case 966:
        return "setZOrder";
      case 967:
        return "show";
      case 968:
        return "showMaximized";
      case 969:
        return "showMinimized";
      case 970:
        return "showNormal";
      case 972:
        return "sizeHint";
      case 1034:
        return "tabAt";
      case 1035:
        return "text";
      case 974:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__TabBar_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback886 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback886, 886);
    const callbackExcept897 = 0;
    final callback897 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept897);
    registerCallback(thisCpp, callback897, 897);
    final callback900 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    const callbackExcept905 = 0;
    final callback905 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept905);
    registerCallback(thisCpp, callback905, 905);
    final callback907 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback909 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback911 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    const callbackExcept914 = 0;
    final callback914 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept914);
    registerCallback(thisCpp, callback914, 914);
    final callback916 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback919 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        TabBar_flutter.init_calledFromC);
    registerCallback(thisCpp, callback919, 919);
    const callbackExcept921 = 0;
    final callback921 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept921);
    registerCallback(thisCpp, callback921, 921);
    const callbackExcept922 = 0;
    final callback922 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept922);
    registerCallback(thisCpp, callback922, 922);
    const callbackExcept923 = 0;
    final callback923 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept923);
    registerCallback(thisCpp, callback923, 923);
    const callbackExcept924 = 0;
    final callback924 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept924);
    registerCallback(thisCpp, callback924, 924);
    const callbackExcept925 = 0;
    final callback925 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept925);
    registerCallback(thisCpp, callback925, 925);
    const callbackExcept926 = 0;
    final callback926 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept926);
    registerCallback(thisCpp, callback926, 926);
    final callback927 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback927, 927);
    final callback928 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback928, 928);
    final callback929 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback929, 929);
    final callback930 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback930, 930);
    final callback931 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback931, 931);
    const callbackExcept932 = 0;
    final callback932 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept932);
    registerCallback(thisCpp, callback932, 932);
    const callbackExcept933 = 0;
    final callback933 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept933);
    registerCallback(thisCpp, callback933, 933);
    final callback935 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback935, 935);
    final callback1027 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            TabBar_flutter.moveTabTo_calledFromC);
    registerCallback(thisCpp, callback1027, 1027);
    final callback936 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback936, 936);
    final callback937 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback937, 937);
    final callback1004 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1004, 1004);
    final callback1005 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
    final callback1028 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        TabBar_flutter.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback1028, 1028);
    const callbackExcept939 = 0;
    final callback939 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.onResize_2_calledFromC, callbackExcept939);
    registerCallback(thisCpp, callback939, 939);
    final callback942 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback942, 942);
    final callback943 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback943, 943);
    final callback1029 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            TabBar_flutter.rectForTab_calledFromC);
    registerCallback(thisCpp, callback1029, 1029);
    final callback945 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback945, 945);
    final callback946 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback1030 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            TabBar_flutter.removeDockWidget_calledFromC);
    registerCallback(thisCpp, callback1030, 1030);
    final callback1031 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            TabBar_flutter.renameTab_calledFromC);
    registerCallback(thisCpp, callback1031, 1031);
    final callback1032 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            TabBar_flutter.setCurrentIndex_calledFromC);
    registerCallback(thisCpp, callback1032, 1032);
    final callback950 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback950, 950);
    final callback951 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback951, 951);
    final callback952 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback952, 952);
    final callback953 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback953, 953);
    final callback954 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback955 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback955, 955);
    final callback956 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback956, 956);
    final callback957 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    final callback958 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback958, 958);
    final callback959 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback961 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback961, 961);
    final callback962 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback962, 962);
    final callback963 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback963, 963);
    final callback964 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback964, 964);
    final callback965 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback967 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback969 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback969, 969);
    final callback970 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback970, 970);
    final callback972 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback972, 972);
    const callbackExcept1034 = 0;
    final callback1034 =
        ffi.Pointer.fromFunction<int_Func_voidstar_voidstar_FFI>(
            TabBar_flutter.tabAt_calledFromC, callbackExcept1034);
    registerCallback(thisCpp, callback1034, 1034);
    final callback1035 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_ffi_Int32_FFI>(
            TabBar_flutter.text_calledFromC);
    registerCallback(thisCpp, callback1035, 1035);
    final callback974 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback974, 974);
  }
}
