
cmake_policy(SET CMP0043 NEW)

set(DOCKSLIBS_SRCS
    DockWidget.cpp
    DragController.cpp
    Draggable.cpp
    DropArea.cpp
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
    WindowBeingDragged.cpp
    WidgetResizeHandler.cpp
    multisplitter/Anchor.cpp
    multisplitter/AnchorGroup.cpp
    multisplitter/MultiSplitter.cpp
    multisplitter/Item.cpp
    multisplitter/LayoutMemory.cpp
    multisplitter/LayoutMemory_p.h
    indicators/AnimatedIndicators.cpp
    indicators/ClassicIndicators.cpp)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(IS_CLANG_BUILD TRUE)
else()
    set(IS_CLANG_BUILD FALSE)
endif()

if (CMAKE_COMPILER_IS_GNUCXX OR IS_CLANG_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wconversion -fvisibility=hidden")

    if (IS_CLANG_BUILD)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wweak-vtables")
    endif()
endif()


set (DOCKS_INSTALLABLE_INCLUDES docks_export.h DockWidget.h MainWindow.h LayoutSaver.h Draggable_p.h KDDockWidgets.h)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_definitions(-DBUILDING_DOCKS_LIBRARY)
add_library(docks SHARED ${DOCKSLIBS_SRCS} ${RESOURCES})

find_package(Qt5X11Extras)

set(NEEDED_QT_MODULES Widgets)
if (Qt5X11Extras_FOUND)
  set(NEEDED_QT_MODULES ${NEEDED_QT_MODULES} X11Extras)
endif()

qt5_use_modules(docks ${NEEDED_QT_MODULES} )

install (TARGETS docks
         RUNTIME DESTINATION bin
         LIBRARY DESTINATION lib
         ARCHIVE DESTINATION lib)
install (FILES ${DOCKS_INSTALLABLE_INCLUDES} DESTINATION include/kddockwidgets)
