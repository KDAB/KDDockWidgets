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

/**
 * @file
 * @brief A MultiSplitter with support for drop indicators when hovering over.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DROP_AREA_P_H
#define KD_DROP_AREA_P_H

#include "docks_export.h"
#include "Frame_p.h"
#include "KDDockWidgets.h"
#include "multisplitter/MultiSplitterWidget_p.h"
#include "multisplitter/MultiSplitterLayout_p.h"
#include "DropIndicatorOverlayInterface_p.h"

#include <QWidget>

namespace KDDockWidgets {

class Frame;
class Draggable;
class DropIndicatorOverlayInterface;
struct WindowBeingDragged;

/**
 * @brief A MultiSplitterWidget with support for drop indicators when hovering over.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS DropArea : public MultiSplitterWidget
{
    Q_OBJECT
public:
    explicit DropArea(QWidget *parent);
    ~DropArea();

    void removeHover();
    void hover(FloatingWindow *floatingWindow, QPoint globalPos);
    bool drop(FloatingWindow *droppedWindow, QPoint globalPos);
    bool drop(QWidget *droppedwindow, KDDockWidgets::Location location, Frame *relativeTo);
    int numFrames() const;
    void setIndicatorStyle(DropIndicatorOverlayInterface::Type);
    DropIndicatorOverlayInterface::Type indicatorStyle() const;

    Anchor::List nonStaticAnchors(bool includePlaceholders = false) const;
    Frame *frameContainingPos(QPoint globalPos) const;
    Item *centralFrame() const;
    DropIndicatorOverlayInterface *dropIndicatorOverlay() const { return m_dropIndicatorOverlay; }
    void addDockWidget(DockWidget *, KDDockWidgets::Location location, DockWidget *relativeTo, AddingOption option = {});

    bool isInFloatingWindow() const;

    void debug_updateItemNamesForGammaray();

    bool checkSanity(MultiSplitterLayout::AnchorSanityOption o = MultiSplitterLayout::AnchorSanity_All);
    QWidget *window() const;
    bool contains(DockWidget *) const;
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
