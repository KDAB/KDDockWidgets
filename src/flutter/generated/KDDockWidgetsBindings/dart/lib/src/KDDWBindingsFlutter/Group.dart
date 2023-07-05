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

class Group extends KDDWBindingsFlutter.View {
  Group.fromCppPointer(var cppPointer, [var needsAutoDelete = false])
      : super.fromCppPointer(cppPointer, needsAutoDelete) {}
  Group.init() : super.init() {}
  factory Group.fromCache(var cppPointer, [needsAutoDelete = false]) {
    if (KDDWBindingsCore.View.isCached(cppPointer)) {
      var instance =
          KDDWBindingsCore.View.s_dartInstanceByCppPtr[cppPointer.address];
      if (instance != null) return instance as Group;
    }
    return Group.fromCppPointer(cppPointer, needsAutoDelete);
  } //Group(KDDockWidgets::Core::Group * controller, KDDockWidgets::Core::View * parent)
  Group(KDDWBindingsCore.Group? controller,
      {required KDDWBindingsCore.View? parent})
      : super.init() {
    final voidstar_Func_voidstar_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Group__constructor_Group_View')
        .asFunction();
    thisCpp = func(controller == null ? ffi.nullptr : controller.thisCpp,
        parent == null ? ffi.nullptr : parent.thisCpp);
    KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] = this;
    registerCallbacks();
  }
  static void activateWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::activateWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.activateWindow();
  }

  static int close_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print("Dart instance not found for Group::close()! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.close();
    return result ? 1 : 0;
  }

  static void createPlatformWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::createPlatformWindow()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.createPlatformWindow();
  } // currentIndex() const

  int currentIndex() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Group__currentIndex')
        .asFunction();
    return func(thisCpp);
  } // dragRect() const

  QRect dragRect() {
    final voidstar_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
            cFunctionSymbolName(894))
        .asFunction();
    ffi.Pointer<void> result = func(thisCpp);
    return QRect.fromCppPointer(result, true);
  }

  static ffi.Pointer<void> dragRect_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::dragRect() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.dragRect();
    return result.thisCpp;
  }

  static int flags_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::flags() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.flags();
    return result;
  }

  static ffi.Pointer<void> geometry_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::geometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.geometry();
    return result.thisCpp;
  }

  static void grabMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::grabMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.grabMouse();
  }

  static int hasFocus_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::hasFocus() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.hasFocus();
    return result ? 1 : 0;
  }

  static void hide_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print("Dart instance not found for Group::hide()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.hide();
  }

  static void init_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print("Dart instance not found for Group::init()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.init();
  }

  static int isActiveWindow_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isActiveWindow() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isActiveWindow();
    return result ? 1 : 0;
  }

  static int isExplicitlyHidden_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isExplicitlyHidden() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isExplicitlyHidden();
    return result ? 1 : 0;
  }

  static int isMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isMaximized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMaximized();
    return result ? 1 : 0;
  }

  static int isMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isMinimized() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMinimized();
    return result ? 1 : 0;
  }

  static int isMounted_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isMounted() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isMounted();
    return result ? 1 : 0;
  }

  static int isNull_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isNull() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isNull();
    return result ? 1 : 0;
  }

  static int isRootView_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isRootView() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isRootView();
    return result ? 1 : 0;
  }

  static int isVisible_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::isVisible() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.isVisible();
    return result ? 1 : 0;
  }

  static ffi.Pointer<void> mapFromGlobal_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> globalPt) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::mapFromGlobal(QPoint globalPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapFromGlobal(QPoint.fromCppPointer(globalPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> mapTo_calledFromC(ffi.Pointer<void> thisCpp,
      ffi.Pointer<void>? parent, ffi.Pointer<void> pos) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::mapTo(KDDockWidgets::Core::View * parent, QPoint pos) const! (${thisCpp.address})");
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
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::mapToGlobal(QPoint localPt) const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.mapToGlobal(QPoint.fromCppPointer(localPt));
    return result.thisCpp;
  }

  static ffi.Pointer<void> maxSizeHint_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::maxSizeHint() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.maxSizeHint();
    return result.thisCpp;
  }

  static ffi.Pointer<void> minSize_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::minSize() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.minSize();
    return result.thisCpp;
  }

  static void move_2_calledFromC(ffi.Pointer<void> thisCpp, int x, int y) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::move(int x, int y)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.move_2(x, y);
  } // nonContentsHeight() const

  int nonContentsHeight() {
    final int_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<int_Func_voidstar_FFI>>(
            cFunctionSymbolName(895))
        .asFunction();
    return func(thisCpp);
  }

  static int nonContentsHeight_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::nonContentsHeight() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.nonContentsHeight();
    return result;
  }

  static ffi.Pointer<void> normalGeometry_calledFromC(
      ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::normalGeometry() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.normalGeometry();
    return result.thisCpp;
  }

  static void onChildAdded_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::onChildAdded(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildAdded((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildRemoved_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::onChildRemoved(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildRemoved((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onChildVisibilityChanged_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::onChildVisibilityChanged(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onChildVisibilityChanged(
        (childView == null || childView.address == 0)
            ? null
            : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void onGeometryChanged_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::onGeometryChanged()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onGeometryChanged();
  }

  static void onRebuildRequested_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::onRebuildRequested()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.onRebuildRequested();
  }

  static int onResize_2_calledFromC(ffi.Pointer<void> thisCpp, int h, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::onResize(int h, int w)! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.onResize_2(h, w);
    return result ? 1 : 0;
  }

  static void raise_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print("Dart instance not found for Group::raise()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raise();
  }

  static void raiseAndActivate_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::raiseAndActivate()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseAndActivate();
  }

  static void raiseChild_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? childView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::raiseChild(KDDockWidgets::Core::View * childView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseChild((childView == null || childView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(childView));
  }

  static void raiseWindow_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? rootView) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::raiseWindow(KDDockWidgets::Core::View * rootView)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.raiseWindow((rootView == null || rootView.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(rootView));
  }

  static void releaseKeyboard_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::releaseKeyboard()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseKeyboard();
  }

  static void releaseMouse_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::releaseMouse()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.releaseMouse();
  }

  static void setCursor_calledFromC(ffi.Pointer<void> thisCpp, int shape) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setCursor(Qt::CursorShape shape)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setCursor(shape);
  }

  static void setFixedHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setFixedHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedHeight(h);
  }

  static void setFixedWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setFixedWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setFixedWidth(w);
  }

  static void setGeometry_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> geometry) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setGeometry(QRect geometry)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setGeometry(QRect.fromCppPointer(geometry));
  }

  static void setHeight_calledFromC(ffi.Pointer<void> thisCpp, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setHeight(int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setHeight(h);
  }

  static void setMaximumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setMaximumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMaximumSize(QSize.fromCppPointer(sz));
  }

  static void setMinimumSize_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void> sz) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setMinimumSize(QSize sz)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMinimumSize(QSize.fromCppPointer(sz));
  }

  static void setMouseTracking_calledFromC(
      ffi.Pointer<void> thisCpp, int enable) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setMouseTracking(bool enable)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setMouseTracking(enable != 0);
  }

  static void setParent_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? parent) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setParent(KDDockWidgets::Core::View * parent)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setParent((parent == null || parent.address == 0)
        ? null
        : KDDWBindingsCore.View.fromCppPointer(parent));
  }

  static void setSize_2_calledFromC(ffi.Pointer<void> thisCpp, int w, int h) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setSize(int w, int h)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setSize_2(w, h);
  }

  static void setViewName_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? name) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setViewName(const QString & name)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setViewName(QString.fromCppPointer(name).toDartString());
  }

  static void setVisible_calledFromC(ffi.Pointer<void> thisCpp, int visible) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setVisible(bool visible)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setVisible(visible != 0);
  }

  static void setWidth_calledFromC(ffi.Pointer<void> thisCpp, int w) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setWidth(int w)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWidth(w);
  }

  static void setWindowOpacity_calledFromC(
      ffi.Pointer<void> thisCpp, double v) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setWindowOpacity(double v)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowOpacity(v);
  }

  static void setWindowTitle_calledFromC(
      ffi.Pointer<void> thisCpp, ffi.Pointer<void>? title) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setWindowTitle(const QString & title)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setWindowTitle(QString.fromCppPointer(title).toDartString());
  }

  static void setZOrder_calledFromC(ffi.Pointer<void> thisCpp, int z) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::setZOrder(int z)! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.setZOrder(z);
  }

  static void show_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print("Dart instance not found for Group::show()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.show();
  }

  static void showMaximized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::showMaximized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMaximized();
  }

  static void showMinimized_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::showMinimized()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showMinimized();
  }

  static void showNormal_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::showNormal()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.showNormal();
  }

  static void update_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::update()! (${thisCpp.address})");
      throw Error();
    }
    dartInstance.update();
  }

  static ffi.Pointer<void> viewName_calledFromC(ffi.Pointer<void> thisCpp) {
    var dartInstance =
        KDDWBindingsCore.View.s_dartInstanceByCppPtr[thisCpp.address] as Group;
    if (dartInstance == null) {
      print(
          "Dart instance not found for Group::viewName() const! (${thisCpp.address})");
      throw Error();
    }
    final result = dartInstance.viewName();
    return result.thisCpp;
  }

  void release() {
    final void_Func_voidstar func = _dylib
        .lookup<ffi.NativeFunction<void_Func_voidstar_FFI>>(
            'c_KDDockWidgets__flutter__Group__destructor')
        .asFunction();
    func(thisCpp);
  }

  String cFunctionSymbolName(int methodId) {
    switch (methodId) {
      case 732:
        return "c_KDDockWidgets__flutter__Group__activateWindow";
      case 742:
        return "c_KDDockWidgets__flutter__Group__close";
      case 744:
        return "c_KDDockWidgets__flutter__Group__createPlatformWindow";
      case 894:
        return "c_KDDockWidgets__flutter__Group__dragRect";
      case 750:
        return "c_KDDockWidgets__flutter__Group__flags";
      case 751:
        return "c_KDDockWidgets__flutter__Group__geometry";
      case 752:
        return "c_KDDockWidgets__flutter__Group__grabMouse";
      case 755:
        return "c_KDDockWidgets__flutter__Group__hasFocus";
      case 757:
        return "c_KDDockWidgets__flutter__Group__hide";
      case 759:
        return "c_KDDockWidgets__flutter__Group__init";
      case 761:
        return "c_KDDockWidgets__flutter__Group__isActiveWindow";
      case 762:
        return "c_KDDockWidgets__flutter__Group__isExplicitlyHidden";
      case 763:
        return "c_KDDockWidgets__flutter__Group__isMaximized";
      case 764:
        return "c_KDDockWidgets__flutter__Group__isMinimized";
      case 834:
        return "c_KDDockWidgets__flutter__Group__isMounted";
      case 765:
        return "c_KDDockWidgets__flutter__Group__isNull";
      case 766:
        return "c_KDDockWidgets__flutter__Group__isRootView";
      case 767:
        return "c_KDDockWidgets__flutter__Group__isVisible";
      case 768:
        return "c_KDDockWidgets__flutter__Group__mapFromGlobal_QPoint";
      case 769:
        return "c_KDDockWidgets__flutter__Group__mapTo_View_QPoint";
      case 770:
        return "c_KDDockWidgets__flutter__Group__mapToGlobal_QPoint";
      case 771:
        return "c_KDDockWidgets__flutter__Group__maxSizeHint";
      case 772:
        return "c_KDDockWidgets__flutter__Group__minSize";
      case 776:
        return "c_KDDockWidgets__flutter__Group__move_int_int";
      case 895:
        return "c_KDDockWidgets__flutter__Group__nonContentsHeight";
      case 777:
        return "c_KDDockWidgets__flutter__Group__normalGeometry";
      case 837:
        return "c_KDDockWidgets__flutter__Group__onChildAdded_View";
      case 838:
        return "c_KDDockWidgets__flutter__Group__onChildRemoved_View";
      case 839:
        return "c_KDDockWidgets__flutter__Group__onChildVisibilityChanged_View";
      case 841:
        return "c_KDDockWidgets__flutter__Group__onGeometryChanged";
      case 843:
        return "c_KDDockWidgets__flutter__Group__onRebuildRequested";
      case 779:
        return "c_KDDockWidgets__flutter__Group__onResize_int_int";
      case 781:
        return "c_KDDockWidgets__flutter__Group__raise";
      case 782:
        return "c_KDDockWidgets__flutter__Group__raiseAndActivate";
      case 846:
        return "c_KDDockWidgets__flutter__Group__raiseChild_View";
      case 847:
        return "c_KDDockWidgets__flutter__Group__raiseWindow_View";
      case 784:
        return "c_KDDockWidgets__flutter__Group__releaseKeyboard";
      case 785:
        return "c_KDDockWidgets__flutter__Group__releaseMouse";
      case 788:
        return "c_KDDockWidgets__flutter__Group__setCursor_CursorShape";
      case 789:
        return "c_KDDockWidgets__flutter__Group__setFixedHeight_int";
      case 790:
        return "c_KDDockWidgets__flutter__Group__setFixedWidth_int";
      case 791:
        return "c_KDDockWidgets__flutter__Group__setGeometry_QRect";
      case 792:
        return "c_KDDockWidgets__flutter__Group__setHeight_int";
      case 793:
        return "c_KDDockWidgets__flutter__Group__setMaximumSize_QSize";
      case 794:
        return "c_KDDockWidgets__flutter__Group__setMinimumSize_QSize";
      case 795:
        return "c_KDDockWidgets__flutter__Group__setMouseTracking_bool";
      case 796:
        return "c_KDDockWidgets__flutter__Group__setParent_View";
      case 798:
        return "c_KDDockWidgets__flutter__Group__setSize_int_int";
      case 799:
        return "c_KDDockWidgets__flutter__Group__setViewName_QString";
      case 800:
        return "c_KDDockWidgets__flutter__Group__setVisible_bool";
      case 801:
        return "c_KDDockWidgets__flutter__Group__setWidth_int";
      case 802:
        return "c_KDDockWidgets__flutter__Group__setWindowOpacity_double";
      case 803:
        return "c_KDDockWidgets__flutter__Group__setWindowTitle_QString";
      case 804:
        return "c_KDDockWidgets__flutter__Group__setZOrder_int";
      case 805:
        return "c_KDDockWidgets__flutter__Group__show";
      case 806:
        return "c_KDDockWidgets__flutter__Group__showMaximized";
      case 807:
        return "c_KDDockWidgets__flutter__Group__showMinimized";
      case 808:
        return "c_KDDockWidgets__flutter__Group__showNormal";
      case 810:
        return "c_KDDockWidgets__flutter__Group__update";
      case 811:
        return "c_KDDockWidgets__flutter__Group__viewName";
    }
    return super.cFunctionSymbolName(methodId);
  }

  static String methodNameFromId(int methodId) {
    switch (methodId) {
      case 732:
        return "activateWindow";
      case 742:
        return "close";
      case 744:
        return "createPlatformWindow";
      case 894:
        return "dragRect";
      case 750:
        return "flags";
      case 751:
        return "geometry";
      case 752:
        return "grabMouse";
      case 755:
        return "hasFocus";
      case 757:
        return "hide";
      case 759:
        return "init";
      case 761:
        return "isActiveWindow";
      case 762:
        return "isExplicitlyHidden";
      case 763:
        return "isMaximized";
      case 764:
        return "isMinimized";
      case 834:
        return "isMounted";
      case 765:
        return "isNull";
      case 766:
        return "isRootView";
      case 767:
        return "isVisible";
      case 768:
        return "mapFromGlobal";
      case 769:
        return "mapTo";
      case 770:
        return "mapToGlobal";
      case 771:
        return "maxSizeHint";
      case 772:
        return "minSize";
      case 776:
        return "move_2";
      case 895:
        return "nonContentsHeight";
      case 777:
        return "normalGeometry";
      case 837:
        return "onChildAdded";
      case 838:
        return "onChildRemoved";
      case 839:
        return "onChildVisibilityChanged";
      case 841:
        return "onGeometryChanged";
      case 843:
        return "onRebuildRequested";
      case 779:
        return "onResize_2";
      case 781:
        return "raise";
      case 782:
        return "raiseAndActivate";
      case 846:
        return "raiseChild";
      case 847:
        return "raiseWindow";
      case 784:
        return "releaseKeyboard";
      case 785:
        return "releaseMouse";
      case 788:
        return "setCursor";
      case 789:
        return "setFixedHeight";
      case 790:
        return "setFixedWidth";
      case 791:
        return "setGeometry";
      case 792:
        return "setHeight";
      case 793:
        return "setMaximumSize";
      case 794:
        return "setMinimumSize";
      case 795:
        return "setMouseTracking";
      case 796:
        return "setParent";
      case 798:
        return "setSize_2";
      case 799:
        return "setViewName";
      case 800:
        return "setVisible";
      case 801:
        return "setWidth";
      case 802:
        return "setWindowOpacity";
      case 803:
        return "setWindowTitle";
      case 804:
        return "setZOrder";
      case 805:
        return "show";
      case 806:
        return "showMaximized";
      case 807:
        return "showMinimized";
      case 808:
        return "showNormal";
      case 810:
        return "update";
      case 811:
        return "viewName";
    }
    throw Error();
  }

  void registerCallbacks() {
    assert(thisCpp != null);
    final RegisterMethodIsReimplementedCallback registerCallback = _dylib
        .lookup<ffi.NativeFunction<RegisterMethodIsReimplementedCallback_FFI>>(
            'c_KDDockWidgets__flutter__Group__registerVirtualMethodCallback')
        .asFunction();
    final callback732 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.activateWindow_calledFromC);
    registerCallback(thisCpp, callback732, 732);
    const callbackExcept742 = 0;
    final callback742 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.close_calledFromC, callbackExcept742);
    registerCallback(thisCpp, callback742, 742);
    final callback744 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.createPlatformWindow_calledFromC);
    registerCallback(thisCpp, callback744, 744);
    final callback894 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Group.dragRect_calledFromC);
    registerCallback(thisCpp, callback894, 894);
    const callbackExcept750 = 0;
    final callback750 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.flags_calledFromC, callbackExcept750);
    registerCallback(thisCpp, callback750, 750);
    final callback751 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.geometry_calledFromC);
    registerCallback(thisCpp, callback751, 751);
    final callback752 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.grabMouse_calledFromC);
    registerCallback(thisCpp, callback752, 752);
    const callbackExcept755 = 0;
    final callback755 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hasFocus_calledFromC, callbackExcept755);
    registerCallback(thisCpp, callback755, 755);
    final callback757 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.hide_calledFromC);
    registerCallback(thisCpp, callback757, 757);
    final callback759 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsCore.View.init_calledFromC);
    registerCallback(thisCpp, callback759, 759);
    const callbackExcept761 = 0;
    final callback761 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isActiveWindow_calledFromC, callbackExcept761);
    registerCallback(thisCpp, callback761, 761);
    const callbackExcept762 = 0;
    final callback762 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isExplicitlyHidden_calledFromC,
        callbackExcept762);
    registerCallback(thisCpp, callback762, 762);
    const callbackExcept763 = 0;
    final callback763 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMaximized_calledFromC, callbackExcept763);
    registerCallback(thisCpp, callback763, 763);
    const callbackExcept764 = 0;
    final callback764 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMinimized_calledFromC, callbackExcept764);
    registerCallback(thisCpp, callback764, 764);
    const callbackExcept834 = 0;
    final callback834 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isMounted_calledFromC, callbackExcept834);
    registerCallback(thisCpp, callback834, 834);
    const callbackExcept765 = 0;
    final callback765 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsCore.View.isNull_calledFromC, callbackExcept765);
    registerCallback(thisCpp, callback765, 765);
    const callbackExcept766 = 0;
    final callback766 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isRootView_calledFromC, callbackExcept766);
    registerCallback(thisCpp, callback766, 766);
    const callbackExcept767 = 0;
    final callback767 = ffi.Pointer.fromFunction<bool_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.isVisible_calledFromC, callbackExcept767);
    registerCallback(thisCpp, callback767, 767);
    final callback768 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapFromGlobal_calledFromC);
    registerCallback(thisCpp, callback768, 768);
    final callback769 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapTo_calledFromC);
    registerCallback(thisCpp, callback769, 769);
    final callback770 =
        ffi.Pointer.fromFunction<voidstar_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.mapToGlobal_calledFromC);
    registerCallback(thisCpp, callback770, 770);
    final callback771 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Group.maxSizeHint_calledFromC);
    registerCallback(thisCpp, callback771, 771);
    final callback772 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Group.minSize_calledFromC);
    registerCallback(thisCpp, callback772, 772);
    final callback776 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.move_2_calledFromC);
    registerCallback(thisCpp, callback776, 776);
    const callbackExcept895 = 0;
    final callback895 = ffi.Pointer.fromFunction<int_Func_voidstar_FFI>(
        KDDWBindingsFlutter.Group.nonContentsHeight_calledFromC,
        callbackExcept895);
    registerCallback(thisCpp, callback895, 895);
    final callback777 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.normalGeometry_calledFromC);
    registerCallback(thisCpp, callback777, 777);
    final callback837 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildAdded_calledFromC);
    registerCallback(thisCpp, callback837, 837);
    final callback838 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildRemoved_calledFromC);
    registerCallback(thisCpp, callback838, 838);
    final callback839 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.onChildVisibilityChanged_calledFromC);
    registerCallback(thisCpp, callback839, 839);
    final callback841 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onGeometryChanged_calledFromC);
    registerCallback(thisCpp, callback841, 841);
    final callback843 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.onRebuildRequested_calledFromC);
    registerCallback(thisCpp, callback843, 843);
    const callbackExcept779 = 0;
    final callback779 =
        ffi.Pointer.fromFunction<bool_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsCore.View.onResize_2_calledFromC, callbackExcept779);
    registerCallback(thisCpp, callback779, 779);
    final callback781 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raise_calledFromC);
    registerCallback(thisCpp, callback781, 781);
    final callback782 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.raiseAndActivate_calledFromC);
    registerCallback(thisCpp, callback782, 782);
    final callback846 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseChild_calledFromC);
    registerCallback(thisCpp, callback846, 846);
    final callback847 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.raiseWindow_calledFromC);
    registerCallback(thisCpp, callback847, 847);
    final callback784 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseKeyboard_calledFromC);
    registerCallback(thisCpp, callback784, 784);
    final callback785 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.releaseMouse_calledFromC);
    registerCallback(thisCpp, callback785, 785);
    final callback788 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setCursor_calledFromC);
    registerCallback(thisCpp, callback788, 788);
    final callback789 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedHeight_calledFromC);
    registerCallback(thisCpp, callback789, 789);
    final callback790 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setFixedWidth_calledFromC);
    registerCallback(thisCpp, callback790, 790);
    final callback791 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setGeometry_calledFromC);
    registerCallback(thisCpp, callback791, 791);
    final callback792 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setHeight_calledFromC);
    registerCallback(thisCpp, callback792, 792);
    final callback793 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMaximumSize_calledFromC);
    registerCallback(thisCpp, callback793, 793);
    final callback794 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setMinimumSize_calledFromC);
    registerCallback(thisCpp, callback794, 794);
    final callback795 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setMouseTracking_calledFromC);
    registerCallback(thisCpp, callback795, 795);
    final callback796 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setParent_calledFromC);
    registerCallback(thisCpp, callback796, 796);
    final callback798 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setSize_2_calledFromC);
    registerCallback(thisCpp, callback798, 798);
    final callback799 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setViewName_calledFromC);
    registerCallback(thisCpp, callback799, 799);
    final callback800 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int8_FFI>(
            KDDWBindingsFlutter.View.setVisible_calledFromC);
    registerCallback(thisCpp, callback800, 800);
    final callback801 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setWidth_calledFromC);
    registerCallback(thisCpp, callback801, 801);
    final callback802 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Double_FFI>(
            KDDWBindingsFlutter.View.setWindowOpacity_calledFromC);
    registerCallback(thisCpp, callback802, 802);
    final callback803 =
        ffi.Pointer.fromFunction<void_Func_voidstar_voidstar_FFI>(
            KDDWBindingsFlutter.View.setWindowTitle_calledFromC);
    registerCallback(thisCpp, callback803, 803);
    final callback804 =
        ffi.Pointer.fromFunction<void_Func_voidstar_ffi_Int32_FFI>(
            KDDWBindingsFlutter.View.setZOrder_calledFromC);
    registerCallback(thisCpp, callback804, 804);
    final callback805 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.show_calledFromC);
    registerCallback(thisCpp, callback805, 805);
    final callback806 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMaximized_calledFromC);
    registerCallback(thisCpp, callback806, 806);
    final callback807 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showMinimized_calledFromC);
    registerCallback(thisCpp, callback807, 807);
    final callback808 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.showNormal_calledFromC);
    registerCallback(thisCpp, callback808, 808);
    final callback810 = ffi.Pointer.fromFunction<void_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.update_calledFromC);
    registerCallback(thisCpp, callback810, 810);
    final callback811 = ffi.Pointer.fromFunction<voidstar_Func_voidstar_FFI>(
        KDDWBindingsFlutter.View.viewName_calledFromC);
    registerCallback(thisCpp, callback811, 811);
  }
}
