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

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

MainWindow_qtquick::MainWindow_qtquick(const QString &uniqueName, MainWindowOptions options,
                                       QQuickItem *parent, Qt::WindowFlags flags)
    : View_qtquick(new Controllers::MainWindow(this, uniqueName, options),
                   Type::MainWindow, parent, flags)
    , m_controller(static_cast<Controllers::MainWindow *>(controller()))
{
    m_controller->init(uniqueName);
    makeItemFillParent(this);

    Controllers::Layout *lw = m_controller->layout();
    auto layoutView = asView_qtquick(lw->view());
    makeItemFillParent(layoutView);


    // MainWindowQuick has the same constraints as Layout, so just forward the signal
    connect(layoutView, &View_qtquick::geometryUpdated, this, &MainWindow_qtquick::geometryUpdated);

    connect(layoutView, &View_qtquick::geometryUpdated, this,
            &MainWindow_qtquick::onMultiSplitterGeometryUpdated);
}

MainWindow_qtquick::~MainWindow_qtquick()
{
    if (isRootView()) {
        if (auto window = this->window()) {
            QObject::setParent(nullptr);
            window->destroy();
        }
    }
}

QSize MainWindow_qtquick::minSize() const
{
    return m_controller->layout()->layoutMinimumSize();
}

QSize MainWindow_qtquick::maximumSize() const
{
    return m_controller->layout()->layoutMaximumSizeHint();
}

Controllers::SideBar *MainWindow_qtquick::sideBar(SideBarLocation) const
{
    return nullptr;
}

QMargins MainWindow_qtquick::centerWidgetMargins() const
{
    qDebug() << Q_FUNC_INFO << "SideBar hasn't been implemented yet";
    return {};
}

void MainWindow_qtquick::onMultiSplitterGeometryUpdated()
{
    const QSize minSz = minSize();
    const bool mainWindowIsTooSmall = minSz.expandedTo(View::size()) != View::size();
    if (mainWindowIsTooSmall) {
        if (isRootView()) {
            // If we're a top-level, let's go ahead and resize the QWindow
            // any other case is too complex for QtQuick as there's no layout propagation.
            window()->resize(minSz.width(), minSz.height());
        }
    }
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

Controllers::MainWindow *MainWindow_qtquick::mainWindow() const
{
    return m_controller;
}
