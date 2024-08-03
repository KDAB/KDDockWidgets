cmake_minimum_required(VERSION 3.21)
project(slint_minimal LANGUAGES CXX)

include(FetchContent)
fetchcontent_declare(
    Slint
    GIT_REPOSITORY https://github.com/slint-ui/slint.git
    GIT_TAG release/1
    SOURCE_SUBDIR api/cpp
)
fetchcontent_makeavailable(Slint)

add_executable(slint_minimal main.cpp)

slint_target_sources(slint_minimal main_ui.slint)

target_link_libraries(slint_minimal PRIVATE Slint::Slint)

if(WIN32)
    # On Windows, copy the Slint DLL next to the application binary so that it's found.
    add_custom_command(
        TARGET slint_minimal
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:slint_minimal> $<TARGET_FILE_DIR:slint_minimal>
        COMMAND_EXPAND_LISTS
    )
endif()
