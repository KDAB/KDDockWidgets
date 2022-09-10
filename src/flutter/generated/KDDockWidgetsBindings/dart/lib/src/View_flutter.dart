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

class View_flutter extends View {
  View_flutter.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  View_flutter.init() : super.init() {}
  factory View_flutter.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (View.isCached(cppPointer)) {
      var instance = View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as View_flutter;
    }
    return View_flutter.fromCppPointer(cppPointer, needsAutoDelete);
  } //View_flutter(KDDockWidgets::Controller * controller, KDDockWidgets::Type type, KDDockWidgets::View * arg__3, Qt::WindowFlags windowFlags)
  View_flutter(Controller? controller, int type, View? arg__3,
      {int windowFlags = 0})
      : super.init() {
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
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::mapTo(KDDockWidgets::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        View.fromCppPointer(parent), QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  } // onChildAdded(KDDockWidgets::View * childView)

  onChildAdded(View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1021))
        .asFunction();
    func(thisCpp, childView == null ? ffi.nullptr : childView.thisCpp);
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::onChildAdded(KDDockWidgets::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded(View.fromCppPointer(childView));
  } // onChildRemoved(KDDockWidgets::View * childView)

  onChildRemoved(View? childView) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            cFunctionSymbolName(1022))
        .asFunction();
    func(thisCpp, childView == null ? ffi.nullptr : childView.thisCpp);
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::onChildRemoved(KDDockWidgets::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved(View.fromCppPointer(childView));
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::onResize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(w, h);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  } // setNormalGeometry(QRect geo)

  setNormalGeometry(QRect geo) {
    final void_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__setNormalGeometry_QRect')
        .asFunction();
    func(thisCpp, geo == null ? ffi.nullptr : geo.thisCpp);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setParent(KDDockWidgets::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent(View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        View.s_dartInstanceByCppPtr[thisCpp.address] as View_flutter;
    if (dartInstance == null) {
      print(
          "Dart instance not found for View_flutter::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  } // updateGeometry()

  updateGeometry() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__updateGeometry')
        .asFunction();
    func(thisCpp);
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 903:
        return "c_KDDockWidgets__Views__View_flutter__activateWindow";
      case 914:
        return "c_KDDockWidgets__Views__View_flutter__close";
      case 917:
        return "c_KDDockWidgets__Views__View_flutter__createPlatformWindow";
      case 922:
        return "c_KDDockWidgets__Views__View_flutter__flags";
      case 924:
        return "c_KDDockWidgets__Views__View_flutter__free_impl";
      case 926:
        return "c_KDDockWidgets__Views__View_flutter__geometry";
      case 928:
        return "c_KDDockWidgets__Views__View_flutter__grabMouse";
      case 931:
        return "c_KDDockWidgets__Views__View_flutter__hasFocus";
      case 933:
        return "c_KDDockWidgets__Views__View_flutter__hide";
      case 936:
        return "c_KDDockWidgets__Views__View_flutter__init";
      case 938:
        return "c_KDDockWidgets__Views__View_flutter__isActiveWindow";
      case 939:
        return "c_KDDockWidgets__Views__View_flutter__isMaximized";
      case 940:
        return "c_KDDockWidgets__Views__View_flutter__isMinimized";
      case 941:
        return "c_KDDockWidgets__Views__View_flutter__isNull";
      case 942:
        return "c_KDDockWidgets__Views__View_flutter__isRootView";
      case 943:
        return "c_KDDockWidgets__Views__View_flutter__isVisible";
      case 944:
        return "c_KDDockWidgets__Views__View_flutter__mapFromGlobal_QPoint";
      case 945:
        return "c_KDDockWidgets__Views__View_flutter__mapTo_View_QPoint";
      case 946:
        return "c_KDDockWidgets__Views__View_flutter__mapToGlobal_QPoint";
      case 947:
        return "c_KDDockWidgets__Views__View_flutter__maxSizeHint";
      case 948:
        return "c_KDDockWidgets__Views__View_flutter__minSize";
      case 949:
        return "c_KDDockWidgets__Views__View_flutter__minimumHeight";
      case 950:
        return "c_KDDockWidgets__Views__View_flutter__minimumWidth";
      case 952:
        return "c_KDDockWidgets__Views__View_flutter__move_int_int";
      case 953:
        return "c_KDDockWidgets__Views__View_flutter__normalGeometry";
      case 954:
        return "c_KDDockWidgets__Views__View_flutter__objectName";
      case 1021:
        return "c_KDDockWidgets__Views__View_flutter__onChildAdded_View";
      case 1022:
        return "c_KDDockWidgets__Views__View_flutter__onChildRemoved_View";
      case 956:
        return "c_KDDockWidgets__Views__View_flutter__onResize_int_int";
      case 959:
        return "c_KDDockWidgets__Views__View_flutter__raise";
      case 960:
        return "c_KDDockWidgets__Views__View_flutter__raiseAndActivate";
      case 962:
        return "c_KDDockWidgets__Views__View_flutter__releaseKeyboard";
      case 963:
        return "c_KDDockWidgets__Views__View_flutter__releaseMouse";
      case 967:
        return "c_KDDockWidgets__Views__View_flutter__setCursor_CursorShape";
      case 968:
        return "c_KDDockWidgets__Views__View_flutter__setFixedHeight_int";
      case 969:
        return "c_KDDockWidgets__Views__View_flutter__setFixedWidth_int";
      case 970:
        return "c_KDDockWidgets__Views__View_flutter__setGeometry_QRect";
      case 971:
        return "c_KDDockWidgets__Views__View_flutter__setHeight_int";
      case 972:
        return "c_KDDockWidgets__Views__View_flutter__setMaximumSize_QSize";
      case 973:
        return "c_KDDockWidgets__Views__View_flutter__setMinimumSize_QSize";
      case 974:
        return "c_KDDockWidgets__Views__View_flutter__setMouseTracking_bool";
      case 975:
        return "c_KDDockWidgets__Views__View_flutter__setObjectName_QString";
      case 976:
        return "c_KDDockWidgets__Views__View_flutter__setParent_View";
      case 978:
        return "c_KDDockWidgets__Views__View_flutter__setSize_int_int";
      case 979:
        return "c_KDDockWidgets__Views__View_flutter__setVisible_bool";
      case 980:
        return "c_KDDockWidgets__Views__View_flutter__setWidth_int";
      case 981:
        return "c_KDDockWidgets__Views__View_flutter__setWindowOpacity_double";
      case 982:
        return "c_KDDockWidgets__Views__View_flutter__setWindowTitle_QString";
      case 983:
        return "c_KDDockWidgets__Views__View_flutter__setZOrder_int";
      case 984:
        return "c_KDDockWidgets__Views__View_flutter__show";
      case 985:
        return "c_KDDockWidgets__Views__View_flutter__showMaximized";
      case 986:
        return "c_KDDockWidgets__Views__View_flutter__showMinimized";
      case 987:
        return "c_KDDockWidgets__Views__View_flutter__showNormal";
      case 989:
        return "c_KDDockWidgets__Views__View_flutter__sizeHint";
      case 991:
        return "c_KDDockWidgets__Views__View_flutter__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 903:
        return "activateWindow";
      case 914:
        return "close";
      case 917:
        return "createPlatformWindow";
      case 922:
        return "flags";
      case 924:
        return "free_impl";
      case 926:
        return "geometry";
      case 928:
        return "grabMouse";
      case 931:
        return "hasFocus";
      case 933:
        return "hide";
      case 936:
        return "init";
      case 938:
        return "isActiveWindow";
      case 939:
        return "isMaximized";
      case 940:
        return "isMinimized";
      case 941:
        return "isNull";
      case 942:
        return "isRootView";
      case 943:
        return "isVisible";
      case 944:
        return "mapFromGlobal";
      case 945:
        return "mapTo";
      case 946:
        return "mapToGlobal";
      case 947:
        return "maxSizeHint";
      case 948:
        return "minSize";
      case 949:
        return "minimumHeight";
      case 950:
        return "minimumWidth";
      case 952:
        return "move_2";
      case 953:
        return "normalGeometry";
      case 954:
        return "objectName";
      case 1021:
        return "onChildAdded";
      case 1022:
        return "onChildRemoved";
      case 956:
        return "onResize_2";
      case 959:
        return "raise";
      case 960:
        return "raiseAndActivate";
      case 962:
        return "releaseKeyboard";
      case 963:
        return "releaseMouse";
      case 967:
        return "setCursor";
      case 968:
        return "setFixedHeight";
      case 969:
        return "setFixedWidth";
      case 970:
        return "setGeometry";
      case 971:
        return "setHeight";
      case 972:
        return "setMaximumSize";
      case 973:
        return "setMinimumSize";
      case 974:
        return "setMouseTracking";
      case 975:
        return "setObjectName";
      case 976:
        return "setParent";
      case 978:
        return "setSize_2";
      case 979:
        return "setVisible";
      case 980:
        return "setWidth";
      case 981:
        return "setWindowOpacity";
      case 982:
        return "setWindowTitle";
      case 983:
        return "setZOrder";
      case 984:
        return "show";
      case 985:
        return "showMaximized";
      case 986:
        return "showMinimized";
      case 987:
        return "showNormal";
      case 989:
        return "sizeHint";
      case 991:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__Views__View_flutter__registerVirtualMethodCallback')
        .asFunction();
    final callback903 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.activateWindow_calledFromC);
    registerCallback(thisCpp, callback903, 903);
    const callbackExcept914 = 0;
    final callback914 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.close_calledFromC, callbackExcept914);
    registerCallback(thisCpp, callback914, 914);
    final callback917 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback917, 917);
    const callbackExcept922 = 0;
    final callback922 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View_flutter.flags_calledFromC, callbackExcept922);
    registerCallback(thisCpp, callback922, 922);
    final callback924 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.free_impl_calledFromC);
    registerCallback(thisCpp, callback924, 924);
    final callback926 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.geometry_calledFromC);
    registerCallback(thisCpp, callback926, 926);
    final callback928 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.grabMouse_calledFromC);
    registerCallback(thisCpp, callback928, 928);
    const callbackExcept931 = 0;
    final callback931 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.hasFocus_calledFromC, callbackExcept931);
    registerCallback(thisCpp, callback931, 931);
    final callback933 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.hide_calledFromC);
    registerCallback(thisCpp, callback933, 933);
    final callback936 =
        ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(View.init_calledFromC);
    registerCallback(thisCpp, callback936, 936);
    const callbackExcept938 = 0;
    final callback938 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isActiveWindow_calledFromC, callbackExcept938);
    registerCallback(thisCpp, callback938, 938);
    const callbackExcept939 = 0;
    final callback939 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMaximized_calledFromC, callbackExcept939);
    registerCallback(thisCpp, callback939, 939);
    const callbackExcept940 = 0;
    final callback940 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isMinimized_calledFromC, callbackExcept940);
    registerCallback(thisCpp, callback940, 940);
    const callbackExcept941 = 0;
    final callback941 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View.isNull_calledFromC, callbackExcept941);
    registerCallback(thisCpp, callback941, 941);
    const callbackExcept942 = 0;
    final callback942 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isRootView_calledFromC, callbackExcept942);
    registerCallback(thisCpp, callback942, 942);
    const callbackExcept943 = 0;
    final callback943 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        View_flutter.isVisible_calledFromC, callbackExcept943);
    registerCallback(thisCpp, callback943, 943);
    final callback944 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback944, 944);
    final callback945 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            View_flutter.mapTo_calledFromC);
    registerCallback(thisCpp, callback945, 945);
    final callback946 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            View_flutter.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback947 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback947, 947);
    final callback948 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.minSize_calledFromC);
    registerCallback(thisCpp, callback948, 948);
    const callbackExcept949 = 0;
    final callback949 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumHeight_calledFromC, callbackExcept949);
    registerCallback(thisCpp, callback949, 949);
    const callbackExcept950 = 0;
    final callback950 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        View.minimumWidth_calledFromC, callbackExcept950);
    registerCallback(thisCpp, callback950, 950);
    final callback952 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.move_2_calledFromC);
    registerCallback(thisCpp, callback952, 952);
    final callback953 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback953, 953);
    final callback954 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.objectName_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback1021 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1021, 1021);
    final callback1022 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1022, 1022);
    const callbackExcept956 = 0;
    final callback956 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.onResize_2_calledFromC, callbackExcept956);
    registerCallback(thisCpp, callback956, 956);
    final callback959 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raise_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback960 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback960, 960);
    final callback962 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback962, 962);
    final callback963 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback963, 963);
    final callback967 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setCursor_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback969 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback969, 969);
    final callback970 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setGeometry_calledFromC);
    registerCallback(thisCpp, callback970, 970);
    final callback971 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setHeight_calledFromC);
    registerCallback(thisCpp, callback971, 971);
    final callback972 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback972, 972);
    final callback973 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback973, 973);
    final callback974 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback974, 974);
    final callback975 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setObjectName_calledFromC);
    registerCallback(thisCpp, callback975, 975);
    final callback976 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setParent_calledFromC);
    registerCallback(thisCpp, callback976, 976);
    final callback978 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            View_flutter.setSize_2_calledFromC);
    registerCallback(thisCpp, callback978, 978);
    final callback979 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            View_flutter.setVisible_calledFromC);
    registerCallback(thisCpp, callback979, 979);
    final callback980 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setWidth_calledFromC);
    registerCallback(thisCpp, callback980, 980);
    final callback981 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            View_flutter.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback982 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            View_flutter.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback982, 982);
    final callback983 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            View_flutter.setZOrder_calledFromC);
    registerCallback(thisCpp, callback983, 983);
    final callback984 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.show_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback985 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMaximized_calledFromC);
    registerCallback(thisCpp, callback985, 985);
    final callback986 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showMinimized_calledFromC);
    registerCallback(thisCpp, callback986, 986);
    final callback987 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.showNormal_calledFromC);
    registerCallback(thisCpp, callback987, 987);
    final callback989 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        View_flutter.sizeHint_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback991 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        View_flutter.update_calledFromC);
    registerCallback(thisCpp, callback991, 991);
  }
}
