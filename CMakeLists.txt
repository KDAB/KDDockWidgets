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

# Pass the following variables to cmake to control the build:
#
# -DKDDockWidgets_STATIC=[true|false]
#  Build static versions of the libraries
#  Default=false
#
# -DKDDockWidgets_TESTS=[true|false]
#  Build the test harness.
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
# -DOPTION_DEVELOPER_MODE=[true|false]
#  Configure the build for a developer setup.
#  Enables some features that are not geared towards end-users.
#  Forces the test harness to be built.
#  Default=false
#
# -DOPTION_BUILD_PYTHON_BINDINGS=[true|false]
#  Build/Generate python bindings.  Always false for Debug builds
#  Default=false
#
# -DPYTHON_BINDINGS_INSTALL_PREFIX=[path]
#  alternative install path for python bindings
#  Default=CMAKE_INSTALL_PREFIX

cmake_minimum_required(VERSION 3.7)
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0042)
  cmake_policy(SET CMP0042 NEW)
endif()

if("${CMAKE_INSTALL_PREFIX}" STREQUAL "")
  set(USE_DEFAULT_INSTALL_LOCATION True)
else()
  set(USE_DEFAULT_INSTALL_LOCATION False)
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
set(${PROJECT_NAME}_VERSION_MINOR 1)
set(${PROJECT_NAME}_VERSION_PATCH 95)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_VERSION_MAJOR}.${${PROJECT_NAME}_VERSION_MINOR}.${${PROJECT_NAME}_VERSION_PATCH})
set(${PROJECT_NAME}_SOVERSION "1.2")

include(FeatureSummary)

option(OPTION_DEVELOPER_MODE "Developer Mode" OFF)
option(OPTION_BUILD_PYTHON_BINDINGS "Build python bindings" OFF)
if(OPTION_BUILD_PYTHON_BINDINGS AND (CMAKE_BUILD_TYPE MATCHES "^[Dd]eb" OR ${PROJECT_NAME}_STATIC))
  message(FATAL_ERROR "** Python Bindings are disabled in debug or static builds.")
endif()
option(${PROJECT_NAME}_TESTS "Build the tests" OFF)
option(${PROJECT_NAME}_EXAMPLES "Build the examples" ON)
option(${PROJECT_NAME}_DOCS "Build the API documentation" OFF)

#Always build the test harness in developer-mode
if(OPTION_DEVELOPER_MODE)
  set(${PROJECT_NAME}_TESTS ON)
endif()

# option(OPTION_QTQUICK "Build for QtQuick instead of QtWidgets" OFF)

find_package(Qt5Widgets 5.9 REQUIRED)

set(CMAKE_AUTOMOC ON)

set(ECM_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ECM/modules/")
set(PYTHON_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/Python")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" ${ECM_MODULE_DIR} ${PYTHON_MODULE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# setup default install locations
include(InstallLocation)
include(QtInstallPaths) #to set QT_INSTALL_FOO variables

macro(set_compiler_flags targetName)
  if(OPTION_DEVELOPER_MODE)
    target_compile_definitions(${targetName} PRIVATE DOCKS_DEVELOPER_MODE QT_FORCE_ASSERTS)
    if(NOT MSVC)
      target_compile_options(${targetName} PRIVATE -Wall -Wextra -Werror -Wno-error=deprecated-declarations)
    endif()
  endif()
endmacro()

if(OPTION_QTQUICK)
  find_package(Qt5Quick)
  find_package(Qt5QuickControls2)
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
if(OPTION_BUILD_PYTHON_BINDINGS)
  add_subdirectory(python)
endif()

if(${PROJECT_NAME}_EXAMPLES)
  if (OPTION_QTQUICK)
    add_subdirectory(examples/qtquick)
    set_compiler_flags(kddockwidgets_example_quick)
  else()
      add_subdirectory(examples/dockwidgets)
      add_subdirectory(examples/minimal)
      set_compiler_flags(kddockwidgets_example)
      set_compiler_flags(kddockwidgets_minimal_example)
  endif()
endif()

if(OPTION_DEVELOPER_MODE)
  include(ECMEnableSanitizers)
  if(${PROJECT_NAME}_TESTS)
    enable_testing()
    add_subdirectory(tests)

    if (NOT OPTION_QTQUICK)
        #Require Qt5.15.1 or higher to run the tests_launcher tests on Mac
        if(NOT APPLE OR Qt5Widgets_VERSION VERSION_GREATER 5.15.0)
        # tst_docks.exe is pretty big (140 tests), so split it in 6 runs so we can use threads.
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
    endif()

    add_test(NAME tst_multisplitter COMMAND tst_multisplitter)
    add_test(NAME tst_common COMMAND tst_common)

  endif()
endif()

if(${PROJECT_NAME}_DOCS)
  add_subdirectory(docs) # needs to go last, in case there are build source files
endif()
