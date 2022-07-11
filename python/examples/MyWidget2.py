#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# pylint: disable=missing-module-docstring,missing-class-docstring,missing-function-docstring

from PySide2 import QtGui, QtCore
from MyWidget import MyWidget


# pylint: disable=too-few-public-methods
class MyWidget2(MyWidget):

    def __init__(self, parent=None):
        super().__init__("", ":/assets/KDAB_bubble_blue.png", parent)

    def paintEvent(self, event):
        del event  # unused at this time
        p = QtGui.QPainter(self)
        p.fillRect(self.rect(), QtCore.Qt.white)
        self.drawLogo(p)
