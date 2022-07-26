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
      case 698:
        return "c_KDDockWidgets__Views__View_flutter__activateWindow";
      case 700:
        return "c_KDDockWidgets__Views__View_flutter__close";
      case 703:
        return "c_KDDockWidgets__Views__View_flutter__createPlatformWindow";
      case 707:
        return "c_KDDockWidgets__Views__View_flutter__free_impl";
      case 709:
        return "c_KDDockWidgets__Views__View_flutter__geometry";
      case 711:
        return "c_KDDockWidgets__Views__View_flutter__grabMouse";
      case 714:
        return "c_KDDockWidgets__Views__View_flutter__hasFocus";
      case 716:
        return "c_KDDockWidgets__Views__View_flutter__hide";
      case 719:
        return "c_KDDockWidgets__Views__View_flutter__init";
      case 720:
        return "c_KDDockWidgets__Views__View_flutter__isActiveWindow";
      case 721:
        return "c_KDDockWidgets__Views__View_flutter__isMaximized";
      case 722:
        return "c_KDDockWidgets__Views__View_flutter__isMinimized";
      case 723:
        return "c_KDDockWidgets__Views__View_flutter__isNull";
      case 724:
        return "c_KDDockWidgets__Views__View_flutter__isRootView";
      case 725:
        return "c_KDDockWidgets__Views__View_flutter__isVisible";
      case 726:
        return "c_KDDockWidgets__Views__View_flutter__mapFromGlobal_QPoint";
      case 727:
        return "c_KDDockWidgets__Views__View_flutter__mapTo_View_QPoint";
      case 728:
        return "c_KDDockWidgets__Views__View_flutter__mapToGlobal_QPoint";
      case 729:
        return "c_KDDockWidgets__Views__View_flutter__maxSizeHint";
      case 730:
        return "c_KDDockWidgets__Views__View_flutter__maximumSize";
      case 731:
        return "c_KDDockWidgets__Views__View_flutter__minSize";
      case 732:
        return "c_KDDockWidgets__Views__View_flutter__minimumHeight";
      case 733:
        return "c_KDDockWidgets__Views__View_flutter__minimumWidth";
      case 735:
        return "c_KDDockWidgets__Views__View_flutter__move_int_int";
      case 736:
        return "c_KDDockWidgets__Views__View_flutter__normalGeometry";
      case 737:
        return "c_KDDockWidgets__Views__View_flutter__objectName";
      case 738:
        return "c_KDDockWidgets__Views__View_flutter__onResize_QSize";
      case 741:
        return "c_KDDockWidgets__Views__View_flutter__raise";
      case 742:
        return "c_KDDockWidgets__Views__View_flutter__raiseAndActivate";
      case 744:
        return "c_KDDockWidgets__Views__View_flutter__releaseKeyboard";
      case 745:
        return "c_KDDockWidgets__Views__View_flutter__releaseMouse";
      case 749:
        return "c_KDDockWidgets__Views__View_flutter__setCursor_CursorShape";
      case 750:
        return "c_KDDockWidgets__Views__View_flutter__setFixedHeight_int";
      case 751:
        return "c_KDDockWidgets__Views__View_flutter__setFixedWidth_int";
      case 752:
        return "c_KDDockWidgets__Views__View_flutter__setGeometry_QRect";
      case 753:
        return "c_KDDockWidgets__Views__View_flutter__setHeight_int";
      case 754:
        return "c_KDDockWidgets__Views__View_flutter__setMaximumSize_QSize";
      case 755:
        return "c_KDDockWidgets__Views__View_flutter__setMinimumSize_QSize";
      case 756:
        return "c_KDDockWidgets__Views__View_flutter__setMouseTracking_bool";
      case 757:
        return "c_KDDockWidgets__Views__View_flutter__setObjectName_QString";
      case 758:
        return "c_KDDockWidgets__Views__View_flutter__setParent_View";
      case 760:
        return "c_KDDockWidgets__Views__View_flutter__setSize_int_int";
      case 761:
        return "c_KDDockWidgets__Views__View_flutter__setVisible_bool";
      case 762:
        return "c_KDDockWidgets__Views__View_flutter__setWidth_int";
      case 763:
        return "c_KDDockWidgets__Views__View_flutter__setWindowOpacity_double";
      case 764:
        return "c_KDDockWidgets__Views__View_flutter__setWindowTitle_QString";
      case 765:
        return "c_KDDockWidgets__Views__View_flutter__setZOrder_int";
      case 766:
        return "c_KDDockWidgets__Views__View_flutter__show";
      case 767:
        return "c_KDDockWidgets__Views__View_flutter__showMaximized";
      case 768:
        return "c_KDDockWidgets__Views__View_flutter__showMinimized";
      case 769:
        return "c_KDDockWidgets__Views__View_flutter__showNormal";
      case 771:
        return "c_KDDockWidgets__Views__View_flutter__sizeHint";
      case 772:
        return "c_KDDockWidgets__Views__View_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 698:
        return "activateWindow";
      case 700:
        return "close";
      case 703:
        return "createPlatformWindow";
      case 707:
        return "free_impl";
      case 709:
        return "geometry";
      case 711:
        return "grabMouse";
      case 714:
        return "hasFocus";
      case 716:
        return "hide";
      case 719:
        return "init";
      case 720:
        return "isActiveWindow";
      case 721:
        return "isMaximized";
      case 722:
        return "isMinimized";
      case 723:
        return "isNull";
      case 724:
        return "isRootView";
      case 725:
        return "isVisible";
      case 726:
        return "mapFromGlobal";
      case 727:
        return "mapTo";
      case 728:
        return "mapToGlobal";
      case 729:
        return "maxSizeHint";
      case 730:
        return "maximumSize";
      case 731:
        return "minSize";
      case 732:
        return "minimumHeight";
      case 733:
        return "minimumWidth";
      case 735:
        return "move_2";
      case 736:
        return "normalGeometry";
      case 737:
        return "objectName";
      case 738:
        return "onResize";
      case 741:
        return "raise";
      case 742:
        return "raiseAndActivate";
      case 744:
        return "releaseKeyboard";
      case 745:
        return "releaseMouse";
      case 749:
        return "setCursor";
      case 750:
        return "setFixedHeight";
      case 751:
        return "setFixedWidth";
      case 752:
        return "setGeometry";
      case 753:
        return "setHeight";
      case 754:
        return "setMaximumSize";
      case 755:
        return "setMinimumSize";
      case 756:
        return "setMouseTracking";
      case 757:
        return "setObjectName";
      case 758:
        return "setParent";
      case 760:
        return "setSize_2";
      case 761:
        return "setVisible";
      case 762:
        return "setWidth";
      case 763:
        return "setWindowOpacity";
      case 764:
        return "setWindowTitle";
      case 765:
        return "setZOrder";
      case 766:
        return "show";
      case 767:
        return "showMaximized";
      case 768:
        return "showMinimized";
      case 769:
        return "showNormal";
      case 771:
        return "sizeHint";
      case 772:
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
    final callback698 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback698, 698);
    const callbackExcept700 = 0;
