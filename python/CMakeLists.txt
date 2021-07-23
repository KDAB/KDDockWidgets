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
set(PYTHON_BINDING_NAMESPACE "PyKDDockWidgets")

if(${PROJECT_NAME}_QT6)
  set(PYSIDE_MAJOR_VERSION "6")
  set(QtWidgets_VERSION ${Qt6Widgets_VERSION})
else()
  set(PYSIDE_MAJOR_VERSION "2")
  set(QtWidgets_VERSION ${Qt5Widgets_VERSION})
endif()

find_package(Python3 3.7 REQUIRED COMPONENTS Interpreter Development)
find_package(Shiboken${PYSIDE_MAJOR_VERSION} REQUIRED)
find_package(PySide${PYSIDE_MAJOR_VERSION} ${QtWidgets_VERSION} EXACT REQUIRED)

if(NOT ${PROJECT_NAME}_PYTHON_BINDINGS_INSTALL_PREFIX)
  set(${PROJECT_NAME}_PYTHON_BINDINGS_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif()
set(BINDINGS_DIR "${INSTALL_LIBRARY_DIR}/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages/${PYTHON_BINDING_NAMESPACE}")
set(${PROJECT_NAME}_PYTHON_BINDINGS_INSTALL_PREFIX "${${PROJECT_NAME}_PYTHON_BINDINGS_INSTALL_PREFIX}/${BINDINGS_DIR}")

include(PySide${PYSIDE_MAJOR_VERSION}ModuleBuild)
add_subdirectory(PyKDDockWidgets)
