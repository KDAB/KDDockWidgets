cmake_policy(SET CMP0043 NEW)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
find_package(Qt5Test)

set(TESTING_SRCS utils.cpp Operations.cpp Testing.cpp)

add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS})
target_link_libraries(tst_docks kddockwidgets Qt5::Widgets Qt5::Test)

##### Fuzzer
add_executable(fuzzer fuzzer.cpp ${TESTING_SRCS})
target_link_libraries(fuzzer kddockwidgets Qt5::Widgets Qt5::Test)
