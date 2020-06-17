
add_executable(fuzzer
               main.cpp
               Fuzzer.cpp
               Operations.cpp
               ../Testing.cpp)

set_property(TARGET fuzzer PROPERTY CXX_STANDARD 17)
target_link_libraries(fuzzer kddockwidgets Qt5::Widgets Qt5::Test)
set_compiler_flags(fuzzer)
