/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief QMainWindow wrapper to enable KDDockWidgets support.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "MainWindow.h"
#include "Config.h"
#include "DropArea_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "SideBar_p.h"
#include "DropAreaWithCentralFrame_p.h"
#include "FrameworkWidgetFactory.h"

#include <QVBoxLayout>
#include <QPainter>

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro

using namespace KDDockWidgets;

class MainWindow::Private
{
public:

    explicit Private(MainWindowOptions, MainWindowBase *mainWindow)
        : m_supportsAutoHide(Config::self().flags() & Config::Flag_AutoHideSupport)
    {
        if (m_supportsAutoHide) {
            for (auto location : { SideBarLocation::North, SideBarLocation::East,
                                   SideBarLocation::West, SideBarLocation::South}) {
                m_sideBars.insert(location, Config::self().frameworkWidgetFactory()->createSideBar(location, mainWindow) );
            }
        }
    }

    const bool m_supportsAutoHide;
    QHash<SideBarLocation, SideBar*> m_sideBars;
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
    auto layout = new QHBoxLayout(centralWidget);  // 1 level of indirection so we can add some margins
    layout->setSpacing(0);
    layout->setContentsMargins(centerWidgetMargins());

    if (d->m_supportsAutoHide) {
        layout->addWidget(sideBar(SideBarLocation::West));
        auto innerVLayout = new QVBoxLayout();
        innerVLayout->setSpacing(0);
        innerVLayout->setContentsMargins(0, 0, 0, 0);
        innerVLayout->addWidget(sideBar(SideBarLocation::North));
        innerVLayout->addWidget(dropArea());
        innerVLayout->addWidget(sideBar(SideBarLocation::South));
        layout->addLayout(innerVLayout);
        layout->addWidget(sideBar(SideBarLocation::East));
    } else {
        layout->addWidget(dropArea());
    }

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::setCentralWidget(QWidget *w)
{
    QMainWindow::setCentralWidget(w);
}

SideBar *MainWindow::sideBar(SideBarLocation location) const
{
    return d->m_sideBars.value(location);
}

void MainWindow::resizeEvent(QResizeEvent *ev)
{
    MainWindowBase::resizeEvent(ev);
    onResized(ev); // Also call our own handler, since QtQuick doesn't have resizeEvent()
}

QMargins MainWindow::centerWidgetMargins() const
{
    return { 1, 5, 1, 1};
}

QRect MainWindow::centralAreaGeometry() const
{
    return centralWidget()->geometry();
}