//tag=1021
    final callback700 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept700);
    registerCallback(thisCpp, callback700, 700);
//tag=1021
    final callback703 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback703, 703);
//tag=1021
    final callback707 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback707, 707);
//tag=1021
    final callback709 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback709, 709);
//tag=1021
    final callback711 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback711, 711);
    const callbackExcept714 = 0;
//tag=1021
    final callback714 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept714);
    registerCallback(thisCpp, callback714, 714);
//tag=1021
    final callback716 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback716, 716);
//tag=1021
    final callback719 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.init_calledFromC);
    registerCallback(thisCpp, callback719, 719);
    const callbackExcept720 = 0;
//tag=1021
    final callback720 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept720);
    registerCallback(thisCpp, callback720, 720);
    const callbackExcept721 = 0;
//tag=1021
    final callback721 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept721);
    registerCallback(thisCpp, callback721, 721);
    const callbackExcept722 = 0;
//tag=1021
    final callback722 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept722);
    registerCallback(thisCpp, callback722, 722);
    const callbackExcept723 = 0;
//tag=1021
    final callback723 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept723);
    registerCallback(thisCpp, callback723, 723);
    const callbackExcept724 = 0;
//tag=1021
    final callback724 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept724);
    registerCallback(thisCpp, callback724, 724);
    const callbackExcept725 = 0;
//tag=1021
    final callback725 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept725);
    registerCallback(thisCpp, callback725, 725);
//tag=1021
    final callback726 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback726, 726);
//tag=1021
    final callback727 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback727, 727);
//tag=1021
    final callback728 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback728, 728);
//tag=1021
    final callback729 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback729, 729);
//tag=1021
    final callback730 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maximumSize_calledFromC);
    registerCallback(thisCpp, callback730, 730);
//tag=1021
    final callback731 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback731, 731);
    const callbackExcept732 = 0;
//tag=1021
    final callback732 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept732);
    registerCallback(thisCpp, callback732, 732);
    const callbackExcept733 = 0;
//tag=1021
    final callback733 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept733);
    registerCallback(thisCpp, callback733, 733);
//tag=1021
    final callback735 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback735, 735);
//tag=1021
    final callback736 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback736, 736);
//tag=1021
    final callback737 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback737, 737);
    const callbackExcept738 = 0;
//tag=1021
    final callback738 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            View.onResize_calledFromC, callbackExcept738);
    registerCallback(thisCpp, callback738, 738);
//tag=1021
    final callback741 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback741, 741);
//tag=1021
    final callback742 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback742, 742);
//tag=1021
    final callback744 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback744, 744);
//tag=1021
    final callback745 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback745, 745);
//tag=1021
    final callback749 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback749, 749);
//tag=1021
    final callback750 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback750, 750);
//tag=1021
    final callback751 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback751, 751);
//tag=1021
    final callback752 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback752, 752);
//tag=1021
    final callback753 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback753, 753);
//tag=1021
    final callback754 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback754, 754);
//tag=1021
    final callback755 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback755, 755);
//tag=1021
    final callback756 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback756, 756);
//tag=1021
    final callback757 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback757, 757);
//tag=1021
    final callback758 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback758, 758);
//tag=1021
    final callback760 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback760, 760);
//tag=1021
    final callback761 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback761, 761);
//tag=1021
    final callback762 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback762, 762);
//tag=1021
    final callback763 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback763, 763);
//tag=1021
    final callback764 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback764, 764);
//tag=1021
    final callback765 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback765, 765);
//tag=1021
    final callback766 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback766, 766);
//tag=1021
    final callback767 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback767, 767);
//tag=1021
    final callback768 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback768, 768);
//tag=1021
    final callback769 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback769, 769);
//tag=1021
    final callback771 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback771, 771);
//tag=1021
    final callback772 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback772, 772);
  }
}
