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

bool isAOT = false;
bool isASAN = false;
bool isLSAN = false;

String kddwSourceDir() {
  return Platform.script.path.replaceAll("run_flutter_tests.dart", "");
}

Future<int> runTests(String buildDir) async {
  if (!await Directory(buildDir).exists()) {
    final presetName = buildDir
        .replaceAll(kddwSourceDir(), "")
        .replaceAll("build-", "")
        .replaceAll("/", "");
    print("ERROR: Could not find $buildDir.\n"
        "Be sure to build the preset: $presetName");
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
  result = await runCommand(
      "flutter", ["build", "bundle", "--suppress-analytics"],
      workingDirectory: flutterEmbedderDir);

  if (result != 0) {
    print("Failed to build bundle");
    return result;
  }

  if (isAOT) {
    result = await runCommand(
        "flutter", ["build", "linux", "--release", "--suppress-analytics"],
        workingDirectory: flutterEmbedderDir);

    if (result != 0) {
      print("Failed to build AOT snapshot (libapp.so)");
      return result;
    }
  }

  final String aotValue = isAOT ? "1" : "0";
  final String lsanValue = isLSAN ? "1" : "0";
  final String asanOptions = "detect_leaks=$lsanValue";
  print("export KDDW_FLUTTER_TESTS_USE_AOT=$aotValue");
  print("export ASAN_OPTIONS=$asanOptions");

  /// Now we can run the tests:
  return await runCommand("ctest", ["-j5"],
      workingDirectory: buildDir,
      env: {
        "KDDW_FLUTTER_TESTS_USE_AOT": aotValue,
        "ASAN_OPTIONS": asanOptions
      });
}

void printUsage() {
  print(
      "Usage: dart run_flutter_tests.dart [--aot] [--asan] [--lsan] <build-dir>");
}

String calculateBuildDir() {
  String result;

  if (isAOT) {
    result = "build-dev-flutter-aot";
  } else {
    result = "build-dev-flutter";
  }

  if (isASAN) result += "-asan";

  print("Using $result");
  return "${kddwSourceDir()}${result}/";
}

Future<void> main(List<String> args) async {
  final _args = List<String>.from(args);

  isAOT = _args.remove("--aot");
  isLSAN = _args.remove("--lsan");
  isASAN = isLSAN || _args.remove("--asan");

  if (_args.length > 1 || _args.contains("--help") || _args.contains("-h")) {
    printUsage();
    exit(0);
  }

  exit(await runTests(calculateBuildDir()));
}
