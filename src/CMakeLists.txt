
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
    DockWidgetBase.cpp
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
    Logging.cpp
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
    multisplitter/MultiSplitter.cpp
    multisplitter/MultiSplitter_p.h
    multisplitter/Separator.cpp
    FrameworkWidgetFactory.cpp
    )

set(DOCKS_INSTALLABLE_INCLUDES
    docks_export.h
    Config.h
    FrameworkWidgetFactory.h
    DockWidgetBase.h
    Draggable_p.h
    KDDockWidgets.h
    QWidgetAdapter.h
    LayoutSaver.h
    )

set(DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES
    widgets/QWidgetAdapter_widgets_p.h)


if (OPTION_QTQUICK)
    set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS}
        quick/QWidgetAdapter_quick.cpp
        quick/QWidgetAdapter_quick_p.h
        )
else()
    set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS}
        MainWindow.cpp
        LayoutSaver.cpp
        # indicators/AnimatedIndicators.cpp
        indicators/ClassicIndicators.cpp
        widgets/QWidgetAdapter_widgets.cpp
        widgets/QWidgetAdapter_widgets_p.h
        widgets/DockWidget.cpp
        widgets/FloatingWindowWidget.cpp
        widgets/FrameWidget.cpp
        widgets/SeparatorWidget.cpp
        widgets/SeparatorWidget_p.h
        widgets/TabWidgetWidget.cpp
        widgets/TabBarWidget.cpp
        widgets/TitleBarWidget.cpp
        )

    set(DOCKS_INSTALLABLE_INCLUDES
        ${DOCKS_INSTALLABLE_INCLUDES}
        MainWindow.h
        widgets/DockWidget.h)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(IS_CLANG_BUILD TRUE)
else()
    set(IS_CLANG_BUILD FALSE)
endif()

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

add_library(kddockwidgets SHARED ${DOCKSLIBS_SRCS} ${DOCKS_INSTALLABLE_INCLUDES} ${RESOURCES})

target_include_directories(kddockwidgets
    PUBLIC
        $<INSTALL_INTERFACE:kddockwidgets>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/widgets>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/quick>
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/widgets
        ${CMAKE_SOURCE_DIR}/src/quick
)

target_compile_definitions(kddockwidgets PRIVATE BUILDING_DOCKS_LIBRARY)
if (CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD)
    target_compile_options(kddockwidgets PRIVATE -Wshadow -Wconversion -fvisibility=hidden)

    if (IS_CLANG_BUILD)
        target_compile_options(kddockwidgets PRIVATE -Wweak-vtables)
    endif()
endif()

if (OPTION_QTQUICK)
    target_link_libraries(kddockwidgets Qt5::Widgets Qt5::Quick)
else()
    target_link_libraries(kddockwidgets Qt5::Widgets)
endif()


if (NOT WIN32 AND NOT APPLE)
    find_package(Qt5X11Extras)
    target_link_libraries(kddockwidgets Qt5::X11Extras)
endif()

install (TARGETS kddockwidgets
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
install (FILES ${DOCKS_INSTALLABLE_INCLUDES} DESTINATION include/kddockwidgets)
install (FILES ${DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES} DESTINATION include/kddockwidgets/widgets)
