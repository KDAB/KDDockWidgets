# SPDX-FileCopyrightText: 2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Sean Harmer <sean.harmer@kdab.com>
#
# SPDX-License-Identifier: MIT
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

set(HEADERS
    binding.h
    binding_evaluator.h
    genindex_array.h
    make_node.h
    node.h
    node_functions.h
    node_operators.h
    property.h
    property_updater.h
    signal.h
    connection_evaluator.h
    connection_handle.h
    utils.h
    KDBindingsConfig.h
)

if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.19.0")
  # Since CMake 3.19 we can add SOURCES here (cf. https://gitlab.kitware.com/cmake/cmake/-/merge_requests/5078)
  add_library(KDBindings INTERFACE ${HEADERS})
else()
  add_library(KDBindings INTERFACE)
endif()
add_library(KDAB::KDBindings ALIAS KDBindings)

set_target_properties(KDBindings PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17)

if(KDBindings_ENABLE_WARN_UNUSED)
  target_compile_definitions(KDBindings INTERFACE KDBINDINGS_ENABLE_WARN_UNUSED=1)
endif()
if(KDBindings_QT_NO_EMIT)
  target_compile_definitions(KDBindings INTERFACE QT_NO_EMIT)
endif()

target_include_directories(
  KDBindings INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..> $<INSTALL_INTERFACE:include>
)
if(KDBindings_ERROR_ON_WARNING)
  if(MSVC)
    target_compile_options(KDBindings INTERFACE /W3 /WX)
  else()
    target_compile_options(KDBindings INTERFACE -Wall -Wextra -Wpedantic -Werror)
  endif()
endif()

# Generate library version files
include(ECMSetupVersion)
ecm_setup_version(
  ${PROJECT_VERSION}
  VARIABLE_PREFIX
  KDBINDINGS
  VERSION_HEADER
  "${CMAKE_BINARY_DIR}/kdbindings_version.h"
  PACKAGE_VERSION_FILE
  "${PROJECT_BINARY_DIR}/KDBindingsConfigVersion.cmake"
  COMPATIBILITY
  AnyNewerVersion
)
install(FILES "${CMAKE_BINARY_DIR}/kdbindings_version.h" DESTINATION ${INSTALL_INCLUDE_DIR}/kdbindings)
install(FILES ${HEADERS} DESTINATION ${INSTALL_INCLUDE_DIR}/kdbindings)

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/KDBindingsConfig.cmake.in" "${PROJECT_BINARY_DIR}/KDBindingsConfig.cmake"
  INSTALL_DESTINATION "${INSTALL_LIBRARY_DIR}/cmake/KDBindings"
  PATH_VARS INSTALL_INCLUDE_DIR
)

install(FILES "${PROJECT_BINARY_DIR}/KDBindingsConfig.cmake" "${PROJECT_BINARY_DIR}/KDBindingsConfigVersion.cmake"
        DESTINATION "${INSTALL_LIBRARY_DIR}/cmake/KDBindings"
)

export(
  TARGETS KDBindings
  NAMESPACE KDAB::
  FILE "${PROJECT_BINARY_DIR}/KDBindingsTargets.cmake"
)

install(
  TARGETS KDBindings
  EXPORT KDBindingsTargets
  LIBRARY DESTINATION ${INSTALL_LIBRARY_DIR}
  ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}
  RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
)

install(
  EXPORT KDBindingsTargets
  DESTINATION ${INSTALL_LIBRARY_DIR}/cmake/KDBindings
  NAMESPACE KDAB::
  FILE KDBindingsTargets.cmake
)
