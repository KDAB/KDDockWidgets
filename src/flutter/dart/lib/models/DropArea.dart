/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

part of kddockwidgets;

enum Location {
  LocationNone,
  LocationOnLeft,
  LocationOnTop,
  LocationOnRight,
  LocationOnBottom
}

final Map<int, WeakReference<DropArea>> _dropAreaInstances = {};

// Called from C++
void _separatorAddedCallback(ffi.Pointer<ffi.Void> host,
    ffi.Pointer<ffi.Void> separator, int isVertical) {
  try {
    DropArea dropArea = _dropAreaInstances[host.address]!.target!;
    dropArea._on_separator_added_in_cpp(
        separator,
        isVertical == 1
            ? SeparatorOrientation.vertical
            : SeparatorOrientation.horizontal);
  } catch (e) {
    print('Error in _separatorAddedCallback: $e');
  }
}

// Called from C++
void _separatorRemovedCallback(
    ffi.Pointer<ffi.Void> host, ffi.Pointer<ffi.Void> separator) {
  try {
    DropArea dropArea = _dropAreaInstances[host.address]!.target!;
    dropArea._on_separator_removed_in_cpp(separator);
  } catch (e) {
    print('Error in _separatorAddedCallback: $e');
  }
}

class DropArea implements ffi.Finalizable {
  static final _finalizer =
      ffi.NativeFinalizer(finalizerFunc("delete_host").cast());

  /// Emitted when separators or groups are added or removed
  final layoutChanged = Signal0();
  final GlobalKey key = GlobalKey();

  List<Group> _groups = [];
  List<Separator> _separators = [];
  late final ffi.Pointer<void> _hostCpp;

  DropArea() {
    _hostCpp = Bindings.instance.nativeLibrary.create_host();
    _finalizer.attach(this, _hostCpp.cast());
    final separatorAddedCallbackPointer = ffi.Pointer.fromFunction<
        ffi.Void Function(ffi.Pointer<ffi.Void>, ffi.Pointer<ffi.Void>,
            ffi.Int)>(_separatorAddedCallback);

    Bindings.instance.nativeLibrary.set_separator_added_callback(
        _hostCpp.cast(), separatorAddedCallbackPointer);

    final separatorRemovedCallbackPointer = ffi.Pointer.fromFunction<
        ffi.Void Function(ffi.Pointer<ffi.Void>,
            ffi.Pointer<ffi.Void>)>(_separatorRemovedCallback);

    Bindings.instance.nativeLibrary.set_separator_removed_callback(
        _hostCpp.cast(), separatorRemovedCallbackPointer);

    _dropAreaInstances[_hostCpp.address] = WeakReference<DropArea>(this);

    // cleanup since we don't have dtors
    _dropAreaInstances.removeWhere((_, weakRef) => weakRef.target == null);
  }

  void _addGroup(Group group) {
    _groups.add(group);
    layoutChanged.emit();
  }

  void _removeGroup(Group group) {
    _groups.remove(group);
    Bindings.instance.nativeLibrary
        .remove_guest(_hostCpp.cast(), group.guestCpp.cast());
    layoutChanged.emit();
  }

  bool containsDockItem(String name) {
    return _groups.any((group) => group.containsDockItem(name));
  }

  bool hasGroups() {
    return _groups.isNotEmpty;
  }

  void setLayoutSize(int width, int height) {
    Bindings.instance.nativeLibrary
        .on_flutter_droparea_widget_resized(_hostCpp.cast(), width, height);
  }

  void addDockItem(DockItem dock, Location location) {
    if (containsDockItem(dock.uniqueName)) {
      // NOLINTNEXTLINE(avoid_print)
      print(
          'WARN: Failed to add dock widget. A dock widget with name ${dock.uniqueName} already exists.');
      return;
    }

    var group = Group(this);
    group.addDockWidget(dock);
    _addGroup(group);

    Bindings.instance.nativeLibrary
        .insert_item(_hostCpp.cast(), group.guestCpp.cast(), location.index);
  }

  Group? groupForDockItem(DockItem dock) {
    for (var group in groups) {
      if (group.containsDockItem(dock.uniqueName)) return group;
    }

    return null;
  }

  bool removeDockItem(DockItem dock) {
    var group = groupForDockItem(dock);
    if (group == null) return false;

    if (group.removeDockItem(dock)) {
      if (group.isEmpty) {
        _removeGroup(group);
      }
      return true;
    }

    return false;
  }

  List<Group> get groups {
    return _groups;
  }

  List<Separator> get separators {
    return _separators;
  }

  void _on_separator_added_in_cpp(
      ffi.Pointer<ffi.Void> separator, SeparatorOrientation orientation) {
    var sep = Separator(separator, orientation: orientation);
    _separators.add(sep);
    layoutChanged.emit();
  }

  void _on_separator_removed_in_cpp(ffi.Pointer<ffi.Void> separator) {
    if (!_separators
        .any((sep) => sep.separatorCpp.address == separator.address)) {
      // This doesn't happen
      throw StateError('Separator not found');
    }

    _separators
        .removeWhere((sep) => sep.separatorCpp.address == separator.address);
    layoutChanged.emit();
  }

  ffi.Pointer<void> get hostPtr {
    return _hostCpp;
  }
}
