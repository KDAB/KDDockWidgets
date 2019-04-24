/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, Author: Sérgio Martins <sergio.martins@kdab.com>

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

#include <QtWidgets>

using namespace KDDockWidgets;

DropArea::DropArea(QWidget *parent)
    : MultiSplitter(parent)
{
    qCDebug(creation) << "DropArea";

    //setIndicatorStyle(DropIndicatorOverlayInterface::TypeAnimated);
    setIndicatorStyle(DropIndicatorOverlayInterface::TypeClassic);

    connect(this, &MultiSplitter::widgetAdded, this, [] (Item *item) {
        if (!qobject_cast<Frame*>(item->widget())) {
            qWarning() << "A widget" << item->widget() << "that is not a Frame was added to multi-splitter."
                       << "; application might crash";
            Q_ASSERT(false);
        }
    });

    connect(this, &MultiSplitter::aboutToDumpDebug,
            this, &DropArea::debug_updateItemNamesForGammaray);
}

DropArea::~DropArea()
{
    m_inDestructor = true;
    qCDebug(creation) << "~DropArea";
}

int DropArea::numFrames() const
{
    return count();
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

Anchor::List DropArea::nonStaticAnchors() const
{
    auto anchors = MultiSplitter::anchors();
    Anchor::List result;
    for (Anchor *anchor : anchors) {
        if (!anchor->isStatic())
            result << anchor;
    }

    return result;
}

Frame *DropArea::frameContainingPos(QPoint globalPos) const
{
    const ItemList &items = this->items();
    for (Item *item : items) {
        auto frame = qobject_cast<Frame *>(item->widget());
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
    for (Item *item : items()) {
        if (auto f = qobject_cast<Frame*>(item->widget())) {
            if (f->isCentralFrame())
                return item;
        }
    }
    return nullptr;
}

void DropArea::addDockWidget(DockWidget *dw, Location location, DockWidget *relativeTo)
{
    // The public API deals in terms of DockWidget, but our internal MultiSplitter deals in terms
    // of Frame, so wrap it:
    auto frame = new Frame();
    frame->addWidget(dw);
    Frame *relativeToFrame = relativeTo ? relativeTo->frame() : nullptr;
    addWidget(frame, location, relativeToFrame);
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
    for (Item *item : items()) {
        if (auto frame = qobject_cast<Frame*>(item->widget())) {
            if (!frame->dockWidgets().isEmpty())
                frame->setObjectName(frame->dockWidgets().at(0)->objectName());
        }
    }

    for (Anchor *a : anchors())
        a->debug_updateItemNames();
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

    Q_ASSERT(window()->geometry().contains(globalPos));

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

bool DropArea::drop(QWidget *droppedWindow, KDDockWidgets::Location location, QWidget *relativeTo)
{
    qCDebug(docking) << "DropArea::addFrame";

    auto floatingWindow = qobject_cast<FloatingWindow *>(droppedWindow);
    if (floatingWindow)
        floatingWindow->deleteLater();

    if (auto dock = qobject_cast<DockWidget *>(droppedWindow)) {
        auto frame = new Frame();
        frame->addWidget(dock);
        addWidget(frame, location, relativeTo);
    } else if (floatingWindow) {
        addMultiSplitter(floatingWindow->dropArea(), location, relativeTo);
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
