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
#include "DockRegistry_p.h"
#include "DropAreaWithCentralFrame_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "multisplitter/MultiSplitter_p.h"

#include <QApplication>
#include <QDataStream>
#include <QVBoxLayout>
#include <QPainter>

using namespace KDDockWidgets;

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

class MainWindow::Private
{
public:
    explicit Private(const QString &mainWindowName, MainWindowOptions options, MainWindow *mainWindow)
        : m_dropArea(new DropAreaWithCentralFrame(mainWindow, options))
        , name(mainWindowName)
        , m_options(options)
    {
    }

    bool supportsCentralFrame() const
    {
        return m_options & MainWindowOption_HasCentralFrame;
    }

    DropAreaWithCentralFrame *const m_dropArea;
    const QString name;
    const MainWindowOptions m_options;
};

MainWindow::MainWindow(const QString &name, MainWindowOptions options,
                       QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
    , d(new Private(name, options, this))
{
    DockRegistry::self()->registerMainWindow(this);

    auto centralWidget = new MyCentralWidget(this);
    auto layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(1, 5, 1, 1);
    layout->addWidget(d->m_dropArea); // 1 level of indirection so we can add some margins
    setCentralWidget(centralWidget);

    // qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    DockRegistry::self()->unregisterMainWindow(this);
    delete d;
}

void MainWindow::addDockWidgetAsTab(DockWidgetBase *widget)
{
    Q_ASSERT(widget);
    qCDebug(addwidget) << Q_FUNC_INFO << widget;

    if (d->supportsCentralFrame()) {
        d->m_dropArea->m_centralFrame->addWidget(widget);
    } else {
        qWarning() << Q_FUNC_INFO << "Not supported without MainWindowOption_HasCentralFrame";
    }
}

void MainWindow::addDockWidget(DockWidgetBase *dw, Location location, DockWidgetBase *relativeTo, AddingOption option)
{
    d->m_dropArea->addDockWidget(dw, location, relativeTo, option);
}

QString MainWindow::uniqueName() const
{
    return d->name;
}

MainWindowOptions MainWindow::options() const
{
    return d->m_options;
}

DropArea *MainWindow::dropArea() const
{
    return d->m_dropArea;
}

MultiSplitterLayout *MainWindow::multiSplitterLayout() const
{
    return d->m_dropArea->multiSplitterLayout();
}

bool MainWindow::eventFilter(QObject *o, QEvent *e)
{
    qCDebug(globalevents) << "event: " << e->type() << ";receiver=" << o;
    return QMainWindow::eventFilter(o, e);
}

bool MainWindow::fillFromDataStream(QDataStream &ds)
{
    int options;
    ds >> options;

    if (options != int(d->m_options)) {
        qWarning() << Q_FUNC_INFO << "Refusing to restore MainWindow with different options"
                   << "; expected=" << options << "; has=" << d->m_options;
        return false;
    }

    return d->m_dropArea->multiSplitterLayout()->fillFromDataStream(ds);
}

QDataStream &KDDockWidgets::operator<<(QDataStream &ds, MainWindow *mainWindow)
{
    ds << mainWindow->d->m_options;
    ds << mainWindow->d->m_dropArea->multiSplitterLayout();

    return ds;
}
