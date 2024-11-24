# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

cmake_minimum_required(VERSION 3.15)
project(qtquick_customplayground)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIRS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT TARGET kddockwidgets)
    # For the purpose of our example, we're looking for Qt5 or Qt6 KDDW.
    # For your own purposes, just chose the one you need.
    find_package(KDDockWidgets QUIET)
    if(NOT KDDockWidgets_FOUND)
        find_package(KDDockWidgets-qt6 REQUIRED)
    endif()
endif()

set(RESOURCES_EXAMPLE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/resources_qtquick_example.qrc
                          ${CMAKE_CURRENT_SOURCE_DIR}/../../dockwidgets/resources_example.qrc
)

add_executable(qtquick_customplayground main.cpp ${RESOURCES_EXAMPLE_SRC})

target_link_libraries(qtquick_customplayground PRIVATE KDAB::kddockwidgets)
