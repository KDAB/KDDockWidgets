
cmake_policy(SET CMP0043 NEW)

add_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS
                -DQT_USE_QSTRINGBUILDER
                -DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT
                -DQT_STRICT_ITERATORS
                -DQT_NO_KEYWORDS
                -DQT_DISABLE_DEPRECATED_BEFORE=0x060000
                -DQT_NO_FOREACH
               )

set(DOCKSLIBS_SRCS
    Config.cpp
    FrameworkWidgetFactory.cpp
    DockWidgetBase.cpp
    MainWindow.cpp
    MainWindowBase.cpp
    LayoutSaver.cpp
    private/LastPosition.cpp
    private/ObjectViewer.cpp
    private/DropIndicatorOverlayInterface.cpp
    private/indicators/ClassicIndicators.cpp
    # private/indicators/AnimatedIndicators.cpp
    private/DropArea.cpp
    private/multisplitter/MultiSplitter.cpp
    private/multisplitter/MultiSplitterLayout.cpp
    private/TabWidget.cpp
    private/FloatingWindow.cpp
    private/Logging.cpp
    private/TitleBar.cpp
    private/DebugWindow.cpp
    private/DockRegistry.cpp
    private/Draggable.cpp
    private/WindowBeingDragged.cpp
    private/DragController.cpp
    private/Frame.cpp
    private/DropAreaWithCentralFrame.cpp
    private/WidgetResizeHandler.cpp
    )

set(DOCKS_INSTALLABLE_INCLUDES
    docks_export.h
    Config.h
    FrameworkWidgetFactory.h
    DockWidgetBase.h
    KDDockWidgets.h
    QWidgetAdapter.h
    LayoutSaver.h
    LayoutSaver_p.h
    )


set(DOCKS_INSTALLABLE_PRIVATE_INCLUDES
    private/Draggable_p.h
    private/DropIndicatorOverlayInterface_p.h
    private/FloatingWindow_p.h
    private/Frame_p.h
    private/TabWidget_p.h
    private/TitleBar_p.h
    )

set(DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES
    private/widgets/QWidgetAdapter_widgets_p.h
    private/widgets/TitleBarWidget_p.h
    private/widgets/SeparatorWidget_p.h
    private/widgets/FloatingWindowWidget_p.h
    private/widgets/FrameWidget_p.h
    private/widgets/TabBarWidget_p.h
    private/widgets/TabWidgetWidget_p.h
)

if (OPTION_QTQUICK)
    set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS}
        private/quick/DockWidgetQuick.cpp
        private/quick/QWidgetAdapter_quick.cpp
        private/quick/FloatingWindowQuick.cpp
        private/quick/TitleBarQuick.cpp
        private/quick/QmlTypes.cpp
        private/quick/TabWidgetQuick.cpp
        private/quick/FrameQuick.cpp
        private/quick/MainWindowQuick.cpp
        private/quick/TabBarQuick.cpp
        private/quick/SeparatorQuick.cpp
        private/quick/LayoutSaverQuick.cpp)

    qt5_add_resources(RESOURCES_QUICK ${CMAKE_CURRENT_SOURCE_DIR}/qtquick.qrc)

else()
    set(DOCKSLIBS_SRCS ${DOCKSLIBS_SRCS}
        private/widgets/SeparatorWidget.cpp
        private/widgets/TabBarWidget.cpp
        private/widgets/FloatingWindowWidget.cpp
        private/widgets/FrameWidget.cpp
        private/widgets/TabWidgetWidget.cpp
        private/widgets/TitleBarWidget.cpp
        private/widgets/DockWidget.cpp
        private/widgets/QWidgetAdapter_widgets.cpp
        )

    set(DOCKS_INSTALLABLE_INCLUDES
        ${DOCKS_INSTALLABLE_INCLUDES}
        MainWindow.h
        MainWindowBase.h
        DockWidget.h)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(IS_CLANG_BUILD TRUE)
else()
    set(IS_CLANG_BUILD FALSE)
endif()


add_subdirectory(private/multisplitter)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

add_library(kddockwidgets SHARED ${DOCKSLIBS_SRCS} ${DOCKS_INSTALLABLE_INCLUDES} ${RESOURCES} ${RESOURCES_QUICK})
add_library(KDAB::kddockwidgets ALIAS kddockwidgets)

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

target_compile_definitions(kddockwidgets PRIVATE BUILDING_DOCKS_LIBRARY
                                                 QT_NO_CAST_TO_ASCII
                                                 QT_NO_CAST_FROM_ASCII
                                                 QT_NO_URL_CAST_FROM_STRING
                                                 QT_NO_CAST_FROM_BYTEARRAY
)

if (CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD)
    target_compile_options(kddockwidgets PRIVATE -Wshadow -Wconversion -fvisibility=hidden)

    if (IS_CLANG_BUILD)
        target_compile_options(kddockwidgets PRIVATE -Wweak-vtables)
    endif()
endif()

if (OPTION_QTQUICK)
    target_link_libraries(kddockwidgets Qt5::Widgets Qt5::Quick)
else()
    target_link_libraries(kddockwidgets PUBLIC Qt5::Widgets PRIVATE kddockwidgets_layouting)
endif()


if (NOT WIN32 AND NOT APPLE)
    find_package(Qt5X11Extras)
    target_link_libraries(kddockwidgets PUBLIC Qt5::X11Extras)
endif()

install (TARGETS kddockwidgets
         EXPORT kddockwidgetsTargets
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
install (FILES ${DOCKS_INSTALLABLE_INCLUDES} DESTINATION include/kddockwidgets)
install (FILES ${DOCKS_INSTALLABLE_PRIVATE_INCLUDES} DESTINATION include/kddockwidgets/private)
install (FILES private/multisplitter/Item_p.h DESTINATION include/kddockwidgets/multisplitter)
install (FILES ${DOCKS_INSTALLABLE_PRIVATE_WIDGET_INCLUDES} DESTINATION include/kddockwidgets/private/widgets)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    KDDockWidgetsConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY AnyNewerVersion
    )

install(EXPORT kddockwidgetsTargets
        FILE KDDockWidgetsTargets.cmake
        NAMESPACE KDAB::
        DESTINATION lib/cmake/KDDockWidgets
)
configure_file(KDDockWidgetsConfig.cmake.in KDDockWidgetsConfig.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgetsConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgetsConfigVersion.cmake"
        DESTINATION lib/cmake/KDDockWidgets
)
