find_package(Qt5Test)


add_executable(tst_multisplitter tst_multisplitter.cpp)
target_link_libraries(tst_multisplitter kddockwidgets_layouting Qt5::Test)
