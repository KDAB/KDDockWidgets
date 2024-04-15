/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// A script to anonymize KDDW layouts
/// Renames dock widget names to generic names
/// To be used for KDDW's development only.

import 'dart:convert';
import 'dart:io';

List<String> dockNames(String filename) {
  final contents = File(filename).readAsStringSync();
  final json = jsonDecode(contents);
  List<String> names = [];
  for (var dw in json["allDockWidgets"]) names.add(dw["uniqueName"]);
  return names;
}

main(List<String> args) {
  if (args.length != 1) {
    print("Expected layout filename");
    return;
  }

  /// Sort them so we process longer names first
  var dockWidgetNames = dockNames(args.first);
  dockWidgetNames.sort((a, b) {
    if (a == b) return 0;
    if (a.length == b.length) return a.compareTo(b);
    if (a.length > b.length) return -1;
    return 1;
  });

  var contents = File(args.first).readAsStringSync();

  int i = 0;
  for (var name in dockWidgetNames) {
    if (name.startsWith("dockwidget_tests_")) {
      print("This file is already anonymized ? Has $name. Aborting.");
      return;
    }

    /// Skip internals
    if (["-persistentCentralDockWidget", "_kddw_internal_dummy", "_kddw_internal_dummy2"].contains(name))
      continue;

    contents = contents.replaceAll(name, "dockwidget_tests_$i");
    i++;
  }

  print(contents);
}
