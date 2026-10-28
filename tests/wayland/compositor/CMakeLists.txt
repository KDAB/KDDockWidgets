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

target_link_libraries(kddw_test_compositor PRIVATE Qt6::Gui Qt6::Qml Qt6::Quick Qt6::Test Qt6::WaylandCompositor)

set_compiler_flags(kddw_test_compositor)
