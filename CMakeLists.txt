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
#  Currently ignored (except for Python bindings) unless KDDockWidgets_DEVELOPER_MODE=True.
#  Default=false
#
# -DKDDockWidgets_EXAMPLES=[true|false]
#  Build the examples.
#  Default=true
#
# -DKDDockWidgets_DOCS=[true|false]
#  Build the API documentation. Enables the 'docs' build target.
#  Default=false
#
# -DKDDockWidgets_PYTHON_BINDINGS=[true|false]
#  Build/Generate python bindings.  Always false for Debug builds
#  (If your shiboken or pyside is installed in a non-standard locations
#  try passing the SHIBOKEN_CUSTOM_PREFIX and PYSIDE_CUSTOM_PREFIX variables.)
#  Default=false
#
# -DKDDockWidgets_PYTHON_BINDINGS_INSTALL_PREFIX=[path]
#  Set an alternative install path for Python bindings
#  Default=CMAKE_INSTALL_PREFIX

# ## DO NOT USE IF YOU ARE AN END-USER.  FOR THE DEVELOPERS ONLY!!
## Special CMake Options for Developers
#
# -DKDDockWidgets_DEVELOPER_MODE=[true|false]
#  Configure the build for a developer setup.
#  Enables some features that are not geared towards end-users.
#  Forces the test harness to be built.
#  Default=false
#
# -DKDDockWidgets_WERROR=[true|false]
#  Compile with the -Werror gcc/clang option (always true for developer-mode)
#  Default=false
#
# -DKDDockWidgets_LINTER=[true|false]
#  Build the layout linter.
#  Ignored unless KDDockWidgets_DEVELOPER_MODE=True
#  Default=true
#
# -DKDDockWidgets_FUZZER=[true|false]
#  Build the fuzzer.
#  Ignored unless KDDockWidgets_DEVELOPER_MODE=True
#  Default=true
#
# -DKDDockWidgets_CODE_COVERAGE=[true|false]
#  Enable coverage reporting.
#  Ignored unless KDDockWidgets_DEVELOPER_MODE=True
#  Default=false
#
# -DKDDockWidgets_FRONTENDS='qtwidgets;qtquick'
# Semicolon separated list of frontends to enable. If not specified,
# frontends will be enabled based on availablity of libraries on
# your system.

cmake_minimum_required(VERSION 3.7)

# Allow using a non-KDAB install location.
set(KDAB_INSTALL True CACHE INTERNAL "Install to default KDAB Location")
if(DEFINED CMAKE_INSTALL_PREFIX)
  if(NOT "${CMAKE_INSTALL_PREFIX}" STREQUAL "")
    set(KDAB_INSTALL False CACHE INTERNAL "Install to non-KDAB Location")
  endif()
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.12.0")
  project(KDDockWidgets LANGUAGES CXX)
else()
  project(KDDockWidgets
          DESCRIPTION "An advanced docking system for Qt"
          HOMEPAGE_URL "https://github.com/KDAB/KDDockWidgets"
          LANGUAGES CXX)
endif()

set(KDDockWidgets_VERSION_MAJOR 2)
set(KDDockWidgets_VERSION_MINOR 0)
set(KDDockWidgets_VERSION_PATCH 9)
set(KDDockWidgets_VERSION ${KDDockWidgets_VERSION_MAJOR}.${KDDockWidgets_VERSION_MINOR}.${KDDockWidgets_VERSION_PATCH})
set(PROJECT_VERSION ${KDDockWidgets_VERSION}) #PROJECT_VERSION is needed by some ECM modules
set(KDDockWidgets_SOVERSION "2.0")

include(FeatureSummary)

