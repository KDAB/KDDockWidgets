include_directories(${CMAKE_SOURCE_DIR}/src/)

if (OPTION_QTQUICK)
    add_subdirectory(dockwidgets_quick)
else()
    add_subdirectory(dockwidgets)
    add_subdirectory(custom_titlebar)
endif()
