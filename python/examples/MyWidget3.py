################################################################################
##  This file is part of KDDockWidgets.
##
##  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

class MyWidget3(MyWidget):

    def __init__(self, parent = None):
        super().__init__(":/assets/base.png", ":/assets/KDAB_bubble_fulcolor.png", parent)
        self.m_triangle = QtGui.QImage(":/assets/tri.png")

    def paintEvent(self, ev):
        p = QtGui.QPainter(self)
        p.fillRect(self.rect(), QtGui.QColor(0xD5, 0xD5, 0xD5))
        p.drawImage(self.m_background.rect(), self.m_background, self.m_background.rect())
        
        targetRect = QtCore.QRect(QtCore.QPoint(self.width() - self.m_triangle.width(), self.height() - self.m_triangle.height()), self.m_triangle.size())

        self.drawLogo(p)

