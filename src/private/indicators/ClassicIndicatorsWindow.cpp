/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ClassicIndicatorsWindow_p.h"
#include "ClassicIndicators_p.h"
#include "Utils_p.h"

using namespace KDDockWidgets;

namespace KDDockWidgets
{

static QString iconName(DropIndicatorOverlayInterface::DropLocation loc, bool active)
{
    QString suffix = active ? QStringLiteral("_active")
                            : QString();

    QString name;
    switch (loc) {
    case DropIndicatorOverlayInterface::DropLocation_Center:
        name = QStringLiteral("center");
        break;
    case DropIndicatorOverlayInterface::DropLocation_Left:
        name = QStringLiteral("inner_left");
        break;
    case DropIndicatorOverlayInterface::DropLocation_Right:
        name = QStringLiteral("inner_right");
        break;
    case DropIndicatorOverlayInterface::DropLocation_Bottom:
        name = QStringLiteral("inner_bottom");
        break;
    case DropIndicatorOverlayInterface::DropLocation_Top:
        name = QStringLiteral("inner_top");
        break;
    case DropIndicatorOverlayInterface::DropLocation_OutterLeft:
        name = QStringLiteral("outter_left");
        break;
    case DropIndicatorOverlayInterface::DropLocation_OutterBottom:
        name = QStringLiteral("outter_bottom");
        break;
    case DropIndicatorOverlayInterface::DropLocation_OutterRight:
        name = QStringLiteral("outter_right");
        break;
    case DropIndicatorOverlayInterface::DropLocation_OutterTop:
        name = QStringLiteral("outter_top");
        break;
    case DropIndicatorOverlayInterface::DropLocation_None:
        return QString();
    }

    return name + suffix;
}
}

#ifdef KDDOCKWIDGETS_QTWIDGETS

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
            q->setDropLocation(DropIndicatorOverlayInterface::DropLocation_None);
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

IndicatorWindow::IndicatorWindow(ClassicIndicators *classicIndicators_)
    : QWidget(nullptr, Qt::Tool | Qt::BypassWindowManagerHint)
    , classicIndicators(classicIndicators_)
    , m_center(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_Center)) // Each indicator is not a top-level. Otherwise there's noticeable delay.
    , m_left(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_Left))
    , m_right(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_Right))
    , m_bottom(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_Bottom))
    , m_top(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_Top))
    , m_outterLeft(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_OutterLeft))
    , m_outterRight(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_OutterRight))
    , m_outterBottom(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_OutterBottom))
    , m_outterTop(new Indicator(classicIndicators, this, DropIndicatorOverlayInterface::DropLocation_OutterTop))
{
    setWindowFlag(Qt::FramelessWindowHint, true);
    setAttribute(Qt::WA_TranslucentBackground);

    connect(classicIndicators, &ClassicIndicators::innerIndicatorsVisibleChanged,
            this, &IndicatorWindow::updateIndicatorVisibility);
    connect(classicIndicators, &ClassicIndicators::outterIndicatorsVisibleChanged,
            this, &IndicatorWindow::updateIndicatorVisibility);

    m_indicators << m_center << m_left << m_right << m_top << m_bottom
                 << m_outterBottom << m_outterTop << m_outterLeft << m_outterRight;
}

Indicator *IndicatorWindow::indicatorForLocation(DropIndicatorOverlayInterface::DropLocation loc) const
{
    switch (loc) {
    case DropIndicatorOverlayInterface::DropLocation_Center:
        return m_center;
    case DropIndicatorOverlayInterface::DropLocation_Left:
        return m_left;
    case DropIndicatorOverlayInterface::DropLocation_Right:
        return m_right;
    case DropIndicatorOverlayInterface::DropLocation_Bottom:
        return m_bottom;
    case DropIndicatorOverlayInterface::DropLocation_Top:
        return m_top;
    case DropIndicatorOverlayInterface::DropLocation_OutterLeft:
        return m_outterLeft;
    case DropIndicatorOverlayInterface::DropLocation_OutterBottom:
        return m_outterBottom;
    case DropIndicatorOverlayInterface::DropLocation_OutterRight:
        return m_outterRight;
    case DropIndicatorOverlayInterface::DropLocation_OutterTop:
        return m_outterTop;
    case DropIndicatorOverlayInterface::DropLocation_None:
        return nullptr;
    }

    return nullptr;
}

void IndicatorWindow::updateMask()
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

void IndicatorWindow::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
    updatePositions();
}