option(KDDockWidgets_QT6 "Build against Qt 6" OFF)
option(KDDockWidgets_DEVELOPER_MODE "Developer Mode" OFF)
option(KDDockWidgets_PYTHON_BINDINGS "Build python bindings" OFF)
option(KDDockWidgets_STATIC "Build statically" OFF)
option(KDDockWidgets_TESTS "Build the tests" OFF)
option(KDDockWidgets_EXAMPLES "Build the examples" ON)
option(KDDockWidgets_DOCS "Build the API documentation" OFF)
option(KDDockWidgets_WERROR "Use -Werror (will be true for developer-mode unconditionally)" OFF)
option(KDDockWidgets_X11EXTRAS "On Linux, link against QtX11Extras so we can detect if the compositor supports transparency. Not applicable to other platforms or Qt6." ON)
option(KDDockWidgets_XLib "On Linux, link against XLib, for a more robust window z-order detection." OFF)
option(KDDockWidgets_CODE_COVERAGE "Enable coverage reporting" OFF)
option(KDDockWidgets_FRONTENDS "Semicolon separated list of frontends to enable" "")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/ECM/modules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/KDAB/modules")

# Set a default build type if none was specified
set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git" OR KDDockWidgets_DEVELOPER_MODE)
  set(default_build_type "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to ${default_build_type} as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if (KDDockWidgets_XLib)
  add_definitions(-DKDDockWidgets_XLIB)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src) # TODOv2 Replace with target_include_directories (PRIVATE)

if(KDDockWidgets_QT6)
  set(Qt_VERSION_MAJOR 6)
  set(QT_MIN_VERSION "6.2.0")
  find_package(Qt6Widgets ${QT_MIN_VERSION} REQUIRED)
  find_package(Qt6Test ${QT_MIN_VERSION} REQUIRED)
  set(KDDockWidgets_LIBRARY_QTID "-qt6")
else()
  set(Qt_VERSION_MAJOR 5)
  set(QT_MIN_VERSION "5.15")
  find_package(Qt5Widgets ${QT_MIN_VERSION} REQUIRED)
  find_package(Qt5Test ${QT_MIN_VERSION} REQUIRED)
  set(KDDockWidgets_LIBRARY_QTID "")
endif()
include(KDQtInstallPaths) #to set QT_INSTALL_FOO variables

# BEGIN frontend enabling
if (KDDockWidgets_FRONTENDS)
  set(KDDockWidgets_ALL_FRONTENDS "qtwidgets;qtquick")
  foreach(frontend ${KDDockWidgets_FRONTENDS})
    if (NOT ${frontend} IN_LIST KDDockWidgets_ALL_FRONTENDS)
      message(FATAL_ERROR "Unknown frontend ${frontend}")
    endif()
  endforeach()
endif()

if (KDDockWidgets_FRONTENDS)
  # qtwidgets
  if ("qtwidgets" IN_LIST KDDockWidgets_FRONTENDS)
    find_package(Qt${Qt_VERSION_MAJOR}Widgets ${QT_MIN_VERSION} REQUIRED)
    set(KDDW_FRONTEND_QTWIDGETS ON)
  endif()
  # qtquick
  if ("qtquick" IN_LIST KDDockWidgets_FRONTENDS)
    find_package(Qt${Qt_VERSION_MAJOR} ${QT_MIN_VERSION} NO_MODULE REQUIRED COMPONENTS Quick QuickControls2)
    set(KDDW_FRONTEND_QTQUICK ON)
  endif()
else()
  set(ENABLED_FRONTENDS "")
  message("No frontends specified explicitly.")
  # qtwidgets
  if (Qt${Qt_VERSION_MAJOR}Widgets_FOUND)
    list(APPEND ENABLED_FRONTENDS "qtwidgets")
    set(KDDW_FRONTEND_QTWIDGETS ON)
  endif()
  # qtquick
  find_package(Qt${Qt_VERSION_MAJOR} ${QT_MIN_VERSION} NO_MODULE REQUIRED COMPONENTS Quick QuickControls2)
  if (Qt${Qt_VERSION_MAJOR}Quick_FOUND AND Qt${Qt_VERSION_MAJOR}QuickControls2_FOUND)
    list(APPEND ENABLED_FRONTENDS "qtquick")
    set(KDDW_FRONTEND_QTQUICK ON)
  endif()

  if (NOT ENABLED_FRONTENDS)
    message(FATAL_ERROR "Failed to enable any frontends. Please install the required libraries and try again.")
  endif()

  message("Following frontends have been enabled:")
  foreach (frontend ${ENABLED_FRONTENDS})
    message("* ${frontend}")
  endforeach()
