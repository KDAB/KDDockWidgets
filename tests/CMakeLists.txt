#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# Tests:
# 1. tst_common     - tests which are common between QtWidgets and QtQuick frontends
# 2. tst_docks      - the old tests, mostly specific to QWidget, unless ported. Ideally we should move code from here into tst_common
# 3. tests_launcher - helper executable to paralelize the execution of tests

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
find_package(Qt5Test)

set(TESTING_SRCS utils.cpp Testing.cpp)

include_directories(..)
include_directories(../src)
include_directories(../src/private)

find_package(Qt5Test)
set(TESTING_SRCS utils.cpp Testing.cpp)

# tst_common
qt5_add_resources(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
add_executable(tst_common tst_common.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
target_link_libraries(tst_common kddockwidgets kddockwidgets_multisplitter Qt5::Test)
set_compiler_flags(tst_common)

# tst_docks
if (NOT ${PROJECT_NAME}_QTQUICK)
    add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_docks kddockwidgets kddockwidgets_multisplitter Qt5::Widgets Qt5::Test)
    set_compiler_flags(tst_docks)
    add_subdirectory(fuzzer)
endif()

# tests_launcher
add_executable(tests_launcher tests_launcher.cpp)
target_link_libraries(tests_launcher Qt5::Core)