void IndicatorWindow::updateIndicatorVisibility()
{
    for (Indicator *indicator : { m_center, m_left, m_right, m_bottom, m_top })
        indicator->setVisible(classicIndicators->innerIndicatorsVisible());

    for (Indicator *indicator : { m_outterTop, m_outterLeft, m_outterRight, m_outterBottom })
        indicator->setVisible(classicIndicators->outterIndicatorsVisible());

    updateMask();
}

QPoint IndicatorWindow::posForIndicator(DropIndicatorOverlayInterface::DropLocation loc) const
{
    Indicator *indicator = indicatorForLocation(loc);
    return indicator->mapToGlobal(indicator->rect().center());
}

void IndicatorWindow::hover(QPoint globalPos)
{
    for (Indicator *indicator : qAsConst(m_indicators)) {
        if (indicator->isVisible())
            indicator->setHovered(indicator->rect().contains(indicator->mapFromGlobal(globalPos)));
    }
}

void IndicatorWindow::updatePositions()
{
    QRect r = rect();
    const int indicatorWidth = m_outterBottom->width();
    const int halfIndicatorWidth = m_outterBottom->width() / 2;

    m_outterLeft->move(r.x() + OUTTER_INDICATOR_MARGIN, r.center().y() - halfIndicatorWidth);
    m_outterBottom->move(r.center().x() - halfIndicatorWidth, r.y() + height() - indicatorWidth - OUTTER_INDICATOR_MARGIN);
    m_outterTop->move(r.center().x() - halfIndicatorWidth, r.y() + OUTTER_INDICATOR_MARGIN);
    m_outterRight->move(r.x() + width() - indicatorWidth - OUTTER_INDICATOR_MARGIN, r.center().y() - halfIndicatorWidth);
    Frame *hoveredFrame = classicIndicators->m_hoveredFrame;
    if (hoveredFrame) {
        QRect hoveredRect = hoveredFrame->QWidget::geometry();
        m_center->move(r.topLeft() + hoveredRect.center() - QPoint(halfIndicatorWidth, halfIndicatorWidth));
        m_top->move(m_center->pos() - QPoint(0, indicatorWidth + OUTTER_INDICATOR_MARGIN));
        m_right->move(m_center->pos() + QPoint(indicatorWidth + OUTTER_INDICATOR_MARGIN, 0));
        m_bottom->move(m_center->pos() + QPoint(0, indicatorWidth + OUTTER_INDICATOR_MARGIN));
        m_left->move(m_center->pos() - QPoint(indicatorWidth + OUTTER_INDICATOR_MARGIN, 0));
    }
}

Indicator::Indicator(ClassicIndicators *classicIndicators, IndicatorWindow *parent, ClassicIndicators::DropLocation location)
    : QWidget(parent)
    , q(classicIndicators)
    , m_dropLocation(location)
{
    m_image = QImage(iconFileName(/*active=*/ false)).scaled(INDICATOR_WIDTH, INDICATOR_WIDTH);
    m_imageActive = QImage(iconFileName(/*active=*/ true)).scaled(INDICATOR_WIDTH, INDICATOR_WIDTH);
    setFixedSize(m_image.size());
    setVisible(true);
}

#else

#include <QQmlContext>

IndicatorWindow::IndicatorWindow(KDDockWidgets::ClassicIndicators *classicIndicators)
    : QQuickView()
    , m_classicIndicators(classicIndicators)
{
    setColor(Qt::transparent);
    setFlags(flags() | Qt::FramelessWindowHint);
    rootContext()->setContextProperty(QStringLiteral("_window"), QVariant::fromValue<QObject*>(this));
    setSource(QUrl(QStringLiteral("qrc:/kddockwidgets/private/quick/qml/ClassicIndicatorsOverlay.qml")));
}

void IndicatorWindow::hover(QPoint pt)
{
    qDebug() << "Hover" << pt;
}

void IndicatorWindow::updatePositions()
{
    qDebug() << "updatePositions";
}

QPoint IndicatorWindow::posForIndicator(KDDockWidgets::DropIndicatorOverlayInterface::DropLocation) const
{
    QQuickItem *root = rootObject();
    const QList<QQuickItem*> items = root->childItems();
    for (QQuickItem *item : items) {
        qDebug() << Q_FUNC_INFO << item;
    }

    qDebug() << Q_FUNC_INFO;
    return {};
}

QString IndicatorWindow::iconName(int loc, bool active) const
{
    return KDDockWidgets::iconName(DropIndicatorOverlayInterface::DropLocation(loc), active);
}

ClassicIndicators *IndicatorWindow::classicIndicators() const
{
    return m_classicIndicators;
}

#endif // QtQuick
