/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2025 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

import 'package:signals_slots/signals_slots.dart';

mixin HasConnections {
  final List<Connection> connections = [];
  void connect(var signal, action) {
    connections.add(signal.connect(action));
  }

  void disconnect() {
    for (var con in connections) con.disconnect();
  }
}
