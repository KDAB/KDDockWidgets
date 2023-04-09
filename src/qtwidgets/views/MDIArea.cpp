/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MDIArea.h"

#include "private/View_p.h"

#include "kddockwidgets/ViewFactory.h"
#include "kddockwidgets/views/DockWidgetViewInterface.h"
#include "kddockwidgets/core/DockWidget.h"
#include "kddockwidgets/core/MDILayout.h"
#include "kddockwidgets/core/DropArea.h"

#include "qtwidgets/views/View.h"
#include "Config.h"

#include <QVBoxLayout>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;
using namespace KDDockWidgets::qtwidgets;

class MDIArea::Private
{
public:
    Private(View *parent)
        : layout(new MDILayout(parent))
    {
    }

    ~Private()
    {
        delete layout;
    }

    MDILayout *const layout;
};

MDIArea::MDIArea(QWidget *parent)
    : qtwidgets::View_qtwidgets<QWidget>(nullptr, ViewType::MDIArea, parent)
    , d(new Private(this))
{

    auto vlay = new QVBoxLayout(this);
    vlay->addWidget(View_qt::asQWidget(d->layout));

    View::d->closeRequested.connect([this](QCloseEvent *ev) { d->layout->onCloseEvent(ev); });

    // TODOm3: for qtquick:
    // QWidgetAdapter::makeItemFillParent(d->layout);
}

MDIArea::~MDIArea()
{
    delete d;
}

void MDIArea::addDockWidget(Core::DockWidget *dw, QPoint localPt,
                            InitialOption addingOption)
{
    if (dw->options() & DockWidgetOption_MDINestable) {
        // We' wrap it with a drop area, so we can drag other dock widgets over this one and dock
        auto wrapperDW =
            Config::self()
                .viewFactory()
                ->createDockWidget(QStringLiteral("%1-mdiWrapper").arg(dw->uniqueName()))
                ->asDockWidgetController();

        auto dropAreaWrapper = new DropArea(wrapperDW->view(), {}, /*isMDIWrapper= */ true);
        dropAreaWrapper->addDockWidget(dw, Location_OnBottom, nullptr);
        wrapperDW->setGuestView(dropAreaWrapper->view()->asWrapper());

        dw = wrapperDW;
    }

    d->layout->addDockWidget(dw, localPt, addingOption);
}

void MDIArea::moveDockWidget(Core::DockWidget *dw, QPoint pos)
{
    d->layout->moveDockWidget(dw, pos);
}

void MDIArea::resizeDockWidget(Core::DockWidget *dw, QSize size)
{
    d->layout->resizeDockWidget(dw, size);
}

void MDIArea::addDockWidget(Views::DockWidgetViewInterface *dwView, QPoint localPt,
                            InitialOption addingOption)
{
    auto dw = dwView ? dwView->dockWidget() : nullptr;
    addDockWidget(dw, localPt, addingOption);
}

void MDIArea::moveDockWidget(Views::DockWidgetViewInterface *dwView, QPoint pos)
{
    auto dw = dwView ? dwView->dockWidget() : nullptr;
    moveDockWidget(dw, pos);
}

void MDIArea::resizeDockWidget(Views::DockWidgetViewInterface *dwView, QSize size)
{
    auto dw = dwView ? dwView->dockWidget() : nullptr;
    resizeDockWidget(dw, size);
}

QList<Core::Group *> MDIArea::groups() const
{
    return d->layout->groups();
}
