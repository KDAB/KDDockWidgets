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

class TitleBar_flutter extends View_flutter {
  TitleBar_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  TitleBar_flutter.init() : super.init() {}
  factory TitleBar_flutter.fromCache(var cppPointer,
      [needsAutoDelete = false]) {
    if (View.isCached(cppPointer)) {
      var instance = View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as TitleBar_flutter;
    }
    return TitleBar_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  } //TitleBar_flutter(KDDockWidgets::Controllers::TitleBar * controller, KDDockWidgets::View * parent)
  TitleBar_flutter(TitleBar? controller, {required View? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Views__TitleBar_flutter__constructor_TitleBar_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  } // isCloseButtonEnabled() const

  bool isCloseButtonEnabled() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(958))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isCloseButtonEnabled_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isCloseButtonEnabled() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isCloseButtonEnabled();
    return result ? 1 : 0;
  } // isCloseButtonVisible() const

  bool isCloseButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(959))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isCloseButtonVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isCloseButtonVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isCloseButtonVisible();
    return result ? 1 : 0;
  } // isFloatButtonVisible() const

  bool isFloatButtonVisible() {
    final bool_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<bool_Func_voidstar_FFI>>(
            cFunctionSymbolName(960))
        .asFunction();
    return func(thisCpp) != 0;
  }

  static int isFloatButtonVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isFloatButtonVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isFloatButtonVisible();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        View.fromCppPointer(parent), QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> maximumSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::maximumSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maximumSize();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static int onResize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> newSize) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::onResize(QSize newSize)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize(QSize.fromCppPointer(newSize));
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> arg__1) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setGeometry(QRect arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(arg__1));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setParent(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent(View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int arg__1) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::setZOrder(int arg__1)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(arg__1);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as TitleBar_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for TitleBar_flutter::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__TitleBar_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 831:
        return "c_KDDockWidgets__Views__TitleBar_flutter__activateWindow";
      case 839:
        return "c_KDDockWidgets__Views__TitleBar_flutter__close";
      case 842:
        return "c_KDDockWidgets__Views__TitleBar_flutter__createPlatformWindow";
      case 847:
        return "c_KDDockWidgets__Views__TitleBar_flutter__flags";
      case 849:
        return "c_KDDockWidgets__Views__TitleBar_flutter__free_impl";
      case 851:
        return "c_KDDockWidgets__Views__TitleBar_flutter__geometry";
      case 853:
        return "c_KDDockWidgets__Views__TitleBar_flutter__grabMouse";
      case 856:
        return "c_KDDockWidgets__Views__TitleBar_flutter__hasFocus";
      case 858:
        return "c_KDDockWidgets__Views__TitleBar_flutter__hide";
      case 861:
        return "c_KDDockWidgets__Views__TitleBar_flutter__init";
      case 863:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isActiveWindow";
      case 958:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonEnabled";
      case 959:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isCloseButtonVisible";
      case 960:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isFloatButtonVisible";
      case 864:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isMaximized";
      case 865:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isMinimized";
      case 866:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isNull";
      case 867:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isRootView";
      case 868:
        return "c_KDDockWidgets__Views__TitleBar_flutter__isVisible";
      case 869:
        return "c_KDDockWidgets__Views__TitleBar_flutter__mapFromGlobal_QPoint";
      case 870:
        return "c_KDDockWidgets__Views__TitleBar_flutter__mapTo_View_QPoint";
      case 871:
        return "c_KDDockWidgets__Views__TitleBar_flutter__mapToGlobal_QPoint";
      case 872:
        return "c_KDDockWidgets__Views__TitleBar_flutter__maxSizeHint";
      case 873:
        return "c_KDDockWidgets__Views__TitleBar_flutter__maximumSize";
      case 874:
        return "c_KDDockWidgets__Views__TitleBar_flutter__minSize";
      case 875:
        return "c_KDDockWidgets__Views__TitleBar_flutter__minimumHeight";
      case 876:
        return "c_KDDockWidgets__Views__TitleBar_flutter__minimumWidth";
      case 878:
        return "c_KDDockWidgets__Views__TitleBar_flutter__move_int_int";
      case 879:
        return "c_KDDockWidgets__Views__TitleBar_flutter__normalGeometry";
      case 880:
        return "c_KDDockWidgets__Views__TitleBar_flutter__objectName";
      case 881:
        return "c_KDDockWidgets__Views__TitleBar_flutter__onResize_QSize";
      case 884:
        return "c_KDDockWidgets__Views__TitleBar_flutter__raise";
      case 885:
        return "c_KDDockWidgets__Views__TitleBar_flutter__raiseAndActivate";
      case 887:
        return "c_KDDockWidgets__Views__TitleBar_flutter__releaseKeyboard";
      case 888:
        return "c_KDDockWidgets__Views__TitleBar_flutter__releaseMouse";
      case 892:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setCursor_CursorShape";
      case 893:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setFixedHeight_int";
      case 894:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setFixedWidth_int";
      case 895:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setGeometry_QRect";
      case 896:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setHeight_int";
      case 897:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setMaximumSize_QSize";
      case 898:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setMinimumSize_QSize";
      case 899:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setMouseTracking_bool";
      case 900:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setObjectName_QString";
      case 901:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setParent_View";
      case 903:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setSize_int_int";
      case 904:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setVisible_bool";
      case 905:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setWidth_int";
      case 906:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setWindowOpacity_double";
      case 907:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setWindowTitle_QString";
      case 908:
        return "c_KDDockWidgets__Views__TitleBar_flutter__setZOrder_int";
      case 909:
        return "c_KDDockWidgets__Views__TitleBar_flutter__show";
      case 910:
        return "c_KDDockWidgets__Views__TitleBar_flutter__showMaximized";
      case 911:
        return "c_KDDockWidgets__Views__TitleBar_flutter__showMinimized";
      case 912:
        return "c_KDDockWidgets__Views__TitleBar_flutter__showNormal";
      case 914:
        return "c_KDDockWidgets__Views__TitleBar_flutter__sizeHint";
      case 916:
        return "c_KDDockWidgets__Views__TitleBar_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 831:
        return "activateWindow";
      case 839:
        return "close";
      case 842:
        return "createPlatformWindow";
      case 847:
        return "flags";
      case 849:
        return "free_impl";
      case 851:
        return "geometry";
      case 853:
        return "grabMouse";
      case 856:
        return "hasFocus";
      case 858:
        return "hide";
      case 861:
        return "init";
      case 863:
        return "isActiveWindow";
      case 958:
        return "isCloseButtonEnabled";
      case 959:
        return "isCloseButtonVisible";
      case 960:
        return "isFloatButtonVisible";
      case 864:
        return "isMaximized";
      case 865:
        return "isMinimized";
      case 866:
        return "isNull";
      case 867:
        return "isRootView";
      case 868:
        return "isVisible";
      case 869:
        return "mapFromGlobal";
      case 870:
        return "mapTo";
      case 871:
        return "mapToGlobal";
      case 872:
        return "maxSizeHint";
      case 873:
        return "maximumSize";
      case 874:
        return "minSize";
      case 875:
        return "minimumHeight";
      case 876:
        return "minimumWidth";
      case 878:
        return "move_2";
      case 879:
        return "normalGeometry";
      case 880:
        return "objectName";
      case 881:
        return "onResize";
      case 884:
        return "raise";
      case 885:
        return "raiseAndActivate";
      case 887:
        return "releaseKeyboard";
      case 888:
        return "releaseMouse";
      case 892:
        return "setCursor";
      case 893:
        return "setFixedHeight";
      case 894:
        return "setFixedWidth";
      case 895:
        return "setGeometry";
      case 896:
        return "setHeight";
      case 897:
        return "setMaximumSize";
      case 898:
        return "setMinimumSize";
      case 899:
        return "setMouseTracking";
      case 900:
        return "setObjectName";
      case 901:
        return "setParent";
      case 903:
        return "setSize_2";
      case 904:
        return "setVisible";
      case 905:
        return "setWidth";
      case 906:
        return "setWindowOpacity";
      case 907:
        return "setWindowTitle";
      case 908:
        return "setZOrder";
      case 909:
        return "show";
      case 910:
        return "showMaximized";
      case 911:
        return "showMinimized";
      case 912:
        return "showNormal";
      case 914:
        return "sizeHint";
      case 916:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Views__TitleBar_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback831 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback831, 831);
    const callbackExcept839 = 0;
    final callback839 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept839);
    registerCallback(thisCpp, callback839, 839);
    final callback842 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback842, 842);
    const callbackExcept847 = 0;
    final callback847 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept847);
    registerCallback(thisCpp, callback847, 847);
    final callback849 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback849, 849);
    final callback851 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback851, 851);
    final callback853 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback853, 853);
    const callbackExcept856 = 0;
    final callback856 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept856);
    registerCallback(thisCpp, callback856, 856);
    final callback858 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback858, 858);
    final callback861 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        TitleBar_flutter.init_calledFromC);
    registerCallback(thisCpp, callback861, 861);
    const callbackExcept863 = 0;
    final callback863 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept863);
    registerCallback(thisCpp, callback863, 863);
    const callbackExcept958 = 0;
    final callback958 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TitleBar_flutter.isCloseButtonEnabled_calledFromC, callbackExcept958);
    registerCallback(thisCpp, callback958, 958);
    const callbackExcept959 = 0;
    final callback959 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TitleBar_flutter.isCloseButtonVisible_calledFromC, callbackExcept959);
    registerCallback(thisCpp, callback959, 959);
    const callbackExcept960 = 0;
    final callback960 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        TitleBar_flutter.isFloatButtonVisible_calledFromC, callbackExcept960);
    registerCallback(thisCpp, callback960, 960);
    const callbackExcept864 = 0;
    final callback864 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept864);
    registerCallback(thisCpp, callback864, 864);
    const callbackExcept865 = 0;
    final callback865 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept865);
    registerCallback(thisCpp, callback865, 865);
    const callbackExcept866 = 0;
    final callback866 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept866);
    registerCallback(thisCpp, callback866, 866);
    const callbackExcept867 = 0;
    final callback867 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept867);
    registerCallback(thisCpp, callback867, 867);
    const callbackExcept868 = 0;
    final callback868 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept868);
    registerCallback(thisCpp, callback868, 868);
    final callback869 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback869, 869);
    final callback870 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback870, 870);
    final callback871 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback871, 871);
    final callback872 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback872, 872);
    final callback873 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maximumSize_calledFromC);
    registerCallback(thisCpp, callback873, 873);
    final callback874 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback874, 874);
    const callbackExcept875 = 0;
    final callback875 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept875);
    registerCallback(thisCpp, callback875, 875);
    const callbackExcept876 = 0;
    final callback876 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept876);
    registerCallback(thisCpp, callback876, 876);
    final callback878 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback878, 878);
    final callback879 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback879, 879);
    final callback880 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback880, 880);
    const callbackExcept881 = 0;
    final callback881 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_voidstar_FFI>(
            View.onResize_calledFromC, callbackExcept881);
    registerCallback(thisCpp, callback881, 881);
    final callback884 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback884, 884);
    final callback885 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback885, 885);
    final callback887 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback887, 887);
    final callback888 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback888, 888);
    final callback892 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback892, 892);
    final callback893 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback893, 893);
    final callback894 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback894, 894);
    final callback895 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback895, 895);
    final callback896 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback896, 896);
    final callback897 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback897, 897);
    final callback898 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback898, 898);
    final callback899 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback899, 899);
    final callback900 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    final callback901 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback901, 901);
    final callback903 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback903, 903);
    final callback904 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback904, 904);
    final callback905 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback905, 905);
    final callback906 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback906, 906);
    final callback907 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback908 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback908, 908);
    final callback909 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback910 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback910, 910);
    final callback911 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    final callback912 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback912, 912);
    final callback914 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback914, 914);
    final callback916 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback916, 916);
  }
}
