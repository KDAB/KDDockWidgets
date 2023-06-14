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

class DropArea extends KDDWBindingsFlutter.View {
  DropArea.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  DropArea.init() : super.init() {}
  factory DropArea.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as DropArea;
    }
    return DropArea.fromCppPointer(cppPointer, needsAutoDelete);
  } //DropArea(KDDockWidgets::Core::DropArea * arg__1, KDDockWidgets::Core::View * parent)
  DropArea(KDDWBindingsCore.DropArea? arg__1, KDDWBindingsCore.View? parent)
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__DropArea__constructor_DropArea_View')
        .asFunction();
    thisCpp = func(arg__1 == null ? ffi.nullptr : arg__1.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  } // indicatorWindow() const

  KDDWBindingsFlutter.View indicatorWindow() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__DropArea__indicatorWindow')
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return KDDWBindingsFlutter.View.fromCppPointer(result, false);
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isExplicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isExplicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExplicitlyHidden();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isMounted_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isMounted() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMounted();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
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
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static int minimumHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::minimumHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumHeight();
    return result;
  }

  static int minimumWidth_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::minimumWidth() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minimumWidth();
    return result;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static ffi.Pointer<void> objectName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::objectName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.objectName();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildVisibilityChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildVisibilityChanged(
        (childView == null || childView.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onGeometryChanged_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::onGeometryChanged()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onGeometryChanged();
  }

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void raiseChild_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::raiseChild(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseChild((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void raiseWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? rootView) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::raiseWindow(KDDockWidgets::Core::View * rootView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseWindow((rootView == null || rootView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(rootView));
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setObjectName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setObjectName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setObjectName(QString.fromCppPointer(name).toDartString());
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static ffi.Pointer<void> sizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::sizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.sizeHint();
    return result.thisCpp;
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance = KDDWBindingsCore
        .View.s_dartInstanceByCppPtr[thisCpp.address] as DropArea;
    if (dartInstance == null) {
      print(
          "Dart instance not found for DropArea::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__DropArea__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 923:
        return "c_KDDockWidgets__flutter__DropArea__activateWindow";
      case 934:
        return "c_KDDockWidgets__flutter__DropArea__close";
      case 937:
        return "c_KDDockWidgets__flutter__DropArea__createPlatformWindow";
      case 944:
        return "c_KDDockWidgets__flutter__DropArea__flags";
      case 947:
        return "c_KDDockWidgets__flutter__DropArea__geometry";
      case 949:
        return "c_KDDockWidgets__flutter__DropArea__grabMouse";
      case 952:
        return "c_KDDockWidgets__flutter__DropArea__hasFocus";
      case 954:
        return "c_KDDockWidgets__flutter__DropArea__hide";
      case 957:
        return "c_KDDockWidgets__flutter__DropArea__init";
      case 959:
        return "c_KDDockWidgets__flutter__DropArea__isActiveWindow";
      case 960:
        return "c_KDDockWidgets__flutter__DropArea__isExplicitlyHidden";
      case 961:
        return "c_KDDockWidgets__flutter__DropArea__isMaximized";
      case 962:
        return "c_KDDockWidgets__flutter__DropArea__isMinimized";
      case 1045:
        return "c_KDDockWidgets__flutter__DropArea__isMounted";
      case 963:
        return "c_KDDockWidgets__flutter__DropArea__isNull";
      case 964:
        return "c_KDDockWidgets__flutter__DropArea__isRootView";
      case 965:
        return "c_KDDockWidgets__flutter__DropArea__isVisible";
      case 966:
        return "c_KDDockWidgets__flutter__DropArea__mapFromGlobal_QPoint";
      case 967:
        return "c_KDDockWidgets__flutter__DropArea__mapTo_View_QPoint";
      case 968:
        return "c_KDDockWidgets__flutter__DropArea__mapToGlobal_QPoint";
      case 969:
        return "c_KDDockWidgets__flutter__DropArea__maxSizeHint";
      case 970:
        return "c_KDDockWidgets__flutter__DropArea__minSize";
      case 971:
        return "c_KDDockWidgets__flutter__DropArea__minimumHeight";
      case 972:
        return "c_KDDockWidgets__flutter__DropArea__minimumWidth";
      case 974:
        return "c_KDDockWidgets__flutter__DropArea__move_int_int";
      case 975:
        return "c_KDDockWidgets__flutter__DropArea__normalGeometry";
      case 976:
        return "c_KDDockWidgets__flutter__DropArea__objectName";
      case 1046:
        return "c_KDDockWidgets__flutter__DropArea__onChildAdded_View";
      case 1047:
        return "c_KDDockWidgets__flutter__DropArea__onChildRemoved_View";
      case 1048:
        return "c_KDDockWidgets__flutter__DropArea__onChildVisibilityChanged_View";
      case 1050:
        return "c_KDDockWidgets__flutter__DropArea__onGeometryChanged";
      case 1052:
        return "c_KDDockWidgets__flutter__DropArea__onRebuildRequested";
      case 978:
        return "c_KDDockWidgets__flutter__DropArea__onResize_int_int";
      case 981:
        return "c_KDDockWidgets__flutter__DropArea__raise";
      case 982:
        return "c_KDDockWidgets__flutter__DropArea__raiseAndActivate";
      case 1056:
        return "c_KDDockWidgets__flutter__DropArea__raiseChild_View";
      case 1057:
        return "c_KDDockWidgets__flutter__DropArea__raiseWindow_View";
      case 984:
        return "c_KDDockWidgets__flutter__DropArea__releaseKeyboard";
      case 985:
        return "c_KDDockWidgets__flutter__DropArea__releaseMouse";
      case 989:
        return "c_KDDockWidgets__flutter__DropArea__setCursor_CursorShape";
      case 990:
        return "c_KDDockWidgets__flutter__DropArea__setFixedHeight_int";
      case 991:
        return "c_KDDockWidgets__flutter__DropArea__setFixedWidth_int";
      case 992:
        return "c_KDDockWidgets__flutter__DropArea__setGeometry_QRect";
      case 993:
        return "c_KDDockWidgets__flutter__DropArea__setHeight_int";
      case 994:
        return "c_KDDockWidgets__flutter__DropArea__setMaximumSize_QSize";
      case 995:
        return "c_KDDockWidgets__flutter__DropArea__setMinimumSize_QSize";
      case 996:
        return "c_KDDockWidgets__flutter__DropArea__setMouseTracking_bool";
      case 997:
        return "c_KDDockWidgets__flutter__DropArea__setObjectName_QString";
      case 998:
        return "c_KDDockWidgets__flutter__DropArea__setParent_View";
      case 1000:
        return "c_KDDockWidgets__flutter__DropArea__setSize_int_int";
      case 1001:
        return "c_KDDockWidgets__flutter__DropArea__setVisible_bool";
      case 1002:
        return "c_KDDockWidgets__flutter__DropArea__setWidth_int";
      case 1003:
        return "c_KDDockWidgets__flutter__DropArea__setWindowOpacity_double";
      case 1004:
        return "c_KDDockWidgets__flutter__DropArea__setWindowTitle_QString";
      case 1005:
        return "c_KDDockWidgets__flutter__DropArea__setZOrder_int";
      case 1006:
        return "c_KDDockWidgets__flutter__DropArea__show";
      case 1007:
        return "c_KDDockWidgets__flutter__DropArea__showMaximized";
      case 1008:
        return "c_KDDockWidgets__flutter__DropArea__showMinimized";
      case 1009:
        return "c_KDDockWidgets__flutter__DropArea__showNormal";
      case 1011:
        return "c_KDDockWidgets__flutter__DropArea__sizeHint";
      case 1013:
        return "c_KDDockWidgets__flutter__DropArea__update";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 923:
        return "activateWindow";
      case 934:
        return "close";
      case 937:
        return "createPlatformWindow";
      case 944:
        return "flags";
      case 947:
        return "geometry";
      case 949:
        return "grabMouse";
      case 952:
        return "hasFocus";
      case 954:
        return "hide";
      case 957:
        return "init";
      case 959:
        return "isActiveWindow";
      case 960:
        return "isExplicitlyHidden";
      case 961:
        return "isMaximized";
      case 962:
        return "isMinimized";
      case 1045:
        return "isMounted";
      case 963:
        return "isNull";
      case 964:
        return "isRootView";
      case 965:
        return "isVisible";
      case 966:
        return "mapFromGlobal";
      case 967:
        return "mapTo";
      case 968:
        return "mapToGlobal";
      case 969:
        return "maxSizeHint";
      case 970:
        return "minSize";
      case 971:
        return "minimumHeight";
      case 972:
        return "minimumWidth";
      case 974:
        return "move_2";
      case 975:
        return "normalGeometry";
      case 976:
        return "objectName";
      case 1046:
        return "onChildAdded";
      case 1047:
        return "onChildRemoved";
      case 1048:
        return "onChildVisibilityChanged";
      case 1050:
        return "onGeometryChanged";
      case 1052:
        return "onRebuildRequested";
      case 978:
        return "onResize_2";
      case 981:
        return "raise";
      case 982:
        return "raiseAndActivate";
      case 1056:
        return "raiseChild";
      case 1057:
        return "raiseWindow";
      case 984:
        return "releaseKeyboard";
      case 985:
        return "releaseMouse";
      case 989:
        return "setCursor";
      case 990:
        return "setFixedHeight";
      case 991:
        return "setFixedWidth";
      case 992:
        return "setGeometry";
      case 993:
        return "setHeight";
      case 994:
        return "setMaximumSize";
      case 995:
        return "setMinimumSize";
      case 996:
        return "setMouseTracking";
      case 997:
        return "setObjectName";
      case 998:
        return "setParent";
      case 1000:
        return "setSize_2";
      case 1001:
        return "setVisible";
      case 1002:
        return "setWidth";
      case 1003:
        return "setWindowOpacity";
      case 1004:
        return "setWindowTitle";
      case 1005:
        return "setZOrder";
      case 1006:
        return "show";
      case 1007:
        return "showMaximized";
      case 1008:
        return "showMinimized";
      case 1009:
        return "showNormal";
      case 1011:
        return "sizeHint";
      case 1013:
        return "update";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__DropArea__registerVirtualMethodCallback')
        .asFunction();
    final callback923 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback923, 923);
    const callbackExcept934 = 0;
    final callback934 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept934);
    registerCallback(thisCpp, callback934, 934);
    final callback937 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback937, 937);
    const callbackExcept944 = 0;
    final callback944 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept944);
    registerCallback(thisCpp, callback944, 944);
    final callback947 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback947, 947);
    final callback949 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback949, 949);
    const callbackExcept952 = 0;
    final callback952 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept952);
    registerCallback(thisCpp, callback952, 952);
    final callback954 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback954, 954);
    final callback957 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback957, 957);
    const callbackExcept959 = 0;
    final callback959 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept959);
    registerCallback(thisCpp, callback959, 959);
    const callbackExcept960 = 0;
    final callback960 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept960);
    registerCallback(thisCpp, callback960, 960);
    const callbackExcept961 = 0;
    final callback961 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept961);
    registerCallback(thisCpp, callback961, 961);
    const callbackExcept962 = 0;
    final callback962 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept962);
    registerCallback(thisCpp, callback962, 962);
    const callbackExcept1045 = 0;
    final callback1045 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMounted_calledFromC, callbackExcept1045);
    registerCallback(thisCpp, callback1045, 1045);
    const callbackExcept963 = 0;
    final callback963 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept963);
    registerCallback(thisCpp, callback963, 963);
    const callbackExcept964 = 0;
    final callback964 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept964);
    registerCallback(thisCpp, callback964, 964);
    const callbackExcept965 = 0;
    final callback965 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept965);
    registerCallback(thisCpp, callback965, 965);
    final callback966 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback966, 966);
    final callback967 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback967, 967);
    final callback968 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback968, 968);
    final callback969 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback969, 969);
    final callback970 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.minSize_calledFromC);
    registerCallback(thisCpp, callback970, 970);
    const callbackExcept971 = 0;
    final callback971 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumHeight_calledFromC, callbackExcept971);
    registerCallback(thisCpp, callback971, 971);
    const callbackExcept972 = 0;
    final callback972 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsCore.View.minimumWidth_calledFromC, callbackExcept972);
    registerCallback(thisCpp, callback972, 972);
    final callback974 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback974, 974);
    final callback975 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback975, 975);
    final callback976 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.objectName_calledFromC);
    registerCallback(thisCpp, callback976, 976);
    final callback1046 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback1046, 1046);
    final callback1047 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback1047, 1047);
    final callback1048 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback1048, 1048);
    final callback1050 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback1050, 1050);
    final callback1052 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback1052, 1052);
    const callbackExcept978 = 0;
    final callback978 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept978);
    registerCallback(thisCpp, callback978, 978);
    final callback981 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback981, 981);
    final callback982 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback982, 982);
    final callback1056 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseChild_calledFromC);
    registerCallback(thisCpp, callback1056, 1056);
    final callback1057 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseWindow_calledFromC);
    registerCallback(thisCpp, callback1057, 1057);
    final callback984 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback984, 984);
    final callback985 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback985, 985);
    final callback989 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback989, 989);
    final callback990 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback990, 990);
    final callback991 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback991, 991);
    final callback992 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback992, 992);
    final callback993 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback993, 993);
    final callback994 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback994, 994);
    final callback995 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback995, 995);
    final callback996 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback996, 996);
    final callback997 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setObjectName_calledFromC);
    registerCallback(thisCpp, callback997, 997);
    final callback998 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback998, 998);
    final callback1000 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback1000, 1000);
    final callback1001 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback1001, 1001);
    final callback1002 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback1002, 1002);
    final callback1003 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback1003, 1003);
    final callback1004 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback1004, 1004);
    final callback1005 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback1005, 1005);
    final callback1006 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback1006, 1006);
    final callback1007 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback1007, 1007);
    final callback1008 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback1008, 1008);
    final callback1009 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback1009, 1009);
    final callback1011 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.sizeHint_calledFromC);
    registerCallback(thisCpp, callback1011, 1011);
    final callback1013 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback1013, 1013);
  }
}
