/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDIArea.h"
#include "private/MDILayoutWidget_p.h"

#ifdef KDDOCKWIDGETS_QTWIDGETS
# include <QVBoxLayout>
#endif

using namespace KDDockWidgets;

class MDIArea::Private
{
public:
    Private(QWidgetOrQuick *parent)
        : layoutWidget(new MDILayoutWidget(parent))
    {
    }

    ~Private()
    {
        delete layoutWidget;
    }

    MDILayoutWidget *const layoutWidget;
};

MDIArea::MDIArea(QWidgetOrQuick *parent)
    : QWidgetOrQuick(parent)
    , d(new Private(this))
{
#ifdef KDDOCKWIDGETS_QTWIDGETS
    auto vlay = new QVBoxLayout(this);
    vlay->setContentsMargins({});
    vlay->addWidget(d->layoutWidget);
#else
    QWidgetAdapter::makeItemFillParent(d->layoutWidget);
#endif
}

MDIArea::~MDIArea()
{
    delete d;
}

void MDIArea::addDockWidget(DockWidgetBase *dw, QPoint localPt, InitialOption addingOption)
{
    d->layoutWidget->addDockWidget(dw, localPt, addingOption);
}

void MDIArea::moveDockWidget(DockWidgetBase *dw, QPoint pos)
{
    d->layoutWidget->moveDockWidget(dw, pos);
}

void MDIArea::resizeDockWidget(DockWidgetBase *dw, QSize size)
{
    d->layoutWidget->resizeDockWidget(dw, size);
}
