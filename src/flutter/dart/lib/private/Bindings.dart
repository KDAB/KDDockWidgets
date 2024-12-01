/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgets/private/kddw_bindings.dart';

import 'dart:ffi' as ffi;
import 'dart:io' show Platform;

final finalizerFunc = (String name) {
  return Bindings.instance.dyLib
      .lookup<ffi.NativeFunction<ffi.Void Function(ffi.Pointer)>>(name);
};

class Bindings {
  static final Bindings _instance = Bindings._create();
  late ffi.DynamicLibrary dyLib;
  late NativeLibrary nativeLibrary;

  Bindings._create() {
    var libPath = Platform.environment['KDDW_BINDINGS_LIB'] ?? '';
    if (libPath.isEmpty) {
      throw Exception('Failed to read KDDW_BINDINGS_LIB env var');
    }

    dyLib = ffi.DynamicLibrary.open(libPath);
    nativeLibrary = NativeLibrary(dyLib);
  }

  static Bindings get instance {
    return _instance;
  }
}
