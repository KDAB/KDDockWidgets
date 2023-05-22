/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:flutter/material.dart';

class MyMenuBar extends StatelessWidget {
  const MyMenuBar({super.key});

  List<Widget> dockWidgetsToToggle() {
    List<Widget> widgets = [];
    for (int i = 1; i <= 6; ++i) {
      final String name = "dw$i";
      widgets.add(MenuItemButton(
        onPressed: () {
          print("Pressed $name");
        },
        child: Text(name),
      ));
    }

    return widgets;
  }

  @override
  Widget build(BuildContext context) {
    return Column(
      children: <Widget>[
        Row(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            Expanded(
              child: MenuBar(
                children: <Widget>[
                  SubmenuButton(
                    menuChildren: <Widget>[
                      MenuItemButton(
                        onPressed: () {
                          print("New DockWidget");
                        },
                        child: const MenuAcceleratorLabel('&New DockWidget'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          print("Save Layout pressed");
                        },
                        child: const MenuAcceleratorLabel('&Save Layout'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          print("Restore Layout");
                        },
                        child: const MenuAcceleratorLabel('&Restore Layout'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          print("Close All pressed");
                        },
                        child: const MenuAcceleratorLabel('&Close All'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          print("Layout Equally pressed");
                        },
                        child: const MenuAcceleratorLabel('&Layout Equally'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          print("Quit pressed");
                        },
                        child: const MenuAcceleratorLabel('&Quit'),
                      ),
                    ],
                    child: const MenuAcceleratorLabel('&File'),
                  ),
                  SubmenuButton(
                    menuChildren: dockWidgetsToToggle(),
                    child: const MenuAcceleratorLabel('&Toggle'),
                  ),
                ],
              ),
            ),
          ],
        ),
      ],
    );
  }
}
