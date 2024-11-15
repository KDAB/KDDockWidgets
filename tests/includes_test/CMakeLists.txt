# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

cmake_minimum_required(VERSION 3.15)
project(includes_test)

if(NOT TARGET kddockwidgets)
    find_package(KDDockWidgets QUIET)
    if(NOT KDDockWidgets_FOUND)
        find_package(KDDockWidgets-qt6 REQUIRED)
    endif()
endif()

add_executable(includes_test main.cpp)
target_link_libraries(includes_test PRIVATE KDAB::kddockwidgets)
