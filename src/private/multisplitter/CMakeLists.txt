set(MULTISPLITTER_SRCS
    Item.cpp
    Item_p.h
    Logging.cpp
    Logging_p.h
    MultiSplitterConfig.cpp
    MultiSplitterConfig.h
    Separator.cpp
    Separator_p.h
    Widget.cpp
    Widget.h
    multisplitter_export.h
)

set(MULTISPLITTER_SRCS_QTWIDGETS
    Widget_qwidget.cpp
    Widget_qwidget.h
    Separator_qwidget.cpp
    Separator_qwidget.h
)

set(MULTISPLITTER_SRCS_QTQUICK
    Widget_quick.cpp
    Widget_quick.h
    Separator_quick.cpp
    Separator_quick.h
)

option(BUILD_MULTISPLITTER_QTWIDGETS_FRONTEND "Build support for QtWidgets" ON)
option(BUILD_MULTISPLITTER_QTQUICK_FRONTEND "Build support for QtQuick" OFF)


if (BUILD_MULTISPLITTER_QTWIDGETS_FRONTEND)
    set(MULTISPLITTER_SRCS ${MULTISPLITTER_SRCS} ${MULTISPLITTER_SRCS_QTWIDGETS})
    add_definitions(-DKDMULTISPLITTER_QTWIDGETS)
endif()

if (BUILD_MULTISPLITTER_QTQUICK_FRONTEND)
    set(MULTISPLITTER_SRCS ${MULTISPLITTER_SRCS} ${MULTISPLITTER_SRCS_QTQUICK})
    add_definitions(-DKDMULTISPLITTER_QTQUICK)
endif()

qt5_add_resources(MULTISPLITTER_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/multisplitter.qrc)

add_library(kddockwidgets_multisplitter SHARED ${MULTISPLITTER_SRCS} ${MULTISPLITTER_RESOURCES})
add_library(KDAB::kddockwidgets_multisplitter ALIAS kddockwidgets_multisplitter)
target_link_libraries(kddockwidgets_multisplitter Qt5::Core Qt5::Widgets)
set_compiler_flags(kddockwidgets_multisplitter)

if (BUILD_MULTISPLITTER_QTWIDGETS_FRONTEND)
    find_package(Qt5Widgets)
    target_link_libraries(kddockwidgets_multisplitter Qt5::Core Qt5::Widgets)
endif()

if (BUILD_MULTISPLITTER_QTQUICK_FRONTEND)
    find_package(Qt5Quick)
    target_link_libraries(kddockwidgets_multisplitter Qt5::Core Qt5::Quick)
endif()

target_compile_definitions(kddockwidgets_multisplitter PRIVATE BUILDING_MULTISPLITTER_LIBRARY)

if (OPTION_DEVELOPER_MODE)
    # Under developer mode since kddw might be a sub-folder of a project setting a different value for QT_DISABLE_DEPRECATED_BEFORE
    target_compile_definitions(kddockwidgets_multisplitter PRIVATE QT_DISABLE_DEPRECATED_BEFORE=0x060000)

    add_subdirectory(tests)
    add_subdirectory(examples)
endif()

target_include_directories(kddockwidgets_multisplitter
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# append d to debug libraries for windows builds
if(WIN32)
    set(postfix ${${PROJECT_NAME}_VERSION_MAJOR})
    string(TOUPPER ${CMAKE_BUILD_TYPE} UPPER_BUILD_TYPE)
    if(${UPPER_BUILD_TYPE} MATCHES "^DEBUG")
        string(CONCAT postfix ${postfix} "d")
        set_target_properties(kddockwidgets_multisplitter PROPERTIES DEBUG_POSTFIX ${postfix})
    else()
        set_target_properties(kddockwidgets_multisplitter PROPERTIES ${UPPER_BUILD_TYPE}_POSTFIX ${postfix})
    endif()
endif()

install (TARGETS kddockwidgets_multisplitter
         EXPORT kddockwidgetsTargets
         RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
         LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
         ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}
         )
if(MSVC)
    install(FILES "$<TARGET_PDB_FILE_DIR:kddockwidgets_multisplitter>/$<TARGET_PDB_FILE_NAME:kddockwidgets_multisplitter>" DESTINATION ${INSTALL_LIBRARY_DIR} CONFIGURATIONS Debug RelWithDebInfo)
endif()
