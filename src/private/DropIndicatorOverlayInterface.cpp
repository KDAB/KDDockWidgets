/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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
                if (inhibited) {
                    removeHover();
                } else {
                    // Re-add hover. Fastest way is simply faking a mouse move
                    if (auto state = qobject_cast<StateDragging *>(DragController::instance()->activeState())) {
                        state->handleMouseMove(QCursor::pos());
                    }
                }
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
    case DropLocation_Horizontal:
    case DropLocation_Vertical:
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

    const DockWidgetBase::List source = windowBeingDragged->dockWidgets();
    const DockWidgetBase::List target = m_hoveredFrame ? m_hoveredFrame->dockWidgets()
                                                       : DockWidgetBase::List();

    const bool isInner = dropLoc & DropLocation_Inner;
    const bool isOutter = dropLoc & DropLocation_Outter;
    if (isInner) {
        if (!m_hoveredFrame)
            return false;
    } else if (isOutter) {
        // If there's only 1 frame in the layout, the outer indicators are redundant, as they do the same thing as the internal ones.
        // But there might be another window obscuring our target, so it's useful to show the outer indicators in this case
        const bool isTheOnlyFrame = m_hoveredFrame && m_hoveredFrame->isTheOnlyFrame();
        if (isTheOnlyFrame && !DockRegistry::self()->isProbablyObscured(m_hoveredFrame->window()->windowHandle(), windowBeingDragged))
            return false;
    } else if (dropLoc == DropLocation_Center) {
        if (!m_hoveredFrame || !m_hoveredFrame->isDockable())
            return false;

        if (auto tabbingAllowedFunc = Config::self().tabbingAllowedFunc()) {
            if (!tabbingAllowedFunc(source, target))
                return false;
        }

        // Only allow to dock to center if the affinities match
        if (!DockRegistry::self()->affinitiesMatch(m_hoveredFrame->affinities(), windowBeingDragged->affinities()))
            return false;
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown drop indicator location" << dropLoc;
        return false;
    }

    if (auto dropIndicatorAllowedFunc = Config::self().dropIndicatorAllowedFunc()) {
        DropArea *dropArea = DragController::instance()->dropAreaUnderCursor();
        if (!dropIndicatorAllowedFunc(dropLoc, source, target, dropArea))
            return false;
    }

    return true;
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
