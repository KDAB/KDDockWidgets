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

from PySide6 import QtGui
from MyWidget import MyWidget


# pylint: disable=too-few-public-methods
class MyWidget1(MyWidget):
    def __init__(self, parent=None):
        super().__init__(":/assets/triangles.png", ":/assets/KDAB_bubble_white.png", parent)

    def paintEvent(self, event):
        del event  # unused at this time
        p = QtGui.QPainter(self)
        p.fillRect(self.rect(), QtGui.QColor(0xCC, 0xCC, 0xCC))
        p.drawImage(self.background.rect(),
                    self.background, self.background.rect())
        self.drawLogo(p)