endif()
# END frontend enabling

add_definitions(-DQT_NO_KEYWORDS)


if (KDDW_FRONTEND_QTWIDGETS)
  add_definitions(-DKDDW_FRONTEND_QTWIDGETS)
  set(KDDockWidgets_DEPS "widgets")
endif()

if (KDDW_FRONTEND_QTQUICK)
  add_definitions(-DKDDW_FRONTEND_QTQUICK)
  set(KDDockWidgets_DEPS "${KDDockWidgets_DEPS} quick quickcontrols2")
endif()

if(NOT WIN32 AND NOT APPLE AND NOT EMSCRIPTEN AND NOT KDDockWidgets_QT6 AND KDDockWidgets_X11EXTRAS)
  set(KDDockWidgets_DEPS "${KDDockWidgets_DEPS} x11extras")
endif()

#Always build the test harness in developer-mode
if(KDDockWidgets_DEVELOPER_MODE)
  set(KDDockWidgets_TESTS ON)
  set(KDDockWidgets_WERROR ON)
  include(ECMEnableSanitizers)
  # find_package(doctest REQUIRED) TODOv2
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(IS_CLANG_BUILD TRUE)
else()
  set(IS_CLANG_BUILD FALSE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Default to hidden visibility for symbols
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

macro(set_compiler_flags targetName)
  if(KDDockWidgets_DEVELOPER_MODE)
    target_compile_definitions(${targetName} PUBLIC DOCKS_DEVELOPER_MODE PRIVATE QT_FORCE_ASSERTS)

    if(NOT MSVC)
      target_compile_options(${targetName} PRIVATE -Wall -Wextra)
    endif()

    # // TODOv2: KDBindings is failing due to weak-vtables
    # if(APPLE)
    #   target_compile_options(${targetName} PRIVATE -Wweak-vtables)
    # endif()
  endif()

  # Enable -Werror
  if(KDDockWidgets_WERROR AND (NOT MSVC OR IS_CLANG_BUILD)) # clang-cl accepts these too
    target_compile_options(${targetName} PRIVATE -Werror -Wundef -Wno-error=deprecated-declarations)
  endif()
endmacro()

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT APPLE) OR
  (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT APPLE) OR
  (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" AND NOT WIN32))
  # Linker warnings should be treated as errors
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--fatal-warnings ${CMAKE_SHARED_LINKER_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--fatal-warnings ${CMAKE_MODULE_LINKER_FLAGS}")

  string(TOUPPER "CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE}" compileflags)
  if("${CMAKE_CXX_FLAGS} ${${compileflags}}" MATCHES "-fsanitize")
    set(sanitizers_enabled TRUE)
  else()
    set(sanitizers_enabled FALSE)
  endif()

  if(APPLE OR LINUX)
    # cannot enable this for clang + sanitizers
    if(NOT sanitizers_enabled OR NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
      # Do not allow undefined symbols, even in non-symbolic shared libraries
      set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")
      set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_MODULE_LINKER_FLAGS}")
    endif()
  endif()
endif()

if(KDDockWidgets_STATIC)
  set(KDDockWidgets_LIBRARY_MODE "STATIC")
else()
  set(KDDockWidgets_LIBRARY_MODE "SHARED")
endif()

if(KDAB_INSTALL)
  if(UNIX)
    set(CMAKE_INSTALL_PREFIX "/usr/local/KDAB/KDDockWidgets-${KDDockWidgets_VERSION}" CACHE INTERNAL "Install to default KDAB Location")
  elseif(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:\\KDAB\\KDDockWidgets-${KDDockWidgets_VERSION}" CACHE INTERNAL "Install to default KDAB Location")
  endif()
endif()

# setup default install locations
include(InstallLocation)

if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(KDDockWidgets_IS_ROOT_PROJECT TRUE)

  message(STATUS "Building KDDockWidgets ${KDDockWidgets_VERSION} in ${CMAKE_BUILD_TYPE} mode. Installing to ${CMAKE_INSTALL_PREFIX}")

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/lib")

  install(FILES LICENSE.txt README.md DESTINATION ${INSTALL_DOC_DIR})
  install(DIRECTORY LICENSES DESTINATION ${INSTALL_DOC_DIR})

  # Generate .pri file for qmake users
  #TODO: ECM does not support Qt6 yet
  if(Qt_VERSION_MAJOR EQUAL 5 AND
    CMAKE_VERSION VERSION_GREATER "3.11.99" AND NOT CMAKE_CONFIGURATION_TYPES) # Not working with VS generator or older cmake versions
    include(ECMGeneratePriFile)
    set(PROJECT_VERSION_STRING ${KDDockWidgets_VERSION})
    ecm_generate_pri_file(BASE_NAME KDDockWidgets
      LIB_NAME kddockwidgets
      DEPS ${KDDockWidgets_DEPS}
      FILENAME_VAR pri_filename
      INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_INCLUDEDIR}
    )
    install(FILES ${pri_filename} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})
  endif()
else()
  #Always disable tests, examples, docs when used as a submodule
  set(KDDockWidgets_IS_ROOT_PROJECT FALSE)
  set(KDDockWidgets_TESTS FALSE)
  set(KDDockWidgets_EXAMPLES FALSE)
  set(KDDockWidgets_DOCS FALSE)
endif()

if(KDDockWidgets_TESTS)
  enable_testing()
endif()

add_subdirectory(src)

if(KDDockWidgets_PYTHON_BINDINGS)
  if(CMAKE_BUILD_TYPE MATCHES "^[Dd]eb" OR KDDockWidgets_STATIC)
    message(FATAL_ERROR "** Python Bindings are disabled in debug or static builds.")
  endif()
endif()
if(KDDockWidgets_PYTHON_BINDINGS)
  add_subdirectory(python)
endif()

if(KDDockWidgets_EXAMPLES)
  if(KDDW_FRONTEND_QTQUICK)
    add_subdirectory(examples/qtquick)
  endif()
  if(KDDW_FRONTEND_QTWIDGETS)
    add_subdirectory(examples/dockwidgets)
    add_subdirectory(examples/minimal)
    add_subdirectory(examples/minimal-mdi)
    add_subdirectory(examples/mdi_with_docking)
    set_compiler_flags(kddockwidgets_example)
    set_compiler_flags(kddockwidgets_minimal_example)
    set_compiler_flags(kddockwidgets_mdi_with_docking_example)
  endif()
endif()

if(KDDockWidgets_TESTS)
  if(KDDockWidgets_DEVELOPER_MODE)
    add_subdirectory(tests)

    # Require Qt5.15.1 or higher to run the tests_launcher tests on Mac
    if(NOT APPLE OR Qt5Widgets_VERSION VERSION_GREATER 5.15.0)
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
    add_test(NAME tst_view COMMAND tst_view)
    add_test(NAME tst_viewwrapper COMMAND tst_viewwrapper)
    add_test(NAME tst_viewguard COMMAND tst_viewguard)
    add_test(NAME tst_frame COMMAND tst_frame)
    add_test(NAME tst_titlebar COMMAND tst_titlebar)
    add_test(NAME tst_stack COMMAND tst_stack)
    add_test(NAME tst_tabbar COMMAND tst_tabbar)
    add_test(NAME tst_separator COMMAND tst_separator)
    add_test(NAME tst_floatingwindow COMMAND tst_floatingwindow)
    add_test(NAME tst_dockwidget COMMAND tst_dockwidget)
    add_test(NAME tst_multisplitter COMMAND tst_multisplitter)

    if(KDDW_FRONTEND_QTWIDGETS)
      add_test(NAME tst_qtwidgets COMMAND tst_qtwidgets)
    endif()
    if(KDDW_FRONTEND_QTQUICK)
      add_test(NAME tst_qtquick COMMAND tst_qtquick)
    endif()
  endif()
endif()

if(KDDockWidgets_DOCS)
  add_subdirectory(docs) # needs to go last, in case there are build source files
endif()

if(KDDockWidgets_IS_ROOT_PROJECT)
   # Add uninstall target (not for submodules since parent projects typically have uninstall too)
  include(ECMUninstallTarget)
endif()

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
