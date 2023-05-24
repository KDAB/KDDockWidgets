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

  static int isExplicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isExplicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExplicitlyHidden();
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
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
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
    dartInstance.onChildAdded((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
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
    dartInstance.onChildRemoved((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildVisibilityChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildVisibilityChanged(
        (childView == null || childView.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onGeometryChanged_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onGeometryChanged()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onGeometryChanged();
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
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
    dartInstance.setParent((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
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
      case 920:
        return "c_KDDockWidgets__flutter__DockWidget__activateWindow";
      case 931:
        return "c_KDDockWidgets__flutter__DockWidget__close";
      case 934:
        return "c_KDDockWidgets__flutter__DockWidget__createPlatformWindow";
      case 941:
        return "c_KDDockWidgets__flutter__DockWidget__flags";
      case 944:
        return "c_KDDockWidgets__flutter__DockWidget__geometry";
      case 946:
        return "c_KDDockWidgets__flutter__DockWidget__grabMouse";
      case 949:
        return "c_KDDockWidgets__flutter__DockWidget__hasFocus";
      case 951:
        return "c_KDDockWidgets__flutter__DockWidget__hide";
      case 954:
        return "c_KDDockWidgets__flutter__DockWidget__init";
      case 956:
        return "c_KDDockWidgets__flutter__DockWidget__isActiveWindow";
      case 957:
        return "c_KDDockWidgets__flutter__DockWidget__isExplicitlyHidden";
      case 958:
        return "c_KDDockWidgets__flutter__DockWidget__isMaximized";
      case 959:
        return "c_KDDockWidgets__flutter__DockWidget__isMinimized";
      case 960:
        return "c_KDDockWidgets__flutter__DockWidget__isNull";
      case 961:
        return "c_KDDockWidgets__flutter__DockWidget__isRootView";
      case 962:
        return "c_KDDockWidgets__flutter__DockWidget__isVisible";
      case 963:
        return "c_KDDockWidgets__flutter__DockWidget__mapFromGlobal_QPoint";
      case 964:
        return "c_KDDockWidgets__flutter__DockWidget__mapTo_View_QPoint";
      case 965:
        return "c_KDDockWidgets__flutter__DockWidget__mapToGlobal_QPoint";
      case 966:
        return "c_KDDockWidgets__flutter__DockWidget__maxSizeHint";
      case 967:
        return "c_KDDockWidgets__flutter__DockWidget__minSize";
      case 968:
        return "c_KDDockWidgets__flutter__DockWidget__minimumHeight";
      case 969:
        return "c_KDDockWidgets__flutter__DockWidget__minimumWidth";
      case 971:
        return "c_KDDockWidgets__flutter__DockWidget__move_int_int";
      case 972:
        return "c_KDDockWidgets__flutter__DockWidget__normalGeometry";
      case 973:
        return "c_KDDockWidgets__flutter__DockWidget__objectName";
      case 1042:
        return "c_KDDockWidgets__flutter__DockWidget__onChildAdded_View";
      case 1043:
        return "c_KDDockWidgets__flutter__DockWidget__onChildRemoved_View";
      case 1044:
        return "c_KDDockWidgets__flutter__DockWidget__onChildVisibilityChanged_View";
      case 1046:
        return "c_KDDockWidgets__flutter__DockWidget__onGeometryChanged";
      case 975:
        return "c_KDDockWidgets__flutter__DockWidget__onResize_int_int";
      case 978:
        return "c_KDDockWidgets__flutter__DockWidget__raise";
      case 979:
        return "c_KDDockWidgets__flutter__DockWidget__raiseAndActivate";
      case 981:
        return "c_KDDockWidgets__flutter__DockWidget__releaseKeyboard";
      case 982:
        return "c_KDDockWidgets__flutter__DockWidget__releaseMouse";
      case 986:
        return "c_KDDockWidgets__flutter__DockWidget__setCursor_CursorShape";
      case 987:
        return "c_KDDockWidgets__flutter__DockWidget__setFixedHeight_int";
      case 988:
        return "c_KDDockWidgets__flutter__DockWidget__setFixedWidth_int";
      case 989:
        return "c_KDDockWidgets__flutter__DockWidget__setGeometry_QRect";
      case 990:
        return "c_KDDockWidgets__flutter__DockWidget__setHeight_int";
      case 991:
        return "c_KDDockWidgets__flutter__DockWidget__setMaximumSize_QSize";
      case 992:
        return "c_KDDockWidgets__flutter__DockWidget__setMinimumSize_QSize";
      case 993:
        return "c_KDDockWidgets__flutter__DockWidget__setMouseTracking_bool";
      case 994:
        return "c_KDDockWidgets__flutter__DockWidget__setObjectName_QString";
      case 995:
        return "c_KDDockWidgets__flutter__DockWidget__setParent_View";
      case 997:
        return "c_KDDockWidgets__flutter__DockWidget__setSize_int_int";
      case 998:
        return "c_KDDockWidgets__flutter__DockWidget__setVisible_bool";
      case 999:
        return "c_KDDockWidgets__flutter__DockWidget__setWidth_int";
      case 1000:
        return "c_KDDockWidgets__flutter__DockWidget__setWindowOpacity_double";
      case 1001:
        return "c_KDDockWidgets__flutter__DockWidget__setWindowTitle_QString";
      case 1002:
        return "c_KDDockWidgets__flutter__DockWidget__setZOrder_int";
      case 1003:
        return "c_KDDockWidgets__flutter__DockWidget__show";
      case 1004:
        return "c_KDDockWidgets__flutter__DockWidget__showMaximized";
      case 1005:
        return "c_KDDockWidgets__flutter__DockWidget__showMinimized";
      case 1006:
        return "c_KDDockWidgets__flutter__DockWidget__showNormal";
      case 1008:
        return "c_KDDockWidgets__flutter__DockWidget__sizeHint";
      case 1010:
        return "c_KDDockWidgets__flutter__DockWidget__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 920:
        return "activateWindow";
      case 931:
        return "close";
      case 934:
        return "createPlatformWindow";
      case 941:
        return "flags";
      case 944:
        return "geometry";
      case 946:
        return "grabMouse";
      case 949:
        return "hasFocus";
      case 951:
        return "hide";
      case 954:
        return "init";
      case 956:
        return "isActiveWindow";
      case 957:
        return "isExplicitlyHidden";
      case 958:
        return "isMaximized";
      case 959:
        return "isMinimized";
      case 960:
        return "isNull";
      case 961:
        return "isRootView";
      case 962:
        return "isVisible";
      case 963:
        return "mapFromGlobal";
      case 964:
        return "mapTo";
      case 965:
        return "mapToGlobal";
      case 966:
        return "maxSizeHint";
      case 967:
        return "minSize";
      case 968:
        return "minimumHeight";
      case 969:
        return "minimumWidth";
      case 971:
        return "move_2";
      case 972:
        return "normalGeometry";
      case 973:
        return "objectName";
      case 1042:
        return "onChildAdded";
      case 1043:
        return "onChildRemoved";
      case 1044:
        return "onChildVisibilityChanged";
      case 1046:
        return "onGeometryChanged";
      case 975:
        return "onResize_2";
      case 978:
        return "raise";
      case 979:
        return "raiseAndActivate";
      case 981:
        return "releaseKeyboard";
      case 982:
        return "releaseMouse";
      case 986:
        return "setCursor";
      case 987:
        return "setFixedHeight";
      case 988:
        return "setFixedWidth";
      case 989:
        return "setGeometry";
      case 990:
        return "setHeight";
      case 991:
        return "setMaximumSize";
      case 992:
        return "setMinimumSize";
      case 993:
        return "setMouseTracking";
      case 994:
        return "setObjectName";
      case 995:
        return "setParent";
      case 997:
        return "setSize_2";
      case 998:
        return "setVisible";
      case 999:
        return "setWidth";
      case 1000:
        return "setWindowOpacity";
      case 1001:
        return "setWindowTitle";
      case 1002:
        return "setZOrder";
      case 1003:
        return "show";
      case 1004:
        return "showMaximized";
      case 1005:
        return "showMinimized";
      case 1006:
        return "showNormal";
      case 1008:
        return "sizeHint";
      case 1010:
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
    final callback920 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback920, 920);
    const callbackExcept931 = 0;
    final callback931 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept931);
    registerCallback(thisCpp, callback931, 931);
    final callback934 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback934, 934);
    const callbackExcept941 = 0;
    final callback941 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept941);
    registerCallback(thisCpp, callback941, 941);
    final callback944 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback944, 944);
    final callback946 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback946, 946);
    const callbackExcept949 = 0;
    final callback949 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept949);
    registerCallback(thisCpp, callback949, 949);
    final callback951 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback951, 951);
    final callback954 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.init_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    const callbackExcept956 = 0;
    final callback956 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept956);
    registerCallback(thisCpp, callback956, 956);
    const callbackExcept957 = 0;
    final callback957 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept957);
    registerCallback(thisCpp, callback957, 957);
    const callbackExcept958 = 0;
    final callback958 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept958);
    registerCallback(thisCpp, callback958, 958);
    const callbackExcept959 = 0;
    final callback959 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept959);
    registerCallback(thisCpp, callback959, 959);
    const callbackExcept960 = 0;
    final callback960 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept960);
    registerCallback(thisCpp, callback960, 960);
    const callbackExcept961 = 0;
    final callback961 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept961);
    registerCallback(thisCpp, callback961, 961);
    const callbackExcept962 = 0;
    final callback962 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept962);
    registerCallback(thisCpp, callback962, 962);
    final callback963 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback963, 963);
    final callback964 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback964, 964);
    final callback965 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback965, 965);
    final callback966 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback967 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.minSize_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    const callbackExcept968 = 0;
    final callback968 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept968);
    registerCallback(thisCpp, callback968, 968);
    const callbackExcept969 = 0;
    final callback969 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept969);
    registerCallback(thisCpp, callback969, 969);
    final callback971 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback971, 971);
    final callback972 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback972, 972);
    final callback973 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback973, 973);
    final callback1042 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1042, 1042);
    final callback1043 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1043, 1043);
    final callback1044 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback1044, 1044);
    final callback1046 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback1046, 1046);
    const callbackExcept975 = 0;
    final callback975 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept975);
    registerCallback(thisCpp, callback975, 975);
    final callback978 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback978, 978);
    final callback979 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback979, 979);
    final callback981 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback982 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback982, 982);
    final callback986 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback986, 986);
    final callback987 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback987, 987);
    final callback988 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback988, 988);
    final callback989 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback990 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback990, 990);
    final callback991 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback991, 991);
    final callback992 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback995 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback997 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback997, 997);
    final callback998 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback998, 998);
    final callback999 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback999, 999);
    final callback1000 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback1000, 1000);
    final callback1001 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback1001, 1001);
    final callback1002 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback1002, 1002);
    final callback1003 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback1003, 1003);
    final callback1004 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback1004, 1004);
    final callback1005 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
    final callback1006 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback1006, 1006);
    final callback1008 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback1008, 1008);
    final callback1010 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback1010, 1010);
  }
}
