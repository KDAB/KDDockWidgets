/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
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

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "MultiSplitter_p.h"
#include "DropIndicatorOverlayInterface_p.h"

class TestDocks;

namespace KDDockWidgets {

class Frame;
class Draggable;
struct WindowBeingDragged;

/**
 * @brief A MultiSplitter with support for drop indicators when hovering over.
 */
class DOCKS_EXPORT DropArea : public MultiSplitter
{
    Q_OBJECT
public:
    explicit DropArea(QWidgetOrQuick *parent, bool isMDIWrapper = false);
    ~DropArea();

    void removeHover();
    DropLocation hover(WindowBeingDragged *draggedWindow, QPoint globalPos);
    ///@brief Called when a user drops a widget via DND
    bool drop(WindowBeingDragged *droppedWindow, QPoint globalPos);
    Frame::List frames() const;

    Layouting::Item *centralFrame() const;
    DropIndicatorOverlayInterface *dropIndicatorOverlay() const
    {
        return m_dropIndicatorOverlay;
    }
    void addDockWidget(DockWidgetBase *, KDDockWidgets::Location location,
                       DockWidgetBase *relativeTo, InitialOption = {});

    bool containsDockWidget(DockWidgetBase *) const;

    /// Returns whether this layout has a single dock widget which is floating
    /// Implies it's in a FloatingWindow and that it has only one dock widget
    bool hasSingleFloatingFrame() const;

    /// Returns whether this drop area has only 1 frame.
    /// See further explanation in FloatingWindow::hasSingleFrame()
    bool hasSingleFrame() const;

    QStringList affinities() const;
    void layoutParentContainerEqually(DockWidgetBase *);

    /// When DockWidget::Option_MDINestable is used, docked MDI dock widgets will be wrapped inside a DropArea, so they accept drops
    /// This DropArea is created implicitly while docking, and this function will return true
    bool isMDIWrapper() const;

    /// Returns the helper dock widget for implementing DockWidget::Option_MDINestable.
    DockWidgetBase *mdiDockWidgetWrapper() const;

private:
    Q_DISABLE_COPY(DropArea)
    friend class Frame;
    friend class ::TestDocks;
    friend class DropIndicatorOverlayInterface;
    friend class AnimatedIndicators;
    friend class FloatingWindow;

    template<typename T>
    bool validateAffinity(T *, Frame *acceptingFrame = nullptr) const;
    bool drop(WindowBeingDragged *draggedWindow, Frame *acceptingFrame, DropLocation);
    bool drop(QWidgetOrQuick *droppedwindow, KDDockWidgets::Location location, Frame *relativeTo);
    Frame *frameContainingPos(QPoint globalPos) const;
    void updateFloatingActions();

    bool m_inDestructor = false;
    const bool m_isMDIWrapper;
    QString m_affinityName;
    DropIndicatorOverlayInterface *m_dropIndicatorOverlay = nullptr;
};
}

#endif
