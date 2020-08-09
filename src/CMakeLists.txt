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

if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

add_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS
                -DQT_USE_QSTRINGBUILDER
                -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
                -DQT_STRICT_ITERATORS
                -DQT_NO_KEYWORDS
                -DQT_NO_FOREACH
)

set(DOCKSLIBS_SRCS
    Config.cpp
    Qt5Qt6Compat_p.h
    FocusScope.cpp
    FrameworkWidgetFactory.cpp
    DockWidgetBase.cpp
    MainWindowBase.cpp
    LayoutSaver.cpp
    private/MultiSplitter.cpp
    private/Position.cpp
    private/ObjectViewer.cpp
    private/DropIndicatorOverlayInterface.cpp
    private/DropArea.cpp
    private/FloatingWindow.cpp
    private/Logging.cpp
    private/TitleBar.cpp
    private/DockRegistry.cpp
    private/Draggable.cpp
    private/WindowBeingDragged.cpp
    private/DragController.cpp
    private/Frame.cpp
    private/DropAreaWithCentralFrame.cpp
    private/WidgetResizeHandler.cpp
    private/indicators/ClassicIndicators.cpp
    private/indicators/ClassicIndicatorsWindow.cpp
)

set(DOCKS_INSTALLABLE_INCLUDES
    docks_export.h
    Config.h
    FrameworkWidgetFactory.h
    DockWidgetBase.h
    KDDockWidgets.h
    FocusScope.h
    QWidgetAdapter.h
    LayoutSaver.h
    LayoutSaver_p.h
)

set(DOCKS_INSTALLABLE_PRIVATE_INCLUDES
    private/Draggable_p.h
    private/DropIndicatorOverlayInterface_p.h
    private/FloatingWindow_p.h
    private/Frame_p.h
    private/TitleBar_p.h
)

set(DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES
    private/widgets/QWidgetAdapter_widgets_p.h
    private/widgets/TitleBarWidget_p.h
    private/widgets/FloatingWindowWidget_p.h
    private/widgets/FrameWidget_p.h
    private/widgets/TabBarWidget_p.h
    private/widgets/TabWidgetWidget_p.h
    private/TabWidget_p.h
)

if(OPTION_QTQUICK)
  set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS}
      private/quick/DockWidgetQuick.cpp
      private/quick/QWidgetAdapter_quick.cpp
      private/quick/FloatingWindowQuick.cpp
      private/quick/TitleBarQuick.cpp
      private/quick/QmlTypes.cpp
      private/quick/FrameQuick.cpp
      private/quick/MainWindowQuick.cpp
      private/quick/MainWindowWrapper.cpp
      )

    qt5_add_resources(RESOURCES_QUICK ${CMAKE_CURRENT_SOURCE_DIR}/qtquick.qrc)
else()
  set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS}
      private/DebugWindow.cpp
      private/TabWidget.cpp
      MainWindow.cpp
      private/widgets/TabBarWidget.cpp
      private/widgets/FloatingWindowWidget.cpp
      private/widgets/FrameWidget.cpp
      private/widgets/TabWidgetWidget.cpp
      private/widgets/TitleBarWidget.cpp
      private/widgets/DockWidget.cpp
      private/widgets/QWidgetAdapter_widgets.cpp
      # private/indicators/AnimatedIndicators.cpp
  )

  set(DOCKS_INSTALLABLE_INCLUDES
      ${DOCKS_INSTALLABLE_INCLUDES}
      MainWindow.h
      MainWindowBase.h
      DockWidget.h
  )
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(IS_CLANG_BUILD TRUE)
else()
  set(IS_CLANG_BUILD FALSE)
endif()

add_subdirectory(private/multisplitter)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

add_library(kddockwidgets ${KDDockWidgets_LIBRARY_MODE} ${DOCKSLIBS_SRCS} ${DOCKS_INSTALLABLE_INCLUDES} ${RESOURCES} ${RESOURCES_QUICK})
add_library(KDAB::kddockwidgets ALIAS kddockwidgets)
set_compiler_flags(kddockwidgets)

target_include_directories(kddockwidgets
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<INSTALL_INTERFACE:include/kddockwidgets>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fwd_headers>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/private
)

