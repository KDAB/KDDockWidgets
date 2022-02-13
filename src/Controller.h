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

namespace KDDockWidgets {

class View;

class DOCKS_EXPORT Controller : public QObject // TODO remove QObject
{
    Q_OBJECT
public:
    explicit Controller(View *);
    virtual ~Controller();

    /// @brief Returns the view associated with this controller, if any.
    View *view() const;

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
    QWidget *window() const; // TODO

    bool inDtor() const;

private:
    View *m_view = nullptr;
    bool m_inDtor = false;
};

}
