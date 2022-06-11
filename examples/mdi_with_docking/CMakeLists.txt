#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

cmake_minimum_required(VERSION 3.7)
project(qtwidgets_mdi_with_docking)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIRS ON)

if(NOT TARGET kddockwidgets)
  # This will look for Qt, do find_package yourself manually before
  # if you want to look for a specific Qt version for instance.
  find_package(KDDockWidgets REQUIRED)
endif()

set(RESOURCES_EXAMPLE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/../dockwidgets/resources_example.qrc)

add_executable(qtwidgets_mdi_with_docking
    main.cpp
    ../dockwidgets/MyWidget.cpp
    ${RESOURCES_EXAMPLE_SRC}
)

set_target_properties(qtwidgets_mdi_with_docking PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/" )

target_link_libraries(qtwidgets_mdi_with_docking
  PRIVATE
    KDAB::kddockwidgets
)

