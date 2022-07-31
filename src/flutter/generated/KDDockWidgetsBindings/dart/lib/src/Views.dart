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

var _dylib = Library.instance()
    .dylib; // asView_flutter(KDDockWidgets::Controller * controller)
View_flutter asView_flutter(Controller? controller) {
  final voidstar_Func_voidstar func = _dylib
      .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
          'c_static_KDDockWidgets__Views__asView_flutter_Controller')
      .asFunction();
  ffi.Pointer<void> result =
      func(controller == null ? ffi.nullptr : controller.thisCpp);
  return View_flutter.fromCppPointer(result, false);
} // asView_flutter(KDDockWidgets::View * view)

View_flutter asView_flutter_2(View? view) {
  final voidstar_Func_voidstar func = _dylib
      .lookup<ffi.NativeFunction<voidstar_Func_voidstar_FFI>>(
          'c_static_KDDockWidgets__Views__asView_flutter_View')
      .asFunction();
  ffi.Pointer<void> result = func(view == null ? ffi.nullptr : view.thisCpp);
  return View_flutter.fromCppPointer(result, false);
}
