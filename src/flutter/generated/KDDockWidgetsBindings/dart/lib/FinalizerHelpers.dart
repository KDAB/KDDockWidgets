/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
/*
Copyright 2020, the Dart project authors.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of Google Inc. nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// File copied from https://github.com/mraleph/dartvm_api_vs_ffi.git
// commit d634ca401ced4a

// Adjusted for null safety

import 'dart:ffi' as ffi;
import 'package:ffi/ffi.dart';

typedef Dart_WeakPersistentHandleFinalizer_Type = ffi.Void Function(
    ffi.Pointer<ffi.Void>, ffi.Pointer<ffi.Void>, ffi.Pointer<ffi.Void>);
typedef Dart_NewWeakPersistentHandle_Type = ffi.Pointer<ffi.Void> Function(
    ffi.Handle,
    ffi.Pointer<ffi.Void>,
    ffi.IntPtr,
    ffi.Pointer<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>);
typedef Dart_NewWeakPersistentHandle_DartType = ffi.Pointer<ffi.Void> Function(
    Object,
    ffi.Pointer<ffi.Void>,
    int,
    ffi.Pointer<ffi.NativeFunction<Dart_WeakPersistentHandleFinalizer_Type>>);

class _DartEntry extends ffi.Struct {
  ffi.Pointer<ffi.Int8>? name;
  ffi.Pointer<ffi.Void>? function;
}

class _DartApi extends ffi.Struct {
  @ffi.Int32()
  int? major;
  @ffi.Int32()
  int? minor;
  ffi.Pointer<_DartEntry>? functions;
}

final newWeakPersistentHandle = () {
  final ffi.Pointer<_DartApi> dlapi = ffi.NativeApi.initializeApiDLData.cast();
  for (int i = 0;
      dlapi.ref.functions?.elementAt(i).ref.name != ffi.nullptr;
      i++) {
    final name = dlapi.ref.functions?.elementAt(i).ref.name?.cast<Utf8>();

    if (name?.toDartString() == 'Dart_NewWeakPersistentHandle') {
      var func = dlapi.ref.functions?.elementAt(i).ref.function;
      if (func != null)
        return func
            .cast<ffi.NativeFunction<Dart_NewWeakPersistentHandle_Type>>()
            .asFunction<Dart_NewWeakPersistentHandle_DartType>();
    }
  }
}();
