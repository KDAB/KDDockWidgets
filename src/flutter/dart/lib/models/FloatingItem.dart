/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

part of kddockwidgets;

class FloatingItem implements ItemWithTitleBar {
  final dropArea = DropArea();
  late final TitleBar titleBar;
  late final Connection _groupCountChangedConnection;

  FloatingItem() {
    DockRegistry.instance.addFloatingItem(this);
    titleBar = TitleBar(this);

    _groupCountChangedConnection =
        dropArea.layoutChanged.connect(onGroupCountChanged);
  }

  void onGroupCountChanged() {
    if (!dropArea.hasGroups()) {
      close();
    }
  }

  bool showsTitleBar() {
    return dropArea.groups.length > 1;
  }

  bool containsGroup(Group group) {
    return dropArea.containsGroup(group);
  }

  void addGroup(Group group) {
    dropArea._addGroup(group);
  }

  @override
  void close() {
    _groupCountChangedConnection.disconnect();
    DockRegistry.instance.removeFloatingItem(this);
  }

  @override
  bool isFloating() {
    // A floating window is floating
    return true;
  }

  @override
  void unfloat() {
    // attach floating window into main window again
  }

  @override
  void float() {
    // a floating window is already floating
    throw "unreachable";
  }
}
