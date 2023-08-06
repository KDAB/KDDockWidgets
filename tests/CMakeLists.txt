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

if(KDDW_FRONTEND_QT)
    find_package(Qt${Qt_VERSION_MAJOR}Test ${QT_MIN_VERSION} REQUIRED)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include_directories(..)
include_directories(../src)
include_directories(../src/private)
add_definitions(-DQT_NO_KEYWORDS)

set(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
set(TESTING_SRCS utils.cpp)
if(KDDockWidgets_HAS_SPDLOG)
    set(TESTING_SRCS ${TESTING_SRCS} fatal_logger.cpp)
endif()

find_package(nlohmann_json QUIET)
# Function to link to nlohmann
function(kddw_add_nlohmann test)
    if(nlohmann_json_FOUND)
        target_link_libraries(${test} nlohmann_json::nlohmann_json)
    else()
        target_include_directories(${test} SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/src/3rdparty/nlohmann)
    endif()
endfunction()

# tst_qtwidgets
if(KDDW_FRONTEND_QTWIDGETS)
    add_executable(tst_qtwidgets qtwidgets/tst_qtwidgets.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_qtwidgets kdbindings kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
    if(KDDockWidgets_HAS_SPDLOG)
        target_link_libraries(tst_qtwidgets spdlog::spdlog)
    endif()
    kddw_add_nlohmann(tst_qtwidgets)
    set_compiler_flags(tst_qtwidgets)
    add_test(NAME tst_qtwidgets COMMAND tst_qtwidgets)
endif()

# tst_qtquick
if(KDDW_FRONTEND_QTQUICK)
    add_executable(tst_qtquick qtquick/tst_qtquick.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_qtquick kddockwidgets kdbindings Qt${Qt_VERSION_MAJOR}::Test)
    if(KDDockWidgets_HAS_SPDLOG)
        target_link_libraries(tst_qtquick spdlog::spdlog)
    endif()
    kddw_add_nlohmann(tst_qtquick)
    set_compiler_flags(tst_qtquick)
    add_test(NAME tst_qtquick COMMAND tst_qtquick)
endif()

#-----------------------------------------------------------------------------
# Add our tests:

# Function to add a test
function(add_kddw_test test srcs)
    add_executable(${test} ${srcs} ${TESTING_RESOURCES} ${TESTING_SRCS})
    target_link_libraries(${test} kddockwidgets kdbindings)
    target_include_directories(${test} PRIVATE ${CMAKE_BINARY_DIR})
    if(KDDockWidgets_HAS_SPDLOG)
        target_link_libraries(${test} spdlog::spdlog)
    endif()

    kddw_add_nlohmann(${test})
    set_compiler_flags(${test})

    if(KDDW_FRONTEND_FLUTTER)
        target_link_libraries(${test} kddockwidgets)
        add_test(NAME ${test} COMMAND ${test})
        target_compile_definitions(${test} PRIVATE KDDW_SRC_DIR="${CMAKE_SOURCE_DIR}")

        if(KDDockWidgets_FLUTTER_TESTS_AOT)
            set(KDDW_AOT_VALUE 1)
        else()
            set(KDDW_AOT_VALUE 0)
        endif()

        set_tests_properties(${test} PROPERTIES ENVIRONMENT "KDDW_FLUTTER_TESTS_USE_AOT=${KDDW_AOT_VALUE}")
    else()
        add_test(NAME ${test} COMMAND ${test})
    endif()
endfunction()

add_kddw_test(tst_docks tst_docks.cpp)

add_kddw_test(tst_docks_slow1 tst_docks_slow1.cpp)
add_kddw_test(tst_docks_slow2 tst_docks_slow2.cpp)
add_kddw_test(tst_docks_slow3 tst_docks_slow3.cpp)
add_kddw_test(tst_docks_slow4 tst_docks_slow4.cpp)
add_kddw_test(tst_docks_slow5 tst_docks_slow5.cpp)
add_kddw_test(tst_docks_slow6 tst_docks_slow6.cpp)
add_kddw_test(tst_docks_slow7 tst_docks_slow7.cpp)

add_kddw_test(tst_multisplitter tst_multisplitter.cpp)
add_kddw_test(tst_viewguard tst_viewguard.cpp)
add_kddw_test(tst_view tst_view.cpp)
add_kddw_test(tst_window tst_window.cpp)
add_kddw_test(tst_droparea core/tst_droparea.cpp)
add_kddw_test(tst_platform tst_platform.cpp)
add_kddw_test(tst_group core/tst_group.cpp)
add_kddw_test(tst_titlebar core/tst_titlebar.cpp)
add_kddw_test(tst_stack core/tst_stack.cpp)
add_kddw_test(tst_tabbar core/tst_tabbar.cpp)
add_kddw_test(tst_separator core/tst_separator.cpp)
add_kddw_test(tst_floatingwindow core/tst_floatingwindow.cpp)
add_kddw_test(tst_dockwidget core/tst_dockwidget.cpp)

# This one doesn't even build yet
if(NOT KDDW_FRONTEND_FLUTTER)
    add_kddw_test(tst_docks_slow8 tst_docks_slow8.cpp)

    # Check if includes are installed
    add_subdirectory(includes_test)
endif()

if(KDDockWidgets_WAYLAND_TESTS)
    add_subdirectory(wayland)
endif()

#-----------------------------------------------------------------------------
