#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# Tests:
# 1. tst_docks      - The KDDockWidge tests. Compatible with QtWidgets and QtQuick.
# 2. tests_launcher - helper executable to paralelize the execution of tests

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(TESTING_SRCS utils.cpp)

include_directories(..)
include_directories(../src)
include_directories(../src/private)
add_definitions(-DQT_NO_KEYWORDS)

option(KDDockWidgets_FUZZER "Builds the fuzzer" ON)

# tst_docks
set(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
target_link_libraries(tst_docks kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
set_compiler_flags(tst_docks)

# tst_qtwidgets
add_executable(tst_qtwidgets qtwidgets/tst_qtwidgets.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
target_link_libraries(tst_qtwidgets kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
set_compiler_flags(tst_qtwidgets)

if(NOT ${PROJECT_NAME}_QTQUICK)
  add_executable(tst_multisplitter tst_multisplitter.cpp)
  target_link_libraries(tst_multisplitter kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
  set_compiler_flags(tst_multisplitter)
  if(KDDockWidgets_FUZZER)
    add_subdirectory(fuzzer)
  endif()
endif()

# tests_launcher
add_executable(tests_launcher tests_launcher.cpp)
target_link_libraries(tests_launcher Qt${Qt_VERSION_MAJOR}::Core)

add_executable(tst_viewguard tst_viewguard.cpp)
target_link_libraries(tst_viewguard kddockwidgets)

add_executable(tst_view tst_view.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_view kddockwidgets)

add_executable(tst_viewwrapper tst_viewwrapper.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_viewwrapper kddockwidgets)

add_executable(tst_frame controllers/tst_frame.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_frame kddockwidgets)

add_executable(tst_titlebar controllers/tst_titlebar.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_titlebar kddockwidgets)

add_executable(tst_stack controllers/tst_stack.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_stack kddockwidgets)

add_executable(tst_tabbar controllers/tst_tabbar.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_tabbar kddockwidgets)

add_executable(tst_separator controllers/tst_separator.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_separator kddockwidgets)

add_executable(tst_floatingwindow controllers/tst_floatingwindow.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_floatingwindow kddockwidgets)

add_executable(tst_dockwidget controllers/tst_dockwidget.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_dockwidget kddockwidgets)
