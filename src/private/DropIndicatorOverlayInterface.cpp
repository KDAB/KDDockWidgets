/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropIndicatorOverlay.h"

#include "kddockwidgets/controllers/DropArea.h"
#include "DockRegistry.h"
#include "DragController_p.h"
#include "Config.h"
#include "Platform.h"

#include "kddockwidgets/controllers/Frame.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

DropIndicatorOverlay::DropIndicatorOverlay(Controllers::DropArea *dropArea)
    : Controller(Type::None, Platform::instance()->createView(dropArea->view()))
    , m_dropArea(dropArea)
{
    view()->setVisible(false);
    view()->setObjectName(QStringLiteral("DropIndicatorOverlay"));

    // Set transparent for mouse events so that topLevel->childAt() never returns the drop indicator overlay
    view()->setAttribute(Qt::WA_TransparentForMouseEvents);

    connect(DockRegistry::self(), &DockRegistry::dropIndicatorsInhibitedChanged, this,
            [this](bool inhibited) {
                if (inhibited)
                    removeHover();

                // if false then simply moving the mouse will make the drop indicators appear again
            });
}

void DropIndicatorOverlay::setWindowBeingDragged(bool is)
{
    if (is == m_draggedWindowIsHovering)
        return;

    m_draggedWindowIsHovering = is;
    if (is) {
        view()->setGeometry(m_dropArea->rect());
        view()->raise();
    } else {
        setHoveredFrame(nullptr);
    }

    setVisible(is);
    updateVisibility();
}

QRect DropIndicatorOverlay::hoveredFrameRect() const
{
    return m_hoveredFrameRect;
}

void DropIndicatorOverlay::setHoveredFrame(Controllers::Frame *frame)
{
    if (frame == m_hoveredFrame)
        return;

    if (m_hoveredFrame)
        disconnect(m_hoveredFrame, &QObject::destroyed, this, &DropIndicatorOverlay::onFrameDestroyed);

    m_hoveredFrame = frame;
    if (m_hoveredFrame) {
        connect(frame, &QObject::destroyed, this, &DropIndicatorOverlay::onFrameDestroyed);
        setHoveredFrameRect(m_hoveredFrame->view()->geometry());
    } else {
        setHoveredFrameRect(QRect());
    }

    updateVisibility();
    Q_EMIT hoveredFrameChanged(m_hoveredFrame);
    onHoveredFrameChanged(m_hoveredFrame);
}

bool DropIndicatorOverlay::isHovered() const
{
    return m_draggedWindowIsHovering;
}

DropLocation DropIndicatorOverlay::currentDropLocation() const
{
    return m_currentDropLocation;
}

KDDockWidgets::Location DropIndicatorOverlay::multisplitterLocationFor(DropLocation dropLoc)
{
    switch (dropLoc) {
    case DropLocation_None:
        return KDDockWidgets::Location_None;
    case DropLocation_Left:
    case DropLocation_OutterLeft:
        return KDDockWidgets::Location_OnLeft;
    case DropLocation_OutterTop:
    case DropLocation_Top:
        return KDDockWidgets::Location_OnTop;
    case DropLocation_OutterRight:
    case DropLocation_Right:
        return KDDockWidgets::Location_OnRight;
    case DropLocation_OutterBottom:
    case DropLocation_Bottom:
        return KDDockWidgets::Location_OnBottom;
    case DropLocation_Center:
        return KDDockWidgets::Location_None;
    case DropLocation_Inner:
    case DropLocation_Outter:
        qWarning() << Q_FUNC_INFO << "Unexpected drop location" << dropLoc;
        break;
    }

    return KDDockWidgets::Location_None;
}

bool DropIndicatorOverlay::dropIndicatorVisible(DropLocation dropLoc) const
{
    if (dropLoc == DropLocation_None)
        return false;

    WindowBeingDragged *windowBeingDragged = DragController::instance()->windowBeingDragged();
    if (!windowBeingDragged)
        return false;

    const Controllers::DockWidget::List source = windowBeingDragged->dockWidgets();
    const Controllers::DockWidget::List target = m_hoveredFrame ? m_hoveredFrame->dockWidgets()
                                                                : Controllers::DockWidget::List();

    const bool isInner = dropLoc & DropLocation_Inner;
    const bool isOutter = dropLoc & DropLocation_Outter;
    if (isInner) {
        if (!m_hoveredFrame)
            return false;
    } else if (isOutter) {
        // If there's only 1 frame in the layout, the outer indicators are redundant, as they do the same thing as the internal ones.
        // But there might be another window obscuring our target, so it's useful to show the outer indicators in this case
        const bool isTheOnlyFrame = m_hoveredFrame && m_hoveredFrame->isTheOnlyFrame();
        if (isTheOnlyFrame && !DockRegistry::self()->isProbablyObscured(m_hoveredFrame->view()->window(), windowBeingDragged))
            return false;
    } else if (dropLoc == DropLocation_Center) {
        if (!m_hoveredFrame)
            return false;

        if (auto tabbingAllowedFunc = Config::self().tabbingAllowedFunc()) {
            if (!tabbingAllowedFunc(source, target))
                return false;
        }

        // Only allow to dock to center if the affinities match
        if (!DockRegistry::self()->affinitiesMatch(m_hoveredFrame->affinities(), windowBeingDragged->affinities()) && m_hoveredFrame->isDockable())
            return false;
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown drop indicator location" << dropLoc;
        return false;
    }

    if (auto dropIndicatorAllowedFunc = Config::self().dropIndicatorAllowedFunc()) {
        if (!dropIndicatorAllowedFunc(dropLoc, source, target))
            return false;
    }

    return true;
}

void DropIndicatorOverlay::onFrameDestroyed()
{
    setHoveredFrame(nullptr);
}

void DropIndicatorOverlay::onHoveredFrameChanged(Controllers::Frame *)
{
}

void DropIndicatorOverlay::setCurrentDropLocation(DropLocation location)
{
    if (m_currentDropLocation != location) {
        m_currentDropLocation = location;
        Q_EMIT currentDropLocationChanged();
    }
}

DropLocation DropIndicatorOverlay::hover(QPoint globalPos)
{
    return hover_impl(globalPos);
}

void DropIndicatorOverlay::setHoveredFrameRect(QRect rect)
{
    if (m_hoveredFrameRect != rect) {
        m_hoveredFrameRect = rect;
        Q_EMIT hoveredFrameRectChanged();
    }
}

void DropIndicatorOverlay::removeHover()
{
    setWindowBeingDragged(false);
    setCurrentDropLocation(DropLocation_None);
}
