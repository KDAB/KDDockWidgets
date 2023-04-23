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

class DockWidget extends KDDWBindingsFlutter.View {
  DockWidget.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DockWidget.init() : super.init() {}
  factory DockWidget.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DockWidget;
    }
    return DockWidget.fromCppPointer(cppPointer, needsAutoDelete);
  } //DockWidget(const QString & uniqueName, QFlags<KDDockWidgets::DockWidgetOption> options, QFlags<KDDockWidgets::LayoutSaverOption> layoutSaverOptions)
  DockWidget(String? uniqueName, {int options = 0, int layoutSaverOptions = 0})
      : super.init() {
    final voidstar_Func_voidstar_int_int func = _dylib
        .lookup<
                ffi.NativeFunction<
                    voidstar_Func_voidstar_ffi_Int32_ffi_Int32_FFI>>(
            'c_KDDockWidgets__flutter__DockWidget__constructor_QString_DockWidgetOptions_LayoutSaverOptions')
        .asFunction();
    thisCpp = func(
        uniqueName?.toNativeUtf8() ?? ffi.nullptr, options, layoutSaverOptions);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  } // dockWidget() const

  KDDWBindingsCore.DockWidget dockWidget() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__DockWidget__dockWidget')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsCore.DockWidget.fromCppPointer(result, false);
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static void free_impl_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::free_impl()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.free_impl();
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        KDDWBindingsCore.View.fromCppPointer(parent),
        QPoint.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded(KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance
        .onChildRemoved(KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onResize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(w, h);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent(KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__DockWidget__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 886:
        return "c_KDDockWidgets__flutter__DockWidget__activateWindow";
      case 897:
        return "c_KDDockWidgets__flutter__DockWidget__close";
      case 900:
        return "c_KDDockWidgets__flutter__DockWidget__createPlatformWindow";
      case 905:
        return "c_KDDockWidgets__flutter__DockWidget__flags";
      case 907:
        return "c_KDDockWidgets__flutter__DockWidget__free_impl";
      case 909:
        return "c_KDDockWidgets__flutter__DockWidget__geometry";
      case 911:
        return "c_KDDockWidgets__flutter__DockWidget__grabMouse";
      case 914:
        return "c_KDDockWidgets__flutter__DockWidget__hasFocus";
      case 916:
        return "c_KDDockWidgets__flutter__DockWidget__hide";
      case 919:
        return "c_KDDockWidgets__flutter__DockWidget__init";
      case 921:
        return "c_KDDockWidgets__flutter__DockWidget__isActiveWindow";
      case 922:
        return "c_KDDockWidgets__flutter__DockWidget__isMaximized";
      case 923:
        return "c_KDDockWidgets__flutter__DockWidget__isMinimized";
      case 924:
        return "c_KDDockWidgets__flutter__DockWidget__isNull";
      case 925:
        return "c_KDDockWidgets__flutter__DockWidget__isRootView";
      case 926:
        return "c_KDDockWidgets__flutter__DockWidget__isVisible";
      case 927:
        return "c_KDDockWidgets__flutter__DockWidget__mapFromGlobal_QPoint";
      case 928:
        return "c_KDDockWidgets__flutter__DockWidget__mapTo_View_QPoint";
      case 929:
        return "c_KDDockWidgets__flutter__DockWidget__mapToGlobal_QPoint";
      case 930:
        return "c_KDDockWidgets__flutter__DockWidget__maxSizeHint";
      case 931:
        return "c_KDDockWidgets__flutter__DockWidget__minSize";
      case 932:
        return "c_KDDockWidgets__flutter__DockWidget__minimumHeight";
      case 933:
        return "c_KDDockWidgets__flutter__DockWidget__minimumWidth";
      case 935:
        return "c_KDDockWidgets__flutter__DockWidget__move_int_int";
      case 936:
        return "c_KDDockWidgets__flutter__DockWidget__normalGeometry";
      case 937:
        return "c_KDDockWidgets__flutter__DockWidget__objectName";
      case 1004:
        return "c_KDDockWidgets__flutter__DockWidget__onChildAdded_View";
      case 1005:
        return "c_KDDockWidgets__flutter__DockWidget__onChildRemoved_View";
      case 939:
        return "c_KDDockWidgets__flutter__DockWidget__onResize_int_int";
      case 942:
        return "c_KDDockWidgets__flutter__DockWidget__raise";
      case 943:
        return "c_KDDockWidgets__flutter__DockWidget__raiseAndActivate";
      case 945:
        return "c_KDDockWidgets__flutter__DockWidget__releaseKeyboard";
      case 946:
        return "c_KDDockWidgets__flutter__DockWidget__releaseMouse";
      case 950:
        return "c_KDDockWidgets__flutter__DockWidget__setCursor_CursorShape";
      case 951:
        return "c_KDDockWidgets__flutter__DockWidget__setFixedHeight_int";
      case 952:
        return "c_KDDockWidgets__flutter__DockWidget__setFixedWidth_int";
      case 953:
        return "c_KDDockWidgets__flutter__DockWidget__setGeometry_QRect";
      case 954:
        return "c_KDDockWidgets__flutter__DockWidget__setHeight_int";
      case 955:
        return "c_KDDockWidgets__flutter__DockWidget__setMaximumSize_QSize";
      case 956:
        return "c_KDDockWidgets__flutter__DockWidget__setMinimumSize_QSize";
      case 957:
        return "c_KDDockWidgets__flutter__DockWidget__setMouseTracking_bool";
      case 958:
        return "c_KDDockWidgets__flutter__DockWidget__setObjectName_QString";
      case 959:
        return "c_KDDockWidgets__flutter__DockWidget__setParent_View";
      case 961:
        return "c_KDDockWidgets__flutter__DockWidget__setSize_int_int";
      case 962:
        return "c_KDDockWidgets__flutter__DockWidget__setVisible_bool";
      case 963:
        return "c_KDDockWidgets__flutter__DockWidget__setWidth_int";
      case 964:
        return "c_KDDockWidgets__flutter__DockWidget__setWindowOpacity_double";
      case 965:
        return "c_KDDockWidgets__flutter__DockWidget__setWindowTitle_QString";
      case 966:
        return "c_KDDockWidgets__flutter__DockWidget__setZOrder_int";
      case 967:
        return "c_KDDockWidgets__flutter__DockWidget__show";
      case 968:
        return "c_KDDockWidgets__flutter__DockWidget__showMaximized";
      case 969:
        return "c_KDDockWidgets__flutter__DockWidget__showMinimized";
      case 970:
        return "c_KDDockWidgets__flutter__DockWidget__showNormal";
      case 972:
        return "c_KDDockWidgets__flutter__DockWidget__sizeHint";
      case 974:
        return "c_KDDockWidgets__flutter__DockWidget__update";
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
      case 936:
        return "normalGeometry";
      case 937:
        return "objectName";
      case 1004:
        return "onChildAdded";
      case 1005:
        return "onChildRemoved";
      case 939:
        return "onResize_2";
      case 942:
        return "raise";
      case 943:
        return "raiseAndActivate";
      case 945:
        return "releaseKeyboard";
      case 946:
        return "releaseMouse";
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
      case 974:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__DockWidget__registerVirtualMethodCallback')
        .asFunction();
    final callback886 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback886, 886);
    const callbackExcept897 = 0;
    final callback897 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept897);
    registerCallback(thisCpp, callback897, 897);
    final callback900 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback900, 900);
    const callbackExcept905 = 0;
    final callback905 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept905);
    registerCallback(thisCpp, callback905, 905);
    final callback907 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.free_impl_calledFromC);
    registerCallback(thisCpp, callback907, 907);
    final callback909 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback909, 909);
    final callback911 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback911, 911);
    const callbackExcept914 = 0;
    final callback914 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept914);
    registerCallback(thisCpp, callback914, 914);
    final callback916 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback916, 916);
    final callback919 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.init_calledFromC);
    registerCallback(thisCpp, callback919, 919);
    const callbackExcept921 = 0;
    final callback921 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept921);
    registerCallback(thisCpp, callback921, 921);
    const callbackExcept922 = 0;
    final callback922 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept922);
    registerCallback(thisCpp, callback922, 922);
    const callbackExcept923 = 0;
    final callback923 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept923);
    registerCallback(thisCpp, callback923, 923);
    const callbackExcept924 = 0;
    final callback924 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept924);
    registerCallback(thisCpp, callback924, 924);
    const callbackExcept925 = 0;
    final callback925 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept925);
    registerCallback(thisCpp, callback925, 925);
    const callbackExcept926 = 0;
    final callback926 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept926);
    registerCallback(thisCpp, callback926, 926);
    final callback927 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback927, 927);
    final callback928 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback928, 928);
    final callback929 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback929, 929);
    final callback930 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback930, 930);
    final callback931 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.minSize_calledFromC);
    registerCallback(thisCpp, callback931, 931);
    const callbackExcept932 = 0;
    final callback932 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept932);
    registerCallback(thisCpp, callback932, 932);
    const callbackExcept933 = 0;
    final callback933 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept933);
    registerCallback(thisCpp, callback933, 933);
    final callback935 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback935, 935);
    final callback936 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback936, 936);
    final callback937 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback937, 937);
    final callback1004 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1004, 1004);
    final callback1005 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
    const callbackExcept939 = 0;
    final callback939 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.onResize_2_calledFromC, callbackExcept939);
    registerCallback(thisCpp, callback939, 939);
    final callback942 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback942, 942);
    final callback943 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback943, 943);
    final callback945 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback945, 945);
    final callback946 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    final callback950 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback950, 950);
    final callback951 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback951, 951);
    final callback952 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback952, 952);
    final callback953 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback953, 953);
    final callback954 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback955 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback955, 955);
    final callback956 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback956, 956);
    final callback957 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    final callback958 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback958, 958);
    final callback959 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback959, 959);
    final callback961 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback961, 961);
    final callback962 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback962, 962);
    final callback963 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback963, 963);
    final callback964 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback964, 964);
    final callback965 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback967 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback969 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback969, 969);
    final callback970 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback970, 970);
    final callback972 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback972, 972);
    final callback974 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback974, 974);
  }
}
