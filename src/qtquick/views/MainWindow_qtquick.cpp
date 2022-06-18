/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindow_qtquick.h"
#include "kddockwidgets/controllers/Layout.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "kddockwidgets/private/DockRegistry.h"
#include "Window.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

namespace KDDockWidgets {
class MainWindow_qtquick::Private
{
public:
    Private(MainWindow_qtquick *qq)
        : q(qq)
    {
    }

    void onLayoutGeometryUpdated()
    {
        const QSize minSz = q->minSize();
        const bool mainWindowIsTooSmall = minSz.expandedTo(q->View::size()) != q->View::size();
        if (mainWindowIsTooSmall) {
            if (q->isRootView()) {
                // If we're a top-level, let's go ahead and resize the QWindow
                // any other case is too complex for QtQuick as there's no layout propagation.
                q->window()->resize(minSz.width(), minSz.height());
            }
        }
    }

    MainWindow_qtquick *const q;
};
}


MainWindow_qtquick::MainWindow_qtquick(const QString &uniqueName, MainWindowOptions options,
                                       QQuickItem *parent, Qt::WindowFlags flags)
    : View_qtquick(new Controllers::MainWindow(this, uniqueName, options),
                   Type::MainWindow, parent, flags)
    , MainWindowViewInterface(static_cast<Controllers::MainWindow *>(View::controller()))
    , d(new Private(this))
{
    MainWindowViewInterface::init(uniqueName);
    makeItemFillParent(this);

    Controllers::Layout *lw = m_mainWindow->layout();
    auto layoutView = asView_qtquick(lw->view());
    makeItemFillParent(layoutView);

    // MainWindowQuick has the same constraints as Layout, so just forward the signal
    connect(layoutView, &View_qtquick::geometryUpdated, this, &MainWindow_qtquick::geometryUpdated);

    connect(layoutView, &View_qtquick::geometryUpdated, this, [this] {
        d->onLayoutGeometryUpdated();
    });
}

MainWindow_qtquick::~MainWindow_qtquick()
{
    if (isRootView()) {
        if (auto window = this->window()) {
            QObject::setParent(nullptr);
            window->destroy();
        }
    }

    delete d;
}

QSize MainWindow_qtquick::minSize() const
{
    return m_mainWindow->layout()->layoutMinimumSize();
}

QSize MainWindow_qtquick::maximumSize() const
{
    return m_mainWindow->layout()->layoutMaximumSizeHint();
}

QMargins MainWindow_qtquick::centerWidgetMargins() const
{
    qDebug() << Q_FUNC_INFO << "SideBar hasn't been implemented yet";
    return {};
}

QRect MainWindow_qtquick::centralAreaGeometry() const
{
    qFatal("Not implemented");
    return {};
}

void MainWindow_qtquick::setContentsMargins(int left, int top, int right, int bottom)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
    Q_UNUSED(top);
    Q_UNUSED(bottom);
    qDebug() << Q_FUNC_INFO << "not implemented";
}

void MainWindow_qtquick::moveToSideBar(const QString &dockId)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->moveToSideBar(dw);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::moveToSideBar(const QString &dockId, KDDockWidgets::SideBarLocation loc)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->moveToSideBar(dw, loc);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::restoreFromSideBar(const QString &dockId)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->restoreFromSideBar(dw);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::overlayOnSideBar(const QString &dockId)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->overlayOnSideBar(dw);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::toggleOverlayOnSideBar(const QString &dockId)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->toggleOverlayOnSideBar(dw);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::layoutParentContainerEqually(const QString &dockId)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->layoutParentContainerEqually(dw);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::addDockWidgetAsTab(const QString &dockId)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        return m_mainWindow->addDockWidgetAsTab(dw);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}

void MainWindow_qtquick::addDockWidget(const QString &dockId,
                                       KDDockWidgets::Location location,
                                       const QString &relativeToDockId,
                                       KDDockWidgets::InitialOption initialOption)
{
    if (Controllers::DockWidget *dw = DockRegistry::self()->dockByName(dockId)) {
        auto relativeTo = relativeToDockId.isEmpty() ? nullptr
                                                     : DockRegistry::self()->dockByName(relativeToDockId);
        return m_mainWindow->addDockWidget(dw, location, relativeTo, initialOption);
    } else {
        qWarning() << Q_FUNC_INFO << "Could not find dock widget" << dockId;
    }
}
