cmake_minimum_required(VERSION 3.3)

project(kddockwidgets_example)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIRS ON)

# This will look for Qt, do find_package yourself manually before 
# if you want to look for a specific version for instance.
find_package(KDDockWidgets REQUIRED)

qt5_add_resources(RESOURCES_SRC ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

add_executable(kddockwidgets_example
    main.cpp
    MyFrameworkWidgetFactory.cpp
    MyMainWindow.cpp
    MyWidget.cpp
    ${RESOURCES_SRC}
)

target_link_libraries(kddockwidgets_example
    PRIVATE 
        KDAB::kddockwidgets
)

