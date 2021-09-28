import unittest
import importlib
import inspect

from config import TstConfig

class TestImportModules(unittest.TestCase):
    def test_importModules(self):
        m = importlib.import_module(TstConfig.bindingsNamespace + '.KDDockWidgets')
        moduleSymbols = []
        for t in inspect.getmembers(m):
            moduleSymbols.append(t[0])

        symbols = ['MainWindow', 'DockWidget']
        for symbol in symbols:
            self.assertIn(symbol, moduleSymbols)

if __name__ == '__main__':
    unittest.main()
