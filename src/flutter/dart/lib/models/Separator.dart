/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ui';

import 'package:KDDockWidgets/models/GeometryItem.dart';

import 'dart:ffi' as ffi;

import 'package:KDDockWidgets/private/Bindings.dart';

enum SeparatorOrientation {
  horizontal,
  vertical, // separates stuff vertically (changes heights)
}

final Map<int, WeakReference<Separator>> _instances = {};

void _geometryChangedCallback(
    ffi.Pointer<ffi.Void> separatorCpp, int x, int y, int width, int height) {
  try {
    final separator = _instances[separatorCpp.address]!.target!;

    separator.geometry = Rect.fromLTWH(
        x.toDouble(), y.toDouble(), width.toDouble(), height.toDouble());

    separator.changed.emit();
  } catch (e) {
    print('Error in _geometryChangedCallback: $e');
  }
}

class Separator extends GeometryItem {
  final SeparatorOrientation orientation;
  ffi.Pointer<ffi.Void> _separatorCpp;

  Separator(
    this._separatorCpp, {
    required this.orientation,
  }) : super(geometry: Rect.zero) {
    final callbackPointer = ffi.Pointer.fromFunction<
        ffi.Void Function(ffi.Pointer<ffi.Void>, ffi.Int, ffi.Int, ffi.Int,
            ffi.Int)>(_geometryChangedCallback);
    Bindings.instance.nativeLibrary
        .set_separator_changed_callback(_separatorCpp, callbackPointer);

    _instances[_separatorCpp.address] = WeakReference<Separator>(this);

    // cleanup since we don't have dtors
    _instances.removeWhere((_, weakRef) => weakRef.target == null);
  }

  int get pos {
    if (isVertical)
      return geometry.top.toInt();
    else
      return geometry.left.toInt();
  }

  void set setPos(int value) {
    if (isVertical) {
      geometry = Rect.fromLTWH(
          value.toDouble(), geometry.top, geometry.width, geometry.height);
    } else {
      geometry = Rect.fromLTWH(
          geometry.left, value.toDouble(), geometry.width, geometry.height);
    }
  }

  bool get isVertical {
    return orientation == SeparatorOrientation.vertical;
  }

  ffi.Pointer<ffi.Void> get separatorCpp => _separatorCpp;

  void onMousePress() {
    Bindings.instance.nativeLibrary
        .on_separator_mouse_button_event(_separatorCpp, 1);
  }

  void onMouseReleased() {
    Bindings.instance.nativeLibrary
        .on_separator_mouse_button_event(_separatorCpp, 0);
  }

  void onMouseMove(Offset localPos) {
    Bindings.instance.nativeLibrary
        .on_separator_mouse_move_event(_separatorCpp, localPos.dx, localPos.dy);
  }
}
