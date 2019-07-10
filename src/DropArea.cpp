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

#include "DropArea_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "Draggable_p.h"
#include "MainWindow.h"
#include "FloatingWindow_p.h"
#include "indicators/ClassicIndicators_p.h"
#include "indicators/AnimatedIndicators_p.h"
#include "WindowBeingDragged_p.h"

using namespace KDDockWidgets;

/**
 * @file
 * @brief A MultiSplitter with support for drop indicators when hovering over.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */
DropArea::DropArea(QWidget *parent)
    : MultiSplitterWidget(parent)
{
    qCDebug(creation) << "DropArea";

    //setIndicatorStyle(DropIndicatorOverlayInterface::TypeAnimated);
    setIndicatorStyle(DropIndicatorOverlayInterface::TypeClassic);
    connect(m_layout, &MultiSplitterLayout::aboutToDumpDebug,
            this, &DropArea::debug_updateItemNamesForGammaray);
}

DropArea::~DropArea()
{
    m_inDestructor = true;
    qCDebug(creation) << "~DropArea";
}

int DropArea::numFrames() const
{
    return m_layout->count();
}

void DropArea::setIndicatorStyle(DropIndicatorOverlayInterface::Type indicatorType)
{
    if (!m_dropIndicatorOverlay || m_dropIndicatorOverlay->indicatorType() != indicatorType) {
        delete m_dropIndicatorOverlay;
        switch (indicatorType) {
        case DropIndicatorOverlayInterface::TypeClassic:
            m_dropIndicatorOverlay = new ClassicIndicators(this);
            break;
        case DropIndicatorOverlayInterface::TypeAnimated:
            m_dropIndicatorOverlay = new AnimatedIndicators(this);
            break;
        case DropIndicatorOverlayInterface::TypeNone:
            Q_ASSERT(false);
            break;
        }
    }
}

DropIndicatorOverlayInterface::Type DropArea::indicatorStyle() const
{
    return m_dropIndicatorOverlay->indicatorType();
}

Anchor::List DropArea::nonStaticAnchors(bool includePlaceholders) const
{
    auto anchors = m_layout->anchors();
    Anchor::List result;
    for (Anchor *anchor : anchors) {
        if (!anchor->isStatic() && !(!includePlaceholders && anchor->isFollowing()))
            result << anchor;
    }

    return result;
}

Frame *DropArea::frameContainingPos(QPoint globalPos) const
{
    const ItemList &items = m_layout->items();
    for (Item *item : items) {
        auto frame = item->frame();
        if (!frame || !frame->isVisible()) {
            continue;
        }

        if (frame->containsMouse(globalPos))
            return frame;
    }
    return nullptr;
}

Item *DropArea::centralFrame() const
{
    for (Item *item : m_layout->items()) {
        if (auto f = item->frame()) {
            if (f->isCentralFrame())
                return item;
        }
    }
    return nullptr;
}

void DropArea::addDockWidget(DockWidget *dw, Location location, DockWidget *relativeTo, AddingOption option)
{
    if (!dw || dw == relativeTo || location == Location_None) {
        qWarning() << Q_FUNC_INFO << "Invalid parameters" << dw << relativeTo << location;
        return;
    }

    if ((option & AddingOption_StartHidden) && dw->frame() != nullptr) {
        // StartHidden is just to be used at startup, not to moving stuff around
        qWarning() << Q_FUNC_INFO << "Dock widget already exists in the layout";
        return;
    }

    Frame *frame = nullptr;
    Frame *relativeToFrame = relativeTo ? relativeTo->frame() : nullptr;

    // Check if the dock widget already exists in the layout
    if (contains(dw)) {
        Frame *oldFrame = dw->frame();
        if (oldFrame->hasSingleDockWidget()) {
            Q_ASSERT(oldFrame->contains(dw));
            // The frame only has this dock widget, and the frame is already in the layout. So move the frame instead
            frame = oldFrame;
        } else {
            frame = new Frame();
            frame->addWidget(dw);
        }
    } else {
        frame = new Frame();
        frame->addWidget(dw);
    }

    if (option & AddingOption_StartHidden) {
        m_layout->addWidget(dw, location, relativeToFrame, option);
    } else {
        m_layout->addWidget(frame, location, relativeToFrame, option);
    }
}

bool DropArea::isInMainWindow() const
{
    return qobject_cast<MainWindow*>(parentWidget());
}

bool DropArea::isInFloatingWindow() const
{
    return qobject_cast<FloatingWindow*>(parentWidget());
}

void DropArea::debug_updateItemNamesForGammaray()
{
    for (Item *item : m_layout->items()) {
        if (auto frame = item->frame()) {
            if (!frame->dockWidgets().isEmpty())
                frame->setObjectName(frame->dockWidgets().at(0)->objectName());
        }
    }

    for (Anchor *a : m_layout->anchors())
        a->debug_updateItemNames();
}

