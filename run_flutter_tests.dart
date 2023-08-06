/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// A script that runs the tests but first ensures the bundle is built

import 'dart:io';
import 'src/flutter/utils.dart';

String kddwSourceDir() {
  return Platform.script.path.replaceAll("run_flutter_tests.dart", "");
}

Future<int> runTests(String buildDir) async {
  if (!await Directory(buildDir).exists()) {
    print("ERROR: Could not find $buildDir");
    return -1;
  }

  /// Make sure the C++ is built:
  int result = await runCommand("ninja", [], workingDirectory: buildDir);
  if (result != 0) {
    print("Failed to build C++");
    return result;
  }

  /// Make sure the flutter bundle is built:
  final flutterEmbedderDir = "${kddwSourceDir()}/tests/flutter_tests_embedder/";
  result = await runCommand("flutter", ["build", "bundle"],
      workingDirectory: flutterEmbedderDir);

  if (result != 0) {
    print("Failed to build bundle");
    return result;
  }

  /// Now we can run the tests:
  return await runCommand("ctest", ["-j5"], workingDirectory: buildDir);
}

void printUsage() {
  print("Usage: dart run_flutter_tests.dart <build-dir>");
}

String calculateBuildDir(List<String> args) {
  if (args.isEmpty) {
    print("No build dir specified, defaulting to build-dev-flutter/");
    return "${kddwSourceDir()}build-dev-flutter/";
  }

  return args.first;
}

Future<void> main(List<String> args) async {
  var _args = List.from(args);
  if (_args.length > 1) {
    printUsage();
    exit(0);
  }

  exit(await runTests(calculateBuildDir(args)));
}
