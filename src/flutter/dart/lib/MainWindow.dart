/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/material.dart';
import 'package:KDDockWidgets/View_mixin.dart';
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsCore.dart'
    as KDDWBindingsCore;
import 'package:KDDockWidgetsBindings/Bindings_KDDWBindingsFlutter.dart'
    as KDDWBindingsFlutter;

class MainWindow extends KDDWBindingsFlutter.MainWindow with View_mixin {
  late final KDDWBindingsCore.MainWindow m_controller;

  MainWindow(String? uniqueName,
      {int options = 0,
      required KDDWBindingsFlutter.View? parent,
      int flags = 0})
      : super(uniqueName, options: options, parent: parent, flags: flags) {
    initMixin(this, color: Colors.black12, debugName: "MainWindow");

    m_controller = controller() as KDDWBindingsCore.MainWindow;
  }
}
