# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

add_subdirectory(dockwidgets)
set_compiler_flags(qtquick_dockwidgets)
set_target_properties(qtquick_dockwidgets PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/" )

add_subdirectory(mdi)
set_compiler_flags(qtquick_mdi)
set_target_properties(qtquick_mdi PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/" )

add_subdirectory(customtitlebar)
set_compiler_flags(qtquick_customtitlebar)
set_target_properties(qtquick_customtitlebar PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/" )
