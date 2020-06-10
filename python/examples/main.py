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


from PySide2 import QtWidgets, QtCore 
from PyKDDockWidgets import KDDockWidgets
from MyMainWindow import MyMainWindow

import sys
import rc_assets

if __name__ == "__main__":
    QtWidgets.QApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    QtWidgets.QApplication.setAttribute(QtCore.Qt.AA_UseHighDpiPixmaps)
    app = QtWidgets.QApplication(sys.argv)

    app.setOrganizationName("KDAB")
    app.setApplicationName("Test app")
    app.setStyle(QtWidgets.QStyleFactory.create("Fusion"))

    mainWindow = MyMainWindow("MyMainWindow", )
    mainWindow.setWindowTitle("Main Window 1")
    mainWindow.resize(1200, 1200)
    mainWindow.show()

    app.exec_()

