/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'View_flutter.dart';
import 'package:KDDockWidgetsBindings/Bindings.dart' as KDDockWidgetBindings;

class DockWidget_flutter extends KDDockWidgetBindings.DockWidget_flutter {
  DockWidget_flutter(String? uniqueName,
      {int options = 0, int layoutSaverOptions = 0})
      : super(uniqueName,
            options: options, layoutSaverOptions: layoutSaverOptions) {
    print("DockWidget_flutter CTOR");
  }
}
