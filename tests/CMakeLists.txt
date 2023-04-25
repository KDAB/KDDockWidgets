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

#function to add slow tests along with a corresponding test number
function(add_slow_test testNumber)
    add_executable(tst_docks_slow${testNumber} tst_docks_slow${testNumber}.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
    target_link_libraries(tst_docks_slow${testNumber} kdbindings kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
    set_compiler_flags(tst_docks_slow${testNumber})
    add_test(NAME tst_docks_slow${testNumber} COMMAND tst_docks_slow${testNumber})
endfunction(add_slow_test)

# tst_docks
add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
target_link_libraries(tst_docks kdbindings kddockwidgets Qt${Qt_VERSION_MAJOR}::Test)
set_compiler_flags(tst_docks)

add_slow_test(1)
add_slow_test(2)
add_slow_test(3)
add_slow_test(4)
add_slow_test(5)
add_slow_test(6)
add_slow_test(7)

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

add_executable(tst_multisplitter tst_multisplitter.cpp)
target_link_libraries(tst_multisplitter kddockwidgets kdbindings Qt${Qt_VERSION_MAJOR}::Test)
set_compiler_flags(tst_multisplitter)

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
        COMMAND ${FLUTTER_EXE} build bundle
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
# Add our doctests:

# Function to add a doctest
function(add_doctest test srcs)
    add_executable(${test} ${srcs} ${TESTING_RESOURCES})
    target_link_libraries(${test} kddockwidgets kdbindings)
    if(KDDW_FRONTEND_FLUTTER)
        target_link_libraries(${test} flutter_tests_embedder)
    endif()
endfunction()

add_doctest(tst_viewguard tst_viewguard.cpp)
add_doctest(tst_view tst_view.cpp)
add_doctest(tst_window tst_window.cpp)
add_doctest(tst_droparea core/tst_droparea.cpp)
add_doctest(tst_platform tst_platform.cpp)
add_doctest(tst_group core/tst_group.cpp)
add_doctest(tst_titlebar core/tst_titlebar.cpp)
add_doctest(tst_stack core/tst_stack.cpp)
add_doctest(tst_tabbar core/tst_tabbar.cpp)
add_doctest(tst_separator core/tst_separator.cpp)
add_doctest(tst_floatingwindow core/tst_floatingwindow.cpp)
add_doctest(tst_dockwidget core/tst_dockwidget.cpp)
#-----------------------------------------------------------------------------
