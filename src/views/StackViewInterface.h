/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

QT_BEGIN_NAMESPACE
class QPoint;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Controllers {
class Stack;
}

namespace Views {

/// @brief The interface that Stack views share
class DOCKS_EXPORT StackViewInterface
{
public:
    explicit StackViewInterface(Controllers::Stack *);
    virtual ~StackViewInterface();

    /// @brief Reimplement if you want to support dragging by QTabWidget instead of TitleBar
    /// This is only implemented by QtWidgets.
    /// Instead of reimplementing this, consider reimplementing
    /// TabBarViewInterface::isPositionDraggable() instead. This exists only because the background
    /// of QTabBar is the QTabWidget, which probably isn't true for other frontends.
    virtual bool isPositionDraggable(QPoint p) const;

    /// @brief Sets QTabWidget::documentMode(). Only implemented for QtWidgets.
    /// Probably not interesting for other frontends to implement, therefore it's not pure-virtual.
    virtual void setDocumentMode(bool);

protected:
    Controllers::Stack *const m_stack;
};

}

}
