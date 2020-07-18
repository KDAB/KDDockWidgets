if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(TESTING_SRCS utils.cpp Testing.cpp)

include_directories(..)
include_directories(../src)
include_directories(../src/private)
qt5_add_resources(TESTING_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test_resources.qrc)
add_executable(tst_docks tst_docks.cpp ${TESTING_SRCS} ${TESTING_RESOURCES})
add_executable(tests_launcher tests_launcher.cpp)
target_link_libraries(tst_docks kddockwidgets kddockwidgets_multisplitter KDAB::QtWidgets KDAB::QtTest)
target_link_libraries(tests_launcher KDAB::QtCore)

set_compiler_flags(tst_docks)

add_subdirectory(fuzzer)

