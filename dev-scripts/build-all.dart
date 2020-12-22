/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * This is an helper script which simply reads CMakePresets.json and builds those
 * presets. It's just for quickly checking that every supported setup builds
 * without having to wait for CI (or in case you don't have access to KDAB CI)
 * 
 * Usage:
 *     $ dart build-all.dart <kddw-source-directory> [--unity] [--tests]
 */

import 'dart:io';
import 'dart:convert';

String s_sourceDirectory = "";
bool s_testUnityVariations = false;
bool s_runTests = true;

class Preset {
  final String name;
  final String buildDir;
  String cmakeVariables = "";
  Preset.fromJson(var jsonData)
      : name = jsonData['name'],
        buildDir = jsonData['binaryDir'] {
    final varsData = jsonData['cacheVariables'];
    varsData.forEach((k, v) => cmakeVariables += ' -D' + k + '=' + v);
  }

  String buildDirectory() {
    return buildDir.replaceAll("\${sourceDir}", s_sourceDirectory);
  }

  List<String> cmakeConfigArguments(bool isUnityBuild) {
    return [
      "-G",
      "Ninja",
      cmakeVariables,
      "-B",
      buildDirectory(),
      "-S",
      s_sourceDirectory,
      "--preset=" + name,
      '-DKDDockWidgets_UNITY_BUILD=${isUnityBuild ? "ON" : "OFF"}'
    ];
  }

  List<String> cmakeBuildArguments() {
    return ["--build", buildDirectory()];
  }

  // Builds twice. One with unity build and one without.
  Future<bool> build() async {
    if (!await buildSingle(true)) return false;
    if (s_testUnityVariations) if (!await buildSingle(false)) return false;
    if (s_runTests && !await runTests()) {
      return false;
    }

    return true;
  }

  Future<bool> buildSingle(bool isUnityBuild) async {
    if (!await runCMake(cmakeConfigArguments(isUnityBuild))) {
      return false;
    }

    if (!await runCMake(cmakeBuildArguments())) {
      return false;
    }

    return true;
  }

  Future<bool> runTests() async {
    print("Running: ctest");

    final savedCwd = Directory.current;
    Directory.current = buildDirectory();
    ProcessResult result = await Process.run('ctest', ["-j8"]);
    Directory.current = savedCwd;

    if (result.exitCode != 0) {
      print(result.stdout);
      print(result.stderr);
      return false;
    }

    return true;
  }
}

/// Returns the contents of the CMakePresets.json file
String cmakePresetsJson(presetsFile) {
  var file = File(presetsFile);
  if (!file.existsSync()) {
    throw Exception('Not existent file');
  }
  return file.readAsStringSync();
}

List<Preset> readPresets(var presetsFile) {
  var presets = List<Preset>();

  final jsonData = jsonDecode(cmakePresetsJson(presetsFile));
  for (var presetData in jsonData['configurePresets']) {
    presets.add(Preset.fromJson(presetData));
  }
  return presets;
}

Future<bool> runCMake(var cmd) async {
  print("Running: cmake " + cmd.join(' '));
  ProcessResult result = await Process.run('cmake', cmd);
  if (result.exitCode != 0) {
    print(result.stdout);
    print(result.stderr);
    return false;
  }

  return true;
}

Future<int> main(List<String> arguments) async {
  if (arguments.length == 0) {
    print("Usage: build-all.dart <src-directory> [--unity]");
    return 1;
  }

  s_sourceDirectory = arguments[0];
  s_testUnityVariations = arguments.contains("--unity");
  s_runTests = arguments.contains("--tests");
  final presetsFile = s_sourceDirectory + '/CMakePresets.json';

  if (FileSystemEntity.typeSync(presetsFile) == FileSystemEntityType.notFound) {
    print('ERROR: CMakePresets.json file not found in the source directory');
    return 1;
  }

  var presets = readPresets(presetsFile);
  for (var preset in presets) {
    if (preset.name == 'python')
      continue; // TODO: blacklisted as it's not building on my setup yet

    if (!await preset.build()) {
      return 1;
    }
  }

  print("Success!!");
  return 0;
}
