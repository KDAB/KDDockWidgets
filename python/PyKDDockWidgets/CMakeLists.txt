# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

# Auto-Genereate files every class will have his cpp/h files
set(PyKDDockWidgets_SRC
    # individual classes
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_config_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_config_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_core_dockwidgetviewinterface_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_core_dockwidgetviewinterface_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_core_mainwindowviewinterface_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_core_mainwindowviewinterface_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_initialoption_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_initialoption_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_layoutsaver_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_layoutsaver_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_qtwidgets_dockwidget_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_qtwidgets_dockwidget_wrapper.h
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_qtwidgets_mainwindow_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_qtwidgets_mainwindow_wrapper.h
    # global module wrapper
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_module_wrapper.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KDDockWidgets/kddockwidgets_python.h
)

# includes necessary to parse and build the classes specified on typesystem
set(PyKDDockWidgets_include_paths
    $<JOIN:$<TARGET_PROPERTY:KDAB::kddockwidgets,INTERFACE_INCLUDE_DIRECTORIES>,${PATH_SEP}>
)

# A list of paths where shiboken should look for typesystem
set(PyKDDockWidgets_typesystem_paths # PySide path, this variable was exposed by
                                     # FindPySide2.cmake
    ${PYSIDE_TYPESYSTEMS}
)
# Include flags/path that will be set in 'target_include_directories'
set(PyKDDockWidgets_target_include_directories ${CMAKE_SOURCE_DIR}/src)

# Libraries that will be necessary to link the target, this will used in the
# command 'target_link_libraries'
set(PyKDDockWidgets_target_link_libraries KDAB::kddockwidgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui
                                          Qt${QT_VERSION_MAJOR}::Widgets ${Python3_LIBRARIES}
)

# changes on these files should trigger a new generation
set(PyKDDockWidgets_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/kddockwidgets_global.h ${CMAKE_SOURCE_DIR}/src/qtwidgets/views/MainWindow.h
    ${CMAKE_SOURCE_DIR}/src/qtwidgets/views/DockWidget.h ${CMAKE_SOURCE_DIR}/src/Config.h
    ${CMAKE_SOURCE_DIR}/src/LayoutSaver.h
)

create_python_bindings(
    "KDDockWidgets"
    "${PyKDDockWidgets_typesystem_paths}"
    "${PyKDDockWidgets_include_paths}"
    "${PyKDDockWidgets_SRC}"
    "${PyKDDockWidgets_target_include_directories}"
    "${PyKDDockWidgets_target_link_libraries}"
    ${CMAKE_CURRENT_SOURCE_DIR}/kddockwidgets_global.h
    ${CMAKE_CURRENT_SOURCE_DIR}/typesystem_kddockwidgets.xml
    "${PyKDDockWidgets_DEPENDS}"
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Make module import from build dir work
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/__init__.py.cmake ${CMAKE_CURRENT_BINARY_DIR}/__init__.py @ONLY)

# install
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/__init__.py $<TARGET_FILE:KDAB::kddockwidgets>
        DESTINATION ${${PROJECT_NAME}_PYTHON_BINDINGS_INSTALL_PREFIX}
)
if(NOT WIN32)
    install(FILES $<TARGET_LINKER_FILE:KDAB::kddockwidgets> $<TARGET_SONAME_FILE:KDAB::kddockwidgets>
            DESTINATION ${${PROJECT_NAME}_PYTHON_BINDINGS_INSTALL_PREFIX}
    )
endif()
