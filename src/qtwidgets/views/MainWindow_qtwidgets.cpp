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
#include "kddockwidgets/ViewFactory.h"

#include "kddockwidgets/controllers/DropArea.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "kddockwidgets/controllers/Frame.h"
#include "kddockwidgets/controllers/SideBar.h"

#include "private/DockRegistry_p.h"
#include "private/Logging_p.h"

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
    explicit Private(MainWindow_qtwidgets *qq)
        : q(qq)
        , m_controller(qq->mainWindow())
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

        m_layout->setSpacing(0);
        updateMargins();

        if (m_supportsAutoHide) {
            m_layout->addWidget(View_qtwidgets::asQWidget(m_controller->sideBar(SideBarLocation::West)->view()));
            auto innerVLayout = new QVBoxLayout();
            innerVLayout->setSpacing(0);
            innerVLayout->setContentsMargins(0, 0, 0, 0);
            innerVLayout->addWidget(View_qtwidgets::asQWidget(m_controller->sideBar(SideBarLocation::North)));
            innerVLayout->addWidget(View_qtwidgets::asQWidget(m_controller->layout()));
            innerVLayout->addWidget(View_qtwidgets::asQWidget(m_controller->sideBar(SideBarLocation::South)));
            m_layout->addLayout(innerVLayout);
            m_layout->addWidget(View_qtwidgets::asQWidget(m_controller->sideBar(SideBarLocation::East)));
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
    MyCentralWidget *const m_centralWidget;
    QHBoxLayout *const m_layout;
    KDBindings::ConnectionHandle m_connection;
    QMargins m_centerWidgetMargins = { 1, 5, 1, 1 };
};

MyCentralWidget::~MyCentralWidget()
{
}

MainWindow_qtwidgets::MainWindow_qtwidgets(const QString &uniqueName,
                                           MainWindowOptions options,
                                           QWidget *parent,
                                           Qt::WindowFlags flags)
    : View_qtwidgets<QMainWindow>(new Controllers::MainWindow(this, uniqueName, options),
                                  Type::MainWindow, parent, flags)
    , MainWindowViewInterface(static_cast<Controllers::MainWindow *>(controller()))
    , d(new Private(this))
{
    MainWindowViewInterface::init(uniqueName);
    d->init();
}

MainWindow_qtwidgets::~MainWindow_qtwidgets()
{
    delete d;
}

void MainWindow_qtwidgets::setCentralWidget(QWidget *w)
{
    QMainWindow::setCentralWidget(w);
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

void MainWindow_qtwidgets::setContentsMargins(int left, int top, int right, int bottom)
{
    QMainWindow::setContentsMargins(left, top, right, bottom);
}

void MainWindow_qtwidgets::setPersistentCentralWidget(QWidget *widget)
{
    if (widget) {
        auto wrapper = std::shared_ptr<KDDockWidgets::ViewWrapper>(new KDDockWidgets::Views::ViewWrapper_qtwidgets(widget));
        m_mainWindow->setPersistentCentralView(wrapper);
    } else {
        m_mainWindow->setPersistentCentralView({});
    }
}

QWidget *MainWindow_qtwidgets::persistentCentralWidget() const
{
    auto view = m_mainWindow->persistentCentralView();
    return view ? qobject_cast<QWidget *>(view->asQObject()) : nullptr;
}
