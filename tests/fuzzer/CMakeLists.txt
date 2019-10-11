
add_executable(fuzzer
               main.cpp
               Fuzzer.cpp
               Operations.cpp
               ../Testing.cpp)


target_link_libraries(fuzzer kddockwidgets Qt5::Widgets Qt5::Test)
