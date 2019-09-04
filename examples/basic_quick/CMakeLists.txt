cmake_minimum_required(VERSION 3.12)


project(kddockwidgets_basic_quick)

find_package(Qt5Quick)

set(EXAMPLE_SRCS
    main.cpp
    )

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(kddockwidgets_basic_quick ${EXAMPLE_SRCS} ${RESOURCES})
target_link_libraries(kddockwidgets_basic_quick kddockwidgets Qt5::Quick)
install(TARGETS kddockwidgets_basic_quick DESTINATION bin)
