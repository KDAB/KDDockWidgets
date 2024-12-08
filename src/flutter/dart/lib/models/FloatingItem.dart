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

  @override
  void close() {
    if (!DockRegistry.instance.containsFloatingItem(this)) {
      // we're closed already, can be removed once we can _groupCountChangedConnection.disconnect()
      return;
    }

    // _groupCountChangedConnection.disconnect(); signals_slot bug
    DockRegistry.instance.removeFloatingItem(this);
  }
}
