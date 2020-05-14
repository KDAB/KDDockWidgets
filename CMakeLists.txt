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
# option(OPTION_QTQUICK "Build for QtQuick instead of QtWidgets" OFF)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)

set(ECM_MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake/ECM/modules/")
set(CMAKE_MODULE_PATH ${ECM_MODULE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (OPTION_DEVELOPER_MODE)
    include(ECMEnableSanitizers)
    add_definitions(-DDOCKS_DEVELOPER_MODE -DQT_FORCE_ASSERTS)
    if (NOT MSVC)
        add_compile_options(-Wall -Wextra -Werror)
    endif()
endif()

if (OPTION_QTQUICK)
    find_package(Qt5Quick)
    add_definitions(-DKDDOCKWIDGETS_QTQUICK)
else()
    add_definitions(-DKDDOCKWIDGETS_QTWIDGETS)
endif()

add_subdirectory(src)
add_subdirectory(examples/dockwidgets)

if (OPTION_DEVELOPER_MODE)
    if (NOT OPTION_QTQUICK)
        enable_testing()
        add_subdirectory(tests)
        add_test(NAME tst_docks COMMAND tst_docks)
        add_test(NAME tst_multisplitter COMMAND tst_multisplitter)
    endif()
endif()
