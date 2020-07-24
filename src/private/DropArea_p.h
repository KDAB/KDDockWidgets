/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
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
#include "widgets/MultiSplitter_p.h"
#include "DropIndicatorOverlayInterface_p.h"

namespace KDDockWidgets {

class Frame;
class Draggable;
class DropIndicatorOverlayInterface;
struct WindowBeingDragged;

/**
 * @brief A MultiSplitter with support for drop indicators when hovering over.
 */
class DOCKS_EXPORT_FOR_UNIT_TESTS DropArea : public MultiSplitter
{
    Q_OBJECT
public:
    explicit DropArea(QWidgetOrQuick *parent);
    ~DropArea();

    void removeHover();
    void hover(FloatingWindow *floatingWindow, QPoint globalPos);
    bool drop(FloatingWindow *droppedWindow, QPoint globalPos);
    bool drop(QWidgetOrQuick *droppedwindow, KDDockWidgets::Location location, Frame *relativeTo);
    int numFrames() const;
    Frame::List frames() const;

    Layouting::Item *centralFrame() const;
    DropIndicatorOverlayInterface *dropIndicatorOverlay() const { return m_dropIndicatorOverlay; }
    void addDockWidget(DockWidgetBase *, KDDockWidgets::Location location, DockWidgetBase *relativeTo, AddingOption option = {});

    bool contains(DockWidgetBase *) const;

    QStringList affinities() const;
    void layoutParentContainerEqually(DockWidgetBase *);
private:
    Q_DISABLE_COPY(DropArea)
    friend class Frame;
    friend class TestDocks;
    friend class DropIndicatorOverlayInterface;
    friend class AnimatedIndicators;
    template <typename T>
    bool validateAffinity(T *) const;
    Frame *frameContainingPos(QPoint globalPos) const;
    bool m_inDestructor = false;
    QString m_affinityName;
    DropIndicatorOverlayInterface *m_dropIndicatorOverlay = nullptr;
};
}

#endif
