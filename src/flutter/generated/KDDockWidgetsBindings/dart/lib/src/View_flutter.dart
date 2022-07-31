/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1052
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

//tag=1051
var _dylib = Library.instance().dylib;

class View_flutter extends View {
//tag=1064
  View_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  View_flutter.init() : super.init() {}
//tag=1062
  factory View_flutter.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (View.isCached(cppPointer)) {
      var instance = View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as View_flutter;
    }
    return View_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  }
//tag=1023
//View_flutter(KDDockWidgets::Controller * controller, KDDockWidgets::Type type, KDDockWidgets::View * arg__3, Qt::WindowFlags windowFlags)
  View_flutter(Controller? controller, int type, View? arg__3,
      {int windowFlags = 0})
      : super.init() {
//tag=1075
    final voidstar_Func_voidstar_int_voidstar_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_voidstar_ffi_Int32_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__constructor_Controller_Type_View_WindowFlags')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp, type,
        arg__3 == null ? ffi.nullptr : arg__3.thisCpp, windowFlags);
    View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
//tag=1024

//tag=1035
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.activateWindow();
  }
//tag=1024

//tag=1035
  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::close()! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.close();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.createPlatformWindow();
  }
//tag=1024

//tag=1035
  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::flags() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.flags();
    return result;
  }
//tag=1024

//tag=1035
  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::free_impl()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.free_impl();
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::geometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.geometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.grabMouse();
  }
//tag=1024

//tag=1035
  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::hide()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.hide();
  }
//tag=1024

//tag=1035
  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::init()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.init();
  }
//tag=1024

//tag=1035
  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isNull() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.mapTo(
        View.fromCppPointer(parent), QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> maximumSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::maximumSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.maximumSize();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::minSize() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minSize();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minimumHeight();
    return result;
  }
//tag=1024

//tag=1035
  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.minimumWidth();
    return result;
  }
//tag=1024

//tag=1035
  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.move_2(x, y);
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::objectName() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.objectName();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static int onResize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> newSize) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::onResize(QSize newSize)! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.onResize(QSize.fromCppPointer(newSize));
    return result ? 1 : 0;
  }
//tag=1024

//tag=1035
  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::raise()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.raise();
  }
//tag=1024

//tag=1035
  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.raiseAndActivate();
  }
//tag=1024

//tag=1035
  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.releaseKeyboard();
  }
//tag=1024

//tag=1035
  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.releaseMouse();
  }
//tag=1024

//tag=1035
  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setCursor(shape);
  }
//tag=1024

//tag=1035
  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setFixedHeight(h);
  }
//tag=1024

//tag=1035
  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setFixedWidth(w);
  }
//tag=1024

//tag=1035
  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  }
//tag=1024

//tag=1035
  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setHeight(h);
  }
//tag=1024

//tag=1035
  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }
//tag=1024

//tag=1035
  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }
//tag=1024

//tag=1035
  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setMouseTracking(enable != 0);
  }
//tag=1024

//tag=1027
// setNormalGeometry(QRect geo)
  setNormalGeometry(QRect geo) {
//tag=1028
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__setNormalGeometry_QRect')
        .asFunction();
//tag=1030
    func(thisCpp, geo == null ? ffi.nullptr : geo.thisCpp);
  }
//tag=1024

//tag=1035
  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }
//tag=1024

//tag=1035
  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setParent(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setParent(View.fromCppPointer(parent));
  }
//tag=1024

//tag=1035
  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setSize_2(w, h);
  }
//tag=1024

//tag=1035
  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setVisible(visible != 0);
  }
//tag=1024

//tag=1035
  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setWidth(w);
  }
//tag=1024

//tag=1035
  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setWindowOpacity(v);
  }
//tag=1024

//tag=1035
  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }
//tag=1024

//tag=1035
  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setZOrder(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.setZOrder(arg__1);
  }
//tag=1024

//tag=1035
  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::show()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.show();
  }
//tag=1024

//tag=1035
  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.showMaximized();
  }
