
cmake_policy(SET CMP0043 NEW)

add_definitions(-DQT_NO_CAST_TO_ASCII
                -DQT_NO_CAST_FROM_ASCII
                -DQT_NO_URL_CAST_FROM_STRING
                -DQT_NO_CAST_FROM_BYTEARRAY
                -DQT_NO_SIGNALS_SLOTS_KEYWORDS
                -DQT_USE_QSTRINGBUILDER
                -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
                -DQT_STRICT_ITERATORS
                -DQT_NO_KEYWORDS
                -DQT_DISABLE_DEPRECATED_BEFORE=0x060000
                -DQT_NO_FOREACH
               )

set(DOCKSLIBS_SRCS
    Config.cpp
    Config.h
    DockWidget.cpp
    DragController.cpp
    Draggable.cpp
    DropArea.cpp
    DropAreaWithCentralFrame_p.h
    DockRegistry.cpp
    DropIndicatorOverlayInterface.cpp
    FloatingWindow.cpp
    Frame.cpp
    LastPosition.cpp
    LastPosition_p.h
    LayoutSaver.cpp
    Logging.cpp
    MainWindow.cpp
    TabWidget.cpp
    TitleBar.cpp
    ObjectViewer.cpp
    ObjectViewer_p.h
    DebugWindow.cpp
    DebugWindow_p.h
    WindowBeingDragged.cpp
    WidgetResizeHandler.cpp
    multisplitter/Anchor.cpp
    multisplitter/AnchorGroup.cpp
    multisplitter/Item.cpp
    multisplitter/MultiSplitterLayout.cpp
    multisplitter/MultiSplitterLayout_p.h
    multisplitter/MultiSplitterWidget.cpp
    multisplitter/MultiSplitterWidget_p.h
    multisplitter/SeparatorWidget.cpp
    multisplitter/SeparatorWidget_p.h
    # indicators/AnimatedIndicators.cpp
    indicators/ClassicIndicators.cpp

    widgets/TitleBarWidget.cpp
    )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(IS_CLANG_BUILD TRUE)
else()
    set(IS_CLANG_BUILD FALSE)
endif()

set (DOCKS_INSTALLABLE_INCLUDES docks_export.h DockWidget.h MainWindow.h LayoutSaver.h Draggable_p.h KDDockWidgets.h Config.h)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(docks SHARED ${DOCKSLIBS_SRCS} ${DOCKS_INSTALLABLE_INCLUDES} ${RESOURCES})
target_compile_definitions(docks PRIVATE BUILDING_DOCKS_LIBRARY)
if (CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD)
    target_compile_options(docks PRIVATE -Wshadow -Wconversion -fvisibility=hidden)

    if (IS_CLANG_BUILD)
        target_compile_options(docks PRIVATE -Wweak-vtables)
    endif()
endif()

target_link_libraries(docks Qt5::Widgets)
if (NOT WIN32 AND NOT APPLE)
    find_package(Qt5X11Extras)
    target_link_libraries(docks Qt5::X11Extras)
endif()

install (TARGETS docks
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
install (FILES ${DOCKS_INSTALLABLE_INCLUDES} DESTINATION include/kddockwidgets)
