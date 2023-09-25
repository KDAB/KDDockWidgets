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

  static int isMounted_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::isMounted() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMounted();
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
          "Dart instance not found for DockWidget::mapFromGlobal(KDDockWidgets::Point globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(Point.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::mapTo(KDDockWidgets::Core::View * parent, KDDockWidgets::Point pos) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapTo(
        (parent == null || parent.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(parent),
        Point.fromCppPointer(pos));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapToGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> localPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::mapToGlobal(KDDockWidgets::Point localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(Point.fromCppPointer(localPt));
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

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
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

  static void raiseChild_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::raiseChild(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseChild((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void raiseWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? rootView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::raiseWindow(KDDockWidgets::Core::View * rootView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseWindow((rootView == null || rootView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(rootView));
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
          "Dart instance not found for DockWidget::setGeometry(KDDockWidgets::Rect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(Rect.fromCppPointer(geometry));
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
          "Dart instance not found for DockWidget::setMaximumSize(KDDockWidgets::Size sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(Size.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setMinimumSize(KDDockWidgets::Size sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(Size.fromCppPointer(sz));
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

  static void setViewName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::setViewName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setViewName(QString.fromCppPointer(name).toDartString());
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

  static ffi.Pointer<void> viewName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DockWidget;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DockWidget::viewName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.viewName();
    return result.thisCpp;
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
      case 349:
        return "c_KDDockWidgets__flutter__DockWidget__activateWindow";
      case 359:
        return "c_KDDockWidgets__flutter__DockWidget__close";
      case 361:
        return "c_KDDockWidgets__flutter__DockWidget__createPlatformWindow";
      case 367:
        return "c_KDDockWidgets__flutter__DockWidget__flags";
      case 368:
        return "c_KDDockWidgets__flutter__DockWidget__geometry";
      case 369:
        return "c_KDDockWidgets__flutter__DockWidget__grabMouse";
      case 372:
        return "c_KDDockWidgets__flutter__DockWidget__hasFocus";
      case 374:
        return "c_KDDockWidgets__flutter__DockWidget__hide";
      case 376:
        return "c_KDDockWidgets__flutter__DockWidget__init";
      case 378:
        return "c_KDDockWidgets__flutter__DockWidget__isActiveWindow";
      case 379:
        return "c_KDDockWidgets__flutter__DockWidget__isExplicitlyHidden";
      case 380:
        return "c_KDDockWidgets__flutter__DockWidget__isMaximized";
      case 381:
        return "c_KDDockWidgets__flutter__DockWidget__isMinimized";
      case 451:
        return "c_KDDockWidgets__flutter__DockWidget__isMounted";
      case 382:
        return "c_KDDockWidgets__flutter__DockWidget__isNull";
      case 383:
        return "c_KDDockWidgets__flutter__DockWidget__isRootView";
      case 384:
        return "c_KDDockWidgets__flutter__DockWidget__isVisible";
      case 385:
        return "c_KDDockWidgets__flutter__DockWidget__mapFromGlobal_Point";
      case 386:
        return "c_KDDockWidgets__flutter__DockWidget__mapTo_View_Point";
      case 387:
        return "c_KDDockWidgets__flutter__DockWidget__mapToGlobal_Point";
      case 388:
        return "c_KDDockWidgets__flutter__DockWidget__maxSizeHint";
      case 389:
        return "c_KDDockWidgets__flutter__DockWidget__minSize";
      case 393:
        return "c_KDDockWidgets__flutter__DockWidget__move_int_int";
      case 394:
        return "c_KDDockWidgets__flutter__DockWidget__normalGeometry";
      case 454:
        return "c_KDDockWidgets__flutter__DockWidget__onChildAdded_View";
      case 455:
        return "c_KDDockWidgets__flutter__DockWidget__onChildRemoved_View";
      case 456:
        return "c_KDDockWidgets__flutter__DockWidget__onChildVisibilityChanged_View";
      case 458:
        return "c_KDDockWidgets__flutter__DockWidget__onGeometryChanged";
      case 460:
        return "c_KDDockWidgets__flutter__DockWidget__onRebuildRequested";
      case 396:
        return "c_KDDockWidgets__flutter__DockWidget__onResize_int_int";
      case 398:
        return "c_KDDockWidgets__flutter__DockWidget__raise";
      case 399:
        return "c_KDDockWidgets__flutter__DockWidget__raiseAndActivate";
      case 463:
        return "c_KDDockWidgets__flutter__DockWidget__raiseChild_View";
      case 464:
        return "c_KDDockWidgets__flutter__DockWidget__raiseWindow_View";
      case 401:
        return "c_KDDockWidgets__flutter__DockWidget__releaseKeyboard";
      case 402:
        return "c_KDDockWidgets__flutter__DockWidget__releaseMouse";
      case 405:
        return "c_KDDockWidgets__flutter__DockWidget__setCursor_CursorShape";
      case 406:
        return "c_KDDockWidgets__flutter__DockWidget__setFixedHeight_int";
      case 407:
        return "c_KDDockWidgets__flutter__DockWidget__setFixedWidth_int";
      case 408:
        return "c_KDDockWidgets__flutter__DockWidget__setGeometry_Rect";
      case 409:
        return "c_KDDockWidgets__flutter__DockWidget__setHeight_int";
      case 410:
        return "c_KDDockWidgets__flutter__DockWidget__setMaximumSize_Size";
      case 411:
        return "c_KDDockWidgets__flutter__DockWidget__setMinimumSize_Size";
      case 412:
        return "c_KDDockWidgets__flutter__DockWidget__setMouseTracking_bool";
      case 413:
        return "c_KDDockWidgets__flutter__DockWidget__setParent_View";
      case 415:
        return "c_KDDockWidgets__flutter__DockWidget__setSize_int_int";
      case 416:
        return "c_KDDockWidgets__flutter__DockWidget__setViewName_QString";
      case 417:
        return "c_KDDockWidgets__flutter__DockWidget__setVisible_bool";
      case 418:
        return "c_KDDockWidgets__flutter__DockWidget__setWidth_int";
      case 419:
        return "c_KDDockWidgets__flutter__DockWidget__setWindowOpacity_double";
      case 420:
        return "c_KDDockWidgets__flutter__DockWidget__setWindowTitle_QString";
      case 421:
        return "c_KDDockWidgets__flutter__DockWidget__setZOrder_int";
      case 422:
        return "c_KDDockWidgets__flutter__DockWidget__show";
      case 423:
        return "c_KDDockWidgets__flutter__DockWidget__showMaximized";
      case 424:
        return "c_KDDockWidgets__flutter__DockWidget__showMinimized";
      case 425:
        return "c_KDDockWidgets__flutter__DockWidget__showNormal";
      case 427:
        return "c_KDDockWidgets__flutter__DockWidget__update";
      case 428:
        return "c_KDDockWidgets__flutter__DockWidget__viewName";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 349:
        return "activateWindow";
      case 359:
        return "close";
      case 361:
        return "createPlatformWindow";
      case 367:
        return "flags";
      case 368:
        return "geometry";
      case 369:
        return "grabMouse";
      case 372:
        return "hasFocus";
      case 374:
        return "hide";
      case 376:
        return "init";
      case 378:
        return "isActiveWindow";
      case 379:
        return "isExplicitlyHidden";
      case 380:
        return "isMaximized";
      case 381:
        return "isMinimized";
      case 451:
        return "isMounted";
      case 382:
        return "isNull";
      case 383:
        return "isRootView";
      case 384:
        return "isVisible";
      case 385:
        return "mapFromGlobal";
      case 386:
        return "mapTo";
      case 387:
        return "mapToGlobal";
      case 388:
        return "maxSizeHint";
      case 389:
        return "minSize";
      case 393:
        return "move_2";
      case 394:
        return "normalGeometry";
      case 454:
        return "onChildAdded";
      case 455:
        return "onChildRemoved";
      case 456:
        return "onChildVisibilityChanged";
      case 458:
        return "onGeometryChanged";
      case 460:
        return "onRebuildRequested";
      case 396:
        return "onResize_2";
      case 398:
        return "raise";
      case 399:
        return "raiseAndActivate";
      case 463:
        return "raiseChild";
      case 464:
        return "raiseWindow";
      case 401:
        return "releaseKeyboard";
      case 402:
        return "releaseMouse";
      case 405:
        return "setCursor";
      case 406:
        return "setFixedHeight";
      case 407:
        return "setFixedWidth";
      case 408:
        return "setGeometry";
      case 409:
        return "setHeight";
      case 410:
        return "setMaximumSize";
      case 411:
        return "setMinimumSize";
      case 412:
        return "setMouseTracking";
      case 413:
        return "setParent";
      case 415:
        return "setSize_2";
      case 416:
        return "setViewName";
      case 417:
        return "setVisible";
      case 418:
        return "setWidth";
      case 419:
        return "setWindowOpacity";
      case 420:
        return "setWindowTitle";
      case 421:
        return "setZOrder";
      case 422:
        return "show";
      case 423:
        return "showMaximized";
      case 424:
        return "showMinimized";
      case 425:
        return "showNormal";
      case 427:
        return "update";
      case 428:
        return "viewName";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__DockWidget__registerVirtualMethodCallback')
        .asFunction();
    final callback349 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback349, 349);
    const callbackExcept359 = 0;
    final callback359 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept359);
    registerCallback(thisCpp, callback359, 359);
    final callback361 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback361, 361);
    const callbackExcept367 = 0;
    final callback367 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept367);
    registerCallback(thisCpp, callback367, 367);
    final callback368 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback368, 368);
    final callback369 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback369, 369);
    const callbackExcept372 = 0;
    final callback372 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept372);
    registerCallback(thisCpp, callback372, 372);
    final callback374 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback374, 374);
    final callback376 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.init_calledFromC);
    registerCallback(thisCpp, callback376, 376);
    const callbackExcept378 = 0;
    final callback378 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept378);
    registerCallback(thisCpp, callback378, 378);
    const callbackExcept379 = 0;
    final callback379 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept379);
    registerCallback(thisCpp, callback379, 379);
    const callbackExcept380 = 0;
    final callback380 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept380);
    registerCallback(thisCpp, callback380, 380);
    const callbackExcept381 = 0;
    final callback381 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept381);
    registerCallback(thisCpp, callback381, 381);
    const callbackExcept451 = 0;
    final callback451 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMounted_calledFromC, callbackExcept451);
    registerCallback(thisCpp, callback451, 451);
    const callbackExcept382 = 0;
    final callback382 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept382);
    registerCallback(thisCpp, callback382, 382);
    const callbackExcept383 = 0;
    final callback383 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept383);
    registerCallback(thisCpp, callback383, 383);
    const callbackExcept384 = 0;
    final callback384 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept384);
    registerCallback(thisCpp, callback384, 384);
    final callback385 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback385, 385);
    final callback386 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback386, 386);
    final callback387 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback387, 387);
    final callback388 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback388, 388);
    final callback389 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.DockWidget.minSize_calledFromC);
    registerCallback(thisCpp, callback389, 389);
    final callback393 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback393, 393);
    final callback394 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback394, 394);
    final callback454 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback454, 454);
    final callback455 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback455, 455);
    final callback456 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback456, 456);
    final callback458 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback458, 458);
    final callback460 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback460, 460);
    const callbackExcept396 = 0;
    final callback396 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept396);
    registerCallback(thisCpp, callback396, 396);
    final callback398 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback398, 398);
    final callback399 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback399, 399);
    final callback463 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseChild_calledFromC);
    registerCallback(thisCpp, callback463, 463);
    final callback464 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseWindow_calledFromC);
    registerCallback(thisCpp, callback464, 464);
    final callback401 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback401, 401);
    final callback402 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback402, 402);
    final callback405 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback405, 405);
    final callback406 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback406, 406);
    final callback407 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback407, 407);
    final callback408 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback408, 408);
    final callback409 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback409, 409);
    final callback410 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback410, 410);
    final callback411 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback411, 411);
    final callback412 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback412, 412);
    final callback413 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback413, 413);
    final callback415 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback415, 415);
    final callback416 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback416, 416);
    final callback417 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback417, 417);
    final callback418 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback418, 418);
    final callback419 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback419, 419);
    final callback420 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback420, 420);
    final callback421 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback421, 421);
    final callback422 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback422, 422);
    final callback423 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback423, 423);
    final callback424 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback424, 424);
    final callback425 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback425, 425);
    final callback427 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback427, 427);
    final callback428 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.viewName_calledFromC);
    registerCallback(thisCpp, callback428, 428);
  }
}
