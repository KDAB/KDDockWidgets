/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "AnimatedIndicators_p.h"
#include "DropArea_p.h"

#include <QPainter>
#include <QPainterPath>

#define RUBBERBAND_LENGTH 11
#define RUBBERBAND_SPACING 2
#define INFLATED_RUBBERBAND_LENGTH 60
#define CENTER_RUBBERBAND_LENGTH 200
#define CENTER_RUBBERBAND_SIZE QSize(CENTER_RUBBERBAND_LENGTH, CENTER_RUBBERBAND_LENGTH)

#define INFLATED_CENTER_RUBBERBAND_LENGTH 300
#define INFLATED_CENTER_RUBBERBAND_SIZE QSize(INFLATED_CENTER_RUBBERBAND_LENGTH, INFLATED_CENTER_RUBBERBAND_LENGTH)

using namespace KDDockWidgets;

namespace KDDockWidgets {

class AnimationStateBase : public QState
{
    Q_OBJECT
public:
    AnimationStateBase(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : QState(parent)
        , rubberBand(band)
        , q(qq)
    {
    }

    ~AnimationStateBase() override;

    AnimatedRubberBand *const rubberBand;
    AnimatedIndicators *const q;
};

AnimationStateBase::~AnimationStateBase() {}

class AnimationState_None : public AnimationStateBase
{
    // In this state no rubber band is shown
    Q_OBJECT
public:
    explicit AnimationState_None(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }

    ~AnimationState_None() override;

    void onEntry(QEvent *) override
    {
        rubberBand->hide();
        Q_EMIT rubberBand->hidden();
    }
};

AnimationState_None::~AnimationState_None() {}

class AnimationState_AnimateShow : public AnimationStateBase
{
    // In this state we show the rubber bands and start animating them
    Q_OBJECT
public:
    explicit AnimationState_AnimateShow(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }

    ~AnimationState_AnimateShow() override;

    void onEntry(QEvent *) override
    {
        rubberBand->resetGeometry();
        rubberBand->show();
        rubberBand->animatedInitialShow();
    }
};

AnimationState_AnimateShow::~AnimationState_AnimateShow() {}

class AnimationState_ShowingRubberBands : public AnimationStateBase
{
    Q_OBJECT
public:
    explicit AnimationState_ShowingRubberBands(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }

    ~AnimationState_ShowingRubberBands() override;

    void onEntry(QEvent *) override
    {
    }
};

AnimationState_ShowingRubberBands::~AnimationState_ShowingRubberBands() {}


class AnimationState_AnimateHide : public AnimationStateBase
{
    Q_OBJECT
public:
    explicit AnimationState_AnimateHide(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }
    ~AnimationState_AnimateHide() override;
    void onEntry(QEvent *) override
    {
        rubberBand->animatedHide();
    }
};

AnimationState_AnimateHide::~AnimationState_AnimateHide() {}

class AnimationState_AnimateInflate : public AnimationStateBase
{
    // In this state we show the rubber bands and start animating them
    Q_OBJECT
public:
    explicit AnimationState_AnimateInflate(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }

