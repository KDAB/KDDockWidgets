/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "../Controller.h"

#include <QVector>
#include <QPoint>

class QRect;

namespace KDDockWidgets {
class Config;
}

namespace Layouting {
class ItemBoxContainer;
}

namespace KDDockWidgets::Controllers {

class DOCKS_EXPORT Separator : public Controller
{
public:
    typedef QVector<Separator *> List;

    explicit Separator(View *host);
    virtual ~Separator() override;

    void init(Layouting::ItemBoxContainer *parentContainer, Qt::Orientation orientation);
    bool isVertical() const;
    void move(int p);
    int position() const;
    Qt::Orientation orientation() const;
    void setGeometry(QRect r);
    void setGeometry(int pos, int pos2, int length);
    Layouting::ItemBoxContainer *parentContainer() const;

    ///@brief Returns whether we're dragging a separator. Can be useful for the app to stop other work while we're not in the final size
    static bool isResizing();

    /// @internal Just for the unit-tests.
    /// Returns the total amount of Separator() instances currently alive.
    static int numSeparators();

public:
    void onMousePress();
    void onMouseReleased();
    void onMouseDoubleClick();
    void onMouseMove(QPoint pos);

private:
    friend class KDDockWidgets::Config;

    Q_DISABLE_COPY(Separator)
    void setLazyPosition(int);
    bool isBeingDragged() const;
    bool usesLazyResize() const;

    struct Private;
    Private *const d;

    static bool s_isResizing;
    static Separator *s_separatorBeingDragged;
};

}
