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

class KDDockWidgets_Location {
  static const Location_None = 0;
  static const Location_OnLeft = 1;
  static const Location_OnTop = 2;
  static const Location_OnRight = 3;
  static const Location_OnBottom = 4;
}

class KDDockWidgets_MainWindowOption {
  static const MainWindowOption_None = 0;
  static const MainWindowOption_HasCentralFrame = 1;
  static const MainWindowOption_MDI = 2;
  static const MainWindowOption_HasCentralWidget = 5;
}

class KDDockWidgets_DockWidgetOption {
  static const DockWidgetOption_None = 0;
  static const DockWidgetOption_NotClosable = 1;
  static const DockWidgetOption_NotDockable = 2;
  static const DockWidgetOption_DeleteOnClose = 4;
  static const DockWidgetOption_MDINestable = 8;
}

class KDDockWidgets_LayoutSaverOption {
  static const None = 0;
  static const Skip = 1;
}

class KDDockWidgets_IconPlace {
  static const TitleBar = 1;
  static const TabBar = 2;
  static const ToggleAction = 4;
  static const All = 7;
}

class KDDockWidgets_FrontendType {
  static const QtWidgets = 1;
  static const QtQuick = 2;
  static const Flutter = 3;
  static const Dummy = 4;
}

class KDDockWidgets_DefaultSizeMode {
  static const ItemSize = 0;
  static const Fair = 1;
  static const FairButFloor = 2;
  static const NoDefaultSizeMode = 3;
}

class KDDockWidgets_AddingOption {
  static const AddingOption_None = 0;
  static const AddingOption_StartHidden = 1;
}

class KDDockWidgets_InitialVisibilityOption {
  static const StartVisible = 0;
  static const StartHidden = 1;
  static const PreserveCurrentTab = 2;
}

class KDDockWidgets_DropLocation {
  static const DropLocation_None = 0;
  static const DropLocation_Left = 1;
  static const DropLocation_Top = 2;
  static const DropLocation_Right = 4;
  static const DropLocation_Bottom = 8;
  static const DropLocation_Center = 16;
  static const DropLocation_OutterLeft = 32;
  static const DropLocation_OutterTop = 64;
  static const DropLocation_OutterRight = 128;
  static const DropLocation_OutterBottom = 256;
  static const DropLocation_Inner = 15;
  static const DropLocation_Outter = 480;
  static const DropLocation_Horizontal = 165;
  static const DropLocation_Vertical = 330;
}

class KDDockWidgets_Type {
  static const FIRST = 1;
  static const None = 0;
  static const Frame = 1;
  static const TitleBar = 2;
  static const TabBar = 4;
  static const Stack = 8;
  static const FloatingWindow = 16;
  static const Separator = 32;
  static const DockWidget = 64;
  static const MDIArea = 128;
  static const LayoutItem = 256;
  static const SideBar = 512;
  static const MainWindow = 1024;
  static const ViewWrapper = 2048;
  static const DropArea = 4096;
  static const MDILayout = 8192;
  static const RubberBand = 16384;
  static const DropAreaIndicatorOverlay = 32768;
  static const LAST = 16384;
} // initFrontend(KDDockWidgets::FrontendType arg__1)

initFrontend(int arg__1) {
  final void_Func_int func = _dylib
      .lookup<ffi.NativeFunction<void_Func_ffi_Int32_FFI>>(
          'c_static_KDDockWidgets__initFrontend_FrontendType')
      .asFunction();
  func(arg__1);
} // locationStr(KDDockWidgets::Location loc)

QString locationStr(int loc) {
  final voidstar_Func_int func = _dylib
      .lookup<ffi.NativeFunction<voidstar_Func_ffi_Int32_FFI>>(
          'c_static_KDDockWidgets__locationStr_Location')
      .asFunction();
  ffi.Pointer<void> result = func(loc);
  return QString.fromCppPointer(result, true);
}
