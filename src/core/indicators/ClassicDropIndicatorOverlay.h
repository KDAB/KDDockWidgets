/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_INDICATORS_CLASSICINDICATORS_P_H
#define KD_INDICATORS_CLASSICINDICATORS_P_H

#include "core/DropIndicatorOverlay.h"

namespace KDDockWidgets {

class Indicator;

namespace Core {

class ClassicIndicatorWindowViewInterface;

class DOCKS_EXPORT ClassicDropIndicatorOverlay : public DropIndicatorOverlay
{
    Q_OBJECT
public:
    explicit ClassicDropIndicatorOverlay(Core::DropArea *dropArea);
    ~ClassicDropIndicatorOverlay() override;
    DropLocation hover_impl(QPoint globalPos) override;
    QPoint posForIndicator(DropLocation) const override;

    bool onResize(QSize newSize);
    void setCurrentDropLocation(DropLocation) override;
    void updateVisibility() override;

    Core::ClassicIndicatorWindowViewInterface *indicatorWindow() const;
    View *rubberBand() const;

Q_SIGNALS:
    void indicatorsVisibleChanged();

private:
    friend class KDDockWidgets::Indicator;
    bool rubberBandIsTopLevel() const;
    void raiseIndicators();
    QRect geometryForRubberband(QRect localRect) const;
    void updateWindowPosition();

    View *const m_rubberBand;
    Core::ClassicIndicatorWindowViewInterface *const m_indicatorWindow;
};

}

}

#endif
