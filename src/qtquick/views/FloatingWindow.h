/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_FLOATING_WINDOWQUICK_P_H
#define KD_FLOATING_WINDOWQUICK_P_H

#include "View.h"
#include <functional>

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Core {
class FloatingWindow;
}

namespace QtQuick {

class MainWindow;
class TitleBar;
class DropArea;


using QuickWindowCreationCallback = std::function<void(QQuickView *window, QtQuick::MainWindow *parent)>;

class DOCKS_EXPORT FloatingWindow : public QtQuick::View
{
    Q_OBJECT
    QML_NAMED_ELEMENT(FloatingWindowView)
    QML_UNCREATABLE("Created by the framework only.")

    Q_PROPERTY(KDDockWidgets::QtQuick::TitleBar *titleBar READ titleBar CONSTANT)
    Q_PROPERTY(KDDockWidgets::QtQuick::DropArea *dropArea READ dropArea CONSTANT)
public:
    explicit FloatingWindow(Core::FloatingWindow *controller,
                            QtQuick::MainWindow *parent = nullptr,
                            Qt::WindowFlags flags = {});
    ~FloatingWindow();

    QSize minSize() const override;

    // QML interface
    KDDockWidgets::QtQuick::TitleBar *titleBar() const;
    KDDockWidgets::QtQuick::DropArea *dropArea() const;

    Core::Item *rootItem() const;

    /// Set a callback if you want to be notified of a QQuickView being created
    static void setQuickWindowCreationCallback(const QuickWindowCreationCallback &);

protected:
    void setGeometry(QRect) override;

private:
    void onWindowStateChanged(Qt::WindowState);
    int contentsMargins() const;
    int titleBarHeight() const;
    QWindow *candidateParentWindow() const;
    void init() final;
    QQuickView *const m_quickWindow;
    QQuickItem *m_visualItem = nullptr;
    Core::FloatingWindow *const m_controller;
    static QuickWindowCreationCallback s_quickWindowCreationCallback;

    Q_DISABLE_COPY(FloatingWindow)
};

}

}

#endif
