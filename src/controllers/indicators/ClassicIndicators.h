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

class Indicator;

namespace Views {
class ClassicIndicatorWindow;
}

namespace Controllers {

class DOCKS_EXPORT ClassicIndicators : public DropIndicatorOverlay
{
    Q_OBJECT
public:
    explicit ClassicIndicators(Controllers::DropArea *dropArea);
    ~ClassicIndicators() override;
    DropLocation hover_impl(QPoint globalPos) override;
    QPoint posForIndicator(DropLocation) const override;

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
