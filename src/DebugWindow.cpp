/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 * @brief Window to show debug information. Used for debugging only, for apps that don't support GammaRay.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "DebugWindow_p.h"
#include "ObjectViewer_p.h"
#include "DockRegistry_p.h"
#include "FloatingWindow_p.h"
#include "DropArea_p.h"
#include "MainWindow.h"

#include <QVBoxLayout>
#include <QPushButton>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Debug;

DebugWindow::DebugWindow(QWidget *parent)
    : QWidget(parent)
    , m_objectViewer(parent)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(&m_objectViewer);

    auto button = new QPushButton(this);
    button->setText(QStringLiteral("Dump DockWidget Info"));
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, &DebugWindow::dumpDockWidgetInfo);

    resize(800, 800);
}

void DebugWindow::dumpDockWidgetInfo()
{
    QVector<FloatingWindow*> floatingWindows = DockRegistry::self()->nestedwindows();
    MainWindow::List mainWindows = DockRegistry::self()->mainwindows();

    for (FloatingWindow *fw : floatingWindows) {
        fw->dropArea()->multiSplitterLayout()->dumpDebug();
    }

    for (MainWindow *mw : mainWindows)
        mw->multiSplitterLayout()->dumpDebug();
}
