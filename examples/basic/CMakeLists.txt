project(docks_example)

set(EXAMPLE_SRCS
    main.cpp
    ExampleDockableWidget.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(docks_example ${EXAMPLE_SRCS})
qt5_use_modules(docks_example Widgets)
target_link_libraries(docks_example docks)
install(TARGETS docks_example DESTINATION bin)

