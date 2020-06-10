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

class MyWidget(QtWidgets.QWidget):
    s_images = {}
    def __init__(self, backgroundFile, logoFile, parent = None):
        super().__init__(parent)

        self.m_background = self._lookupImage(backgroundFile)
        self.m_logo = self._lookupImage(logoFile)

    def _lookupImage(self, imageName):
        if imageName == "":
            return None

        if imageName not in MyWidget.s_images:
            MyWidget.s_images[imageName] = QtGui.QImage(imageName)

        return MyWidget.s_images[imageName]
        
    def drawLogo(self, p):

        if not self.m_logo:
            return

        ratio = self.m_logo.height() / (self.m_logo.width() * 1.0)
        maxWidth = int(0.80 * self.size().width())
        maxHeight = int(0.80 * self.size().height())
        proposedHeight = int(maxWidth * ratio)
        if (proposedHeight <= maxHeight):
            width = maxWidth
        else:
            width = int(maxHeight / ratio)

        height = int(width * ratio)
        targetLogoRect = QtCore.QRect(0,0, width, height)
        targetLogoRect.moveCenter(self.rect().center() + QtCore.QPoint(0, -int(self.size().height() * 0.00)))
        p.drawImage(targetLogoRect, self.m_logo, self.m_logo.rect());

