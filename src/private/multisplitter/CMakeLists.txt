#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

set(MULTISPLITTER_SRCS
    Item.cpp
    Item_p.h
    Logging.cpp
    Logging_p.h
    MultiSplitterConfig.cpp
    MultiSplitterConfig.h
    Separator.cpp
    Separator_p.h
    Widget.cpp
    Widget.h
    multisplitter_export.h
)

set(MULTISPLITTER_SRCS_QTWIDGETS
    Widget_qwidget.cpp
    Widget_qwidget.h
    Separator_qwidget.cpp
    Separator_qwidget.h
)

set(MULTISPLITTER_SRCS_QTQUICK
    Widget_quick.cpp
    Widget_quick.h
    Separator_quick.cpp
    Separator_quick.h
    Rubberband_quick.cpp
    Rubberband_quick.h
)


if(${PROJECT_NAME}_QTQUICK)
  find_package(Qt${QT_MAJOR_VERSION}Quick)
  set(MULTISPLITTER_SRCS ${MULTISPLITTER_SRCS} ${MULTISPLITTER_SRCS_QTQUICK})
  add_definitions(-DKDMULTISPLITTER_QTQUICK)
else()
  find_package(Qt${QT_MAJOR_VERSION}Widgets)
  set(MULTISPLITTER_SRCS ${MULTISPLITTER_SRCS} ${MULTISPLITTER_SRCS_QTWIDGETS})
  add_definitions(-DKDMULTISPLITTER_QTWIDGETS)
endif()

set(MULTISPLITTER_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/kddockwidgets_multisplitter.qrc)

add_library(kddockwidgets_multisplitter ${KDDockWidgets_LIBRARY_MODE} ${MULTISPLITTER_SRCS} ${MULTISPLITTER_RESOURCES})
add_library(KDAB::kddockwidgets_multisplitter ALIAS kddockwidgets_multisplitter)

set_compiler_flags(kddockwidgets_multisplitter)

if(${PROJECT_NAME}_QTQUICK)
  target_link_libraries(kddockwidgets_multisplitter Qt${QT_MAJOR_VERSION}::Core Qt${QT_MAJOR_VERSION}::Quick)
else()
  target_link_libraries(kddockwidgets_multisplitter Qt${QT_MAJOR_VERSION}::Core Qt${QT_MAJOR_VERSION}::Widgets)
endif()

if(${PROJECT_NAME}_STATIC)
  target_compile_definitions(kddockwidgets_multisplitter PUBLIC MULTISPLITTER_STATICLIB)
else()
  target_compile_definitions(kddockwidgets_multisplitter PRIVATE BUILDING_MULTISPLITTER_LIBRARY)
endif()

if(${PROJECT_NAME}_DEVELOPER_MODE)
  # Under developer mode since kddw might be a sub-folder of a project setting a different value for QT_DISABLE_DEPRECATED_BEFORE
  target_compile_definitions(kddockwidgets_multisplitter PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)

  set_target_properties(kddockwidgets_multisplitter PROPERTIES UNITY_BUILD ON)

  if(${PROJECT_NAME}_TESTS AND NOT ${PROJECT_NAME}_QTQUICK)
    add_subdirectory(tests)
  endif()
endif()

target_include_directories(kddockwidgets_multisplitter
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../fwd_headers>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(kddockwidgets_multisplitter PROPERTIES
  SOVERSION ${${PROJECT_NAME}_SOVERSION}
  VERSION ${${PROJECT_NAME}_VERSION}
)

#version libraries on Windows
if(WIN32)
  set(postfix ${${PROJECT_NAME}_VERSION_MAJOR})
  set(CMAKE_RELEASE_POSTFIX ${postfix})
  set_target_properties(kddockwidgets_multisplitter PROPERTIES RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX})
  #append 'd' to debug libraries
  string(CONCAT postfix ${postfix} "d")
  set(CMAKE_DEBUG_POSTFIX ${postfix})
  set_target_properties(kddockwidgets_multisplitter PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
endif()

install(TARGETS kddockwidgets_multisplitter
        EXPORT kddockwidgetsTargets
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}
)
if(MSVC AND NOT ${PROJECT_NAME}_STATIC)
  install(FILES "$<TARGET_PDB_FILE_DIR:kddockwidgets_multisplitter>/$<TARGET_PDB_FILE_NAME:kddockwidgets_multisplitter>" DESTINATION ${INSTALL_LIBRARY_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()
