/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_INDICATORS_CLASSICINDICATORS_P_H
#define KD_INDICATORS_CLASSICINDICATORS_P_H

#include "controllers/DropIndicatorOverlay.h"

namespace KDDockWidgets {

class IndicatorWindow_qtwidgets;
class Indicator;

namespace Views {
class ClassicIndicatorWindow;
}

namespace Controllers {

class DOCKS_EXPORT ClassicIndicators : public DropIndicatorOverlay
{
    Q_OBJECT

    // Properties for QML
    Q_PROPERTY(bool innerLeftIndicatorVisible READ innerLeftIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool innerRightIndicatorVisible READ innerRightIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool innerTopIndicatorVisible READ innerTopIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool innerBottomIndicatorVisible READ innerBottomIndicatorVisible NOTIFY indicatorsVisibleChanged)

    Q_PROPERTY(bool outterLeftIndicatorVisible READ outterLeftIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool outterRightIndicatorVisible READ outterRightIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool outterTopIndicatorVisible READ outterTopIndicatorVisible NOTIFY indicatorsVisibleChanged)
    Q_PROPERTY(bool outterBottomIndicatorVisible READ outterBottomIndicatorVisible NOTIFY indicatorsVisibleChanged)

    Q_PROPERTY(bool tabIndicatorVisible READ tabIndicatorVisible NOTIFY indicatorsVisibleChanged)

public:
    explicit ClassicIndicators(Controllers::DropArea *dropArea);
    ~ClassicIndicators() override;
    DropLocation hover_impl(QPoint globalPos) override;
    QPoint posForIndicator(DropLocation) const override;

    // Lots of getters needed because of QML:
    bool innerLeftIndicatorVisible() const;
    bool innerRightIndicatorVisible() const;
    bool innerTopIndicatorVisible() const;
    bool innerBottomIndicatorVisible() const;
    bool outterLeftIndicatorVisible() const;
    bool outterRightIndicatorVisible() const;
    bool outterTopIndicatorVisible() const;
    bool outterBottomIndicatorVisible() const;
    bool tabIndicatorVisible() const;

    bool onResize(QSize newSize);
    void setDropLocation(DropLocation);
    void updateVisibility() override;

Q_SIGNALS:
    void indicatorsVisibleChanged();

private:
    friend class KDDockWidgets::Indicator;
    bool rubberBandIsTopLevel() const;
    void raiseIndicators();
    QRect geometryForRubberband(QRect localRect) const;
    void updateWindowPosition();

    View *const m_rubberBand;
    Views::ClassicIndicatorWindow *const m_indicatorWindow;
};

}

}

#endif
