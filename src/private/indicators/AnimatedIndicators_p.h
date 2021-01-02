/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_INDICATORS_ANIMATEDINDICATORS_P_H
#define KD_INDICATORS_ANIMATEDINDICATORS_P_H

#include "DropIndicatorOverlayInterface_p.h"

#include <QRubberBand>
#include <QList>
#include <QPropertyAnimation>

namespace KDDockWidgets {

class Anchor;
class AnimatedIndicators;

class AnimatedRubberBand : public QRubberBand
{
    Q_OBJECT
    Q_PROPERTY(QVariant length READ length WRITE setLength) // clazy:exclude=qproperty-without-notify
public:
    typedef QList<AnimatedRubberBand *> List;
    explicit AnimatedRubberBand(DropIndicatorOverlayInterface::DropLocation, AnimatedIndicators *parent = nullptr);

    virtual void animatedInitialShow() = 0;
    virtual void animatedInflate() = 0;
    virtual void animatedDeflate() = 0;
    virtual void animatedHide() = 0;
    virtual void resetGeometry() = 0;
    virtual void onHoveredFrameChanged(Frame *) = 0;
    virtual void setLength(const QVariant &) = 0;
    virtual void updatePosition() = 0;
    virtual QVariant length() const = 0;

    bool hover(QPoint globalPos);
Q_SIGNALS:
    void animationFinished();
    void hidden();
    void hovered();
    void notHovered();
    void positionChanged(int);

public:
    void setLengthAnimated(const QVariant &value);
    bool inflated = false;
    const DropIndicatorOverlayInterface::DropLocation dropLocation;
    QPropertyAnimation animation;
    AnimatedIndicators *const q;
    QPointer<Frame> hoveredFrame;
};

class AnimatedOutterRubberBand  : public AnimatedRubberBand
{
    Q_OBJECT
public:
    explicit AnimatedOutterRubberBand(Qt::Orientation orientation, DropIndicatorOverlayInterface::DropLocation, AnimatedIndicators *parent = nullptr);
    void setAnchor(Anchor *);
    QVariant length() const override;
    void setLength(const QVariant &) override;
    void updateAnchorOffset();

    void animatedInitialShow() override;
    void animatedInflate() override;
    void animatedDeflate() override;
    void animatedHide() override;
    void resetGeometry() override;
    void onHoveredFrameChanged(Frame *) override {}
    void updatePosition() override;
public:
    void paintEvent(QPaintEvent *) override;
    const Qt::Orientation orientation;
    Anchor *anchor = nullptr;
};

class AnimatedInnerRubberBand : public AnimatedOutterRubberBand
{
    Q_OBJECT
public:
    explicit AnimatedInnerRubberBand(Qt::Orientation orientation,
                                     DropIndicatorOverlayInterface::DropLocation location,
                                     AnimatedIndicators *parent = nullptr);

    ~AnimatedInnerRubberBand() override;
};

class AnimatedCenterRubberBand : public AnimatedRubberBand
{
    Q_OBJECT
public:
    explicit AnimatedCenterRubberBand(AnimatedIndicators *parent = nullptr);
    void recenter();
    void animatedInitialShow() override;
    void animatedInflate() override;
    void animatedDeflate() override;
    void animatedHide() override;
    void resetGeometry() override;
    void onHoveredFrameChanged(Frame *) override;
    void setLength(const QVariant &v) override;
    QVariant length() const override;
    void updatePosition() override;
};

class AnimatedIndicators : public DropIndicatorOverlayInterface
{
    Q_OBJECT
public:
    explicit AnimatedIndicators(DropArea *dropArea);

    Type indicatorType() const override;
    void hover(QPoint globalPos) override;
    void updateVisibility() override;
    void updateRubberBandPositions();
    bool allRubberBandsAreHidden() const;
    QPoint posForIndicator(DropLocation) const override;
Q_SIGNALS:
    void hovered();
    void notHovered();
private:
    friend class AnimationState_None;
    friend class AnimationStateBase;
    void onHoveredFrameChanged(Frame *) override;
    AnimatedOutterRubberBand *const m_outterLeftRubberBand;
    AnimatedOutterRubberBand *const m_outterRightRubberBand;
    AnimatedOutterRubberBand *const m_outterTopRubberBand;
    AnimatedOutterRubberBand *const m_outterBottomRubberBand;
    AnimatedCenterRubberBand *const m_centerRubberBand;
    AnimatedInnerRubberBand *const m_innerLeftRubberBand;
    AnimatedInnerRubberBand *const m_innerRightRubberBand;
    AnimatedInnerRubberBand *const m_innerTopRubberBand;
    AnimatedInnerRubberBand *const m_innerBottomRubberBand;

    AnimatedRubberBand::List m_rubberBands;
};
}

#endif
