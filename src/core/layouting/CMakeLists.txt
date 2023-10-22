#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.

# This is the CMakeLists.txt used by passing -DKDDockWidgets_SEPARATE_LAYOUTING_LIBRARY=ON

cmake_minimum_required(VERSION 3.21)

project(
    KDDockWidgets
    DESCRIPTION "KDDockWidgets standalone layouting library"
    HOMEPAGE_URL "https://github.com/KDAB/KDDockWidgets"
    LANGUAGES CXX C
)

set(KDDW_LAYOUTING_SRCS Item.cpp ItemFreeContainer.cpp ../../qtcompat/Object.cpp)

add_library(kddockwidgetslayouting SHARED ${KDDW_LAYOUTING_SRCS})

target_include_directories(
    kddockwidgetslayouting
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../fwd_headers>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../core>
           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..> $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
)

target_link_libraries(kddockwidgetslayouting PRIVATE kdbindings)

include(../../nlohmann.cmake)
link_to_nlohman(kddockwidgetslayouting)

include(GenerateExportHeader)
generate_export_header(
    kddockwidgetslayouting EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/kddockwidgets_export.h" EXPORT_MACRO_NAME DOCKS_EXPORT
)