//tag=1024

//tag=1035
  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.showMinimized();
  }
//tag=1024

//tag=1035
  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::showNormal()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.showNormal();
  }
//tag=1024

//tag=1035
  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
//tag=1037
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }
//tag=1024

//tag=1035
  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::update()! (${thisCpp.address})");
      throw Error();
    }
//tag=1036
    dartInstance.update();
  }
//tag=1024

//tag=1027
// updateGeometry()
  updateGeometry() {
//tag=1028
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__updateGeometry')
        .asFunction();
//tag=1030
    func(thisCpp);
  }

//tag=1022
  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

//tag=1019
  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 733:
        return "c_KDDockWidgets__Views__View_flutter__activateWindow";
      case 737:
        return "c_KDDockWidgets__Views__View_flutter__close";
      case 740:
        return "c_KDDockWidgets__Views__View_flutter__createPlatformWindow";
      case 745:
        return "c_KDDockWidgets__Views__View_flutter__flags";
      case 747:
        return "c_KDDockWidgets__Views__View_flutter__free_impl";
      case 749:
        return "c_KDDockWidgets__Views__View_flutter__geometry";
      case 751:
        return "c_KDDockWidgets__Views__View_flutter__grabMouse";
      case 754:
        return "c_KDDockWidgets__Views__View_flutter__hasFocus";
      case 756:
        return "c_KDDockWidgets__Views__View_flutter__hide";
      case 759:
        return "c_KDDockWidgets__Views__View_flutter__init";
      case 761:
        return "c_KDDockWidgets__Views__View_flutter__isActiveWindow";
      case 762:
        return "c_KDDockWidgets__Views__View_flutter__isMaximized";
      case 763:
        return "c_KDDockWidgets__Views__View_flutter__isMinimized";
      case 764:
        return "c_KDDockWidgets__Views__View_flutter__isNull";
      case 765:
        return "c_KDDockWidgets__Views__View_flutter__isRootView";
      case 766:
        return "c_KDDockWidgets__Views__View_flutter__isVisible";
      case 767:
        return "c_KDDockWidgets__Views__View_flutter__mapFromGlobal_QPoint";
      case 768:
        return "c_KDDockWidgets__Views__View_flutter__mapTo_View_QPoint";
      case 769:
        return "c_KDDockWidgets__Views__View_flutter__mapToGlobal_QPoint";
      case 770:
        return "c_KDDockWidgets__Views__View_flutter__maxSizeHint";
      case 771:
        return "c_KDDockWidgets__Views__View_flutter__maximumSize";
      case 772:
        return "c_KDDockWidgets__Views__View_flutter__minSize";
      case 773:
        return "c_KDDockWidgets__Views__View_flutter__minimumHeight";
      case 774:
        return "c_KDDockWidgets__Views__View_flutter__minimumWidth";
      case 776:
        return "c_KDDockWidgets__Views__View_flutter__move_int_int";
      case 777:
        return "c_KDDockWidgets__Views__View_flutter__normalGeometry";
      case 778:
        return "c_KDDockWidgets__Views__View_flutter__objectName";
      case 779:
        return "c_KDDockWidgets__Views__View_flutter__onResize_QSize";
      case 782:
        return "c_KDDockWidgets__Views__View_flutter__raise";
      case 783:
        return "c_KDDockWidgets__Views__View_flutter__raiseAndActivate";
      case 785:
        return "c_KDDockWidgets__Views__View_flutter__releaseKeyboard";
      case 786:
        return "c_KDDockWidgets__Views__View_flutter__releaseMouse";
      case 790:
        return "c_KDDockWidgets__Views__View_flutter__setCursor_CursorShape";
      case 791:
        return "c_KDDockWidgets__Views__View_flutter__setFixedHeight_int";
      case 792:
        return "c_KDDockWidgets__Views__View_flutter__setFixedWidth_int";
      case 793:
        return "c_KDDockWidgets__Views__View_flutter__setGeometry_QRect";
      case 794:
        return "c_KDDockWidgets__Views__View_flutter__setHeight_int";
      case 795:
        return "c_KDDockWidgets__Views__View_flutter__setMaximumSize_QSize";
      case 796:
        return "c_KDDockWidgets__Views__View_flutter__setMinimumSize_QSize";
      case 797:
        return "c_KDDockWidgets__Views__View_flutter__setMouseTracking_bool";
      case 798:
        return "c_KDDockWidgets__Views__View_flutter__setObjectName_QString";
      case 799:
        return "c_KDDockWidgets__Views__View_flutter__setParent_View";
      case 801:
        return "c_KDDockWidgets__Views__View_flutter__setSize_int_int";
      case 802:
        return "c_KDDockWidgets__Views__View_flutter__setVisible_bool";
      case 803:
        return "c_KDDockWidgets__Views__View_flutter__setWidth_int";
      case 804:
        return "c_KDDockWidgets__Views__View_flutter__setWindowOpacity_double";
      case 805:
        return "c_KDDockWidgets__Views__View_flutter__setWindowTitle_QString";
      case 806:
        return "c_KDDockWidgets__Views__View_flutter__setZOrder_int";
      case 807:
        return "c_KDDockWidgets__Views__View_flutter__show";
      case 808:
        return "c_KDDockWidgets__Views__View_flutter__showMaximized";
      case 809:
        return "c_KDDockWidgets__Views__View_flutter__showMinimized";
      case 810:
        return "c_KDDockWidgets__Views__View_flutter__showNormal";
      case 812:
        return "c_KDDockWidgets__Views__View_flutter__sizeHint";
      case 814:
        return "c_KDDockWidgets__Views__View_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 733:
        return "activateWindow";
      case 737:
        return "close";
      case 740:
        return "createPlatformWindow";
      case 745:
        return "flags";
      case 747:
        return "free_impl";
      case 749:
        return "geometry";
      case 751:
        return "grabMouse";
      case 754:
        return "hasFocus";
      case 756:
        return "hide";
      case 759:
        return "init";
      case 761:
        return "isActiveWindow";
      case 762:
        return "isMaximized";
      case 763:
        return "isMinimized";
      case 764:
        return "isNull";
      case 765:
        return "isRootView";
      case 766:
        return "isVisible";
      case 767:
        return "mapFromGlobal";
      case 768:
        return "mapTo";
      case 769:
        return "mapToGlobal";
      case 770:
        return "maxSizeHint";
      case 771:
        return "maximumSize";
      case 772:
        return "minSize";
      case 773:
        return "minimumHeight";
      case 774:
        return "minimumWidth";
      case 776:
        return "move_2";
      case 777:
        return "normalGeometry";
      case 778:
        return "objectName";
      case 779:
        return "onResize";
      case 782:
        return "raise";
      case 783:
        return "raiseAndActivate";
      case 785:
        return "releaseKeyboard";
      case 786:
        return "releaseMouse";
      case 790:
        return "setCursor";
      case 791:
        return "setFixedHeight";
      case 792:
        return "setFixedWidth";
      case 793:
        return "setGeometry";
      case 794:
        return "setHeight";
      case 795:
        return "setMaximumSize";
      case 796:
        return "setMinimumSize";
      case 797:
        return "setMouseTracking";
      case 798:
        return "setObjectName";
      case 799:
        return "setParent";
      case 801:
        return "setSize_2";
      case 802:
        return "setVisible";
      case 803:
        return "setWidth";
      case 804:
        return "setWindowOpacity";
      case 805:
        return "setWindowTitle";
      case 806:
        return "setZOrder";
      case 807:
        return "show";
      case 808:
        return "showMaximized";
      case 809:
        return "showMinimized";
      case 810:
        return "showNormal";
      case 812:
        return "sizeHint";
      case 814:
        return "update";
    }
    throw Error();
  }

