/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
import 'dart:io';

import 'package:flutter/material.dart';

// ignore: must_be_immutable
class MyWidget extends StatelessWidget {
  static int nextImageId = 0;
  final int imageId;
  MyWidget({super.key}) : imageId = nextImageId {
    MyWidget.nextImageId++;
  }

  String imageName() {
    switch (imageId % 2) {
      case 0:
        return 'assets/KDAB_bubble_fulcolor.png';
      case 1:
        return 'assets/KDAB_bubble_blue.png';
    }

    return 'assets/KDAB_bubble_fulcolor.png';
  }

  @override
  Widget build(BuildContext context) {
    return Container(
      color: Colors.white,
      padding: const EdgeInsets.all(40.0),
      child: Image.file(
        File(imageName()),
        fit: BoxFit.contain,
      ),
    );
  }
}