bool DropArea::checkSanity(MultiSplitterLayout::AnchorSanityOption o)
{
    return m_layout->checkSanity(o);
}

QWidget *DropArea::window() const
{
    if (auto pw = parentWidget())
        return pw->window();

    return nullptr;
}

bool DropArea::contains(DockWidget *dw) const
{
    return dw->frame() && m_layout->contains(dw->frame());
}

void DropArea::hover(Draggable *draggable, QPoint globalPos)
{
    Frame *frame = frameContainingPos(globalPos); // Frame is nullptr if MainWindowOption_HasCentralFrame isn't set
    m_dropIndicatorOverlay->setWindowBeingDragged(draggable->asWidget());
    m_dropIndicatorOverlay->setHoveredFrame(frame);
    m_dropIndicatorOverlay->hover(globalPos);
}

static bool isOutterLocation(DropIndicatorOverlayInterface::DropLocation location)
{
    switch (location) {
    case DropIndicatorOverlayInterface::DropLocation_OutterLeft:
    case DropIndicatorOverlayInterface::DropLocation_OutterTop:
    case DropIndicatorOverlayInterface::DropLocation_OutterRight:
    case DropIndicatorOverlayInterface::DropLocation_OutterBottom:
        return true;
    default:
        return false;
    }
}

bool DropArea::drop(Draggable *draggable, QPoint globalPos)
{
    QWidget *droppedWindow = draggable->asWidget();
    if (droppedWindow == window()) {
        qWarning() << "Refusing to drop onto itself"; // Doesn't happen
        Q_ASSERT(false);
        return false;
    }

    if (m_dropIndicatorOverlay->currentDropLocation() == DropIndicatorOverlayInterface::DropLocation_None) {
        qCDebug(hovering) << "DropArea::drop: bailing out, drop location = none";
        return false;
    }

    qCDebug(dropping) << "DropArea::drop:" << droppedWindow;

    hover(draggable, globalPos);
    Frame *acceptingFrame = m_dropIndicatorOverlay->hoveredFrame();
    if (!(acceptingFrame || isOutterLocation(m_dropIndicatorOverlay->currentDropLocation()))) {
        qWarning() << "DropArea::drop: asserted with frame=" << acceptingFrame << "; Location=" << m_dropIndicatorOverlay->currentDropLocation();
        Q_ASSERT(false);
        return false;
    }

    bool result = true;

    auto droploc = m_dropIndicatorOverlay->currentDropLocation();
    switch (droploc) {
    case DropIndicatorOverlayInterface::DropLocation_Left:
    case DropIndicatorOverlayInterface::DropLocation_Top:
    case DropIndicatorOverlayInterface::DropLocation_Bottom:
    case DropIndicatorOverlayInterface::DropLocation_Right:
        result = drop(droppedWindow, DropIndicatorOverlayInterface::multisplitterLocationFor(droploc), acceptingFrame);
        break;
    case DropIndicatorOverlayInterface::DropLocation_OutterLeft:
    case DropIndicatorOverlayInterface::DropLocation_OutterTop:
    case DropIndicatorOverlayInterface::DropLocation_OutterRight:
    case DropIndicatorOverlayInterface::DropLocation_OutterBottom:
        result = drop(droppedWindow, DropIndicatorOverlayInterface::multisplitterLocationFor(droploc), nullptr);
        break;
    case DropIndicatorOverlayInterface::DropLocation_Center:
        qCDebug(hovering) << "Tabbing" << droppedWindow << "into" << acceptingFrame;
        acceptingFrame->addWidget(draggable);
        break;

    default:
        qWarning() << "DropArea::drop: Unexpected drop location" << m_dropIndicatorOverlay->currentDropLocation();
        Q_ASSERT(false);
        result = false;
        break;
    }

    if (result) {
        qCDebug(hovering) << "Raising";
        window()->raise();
        window()->activateWindow();
    }

    return result;
}

bool DropArea::drop(QWidget *droppedWindow, KDDockWidgets::Location location, Frame *relativeTo)
{
    qCDebug(docking) << "DropArea::addFrame";

    auto floatingWindow = qobject_cast<FloatingWindow *>(droppedWindow);
    if (floatingWindow)
        floatingWindow->deleteLater();

    if (auto dock = qobject_cast<DockWidget *>(droppedWindow)) {
        auto frame = new Frame();
        frame->addWidget(dock);
        m_layout->addWidget(frame, location, relativeTo);
    } else if (floatingWindow) {
        m_layout->addMultiSplitter(floatingWindow->dropArea(), location, relativeTo);
        return true;
    } else {
        qWarning() << "Unknown dropped widget" << droppedWindow;
        return false;
    }

    return true;
}

void DropArea::removeHover()
{
    m_dropIndicatorOverlay->setWindowBeingDragged(nullptr);
}
