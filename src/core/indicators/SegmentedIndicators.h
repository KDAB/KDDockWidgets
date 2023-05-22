/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SEGMENTED_INDICATORS_P_H
#define KD_SEGMENTED_INDICATORS_P_H

#include <kddockwidgets/NonQtCompat_p.h>
#include <kddockwidgets/core/DropIndicatorOverlay.h>

#include <QHash>

namespace KDDockWidgets {

namespace Core {

class DOCKS_EXPORT SegmentedIndicators : public DropIndicatorOverlay
{
    Q_OBJECT
public:
    explicit SegmentedIndicators(Core::DropArea *dropArea);
    ~SegmentedIndicators() override;
    DropLocation hover_impl(QPoint globalPos) override;

    DropLocation dropLocationForPos(QPoint pos) const;
    QPoint hoveredPt() const;
    QHash<DropLocation, Polygon> segments() const;

    static int s_segmentGirth;
    static int s_segmentPenWidth;
    static int s_centralIndicatorMaxWidth;
    static int s_centralIndicatorMaxHeight;
    static qreal s_draggedWindowOpacity;

protected:
    QPoint posForIndicator(DropLocation) const override;

private:
    QHash<DropLocation, Polygon> segmentsForRect(QRect, bool inner, bool useOffset = false) const;
    void updateSegments();
    QPoint m_hoveredPt = {};
    QHash<DropLocation, Polygon> m_segments;
};

}

}

#endif
