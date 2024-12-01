/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/widgets.dart';
import 'package:signals_slots/signals_slots.dart';

/// represents the state of a dock widget

class DockItem {
  Widget? guestWidget;
  final String uniqueName;
  String _title = "";

  final titleChanged = Signal1();

  DockItem({
    required this.uniqueName,
    this.guestWidget,
  });

  String get title {
    if (_title.isNotEmpty) return _title;

    return uniqueName;
  }

  set title(String title) {
    if (_title != title) {
      _title = title;
      titleChanged.emit(title);
    }
  }
}
