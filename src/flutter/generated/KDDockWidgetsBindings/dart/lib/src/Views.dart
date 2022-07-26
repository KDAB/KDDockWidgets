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
//tag=1024

//tag=1027
// asView_flutter(KDDockWidgets::Controller * controller)
View_flutter asView_flutter(Controller? controller) {
//tag=1028
  final voidstar_Func_voidstar func = _dylib
      .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
          'c_static_KDDockWidgets__Views__asView_flutter_Controller')
      .asFunction();
//tag=1033
  ffi.Pointer<void> result =
      func(controller == null ? ffi.nullptr : controller.thisCpp);
  return View_flutter.fromCppPointer(result, false);
}
//tag=1024

//tag=1027
// asView_flutter(KDDockWidgets::View * view)
View_flutter asView_flutter_2(View? view) {
//tag=1028
  final voidstar_Func_voidstar func = _dylib
      .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
          'c_static_KDDockWidgets__Views__asView_flutter_View')
      .asFunction();
//tag=1033
  ffi.Pointer<void> result = func(view == null ? ffi.nullptr : view.thisCpp);
  return View_flutter.fromCppPointer(result, false);
}
