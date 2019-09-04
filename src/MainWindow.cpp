/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
 * @brief QMainWindow wrapper to enable KDDockWidgets support.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "MainWindow.h"
#include "DropArea_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "DropAreaWithCentralFrame_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "multisplitter/MultiSplitter_p.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QPainter>

using namespace KDDockWidgets;

class MainWindow::Private
{
public:
    explicit Private(MainWindowOptions options, MainWindowBase *mainWindow)
        : m_dropArea(new DropAreaWithCentralFrame(mainWindow, options))
    {
    }

    DropAreaWithCentralFrame *const m_dropArea;
};


namespace KDDockWidgets {
class MyCentralWidget : public QWidget
{
public:
    explicit MyCentralWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        setObjectName(QStringLiteral("MyCentralWidget"));
    }

    ~MyCentralWidget() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        QPen pen(QColor(184, 184, 184, 184));
        p.setPen(pen);
        p.drawLine(0, 0, width(), 0);
    }
};
}

MyCentralWidget::~MyCentralWidget() {}


MainWindow::MainWindow(const QString &name, MainWindowOptions options,
                       QWidget *parent, Qt::WindowFlags flags)
    : MainWindowBase(name, options, parent, flags)
    , d(new Private(options, this))
{
    auto centralWidget = new MyCentralWidget(this);
    auto layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(1, 5, 1, 1);
    layout->addWidget(dropArea()); // 1 level of indirection so we can add some margins
    setCentralWidget(centralWidget);

    // qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete d;
}

DropAreaWithCentralFrame *MainWindow::dropArea() const
{
    return d->m_dropArea;
}
