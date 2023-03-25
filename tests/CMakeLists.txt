#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(TESTING_SRCS utils.cpp Testing.cpp)

include_directories(..)
include_directories(../src)
include_directories(../src/private)
add_definitions(-DQT_NO_KEYWORDS)

set(TESTING_SRCS utils.cpp Testing.cpp)

# tst_docks
set(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
add_executable(
    tst_docks
    ${TESTING_RESOURCES} ${TESTING_SRCS} tst_docks.cpp
)
target_link_libraries(
    tst_docks kddockwidgets Qt${Qt_VERSION_MAJOR}::Test
)
set_compiler_flags(tst_docks)

if(NOT ${PROJECT_NAME}_QTQUICK)
    add_executable(tst_multisplitter tst_multisplitter.cpp)
    target_link_libraries(tst_multisplitter kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
    set_compiler_flags(tst_multisplitter)
endif()
