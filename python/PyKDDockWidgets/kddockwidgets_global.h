/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

// Make "signals:", "slots:" visible as access specifiers
#define QT_ANNOTATE_ACCESS_SPECIFIER(a) __attribute__((annotate(#a)))

#define QT_WIDGETS_LIB
// Define PYTHON_BINDINGS this will be used in some part of c++ to skip problematic parts
#define PYTHON_BINDINGS

#include <DockWidgetBase.h>
#include <MainWindowBase.h>
#include <MainWindow.h>
#include <DockWidget.h>
