/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindow.h"
#include "kddockwidgets/core/Layout.h"
#include "kddockwidgets/core/MainWindow.h"
#include "kddockwidgets/core/Window.h"
#include "kddockwidgets/private/DockRegistry.h"
#include "private/multisplitter/Item_p.h"

#include <QDebug>
#include <QTimer>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;
using namespace KDDockWidgets::qtquick;

namespace KDDockWidgets {
class MainWindow::Private
{
public:
    Private(MainWindow *qq)
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

    MainWindow *const q;
};
}


MainWindow::MainWindow(const QString &uniqueName, MainWindowOptions options,
                       QQuickItem *parent, Qt::WindowFlags flags)
    : View_qtquick(new Core::MainWindow(this, uniqueName, options), Core::ViewType::MainWindow, parent,
                   flags)
    , MainWindowViewInterface(static_cast<Core::MainWindow *>(View::controller()))
    , d(new Private(this))
{
    MainWindowViewInterface::init(uniqueName);
    makeItemFillParent(this);

    Core::Layout *lw = m_mainWindow->layout();
    auto layoutView = asView_qtquick(lw->view());
    makeItemFillParent(layoutView);

    // MainWindowQuick has the same constraints as Layout, so just forward the signal
    connect(layoutView, &View_qtquick::geometryUpdated, this, &MainWindow::geometryUpdated);

    connect(layoutView, &View_qtquick::geometryUpdated, this,
            [this] { d->onLayoutGeometryUpdated(); });

    {
        // This block silences a benign layouting constraints warning.
        // During initialization, QtQuick will evaluate the width and height bindings separately,
        // meaning our first Layout::setSize() might have height=0 still, as we're processing the
        // width binding.

        auto timer = new QTimer(this);
        timer->setSingleShot(true);
        timer->start();
        Layouting::Item::s_silenceSanityChecks = true;
        timer->callOnTimeout([] { Layouting::Item::s_silenceSanityChecks = false; });
    }
}

MainWindow::~MainWindow()
{
    if (isRootView()) {
        if (auto window = this->window()) {
            QObject::setParent(nullptr);
            window->destroy();
        }
    }

    delete d;
}

QSize MainWindow::minSize() const
{
    return m_mainWindow->layout()->layoutMinimumSize();
}

QSize MainWindow::maxSizeHint() const
{
    return m_mainWindow->layout()->layoutMaximumSizeHint();
}

QMargins MainWindow::centerWidgetMargins() const
{
    qDebug() << Q_FUNC_INFO << "SideBar hasn't been implemented yet";
    return {};
}

QRect MainWindow::centralAreaGeometry() const
{
    qFatal("Not implemented");
    return {};
}

void MainWindow::setContentsMargins(int left, int top, int right, int bottom)
{
    Q_UNUSED(left);
    Q_UNUSED(right);
    Q_UNUSED(top);
    Q_UNUSED(bottom);
    qDebug() << Q_FUNC_INFO << "not implemented";
}
