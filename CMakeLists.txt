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

# Pass the following variables to cmake to control the build:
#
# -DKDDockWidgets_QT6=[true|false]
#  Build against Qt6 rather than Qt5
#  Default=false (Qt5 will be used even if Qt6 is available)
#
# -DKDDockWidgets_STATIC=[true|false]
#  Build static versions of the libraries
#  Default=false
#
# -DKDDockWidgets_TESTS=[true|false]
#  Build the test harness.
#  Currently does nothing unless you also set KDDockWidgets_DEVELOPER_MODE=True
#  Default=false
#
# -DKDDockWidgets_EXAMPLES=[true|false]
#  Build the examples.
#  Default=true
#
# -DKDDockWidgets_DOCS=[true|false]
#  Build the API documentation.
#  Default=false
#
# -DKDDockWidgets_DEVELOPER_MODE=[true|false]
#  Configure the build for a developer setup.
#  Enables some features that are not geared towards end-users.
#  Forces the test harness to be built.
#  Default=false
#
# -DKDDockWidgets_QTQUICK == IN DEVELOPMENT. DO NOT USE! ==
#  Build for QtQuick instead of QtWidgets
#  Default=false
#
# -DKDDockWidgets_PYTHON_BINDINGS=[true|false]
#  Build/Generate python bindings.  Always false for Debug builds
#  Default=false
#
# -DKDDockWidgets_PYTHON_BINDINGS_INSTALL_PREFIX=[path]
#  Set an alternative install path for Python bindings
#  Default=CMAKE_INSTALL_PREFIX
#
# -DKDDockWidgets_UNITY_BUILD=[true|false]
#  Build with CMake's UNITY_BUILD (requires CMake version 3.16 or higher)
#  Default=true
#

cmake_minimum_required(VERSION 3.7)
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

set(KDAB_INSTALL True)
if((NOT DEFINED ${USE_DEFAULT_INSTALL_LOCATION}) OR (NOT ${USE_DEFAULT_INSTALL_LOCATION}))
  if(NOT "${CMAKE_INSTALL_PREFIX}" STREQUAL "")
    set(KDAB_INSTALL False)
  endif()
  set(USE_DEFAULT_INSTALL_LOCATION ${KDAB_INSTALL} CACHE INTERNAL "Install to default KDAB Location" FORCE)
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
  project(KDDockWidgets LANGUAGES CXX)
else()
  project(KDDockWidgets
          DESCRIPTION "An advanced docking system for Qt"
          HOMEPAGE_URL "https://github.com/KDAB/KDDockWidgets"
          LANGUAGES CXX)
endif()

set(${PROJECT_NAME}_VERSION_MAJOR 1)
set(${PROJECT_NAME}_VERSION_MINOR 2)
set(${PROJECT_NAME}_VERSION_PATCH 1)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
set(${PROJECT_NAME}_SOVERSION "1.3")

include(FeatureSummary)

option(${PROJECT_NAME}_QT6 "Build against Qt 6" OFF)
option(${PROJECT_NAME}_DEVELOPER_MODE "Developer Mode" OFF)
option(${PROJECT_NAME}_PYTHON_BINDINGS "Build python bindings" OFF)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.16.0")
  option(${PROJECT_NAME}_UNITY_BUILD "Build with CMake's UNITY_BUILD" ON)
endif()


if(${PROJECT_NAME}_PYTHON_BINDINGS AND (CMAKE_BUILD_TYPE MATCHES "^[Dd]eb" OR ${PROJECT_NAME}_STATIC))
  message(FATAL_ERROR "** Python Bindings are disabled in debug or static builds.")
endif()

option(${PROJECT_NAME}_TESTS "Build the tests" OFF)
option(${PROJECT_NAME}_EXAMPLES "Build the examples" ON)
option(${PROJECT_NAME}_DOCS "Build the API documentation" OFF)
option(${PROJECT_NAME}_WERROR "Use -Werror (will be true for developer-mode unconditionally)" OFF)

#Always build the test harness in developer-mode
if(${PROJECT_NAME}_DEVELOPER_MODE)
  set(${PROJECT_NAME}_TESTS ON)
  set(${PROJECT_NAME}_WERROR ON)
endif()

#option(${PROJECT_NAME}_QTQUICK "Build for QtQuick instead of QtWidgets" OFF)

if (${PROJECT_NAME}_QT6)
  find_package(Qt6Widgets REQUIRED)
  find_package(Qt6Test REQUIRED)
  set(QT_MAJOR_VERSION 6)
