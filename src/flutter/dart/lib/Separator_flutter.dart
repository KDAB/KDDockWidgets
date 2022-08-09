/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/material.dart';

import 'View_flutter.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

class Separator_flutter extends View_flutter {
  Separator_flutter(KDDockWidgetBindings.Separator? separator,
      {required KDDockWidgetBindings.View? parent})
      : super(separator, KDDockWidgetBindings.KDDockWidgets_Type.Separator,
            parent) {
    m_color = Colors.blueGrey;
    debugName = "Separator";
    print("Separator_flutter CTOR");
    if (parent != null) {
      var v = KDDockWidgetBindings.View_flutter.fromCache(parent.thisCpp);
      v.onChildAdded(this);
    }
  }
}
