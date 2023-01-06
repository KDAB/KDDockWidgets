/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_INDICATORS_CLASSICINDICATORS_P_H
#define KD_INDICATORS_CLASSICINDICATORS_P_H

#include "../DropIndicatorOverlayInterface_p.h"

namespace KDDockWidgets {

class IndicatorWindow;
class Indicator;

class DOCKS_EXPORT ClassicIndicators : public DropIndicatorOverlayInterface
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
    explicit ClassicIndicators(DropArea *dropArea);
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

protected:
    bool onResize(QSize newSize) override;
    void updateVisibility() override;
Q_SIGNALS:
    void indicatorsVisibleChanged();

private:
    friend class KDDockWidgets::Indicator;
    friend class KDDockWidgets::IndicatorWindow;
    bool rubberBandIsTopLevel() const;
    void raiseIndicators();
    QRect geometryForRubberband(QRect localRect) const;
    void setDropLocation(DropLocation);
    void updateWindowPosition();

    QWidgetOrQuick *const m_rubberBand;
    IndicatorWindow *const m_indicatorWindow;
};

}

#endif
