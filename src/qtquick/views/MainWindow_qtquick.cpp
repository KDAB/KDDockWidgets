/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MainWindow_qtquick.h"
#include "private/LayoutWidget_p.h"
#include "controllers/MainWindow.h"

#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

MainWindow_qtquick::MainWindow_qtquick(const QString &uniqueName, MainWindowOptions options,
                                       QQuickItem *parent, Qt::WindowFlags flags)
    : View_qtquick(new Controllers::MainWindow(this, uniqueName, options),
                   Type::MainWindow, parent, flags)
{
    makeItemFillParent(this);



    LayoutWidget *lw = layoutWidget();
    makeItemFillParent(lw);


    // MainWindowQuick has the same constraints as LayoutWidget, so just forward the signal
    connect(lw, &LayoutWidget::geometryUpdated, this, &MainWindow_qtquick::geometryUpdated);

    connect(lw, &LayoutWidget::geometryUpdated, this,
            &MainWindow_qtquick::onMultiSplitterGeometryUpdated);
}

MainWindow_qtquick::~MainWindow_qtquick()
{
    if (isRootView()()) {
        if (QWindow *window = window()) {
            QObject::setParent(nullptr);
            delete window;
        }
    }
}

QSize MainWindow_qtquick::minSize() const
{
    return layoutWidget()->layoutMinimumSize();
}

QSize MainWindow_qtquick::maximumSize() const
{
    return layoutWidget()->layoutMaximumSizeHint();
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
    const bool mainWindowIsTooSmall = minSz.expandedTo(size()) != size();
    if (mainWindowIsTooSmall) {
        if (isRootView()()) {
            // If we're a top-level, let's go ahead and resize the QWindow
            // any other case is too complex for QtQuick as there's no layout propagation.
            window()->resize(minSz.width(), minSz.height());
        }
    }
}