//tag=1020
  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__registerVirtualMethodCallback')
        .asFunction();

//tag=1021
    final callback733 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback733, 733);
    const callbackExcept737 = 0;
//tag=1021
    final callback737 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept737);
    registerCallback(thisCpp, callback737, 737);
//tag=1021
    final callback740 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback740, 740);
    const callbackExcept745 = 0;
//tag=1021
    final callback745 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept745);
    registerCallback(thisCpp, callback745, 745);
//tag=1021
    final callback747 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback747, 747);
//tag=1021
    final callback749 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback749, 749);
//tag=1021
    final callback751 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback751, 751);
    const callbackExcept754 = 0;
//tag=1021
    final callback754 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept754);
    registerCallback(thisCpp, callback754, 754);
//tag=1021
    final callback756 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback756, 756);
//tag=1021
    final callback759 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.init_calledFromC);
    registerCallback(thisCpp, callback759, 759);
    const callbackExcept761 = 0;
//tag=1021
    final callback761 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept761);
    registerCallback(thisCpp, callback761, 761);
    const callbackExcept762 = 0;
//tag=1021
    final callback762 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept762);
    registerCallback(thisCpp, callback762, 762);
    const callbackExcept763 = 0;
//tag=1021
    final callback763 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept763);
    registerCallback(thisCpp, callback763, 763);
    const callbackExcept764 = 0;
