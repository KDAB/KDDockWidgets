#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# pylint: disable=missing-module-docstring,missing-function-docstring,missing-class-docstring

# pylint: disable=no-name-in-module
from PySide6 import QtCore, QtWidgets, QtGui
from PyKDDockWidgetsQt6 import KDDockWidgets

from MyWidget1 import MyWidget1
from MyWidget2 import MyWidget2
from MyWidget3 import MyWidget3


def newMyWidget(parent=None):
    randomNumber = QtCore.QRandomGenerator.global_().bounded(0, 100) + 1
    if randomNumber < 50:
        if randomNumber < 33:
            return MyWidget1(parent)
        return MyWidget3(parent)
    return MyWidget2(parent)


class MyMainWindow(KDDockWidgets.MainWindow):
    s_count = 0
    s_menuCount = 0

    def __init__(self,
                 uniqueName,
                 options=KDDockWidgets.MainWindowOption_None,
                 dockWidget0IsNonClosable=False,
                 nonDockableDockWidget9=False,
                 restoreIsRelative=False,
                 maxSizeForDockWidget8=False,
                 affinityName="",
                 parent=None):
        super().__init__(uniqueName, options, parent)
        self.dockWidget0IsNonClosable = dockWidget0IsNonClosable
        self.dockWidget9IsNonDockable = nonDockableDockWidget9
        self.restoreIsRelative = restoreIsRelative
        self.maxSizeForDockWidget8 = maxSizeForDockWidget8
        self.dockwidgets = []

        menubar = self.menuBar()
        fileMenu = QtWidgets.QMenu("File")
        self.toggleMenu = QtWidgets.QMenu("Toggle")
        menubar.addMenu(fileMenu)
        menubar.addMenu(self.toggleMenu)

        newAction = fileMenu.addAction("New DockWidget")
        newAction.triggered.connect(self._newDockWidget)

        saveLayoutAction = fileMenu.addAction("Save Layout")
        saveLayoutAction.triggered.connect(self._saveLayout)

        restoreLayoutAction = fileMenu.addAction("Restore Layout")
        restoreLayoutAction.triggered.connect(self._restoreLayout)

        closeAllAction = fileMenu.addAction("Close All")
        closeAllAction.triggered.connect(self._closeAll)

        layoutEqually = fileMenu.addAction("Layout Equally")
        layoutEqually.triggered.connect(self.layoutEqually)

        quitAction = fileMenu.addAction("Quit")
        quitAction.triggered.connect(QtWidgets.QApplication.instance().quit)

        self.setAffinities([affinityName])
        self.createDockWidgets()

    def _newDockWidget(self):
        MyMainWindow.s_menuCount += 1
        w = newMyWidget(self)
        w.setGeometry(100, 100, 400, 400)
        dock = KDDockWidgets.DockWidget("new dock %d" % (MyMainWindow.s_menuCount))
        dock.setWidget(w)
        dock.resize(600, 600)
        dock.show()
        self.dockwidgets.append(dock)

    # pylint: disable=no-self-use
    def _saveLayout(self):
        # saver = KDDockWidgets.LayoutSaver()
        # result = saver.saveToFile("mylayout.json")
        # print("Saving layout to disk. Result=", result)
        print("Not available")

    # pylint: disable=no-self-use
    def _restoreLayout(self):
        # options = KDDockWidgets.RestoreOption_None
        # if self.restoreIsRelative:
        #    options |= KDDockWidgets.RestoreOption_RelativeToMainWindow
        # saver = KDDockWidgets.LayoutSaver(options)
        # saver.restoreFromFile("mylayout.json")
        print("Not available")

    def _closeAll(self):
        for widget in self.dockwidgets:
            widget.close()

    def createDockWidgets(self):
        if self.dockWidget9IsNonDockable:
            numDockWidgets = 10
        else:
            numDockWidgets = 9

        # numDockWidgets = 2
        # Create 9 KDDockWidget::DockWidget and the respective widgets they're hosting (MyWidget instances)
        for _ in range(numDockWidgets):
            self.dockwidgets.append(self.newDockWidget())

        # MainWindow::addDockWidget() attaches a dock widget to the main window:
        initialOpts = KDDockWidgets.InitialOption(KDDockWidgets.InitialVisibilityOption.StartHidden,
                                                  QtCore.QSize(500, 500))
        self.addDockWidget(self.dockwidgets[0], KDDockWidgets.Location_OnBottom, None, initialOpts)

        # Here, for finer granularity we specify right of dockwidgets[0]:
        self.addDockWidget(self.dockwidgets[1], KDDockWidgets.Location_OnRight, self.dockwidgets[0])

        self.addDockWidget(self.dockwidgets[2], KDDockWidgets.Location_OnLeft)
        self.addDockWidget(self.dockwidgets[3], KDDockWidgets.Location_OnBottom)
        self.addDockWidget(self.dockwidgets[4], KDDockWidgets.Location_OnBottom)

        # Tab two dock widgets together
        self.dockwidgets[3].addDockWidgetAsTab(self.dockwidgets[5])

        # 6 is floating, as it wasn't added to the main window via MainWindow::addDockWidget().
        # and we tab 7 with it.
        self.dockwidgets[6].addDockWidgetAsTab(self.dockwidgets[7])

        # Floating windows also support nesting, here we add 8 to the bottom of the group
        self.dockwidgets[6].addDockWidgetToContainingWindow(self.dockwidgets[8], KDDockWidgets.Location_OnBottom)

        floatingWindow = self.dockwidgets[6].window()
        floatingWindow.move(100, 100)

    def newDockWidget(self):
        # Passing options is optional, we just want to illustrate Option_NotClosable here
        options = KDDockWidgets.DockWidget.Option_None
        if (MyMainWindow.s_count == 0) and self.dockWidget0IsNonClosable:
            options |= KDDockWidgets.DockWidget.Option_NotClosable

        if (MyMainWindow.s_count == 9) and self.dockWidget9IsNonDockable:
            options |= KDDockWidgets.DockWidget.Option_NotDockable

        dock = KDDockWidgets.DockWidget("DockWidget #%d" % (MyMainWindow.s_count), options)
        # optional, just to show the feature. Pass -mi to the example to see incompatible dock widgets
        dock.setAffinities(self.affinities())

        if MyMainWindow.s_count == 1:
            dock.setIcon(QtGui.QIcon.fromTheme("mail-message"))

        myWidget = newMyWidget(self)
        if (MyMainWindow.s_count == 8) and self.maxSizeForDockWidget8:
            # Set a maximum size on dock #8
            myWidget.setMaximumSize(200, 200)

        dock.setWidget(myWidget)

        if dock.options() & KDDockWidgets.DockWidget.Option_NotDockable:
            dock.setTitle("DockWidget #%d (%s)" % (MyMainWindow.s_count, "non dockable"))
        else:
            dock.setTitle("DockWidget #%d" % (MyMainWindow.s_count))

        dock.resize(600, 600)
        self.toggleMenu.addAction(dock.toggleAction())
        MyMainWindow.s_count += 1
        return dock
