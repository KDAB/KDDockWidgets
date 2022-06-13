
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

set(KDDW_BACKEND_SRCS
    KDDockWidgets.cpp
    Config.cpp
    Config.h
    Qt5Qt6Compat_p.h
    FocusScope.cpp
    FocusScope.h
    ViewFactory.cpp
    ViewFactory.h
    LayoutSaver.cpp
    LayoutSaver.h
    private/LayoutSaver_p.h
    private/Position.cpp
    private/Position_p.h
    private/Logging.cpp
    private/Logging_p.h
    private/DockRegistry.cpp
    private/DockRegistry_p.h
    private/Draggable.cpp
    private/Draggable_p.h
    private/WindowBeingDragged.cpp
    private/WindowBeingDragged_p.h
    private/DragController.cpp
    private/DragController_p.h
    private/WidgetResizeHandler.cpp
    private/WidgetResizeHandler_p.h
    private/WindowZOrder_x11_p.h
    private/multisplitter/Item.cpp
    private/multisplitter/Item_p.h
    private/multisplitter/ItemFreeContainer.cpp
    private/multisplitter/ItemFreeContainer_p.h
    controllers/DockWidget.cpp
    controllers/DockWidget.h
    controllers/DropArea.cpp
    controllers/DropArea.h
    controllers/DropIndicatorOverlay.cpp
    controllers/DropIndicatorOverlay.h
    controllers/FloatingWindow.cpp
    controllers/FloatingWindow.h
    controllers/Frame.cpp
    controllers/Frame.h
    controllers/Layout.cpp
    controllers/Layout.h
    controllers/MainWindow.cpp
    controllers/MainWindow.h
    controllers/MDILayout.cpp
    controllers/MDILayout.h
    controllers/Separator.cpp
    controllers/Separator.h
    controllers/SideBar.cpp
    controllers/SideBar.h
    controllers/Stack.cpp
    controllers/Stack.h
    controllers/TitleBar.cpp
    controllers/TitleBar.h
    controllers/TabBar.cpp
    controllers/TabBar.h
    controllers/indicators/NullIndicators.cpp
    controllers/indicators/NullIndicators.h
    controllers/indicators/ClassicIndicators.cpp
    controllers/indicators/ClassicIndicators.h
    controllers/indicators/SegmentedIndicators.cpp
    controllers/indicators/SegmentedIndicators.h
    Action.cpp
    Action.h
    Window.cpp
    Window.h
    View.cpp
    View.h
    ViewGuard.cpp
    ViewGuard.h
    ViewWrapper.cpp
    ViewWrapper.h
    Controller.cpp
    Controller.h
    Platform.cpp
    Platform.h
    views/ClassicIndicatorWindow.cpp
    views/MainWindowMDI.cpp
    views/MainWindowMDI.h
    qtcommon/Platform_qt.cpp
    qtcommon/Platform_qt.h
    qtcommon/Window_qt.cpp
    qtcommon/Window_qt.h
    kddockwidgets_resources.qrc
)

