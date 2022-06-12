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

#include "MainWindow_qtwidgets.h"
#include "Config.h"
#include "ViewFactory.h"

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

class MainWindow_qtwidgets::Private
{
public:
    explicit Private(Controllers::MainWindow *controller, MainWindow_qtwidgets *qq)
        : q(qq)
        , m_controller(controller)
        , m_supportsAutoHide(Config::self().flags() & Config::Flag_AutoHideSupport)
        , m_centralWidget(new MyCentralWidget(qq))
        , m_layout(new QHBoxLayout(m_centralWidget)) // 1 level of indirection so we can add some margins
    {
    }

    ~Private()
    {
        m_connection.disconnect();
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
            m_layout->addWidget(View_qtwidgets::asQWidget(q->sideBar(SideBarLocation::West)->view()));
            auto innerVLayout = new QVBoxLayout();
            innerVLayout->setSpacing(0);
            innerVLayout->setContentsMargins(0, 0, 0, 0);
            innerVLayout->addWidget(View_qtwidgets::asQWidget(q->sideBar(SideBarLocation::North)));
            innerVLayout->addWidget(View_qtwidgets::asQWidget(m_controller->layout()));
            innerVLayout->addWidget(View_qtwidgets::asQWidget(q->sideBar(SideBarLocation::South)));
            m_layout->addLayout(innerVLayout);
            m_layout->addWidget(View_qtwidgets::asQWidget(q->sideBar(SideBarLocation::East)));
        } else {
            m_layout->addWidget(qobject_cast<QWidget *>(m_controller->layout()->view()->asQObject()));
        }

        q->setCentralWidget(m_centralWidget);

        q->create();
        m_connection = q->window()->screenChanged.connect([this] {
            updateMargins(); // logical dpi might have changed
            Q_EMIT DockRegistry::self()->windowChangedScreen(q->window());
        });
    }

    void updateMargins()
    {
        const qreal factor = Views::logicalDpiFactor(q);
        m_layout->setContentsMargins(m_centerWidgetMargins * factor);
    }

    MainWindow_qtwidgets *const q;
    Controllers::MainWindow *const m_controller;
    const bool m_supportsAutoHide;
    QHash<SideBarLocation, Controllers::SideBar *> m_sideBars; // TODOm3: Move to controller
    MyCentralWidget *const m_centralWidget;
    QHBoxLayout *const m_layout;
    KDBindings::ConnectionHandle m_connection;
    QMargins m_centerWidgetMargins = { 1, 5, 1, 1 };
};

MyCentralWidget::~MyCentralWidget()
{
}

MainWindow_qtwidgets::MainWindow_qtwidgets(Controllers::MainWindow *controller,
                                           QWidget *parent, Qt::WindowFlags flags)
    : View_qtwidgets<QMainWindow>(controller, Type::MainWindow, parent, flags)
    , d(new Private(controller, this))
{
}

MainWindow_qtwidgets::MainWindow_qtwidgets(const QString &uniqueName,
                                           MainWindowOptions options,
                                           QWidget *parent,
                                           Qt::WindowFlags flags)
    : View_qtwidgets<QMainWindow>(new Controllers::MainWindow(this, uniqueName, options),
                                  Type::MainWindow, parent, flags)
    , d(new Private(static_cast<Controllers::MainWindow *>(controller()), this))
{
    auto controller = mainWindow();
    controller->init(uniqueName);
    init();
}

MainWindow_qtwidgets::~MainWindow_qtwidgets()
{
    delete d;
}

void MainWindow_qtwidgets::init()
{
    d->init();
}

void MainWindow_qtwidgets::setCentralWidget(QWidget *w)
{
    QMainWindow::setCentralWidget(w);
}

Controllers::SideBar *MainWindow_qtwidgets::sideBar(SideBarLocation location) const
{
    return d->m_sideBars.value(location);
}

void MainWindow_qtwidgets::resizeEvent(QResizeEvent *ev)
{
    d->m_controller->onResized(ev);
}

QMargins MainWindow_qtwidgets::centerWidgetMargins() const
{
    return d->m_centerWidgetMargins;
}

void MainWindow_qtwidgets::setCenterWidgetMargins(const QMargins &margins)
{
    if (d->m_centerWidgetMargins == margins)
        return;
    d->m_centerWidgetMargins = margins;
    d->updateMargins();
}

QRect MainWindow_qtwidgets::centralAreaGeometry() const
{
    return centralWidget()->geometry();
}

Controllers::MainWindow *MainWindow_qtwidgets::mainWindow() const
{
    return d->m_controller;
}

void MainWindow_qtwidgets::setContentsMargins(int left, int top, int right, int bottom)
{
    QMainWindow::setContentsMargins(left, top, right, bottom);
}
