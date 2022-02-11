/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DropIndicatorOverlayInterface_p.h"

#include "Frame_p.h"
#include "DropArea_p.h"
#include "DockRegistry_p.h"
#include "DragController_p.h"
#include "Config.h"

using namespace KDDockWidgets;

DropIndicatorOverlayInterface::DropIndicatorOverlayInterface(DropArea *dropArea)
    : QWidgetAdapter(dropArea)
    , m_dropArea(dropArea)
{
    setVisible(false);
    setObjectName(QStringLiteral("DropIndicatorOverlayInterface"));

    // Set transparent for mouse events so that topLevel->childAt() never returns the drop indicator overlay
    setAttribute(Qt::WA_TransparentForMouseEvents);

    connect(DockRegistry::self(), &DockRegistry::dropIndicatorsInhibitedChanged, this,
            [this](bool inhibited) {
                if (inhibited)
                    removeHover();

                // if false then simply moving the mouse will make the drop indicators appear again
            });
}

void DropIndicatorOverlayInterface::setWindowBeingDragged(bool is)
{
    if (is == m_draggedWindowIsHovering)
        return;

    m_draggedWindowIsHovering = is;
    if (is) {
        setGeometry(m_dropArea->QWidgetAdapter::rect());
        raise();
    } else {
        setHoveredFrame(nullptr);
    }

    setVisible(is);
    updateVisibility();
}

QRect DropIndicatorOverlayInterface::hoveredFrameRect() const
{
    return m_hoveredFrameRect;
}

void DropIndicatorOverlayInterface::setHoveredFrame(Frame *frame)
{
    if (frame == m_hoveredFrame)
        return;

    if (m_hoveredFrame)
        disconnect(m_hoveredFrame, &QObject::destroyed, this, &DropIndicatorOverlayInterface::onFrameDestroyed);

    m_hoveredFrame = frame;
    if (m_hoveredFrame) {
        connect(frame, &QObject::destroyed, this, &DropIndicatorOverlayInterface::onFrameDestroyed);
        setHoveredFrameRect(m_hoveredFrame->QWidgetAdapter::geometry());
    } else {
        setHoveredFrameRect(QRect());
    }

    updateVisibility();
    Q_EMIT hoveredFrameChanged(m_hoveredFrame);
    onHoveredFrameChanged(m_hoveredFrame);
}

bool DropIndicatorOverlayInterface::isHovered() const
{
    return m_draggedWindowIsHovering;
}

DropLocation DropIndicatorOverlayInterface::currentDropLocation() const
{
    return m_currentDropLocation;
}

KDDockWidgets::Location DropIndicatorOverlayInterface::multisplitterLocationFor(DropLocation dropLoc)
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

bool DropIndicatorOverlayInterface::dropIndicatorVisible(DropLocation dropLoc) const
{
    if (dropLoc == DropLocation_None)
        return false;

    WindowBeingDragged *windowBeingDragged = DragController::instance()->windowBeingDragged();
    if (!windowBeingDragged)
        return false;

    const bool isInner = dropLoc & DropLocation_Inner;
    const bool isOutter = dropLoc & DropLocation_Outter;
    if (isInner) {
        return m_hoveredFrame != nullptr;
    } else if (isOutter) {
        // If there's only 1 frame in the layout, the outer indicators are redundant, as they do the same thing as the internal ones.
        // But there might be another window obscuring our target, so it's useful to show the outer indicators in this case
        const bool isTheOnlyFrame = m_hoveredFrame && m_hoveredFrame->isTheOnlyFrame();
        return !isTheOnlyFrame || DockRegistry::self()->isProbablyObscured(m_hoveredFrame->window()->windowHandle(), windowBeingDragged);
    } else if (dropLoc == DropLocation_Center) {
        if (!m_hoveredFrame)
            return false;

        if (auto tabbingAllowedFunc = Config::self().tabbingAllowedFunc()) {
            const DockWidgetBase::List source = windowBeingDragged->dockWidgets();
            const DockWidgetBase::List target = m_hoveredFrame->dockWidgets();
            if (!tabbingAllowedFunc(source, target))
                return false;
        }

        // Only allow to dock to center if the affinities match
        return windowBeingDragged && DockRegistry::self()->affinitiesMatch(m_hoveredFrame->affinities(), windowBeingDragged->affinities()) && m_hoveredFrame->isDockable();
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown drop indicator location" << dropLoc;
    }

    return false;
}

void DropIndicatorOverlayInterface::onFrameDestroyed()
{
    setHoveredFrame(nullptr);
}

void DropIndicatorOverlayInterface::onHoveredFrameChanged(Frame *)
{
}

void DropIndicatorOverlayInterface::setCurrentDropLocation(DropLocation location)
{
    if (m_currentDropLocation != location) {
        m_currentDropLocation = location;
        Q_EMIT currentDropLocationChanged();
    }
}

DropLocation DropIndicatorOverlayInterface::hover(QPoint globalPos)
{
    return hover_impl(globalPos);
}

void DropIndicatorOverlayInterface::setHoveredFrameRect(QRect rect)
{
    if (m_hoveredFrameRect != rect) {
        m_hoveredFrameRect = rect;
        Q_EMIT hoveredFrameRectChanged();
    }
}

void DropIndicatorOverlayInterface::removeHover()
{
    setWindowBeingDragged(false);
    setCurrentDropLocation(DropLocation_None);
}
