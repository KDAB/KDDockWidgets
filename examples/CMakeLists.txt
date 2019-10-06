include_directories(${CMAKE_SOURCE_DIR}/src/)

if (OPTION_QTQUICK)
    add_subdirectory(basic_quick)
else()
    add_subdirectory(basic_external)
    add_subdirectory(custom_titlebar)
endif()
