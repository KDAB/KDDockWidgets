###############################################################################
##  This file is part of KDDockWidgets.
##
##  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
##  Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
##
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 2 of the License, or
##  (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.
################################################################################

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