SET(KDDW_FRONTEND_QTWIDGETS_SRCS
    qtwidgets/Window_qtwidgets.cpp
    qtwidgets/Window_qtwidgets.h
    qtwidgets/Platform_qtwidgets.cpp
    qtwidgets/Platform_qtwidgets.h
    qtwidgets/views/View_qtwidgets.cpp
    qtwidgets/views/View_qtwidgets.h
    qtwidgets/views/ViewWrapper_qtwidgets.cpp
    qtwidgets/views/ViewWrapper_qtwidgets.h
    qtwidgets/views/FloatingWindow_qtwidgets.cpp
    qtwidgets/views/FloatingWindow_qtwidgets.h
    qtwidgets/views/DockWidget_qtwidgets.cpp
    qtwidgets/views/DockWidget_qtwidgets.h
    qtwidgets/views/DropArea_qtwidgets.cpp
    qtwidgets/views/DropArea_qtwidgets.h
    qtwidgets/views/MDILayout_qtwidgets.cpp
    qtwidgets/views/MDILayout_qtwidgets.h
    qtwidgets/views/Frame_qtwidgets.cpp
    qtwidgets/views/Frame_qtwidgets.h
    qtwidgets/views/MainWindow_qtwidgets.cpp
    qtwidgets/views/MainWindow_qtwidgets.h
    qtwidgets/views/MainWindowMDI_qtwidgets.cpp
    qtwidgets/views/MainWindowMDI_qtwidgets.h
    qtwidgets/views/RubberBand_qtwidgets.cpp
    qtwidgets/views/RubberBand_qtwidgets.h
    qtwidgets/views/Separator_qtwidgets.cpp
    qtwidgets/views/Separator_qtwidgets.h
    qtwidgets/views/TitleBar_qtwidgets.cpp
    qtwidgets/views/TitleBar_qtwidgets.h
    qtwidgets/views/TabBar_qtwidgets.cpp
    qtwidgets/views/TabBar_qtwidgets.h
    qtwidgets/views/Stack_qtwidgets.cpp
    qtwidgets/views/Stack_qtwidgets.h
    qtwidgets/views/SideBar_qtwidgets.cpp
    qtwidgets/views/ClassicIndicatorsOverlay_qtwidgets.cpp
    qtwidgets/views/ClassicIndicatorsOverlay_qtwidgets.h
    qtwidgets/views/ClassicIndicatorsWindow_qtwidgets.cpp
    qtwidgets/views/ClassicIndicatorsWindow_qtwidgets.h
    qtwidgets/views/SegmentedIndicatorsOverlay_qtwidgets.cpp
    qtwidgets/views/SegmentedIndicatorsOverlay_qtwidgets.h
    qtwidgets/TestHelpers_qtwidgets.cpp
    qtwidgets/MDIArea.cpp
    qtwidgets/MDIArea.h
    qtwidgets/ViewFactory_qtwidgets.cpp
    qtwidgets/ViewFactory_qtwidgets.h
    qtwidgets/DebugWindow.cpp
    qtwidgets/DebugWindow.h
    qtwidgets/ObjectViewer.cpp
    qtwidgets/ObjectViewer.h
)

SET(KDDW_FRONTEND_QTQUICK_SRCS
  qtquick/Window_qtquick.cpp
  qtquick/Window_qtquick.h
  qtquick/Platform_qtquick.cpp
  qtquick/Platform_qtquick.h
  qtquick/Helpers.cpp
  qtquick/TestHelpers_qtquick.cpp
  qtquick/ViewFactory_qtquick.cpp
  qtquick/ViewFactory_qtquick.h
  qtquick/LayoutSaverInstantiator.cpp
  qtquick/LayoutSaverInstantiator.h
  qtquick/MainWindowInstantiator.cpp
  qtquick/MainWindowInstantiator.h
  qtquick/DockWidgetInstantiator.cpp
  qtquick/DockWidgetInstantiator.h
  qtquick/QmlTypes.cpp
  qtquick/QmlTypes.h
  qtquick/views/DropArea_qtquick.cpp
  qtquick/views/DropArea_qtquick.h
  qtquick/views/DockWidget_qtquick.cpp
  qtquick/views/DockWidget_qtquick.h
  qtquick/views/FloatingWindow_qtquick.cpp
  qtquick/views/FloatingWindow_qtquick.h
  qtquick/views/Frame_qtquick.cpp
  qtquick/views/Frame_qtquick.h
  qtquick/views/MainWindow_qtquick.cpp
  qtquick/views/MainWindow_qtquick.h
  qtquick/views/MainWindowMDI_qtquick.cpp
  qtquick/views/MainWindowMDI_qtquick.h
  qtquick/views/MDILayout_qtquick.cpp
  qtquick/views/MDILayout_qtquick.h
  qtquick/views/RubberBand_qtquick.cpp
  qtquick/views/RubberBand_qtquick.h
  qtquick/views/Separator_qtquick.cpp
  qtquick/views/Separator_qtquick.h
  qtquick/views/Stack_qtquick.cpp
  qtquick/views/Stack_qtquick.h
  qtquick/views/TabBar_qtquick.cpp
  qtquick/views/TabBar_qtquick.h
  qtquick/views/TitleBar_qtquick.cpp
  qtquick/views/TitleBar_qtquick.h
  qtquick/views/View_qtquick.cpp
  qtquick/views/View_qtquick.h
  qtquick/views/ViewWrapper_qtquick.cpp
  qtquick/views/ViewWrapper_qtquick.h
  qtquick/views/ClassicIndicatorsWindow_qtquick.cpp
  qtquick/views/ClassicIndicatorsWindow_qtquick.h
  kddockwidgets_qtquick.qrc
)

