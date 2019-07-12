
cmake_policy(SET CMP0043 NEW)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_executable(tst_docks tst_docks.cpp)
qt5_use_modules(tst_docks Widgets Test)
target_link_libraries(tst_docks docks)

##### Fuzzer
add_executable(fuzzer fuzzer.cpp)
qt5_use_modules(fuzzer Widgets)
target_link_libraries(fuzzer docks)