target_compile_definitions(kddockwidgets
  PRIVATE
  QT_NO_CAST_TO_ASCII
  QT_NO_CAST_FROM_ASCII
  QT_NO_URL_CAST_FROM_STRING
  QT_NO_CAST_FROM_BYTEARRAY
)
if(${PROJECT_NAME}_STATIC)
  target_compile_definitions(kddockwidgets PUBLIC KDDOCKWIDGETS_STATICLIB)
else()
  target_compile_definitions(kddockwidgets PRIVATE BUILDING_DOCKS_LIBRARY)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD)
  target_compile_options(kddockwidgets PRIVATE -Wshadow -Wconversion -fvisibility=hidden)

  if(IS_CLANG_BUILD)
    target_compile_options(kddockwidgets PRIVATE -Wweak-vtables)
  endif()
endif()

if(OPTION_QTQUICK)
  target_link_libraries(kddockwidgets PUBLIC Qt5::Widgets Qt5::Quick Qt5::QuickControls2 kddockwidgets_multisplitter)
else()
  target_link_libraries(kddockwidgets PUBLIC Qt5::Widgets kddockwidgets_multisplitter)
endif()

if(NOT WIN32 AND NOT APPLE)
  find_package(Qt5X11Extras)
  target_link_libraries(kddockwidgets PUBLIC Qt5::X11Extras)
endif()

#version libraries on Windows
if(WIN32)
  set(postfix ${${PROJECT_NAME}_VERSION_MAJOR})
  set(CMAKE_RELEASE_POSTFIX ${postfix})
  set_target_properties(kddockwidgets PROPERTIES RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX})
  #append 'd' to debug libraries
  string(CONCAT postfix ${postfix} "d")
  set(CMAKE_DEBUG_POSTFIX ${postfix})
  set_target_properties(kddockwidgets PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
endif()

install(TARGETS kddockwidgets
        EXPORT kddockwidgetsTargets
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}
)
if(MSVC AND NOT ${PROJECT_NAME}_STATIC)
  install(FILES "$<TARGET_PDB_FILE_DIR:kddockwidgets>/$<TARGET_PDB_FILE_NAME:kddockwidgets>" DESTINATION ${INSTALL_LIBRARY_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()
install(FILES ${DOCKS_INSTALLABLE_INCLUDES} DESTINATION include/kddockwidgets)
install(FILES ${DOCKS_INSTALLABLE_PRIVATE_INCLUDES} DESTINATION include/kddockwidgets/private)
install(FILES private/multisplitter/Item_p.h DESTINATION include/kddockwidgets/multisplitter)
install(FILES private/multisplitter/Widget.h DESTINATION include/kddockwidgets/multisplitter)
install(FILES private/multisplitter/Widget_qwidget.h DESTINATION include/kddockwidgets/multisplitter)
install(FILES private/multisplitter/Separator_p.h DESTINATION include/kddockwidgets/multisplitter)
install(FILES private/multisplitter/Separator_qwidget.h DESTINATION include/kddockwidgets/multisplitter)
install(FILES private/multisplitter/multisplitter_export.h DESTINATION include/kddockwidgets/multisplitter)
install(FILES ${DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES} DESTINATION include/kddockwidgets/private/widgets)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  KDDockWidgetsConfigVersion.cmake
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY AnyNewerVersion
)

install(EXPORT kddockwidgetsTargets
        FILE KDDockWidgetsTargets.cmake
        NAMESPACE KDAB::
        DESTINATION ${INSTALL_LIBRARY_DIR}/cmake/KDDockWidgets
)
configure_file(KDDockWidgetsConfig.cmake.in KDDockWidgetsConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgetsConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgetsConfigVersion.cmake"
        DESTINATION ${INSTALL_LIBRARY_DIR}/cmake/KDDockWidgets
)

if(OPTION_DEVELOPER_MODE)
  # Under developer mode since kddw might be a sub-folder of a project setting a different value for QT_DISABLE_DEPRECATED_BEFORE
  target_compile_definitions(kddockwidgets PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)

  if (NOT OPTION_QTQUICK) # TODO: We can support it
    add_executable(kddockwidgets_linter layoutlinter_main.cpp)
    target_link_libraries(kddockwidgets_linter kddockwidgets kddockwidgets_multisplitter Qt5::Widgets)
  endif()
endif()
