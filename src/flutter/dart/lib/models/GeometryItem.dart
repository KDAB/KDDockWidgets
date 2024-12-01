/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:ui';

import 'package:signals_slots/signals_slots.dart';

/// Inherited by stuff which KDDW controls geometry of
/// basically tab groups and separators
class GeometryItem {
  Rect geometry;
  bool isVisible = true;

  final changed = Signal0();

  GeometryItem({this.geometry = Rect.zero});
}
