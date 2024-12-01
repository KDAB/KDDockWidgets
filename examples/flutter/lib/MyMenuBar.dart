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
          // final dw = DockRegistry.self().dockByName(name);
          // if (dw.isOpen()) {
          //   dw.close();
          // } else {
          //   dw.open();
          // }
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
                        onPressed: () {},
                        child: const MenuAcceleratorLabel('&New DockWidget'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          // final saver = LayoutSaver();
                          // saver.saveToFile("savedLayout.json");
                        },
                        child: const MenuAcceleratorLabel('&Save Layout'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          // final saver = LayoutSaver();
                          // saver.restoreFromFile("savedLayout.json");
                        },
                        child: const MenuAcceleratorLabel('&Restore Layout'),
                      ),
                      MenuItemButton(
                        onPressed: () {
                          // DockRegistry.self().clear();
                        },
                        child: const MenuAcceleratorLabel('&Close All'),
                      ),
                      MenuItemButton(
                        onPressed: () {},
                        child: const MenuAcceleratorLabel('&Layout Equally'),
                      ),
                      MenuItemButton(
                        onPressed: () {},
                        child: const MenuAcceleratorLabel('&Quit'),
                      ),
                    ],
                    child: const MenuAcceleratorLabel('&File'),
                  ),
                  SubmenuButton(
                    menuChildren: dockWidgetsToToggle(),
                    child: const MenuAcceleratorLabel('&Toggle'),
                  )
                ],
              ),
            ),
          ],
        ),
      ],
    );
  }
}
