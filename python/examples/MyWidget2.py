################################################################################
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

from PySide2 import QtWidgets, QtGui, QtCore

from MyWidget import MyWidget

class MyWidget2(MyWidget):

    def __init__(self, parent = None):
        super().__init__("", ":/assets/KDAB_bubble_blue.png", parent)

    def paintEvent(self, ev):
        p = QtGui.QPainter(self)
        p.fillRect(self.rect(), QtCore.Qt.white);
        self.drawLogo(p)

