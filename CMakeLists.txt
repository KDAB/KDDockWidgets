cmake_minimum_required(VERSION 3.7)

if (${CMAKE_VERSION} VERSION_LESS "3.12.0")
    project(KDDockWidgets VERSION 0.1 LANGUAGES CXX)
else()
    project(KDDockWidgets
            VERSION 0.1
            DESCRIPTION "An advanced docking system for Qt"
            HOMEPAGE_URL "https://github.com/KDAB/KDDockWidgets"
            LANGUAGES CXX)
endif()


cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0042 NEW)

option(OPTION_DEVELOPER_MODE "Developer Mode" OFF)
option(OPTION_BUILD_PYTHON_BINDINGS "Build python bindings" OFF)
# option(OPTION_QTQUICK "Build for QtQuick instead of QtWidgets" OFF)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)

set(ECM_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ECM/modules/")
set(PYTHON_MODULE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake/Python")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake" ${ECM_MODULE_DIR} ${PYTHON_MODULE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# setup default install locations
include(InstallLocation)

macro(set_compiler_flags targetName)
    if (OPTION_DEVELOPER_MODE)
        target_compile_definitions(${targetName} PRIVATE DOCKS_DEVELOPER_MODE QT_FORCE_ASSERTS)
        if (NOT MSVC)
            target_compile_options(${targetName} PRIVATE -Wall -Wextra -Werror -Wno-error=deprecated-declarations)
        endif()
    endif()
endmacro()

if (OPTION_QTQUICK)
    find_package(Qt5Quick)
    add_definitions(-DKDDOCKWIDGETS_QTQUICK)
else()
    add_definitions(-DKDDOCKWIDGETS_QTWIDGETS)
endif()

# Generate .pri file for qmake users
include(ECMGeneratePriFile)
set(PROJECT_VERSION_STRING ${${PROJECT_NAME}_VERSION})
ecm_generate_pri_file(BASE_NAME KDDockWidgets
    LIB_NAME kddockwidgets
    FILENAME_VAR pri_filename
)
install(FILES ${pri_filename} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

add_subdirectory(src)
add_subdirectory(examples/dockwidgets)
if (OPTION_BUILD_PYTHON_BINDINGS)
    add_subdirectory(python)
endif()
set_compiler_flags(kddockwidgets_example)

if (OPTION_DEVELOPER_MODE)
    include(ECMEnableSanitizers)
    if (NOT OPTION_QTQUICK)
        enable_testing()
        add_subdirectory(tests)

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

        add_test(NAME tst_multisplitter COMMAND tst_multisplitter)
    endif()
endif()
