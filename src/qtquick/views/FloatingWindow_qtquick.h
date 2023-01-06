/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_FLOATING_WINDOWQUICK_P_H
#define KD_FLOATING_WINDOWQUICK_P_H

#include "View_qtquick.h"

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Controllers {
class FloatingWindow;
}

namespace Views {

class MainWindow_qtquick;
class TitleBar_qtquick;
class DropArea_qtquick;

class DOCKS_EXPORT FloatingWindow_qtquick : public Views::View_qtquick
{
    Q_OBJECT
    Q_PROPERTY(QObject *titleBar READ titleBar CONSTANT)
    Q_PROPERTY(QObject *dropArea READ dropArea CONSTANT)
public:
    explicit FloatingWindow_qtquick(Controllers::FloatingWindow *controller,
                                    Views::MainWindow_qtquick *parent = nullptr,
                                    Qt::WindowFlags flags = {});
    ~FloatingWindow_qtquick();

    QSize minSize() const override;

    // QML interface
    QObject *titleBar() const;
    QObject *dropArea() const;

    Layouting::Item *rootItem() const;

protected:
    void setGeometry(QRect) override;

private:
    void onWindowStateChanged(Qt::WindowState);
    int contentsMargins() const;
    int titleBarHeight() const;
    QWindow *candidateParentWindow() const;
    void init() override;
    QQuickView *const m_quickWindow;
    QQuickItem *m_visualItem = nullptr;
    Controllers::FloatingWindow *const m_controller;
    Q_DISABLE_COPY(FloatingWindow_qtquick)
};

}

}

#endif
