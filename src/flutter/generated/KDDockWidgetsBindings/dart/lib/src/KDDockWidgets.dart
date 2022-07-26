/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

//tag=1052
import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';
import 'TypeHelpers.dart';
import '../Bindings.dart';
import '../FinalizerHelpers.dart';

//tag=1051
var _dylib = Library.instance().dylib;

//tag=1038
class KDDockWidgets_MainWindowOption {
  static const MainWindowOption_None = 0;
  static const MainWindowOption_HasCentralFrame = 1;
  static const MainWindowOption_MDI = 2;
  static const MainWindowOption_HasCentralWidget = 5;
}
//tag=1024

//tag=1027
// qt_getEnumName(QFlags<KDDockWidgets::MainWindowOption> arg__1)
String qt_getEnumName(int arg__1) {
//tag=1028
  final string_Func_int func = _dylib
      .lookup<ffi.NativeFunction<string_Func_ffi_Int32_FFI>>(
          'c_static_KDDockWidgets__qt_getEnumName_MainWindowOptions')
      .asFunction();
//tag=1032
  ffi.Pointer<Utf8> result = func(arg__1);
  return result.toDartString();
}
