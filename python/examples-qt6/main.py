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

''' KDDockWidgets example (Qt6) '''

import sys

from PySide6 import QtWidgets, QtCore
from MyMainWindow import MyMainWindow

try:
    # pylint: disable=unused-import
    import rc_assets
except ImportError:
    sys.exit(
        '''
Oops.. rc_assets needs to be generated first.
Please run:
 rcc -g python -o rc_assets.py ../../examples/dockwidgets/resources_example.qrc
 (Make sure to use the rcc from the Qt6 version used to generate the bindings!)
 On some systems rcc might be invoked as rcc-qt6.
'''
    )

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

    app.exec()
