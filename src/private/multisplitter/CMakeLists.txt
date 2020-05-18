set(MULTISPLITTER_SRCS
    Item.cpp
    Item_p.h
    Logging.cpp
    Logging_p.h
    Separator.cpp
    Separator_p.h
)

add_library(kddockwidgets_layouting STATIC ${MULTISPLITTER_SRCS})
target_link_libraries(kddockwidgets_layouting Qt5::Core Qt5::Widgets)

if (OPTION_DEVELOPER_MODE)
    add_subdirectory(tests)
endif()

target_include_directories(kddockwidgets_layouting
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
