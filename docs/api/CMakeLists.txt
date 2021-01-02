#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Allen Winter <allen.winter@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

find_file(QDOC_QTCORE_TAG qtcore.tags
  HINTS ${QT_INSTALL_DOCS}/qtcore
  HINTS ${QT_INSTALL_DATA}/doc/qtcore
)
if(QDOC_QTCORE_TAG)
  get_filename_component(QDOC_TAG_DIR ${QDOC_QTCORE_TAG} DIRECTORY)
  get_filename_component(QDOC_TAG_DIR ${QDOC_TAG_DIR} DIRECTORY)
endif()

file(GLOB _dox_deps *.dox *.html)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

#apidox generation using doxygen
configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
)

add_custom_command(
  OUTPUT ${DOXYGEN_OUTPUT_DIR}/qch/kddockwidgets-api.qch
  COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  #handle a bug in doxygen where image files referred to in markdown are not copied the output
  COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_SOURCE_DIR}/../../screencap.gif ${DOXYGEN_OUTPUT_DIR}/html
  DEPENDS ${_dox_deps} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_custom_target(kddockwidgets-api.qch ALL DEPENDS ${DOXYGEN_OUTPUT_DIR}/qch/kddockwidgets-api.qch)

install(FILES ${DOXYGEN_OUTPUT_DIR}/qch/kddockwidgets-api.qch DESTINATION ${INSTALL_DOC_DIR})
