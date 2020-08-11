/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_DROPINDICATOROVERLAYINTERFACE_P_H
#define KD_DROPINDICATOROVERLAYINTERFACE_P_H

#include "docks_export.h"
#include "QWidgetAdapter.h"
#include "Frame_p.h"
#include "KDDockWidgets.h"

namespace KDDockWidgets {

class FloatingWindow;
class DropArea;

class DOCKS_EXPORT_FOR_UNIT_TESTS DropIndicatorOverlayInterface : public QWidgetAdapter
{
    Q_OBJECT
    Q_PROPERTY(QRect hoveredFrameRect READ hoveredFrameRect NOTIFY hoveredFrameRectChanged)
public:
    enum Type {
        TypeNone = 0,
        TypeClassic = 1,
        TypeAnimated = 2
    };
    Q_ENUM(Type)

    enum DropLocation {
        DropLocation_None = 0,
        DropLocation_Left,
        DropLocation_Top,
        DropLocation_Right,
        DropLocation_Bottom,
        DropLocation_Center,
        DropLocation_OutterLeft,
        DropLocation_OutterTop,
        DropLocation_OutterRight,
        DropLocation_OutterBottom
    };
    Q_ENUM(DropLocation)

    explicit DropIndicatorOverlayInterface(DropArea *dropArea);
    void setHoveredFrame(Frame *);
    void setWindowBeingDragged(const FloatingWindow *);
    QRect hoveredFrameRect() const;
    bool isHovered() const;
    DropLocation currentDropLocation() const { return m_currentDropLocation; }
    Frame *hoveredFrame() const { return m_hoveredFrame; }
    void setCurrentDropLocation(DropIndicatorOverlayInterface::DropLocation location);

    virtual Type indicatorType() const = 0;
    virtual void hover(QPoint globalPos) = 0;

    virtual QPoint posForIndicator(DropLocation) const = 0; // Used by unit-tests only

    static KDDockWidgets::Location multisplitterLocationFor(DropLocation);

Q_SIGNALS:
    void hoveredFrameChanged(KDDockWidgets::Frame *);
    void hoveredFrameRectChanged();

private:
    void onFrameDestroyed();
    void setHoveredFrameRect(QRect);
    QRect m_hoveredFrameRect;

protected:
    virtual void onHoveredFrameChanged(Frame *);
    virtual void updateVisibility() = 0;
    Frame *m_hoveredFrame = nullptr;
    DropLocation m_currentDropLocation = DropLocation_None;
    QPointer<const FloatingWindow> m_windowBeingDragged;
    DropArea *const m_dropArea;
};
}

#endif
