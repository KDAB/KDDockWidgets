/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "TitleBar.h"

#include "core/DragController_p.h"

#include "kddockwidgets/core/Group.h"
#include "kddockwidgets/core/FloatingWindow.h"
#include "kddockwidgets/core/TitleBar.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::flutter;


TitleBar::TitleBar(Core::TitleBar *controller, Core::View *parent)
    : View(controller, Core::ViewType::TitleBar, parent)
    , Core::TitleBarViewInterface(controller)
{
}

TitleBar::~TitleBar()
{
}

void TitleBar::init()
{
    setFixedHeight(30);
    QObject::connect(m_titleBar, &Core::TitleBar::titleChanged, [this] { onTitleBarChanged(m_titleBar->title()); });
}

void TitleBar::onTitleBarChanged(const QString &)
{
    qWarning() << Q_FUNC_INFO << "Should be called in dart instead";
}

#ifdef DOCKS_DEVELOPER_MODE

bool TitleBar::isCloseButtonEnabled() const
{
    return true;
}

bool TitleBar::isCloseButtonVisible() const
{
    return true;
}

bool TitleBar::isFloatButtonVisible() const
{
    return true;
}

#endif
