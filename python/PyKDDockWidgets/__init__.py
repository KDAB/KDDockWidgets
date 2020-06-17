__all__ = ['KDDockWidgets']

# Preload PySide2 libraries to avoid missing libraries while loading KDDockWidgets
try:
    from PySide2 import QtCore
except Exception:
    print("Failed to lod PySide")
    raise

# avoid duplicate namespace, due the PYSIDE-1325 bug I will have my package like this
# PyKDDockWidgets.KDDockWidgets.KDDockWidgets.MainWindow
# To avoid this I add a WORKAROUND to reduce it
from .KDDockWidgets import KDDockWidgets as _priv
KDDockWidgets = _priv
