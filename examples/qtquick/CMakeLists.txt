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

add_subdirectory(mdi)
set_compiler_flags(qtquick_mdi)

add_subdirectory(customtitlebar)
set_compiler_flags(qtquick_customtitlebar)