    ~AnimationState_AnimateInflate() override;
    void onEntry(QEvent *) override
    {
        rubberBand->animatedInflate();
    }
};

AnimationState_AnimateInflate::~AnimationState_AnimateInflate() {}

class AnimationState_Inflated : public AnimationStateBase
{
    // In this state we show the rubber bands and start animating them
    Q_OBJECT
public:
    explicit AnimationState_Inflated(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }
    ~AnimationState_Inflated() override;
    void onEntry(QEvent *) override
    {
    }
};

AnimationState_Inflated::~AnimationState_Inflated() {}

class AnimationState_AnimateDeflate : public AnimationStateBase
{
    Q_OBJECT
public:
    explicit AnimationState_AnimateDeflate(AnimatedIndicators *qq, AnimatedRubberBand *band, QState *parent)
        : AnimationStateBase(qq, band, parent)
    {
    }
    ~AnimationState_AnimateDeflate() override;
    void onEntry(QEvent *) override
    {
        rubberBand->animatedDeflate();
    }
};

AnimationState_AnimateDeflate::~AnimationState_AnimateDeflate() {}

}

AnimatedRubberBand::AnimatedRubberBand(DropIndicatorOverlayInterface::DropLocation location, AnimatedIndicators *qq)
    : QRubberBand(QRubberBand::Rectangle, qq)
    , dropLocation(location)
    , animation(this)
    , q(qq)
{
    animation.setTargetObject(this);
    animation.setDuration(500);
    animation.setEasingCurve(QEasingCurve::OutBack);

    auto stateMachine = new QStateMachine(this);
    auto stateNone = new AnimationState_None(q, this, stateMachine);
    auto stateAnimatedShow = new AnimationState_AnimateShow(q, this, stateMachine);
    auto stateShowingRubberBand = new AnimationState_ShowingRubberBands(q, this, stateMachine);
    auto stateAnimateHide = new AnimationState_AnimateHide(q, this, stateMachine);
    auto stateAnimateInflate = new AnimationState_AnimateInflate(q, this, stateMachine);
    auto stateAnimateInflated = new AnimationState_Inflated(q, this, stateMachine);
    auto stateAnimateDeflate = new AnimationState_AnimateDeflate(q, this, stateMachine);

    connect(q, &AnimatedIndicators::hoveredFrameChanged, this, &AnimatedRubberBand::onHoveredFrameChanged);

    // -> animate show
    stateNone->addTransition(q, &AnimatedIndicators::hovered, stateAnimatedShow);
    stateAnimateHide->addTransition(q, &AnimatedIndicators::hovered, stateAnimatedShow);

    // -> showing rubber band
    stateAnimatedShow->addTransition(&animation, &QPropertyAnimation::finished, stateShowingRubberBand);
    stateAnimateDeflate->addTransition(&animation, &QPropertyAnimation::finished, stateShowingRubberBand);

    // -> animate hide
    stateAnimatedShow->addTransition(q, &AnimatedIndicators::notHovered, stateAnimateHide);
    stateShowingRubberBand->addTransition(q, &AnimatedIndicators::notHovered, stateAnimateHide);
    stateAnimateInflate->addTransition(q, &AnimatedIndicators::notHovered, stateAnimateHide);
    stateAnimateDeflate->addTransition(q, &AnimatedIndicators::notHovered, stateAnimateHide);
    stateAnimateInflated->addTransition(q, &AnimatedIndicators::notHovered, stateAnimateHide);

    // -> none
    stateAnimateHide->addTransition(&animation, &QPropertyAnimation::finished, stateNone);

    // -> animate inflate
    stateAnimatedShow->addTransition(this, &AnimatedRubberBand::hovered, stateAnimateInflate);
    stateShowingRubberBand->addTransition(this, &AnimatedRubberBand::hovered, stateAnimateInflate);
    stateAnimateHide->addTransition(this, &AnimatedRubberBand::hovered, stateAnimateInflate);
    stateNone->addTransition(this, &AnimatedRubberBand::hovered, stateAnimateInflate);

    // -> inflated
    stateAnimateInflate->addTransition(&animation, &QPropertyAnimation::finished, stateAnimateInflated);

    // -> animate deflate
    stateAnimateInflate->addTransition(this, &AnimatedRubberBand::notHovered, stateAnimateDeflate);
    stateAnimateInflated->addTransition(this, &AnimatedRubberBand::notHovered, stateAnimateDeflate);


    stateMachine->setInitialState(stateNone);
    stateMachine->start();
}

bool AnimatedRubberBand::hover(QPoint globalPos)
{
    const bool containsMouse = rect().contains(mapFromGlobal(globalPos));
    if (containsMouse) {
        Q_EMIT hovered();
        return true;
    } else {
        Q_EMIT notHovered();
        return false;
    }
}

void AnimatedRubberBand::setLengthAnimated(const QVariant &value)
{
    animation.setStartValue(length());
    animation.setEndValue(value);
    animation.start();
}

AnimatedIndicators::AnimatedIndicators(DropArea *dropArea)
    : DropIndicatorOverlayInterface(dropArea)
    , m_outterLeftRubberBand(new AnimatedOutterRubberBand(Qt::Vertical, DropIndicatorOverlayInterface::DropLocation_OutterLeft, this))
    , m_outterRightRubberBand(new AnimatedOutterRubberBand(Qt::Vertical, DropIndicatorOverlayInterface::DropLocation_OutterRight, this))
    , m_outterTopRubberBand(new AnimatedOutterRubberBand(Qt::Horizontal, DropIndicatorOverlayInterface::DropLocation_OutterTop, this))
    , m_outterBottomRubberBand(new AnimatedOutterRubberBand(Qt::Horizontal, DropIndicatorOverlayInterface::DropLocation_OutterBottom, this))
    , m_centerRubberBand(new AnimatedCenterRubberBand(this))
    , m_innerLeftRubberBand(new AnimatedInnerRubberBand(Qt::Vertical, DropIndicatorOverlayInterface::DropLocation_Left, this))
    , m_innerRightRubberBand(new AnimatedInnerRubberBand(Qt::Vertical, DropIndicatorOverlayInterface::DropLocation_Right, this))
    , m_innerTopRubberBand(new AnimatedInnerRubberBand(Qt::Horizontal, DropIndicatorOverlayInterface::DropLocation_Top, this))
    , m_innerBottomRubberBand(new AnimatedInnerRubberBand(Qt::Horizontal, DropIndicatorOverlayInterface::DropLocation_Bottom, this))
{
    m_rubberBands << m_outterLeftRubberBand << m_outterRightRubberBand
                  << m_outterTopRubberBand << m_outterBottomRubberBand
                  << m_centerRubberBand << m_innerLeftRubberBand << m_innerRightRubberBand
                  << m_innerTopRubberBand << m_innerBottomRubberBand;

    for (auto rubberBand : qAsConst(m_rubberBands)) {
        connect(rubberBand, &AnimatedRubberBand::positionChanged, this, &AnimatedIndicators::updateRubberBandPositions);
        connect(rubberBand, &AnimatedRubberBand::hidden, this, [this] {
            if (allRubberBandsAreHidden()) {
                setVisible(false);
            }
        });
    }

    auto group = dropArea->multiSplitterLayout()->staticAnchorGroup();
    m_outterLeftRubberBand->setAnchor(group.left);
    m_outterRightRubberBand->setAnchor(group.right);
    m_outterTopRubberBand->setAnchor(group.top);
    m_outterBottomRubberBand->setAnchor(group.bottom);
}

DropIndicatorOverlayInterface::Type AnimatedIndicators::indicatorType() const
{
    return TypeAnimated;
}

void AnimatedIndicators::hover(QPoint globalPos)
{
    setCurrentDropLocation(DropIndicatorOverlayInterface::DropLocation_None);
    for (auto rubberBand : qAsConst(m_rubberBands)) {
        if (rubberBand->hover(globalPos)) {
            setCurrentDropLocation(rubberBand->dropLocation);
        }
    }
}

void AnimatedIndicators::updateVisibility()
{
    const bool visible = isHovered();

    if (!isVisible() && visible) {
        updateRubberBandPositions();
        setVisible(true);
    } // visibility is set to false when animation ends

    if (visible) {
        Q_EMIT hovered();
    } else {
        Q_EMIT notHovered();
    }
}

void AnimatedIndicators::updateRubberBandPositions()
{
    for (auto rubberBand : qAsConst(m_rubberBands)) {
        rubberBand->updatePosition();
    }
}

bool AnimatedIndicators::allRubberBandsAreHidden() const
{
    for (auto rubberBand : m_rubberBands) {
        if (rubberBand->isVisible())
            return false;
    }
    return true;
}

QPoint AnimatedIndicators::posForIndicator(DropIndicatorOverlayInterface::DropLocation) const
{
    // TODO: This is only used by unit-tests, and we're not testing AnimatedIndicators yet, only Classical.
    return QPoint();
}

void AnimatedIndicators::onHoveredFrameChanged(Frame *frame)
{
    if (frame) {
        Item *item = m_dropArea->multiSplitterLayout()->itemForFrame(frame);
        AnchorGroup group = item->anchorGroup();
        Q_ASSERT(group.isValid());

        if (!group.bottom->isStatic())
            m_innerBottomRubberBand->setAnchor(group.bottom);

        if (!group.top->isStatic())
            m_innerTopRubberBand->setAnchor(group.top);

        if (!group.left->isStatic())
            m_innerLeftRubberBand->setAnchor(group.left);

        if (!group.right->isStatic())
            m_innerRightRubberBand->setAnchor(group.right);

    } else {
        m_innerBottomRubberBand->setAnchor(nullptr);
        m_innerTopRubberBand->setAnchor(nullptr);
        m_innerLeftRubberBand->setAnchor(nullptr);
        m_innerRightRubberBand->setAnchor(nullptr);
    }
}

AnimatedCenterRubberBand::AnimatedCenterRubberBand(AnimatedIndicators *parent)
    : AnimatedRubberBand(DropIndicatorOverlayInterface::DropLocation_Center, parent)
{
    connect(q, &AnimatedIndicators::hoveredFrameChanged, this, [this] (Frame *f) {
        hoveredFrame = f;
    });
    animation.setPropertyName("length"); // delayed, since the getters are virtual
}

void AnimatedCenterRubberBand::animatedInitialShow()
{
    setLength(CENTER_RUBBERBAND_SIZE);
}

void AnimatedCenterRubberBand::animatedInflate()
{
    setLengthAnimated(INFLATED_CENTER_RUBBERBAND_SIZE);
}

void AnimatedCenterRubberBand::animatedDeflate()
{
    setLengthAnimated(CENTER_RUBBERBAND_SIZE);
}

void AnimatedCenterRubberBand::animatedHide()
{
    // It's not animated.
    resetGeometry();
    hide();
}

void AnimatedCenterRubberBand::resetGeometry()
{
    setLength(CENTER_RUBBERBAND_SIZE);
}

void AnimatedCenterRubberBand::onHoveredFrameChanged(Frame *frame)
{
    if (hoveredFrame != frame) {
        hoveredFrame = frame;
        recenter();
    }
}

void AnimatedCenterRubberBand::setLength(const QVariant &v)
{
    resize(v.toSize());
    recenter();
}

QVariant AnimatedCenterRubberBand::length() const
{
    return size();
}

void AnimatedCenterRubberBand::updatePosition()
{
    recenter();
}

void AnimatedCenterRubberBand::recenter()
{
    if (hoveredFrame) {
        QRect geo = geometry();
        geo.moveCenter(hoveredFrame->geometry().center());
        setGeometry(geo);
    }
}

AnimatedOutterRubberBand::AnimatedOutterRubberBand(Qt::Orientation orient,
                                                   DropIndicatorOverlayInterface::DropLocation location,
                                                   AnimatedIndicators *parent_)
    : AnimatedRubberBand(location, parent_)
    , orientation(orient)
{
    animation.setPropertyName("length"); // delayed, since the getters are virtual
}

void AnimatedOutterRubberBand::animatedInitialShow()
{
    setLengthAnimated(RUBBERBAND_LENGTH);
}

void AnimatedOutterRubberBand::animatedInflate()
{
    setLengthAnimated(INFLATED_RUBBERBAND_LENGTH);
}

void AnimatedOutterRubberBand::animatedDeflate()
{
    setLengthAnimated(RUBBERBAND_LENGTH);
}

void AnimatedOutterRubberBand::animatedHide()
{
    setLengthAnimated(0);
}

void AnimatedOutterRubberBand::resetGeometry()
{
    setLength(0);
    updateAnchorOffset();
}

void AnimatedOutterRubberBand::updatePosition()
{
    /*auto group = m_dropArea->staticAnchorGroup();
    auto leftAnchorGeo = group.left->geometry();
    auto rightAnchorGeo = group.right->geometry();
    auto topAnchorGeo = group.top->geometry();
    auto bottomAnchorGeo = group.bottom->geometry();

    QRect newTopGeo = QRect(topAnchorGeo.x(), topAnchorGeo.bottom(), width(), m_outterTopRubberBand->height());
    m_outterTopRubberBand->setGeometry(newTopGeo);
    m_outterBottomRubberBand->setGeometry(bottomAnchorGeo.x(), bottomAnchorGeo.y() - m_outterBottomRubberBand->height() + RUBBERBAND_SPACING, width(), m_outterBottomRubberBand->height());
    m_outterLeftRubberBand->setGeometry(leftAnchorGeo.right(), m_outterTopRubberBand->geometry().bottom() + RUBBERBAND_SPACING, m_outterLeftRubberBand->width(), height() - 2*RUBBERBAND_SPACING - m_outterBottomRubberBand->height() - m_outterTopRubberBand->height());
    m_outterRightRubberBand->setGeometry(rightAnchorGeo.right() - m_outterRightRubberBand->width() + RUBBERBAND_SPACING, m_outterTopRubberBand->geometry().bottom() + RUBBERBAND_SPACING, m_outterRightRubberBand->width(), height() - 2*RUBBERBAND_SPACING - m_outterBottomRubberBand->height() - m_outterTopRubberBand->height());*/
}

QVariant AnimatedOutterRubberBand::length() const
{
    return orientation == Qt::Vertical ? width() : height();
}

void AnimatedOutterRubberBand::setLength(const QVariant &value)
{
    if (value != length()) {
        if (orientation == Qt::Vertical) {
            resize(value.toInt(), height());
        } else {
            resize(width(), value.toInt());
        }
        Q_EMIT positionChanged(value.toInt());
        updateAnchorOffset();
    }
}

void AnimatedOutterRubberBand::setAnchor(Anchor *a)
{
    if (a != anchor) {
        this->anchor = a;
        updateAnchorOffset();
    }
}

void AnimatedOutterRubberBand::updateAnchorOffset()
{
    if (anchor) {
        if (isVisible()) {
            anchor->setPositionOffset(length().toInt());
        } else {
            anchor->setPositionOffset(0);
        }
    }
}

void AnimatedOutterRubberBand::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    const int t = length().toInt();
    p.setOpacity(-(0.0007625272331 * t * t) + (0.06241830065 * t));
    QPainterPath path;
    p.setPen(QPen(QColor(0xf6, 0x47, 0x6b, 0xae)));

    QRectF r = rect();
    if (orientation == Qt::Vertical) {
        r = r.adjusted(0.5, 0.5, -RUBBERBAND_SPACING - 0.5, -0.5);
    } else {
        r = r.adjusted(0.5, 0.5, -0.5, -RUBBERBAND_SPACING - 0.5);
    }

    path.addRoundedRect(r, 3, 3);
    p.fillPath(path, QColor(0x39, 0x34, 0x47, 0x6f));
    p.setRenderHint(QPainter::Antialiasing);
    p.drawPath(path);
}

AnimatedInnerRubberBand::AnimatedInnerRubberBand(Qt::Orientation orient,
                                                 DropIndicatorOverlayInterface::DropLocation location,
                                                 AnimatedIndicators *parent_)
    : AnimatedOutterRubberBand(orient, location, parent_)
{

}

AnimatedInnerRubberBand::~AnimatedInnerRubberBand()
{
}

#include <AnimatedIndicators.moc>
