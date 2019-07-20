cmake_policy(SET CMP0043 NEW)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
find_package(Qt5Test)

add_executable(tst_docks tst_docks.cpp utils.cpp)
target_link_libraries(tst_docks docks Qt5::Widgets Qt5::Test)

##### Fuzzer
add_executable(fuzzer fuzzer.cpp utils.cpp)
target_link_libraries(fuzzer docks Qt5::Widgets Qt5::Test)

