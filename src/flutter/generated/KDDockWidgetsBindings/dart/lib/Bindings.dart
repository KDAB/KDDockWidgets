/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
export 'src/Config.dart' show Config;
export 'src/DropArea.dart' show DropArea;
export 'src/Layout.dart' show Layout;
export 'src/View_flutter.dart' show View_flutter;
export 'src/View.dart' show View;
export 'src/Controller.dart' show Controller;
export 'src/ClassicIndicators.dart' show ClassicIndicators;
export 'src/CreateViewOptions.dart' show CreateViewOptions;
export 'src/InitialOption.dart' show InitialOption;
export 'src/Platform_flutter.dart' show Platform_flutter;
export 'src/ViewFactory_flutter.dart' show ViewFactory_flutter;
export 'src/ViewFactory.dart' show ViewFactory;
export 'src/ClassicIndicatorWindowViewInterface.dart'
    show ClassicIndicatorWindowViewInterface;
export 'src/Views.dart' show asView_flutter, asView_flutter;
export 'src/KDDockWidgets.dart'
    show
        locationStr,
        qt_getEnumName,
        qt_getEnumName,
        qt_getEnumName,
        KDDockWidgets_Location,
        KDDockWidgets_MainWindowOption,
        KDDockWidgets_DropLocation,
        KDDockWidgets_Type;
export 'src/QByteArray.dart' show QByteArray;
export 'src/QEvent.dart' show QEvent, QEvent_Type;
export 'src/QList.dart' show QList;
export 'src/QObject.dart' show QObject;
export 'src/QPoint.dart' show QPoint;
export 'src/QRect.dart' show QRect;
export 'src/QSize.dart' show QSize;
export 'src/QString.dart' show QString;
export 'src/Qt.dart' show qt_getEnumName, qt_getEnumName, Qt_CursorShape;
import 'dart:ffi' as ffi;
import 'dart:io' show Platform;

String bindingsLibraryName(String name) {
  if (Platform.isWindows) return "${name}.dll";
  if (Platform.isMacOS) return "lib${name}.dylib";
  return "lib${name}.so";
}

class Library {
  var _dylib;

  ffi.DynamicLibrary get dylib {
    return _dylib;
  }

  static var _library = null;

  factory Library.instance() {
    // Singleton impl.
    if (_library == null) _library = Library._();
    return _library;
  }

  Library._() {
    // DYLD_LIBRARY_PATH doesn't work by default on newer macOS. Instead
    // introduce our own env variable for the same use case
    var bindingsPath = Platform.environment["DARTAGNAN_BINDINGSLIB_PATH"] ?? "";

    var libraryPath = bindingsLibraryName("kddockwidgets");
    if (!bindingsPath.isEmpty) {
      libraryPath = bindingsPath + "/" + libraryPath;
    }

    _dylib = ffi.DynamicLibrary.open(libraryPath);
  }
}
