cmake_minimum_required(VERSION 3.16)
project(
    kddwtest
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

if(NOT TARGET kddockwidgets)
    # Allow this folder to also be built standalone, against an installed KDDockWidgets.
    qt_standard_project_setup(REQUIRES 6.5)
    find_package(KDDockWidgets-qt6 REQUIRED)
endif()

qt_policy(SET QTP0001 NEW)

qt_add_executable(appkddwtest main.cpp)

qt_add_qml_module(
    appkddwtest
    URI
    kddwtest
    QML_FILES
    Main.qml
    MdiRepro.qml
    FloatingCloseRepro.qml
    MaximizeButtonRepro.qml
    InitialSizeRepro.qml
    TitleBarMouseLeakRepro.qml
    TitleBarThemeRepro.qml
)

target_link_libraries(appkddwtest PRIVATE Qt6::Quick Qt6::QuickControls2 KDAB::kddockwidgets)
