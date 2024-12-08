/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

part of kddockwidgets;

final Map<int, WeakReference<Group>> _instances = {};
final Map<DockItem, Connection> _titleChangedConnections = {};

// C++ might call the callback before _instances has the group
Group? groupInCtor;

void _geometryChangedCallback(ffi.Pointer<ffi.Void> guest, int x, int y,
    int width, int height, int isVisible) {
  try {
    final group =
        groupInCtor == null ? _instances[guest.address]!.target! : groupInCtor!;

    group.geometry = Rect.fromLTWH(
        x.toDouble(), y.toDouble(), width.toDouble(), height.toDouble());
    group.isVisible = isVisible != 0;

    group.changed.emit();
  } catch (e) {
    print('Error in _geometryChangedCallback: $e');
    print('Instances size=${_instances.length}');
    print('Guest address=${guest.address}');
  }
}

class Group extends GeometryItem implements ffi.Finalizable, ItemWithTitleBar {
  static final _finalizer =
      ffi.NativeFinalizer(finalizerFunc("delete_guest").cast());

  int _currentIndex = -1;
  List<DockItem> items = [];
  late final TitleBar titlebar;

  final ffi.Pointer<void> _hostCpp;
  late final ffi.Pointer<void> guestCpp;

  final titleChanged = Signal0();
  DropArea dropArea;

  Group(this.dropArea, {super.geometry}) : _hostCpp = dropArea.hostPtr {
    titlebar = TitleBar(this);

    final callbackPointer = ffi.Pointer.fromFunction<
        ffi.Void Function(ffi.Pointer<ffi.Void>, ffi.Int, ffi.Int, ffi.Int,
            ffi.Int, ffi.Int)>(_geometryChangedCallback);

    groupInCtor = this;
    guestCpp = Bindings.instance.nativeLibrary
        .create_guest(this._hostCpp.cast(), callbackPointer);
    groupInCtor = null;

    _instances[guestCpp.address] = WeakReference<Group>(this);
    _instances.removeWhere((_, weakRef) => weakRef.target == null);
    _finalizer.attach(this, guestCpp.cast());
  }

  void addDockWidget(DockItem item) {
    items.add(item);

    _titleChangedConnections[item] = item.titleChanged.connect((_) {
      if (isCurrentDockItem(item)) {
        _updateTitle();
      }
    });

    if (_currentIndex == -1) {
      currentIndex = 0;
    }

    changed.emit();
  }

  int numDockWidgets() {
    return items.length;
  }

  DockItem dockWidgetAt(int index) {
    return items[index];
  }

  int get currentIndex {
    return _currentIndex;
  }

  set currentIndex(int index) {
    if (index != _currentIndex) {
      _currentIndex = index;
      _updateTitle();
    }
  }

  DockItem? get currentDockItem {
    if (_currentIndex < 0 || _currentIndex >= items.length) {
      return null;
    }
    return items[_currentIndex];
  }

  bool isCurrentDockItem(DockItem dock) {
    return _currentIndex != -1 && indexOfDockItem(dock) == _currentIndex;
  }

  bool showsTabs() {
    return numDockWidgets() > 1;
  }

  bool showsTitleBar() {
    return !titlebar.isExplicitlyHidden;
  }

  bool containsDockItem(String name) {
    return items.any((item) => item.uniqueName == name);
  }

  int indexOfDockItem(DockItem dock) {
    return items.indexOf(dock);
  }

  bool removeDockItem(DockItem dock) {
    final int index = indexOfDockItem(dock);
    if (index < 0) return false;

    items.removeAt(index);

    _titleChangedConnections[dock]!.disconnect();
    _titleChangedConnections.remove(dock);

    if (_currentIndex == index) {
      if (items.isEmpty) {
        currentIndex = -1;
      } else if (index >= items.length) {
        currentIndex = items.length - 1;
      }
    }

    changed.emit();
    return true;
  }

  bool get isEmpty {
    return items.isEmpty;
  }

  void _updateTitle() {
    if (currentDockItem != null) {
      titlebar.title = currentDockItem!.title;
      titleChanged.emit();
    }
  }

  @override
  void close() {
    dropArea._removeGroup(this);
  }
}
