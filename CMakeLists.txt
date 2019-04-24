cmake_minimum_required(VERSION 3.3)

project(docks)
find_package(Qt5Widgets)

cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0042 NEW)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(OPTION_DEVELOPER_MODE "Developer Mode" OFF)

if (OPTION_DEVELOPER_MODE)
    add_definitions(-DDOCKS_DEVELOPER_MODE)
endif()

if (OPTION_DEVELOPER_MODE)
    add_definitions(-DQT_FORCE_ASSERTS)
endif()

add_definitions(-DQT_NO_CAST_TO_ASCII
                -DQT_NO_CAST_FROM_ASCII
                -DQT_NO_URL_CAST_FROM_STRING
                -DQT_NO_CAST_FROM_BYTEARRAY
                -DQT_NO_SIGNALS_SLOTS_KEYWORDS
                -DQT_USE_QSTRINGBUILDER
                -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
                -DQT_STRICT_ITERATORS
               )

add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
set(CMAKE_AUTOMOC ON)
add_definitions(-DQT_NO_FOREACH)
add_subdirectory(src)

if (OPTION_DEVELOPER_MODE)
    add_subdirectory(tests)
    add_subdirectory(examples)
endif()
