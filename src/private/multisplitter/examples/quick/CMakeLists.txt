#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

find_package(Qt5Quick)
set(SRCS main.cpp controller.cpp multisplitter.cpp)

set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)
add_executable(kdmultisplitter_example_quick ${SRCS} ${RESOURCES})
target_link_libraries(kdmultisplitter_example_quick kddockwidgets kddockwidgets_multisplitter Qt5::Quick) # Linking to kddockwidgets just so we get the indicators png
