# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

add_subdirectory(compositor)

find_package(Qt6 NO_MODULE REQUIRED COMPONENTS GuiPrivate Test WaylandClient)

add_executable(
    tst_wayland tst_wayland.cpp WaylandTestUtils.cpp WaylandTestUtils.h ${CMAKE_CURRENT_SOURCE_DIR}/../utils.cpp
                ${TESTING_RESOURCES}
)
if(KDDockWidgets_HAS_SPDLOG)
    target_sources(tst_wayland PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../fatal_logger.cpp)
    target_link_libraries(tst_wayland PRIVATE spdlog::spdlog)
    target_compile_definitions(tst_wayland PRIVATE KDDW_HAS_SPDLOG)
endif()

qt6_generate_wayland_protocol_client_sources(
    tst_wayland PRIVATE_CODE FILES ${CMAKE_CURRENT_SOURCE_DIR}/protocol/kddw-test-v1.xml
)

target_link_libraries(tst_wayland PRIVATE kddockwidgets Qt6::GuiPrivate Qt6::Test Qt6::WaylandClient)
kddw_link_to_kdbindings(tst_wayland)
kddw_add_nlohmann(tst_wayland)
set_compiler_flags(tst_wayland)

add_test(NAME tst_wayland COMMAND kddw_test_compositor -- $<TARGET_FILE:tst_wayland>)

# For the message telling how to run it, when it's not run through the compositor
target_compile_definitions(
    tst_wayland PRIVATE KDDW_BUILD_DIR="${CMAKE_BINARY_DIR}" KDDW_TEST_COMPOSITOR="$<TARGET_FILE:kddw_test_compositor>"
)
set_tests_properties(tst_wayland PROPERTIES LABELS wayland)
