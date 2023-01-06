/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ClassicIndicators_p.h"
#include "Config.h"
#include "FrameworkWidgetFactory.h"
#include "ClassicIndicatorsWindow_p.h"

#include "private/DropArea_p.h"
#include "private/DragController_p.h"
#include "private/Frame_p.h"
#include "private/Logging_p.h"
#include "private/DockRegistry_p.h"
#include "private/Utils_p.h"

using namespace KDDockWidgets;

static IndicatorWindow *createIndicatorWindow(ClassicIndicators *classicIndicators)
{
    auto window = new IndicatorWindow(classicIndicators);
    window->setObjectName(QStringLiteral("_docks_IndicatorWindow_Overlay"));

    return window;
}

ClassicIndicators::ClassicIndicators(DropArea *dropArea)
    : DropIndicatorOverlayInterface(dropArea) // Is parented on the drop-area, not a toplevel.
    , m_rubberBand(Config::self().frameworkWidgetFactory()->createRubberBand(rubberBandIsTopLevel() ? nullptr : dropArea))
    , m_indicatorWindow(createIndicatorWindow(this))
{
    if (rubberBandIsTopLevel())
        m_rubberBand->setWindowOpacity(0.5);
}

ClassicIndicators::~ClassicIndicators()
{
    delete m_indicatorWindow;
}

DropLocation ClassicIndicators::hover_impl(QPoint globalPos)
{
    return m_indicatorWindow->hover(globalPos);
}

QPoint ClassicIndicators::posForIndicator(DropLocation loc) const
{
    return m_indicatorWindow->posForIndicator(loc);
}

bool ClassicIndicators::innerLeftIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_Left);
}

bool ClassicIndicators::innerRightIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_Right);
}

bool ClassicIndicators::innerTopIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_Top);
}

bool ClassicIndicators::innerBottomIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_Bottom);
}

bool ClassicIndicators::outterLeftIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_OutterLeft);
}

bool ClassicIndicators::outterRightIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_OutterRight);
}

bool ClassicIndicators::outterTopIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_OutterTop);
}

bool ClassicIndicators::outterBottomIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_OutterBottom);
}

bool ClassicIndicators::tabIndicatorVisible() const
{
    return dropIndicatorVisible(DropLocation_Center);
}

bool ClassicIndicators::onResize(QSize)
{
    m_indicatorWindow->resize(window()->size());
    return false;
}

void ClassicIndicators::updateVisibility()
{
    if (isHovered()) {
        m_indicatorWindow->updatePositions();
        m_indicatorWindow->setVisible(true);
        updateWindowPosition();
        raiseIndicators();
    } else {
        m_rubberBand->setVisible(false);
        m_indicatorWindow->setVisible(false);
    }

    Q_EMIT indicatorsVisibleChanged();
}

void ClassicIndicators::raiseIndicators()
{
    m_indicatorWindow->raise();
}

KDDockWidgets::Location locationToMultisplitterLocation(DropLocation location)
{
    switch (location) {
    case DropLocation_Left:
        return KDDockWidgets::Location_OnLeft;
    case DropLocation_Top:
        return KDDockWidgets::Location_OnTop;
    case DropLocation_Right:
        return KDDockWidgets::Location_OnRight;
    case DropLocation_Bottom:
        return KDDockWidgets::Location_OnBottom;
    case DropLocation_OutterLeft:
        return KDDockWidgets::Location_OnLeft;
    case DropLocation_OutterTop:
        return KDDockWidgets::Location_OnTop;
    case DropLocation_OutterRight:
        return KDDockWidgets::Location_OnRight;
    case DropLocation_OutterBottom:
        return KDDockWidgets::Location_OnBottom;
    default:
        return KDDockWidgets::Location_None;
    }
}

void ClassicIndicators::setDropLocation(DropLocation location)
{
    setCurrentDropLocation(location);

    if (location == DropLocation_None) {
        m_rubberBand->setVisible(false);
        return;
    }

    if (location == DropLocation_Center) {
        m_rubberBand->setGeometry(geometryForRubberband(m_hoveredFrame ? m_hoveredFrame->QWidgetAdapter::geometry() : rect()));
        m_rubberBand->setVisible(true);
        if (rubberBandIsTopLevel()) {
            m_rubberBand->raise();
            raiseIndicators();
        }

        return;
    }

    KDDockWidgets::Location multisplitterLocation = locationToMultisplitterLocation(location);
    Frame *relativeToFrame = nullptr;

    switch (location) {
    case DropLocation_Left:
    case DropLocation_Top:
    case DropLocation_Right:
    case DropLocation_Bottom:
        if (!m_hoveredFrame) {
            qWarning() << "ClassicIndicators::setCurrentDropLocation: frame is null. location=" << location
                       << "; isHovered=" << isHovered()
                       << "; dropArea->widgets=" << m_dropArea->items();
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

    auto windowBeingDragged = DragController::instance()->windowBeingDragged();

    QRect rect = m_dropArea->rectForDrop(windowBeingDragged, multisplitterLocation,
                                         m_dropArea->itemForFrame(relativeToFrame));

    m_rubberBand->setGeometry(geometryForRubberband(rect));
    m_rubberBand->setVisible(true);
    if (rubberBandIsTopLevel()) {
        m_rubberBand->raise();
        raiseIndicators();
    }
}

void ClassicIndicators::updateWindowPosition()
{
    QRect rect = this->rect();
    if (KDDockWidgets::isWindow(m_indicatorWindow)) {
        // On all non-wayland platforms it's a top-level.
        QPoint pos = mapToGlobal(QPoint(0, 0));
        rect.moveTo(pos);
    }
    m_indicatorWindow->setGeometry(rect);
}

bool ClassicIndicators::rubberBandIsTopLevel() const
{
    return Config::self().internalFlags() & Config::InternalFlag_TopLevelIndicatorRubberBand;
}

QRect ClassicIndicators::geometryForRubberband(QRect localRect) const
{
    if (!rubberBandIsTopLevel())
        return localRect;

    QPoint topLeftLocal = localRect.topLeft();
    QPoint topLeftGlobal = m_dropArea->QWidgetAdapter::mapToGlobal(topLeftLocal);

    localRect.moveTopLeft(topLeftGlobal);

    return localRect;
}
