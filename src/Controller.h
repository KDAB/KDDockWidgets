/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

#include <QObject>

#include <memory>

class QWindow;

namespace KDDockWidgets {

class View;
class ViewWrapper;

enum class Type
{
    FIRST = 1, // Keep first
    Frame = 1,
    TitleBar = 2,
    TabBar = 4,
    Stack = 8,
    FloatingWindow = 16,
    Separator = 32,
    DockWidget = 64,
    Layout = 128,
    LayoutItem = 256,
    SideBar = 512,
    MainWindow = 1024,
    DropIndicatorOverlayInterface = 2048,
    ViewWrapper = 4096,
    LAST = ViewWrapper // Keep last
};

class DOCKS_EXPORT Controller : public QObject // TODOv2 remove QObject
{
    Q_OBJECT
public:
    explicit Controller(Type type, View *);
    virtual ~Controller();

    /// @brief Returns the view associated with this controller, if any.
    View *view() const;

    /// @brief Returns the type of this controller
    Type type() const;

    /// @brief Returns whether this controller is of the specified type
    bool is(Type) const;

    // View convienence methods to save 1 indirection
    bool isVisible() const;
    void setVisible(bool);
    QRect rect() const;
    QPoint mapToGlobal(QPoint) const;
    int height() const;
    int width() const;
    QSize size() const;
    QPoint pos() const;
    QRect geometry() const;
    int x() const;
    int y() const;
    bool close();
    std::unique_ptr<ViewWrapper> window() const;
    QWindow *windowHandle() const; // TODOv2
    void show() const;
    bool inDtor() const;

private:
    View *m_view = nullptr;
    bool m_inDtor = false;
    const Type m_type;
};

}
