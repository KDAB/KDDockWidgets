/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ClassicIndicators_p.h"
#include "DropArea_p.h"
#include "DragController_p.h"
#include "Frame_p.h"
#include "Logging_p.h"
#include "Utils_p.h"

#include <QPainter>
#include <QRubberBand>

#define INDICATOR_WIDTH 40
#define OUTTER_INDICATOR_MARGIN 10

using namespace KDDockWidgets;

namespace KDDockWidgets {
class IndicatorWindow;
}

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
    QString suffix = active ? QStringLiteral("_active")
                            : QString();

    QString name;
    switch (m_dropLocation) {
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

QString Indicator::iconFileName(bool active) const
{
    return QStringLiteral(":/img/classic_indicators/%1.png").arg(iconName(active));
}



IndicatorWindow::IndicatorWindow(ClassicIndicators *classicIndicators_, QWidget *)
    : QWidget(nullptr, Qt::Tool)
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
    updatePosition();

    m_indicators << m_center << m_left << m_right << m_top << m_bottom
                 << m_outterBottom << m_outterTop << m_outterLeft << m_outterRight;

    setObjectName(QStringLiteral("_docks_IndicatorWindow_Overlay"));
}

bool IndicatorWindow::event(QEvent *e)
{
    if (e->type() == QEvent::Show) {
        updatePosition();
    }

    return QWidget::event(e);
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

    if (!KDDockWidgets::windowManagerSupportsTranslucency()) {
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

void IndicatorWindow::updateIndicatorVisibility(bool visible)
{
    Frame *hoveredFrame = classicIndicators->m_hoveredFrame;
    const bool isTheOnlyFrame = hoveredFrame && hoveredFrame->isTheOnlyFrame();

    const bool innerShouldBeVisible = visible && hoveredFrame;
    const bool outterShouldBeVisible = visible && !isTheOnlyFrame;

    for (Indicator *indicator : { m_center, m_left, m_right, m_bottom, m_top })
        indicator->setVisible(innerShouldBeVisible);

    for (Indicator *indicator : { m_outterTop, m_outterLeft, m_outterRight, m_outterBottom })
        indicator->setVisible(outterShouldBeVisible);

    updateMask();
}

void IndicatorWindow::hover(QPoint globalPos)
{
    for (Indicator *indicator : qAsConst(m_indicators)) {
        if (indicator->isVisible())
            indicator->setHovered(indicator->rect().contains(indicator->mapFromGlobal(globalPos)));
    }
}

void IndicatorWindow::updatePosition()
{
    QRect rect = classicIndicators->rect();
    QPoint pos = classicIndicators->mapToGlobal(QPoint(0, 0));
    rect.moveTo(pos);
    setGeometry(rect);
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
        QRect hoveredRect = hoveredFrame->geometry();
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

ClassicIndicators::ClassicIndicators(DropArea *dropArea)
    : DropIndicatorOverlayInterface(dropArea) // Is parented on the drop-area, not a toplevel.
    , m_rubberBand(new QRubberBand(QRubberBand::Rectangle, this))
    , m_indicatorWindow(new IndicatorWindow(this, /*parent=*/ nullptr)) // Top-level so the indicators can appear above the window being dragged.
{
    setAttribute(Qt::WA_TranslucentBackground);
    setVisible(false);
}

ClassicIndicators::~ClassicIndicators()
{
    delete m_indicatorWindow;
}

DropIndicatorOverlayInterface::Type ClassicIndicators::indicatorType() const
{
    return TypeClassic;
}

void ClassicIndicators::hover(QPoint globalPos)
{
    m_indicatorWindow->hover(globalPos);
}

QPoint ClassicIndicators::posForIndicator(DropIndicatorOverlayInterface::DropLocation loc) const
{
    Indicator *indicator = m_indicatorWindow->indicatorForLocation(loc);
    return indicator->mapToGlobal(indicator->rect().center());
}

void ClassicIndicators::updateVisibility()
{
    if (isHovered()) {
        setVisible(true);
        m_indicatorWindow->updatePositions();
        m_indicatorWindow->setVisible(true);
        m_indicatorWindow->updateIndicatorVisibility(true);
        raiseIndicators();
    } else {
        setVisible(false);
        m_indicatorWindow->setVisible(false);
        m_indicatorWindow->updateIndicatorVisibility(false);
    }
}

void ClassicIndicators::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
}

void ClassicIndicators::hideEvent(QHideEvent *e)
{
    QWidget::hideEvent(e);
}

void ClassicIndicators::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);
    m_indicatorWindow->resize(window()->size());
}

void ClassicIndicators::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::transparent);
}

void ClassicIndicators::raiseIndicators()
{
    m_indicatorWindow->raise();
}

KDDockWidgets::Location locationToMultisplitterLocation(ClassicIndicators::DropLocation location)
{
    switch (location) {
    case DropIndicatorOverlayInterface::DropLocation_Left:
        return KDDockWidgets::Location_OnLeft;
    case DropIndicatorOverlayInterface::DropLocation_Top:
        return KDDockWidgets::Location_OnTop;
    case DropIndicatorOverlayInterface::DropLocation_Right:
        return KDDockWidgets::Location_OnRight;
    case DropIndicatorOverlayInterface::DropLocation_Bottom:
        return KDDockWidgets::Location_OnBottom;
    case DropIndicatorOverlayInterface::DropLocation_OutterLeft:
        return KDDockWidgets::Location_OnLeft;
    case DropIndicatorOverlayInterface::DropLocation_OutterTop:
        return KDDockWidgets::Location_OnTop;
    case DropIndicatorOverlayInterface::DropLocation_OutterRight:
        return KDDockWidgets::Location_OnRight;
    case DropIndicatorOverlayInterface::DropLocation_OutterBottom:
        return KDDockWidgets::Location_OnBottom;
    default:
        return KDDockWidgets::Location_None;
    }
}

void ClassicIndicators::setDropLocation(ClassicIndicators::DropLocation location)
{
    qCDebug(overlay) << "ClassicIndicators::setCurrentDropLocation" << location;
    setCurrentDropLocation(location);

    if (location == DropLocation_None) {
        m_rubberBand->setVisible(false);
        return;
    }

    if (location == DropLocation_Center) {
        m_rubberBand->setGeometry(m_hoveredFrame ? m_hoveredFrame->geometry() : rect());
        m_rubberBand->setVisible(true);
        return;
    }

    KDDockWidgets::Location multisplitterLocation = locationToMultisplitterLocation(location);
    Frame *relativeToFrame = nullptr;

    MultiSplitterLayout *layout = m_dropArea->multiSplitter();

    switch (location) {
    case DropLocation_Left:
    case DropLocation_Top:
    case DropLocation_Right:
    case DropLocation_Bottom:
        if (!m_hoveredFrame) {
            qWarning() << "ClassicIndicators::setCurrentDropLocation: frame is null. location=" << location
                       << "; windowBeingDragged=" << m_windowBeingDragged
                       << "; dropArea->widgets=" << layout->items();
            Q_ASSERT(false);
            return;
        }
        relativeToFrame = m_hoveredFrame;
        break;
    case DropLocation_OutterLeft:
    case DropLocation_OutterTop:
    case DropLocation_OutterRight:
    case DropLocation_OutterBottom:
        break;
    default:
        break;
    }

    QRect rect = layout->rectForDrop(m_windowBeingDragged, multisplitterLocation,
                                     layout->itemForFrame(relativeToFrame));

    m_rubberBand->setGeometry(rect);
    m_rubberBand->setVisible(true);
}
