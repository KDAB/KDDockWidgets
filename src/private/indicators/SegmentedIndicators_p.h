/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_SEGMENTED_INDICATORS_P_H
#define KD_SEGMENTED_INDICATORS_P_H

#include "DropIndicatorOverlayInterface_p.h"

#include <QHash>
#include <QPolygon>

namespace KDDockWidgets {

class SegmentedIndicators : public DropIndicatorOverlayInterface
{
    Q_OBJECT
public:
    explicit SegmentedIndicators(DropArea *dropArea);
    ~SegmentedIndicators() override;
    Type indicatorType() const override;
    void hover_impl(QPoint globalPos) override;

    DropLocation dropLocationForPos(QPoint pos) const;

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QVector<QPolygon> segmentsForRect(QRect, QPolygon &center, bool useOffset = false) const;
    void updateSegments();
    void drawSegments(QPainter *p);
    void drawSegment(QPainter *p, const QPolygon &segment);
    QPoint m_hoveredPt = {};
    QHash<DropLocation, QPolygon> m_segments;
};

}

#endif
