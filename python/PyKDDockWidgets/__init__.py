#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

__all__ = ['KDDockWidgets']

# Preload PySide2 libraries to avoid missing libraries while loading KDDockWidgets
try:
    from PySide2 import QtCore
except Exception:
    print("Failed to load PySide")
    raise

# avoid duplicate namespace, due the PYSIDE-1325 bug I will have my package like this
# PyKDDockWidgets.KDDockWidgets.KDDockWidgets.MainWindow
# To avoid this I add a WORKAROUND to reduce it
from .KDDockWidgets import KDDockWidgets as _priv
KDDockWidgets = _priv
