/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include "MainWindow_qtquick.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

#include "private/DockRegistry_p.h"
#include "controllers/DropArea.h"
#include "controllers/DropArea.h"
#include "private/Logging_p.h"

#include "controllers/Frame.h"
#include "controllers/SideBar.h"

#include <QPainter>
#include <QScreen>
#include <QVBoxLayout>
#include <QWindow>

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

namespace KDDockWidgets {
class MyCentralWidget : public QWidget
{
public:
    explicit MyCentralWidget(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setObjectName(QStringLiteral("MyCentralWidget"));
    }

    ~MyCentralWidget() override;
};
}

class MainWindow_qtquick::Private
{
public:
    explicit Private(Controllers::MainWindow *controller, MainWindow_qtquick *qq)
        : q(qq)
        , m_controller(controller)
        , m_supportsAutoHide(Config::self().flags() & Config::Flag_AutoHideSupport)
        , m_centralWidget(new MyCentralWidget(qq))
        , m_layout(new QHBoxLayout(m_centralWidget)) // 1 level of indirection so we can add some margins
    {
    }

    void init()
    {
        if (m_supportsAutoHide) {
            for (auto location : { SideBarLocation::North, SideBarLocation::East,
                                   SideBarLocation::West, SideBarLocation::South }) {
                m_sideBars.insert(location, new Controllers::SideBar(location, m_controller));
            }
        }

        m_layout->setSpacing(0);
        updateMargins();

        if (m_supportsAutoHide) {
            m_layout->addWidget(q->sideBar(SideBarLocation::West)->view()->asQWidget());
            auto innerVLayout = new QVBoxLayout();
            innerVLayout->setSpacing(0);
            innerVLayout->setContentsMargins(0, 0, 0, 0);
            innerVLayout->addWidget(q->sideBar(SideBarLocation::North)->view()->asQWidget());
            innerVLayout->addWidget(m_controller->layoutWidget());
            innerVLayout->addWidget(q->sideBar(SideBarLocation::South)->view()->asQWidget());
            m_layout->addLayout(innerVLayout);
            m_layout->addWidget(q->sideBar(SideBarLocation::East)->view()->asQWidget());
        } else {
            m_layout->addWidget(m_controller->layoutWidget());
        }

        q->setCentralWidget(m_centralWidget);

        q->create();
        connect(q->window(), &QWindow::screenChanged, DockRegistry::self(),
                [this] {
                    updateMargins(); // logical dpi might have changed
                    Q_EMIT DockRegistry::self()->windowChangedScreen(q->window());
                });
    }

    void updateMargins()
    {
        const qreal factor = Views::logicalDpiFactor(q);
        m_layout->setContentsMargins(m_centerWidgetMargins * factor);
    }

    MainWindow_qtquick *const q;
    Controllers::MainWindow *const m_controller;
    const bool m_supportsAutoHide;
    QHash<SideBarLocation, Controllers::SideBar *> m_sideBars; // TODOv2: Move to controller
    MyCentralWidget *const m_centralWidget;
    QHBoxLayout *const m_layout;
    QMargins m_centerWidgetMargins = { 1, 5, 1, 1 };
};

MyCentralWidget::~MyCentralWidget()
{
}

MainWindow_qtquick::MainWindow_qtquick(Controllers::MainWindow *controller,
                                       QWidget *parent, Qt::WindowFlags flags)
    : View_qtquick<QMainWindow>(controller, Type::MainWindow, parent, flags)
    , d(new Private(controller, this))
{
}

MainWindow_qtquick::MainWindow_qtquick(const QString &uniqueName,
                                       MainWindowOptions options,
                                       QWidget *parent,
                                       Qt::WindowFlags flags)
    : View_qtquick<QMainWindow>(new Controllers::MainWindow(this, uniqueName, options),
                                Type::MainWindow, parent, flags)
    , d(new Private(static_cast<Controllers::MainWindow *>(controller()), this))
{
    auto controller = mainWindow();
    controller->init(uniqueName, false);
    init();
}

MainWindow_qtquick::~MainWindow_qtquick()
{
    delete d;
}

void MainWindow_qtquick::init()
{
    d->init();
}

void MainWindow_qtquick::setCentralWidget(QWidget *w)
{
    QMainWindow::setCentralWidget(w);
}

Controllers::SideBar *MainWindow_qtquick::sideBar(SideBarLocation location) const
{
    return d->m_sideBars.value(location);
}

void MainWindow_qtquick::resizeEvent(QResizeEvent *ev)
{
    d->m_controller->onResized(ev);
}

QMargins MainWindow_qtquick::centerWidgetMargins() const
{
    return d->m_centerWidgetMargins;
}

void MainWindow_qtquick::setCenterWidgetMargins(const QMargins &margins)
{
    if (d->m_centerWidgetMargins == margins)
        return;
    d->m_centerWidgetMargins = margins;
    d->updateMargins();
}

QRect MainWindow_qtquick::centralAreaGeometry() const
{
    return centralWidget()->geometry();
}

Controllers::MainWindow *MainWindow_qtquick::mainWindow() const
{
    return d->m_controller;
}

void MainWindow_qtquick::setContentsMargins(int left, int top, int right, int bottom)
{
    QMainWindow::setContentsMargins(left, top, right, bottom);
}
