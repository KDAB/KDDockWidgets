#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# Adds a qtquick example target
function(kddw_add_qtquick_example name)
    add_subdirectory(${name})
    set_target_properties(
        qtquick_${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/examples/"
    )
endfunction()

kddw_add_qtquick_example(dockwidgets)
kddw_add_qtquick_example(mdi)
kddw_add_qtquick_example(customtitlebar)
kddw_add_qtquick_example(customtabbar)
kddw_add_qtquick_example(customseparator)
kddw_add_qtquick_example(mdi_with_docking)
