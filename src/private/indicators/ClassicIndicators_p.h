/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_INDICATORS_CLASSICINDICATORS_P_H
#define KD_INDICATORS_CLASSICINDICATORS_P_H

#include "DropIndicatorOverlayInterface_p.h"

namespace KDDockWidgets {

class IndicatorWindow;
class Indicator;

class ClassicIndicators : public DropIndicatorOverlayInterface
{
    Q_OBJECT
public:
    explicit ClassicIndicators(DropArea *dropArea);
    ~ClassicIndicators() override;
    Type indicatorType() const override;
    void hover(QPoint globalPos) override;
    QPoint posForIndicator(DropLocation) const override;
protected:
    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void updateVisibility() override;
private:
    friend class KDDockWidgets::Indicator;
    friend class KDDockWidgets::IndicatorWindow;
    void raiseIndicators();
    void setDropLocation(DropLocation);
    QRect geometryForRubberband(QRect localRect) const;
    bool rubberBandIsTopLevel() const;

    QWidgetOrQuick *const m_rubberBand;
    IndicatorWindow *const m_indicatorWindow;
};

class IndicatorWindow : public QWidget
{
    Q_OBJECT
public:
    explicit IndicatorWindow(ClassicIndicators *classicIndicators, QWidget * = nullptr);
    void hover(QPoint globalPos);

    void updatePosition();
    void updatePositions();
    void updateIndicatorVisibility(bool visible);
    void resizeEvent(QResizeEvent *ev) override;
    bool event(QEvent *e) override;

    Indicator *indicatorForLocation(DropIndicatorOverlayInterface::DropLocation loc) const;

    // When the compositor doesn't support translucency, we use a mask instead
    // Only happens on Linux
    void updateMask();

    ClassicIndicators *const classicIndicators;
    Indicator *const m_center;
    Indicator *const m_left;
    Indicator *const m_right;
    Indicator *const m_bottom;
    Indicator *const m_top;
    Indicator *const m_outterLeft;
    Indicator *const m_outterRight;
    Indicator *const m_outterBottom;
    Indicator *const m_outterTop;
    QVector<Indicator *> m_indicators;
};

class Indicator : public QWidget
{
    Q_OBJECT
public:
    typedef QList<Indicator *> List;
    explicit Indicator(ClassicIndicators *classicIndicators, IndicatorWindow *parent, ClassicIndicators::DropLocation location);
    void paintEvent(QPaintEvent *) override;

    void setHovered(bool hovered);
    QString iconName(bool active) const;
    QString iconFileName(bool active) const;

    QImage m_image;
    QImage m_imageActive;
    ClassicIndicators *const q;
    bool m_hovered = false;
    const ClassicIndicators::DropLocation m_dropLocation;
};

}

#endif
