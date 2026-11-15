# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

find_package(Qt6 NO_MODULE REQUIRED COMPONENTS Gui Qml Quick Test WaylandCompositor)

add_executable(kddw_test_compositor main.cpp TestExtension.cpp TestExtension.h compositor.qrc)

qt6_generate_wayland_protocol_server_sources(
    kddw_test_compositor PRIVATE_CODE FILES ${CMAKE_CURRENT_SOURCE_DIR}/../protocol/kddw-test-v1.xml
)

# xdg-toplevel-drag, so dragged windows move with the pointer. Ships with Qt and wayland-protocols.
find_file(
    KDDW_XDG_TOPLEVEL_DRAG_XML xdg-toplevel-drag-v1.xml
    HINTS "${QT6_INSTALL_PREFIX}/${QT6_INSTALL_QT_SHAREDIR}/wayland/protocols/xdg-toplevel-drag"
          "${QT6_INSTALL_PREFIX}/share/qt6/wayland/protocols/xdg-toplevel-drag"
    PATH_SUFFIXES wayland-protocols/staging/xdg-toplevel-drag qt6/wayland/protocols/xdg-toplevel-drag
)
if(KDDW_XDG_TOPLEVEL_DRAG_XML)
    target_sources(kddw_test_compositor PRIVATE ToplevelDrag.cpp ToplevelDrag.h)
    qt6_generate_wayland_protocol_server_sources(kddw_test_compositor PRIVATE_CODE FILES ${KDDW_XDG_TOPLEVEL_DRAG_XML})

    # It references xdg_toplevel_interface, which QtWaylandCompositor doesn't export. Only the
    # interface tables are needed, generating the whole xdg-shell server code would clash with Qt's.
    get_filename_component(_protocols_dir "${KDDW_XDG_TOPLEVEL_DRAG_XML}" DIRECTORY)
    find_file(KDDW_XDG_SHELL_XML xdg-shell.xml HINTS "${_protocols_dir}/../xdg-shell"
                                                     "${_protocols_dir}/../../stable/xdg-shell" REQUIRED
    )
    set(_xdg_shell_code "${CMAKE_CURRENT_BINARY_DIR}/xdg-shell-protocol.c")
    add_custom_command(
        OUTPUT "${_xdg_shell_code}"
        COMMAND ${WaylandScanner_EXECUTABLE} private-code "${KDDW_XDG_SHELL_XML}" "${_xdg_shell_code}"
        DEPENDS "${KDDW_XDG_SHELL_XML}"
        COMMENT "Generating xdg-shell-protocol.c"
    )
    target_sources(kddw_test_compositor PRIVATE "${_xdg_shell_code}")
    target_compile_definitions(kddw_test_compositor PRIVATE KDDW_HAS_TOPLEVEL_DRAG)
else()
    message(STATUS "xdg-toplevel-drag-v1.xml not found, kddw_test_compositor won't support xdg-toplevel-drag")
endif()

target_link_libraries(kddw_test_compositor PRIVATE Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Test Qt6::WaylandCompositor)

set_compiler_flags(kddw_test_compositor)
