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

find_package(Qt${Qt_VERSION_MAJOR}Test ${QT_MIN_VERSION} REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(TESTING_SRCS utils.cpp)

include_directories(..)
include_directories(../src)
include_directories(../src/private)
add_definitions(-DQT_NO_KEYWORDS)

set(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)

# tst_qtwidgets
if(KDDW_FRONTEND_QTWIDGETS)
    add_executable(tst_qtwidgets qtwidgets/tst_qtwidgets.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_qtwidgets kdbindings kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
    set_compiler_flags(tst_qtwidgets)
    add_test(NAME tst_qtwidgets COMMAND tst_qtwidgets)
endif()

if(KDDW_FRONTEND_QTQUICK)
    add_executable(tst_qtquick qtquick/tst_qtquick.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_qtquick kddockwidgets kdbindings Qt${Qt_VERSION_MAJOR}::Test)
    set_compiler_flags(tst_qtquick)
    add_test(NAME tst_qtquick COMMAND tst_qtquick)
endif()

#-----------------------------------------------------------------------------
# Flutter embedder
if(KDDW_FRONTEND_FLUTTER)

    if(NOT DEFINED ENV{FLUTTER_ENGINE_FOLDER})
        message(FATAL_ERROR "Point env var FLUTTER_ENGINE_FOLDER to engine folder")
    endif()

    add_library(flutter_tests_embedder STATIC flutter_tests_embedder/tests_embedder.cpp)
    find_package(glfw3 REQUIRED)
    find_program(FLUTTER_EXE flutter REQUIRED)
    message(STATUS "Flutter SDK: ${FLUTTER_EXE}")
    get_filename_component(FLUTTER_SDK_PATH ${FLUTTER_EXE} PATH)
    file(GLOB_RECURSE ICUDTL "${FLUTTER_SDK_PATH}/icudtl.dat")
    message(STATUS "flutter icudtl.dat file: ${ICUDTL}")
    if(ICUDTL)
        add_custom_command(
            TARGET flutter_tests_embedder
            PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${ICUDTL} ${CMAKE_BINARY_DIR}
            COMMENT "Copying icudtl.dat to ${CMAKE_BINARY_DIR}"
        )
    else()
        message(FATAL_ERROR "icudtl.dat not found!")
    endif()

    # Build our dart code for the tests embedder
    add_custom_command(
        TARGET flutter_tests_embedder
        PRE_BUILD
        COMMAND ${FLUTTER_EXE} build bundle --suppress-analytics
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/tests/flutter_tests_embedder/"
        COMMENT "Running flutter build bundle flutter_tests_embedder"
    )

    target_link_libraries(
        flutter_tests_embedder PRIVATE kddockwidgets Qt${Qt_VERSION_MAJOR}::Core glfw
                                       $ENV{FLUTTER_ENGINE_FOLDER}/libflutter_engine.so
    )
    include_directories($ENV{FLUTTER_ENGINE_FOLDER})

    target_compile_definitions(
        flutter_tests_embedder PRIVATE FLUTTER_ICUDTL_DIR="${CMAKE_BINARY_DIR}"
                                       FLUTTER_TEST_MAIN="${CMAKE_SOURCE_DIR}/tests/flutter_tests_embedder/"
    )
endif()
#-----------------------------------------------------------------------------
# Add our tests:

# Function to add a test
function(add_kddw_test test srcs)
    add_executable(${test} ${srcs} ${TESTING_RESOURCES} utils.cpp)
    target_link_libraries(${test} kddockwidgets kdbindings)
    set_compiler_flags(${test})

    if(KDDW_FRONTEND_FLUTTER)
        target_link_libraries(${test} flutter_tests_embedder)
        add_test(NAME ${test} COMMAND ${test})
        set_tests_properties(${test} PROPERTIES ENVIRONMENT "ASAN_OPTIONS=detect_leaks=0")
    else()
        add_test(NAME ${test} COMMAND ${test})
    endif()
endfunction()

add_kddw_test(tst_docks tst_docks.cpp)

add_kddw_test(tst_docks_slow1 tst_docks_slow1.cpp)
add_kddw_test(tst_docks_slow2 tst_docks_slow2.cpp)
add_kddw_test(tst_docks_slow3 tst_docks_slow3.cpp)
add_kddw_test(tst_docks_slow4 tst_docks_slow4.cpp)
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

# These build with flutter but don't pass. So just build them but don't add
# them to the ctest set yet:
add_kddw_test(tst_docks_slow5 tst_docks_slow5.cpp)
add_kddw_test(tst_docks_slow6 tst_docks_slow6.cpp)

# This one doesn't even build yet
if(NOT KDDW_FRONTEND_FLUTTER)
    add_kddw_test(tst_docks_slow8 tst_docks_slow8.cpp)
endif()

#-----------------------------------------------------------------------------
