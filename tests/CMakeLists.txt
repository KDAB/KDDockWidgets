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

if(POLICY CMP0043)
    cmake_policy(SET CMP0043 NEW)
endif()

find_package(Qt${Qt_VERSION_MAJOR}Test ${QT_MIN_VERSION} REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(TESTING_SRCS utils.cpp)

include_directories(..)
include_directories(../src)
include_directories(../src/private)
add_definitions(-DQT_NO_KEYWORDS)

# Will enable it once needed option(KDDockWidgets_FUZZER "Builds the fuzzer" ON)

# tst_docks
set(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
target_link_libraries(tst_docks kdbindings kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
set_compiler_flags(tst_docks)

# tst_qtwidgets
if(KDDW_FRONTEND_QTWIDGETS)
    add_executable(tst_qtwidgets qtwidgets/tst_qtwidgets.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_qtwidgets kdbindings kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
    set_compiler_flags(tst_qtwidgets)
endif()

if(KDDW_FRONTEND_QTQUICK)
    add_executable(tst_qtquick qtquick/tst_qtquick.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_qtquick kddockwidgets kdbindings Qt${Qt_VERSION_MAJOR}::Test)
    set_compiler_flags(tst_qtquick)
endif()

if(KDDW_FRONTEND_DUMMY)
    add_executable(tst_dummyplatform tst_dummyplatform.cpp ${TESTING_RESOURCES})
    target_link_libraries(tst_dummyplatform kddockwidgets kdbindings)
    set_compiler_flags(tst_dummyplatform)
endif()

add_executable(tst_multisplitter tst_multisplitter.cpp)
target_link_libraries(tst_multisplitter kddockwidgets kdbindings Qt${Qt_VERSION_MAJOR}::Test)
set_compiler_flags(tst_multisplitter)

# tests_launcher
add_executable(tests_launcher tests_launcher.cpp)
target_link_libraries(tests_launcher Qt${Qt_VERSION_MAJOR}::Core)

add_executable(tst_viewguard tst_viewguard.cpp)
target_link_libraries(tst_viewguard kddockwidgets kdbindings)

add_executable(tst_view tst_view.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_view kddockwidgets kdbindings)

add_executable(tst_window tst_window.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_window kddockwidgets kdbindings)

add_executable(tst_droparea tst_droparea.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_droparea kddockwidgets kdbindings)

add_executable(tst_platform tst_platform.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_platform kddockwidgets kdbindings)

add_executable(tst_group controllers/tst_group.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_group kddockwidgets kdbindings)

add_executable(tst_titlebar controllers/tst_titlebar.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_titlebar kddockwidgets kdbindings)

add_executable(tst_stack controllers/tst_stack.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_stack kddockwidgets kdbindings)

add_executable(tst_tabbar controllers/tst_tabbar.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_tabbar kddockwidgets kdbindings)

add_executable(tst_separator controllers/tst_separator.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_separator kddockwidgets kdbindings)

add_executable(tst_floatingwindow controllers/tst_floatingwindow.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_floatingwindow kddockwidgets kdbindings)

add_executable(tst_dockwidget controllers/tst_dockwidget.cpp ${TESTING_RESOURCES})
target_link_libraries(tst_dockwidget kddockwidgets kdbindings)
