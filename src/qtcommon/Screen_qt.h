/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Waqar Ahmed <waqar.ahmed@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Screen.h"

#include <QPointer>

QT_BEGIN_NAMESPACE
class QScreen;
QT_END_NAMESPACE

namespace KDDockWidgets {

class Screen_qt final : public Screen
{
public:
    Screen_qt(QScreen *);

    QString name() const override;

    QSize size() const override;
    QRect geometry() const override;

    qreal devicePixelRatio() const override;

    QSize availableSize() const override;
    QRect availableGeometry() const override;

    QSize virtualSize() const override;
    QRect virtualGeometry() const override;

    QScreen *qtScreen() const;

public:
    QPointer<QScreen> m_screen;
};

}
