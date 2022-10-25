/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/KDDockWidgets.h"

QT_BEGIN_NAMESPACE
class QPoint;
class QRect;
class QSize;
class QString;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Views {

/// @brief The window that will hold the classic indicators
/// This is a window so it can be over the window that is being dragged
class DOCKS_EXPORT ClassicIndicatorWindowViewInterface
{
public:
    virtual ~ClassicIndicatorWindowViewInterface();

    virtual void setObjectName(const QString &) = 0;
    virtual DropLocation hover(QPoint) = 0;
    virtual QPoint posForIndicator(DropLocation) const = 0;
    virtual void updatePositions() = 0;
    virtual void raise() = 0;
    virtual void setVisible(bool) = 0;
    virtual void resize(QSize) = 0;
    virtual void setGeometry(QRect) = 0;
    virtual bool isWindow() const = 0;
};

}

}