set(DOCKS_INSTALLABLE_INCLUDES
    docks_export.h
    Config.h
    ViewFactory.h
    # DockWidget.h
    KDDockWidgets.h
    Qt5Qt6Compat_p.h
    FocusScope.h
    # QWidgetAdapter.h
    LayoutSaver.h
    # MainWindowMDI.h
    # MainWindow.h
)

set(DOCKS_INSTALLABLE_PRIVATE_INCLUDES
    private/DragController_p.h
    private/Draggable_p.h
    private/DropIndicatorOverlay.h
    # private/FloatingWindow_p.h
    # private/Frame_p.h
    private/LayoutSaver_p.h
    # private/Layout.h
    # private/SideBar_p.h
    private/TitleBar_p.h
    private/WindowBeingDragged_p.h
    private/WidgetResizeHandler_p.h
    private/DockRegistry_p.h
    # private/TabWidget_p.h
)

set(DOCKSLIBS_SRCS ${KDDW_BACKEND_SRCS})

if (KDDW_FRONTEND_QTWIDGETS)
  set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS} ${KDDW_FRONTEND_QTWIDGETS_SRCS})
endif()

if (KDDW_FRONTEND_QTQUICK)
  set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS} ${KDDW_FRONTEND_QTQUICK_SRCS})
endif()

#Generate C/C++ CamelCase forwarding headers (only public includes)
include(ECMGenerateHeaders)
ecm_generate_headers(camelcase_HEADERS
  ORIGINAL
    CAMELCASE
  HEADER_NAMES
    Config
    # DockWidget
    # DockWidgetBase
    FocusScope
    ViewFactory,
    # DefaultWidgetFactory
    LayoutSaver
    # MainWindow
    # MainWindowBase
    # MainWindowMDI
)

add_library(kddockwidgets ${KDDockWidgets_LIBRARY_MODE} ${DOCKSLIBS_SRCS} ${DOCKS_INSTALLABLE_INCLUDES} ${RESOURCES})

add_library(KDAB::kddockwidgets ALIAS kddockwidgets)
set_target_properties(kddockwidgets PROPERTIES OUTPUT_NAME "kddockwidgets${KDDockWidgets_LIBRARY_QTID}")
set_compiler_flags(kddockwidgets)

if(KDDockWidgets_QT6)
  set(DOCKS_INCLUDES_INSTALL_PATH "include/kddockwidgets-qt6")
else()
  set(DOCKS_INCLUDES_INSTALL_PATH "include/")
endif()


