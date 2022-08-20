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

class Stack_flutter extends View_flutter {
  Stack_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Stack_flutter.init() : super.init() {}
  factory Stack_flutter.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (View.isCached(cppPointer)) {
      var instance = View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Stack_flutter;
    }
    return Stack_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  } //Stack_flutter(KDDockWidgets::Controllers::Stack * controller, KDDockWidgets::View * parent)
  Stack_flutter(Stack? controller, {required View? parent}) : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Views__Stack_flutter__constructor_Stack_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  } // isPositionDraggable(QPoint p) const

  bool isPositionDraggable(QPoint p) {
    final bool_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(990))
        .asFunction();
    return func(thisCpp, p == null ? ffi.nullptr : p.thisCpp) != 0;
  }

  static int isPositionDraggable_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> p) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isPositionDraggable(QPoint p) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isPositionDraggable(QPoint.fromCppPointer(p));
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        View.fromCppPointer(parent), QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::onChildAdded(KDDockWidgets::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded(View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::onChildRemoved(KDDockWidgets::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved(View.fromCppPointer(childView));
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::onResize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(w, h);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  } // setDocumentMode(bool arg__1)

  setDocumentMode(bool arg__1) {
    final void_Func_voidstar_bool func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int8_FFI>>(
            cFunctionSymbolName(991))
        .asFunction();
    func(thisCpp, arg__1 ? 1 : 0);
  }

  static void setDocumentMode_calledFromC(
      ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setDocumentMode(bool arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setDocumentMode(arg__1 != 0);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setParent(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent(View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__Stack_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 840:
        return "c_KDDockWidgets__Views__Stack_flutter__activateWindow";
      case 850:
        return "c_KDDockWidgets__Views__Stack_flutter__close";
      case 853:
        return "c_KDDockWidgets__Views__Stack_flutter__createPlatformWindow";
      case 858:
        return "c_KDDockWidgets__Views__Stack_flutter__flags";
      case 860:
        return "c_KDDockWidgets__Views__Stack_flutter__free_impl";
      case 862:
        return "c_KDDockWidgets__Views__Stack_flutter__geometry";
      case 864:
        return "c_KDDockWidgets__Views__Stack_flutter__grabMouse";
      case 867:
        return "c_KDDockWidgets__Views__Stack_flutter__hasFocus";
      case 869:
        return "c_KDDockWidgets__Views__Stack_flutter__hide";
      case 872:
        return "c_KDDockWidgets__Views__Stack_flutter__init";
      case 874:
        return "c_KDDockWidgets__Views__Stack_flutter__isActiveWindow";
      case 875:
        return "c_KDDockWidgets__Views__Stack_flutter__isMaximized";
      case 876:
        return "c_KDDockWidgets__Views__Stack_flutter__isMinimized";
      case 877:
        return "c_KDDockWidgets__Views__Stack_flutter__isNull";
      case 990:
        return "c_KDDockWidgets__Views__Stack_flutter__isPositionDraggable_QPoint";
      case 878:
        return "c_KDDockWidgets__Views__Stack_flutter__isRootView";
      case 879:
        return "c_KDDockWidgets__Views__Stack_flutter__isVisible";
      case 880:
        return "c_KDDockWidgets__Views__Stack_flutter__mapFromGlobal_QPoint";
      case 881:
        return "c_KDDockWidgets__Views__Stack_flutter__mapTo_View_QPoint";
      case 882:
        return "c_KDDockWidgets__Views__Stack_flutter__mapToGlobal_QPoint";
      case 883:
        return "c_KDDockWidgets__Views__Stack_flutter__maxSizeHint";
      case 884:
        return "c_KDDockWidgets__Views__Stack_flutter__minSize";
      case 885:
        return "c_KDDockWidgets__Views__Stack_flutter__minimumHeight";
      case 886:
        return "c_KDDockWidgets__Views__Stack_flutter__minimumWidth";
      case 888:
        return "c_KDDockWidgets__Views__Stack_flutter__move_int_int";
      case 889:
        return "c_KDDockWidgets__Views__Stack_flutter__normalGeometry";
      case 890:
        return "c_KDDockWidgets__Views__Stack_flutter__objectName";
      case 956:
        return "c_KDDockWidgets__Views__Stack_flutter__onChildAdded_View";
      case 957:
        return "c_KDDockWidgets__Views__Stack_flutter__onChildRemoved_View";
      case 892:
        return "c_KDDockWidgets__Views__Stack_flutter__onResize_int_int";
      case 895:
        return "c_KDDockWidgets__Views__Stack_flutter__raise";
      case 896:
        return "c_KDDockWidgets__Views__Stack_flutter__raiseAndActivate";
      case 898:
        return "c_KDDockWidgets__Views__Stack_flutter__releaseKeyboard";
      case 899:
        return "c_KDDockWidgets__Views__Stack_flutter__releaseMouse";
      case 903:
        return "c_KDDockWidgets__Views__Stack_flutter__setCursor_CursorShape";
      case 991:
        return "c_KDDockWidgets__Views__Stack_flutter__setDocumentMode_bool";
      case 904:
        return "c_KDDockWidgets__Views__Stack_flutter__setFixedHeight_int";
      case 905:
        return "c_KDDockWidgets__Views__Stack_flutter__setFixedWidth_int";
      case 906:
        return "c_KDDockWidgets__Views__Stack_flutter__setGeometry_QRect";
      case 907:
        return "c_KDDockWidgets__Views__Stack_flutter__setHeight_int";
      case 908:
        return "c_KDDockWidgets__Views__Stack_flutter__setMaximumSize_QSize";
      case 909:
        return "c_KDDockWidgets__Views__Stack_flutter__setMinimumSize_QSize";
      case 910:
        return "c_KDDockWidgets__Views__Stack_flutter__setMouseTracking_bool";
      case 911:
        return "c_KDDockWidgets__Views__Stack_flutter__setObjectName_QString";
      case 912:
        return "c_KDDockWidgets__Views__Stack_flutter__setParent_View";
      case 914:
        return "c_KDDockWidgets__Views__Stack_flutter__setSize_int_int";
      case 915:
        return "c_KDDockWidgets__Views__Stack_flutter__setVisible_bool";
      case 916:
        return "c_KDDockWidgets__Views__Stack_flutter__setWidth_int";
      case 917:
        return "c_KDDockWidgets__Views__Stack_flutter__setWindowOpacity_double";
      case 918:
        return "c_KDDockWidgets__Views__Stack_flutter__setWindowTitle_QString";
      case 919:
        return "c_KDDockWidgets__Views__Stack_flutter__setZOrder_int";
      case 920:
        return "c_KDDockWidgets__Views__Stack_flutter__show";
      case 921:
        return "c_KDDockWidgets__Views__Stack_flutter__showMaximized";
      case 922:
        return "c_KDDockWidgets__Views__Stack_flutter__showMinimized";
      case 923:
        return "c_KDDockWidgets__Views__Stack_flutter__showNormal";
      case 925:
        return "c_KDDockWidgets__Views__Stack_flutter__sizeHint";
      case 927:
        return "c_KDDockWidgets__Views__Stack_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 840:
        return "activateWindow";
      case 850:
        return "close";
      case 853:
        return "createPlatformWindow";
      case 858:
        return "flags";
      case 860:
        return "free_impl";
      case 862:
        return "geometry";
      case 864:
        return "grabMouse";
      case 867:
        return "hasFocus";
      case 869:
        return "hide";
      case 872:
        return "init";
      case 874:
        return "isActiveWindow";
      case 875:
        return "isMaximized";
      case 876:
        return "isMinimized";
      case 877:
        return "isNull";
      case 990:
        return "isPositionDraggable";
      case 878:
        return "isRootView";
      case 879:
        return "isVisible";
      case 880:
        return "mapFromGlobal";
      case 881:
        return "mapTo";
      case 882:
        return "mapToGlobal";
      case 883:
        return "maxSizeHint";
      case 884:
        return "minSize";
      case 885:
        return "minimumHeight";
      case 886:
        return "minimumWidth";
      case 888:
        return "move_2";
      case 889:
        return "normalGeometry";
      case 890:
        return "objectName";
      case 956:
        return "onChildAdded";
      case 957:
        return "onChildRemoved";
      case 892:
        return "onResize_2";
      case 895:
        return "raise";
      case 896:
        return "raiseAndActivate";
      case 898:
        return "releaseKeyboard";
      case 899:
        return "releaseMouse";
      case 903:
        return "setCursor";
      case 991:
        return "setDocumentMode";
      case 904:
        return "setFixedHeight";
      case 905:
        return "setFixedWidth";
      case 906:
        return "setGeometry";
      case 907:
        return "setHeight";
      case 908:
        return "setMaximumSize";
      case 909:
        return "setMinimumSize";
      case 910:
        return "setMouseTracking";
      case 911:
        return "setObjectName";
      case 912:
        return "setParent";
      case 914:
        return "setSize_2";
      case 915:
        return "setVisible";
      case 916:
        return "setWidth";
      case 917:
        return "setWindowOpacity";
      case 918:
        return "setWindowTitle";
      case 919:
        return "setZOrder";
      case 920:
        return "show";
      case 921:
        return "showMaximized";
      case 922:
        return "showMinimized";
      case 923:
        return "showNormal";
      case 925:
        return "sizeHint";
      case 927:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Views__Stack_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback840 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback840, 840);
    const callbackExcept850 = 0;
    final callback850 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept850);
    registerCallback(thisCpp, callback850, 850);
    final callback853 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback853, 853);
    const callbackExcept858 = 0;
    final callback858 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept858);
    registerCallback(thisCpp, callback858, 858);
    final callback860 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback860, 860);
    final callback862 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback862, 862);
    final callback864 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback864, 864);
    const callbackExcept867 = 0;
    final callback867 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept867);
    registerCallback(thisCpp, callback867, 867);
    final callback869 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback869, 869);
    final callback872 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Stack_flutter.init_calledFromC);
    registerCallback(thisCpp, callback872, 872);
    const callbackExcept874 = 0;
    final callback874 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept874);
    registerCallback(thisCpp, callback874, 874);
    const callbackExcept875 = 0;
    final callback875 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept875);
    registerCallback(thisCpp, callback875, 875);
    const callbackExcept876 = 0;
    final callback876 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept876);
    registerCallback(thisCpp, callback876, 876);
    const callbackExcept877 = 0;
    final callback877 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept877);
    registerCallback(thisCpp, callback877, 877);
    const callbackExcept990 = 0;
    final callback990 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Stack_flutter.isPositionDraggable_calledFromC, callbackExcept990);
    registerCallback(thisCpp, callback990, 990);
    const callbackExcept878 = 0;
    final callback878 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept878);
    registerCallback(thisCpp, callback878, 878);
    const callbackExcept879 = 0;
    final callback879 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept879);
    registerCallback(thisCpp, callback879, 879);
    final callback880 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback880, 880);
    final callback881 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback881, 881);
    final callback882 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback882, 882);
    final callback883 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback883, 883);
    final callback884 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback884, 884);
    const callbackExcept885 = 0;
    final callback885 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept885);
    registerCallback(thisCpp, callback885, 885);
    const callbackExcept886 = 0;
    final callback886 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept886);
    registerCallback(thisCpp, callback886, 886);
    final callback888 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback888, 888);
    final callback889 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback889, 889);
    final callback890 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback890, 890);
    final callback956 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback956, 956);
    final callback957 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    const callbackExcept892 = 0;
    final callback892 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.onResize_2_calledFromC, callbackExcept892);
    registerCallback(thisCpp, callback892, 892);
    final callback895 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback895, 895);
    final callback896 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback896, 896);
    final callback898 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback898, 898);
    final callback899 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback899, 899);
    final callback903 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback903, 903);
    final callback991 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            Stack_flutter.setDocumentMode_calledFromC);
    registerCallback(thisCpp, callback991, 991);
    final callback904 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback904, 904);
    final callback905 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback905, 905);
    final callback906 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback906, 906);
    final callback907 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback908 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback908, 908);
    final callback909 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback910 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback911 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    final callback912 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    final callback914 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback914, 914);
    final callback915 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback915, 915);
    final callback916 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback917 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback917, 917);
    final callback918 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback918, 918);
    final callback919 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback919, 919);
    final callback920 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback920, 920);
    final callback921 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback921, 921);
    final callback922 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback922, 922);
    final callback923 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback923, 923);
    final callback925 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback925, 925);
    final callback927 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback927, 927);
  }
}
