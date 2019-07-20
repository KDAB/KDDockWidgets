project(docks_example)

set(EXAMPLE_SRCS
    main.cpp
    ExampleDockableWidget.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(docks_example ${EXAMPLE_SRCS})
target_link_libraries(docks_example docks Qt5::Widgets)
install(TARGETS docks_example DESTINATION bin)

