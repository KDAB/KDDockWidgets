/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropAreaWithCentralFrame_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"

using namespace KDDockWidgets;

DropAreaWithCentralFrame::DropAreaWithCentralFrame(QWidgetOrQuick *parent, MainWindowOptions options)
    : DropArea(parent)
    , m_centralFrame(createCentralFrame(options))
{
    if (m_centralFrame)
        addWidget(m_centralFrame->view()->asQWidget(), KDDockWidgets::Location_OnTop, {});
}

DropAreaWithCentralFrame::~DropAreaWithCentralFrame()
{
}

Controllers::Frame *DropAreaWithCentralFrame::createCentralFrame(MainWindowOptions options)
{
    Controllers::Frame *frame = nullptr;
    if (options & MainWindowOption_HasCentralFrame) {
        FrameOptions frameOptions = FrameOption_IsCentralFrame;
        const bool hasPersistentCentralWidget = (options & MainWindowOption_HasCentralWidget) == MainWindowOption_HasCentralWidget;
        if (hasPersistentCentralWidget) {
            frameOptions |= FrameOption_NonDockable;
        } else {
            // With a persistent central widget we don't allow detaching it
            frameOptions |= FrameOption_AlwaysShowsTabs;
        }

        frame = new Controllers::Frame(nullptr, frameOptions);
        frame->setObjectName(QStringLiteral("central frame"));
    }

    return frame;
}
