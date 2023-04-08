/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DROPINDICATOROVERLAY_H
#define KD_DROPINDICATOROVERLAY_H

#include "kddockwidgets/docks_export.h"
#include "kddockwidgets/KDDockWidgets.h"
#include "Controller.h"

#include <QRect>

namespace KDDockWidgets {

namespace Core {

class DropArea;
class Group;

class DOCKS_EXPORT DropIndicatorOverlay : public Controller
{
    Q_OBJECT
public:
    explicit DropIndicatorOverlay(Core::DropArea *dropArea);
    void setHoveredFrame(Core::Group *);
    void setWindowBeingDragged(bool);
    QRect hoveredFrameRect() const;
    bool isHovered() const;
    DropLocation currentDropLocation() const;
    Core::Group *hoveredFrame() const
    {
        return m_hoveredFrame;
    }
    void setCurrentDropLocation(DropLocation location);

    KDDockWidgets::DropLocation hover(QPoint globalPos);

    /// Clears and hides drop indicators
    void removeHover();

    /// @brief returns the position of the specified drop location
    /// The return is in global coordinates
    virtual QPoint posForIndicator(DropLocation) const = 0;

    /// @brief Returns whether the specified drop indicator should be visible
    virtual bool dropIndicatorVisible(DropLocation) const;

    static KDDockWidgets::Location multisplitterLocationFor(DropLocation);

Q_SIGNALS:
    void hoveredFrameChanged(Core::Group *);
    void hoveredFrameRectChanged();
    void currentDropLocationChanged();

private:
    void onFrameDestroyed();
    void setHoveredFrameRect(QRect);
    QRect m_hoveredFrameRect;
    DropLocation m_currentDropLocation = DropLocation_None;

protected:
    virtual DropLocation hover_impl(QPoint globalPos) = 0;
    virtual void onHoveredFrameChanged(Core::Group *);
    virtual void updateVisibility()
    {
    }

    Core::Group *m_hoveredFrame = nullptr;
    Core::DropArea *const m_dropArea;
    bool m_draggedWindowIsHovering = false;
};

}

}

#endif
