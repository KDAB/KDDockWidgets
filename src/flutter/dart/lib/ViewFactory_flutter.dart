/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:KDDockWidgetsBindings/src/ViewFactory_flutter.dart'
    as KDDockWidgetBindings;

class ViewFactory_flutter extends KDDockWidgetBindings.ViewFactory_flutter {
ViewFactory_flutter() {
  print("Dart: Created ViewFactory_flutter");
}
}
