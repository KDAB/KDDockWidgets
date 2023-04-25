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

class Stack extends KDDWBindingsFlutter.View {
  Stack.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Stack.init() : super.init() {}
  factory Stack.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Stack;
    }
    return Stack.fromCppPointer(cppPointer, needsAutoDelete);
  } //Stack(KDDockWidgets::Core::Stack * controller, KDDockWidgets::Core::View * parent)
  Stack(KDDWBindingsCore.Stack? controller,
      {required KDDWBindingsCore.View? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Stack__constructor_Stack_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print("Dart instance not found for Stack::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print("Dart instance not found for Stack::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print("Dart instance not found for Stack::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  } // isPositionDraggable(QPoint p) const

  bool isPositionDraggable(QPoint p) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1039))
        .asFunction();
    return func(thisCpp, p == null ? ffi.nullptr : p.thisCpp) != 0;
  }

  static int isPositionDraggable_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> p) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isPositionDraggable(QPoint p) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isPositionDraggable(QPoint.fromCppPointer(p));
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        KDDWBindingsCore.View.fromCppPointer(parent),
        QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded(KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance
        .onChildRemoved(KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::onResize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(w, h);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print("Dart instance not found for Stack::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  } // setDocumentMode(bool arg__1)

  setDocumentMode(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(1040))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setDocumentMode_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setDocumentMode(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setDocumentMode(arg__1 != 0);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent(KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print("Dart instance not found for Stack::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Stack;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Stack__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 887:
        return "c_KDDockWidgets__flutter__Stack__activateWindow";
      case 898:
        return "c_KDDockWidgets__flutter__Stack__close";
      case 901:
        return "c_KDDockWidgets__flutter__Stack__createPlatformWindow";
      case 906:
        return "c_KDDockWidgets__flutter__Stack__flags";
      case 908:
        return "c_KDDockWidgets__flutter__Stack__free_impl";
      case 910:
        return "c_KDDockWidgets__flutter__Stack__geometry";
      case 912:
        return "c_KDDockWidgets__flutter__Stack__grabMouse";
      case 915:
        return "c_KDDockWidgets__flutter__Stack__hasFocus";
      case 917:
        return "c_KDDockWidgets__flutter__Stack__hide";
      case 920:
        return "c_KDDockWidgets__flutter__Stack__init";
      case 922:
        return "c_KDDockWidgets__flutter__Stack__isActiveWindow";
      case 923:
        return "c_KDDockWidgets__flutter__Stack__isMaximized";
      case 924:
        return "c_KDDockWidgets__flutter__Stack__isMinimized";
      case 925:
        return "c_KDDockWidgets__flutter__Stack__isNull";
      case 1039:
        return "c_KDDockWidgets__flutter__Stack__isPositionDraggable_QPoint";
      case 926:
        return "c_KDDockWidgets__flutter__Stack__isRootView";
      case 927:
        return "c_KDDockWidgets__flutter__Stack__isVisible";
      case 928:
        return "c_KDDockWidgets__flutter__Stack__mapFromGlobal_QPoint";
      case 929:
        return "c_KDDockWidgets__flutter__Stack__mapTo_View_QPoint";
      case 930:
        return "c_KDDockWidgets__flutter__Stack__mapToGlobal_QPoint";
      case 931:
        return "c_KDDockWidgets__flutter__Stack__maxSizeHint";
      case 932:
        return "c_KDDockWidgets__flutter__Stack__minSize";
      case 933:
        return "c_KDDockWidgets__flutter__Stack__minimumHeight";
      case 934:
        return "c_KDDockWidgets__flutter__Stack__minimumWidth";
      case 936:
        return "c_KDDockWidgets__flutter__Stack__move_int_int";
      case 937:
        return "c_KDDockWidgets__flutter__Stack__normalGeometry";
      case 938:
        return "c_KDDockWidgets__flutter__Stack__objectName";
      case 1005:
        return "c_KDDockWidgets__flutter__Stack__onChildAdded_View";
      case 1006:
        return "c_KDDockWidgets__flutter__Stack__onChildRemoved_View";
      case 940:
        return "c_KDDockWidgets__flutter__Stack__onResize_int_int";
      case 943:
        return "c_KDDockWidgets__flutter__Stack__raise";
      case 944:
        return "c_KDDockWidgets__flutter__Stack__raiseAndActivate";
      case 946:
        return "c_KDDockWidgets__flutter__Stack__releaseKeyboard";
      case 947:
        return "c_KDDockWidgets__flutter__Stack__releaseMouse";
      case 951:
        return "c_KDDockWidgets__flutter__Stack__setCursor_CursorShape";
      case 1040:
        return "c_KDDockWidgets__flutter__Stack__setDocumentMode_bool";
      case 952:
        return "c_KDDockWidgets__flutter__Stack__setFixedHeight_int";
      case 953:
        return "c_KDDockWidgets__flutter__Stack__setFixedWidth_int";
      case 954:
        return "c_KDDockWidgets__flutter__Stack__setGeometry_QRect";
      case 955:
        return "c_KDDockWidgets__flutter__Stack__setHeight_int";
      case 956:
        return "c_KDDockWidgets__flutter__Stack__setMaximumSize_QSize";
      case 957:
        return "c_KDDockWidgets__flutter__Stack__setMinimumSize_QSize";
      case 958:
        return "c_KDDockWidgets__flutter__Stack__setMouseTracking_bool";
      case 959:
        return "c_KDDockWidgets__flutter__Stack__setObjectName_QString";
      case 960:
        return "c_KDDockWidgets__flutter__Stack__setParent_View";
      case 962:
        return "c_KDDockWidgets__flutter__Stack__setSize_int_int";
      case 963:
        return "c_KDDockWidgets__flutter__Stack__setVisible_bool";
      case 964:
        return "c_KDDockWidgets__flutter__Stack__setWidth_int";
      case 965:
        return "c_KDDockWidgets__flutter__Stack__setWindowOpacity_double";
      case 966:
        return "c_KDDockWidgets__flutter__Stack__setWindowTitle_QString";
      case 967:
        return "c_KDDockWidgets__flutter__Stack__setZOrder_int";
      case 968:
        return "c_KDDockWidgets__flutter__Stack__show";
      case 969:
        return "c_KDDockWidgets__flutter__Stack__showMaximized";
      case 970:
        return "c_KDDockWidgets__flutter__Stack__showMinimized";
      case 971:
        return "c_KDDockWidgets__flutter__Stack__showNormal";
      case 973:
        return "c_KDDockWidgets__flutter__Stack__sizeHint";
      case 975:
        return "c_KDDockWidgets__flutter__Stack__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 887:
        return "activateWindow";
      case 898:
        return "close";
      case 901:
        return "createPlatformWindow";
      case 906:
        return "flags";
      case 908:
        return "free_impl";
      case 910:
        return "geometry";
      case 912:
        return "grabMouse";
      case 915:
        return "hasFocus";
      case 917:
        return "hide";
      case 920:
        return "init";
      case 922:
        return "isActiveWindow";
      case 923:
        return "isMaximized";
      case 924:
        return "isMinimized";
      case 925:
        return "isNull";
      case 1039:
        return "isPositionDraggable";
      case 926:
        return "isRootView";
      case 927:
        return "isVisible";
      case 928:
        return "mapFromGlobal";
      case 929:
        return "mapTo";
      case 930:
        return "mapToGlobal";
      case 931:
        return "maxSizeHint";
      case 932:
        return "minSize";
      case 933:
        return "minimumHeight";
      case 934:
        return "minimumWidth";
      case 936:
        return "move_2";
      case 937:
        return "normalGeometry";
      case 938:
        return "objectName";
      case 1005:
        return "onChildAdded";
      case 1006:
        return "onChildRemoved";
      case 940:
        return "onResize_2";
      case 943:
        return "raise";
      case 944:
        return "raiseAndActivate";
      case 946:
        return "releaseKeyboard";
      case 947:
        return "releaseMouse";
      case 951:
        return "setCursor";
      case 1040:
        return "setDocumentMode";
      case 952:
        return "setFixedHeight";
      case 953:
        return "setFixedWidth";
      case 954:
        return "setGeometry";
      case 955:
        return "setHeight";
      case 956:
        return "setMaximumSize";
      case 957:
        return "setMinimumSize";
      case 958:
        return "setMouseTracking";
      case 959:
        return "setObjectName";
      case 960:
        return "setParent";
      case 962:
        return "setSize_2";
      case 963:
        return "setVisible";
      case 964:
        return "setWidth";
      case 965:
        return "setWindowOpacity";
      case 966:
        return "setWindowTitle";
      case 967:
        return "setZOrder";
      case 968:
        return "show";
      case 969:
        return "showMaximized";
      case 970:
        return "showMinimized";
      case 971:
        return "showNormal";
      case 973:
        return "sizeHint";
      case 975:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__Stack__registerVirtualMethodCallback')
        .asFunction();
    final callback887 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback887, 887);
    const callbackExcept898 = 0;
    final callback898 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept898);
    registerCallback(thisCpp, callback898, 898);
    final callback901 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback901, 901);
    const callbackExcept906 = 0;
    final callback906 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept906);
    registerCallback(thisCpp, callback906, 906);
    final callback908 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.free_impl_calledFromC);
    registerCallback(thisCpp, callback908, 908);
    final callback910 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback912 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    const callbackExcept915 = 0;
    final callback915 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept915);
    registerCallback(thisCpp, callback915, 915);
    final callback917 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback917, 917);
    final callback920 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Stack.init_calledFromC);
    registerCallback(thisCpp, callback920, 920);
    const callbackExcept922 = 0;
    final callback922 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept922);
    registerCallback(thisCpp, callback922, 922);
    const callbackExcept923 = 0;
    final callback923 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept923);
    registerCallback(thisCpp, callback923, 923);
    const callbackExcept924 = 0;
    final callback924 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept924);
    registerCallback(thisCpp, callback924, 924);
    const callbackExcept925 = 0;
    final callback925 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept925);
    registerCallback(thisCpp, callback925, 925);
    const callbackExcept1039 = 0;
    final callback1039 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.Stack.isPositionDraggable_calledFromC,
            callbackExcept1039);
    registerCallback(thisCpp, callback1039, 1039);
    const callbackExcept926 = 0;
    final callback926 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept926);
    registerCallback(thisCpp, callback926, 926);
    const callbackExcept927 = 0;
    final callback927 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept927);
    registerCallback(thisCpp, callback927, 927);
    final callback928 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback928, 928);
    final callback929 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback929, 929);
    final callback930 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback930, 930);
    final callback931 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback931, 931);
    final callback932 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback932, 932);
    const callbackExcept933 = 0;
    final callback933 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept933);
    registerCallback(thisCpp, callback933, 933);
    const callbackExcept934 = 0;
    final callback934 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept934);
    registerCallback(thisCpp, callback934, 934);
    final callback936 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback936, 936);
    final callback937 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback937, 937);
    final callback938 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback938, 938);
    final callback1005 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
    final callback1006 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1006, 1006);
    const callbackExcept940 = 0;
    final callback940 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.onResize_2_calledFromC, callbackExcept940);
    registerCallback(thisCpp, callback940, 940);
    final callback943 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback943, 943);
    final callback944 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback944, 944);
    final callback946 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback947 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback947, 947);
    final callback951 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback951, 951);
    final callback1040 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.Stack.setDocumentMode_calledFromC);
    registerCallback(thisCpp, callback1040, 1040);
    final callback952 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback952, 952);
    final callback953 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback953, 953);
    final callback954 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback955 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback955, 955);
    final callback956 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback956, 956);
    final callback957 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    final callback958 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback958, 958);
    final callback959 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback960 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback960, 960);
    final callback962 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback962, 962);
    final callback963 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback963, 963);
    final callback964 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback964, 964);
    final callback965 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback967 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback969 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback969, 969);
    final callback970 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback970, 970);
    final callback971 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback971, 971);
    final callback973 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback973, 973);
    final callback975 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback975, 975);
  }
}
