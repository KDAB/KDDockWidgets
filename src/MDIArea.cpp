/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDIArea.h"
#include "DockWidgetBase.h"
#include "private/MDILayoutWidget_p.h"
#include "private/DropAreaWithCentralFrame_p.h"

#ifdef KDDOCKWIDGETS_QTWIDGETS
#include "DockWidget.h"
#include <QVBoxLayout>
#else
#include "DockWidgetQuick.h"
#endif

#include <QGuiApplication>
#include <QCloseEvent>

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
    : QWidgetAdapter(parent)
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
    if (dw->options() & DockWidgetBase::Option_MDINestable) {
        // We' wrap it with a drop area, so we can drag other dock widgets over this one and dock
        auto wrapperDW = new DockWidgetType(QStringLiteral("%1-mdiWrapper").arg(dw->uniqueName()));
        auto dropAreaWrapper = new DropArea(wrapperDW, /*isMDIWrapper= */ true);
        dropAreaWrapper->addDockWidget(dw, Location_OnBottom, nullptr);
        wrapperDW->setWidget(dropAreaWrapper);

        dw = wrapperDW;
    }

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

QList<Frame *> MDIArea::frames() const
{
    return d->layoutWidget->frames();
}

void MDIArea::onCloseEvent(QCloseEvent *e)
{
    e->accept(); // Accepted by default (will close unless ignored)

    const Frame::List frames = this->frames();
    for (Frame *frame : frames) {
        qApp->sendEvent(frame, e);
        if (!e->isAccepted())
            break; // Stop when the first frame prevents closing
    }
}
