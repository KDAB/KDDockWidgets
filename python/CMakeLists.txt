set(PYTHON_VERSION "3.7" CACHE STRING  "Use specific python version to build the project.")
find_package(Python3 ${PYTHON_VERSION} REQUIRED COMPONENTS Interpreter Development)
find_package(Shiboken2 REQUIRED)
find_package(PySide2 ${Qt5Widgets_VERSION} EXACT REQUIRED)
include(PySide2ModuleBuild)

add_subdirectory(PyKDDockWidgets)
