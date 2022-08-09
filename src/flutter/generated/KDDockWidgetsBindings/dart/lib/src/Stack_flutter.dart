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
  } // currentIndex() const

  int currentIndex() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(990))
        .asFunction();
    return func(thisCpp);
  }

  static int currentIndex_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::currentIndex() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.currentIndex();
    return result;
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
            cFunctionSymbolName(991))
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
  } // numDockWidgets() const

  int numDockWidgets() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(992))
        .asFunction();
    return func(thisCpp);
  }

  static int numDockWidgets_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::numDockWidgets() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.numDockWidgets();
    return result;
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

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
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
  } // renameTab(int index, const QString & arg__2)

  renameTab(int index, String? arg__2) {
    final void_Func_voidstar_int_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>>(
            cFunctionSymbolName(993))
        .asFunction();
    func(thisCpp, index, arg__2?.toNativeUtf8() ?? ffi.nullptr);
  }

  static void renameTab_calledFromC(
      ffi.Pointer<void> thisCpp, int index, ffi.Pointer<void>? arg__2) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::renameTab(int index, const QString & arg__2)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.renameTab(
        index, QString.fromCppPointer(arg__2).toDartString());
  } // setCurrentDockWidget(int index)

  setCurrentDockWidget(int index) {
    final void_Func_voidstar_int func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_ffi_Int32_FFI>>(
            cFunctionSymbolName(994))
        .asFunction();
    func(thisCpp, index);
  }

  static void setCurrentDockWidget_calledFromC(
      ffi.Pointer<void> thisCpp, int index) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as Stack_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Stack_flutter::setCurrentDockWidget(int index)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCurrentDockWidget(index);
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
            cFunctionSymbolName(995))
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
      case 848:
        return "c_KDDockWidgets__Views__Stack_flutter__activateWindow";
      case 856:
        return "c_KDDockWidgets__Views__Stack_flutter__close";
      case 859:
        return "c_KDDockWidgets__Views__Stack_flutter__createPlatformWindow";
      case 990:
        return "c_KDDockWidgets__Views__Stack_flutter__currentIndex";
      case 864:
        return "c_KDDockWidgets__Views__Stack_flutter__flags";
      case 866:
        return "c_KDDockWidgets__Views__Stack_flutter__free_impl";
      case 868:
        return "c_KDDockWidgets__Views__Stack_flutter__geometry";
      case 870:
        return "c_KDDockWidgets__Views__Stack_flutter__grabMouse";
      case 873:
        return "c_KDDockWidgets__Views__Stack_flutter__hasFocus";
      case 875:
        return "c_KDDockWidgets__Views__Stack_flutter__hide";
      case 878:
        return "c_KDDockWidgets__Views__Stack_flutter__init";
      case 880:
        return "c_KDDockWidgets__Views__Stack_flutter__isActiveWindow";
      case 881:
        return "c_KDDockWidgets__Views__Stack_flutter__isMaximized";
      case 882:
        return "c_KDDockWidgets__Views__Stack_flutter__isMinimized";
      case 883:
        return "c_KDDockWidgets__Views__Stack_flutter__isNull";
      case 991:
        return "c_KDDockWidgets__Views__Stack_flutter__isPositionDraggable_QPoint";
      case 884:
        return "c_KDDockWidgets__Views__Stack_flutter__isRootView";
      case 885:
        return "c_KDDockWidgets__Views__Stack_flutter__isVisible";
      case 886:
        return "c_KDDockWidgets__Views__Stack_flutter__mapFromGlobal_QPoint";
      case 887:
        return "c_KDDockWidgets__Views__Stack_flutter__mapTo_View_QPoint";
      case 888:
        return "c_KDDockWidgets__Views__Stack_flutter__mapToGlobal_QPoint";
      case 889:
        return "c_KDDockWidgets__Views__Stack_flutter__maxSizeHint";
      case 890:
        return "c_KDDockWidgets__Views__Stack_flutter__minSize";
      case 891:
        return "c_KDDockWidgets__Views__Stack_flutter__minimumHeight";
      case 892:
        return "c_KDDockWidgets__Views__Stack_flutter__minimumWidth";
      case 894:
        return "c_KDDockWidgets__Views__Stack_flutter__move_int_int";
      case 895:
        return "c_KDDockWidgets__Views__Stack_flutter__normalGeometry";
      case 992:
        return "c_KDDockWidgets__Views__Stack_flutter__numDockWidgets";
      case 896:
        return "c_KDDockWidgets__Views__Stack_flutter__objectName";
      case 898:
        return "c_KDDockWidgets__Views__Stack_flutter__onResize_int_int";
      case 901:
        return "c_KDDockWidgets__Views__Stack_flutter__raise";
      case 902:
        return "c_KDDockWidgets__Views__Stack_flutter__raiseAndActivate";
      case 904:
        return "c_KDDockWidgets__Views__Stack_flutter__releaseKeyboard";
      case 905:
        return "c_KDDockWidgets__Views__Stack_flutter__releaseMouse";
      case 993:
        return "c_KDDockWidgets__Views__Stack_flutter__renameTab_int_QString";
      case 994:
        return "c_KDDockWidgets__Views__Stack_flutter__setCurrentDockWidget_int";
      case 909:
        return "c_KDDockWidgets__Views__Stack_flutter__setCursor_CursorShape";
      case 995:
        return "c_KDDockWidgets__Views__Stack_flutter__setDocumentMode_bool";
      case 910:
        return "c_KDDockWidgets__Views__Stack_flutter__setFixedHeight_int";
      case 911:
        return "c_KDDockWidgets__Views__Stack_flutter__setFixedWidth_int";
      case 912:
        return "c_KDDockWidgets__Views__Stack_flutter__setGeometry_QRect";
      case 913:
        return "c_KDDockWidgets__Views__Stack_flutter__setHeight_int";
      case 914:
        return "c_KDDockWidgets__Views__Stack_flutter__setMaximumSize_QSize";
      case 915:
        return "c_KDDockWidgets__Views__Stack_flutter__setMinimumSize_QSize";
      case 916:
        return "c_KDDockWidgets__Views__Stack_flutter__setMouseTracking_bool";
      case 917:
        return "c_KDDockWidgets__Views__Stack_flutter__setObjectName_QString";
      case 918:
        return "c_KDDockWidgets__Views__Stack_flutter__setParent_View";
      case 920:
        return "c_KDDockWidgets__Views__Stack_flutter__setSize_int_int";
      case 921:
        return "c_KDDockWidgets__Views__Stack_flutter__setVisible_bool";
      case 922:
        return "c_KDDockWidgets__Views__Stack_flutter__setWidth_int";
      case 923:
        return "c_KDDockWidgets__Views__Stack_flutter__setWindowOpacity_double";
      case 924:
        return "c_KDDockWidgets__Views__Stack_flutter__setWindowTitle_QString";
      case 925:
        return "c_KDDockWidgets__Views__Stack_flutter__setZOrder_int";
      case 926:
        return "c_KDDockWidgets__Views__Stack_flutter__show";
      case 927:
        return "c_KDDockWidgets__Views__Stack_flutter__showMaximized";
      case 928:
        return "c_KDDockWidgets__Views__Stack_flutter__showMinimized";
      case 929:
        return "c_KDDockWidgets__Views__Stack_flutter__showNormal";
      case 931:
        return "c_KDDockWidgets__Views__Stack_flutter__sizeHint";
      case 933:
        return "c_KDDockWidgets__Views__Stack_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 848:
        return "activateWindow";
      case 856:
        return "close";
      case 859:
        return "createPlatformWindow";
      case 990:
        return "currentIndex";
      case 864:
        return "flags";
      case 866:
        return "free_impl";
      case 868:
        return "geometry";
      case 870:
        return "grabMouse";
      case 873:
        return "hasFocus";
      case 875:
        return "hide";
      case 878:
        return "init";
      case 880:
        return "isActiveWindow";
      case 881:
        return "isMaximized";
      case 882:
        return "isMinimized";
      case 883:
        return "isNull";
      case 991:
        return "isPositionDraggable";
      case 884:
        return "isRootView";
      case 885:
        return "isVisible";
      case 886:
        return "mapFromGlobal";
      case 887:
        return "mapTo";
      case 888:
        return "mapToGlobal";
      case 889:
        return "maxSizeHint";
      case 890:
        return "minSize";
      case 891:
        return "minimumHeight";
      case 892:
        return "minimumWidth";
      case 894:
        return "move_2";
      case 895:
        return "normalGeometry";
      case 992:
        return "numDockWidgets";
      case 896:
        return "objectName";
      case 898:
        return "onResize_2";
      case 901:
        return "raise";
      case 902:
        return "raiseAndActivate";
      case 904:
        return "releaseKeyboard";
      case 905:
        return "releaseMouse";
      case 993:
        return "renameTab";
      case 994:
        return "setCurrentDockWidget";
      case 909:
        return "setCursor";
      case 995:
        return "setDocumentMode";
      case 910:
        return "setFixedHeight";
      case 911:
        return "setFixedWidth";
      case 912:
        return "setGeometry";
      case 913:
        return "setHeight";
      case 914:
        return "setMaximumSize";
      case 915:
        return "setMinimumSize";
      case 916:
        return "setMouseTracking";
      case 917:
        return "setObjectName";
      case 918:
        return "setParent";
      case 920:
        return "setSize_2";
      case 921:
        return "setVisible";
      case 922:
        return "setWidth";
      case 923:
        return "setWindowOpacity";
      case 924:
        return "setWindowTitle";
      case 925:
        return "setZOrder";
      case 926:
        return "show";
      case 927:
        return "showMaximized";
      case 928:
        return "showMinimized";
      case 929:
        return "showNormal";
      case 931:
        return "sizeHint";
      case 933:
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
    final callback848 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback848, 848);
    const callbackExcept856 = 0;
    final callback856 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept856);
    registerCallback(thisCpp, callback856, 856);
    final callback859 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback859, 859);
    const callbackExcept990 = 0;
    final callback990 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Stack_flutter.currentIndex_calledFromC, callbackExcept990);
    registerCallback(thisCpp, callback990, 990);
    const callbackExcept864 = 0;
    final callback864 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept864);
    registerCallback(thisCpp, callback864, 864);
    final callback866 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback866, 866);
    final callback868 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback868, 868);
    final callback870 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback870, 870);
    const callbackExcept873 = 0;
    final callback873 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept873);
    registerCallback(thisCpp, callback873, 873);
    final callback875 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback875, 875);
    final callback878 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        Stack_flutter.init_calledFromC);
    registerCallback(thisCpp, callback878, 878);
    const callbackExcept880 = 0;
    final callback880 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept880);
    registerCallback(thisCpp, callback880, 880);
    const callbackExcept881 = 0;
    final callback881 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept881);
    registerCallback(thisCpp, callback881, 881);
    const callbackExcept882 = 0;
    final callback882 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept882);
    registerCallback(thisCpp, callback882, 882);
    const callbackExcept883 = 0;
    final callback883 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept883);
    registerCallback(thisCpp, callback883, 883);
    const callbackExcept991 = 0;
    final callback991 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            Stack_flutter.isPositionDraggable_calledFromC, callbackExcept991);
    registerCallback(thisCpp, callback991, 991);
    const callbackExcept884 = 0;
    final callback884 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept884);
    registerCallback(thisCpp, callback884, 884);
    const callbackExcept885 = 0;
    final callback885 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept885);
    registerCallback(thisCpp, callback885, 885);
    final callback886 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback886, 886);
    final callback887 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback887, 887);
    final callback888 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback888, 888);
    final callback889 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback889, 889);
    final callback890 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback890, 890);
    const callbackExcept891 = 0;
    final callback891 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept891);
    registerCallback(thisCpp, callback891, 891);
    const callbackExcept892 = 0;
    final callback892 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept892);
    registerCallback(thisCpp, callback892, 892);
    final callback894 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback894, 894);
    final callback895 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback895, 895);
    const callbackExcept992 = 0;
    final callback992 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        Stack_flutter.numDockWidgets_calledFromC, callbackExcept992);
    registerCallback(thisCpp, callback992, 992);
    final callback896 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback896, 896);
    const callbackExcept898 = 0;
    final callback898 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View.onResize_2_calledFromC, callbackExcept898);
    registerCallback(thisCpp, callback898, 898);
    final callback901 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback901, 901);
    final callback902 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback902, 902);
    final callback904 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback904, 904);
    final callback905 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback905, 905);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_voidstar_FFI>(
            Stack_flutter.renameTab_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            Stack_flutter.setCurrentDockWidget_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback909 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback995 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            Stack_flutter.setDocumentMode_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback910 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback911 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    final callback912 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    final callback913 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback913, 913);
    final callback914 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback914, 914);
    final callback915 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback915, 915);
    final callback916 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback917 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback917, 917);
    final callback918 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback918, 918);
    final callback920 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback920, 920);
    final callback921 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback921, 921);
    final callback922 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback922, 922);
    final callback923 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback923, 923);
    final callback924 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback924, 924);
    final callback925 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback925, 925);
    final callback926 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback926, 926);
    final callback927 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback927, 927);
    final callback928 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback928, 928);
    final callback929 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback929, 929);
    final callback931 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback931, 931);
    final callback933 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback933, 933);
  }
}
