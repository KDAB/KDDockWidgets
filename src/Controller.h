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

QT_BEGIN_NAMESPACE
class QWindow;
QT_END_NAMESPACE

namespace KDDockWidgets {

class View;

enum class Type {
    FIRST = 1, // Keep first
    None = 0,
    Frame = 1,
    TitleBar = 2,
    TabBar = 4,
    Stack = 8,
    FloatingWindow = 16,
    Separator = 32,
    DockWidget = 64,
    MDIArea = 128,
    LayoutItem = 256,
    SideBar = 512,
    MainWindow = 1024,
    ViewWrapper = 2048,
    DropArea = 4096,
    MDILayout = 8192,
    RubberBand = 0x4000,
    DropAreaIndicatorOverlay = 0x8000,

    LAST = RubberBand // Keep last
};

class DOCKS_EXPORT Controller : public QObject // TODOm4 remove QObject
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

    // View convenience methods to save 1 indirection
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
    std::shared_ptr<View> window() const;
    void show() const;
    bool inDtor() const;

    /// Sets the parent view
    /// In Qt this would be equivalent to calling view()->setParent(parent);
    void setParentView(View *parent);

Q_SIGNALS:
    ///@brief signal counterpart for setParentView()
    void parentViewChanged(View *parent);

protected:
    virtual void setParentView_impl(View *parent);

private:
    void setParent(QObject *) = delete;
    View *m_view = nullptr;
    bool m_inDtor = false;
    const Type m_type;
};

}
