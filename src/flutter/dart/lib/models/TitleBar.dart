/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

part of kddockwidgets;

class TitleBar {
  String title = "";
  bool isExplicitlyHidden = false;
  final Group? _group;

  TitleBar(Group? group, {this.title = ""}) : _group = group {}

  void onCloseClicked() {
    if (_group != null) {
      _group.close();
    }
  }

  void onFloatClicked() {}

  void onMouseEvent(PointerEvent ev) {}
}
