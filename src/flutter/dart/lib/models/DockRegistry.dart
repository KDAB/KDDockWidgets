/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

part of kddockwidgets;

class DockRegistry {
  static final DockRegistry _instance = DockRegistry._internal();

  final floatingItems = <FloatingItem>[];
  final dockItems = <DockItem>[];
  late final Widget rootMainWidget;

  void addFloatingItem(FloatingItem floatingItem) {
    if (floatingItems.contains(floatingItem)) {
      throw Exception("FloatingItem already exists in registry");
    }

    if (floatingItemForDropArea(floatingItem.dropArea) != null) {
      throw Exception("Already have a floating item for this drop area");
    }

    floatingItems.add(floatingItem);
    recreateViews();
  }

  void removeFloatingItem(FloatingItem floatingItem) {
    if (!floatingItems.contains(floatingItem)) {
      throw Exception("FloatingItem doesn't exists in registry");
    }

    floatingItems.remove(floatingItem);
    recreateViews();
  }

  void addDockItem(DockItem dockItem) {
    if (dockItems.contains(dockItem)) {
      throw Exception("DockItem already exists in registry");
    }

    dockItems.add(dockItem);
  }

  void removeDockItem(DockItem dockItem) {
    if (!dockItems.contains(dockItem)) {
      throw Exception("DockItem doesn't exists in registry");
    }

    dockItems.remove(dockItem);
  }

  FloatingItem? floatingItemForDropArea(DropArea da) {
    for (FloatingItem floatingItem in floatingItems) {
      if (floatingItem.dropArea == da) {
        return floatingItem;
      }
    }

    return null;
  }

  bool containsFloatingItem(FloatingItem floatingItem) {
    return floatingItems.contains(floatingItem);
  }

  void recreateViews() {
    final floatingViews = floatingItems.map((fi) {
      return View(
          view: PlatformDispatcher.instance.views
              .where((v) =>
                  v.viewId == 1) // TODO: Support more than 1 floating window
              .first,
          child: MaterialApp(
              title: 'Floating Window',
              theme: ThemeData(
                colorScheme: ColorScheme.fromSeed(seedColor: Colors.deepPurple),
                useMaterial3: true,
              ),
              home: Scaffold(
                  body: Container(
                color: Colors.orange,
                child: FloatingWidget(fi),
              ))));
    });

    runWidget(ViewCollection(views: [
      View(
        view: PlatformDispatcher.instance.implicitView!,
        child: rootMainWidget,
      ),
      ...floatingViews
    ]));
  }

  factory DockRegistry() {
    return _instance;
  }
  DockRegistry._internal();

  static DockRegistry get instance => _instance;
}
