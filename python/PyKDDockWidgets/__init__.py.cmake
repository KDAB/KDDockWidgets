#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#

import sys
import os

__all__ = ['KDDockWidgets']

def setupLibraryPath():
    package_dir = os.path.abspath(os.path.dirname(__file__))
    if sys.platform != 'win32':
        return

    if sys.version_info[0] == 3 and sys.version_info[1] >= 8:
        os.add_dll_directory(package_dir)
        return

    os.environ['PATH'] = os.fspath(package_dir) + os.pathsep + os.environ['PATH']

# Preload PySide libraries to avoid missing libraries while loading KDDockWidgets
try:
    from PySide@PYSIDE_MAJOR_VERSION@ import QtCore
    # Create a alias for PySide module so we can use a single import in source files
    import PySide@PYSIDE_MAJOR_VERSION@
    sys.modules["PySide"] = PySide@PYSIDE_MAJOR_VERSION@
except Exception:
    print("Failed to load PySide")
    raise

setupLibraryPath()


#
# This file is part of KDDockWidgets.
#
# SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
# Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
#
# SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only
#
# Contact KDAB at <info@kdab.com> for commercial licensing options.
#