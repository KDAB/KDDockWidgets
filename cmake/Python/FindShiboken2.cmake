###
#  This file is part of KDDockWidgets.
#
#  Copyright (C) 2018-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
#  Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
#  This program is free software you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
##

#  SHIBOKEN_INCLUDE_DIR        - Directories to include to use SHIBOKEN
#  SHIBOKEN_LIBRARY            - Files to link against to use SHIBOKEN
#  SHIBOKEN_BINARY             - Executable name
#  SHIBOKEN_BUILD_TYPE         - Tells if Shiboken was compiled in Release or Debug mode.

# You can install Shiboken from Qt repository with
# pip3 install --index-url=http://download.qt.io/snapshots/ci/pyside/<Qt-Version>/latest/ shiboken2-generator --trusted-host download.qt.io
set(SHIBOKEN_FOUND FALSE)

execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "if True:
       import os
       try:
        import shiboken2_generator
        print(shiboken2_generator.__path__[0])
       except:
        exit()
    "
    OUTPUT_VARIABLE SHIBOKEN_GENERATOR_BASEDIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "if True:
       import os
       try:
        import shiboken2
        print(shiboken2.__path__[0])
       except:
        exit()
    "
    OUTPUT_VARIABLE SHIBOKEN_BASEDIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${Python3_EXECUTABLE} -c "if True:
       import os
       import shiboken2
       print(';'.join(filter(None, map(str, shiboken2.__version_info__))))
    "
    OUTPUT_VARIABLE SHIBOKEN_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(GET SHIBOKEN_VERSION 0 SHIBOKEN_MACRO_VERSION)
list(GET SHIBOKEN_VERSION 1 SHIBOKEN_MICRO_VERSION)
list(GET SHIBOKEN_VERSION 2 SHIBOKEN_MINOR_VERSION)
string(REPLACE ";" "." SHIBOKEN_VERSION "${SHIBOKEN_VERSION}")

message(STATUS "ShibokenGenerator base dir: ${SHIBOKEN_GENERATOR_BASEDIR}")
message(STATUS "Shiboken base dir:          ${SHIBOKEN_BASEDIR}")
message(STATUS "Shiboken version:           ${SHIBOKEN_VERSION}")

if(SHIBOKEN_BASEDIR)
    find_path(SHIBOKEN_INCLUDE_DIR
          shiboken.h
          PATHS ${SHIBOKEN_GENERATOR_BASEDIR}/include
          NO_DEFAULT_PATH)
    if(MSVC)
        SET(SHIBOKEN_LIBRARY_BASENAMES "shiboken2.abi3.lib")
    elseif(CYGWIN)
        SET(SHIBOKEN_LIBRARY_BASENAMES "")
    elseif(WIN32)
        SET(SHIBOKEN_LIBRARY_BASENAMES "libshiboken2.${PYSIDE2_SUFFIX}")
    else()
        SET(SHIBOKEN_LIBRARY_BASENAMES
                libshiboken2.abi3.so
                libshiboken2.abi3.so.${SHIBOKEN_MACRO_VERSION}
                libshiboken2.abi3.so.${SHIBOKEN_MACRO_VERSION}.${SHIBOKEN_MICRO_VERSION}
                libshiboken2.abi3.so.${SHIBOKEN_VERSION}
        )
    endif()

    if (NOT SHIBOKEN_INCLUDE_DIR)
        return()
    endif()

    find_file(SHIBOKEN_LIBRARY
        ${SHIBOKEN_LIBRARY_BASENAMES}
        PATHS ${SHIBOKEN_BASEDIR}
        NO_DEFAULT_PATH)

    find_program(SHIBOKEN_BINARY
        shiboken2
        PATHS ${SHIBOKEN_GENERATOR_BASEDIR}
        NO_DEFAULT_PATH
    )

    message(STATUS "Shiboken include dir:       ${SHIBOKEN_INCLUDE_DIR}")
    message(STATUS "Shiboken library:           ${SHIBOKEN_LIBRARY}")
    message(STATUS "Shiboken binary:            ${SHIBOKEN_BINARY}")

    if (SHIBOKEN_INCLUDE_DIR AND SHIBOKEN_LIBRARY AND SHIBOKEN_BINARY)
        set(SHIBOKEN_FOUND TRUE)
    endif()

else()
    set(SHIBOKEN_FOUND FALSE)
endif()

if(MSVC)
    # On Windows we must link to python3.dll that is a small library that links against python3x.dll
    # that allow us to choose any python3x.dll at runtime
    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "if True:
            for lib in '${Python3_LIBRARIES}'.split(';'):
                if '/' in lib:
                    prefix, py = lib.rsplit('/', 1)
                    if py.startswith('python3'):
                        print(prefix + '/python3.lib')
                        break
            "
        OUTPUT_VARIABLE PYTHON_LIMITED_LIBRARIES
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
     # On Linux and MacOs our modules should not link with any python library
     # that must be handled by the main process
    set(PYTHON_LIMITED_LIBRARIES "")
endif()

if (SHIBOKEN_FOUND)
    # Create shiboke2 target
    add_library(Shiboken2::libshiboken SHARED IMPORTED GLOBAL)
    if(MSVC)
        set_property(TARGET Shiboken2::libshiboken PROPERTY
            IMPORTED_IMPLIB ${SHIBOKEN_LIBRARY})
    endif()
    set_property(TARGET Shiboken2::libshiboken PROPERTY
        IMPORTED_LOCATION ${SHIBOKEN_LIBRARY})
    set_property(TARGET Shiboken2::libshiboken APPEND PROPERTY
        INTERFACE_INCLUDE_DIRECTORIES ${SHIBOKEN_INCLUDE_DIR} ${Python3_INCLUDE_DIRS})
    set_property(TARGET Shiboken2::libshiboken APPEND PROPERTY
        INTERFACE_LINK_LIBRARIES ${PYTHON_LIMITED_LIBRARIES})
endif()

find_package_handle_standard_args(Shiboken2
    REQUIRED_VARS SHIBOKEN_BASEDIR SHIBOKEN_INCLUDE_DIR SHIBOKEN_LIBRARY SHIBOKEN_BINARY
    VERSION_VAR SHIBOKEN_VERSION
)
