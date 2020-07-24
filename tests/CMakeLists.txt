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
qt5_add_resources(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
add_executable(tests_launcher tests_launcher.cpp)
target_link_libraries(tst_docks kddockwidgets kddockwidgets_multisplitter Qt5::Widgets Qt5::Test)
target_link_libraries(tests_launcher Qt5::Core)

set_compiler_flags(tst_docks)

add_subdirectory(fuzzer)

