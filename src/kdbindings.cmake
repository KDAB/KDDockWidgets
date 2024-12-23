# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sergio Martins <sergio.martins@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

set(KDDW_3DPARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/3rdparty")

# links a target to KDBindings
function(kddw_link_to_kdbindings target)
    if(TARGET KDAB::KDBindings)
        target_link_libraries(${target} PRIVATE KDAB::KDBindings)
    else()
        target_include_directories(${target} SYSTEM PRIVATE ${KDDW_3DPARTY_DIR})
    endif()
endfunction()