target_include_directories(kddockwidgets
  PUBLIC
    $<INSTALL_INTERFACE:${DOCKS_INCLUDES_INSTALL_PATH}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fwd_headers>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fwd_headers/qtwidgets>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/fwd_headers/qtquick>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/3rdparty> # TODOm2: Link to KDBindings instead
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(kddockwidgets
  PRIVATE
  QT_NO_CAST_TO_ASCII
  QT_NO_CAST_FROM_ASCII
  QT_NO_URL_CAST_FROM_STRING
  QT_NO_CAST_FROM_BYTEARRAY
)
if(KDDockWidgets_STATIC)
  target_compile_definitions(kddockwidgets PUBLIC KDDOCKWIDGETS_STATICLIB)
else()
  target_compile_definitions(kddockwidgets PRIVATE BUILDING_DOCKS_LIBRARY)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD)
  target_compile_options(kddockwidgets PRIVATE -Wshadow)
  if(NOT MSVC)
    target_compile_options(kddockwidgets PRIVATE -fvisibility=hidden)
  endif()

  # Disable -Wconversion for Qt6. The qsizetype to int conversions are harmless
  if(NOT KDDockWidgets_QT6)
    target_compile_options(kddockwidgets PRIVATE -Wconversion)
  endif()

  if(IS_CLANG_BUILD)
    # // TODOm2: KDBindings is failing due to weak-vtables
    # target_compile_options(kddockwidgets PRIVATE -Wweak-vtables)
  endif()
endif()

# BEGIN coverage
add_library(coverage_options INTERFACE)

if(KDDockWidgets_CODE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD) AND NOT MSVC)
  if(KDDockWidgets_DEVELOPER_MODE)
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_options INTERFACE --coverage)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
      target_link_options(coverage_options INTERFACE --coverage)
    else()
      target_link_libraries(coverage_options INTERFACE --coverage)
    endif()
  endif()
endif()
# END coverage

if (KDDW_FRONTEND_QTWIDGETS)
  target_link_libraries(kddockwidgets PUBLIC Qt${Qt_VERSION_MAJOR}::Widgets PRIVATE Qt${Qt_VERSION_MAJOR}::WidgetsPrivate)
endif()

if (KDDW_FRONTEND_QTQUICK)
  target_link_libraries(kddockwidgets PUBLIC Qt${Qt_VERSION_MAJOR}::Quick Qt${Qt_VERSION_MAJOR}::QuickControls2)
  target_link_libraries(kddockwidgets PRIVATE Qt${Qt_VERSION_MAJOR}::GuiPrivate)
endif()

if (KDDockWidgets_CODE_COVERAGE)
  target_link_libraries(kddockwidgets PUBLIC coverage_options)
endif()

if (KDDockWidgets_DEVELOPER_MODE)
  find_package(Qt${Qt_VERSION_MAJOR}Test ${QT_MIN_VERSION} REQUIRED)
  target_link_libraries(kddockwidgets PUBLIC Qt${Qt_VERSION_MAJOR}::Test)
endif()


if(WIN32)
  target_link_libraries(kddockwidgets PRIVATE Qt${Qt_VERSION_MAJOR}::GuiPrivate dwmapi)
elseif(NOT APPLE AND NOT EMSCRIPTEN AND NOT KDDockWidgets_QT6 AND KDDockWidgets_X11EXTRAS)
  find_package(Qt${Qt_VERSION_MAJOR}X11Extras)
  target_link_libraries(kddockwidgets PUBLIC Qt${Qt_VERSION_MAJOR}::X11Extras)
endif()

if(KDDockWidgets_XLib)
  target_link_libraries(kddockwidgets PRIVATE X11)
endif()

find_package(nlohmann_json)
if (nlohmann_json_FOUND)
  target_link_libraries(kddockwidgets PRIVATE nlohmann_json::nlohmann_json)
else()
  message("nlohmann_json not found in system. Using our own bundled one")
  target_include_directories(kddockwidgets SYSTEM PRIVATE 3rdparty/nlohmann)
endif()

set_target_properties(kddockwidgets PROPERTIES
  SOVERSION ${KDDockWidgets_SOVERSION}
  VERSION ${KDDockWidgets_VERSION}
)

