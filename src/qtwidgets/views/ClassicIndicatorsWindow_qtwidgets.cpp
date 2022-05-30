/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ClassicIndicatorsWindow_qtwidgets.h"
#include "controllers/indicators/ClassicIndicators.h"
#include "private/Utils_p.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Controllers;

namespace KDDockWidgets {

class Indicator : public QWidget
{
    Q_OBJECT
public:
    typedef QList<Indicator *> List;
    explicit Indicator(Controllers::ClassicIndicators *classicIndicators, IndicatorWindow_qtwidgets *parent,
                       DropLocation location);
    void paintEvent(QPaintEvent *) override;

    void setHovered(bool hovered);
    QString iconName(bool active) const;
    QString iconFileName(bool active) const;

    QImage m_image;
    QImage m_imageActive;
    Controllers::ClassicIndicators *const q;
    bool m_hovered = false;
    const DropLocation m_dropLocation;
};

static QString iconName(DropLocation loc, bool active)
{
    QString suffix = active ? QStringLiteral("_active")
                            : QString();

    QString name;
    switch (loc) {
    case DropLocation_Center:
        name = QStringLiteral("center");
        break;
    case DropLocation_Left:
        name = QStringLiteral("inner_left");
        break;
    case DropLocation_Right:
        name = QStringLiteral("inner_right");
        break;
    case DropLocation_Bottom:
        name = QStringLiteral("inner_bottom");
        break;
    case DropLocation_Top:
        name = QStringLiteral("inner_top");
        break;
    case DropLocation_OutterLeft:
        name = QStringLiteral("outter_left");
        break;
    case DropLocation_OutterBottom:
        name = QStringLiteral("outter_bottom");
        break;
    case DropLocation_OutterRight:
        name = QStringLiteral("outter_right");
        break;
    case DropLocation_OutterTop:
        name = QStringLiteral("outter_top");
        break;
    case DropLocation_None:
    case DropLocation_Inner:
    case DropLocation_Outter:
        return QString();
    }

    return name + suffix;
}
}

#include <QPainter>

#define INDICATOR_WIDTH 40
#define OUTTER_INDICATOR_MARGIN 10

void Indicator::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    if (m_hovered)
        p.drawImage(rect(), m_imageActive, rect());
    else
        p.drawImage(rect(), m_image, rect());
}

void Indicator::setHovered(bool hovered)
{
    if (hovered != m_hovered) {
        m_hovered = hovered;
        update();
        if (hovered) {
            q->setDropLocation(m_dropLocation);
        } else if (q->currentDropLocation() == m_dropLocation) {
            q->setDropLocation(DropLocation_None);
        }
    }
}

QString Indicator::iconName(bool active) const
{
    return KDDockWidgets::iconName(m_dropLocation, active);
}

QString Indicator::iconFileName(bool active) const
{
    const QString name = iconName(active);
    return KDDockWidgets::windowManagerHasTranslucency() ? QStringLiteral(":/img/classic_indicators/%1.png").arg(name)
                                                         : QStringLiteral(":/img/classic_indicators/opaque/%1.png").arg(name);
}

static QWidget *parentForIndicatorWindow(ClassicIndicators *classicIndicators_)
{
    // On Wayland it can't be a top-level, as we have no way of positioning it

    return isWayland() ? qobject_cast<QWidget *>(classicIndicators_->view()->asQObject())
                       : nullptr;
}

static Qt::WindowFlags flagsForIndicatorWindow()
{
    return isWayland() ? Qt::Widget
                       : (Qt::Tool | Qt::BypassWindowManagerHint);
}

IndicatorWindow_qtwidgets::IndicatorWindow_qtwidgets(ClassicIndicators *classicIndicators_)
    : QWidget(parentForIndicatorWindow(classicIndicators_), flagsForIndicatorWindow())
    , classicIndicators(classicIndicators_)
    , m_center(new Indicator(classicIndicators, this, DropLocation_Center)) // Each indicator is not a top-level. Otherwise there's noticeable delay.
    , m_left(new Indicator(classicIndicators, this, DropLocation_Left))
    , m_right(new Indicator(classicIndicators, this, DropLocation_Right))
    , m_bottom(new Indicator(classicIndicators, this, DropLocation_Bottom))
    , m_top(new Indicator(classicIndicators, this, DropLocation_Top))
    , m_outterLeft(new Indicator(classicIndicators, this, DropLocation_OutterLeft))
    , m_outterRight(new Indicator(classicIndicators, this, DropLocation_OutterRight))
    , m_outterBottom(new Indicator(classicIndicators, this, DropLocation_OutterBottom))
    , m_outterTop(new Indicator(classicIndicators, this, DropLocation_OutterTop))
{
    setWindowFlag(Qt::FramelessWindowHint, true);

    if (Config::self().flags() & Config::Flag_KeepAboveIfNotUtilityWindow) {
        // Ensure the overlay window is on top
        setWindowFlag(Qt::WindowStaysOnTopHint, true);
    }

    setAttribute(Qt::WA_TranslucentBackground);

    connect(classicIndicators, &ClassicIndicators::indicatorsVisibleChanged,
            this, &IndicatorWindow_qtwidgets::updateIndicatorVisibility);
    connect(classicIndicators, &ClassicIndicators::indicatorsVisibleChanged,
            this, &IndicatorWindow_qtwidgets::updateIndicatorVisibility);

    m_indicators << m_center << m_left << m_right << m_top << m_bottom
                 << m_outterBottom << m_outterTop << m_outterLeft << m_outterRight;
}