else()
  find_package(Qt5Widgets 5.9 REQUIRED)
  find_package(Qt5Test 5.9 REQUIRED)
  set(QT_MAJOR_VERSION 5)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(ECM_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ECM/modules/")
set(PYTHON_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/Python")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" ${ECM_MODULE_DIR} ${PYTHON_MODULE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# setup default install locations
include(InstallLocation)
include(QtInstallPaths) #to set QT_INSTALL_FOO variables

macro(set_compiler_flags targetName)
  if(${PROJECT_NAME}_DEVELOPER_MODE)
    target_compile_definitions(${targetName} PUBLIC DOCKS_DEVELOPER_MODE PRIVATE QT_FORCE_ASSERTS)

    if(NOT MSVC)
      target_compile_options(${targetName} PRIVATE -Wall -Wextra)
    endif()

    if(APPLE)
      target_compile_options(${targetName} PRIVATE -Wweak-vtables)
    endif()
  endif()

  # Enable -Werror
  if(NOT MSVC AND ${PROJECT_NAME}_WERROR)
    target_compile_options(${targetName} PRIVATE -Werror -Wno-error=deprecated-declarations)
  endif()

endmacro()

if(${PROJECT_NAME}_QTQUICK)
  find_package(Qt${QT_MAJOR_VERSION}Quick)
  find_package(Qt${QT_MAJOR_VERSION}QuickControls2)
  add_definitions(-DKDDOCKWIDGETS_QTQUICK)
else()
  add_definitions(-DKDDOCKWIDGETS_QTWIDGETS)
endif()

if(${PROJECT_NAME}_STATIC)
  set(${PROJECT_NAME}_LIBRARY_MODE "STATIC")
else()
  set(${PROJECT_NAME}_LIBRARY_MODE "SHARED")
endif()

if(USE_DEFAULT_INSTALL_LOCATION)
  if(UNIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local/KDAB/${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}")
  elseif(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:\\KDAB\\${PROJECT_NAME}-${${PROJECT_NAME}_VERSION}")
  endif()
endif()

# Generate .pri file for qmake users
include(ECMGeneratePriFile)
set(PROJECT_VERSION_STRING ${${PROJECT_NAME}_VERSION})
ecm_generate_pri_file(BASE_NAME KDDockWidgets
  LIB_NAME kddockwidgets
  FILENAME_VAR pri_filename
)
install(FILES ${pri_filename} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

install(FILES LICENSE.txt README.md DESTINATION ${INSTALL_DOC_DIR})
install(DIRECTORY LICENSES DESTINATION ${INSTALL_DOC_DIR})

add_subdirectory(src)
if(${PROJECT_NAME}_PYTHON_BINDINGS)
  add_subdirectory(python)
endif()

if(${PROJECT_NAME}_EXAMPLES)
  if (${PROJECT_NAME}_QTQUICK)
    add_subdirectory(examples/qtquick)
  else()
      add_subdirectory(examples/dockwidgets)
      add_subdirectory(examples/minimal)
      set_compiler_flags(kddockwidgets_example)
      set_compiler_flags(kddockwidgets_minimal_example)
  endif()
endif()

if(${PROJECT_NAME}_DEVELOPER_MODE)
  include(ECMEnableSanitizers)
  if(${PROJECT_NAME}_TESTS)
    enable_testing()
    add_subdirectory(tests)

    # Require Qt5.15.1 or higher to run the tests_launcher tests on Mac
    if (NOT APPLE OR Qt5Widgets_VERSION VERSION_GREATER 5.15.0)
        # tst_docks.exe is pretty big (160 tests), so split it in more runs so we can use threads.
        add_test(NAME tst_docks0 COMMAND tests_launcher 0 5)
        add_test(NAME tst_docks1 COMMAND tests_launcher 1 5)
        add_test(NAME tst_docks2 COMMAND tests_launcher 2 5)
        add_test(NAME tst_docks3 COMMAND tests_launcher 3 5)
        add_test(NAME tst_docks4 COMMAND tests_launcher 4 5)
        add_test(NAME tst_docks5 COMMAND tests_launcher 5 5)
        add_test(NAME tst_docks6 COMMAND tests_launcher 6 5)
        add_test(NAME tst_docks7 COMMAND tests_launcher 7 5)
        add_test(NAME tst_docks8 COMMAND tests_launcher 8 5)
        add_test(NAME tst_docks9 COMMAND tests_launcher 9 5)
        add_test(NAME tst_docks10 COMMAND tests_launcher 10 5)
        add_test(NAME tst_docks11 COMMAND tests_launcher 10 5)
        add_test(NAME tst_docks12 COMMAND tests_launcher 11 5)
        add_test(NAME tst_docks13 COMMAND tests_launcher 12 5)
        add_test(NAME tst_docks14 COMMAND tests_launcher 13 5)
        add_test(NAME tst_docks15 COMMAND tests_launcher 14 5)
        add_test(NAME tst_docks16 COMMAND tests_launcher 15 5)
        add_test(NAME tst_docks17 COMMAND tests_launcher 16 5)
        add_test(NAME tst_docks18 COMMAND tests_launcher 17 5)
        add_test(NAME tst_docks19 COMMAND tests_launcher 18 5)
        add_test(NAME tst_docks20 COMMAND tests_launcher 19 5)
        add_test(NAME tst_docks21 COMMAND tests_launcher 20 5) # one more for rounding leftovers
    endif()
    if (NOT ${PROJECT_NAME}_QTQUICK)
        # tst_multisplitter depends on QWidget
        add_test(NAME tst_multisplitter COMMAND tst_multisplitter)
    endif()

  endif()
endif()

if(${PROJECT_NAME}_DOCS)
  add_subdirectory(docs) # needs to go last, in case there are build source files
endif()

if (${PROJECT_NAME}_UNITY_BUILD)
  set_target_properties(kddockwidgets PROPERTIES UNITY_BUILD ON)
endif()