//tag=1021
    final callback764 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept764);
    registerCallback(thisCpp, callback764, 764);
    const callbackExcept765 = 0;
//tag=1021
    final callback765 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept765);
    registerCallback(thisCpp, callback765, 765);
    const callbackExcept766 = 0;
//tag=1021
    final callback766 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept766);
    registerCallback(thisCpp, callback766, 766);
//tag=1021
    final callback767 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback767, 767);
//tag=1021
    final callback768 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback768, 768);
//tag=1021
    final callback769 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback769, 769);
//tag=1021
    final callback770 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback770, 770);
//tag=1021
    final callback771 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maximumSize_calledFromC);
    registerCallback(thisCpp, callback771, 771);
//tag=1021
    final callback772 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback772, 772);
    const callbackExcept773 = 0;
//tag=1021
    final callback773 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept773);
    registerCallback(thisCpp, callback773, 773);
    const callbackExcept774 = 0;
//tag=1021
    final callback774 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept774);
    registerCallback(thisCpp, callback774, 774);
//tag=1021
    final callback776 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback776, 776);
//tag=1021
    final callback777 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback777, 777);
//tag=1021
    final callback778 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback778, 778);
    const callbackExcept779 = 0;
//tag=1021
    final callback779 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            View.onResize_calledFromC, callbackExcept779);
    registerCallback(thisCpp, callback779, 779);
//tag=1021
    final callback782 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback782, 782);
//tag=1021
    final callback783 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback783, 783);
//tag=1021
    final callback785 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback785, 785);
//tag=1021
    final callback786 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback786, 786);
//tag=1021
    final callback790 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback790, 790);
//tag=1021
    final callback791 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback791, 791);
//tag=1021
    final callback792 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback792, 792);
//tag=1021
    final callback793 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback793, 793);
//tag=1021
    final callback794 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback794, 794);
//tag=1021
    final callback795 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback795, 795);
//tag=1021
    final callback796 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback796, 796);
//tag=1021
    final callback797 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback797, 797);
//tag=1021
    final callback798 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback798, 798);
//tag=1021
    final callback799 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback799, 799);
//tag=1021
    final callback801 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback801, 801);
//tag=1021
    final callback802 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback802, 802);
//tag=1021
    final callback803 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback803, 803);
//tag=1021
    final callback804 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback804, 804);
//tag=1021
    final callback805 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback805, 805);
//tag=1021
    final callback806 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback806, 806);
//tag=1021
    final callback807 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback807, 807);
//tag=1021
    final callback808 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback808, 808);
//tag=1021
    final callback809 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback809, 809);
//tag=1021
    final callback810 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback810, 810);
//tag=1021
    final callback812 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback812, 812);
//tag=1021
    final callback814 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback814, 814);
  }
}
