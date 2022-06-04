/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MULTISPLITTER_SEPARATOR_QUICK_H
#define KD_MULTISPLITTER_SEPARATOR_QUICK_H
#pragma once

#include "View_qtquick.h"
#include "kddockwidgets/docks_export.h"

#include <QQuickItem>

namespace KDDockWidgets::Views {

class DOCKS_EXPORT Separator_qtquick : public View_qtquick
{
    Q_OBJECT
    Q_PROPERTY(bool isVertical READ isVertical NOTIFY isVerticalChanged)
public:
    explicit Separator_qtquick(Controllers::Separator *controller, QQuickItem *parent = nullptr);
    bool isVertical() const;
    void init() override;

protected:
    // TODOm2
    // Widget *createRubberBand(Widget *parent) override;

public:
    // Interface with QML:
    Q_INVOKABLE void onMousePressed();
    Q_INVOKABLE void onMouseMoved(QPointF localPos);
    Q_INVOKABLE void onMouseReleased();
    Q_INVOKABLE void onMouseDoubleClicked();
Q_SIGNALS:
    // constant but it's only set after Separator::init
    void isVerticalChanged();

private:
    Controllers::Separator *const m_controller;
};

}

#endif
