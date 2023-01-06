/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ClassicIndicatorsWindow_p.h"
#include "ClassicIndicators_p.h"
#include "../Utils_p.h"

using namespace KDDockWidgets;

namespace KDDockWidgets {

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
    case DropLocation_Horizontal:
    case DropLocation_Vertical:
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

static QWidgetAdapter *parentForIndicatorWindow(ClassicIndicators *classicIndicators_)
{
    // On Wayland it can't be a top-level, as we have no way of positioning it

    return isWayland() ? classicIndicators_
                       : nullptr;
}

static Qt::WindowFlags flagsForIndicatorWindow()
{
    return isWayland() ? Qt::Widget
                       : (Qt::Tool | Qt::BypassWindowManagerHint);
}

IndicatorWindow::IndicatorWindow(ClassicIndicators *classicIndicators_)
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
            this, &IndicatorWindow::updateIndicatorVisibility);
    connect(classicIndicators, &ClassicIndicators::indicatorsVisibleChanged,
            this, &IndicatorWindow::updateIndicatorVisibility);

    m_indicators << m_center << m_left << m_right << m_top << m_bottom
                 << m_outterBottom << m_outterTop << m_outterLeft << m_outterRight;
}

Indicator *IndicatorWindow::indicatorForLocation(DropLocation loc) const
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
    case DropLocation_Horizontal:
    case DropLocation_Vertical:
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
    for (Indicator *indicator : { m_left, m_right, m_bottom, m_top,
                                  m_outterTop, m_outterLeft, m_outterRight, m_outterBottom,
                                  m_center })
        indicator->setVisible(classicIndicators->dropIndicatorVisible(indicator->m_dropLocation));

    updateMask();
}

QPoint IndicatorWindow::posForIndicator(DropLocation loc) const
{
    Indicator *indicator = indicatorForLocation(loc);
    return indicator->mapToGlobal(indicator->rect().center());
}

DropLocation IndicatorWindow::hover(QPoint globalPos)
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

Indicator::Indicator(ClassicIndicators *classicIndicators, IndicatorWindow *parent, DropLocation location)
    : QWidget(parent)
    , q(classicIndicators)
    , m_dropLocation(location)
{
    m_image = QImage(iconFileName(/*active=*/false)).scaled(INDICATOR_WIDTH, INDICATOR_WIDTH);
    m_imageActive = QImage(iconFileName(/*active=*/true)).scaled(INDICATOR_WIDTH, INDICATOR_WIDTH);
    setFixedSize(m_image.size());
    setVisible(true);
}

#else

#include <QQmlContext>

IndicatorWindow::IndicatorWindow(KDDockWidgets::ClassicIndicators *classicIndicators)
    : QQuickView()
    , m_classicIndicators(classicIndicators)
{
    setFlags(flags() | Qt::FramelessWindowHint | Qt::BypassWindowManagerHint | Qt::Tool);
    setColor(Qt::transparent);

    rootContext()->setContextProperty(QStringLiteral("_window"), QVariant::fromValue<QObject *>(this));
    setSource(QUrl(QStringLiteral("qrc:/kddockwidgets/private/quick/qml/ClassicIndicatorsOverlay.qml")));


    // Two workarounds for two unrelated bugs:
    if (KDDockWidgets::isOffscreen()) {
        // 1. We need to create the window asap, otherwise, if a drag triggers the indicator window
        // to show, that creates a QOffscreenWindow, which flushes events in the ctor, triggering
        // more hover events which will trigger another QOffscreenWindow.
        // We then end up with a QWindow with two QPlatformWindow, and only one is deleted in
        // at shutdown, meaning some timers aren't unregistered, meaning we get a crash when
        // the timer event is sent to the destroyed QWindow.
        create();
    } else {
        // 2.
        // Small hack to avoid flickering when we drag over a window the first time
        // Not sure why a simply create() doesn't work instead
        // Not if offscreen though, as that QPA is flaky with window activation/focus
        resize(QSize(1, 1));
        show();
        hide();
    }
}

DropLocation IndicatorWindow::hover(QPoint pt)
{
    QQuickItem *item = indicatorForPos(pt);
    const DropLocation loc = item ? locationForIndicator(item)
                                  : DropLocation_None;
    classicIndicators()->setDropLocation(loc);
    return loc;
}

QQuickItem *IndicatorWindow::indicatorForPos(QPoint pt) const
{
    const QVector<QQuickItem *> indicators = indicatorItems();
    Q_ASSERT(indicators.size() == 9);

    for (QQuickItem *item : indicators) {
        if (item->isVisible()) {
            QRect rect(0, 0, int(item->width()), int(item->height()));
            rect.moveTopLeft(item->mapToGlobal(QPointF(0, 0)).toPoint());
            if (rect.contains(pt)) {
                return item;
            }
        }
    }

    return nullptr;
}

void IndicatorWindow::updatePositions()
{
    // Not needed to implement, the Indicators use QML anchors
}

QPoint IndicatorWindow::posForIndicator(KDDockWidgets::DropLocation loc) const
{
    QQuickItem *indicator = IndicatorWindow::indicatorForLocation(loc);
    return indicator->mapToGlobal(indicator->boundingRect().center()).toPoint();
}

QString IndicatorWindow::iconName(int loc, bool active) const
{
    return KDDockWidgets::iconName(DropLocation(loc), active);
}

ClassicIndicators *IndicatorWindow::classicIndicators() const
{
    return m_classicIndicators;
}

QQuickItem *IndicatorWindow::indicatorForLocation(DropLocation loc) const
{
    const QVector<QQuickItem *> indicators = indicatorItems();
    Q_ASSERT(indicators.size() == 9);

    for (QQuickItem *item : indicators) {
        if (locationForIndicator(item) == loc)
            return item;
    }

    qWarning() << Q_FUNC_INFO << "Couldn't find indicator for location" << loc;
    return nullptr;
}

DropLocation IndicatorWindow::locationForIndicator(const QQuickItem *item) const
{
    return DropLocation(item->property("indicatorType").toInt());
}

QVector<QQuickItem *> IndicatorWindow::indicatorItems() const
{
    QVector<QQuickItem *> indicators;
    indicators.reserve(9);

    QQuickItem *root = rootObject();
    const QList<QQuickItem *> items = root->childItems();
    for (QQuickItem *item : items) {
        if (QString::fromLatin1(item->metaObject()->className()).startsWith(QLatin1String("ClassicIndicator_QMLTYPE"))) {
            indicators.push_back(item);
        } else if (item->objectName() == QLatin1String("innerIndicators")) {
            const QList<QQuickItem *> innerIndicators = item->childItems();
            for (QQuickItem *innerItem : innerIndicators) {
                if (QString::fromLatin1(innerItem->metaObject()->className()).startsWith(QLatin1String("ClassicIndicator_QMLTYPE"))) {
                    indicators.push_back(innerItem);
                }
            }
        }
    }

    return indicators;
}

#endif // QtQuick
