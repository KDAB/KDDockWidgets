/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DropIndicatorOverlayInterface_p.h"

#include "Frame_p.h"
#include "DropArea_p.h"

using namespace KDDockWidgets;

DropIndicatorOverlayInterface::DropIndicatorOverlayInterface(DropArea *dropArea)
    : QWidget(dropArea)
    , m_dropArea(dropArea)
{
    setVisible(false);
    setObjectName(QStringLiteral("DropIndicatorOverlayInterface"));
}

void DropIndicatorOverlayInterface::setWindowBeingDragged(const QWidget *window)
{
    if (window != m_windowBeingDragged) {
        m_windowBeingDragged = window;
        if (m_windowBeingDragged) {
            setGeometry(m_dropArea->rect());
            raise();
        } else {
            setHoveredFrame(nullptr);
        }

        updateVisibility();
    }
}

void DropIndicatorOverlayInterface::setHoveredFrame(Frame *frame)
{
    if (frame != m_hoveredFrame) {
        if (m_hoveredFrame)
            disconnect(m_hoveredFrame, &QObject::destroyed, this, &DropIndicatorOverlayInterface::onFrameDestroyed);

        m_hoveredFrame = frame;
        if (m_hoveredFrame)
            connect(frame, &QObject::destroyed, this, &DropIndicatorOverlayInterface::onFrameDestroyed);

        updateVisibility();
        Q_EMIT hoveredFrameChanged(m_hoveredFrame);
        onHoveredFrameChanged(m_hoveredFrame);
    }
}

bool DropIndicatorOverlayInterface::isHovered() const
{
    return m_windowBeingDragged != nullptr;
}

KDDockWidgets::Location DropIndicatorOverlayInterface::multisplitterLocationFor(DropIndicatorOverlayInterface::DropLocation dropLoc)
{
    switch (dropLoc) {
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_None:
        return KDDockWidgets::Location_None;
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_Left:
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_OutterLeft:
        return KDDockWidgets::Location_OnLeft;
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_OutterTop:
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_Top:
        return KDDockWidgets::Location_OnTop;
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_OutterRight:
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_Right:
        return KDDockWidgets::Location_OnRight;
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_OutterBottom:
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_Bottom:
        return KDDockWidgets::Location_OnBottom;
    case KDDockWidgets::DropIndicatorOverlayInterface::DropLocation_Center:
        return KDDockWidgets::Location_None;
    }

    return KDDockWidgets::Location_None;
}

void DropIndicatorOverlayInterface::onFrameDestroyed()
{
    setHoveredFrame(nullptr);
}

void DropIndicatorOverlayInterface::onHoveredFrameChanged(Frame *)
{

}

void DropIndicatorOverlayInterface::setCurrentDropLocation(DropIndicatorOverlayInterface::DropLocation location)
{
    m_currentDropLocation = location;
}
