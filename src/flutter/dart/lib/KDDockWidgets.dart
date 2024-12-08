/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

library kddockwidgets;

import 'package:KDDockWidgets/models/GeometryItem.dart';
import 'package:KDDockWidgets/models/Separator.dart';
import 'package:KDDockWidgets/private/Bindings.dart';
import 'package:flutter/material.dart';

import 'dart:ffi' as ffi;

import 'package:signals_slots/signals_slots.dart';

part 'models/Group.dart';
part 'models/DropArea.dart';
part 'models/TitleBar.dart';
part 'models/FloatingItem.dart';
part 'models/DockRegistry.dart';
part 'models/DockItem.dart';

class DropLocation {
  static const int DropLocation_None = 0;
  static const int DropLocation_Left = 1;
  static const int DropLocation_Top = 2;
  static const int DropLocation_Right = 4;
  static const int DropLocation_Bottom = 8;
  static const int DropLocation_Center = 16;
  static const int DropLocation_OutterLeft = 32;
  static const int DropLocation_OutterTop = 64;
  static const int DropLocation_OutterRight = 128;
  static const int DropLocation_OutterBottom = 256;
  static const int DropLocation_Inner = DropLocation_Left |
      DropLocation_Right |
      DropLocation_Top |
      DropLocation_Bottom;
  static const int DropLocation_Outter = DropLocation_OutterLeft |
      DropLocation_OutterRight |
      DropLocation_OutterTop |
      DropLocation_OutterBottom;
  static const int DropLocation_Horizontal = DropLocation_Left |
      DropLocation_Right |
      DropLocation_OutterLeft |
      DropLocation_OutterRight;
  static const int DropLocation_Vertical = DropLocation_Top |
      DropLocation_Bottom |
      DropLocation_OutterTop |
      DropLocation_OutterBottom;
}
