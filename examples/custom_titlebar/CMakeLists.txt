project(custom_titlebar)

set(CUSTOMTITLEBAR_SRC main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/src/)

add_executable(custom_titlebar ${CUSTOMTITLEBAR_SRC})
target_link_libraries(custom_titlebar docks Qt5::Widgets)
install(TARGETS custom_titlebar DESTINATION bin)

