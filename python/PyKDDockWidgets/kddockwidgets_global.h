#pragma once

// Make "signals:", "slots:" visible as access specifiers
#define QT_ANNOTATE_ACCESS_SPECIFIER(a) __attribute__((annotate(#a)))

// Define PYTHON_BINDINGS this will be used in some part of c++ to skip problematic parts
#define PYTHON_BINDINGS

#include <MainWindowBase.h>
#include <MainWindow.h>
#include <DockWidgetBase.h>
#include <DockWidget.h>

