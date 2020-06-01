find_package(Qt5Quick)

set(SRCS main.cpp controller.cpp multisplitter.cpp)

qt5_add_resources(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)
add_executable(kdmultisplitter_example_quick ${SRCS} ${RESOURCES})
target_link_libraries(kdmultisplitter_example_quick kddockwidgets kddockwidgets_multisplitter Qt5::Quick) # Linking to kddockwidgets just so we get the indicators png
