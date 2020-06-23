/**
*  This file is part of KDDockWidgets.
*  Copyright (C) 2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
*  Author: Renato Araujo Oliveira Filho <renato.araujo@kdab.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Make "signals:", "slots:" visible as access specifiers
#define QT_ANNOTATE_ACCESS_SPECIFIER(a) __attribute__((annotate(#a)))

// Define PYTHON_BINDINGS this will be used in some part of c++ to skip problematic parts
#define PYTHON_BINDINGS

#include <MainWindowBase.h>
#include <MainWindow.h>
#include <DockWidgetBase.h>
#include <DockWidget.h>

