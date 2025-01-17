/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

part of kddockwidgets;

// Floating windows and tab groups have titlebars
abstract class ItemWithTitleBar {
  // called when close button on the titlebar is clicked
  void close();

  // whether the titlebar is attached to a floating window or group
  bool isFloating();

  // detaches into a floating window
  void float();

  // docks a floating window into the main drop area
  void unfloat();
}

class TitleBar {
  String title = "";
  bool isExplicitlyHidden = false;
  final ItemWithTitleBar _itemWithTitleBar;

  TitleBar(ItemWithTitleBar itemWithTitleBar, {this.title = ""})
      : _itemWithTitleBar = itemWithTitleBar {}

  void onCloseClicked() {
    _itemWithTitleBar.close();
  }

  void onFloatClicked() {
    if (isFloating()) {
      _itemWithTitleBar.unfloat();
    } else {
      _itemWithTitleBar.float();
    }
  }

  void onMouseEvent(PointerEvent ev) {}

  bool isFloating() {
    return _itemWithTitleBar.isFloating();
  }
}
