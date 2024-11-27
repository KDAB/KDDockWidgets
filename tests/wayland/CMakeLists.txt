# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Joshua Goins <joshua.goins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

find_package(KF${QT_VERSION_MAJOR}Wayland CONFIG)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WaylandClient Concurrent)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

find_package(PlasmaWaylandProtocols)
find_package(QtWaylandScanner)
find_package(Wayland REQUIRED Client)

ecm_add_qtwayland_client_protocol(
    wayland_SRCS PROTOCOL ${PLASMA_WAYLAND_PROTOCOLS_DIR}/fake-input.xml BASENAME fake-input
)

# add wayland test
function(add_wayland_test test srcs)
    add_executable(${test} ${srcs})
    target_link_libraries(
        ${test}
        kddockwidgets
        KDAB::KDBindings
        Wayland::Client
        Qt::WaylandClient
        KF${QT_VERSION_MAJOR}::WaylandClient
        Qt::Concurrent
    )
    if(KDDockWidgets_HAS_SPDLOG)
        target_link_libraries(${test} spdlog::spdlog)
    endif()
    target_sources(${test} PRIVATE ${wayland_SRCS})
    kddw_add_nlohmann(${test})
    set_compiler_flags(${test})

    # FIXME: Use find_program to check if kwin_wayland exists first
    add_test(NAME ${test} COMMAND kwin_wayland --no-kactivities --no-global-shortcuts --no-lockscreen --virtual
                                  --exit-with-session $<TARGET_FILE:${test}>
    )
endfunction()

add_wayland_test(tst_wayland_qtwidgets tst_wayland.cpp)
