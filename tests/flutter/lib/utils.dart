/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2024 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'dart:io';
import 'dart:ui';

import 'package:flutter/material.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter_test/flutter_test.dart';

Map<String, int> _s_count = {};

String _screenshotDirectory() {
  return '${Directory(Platform.script.toFilePath()).parent.path}/../reference-images/images/flutter';
}

Future<void> saveScreenShot(WidgetTester tester,
    {required String prefix}) async {
  final renderObject = tester.firstRenderObject(find.byType(RepaintBoundary));
  final image =
      await (renderObject as RenderRepaintBoundary).toImage(pixelRatio: 2);

  final byteDataFuture = image.toByteData(format: ImageByteFormat.png);
  final byteData = await byteDataFuture;
  final buffer = byteData!.buffer.asUint8List();

  _s_count[prefix] = (_s_count[prefix] ?? 0) + 1;

  final file =
      File('${_screenshotDirectory()}/${prefix}_${_s_count[prefix]}.png');
  file.writeAsBytesSync(buffer);
}
