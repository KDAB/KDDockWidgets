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

#ifndef KD_DROP_AREA_P_H
#define KD_DROP_AREA_P_H

#include "docks_export.h"
#include "Frame_p.h"
#include "multisplitter/MultiSplitterWidget_p.h"
#include "DropIndicatorOverlayInterface_p.h"

#include <QWidget>

namespace KDDockWidgets {

class Frame;
class Draggable;
class MultiSplitter;
class DropIndicatorOverlayInterface;
struct WindowBeingDragged;

class DOCKS_EXPORT_FOR_UNIT_TESTS DropArea : public MultiSplitterWidget
{
    Q_OBJECT
public:
    explicit DropArea(QWidget *parent);
    ~DropArea();

    void removeHover();
    void hover(Draggable *draggable, QPoint globalPos);
    bool drop(Draggable *draggable, QPoint globalPos);
    bool drop(QWidget *droppedwindow, KDDockWidgets::Location location, QWidget *relativeTo);
    int numFrames() const;
    void setIndicatorStyle(DropIndicatorOverlayInterface::Type);
    DropIndicatorOverlayInterface::Type indicatorStyle() const;

    Anchor::List nonStaticAnchors() const;
    Frame *frameContainingPos(QPoint globalPos) const;
    Item *centralFrame() const;
    DropIndicatorOverlayInterface *dropIndicatorOverlay() const { return m_dropIndicatorOverlay; }
    void addDockWidget(DockWidget *, KDDockWidgets::Location location, DockWidget *relativeTo);

    bool isInMainWindow() const;
    bool isInFloatingWindow() const;

    void debug_updateItemNamesForGammaray();

    bool checkSanity(MultiSplitter::AnchorSanityOption o = MultiSplitter::AnchorSanity_All);
    QWidget *window() const;
private:
    Q_DISABLE_COPY(DropArea)
    friend class Frame;
    friend class TestDocks;
    friend class DropIndicatorOverlayInterface;
    friend class AnimatedIndicators;
    bool m_inDestructor = false;
    DropIndicatorOverlayInterface *m_dropIndicatorOverlay = nullptr;
};
}

#endif
