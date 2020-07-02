find_package(Qt5Test)

add_executable(tst_multisplitter tst_multisplitter.cpp)
target_link_libraries(tst_multisplitter kddockwidgets_multisplitter Qt5::Test)
set_compiler_flags(tst_multisplitter)

if(${PROJECT_NAME}_STATIC)
  target_compile_definitions(tst_multisplitter PRIVATE MULTISPLITTER_STATICLIB KDDOCKWIDGETS_STATICLIB)
else()
  target_compile_definitions(tst_multisplitter PRIVATE BUILDING_MULTISPLITTER_LIBRARY BUILDING_DOCKS_LIBRARY)
endif()