#version libraries on Windows
if(WIN32)
  if(CMAKE_BUILD_TYPE)
    set(postfix ${KDDockWidgets_VERSION_MAJOR})
    string(TOUPPER ${CMAKE_BUILD_TYPE} UPPER_BUILD_TYPE)
    if(${UPPER_BUILD_TYPE} MATCHES "^DEBUG")
      string(CONCAT postfix ${postfix} "d")
      set_target_properties(kddockwidgets PROPERTIES DEBUG_POSTFIX ${postfix})
    else()
      set_target_properties(kddockwidgets PROPERTIES ${UPPER_BUILD_TYPE}_POSTFIX ${postfix})
    endif()
  elseif(CMAKE_CONFIGURATION_TYPES)
    # Visual Studio generator
    set_target_properties(kddockwidgets PROPERTIES DEBUG_POSTFIX d)
  endif()
endif()

install(TARGETS kddockwidgets
        EXPORT kddockwidgetsTargets
        RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
        LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
        ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}
)
if(MSVC AND NOT KDDockWidgets_STATIC)
  install(FILES "$<TARGET_PDB_FILE_DIR:kddockwidgets>/$<TARGET_PDB_FILE_NAME:kddockwidgets>" DESTINATION ${INSTALL_LIBRARY_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()

install(FILES ${camelcase_HEADERS} DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets)
install(FILES ${DOCKS_INSTALLABLE_INCLUDES} DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets)
install(FILES ${DOCKS_INSTALLABLE_PRIVATE_INCLUDES} DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private)
install(FILES private/multisplitter/Item_p.h DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/multisplitter)
install(FILES private/indicators/ClassicIndicators_p.h DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/indicators)
# install(FILES private/indicators/SegmentedIndicators_p.h DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/indicators)

if(KDDockWidgets_QTQUICK)
  install(FILES ${DOCKS_INSTALLABLE_PRIVATE_QUICK_INCLUDES} DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/quick)
  install(FILES private/multisplitter/Separator_quick.h DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/multisplitter)
  install(FILES private/multisplitter/Widget_quick.h DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/multisplitter)
else()
  install(FILES ${DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES} DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets/private/widgets)
endif()

# Generate library version files
include(ECMSetupVersion)
ecm_setup_version(
  ${KDDockWidgets_VERSION}
  VARIABLE_PREFIX KDDOCKWIDGETS
  VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kddockwidgets_version.h"
  PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets${KDDockWidgets_LIBRARY_QTID}ConfigVersion.cmake"
  SOVERSION ${KDDockWidgets_SOVERSION}
  COMPATIBILITY AnyNewerVersion
)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/kddockwidgets_version.h" DESTINATION ${DOCKS_INCLUDES_INSTALL_PATH}/kddockwidgets)

install(EXPORT kddockwidgetsTargets
        FILE KDDockWidgets${KDDockWidgets_LIBRARY_QTID}Targets.cmake
        NAMESPACE KDAB::
        DESTINATION ${INSTALL_LIBRARY_DIR}/cmake/KDDockWidgets${KDDockWidgets_LIBRARY_QTID}
)
configure_file(KDDockWidgetsConfig.cmake.in KDDockWidgets${KDDockWidgets_LIBRARY_QTID}Config.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets${KDDockWidgets_LIBRARY_QTID}Config.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets${KDDockWidgets_LIBRARY_QTID}ConfigVersion.cmake"
        DESTINATION ${INSTALL_LIBRARY_DIR}/cmake/KDDockWidgets${KDDockWidgets_LIBRARY_QTID}
)

if(KDDockWidgets_DEVELOPER_MODE)
  # Under developer mode since kddw might be a sub-folder of a project setting a different value for QT_DISABLE_DEPRECATED_BEFORE
  target_compile_definitions(kddockwidgets PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)

  option(KDDockWidgets_LINTER "Build the layout linter" ON)

  if(KDDockWidgets_LINTER)

    set(LINTER_SRCS layoutlinter_main.cpp)
    if (KDDW_FRONTEND_QTQUICK)
      # QtQuick needs main.qml to create views
      set(LINTER_SRCS ${LINTER_SRCS} ../tests/test_resources.qrc)
    endif()

    add_executable(kddockwidgets_linter ${LINTER_SRCS})
    target_link_libraries(kddockwidgets_linter kddockwidgets)
  endif()

endif()
