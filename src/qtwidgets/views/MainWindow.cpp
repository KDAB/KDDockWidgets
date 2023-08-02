/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
#include "qtwidgets/ViewFactory.h"
#include "ViewWrapper_p.h"
#include "core/DockRegistry_p.h"
#include "core/DropArea.h"
#include "core/MainWindow.h"
#include "core/Group.h"
#include "core/SideBar.h"
#include "core/Window_p.h"
#include "core/DockRegistry.h"

#include "core/Logging_p.h"

#include <QPainter>
#include <QScreen>
#include <QVBoxLayout>
#include <QWindow>

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtWidgets;

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

class MainWindow::Private
{
public:
    explicit Private(MainWindow *qq)
        : q(qq)
        , m_controller(qq->mainWindow())
        , m_supportsAutoHide(Config::self().flags() & Config::Flag_AutoHideSupport)
        , m_centralWidget(new MyCentralWidget(qq))
        , m_layout(new QHBoxLayout(m_centralWidget)) // 1 level of indirection so we can add some
                                                     // margins
    {
    }

    ~Private()
    {
    }

    void updateMargins()
    {
        const qreal factor = QtWidgets::logicalDpiFactor(q);
        m_layout->setContentsMargins(m_centerWidgetMargins * factor);
    }

    MainWindow *const q;
    Core::MainWindow *const m_controller;
    const bool m_supportsAutoHide;
    MyCentralWidget *const m_centralWidget;
    QHBoxLayout *const m_layout;
    QMargins m_centerWidgetMargins = { 1, 5, 1, 1 };
};

MyCentralWidget::~MyCentralWidget() = default;

MainWindow::MainWindow(const QString &uniqueName, MainWindowOptions options,
                       QWidget *parent, Qt::WindowFlags flags)
    : View<QMainWindow>(new Core::MainWindow(this, uniqueName, options),
                        Core::ViewType::MainWindow, parent, flags)
    , MainWindowViewInterface(static_cast<Core::MainWindow *>(controller()))
    , d(new Private(this))
{
    m_mainWindow->init(uniqueName);

    d->m_layout->setSpacing(0);
    d->updateMargins();

    if (d->m_supportsAutoHide) {
        d->m_layout->addWidget(
            View_qt::asQWidget(d->m_controller->sideBar(SideBarLocation::West)->view()));
        auto innerVLayout = new QVBoxLayout();
        innerVLayout->setSpacing(0);
        innerVLayout->setContentsMargins(0, 0, 0, 0);
        innerVLayout->addWidget(
            View_qt::asQWidget(d->m_controller->sideBar(SideBarLocation::North)));
        innerVLayout->addWidget(View_qt::asQWidget(d->m_controller->layout()));
        innerVLayout->addWidget(
            View_qt::asQWidget(d->m_controller->sideBar(SideBarLocation::South)));
        d->m_layout->addLayout(innerVLayout);
        d->m_layout->addWidget(View_qt::asQWidget(d->m_controller->sideBar(SideBarLocation::East)));
    } else {
        d->m_layout->addWidget(View_qt::asQWidget(d->m_controller->layout()->view()));
    }

    setCentralWidget(d->m_centralWidget);

    const bool isWindow = !parentWidget() || (flags & Qt::Window);
    if (isWindow) {
        // Update our margins when logical dpi changes.
        // QWidget doesn't have any screenChanged signal, so we need to use QWindow::screenChanged.
        // Note #1: Someone might be using this main window embedded into another main window, in
        // which case it will never have a QWindow, so guard it with isWindow. Note #2: We don't use
        // QWidget::isWindow() as that will always be true since QMainWindow sets it. Anyone wanting
        // or not wanting this immediate create() needs to pass a parent/flag pair that makes sense.
        // For example, some people might want to add this main window into a layout and avoid the
        // create(), so they pass a parent, with null flag.

        create(); // ensure QWindow exists
        window()->onScreenChanged(this, [](QObject *context, auto window) {
            if (auto mw = qobject_cast<MainWindow *>(context))
                mw->updateMargins(); // logical dpi might have changed
            DockRegistry::self()->dptr()->windowChangedScreen.emit(window);
        });
    }
}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::setCentralWidget(QWidget *w)
{
    QMainWindow::setCentralWidget(w);
}

QMargins MainWindow::centerWidgetMargins() const
{
    return d->m_centerWidgetMargins;
}

void MainWindow::setCenterWidgetMargins(const QMargins &margins)
{
    if (d->m_centerWidgetMargins == margins)
        return;
    d->m_centerWidgetMargins = margins;
    d->updateMargins();
}

QRect MainWindow::centralAreaGeometry() const
{
    return centralWidget()->geometry();
}

void MainWindow::setContentsMargins(int left, int top, int right, int bottom)
{
    QMainWindow::setContentsMargins(left, top, right, bottom);
}

void MainWindow::setPersistentCentralWidget(QWidget *widget)
{
    m_mainWindow->setPersistentCentralView(QtWidgets::ViewWrapper::create(widget));
}

QWidget *MainWindow::persistentCentralWidget() const
{
    auto view = m_mainWindow->persistentCentralView();
    return View_qt::asQWidget(view.get());
}

QHBoxLayout *MainWindow::internalLayout() const
{
    return d->m_layout;
}

void MainWindow::updateMargins()
{
    d->updateMargins();
}
