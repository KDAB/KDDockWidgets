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
#include "LayoutSaver.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QMessageBox>
#include <QApplication>
#include <QMouseEvent>

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

    auto hlay = new QHBoxLayout();
    layout->addLayout(hlay);

    button = new QPushButton(this);
    auto spin = new QSpinBox(this);
    spin->setMinimum(0);
    button->setText(QStringLiteral("Toggle float"));
    hlay->addWidget(button);
    hlay->addWidget(spin);

    connect(button, &QPushButton::clicked, this, [spin] {
        auto docks = DockRegistry::self()->dockwidgets();
        const int index = spin->value();
        if (index >= docks.size()) {
            QMessageBox::warning(nullptr, QStringLiteral("Invalid index"),
                                 QStringLiteral("Max index is %1").arg(docks.size() - 1));
        } else {
            auto dw = docks.at(index);
            dw->setFloating(!dw->isFloating());
        }
    });

    button = new QPushButton(this);
    button->setText(QStringLiteral("Save layout"));
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [] {
        LayoutSaver saver;
        QString message = saver.saveToDisk() ? QStringLiteral("Saved!")
                                             : QStringLiteral("Error!");
        qDebug() << message;
    });

    button = new QPushButton(this);
    button->setText(QStringLiteral("Restore layout"));
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [] {
        LayoutSaver saver;
        QString message = saver.restoreFromDisk() ? QStringLiteral("Restored!")
                                                  : QStringLiteral("Error!");
        qDebug() << message;
    });

    button = new QPushButton(this);
    button->setText(QStringLiteral("Pick Widget"));
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [this] {

        qApp->setOverrideCursor(Qt::CrossCursor);
        grabMouse();

        QEventLoop loop;
        m_isPickingWidget = &loop;
        loop.exec();

        releaseMouse();
        m_isPickingWidget = nullptr;
        qApp->restoreOverrideCursor();
    });

    button = new QPushButton(this);
    button->setText(QStringLiteral("dump main windows"));
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [] {
        const auto mainWindows = DockRegistry::self()->mainwindows();
        for (MainWindow *mainWindow : mainWindows) {
            mainWindow->multiSplitterLayout()->dumpDebug();
        }
    });

    button = new QPushButton(this);
    button->setText(QStringLiteral("check sanity"));
    layout->addWidget(button);
    connect(button, &QPushButton::clicked, this, [] {
        const auto mainWindows = DockRegistry::self()->mainwindows();
        for (MainWindow *mainWindow : mainWindows) {
            mainWindow->multiSplitterLayout()->checkSanity();
        }

        const auto floatingWindows = DockRegistry::self()->nestedwindows();
        for (FloatingWindow *floatingWindow : floatingWindows) {
            floatingWindow->multiSplitterLayout()->checkSanity();
        }
    });

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

void DebugWindow::mousePressEvent(QMouseEvent *event)
{
    if (!m_isPickingWidget)
        return QWidget::mousePressEvent(event);

    QWidget *w = qApp->widgetAt(event->globalPos());
    qDebug() << "Widget at pos" << event->globalPos() << "is"
             << w << "; parent="
             << (w ? w->parentWidget() : nullptr) << "; geometry="
             << (w ? w->geometry() : QRect());


    m_isPickingWidget->quit();
}
