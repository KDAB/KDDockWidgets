/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018 Sérgio Martins <sergio.martins@kdab.com>

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

#ifndef CLASSIC_DROPINDICATOROVERLAY_H
#define CLASSIC_DROPINDICATOROVERLAY_H

#include "DropIndicatorOverlayInterface_p.h"

class QRubberBand;

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
    void paintEvent(QPaintEvent *) override;
    void updateVisibility() override;
private:
    friend class KDDockWidgets::Indicator;
    friend class KDDockWidgets::IndicatorWindow;
    void onDragging(QPoint globalPos);
    void raiseIndicators();
    void setDropLocation(DropLocation);

    QRubberBand *const m_rubberBand;
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
}

#endif
