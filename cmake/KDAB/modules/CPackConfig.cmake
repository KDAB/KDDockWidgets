#
# SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Daniel Nicoletti <daniel.nicoletti@kdab.com>
#
# SPDX-License-Identifier: BSD-3-Clause
#

set(CPACK_PACKAGE_VENDOR "Klarälvdalens Datakonsult AB")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "KDAB's Dock Widget Framework for Qt.")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
set(CPACK_PACKAGE_CONTACT "KDAB Group company <info@kdab.com>")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}${PROJECT_VERSION_MAJOR}-qt${QT_VERSION_MAJOR}")

if(UNIX)
    if(NOT CPACK_GENERATOR)
        set(CPACK_GENERATOR "DEB")
    endif()

    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(CPACK_DEBIAN_DEBUGINFO_PACKAGE ON)
    endif()
endif()

include(CPack)