Indicator *IndicatorWindow_qtwidgets::indicatorForLocation(DropLocation loc) const
{
    switch (loc) {
    case DropLocation_Center:
        return m_center;
    case DropLocation_Left:
        return m_left;
    case DropLocation_Right:
        return m_right;
    case DropLocation_Bottom:
        return m_bottom;
    case DropLocation_Top:
        return m_top;
    case DropLocation_OutterLeft:
        return m_outterLeft;
    case DropLocation_OutterBottom:
        return m_outterBottom;
    case DropLocation_OutterRight:
        return m_outterRight;
    case DropLocation_OutterTop:
        return m_outterTop;
    case DropLocation_None:
    case DropLocation_Outter:
    case DropLocation_Inner:
        return nullptr;
    }

    return nullptr;
}

void IndicatorWindow_qtwidgets::updateMask()
{
    QRegion region;

    if (!KDDockWidgets::windowManagerHasTranslucency()) {
        for (Indicator *indicator : qAsConst(m_indicators)) {
            if (indicator->isVisible())
                region = region.united(QRegion(indicator->geometry(), QRegion::Rectangle));
        }
    }

    setMask(region);
}

void IndicatorWindow_qtwidgets::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
    updatePositions();
}

void IndicatorWindow_qtwidgets::updateIndicatorVisibility()
{
    for (Indicator *indicator : { m_left, m_right, m_bottom, m_top,
                                  m_outterTop, m_outterLeft, m_outterRight, m_outterBottom,
                                  m_center })
        indicator->setVisible(classicIndicators->dropIndicatorVisible(indicator->m_dropLocation));

    updateMask();
}

QPoint IndicatorWindow_qtwidgets::posForIndicator(DropLocation loc) const
{
    Indicator *indicator = indicatorForLocation(loc);
    return indicator->mapToGlobal(indicator->rect().center());
}

DropLocation IndicatorWindow_qtwidgets::hover(QPoint globalPos)
{
    DropLocation loc = DropLocation_None;

    for (Indicator *indicator : qAsConst(m_indicators)) {
        if (indicator->isVisible()) {
            const bool hovered = indicator->rect().contains(indicator->mapFromGlobal(globalPos));
            indicator->setHovered(hovered);
            if (hovered)
                loc = indicator->m_dropLocation;
        }
    }

    return loc;
}

void IndicatorWindow_qtwidgets::updatePositions()
{
    QRect r = rect();
    const int indicatorWidth = m_outterBottom->width();
    const int halfIndicatorWidth = m_outterBottom->width() / 2;

    m_outterLeft->move(r.x() + OUTTER_INDICATOR_MARGIN, r.center().y() - halfIndicatorWidth);
    m_outterBottom->move(r.center().x() - halfIndicatorWidth, r.y() + height() - indicatorWidth - OUTTER_INDICATOR_MARGIN);
    m_outterTop->move(r.center().x() - halfIndicatorWidth, r.y() + OUTTER_INDICATOR_MARGIN);
    m_outterRight->move(r.x() + width() - indicatorWidth - OUTTER_INDICATOR_MARGIN, r.center().y() - halfIndicatorWidth);
    Controllers::Frame *hoveredFrame = classicIndicators->hoveredFrame();
    if (hoveredFrame) {
        QRect hoveredRect = hoveredFrame->view()->geometry();
        m_center->move(r.topLeft() + hoveredRect.center() - QPoint(halfIndicatorWidth, halfIndicatorWidth));
        m_top->move(m_center->pos() - QPoint(0, indicatorWidth + OUTTER_INDICATOR_MARGIN));
        m_right->move(m_center->pos() + QPoint(indicatorWidth + OUTTER_INDICATOR_MARGIN, 0));
        m_bottom->move(m_center->pos() + QPoint(0, indicatorWidth + OUTTER_INDICATOR_MARGIN));
        m_left->move(m_center->pos() - QPoint(indicatorWidth + OUTTER_INDICATOR_MARGIN, 0));
    }
}

void IndicatorWindow_qtwidgets::raise()
{
    QWidget::raise();
}

void IndicatorWindow_qtwidgets::setGeometry(QRect rect)
{
    QWidget::setGeometry(rect);
}

void IndicatorWindow_qtwidgets::setObjectName(const QString &name)
{
    QWidget::setObjectName(name);
}

void IndicatorWindow_qtwidgets::setVisible(bool is)
{
    QWidget::setVisible(is);
}

void IndicatorWindow_qtwidgets::resize(QSize size)
{
    QWidget::resize(size);
}

bool IndicatorWindow_qtwidgets::isWindow() const
{
    return QWidget::isWindow();
}

Indicator::Indicator(ClassicIndicators *classicIndicators, IndicatorWindow_qtwidgets *parent, DropLocation location)
    : QWidget(parent)
    , q(classicIndicators)
    , m_dropLocation(location)
{
    m_image = QImage(iconFileName(/*active=*/false)).scaled(INDICATOR_WIDTH, INDICATOR_WIDTH);
    m_imageActive = QImage(iconFileName(/*active=*/true)).scaled(INDICATOR_WIDTH, INDICATOR_WIDTH);
    setFixedSize(m_image.size());
    setVisible(true);
}

#include "ClassicIndicatorsWindow_qtwidgets.moc"
