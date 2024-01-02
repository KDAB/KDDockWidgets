/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include <kddockwidgets/DockWidget.h>
#include <kddockwidgets/MainWindow.h>

class MyMainWindow : public KDDockWidgets::QtWidgets::MainWindow
{
    Q_OBJECT
public:
    enum class ExampleOption {
        DockWidget0IsNonClosable = 1,
        NonDockableDockWidget9 = 2,
        RestoreIsRelative = 4,
        MaxSizeForDockWidget8 = 8,
        DockWidgets678DontCloseBeforeRestore = 16,
        Dock0BlocksCloseEvent = 32,
        ProgrammaticDragEvent = 64,
        CtrlKeyFiltersDropIndicators = 128,
    };
    Q_DECLARE_FLAGS(ExampleOptions, ExampleOption)

    explicit MyMainWindow(const QString &uniqueName, KDDockWidgets::MainWindowOptions options,
                          ExampleOptions exampleOptions,
                          const QString &affinityName = {}, // Usually not needed. Just here to show
                                                            // the feature.
                          QWidget *parent = nullptr);
    ~MyMainWindow() override;

private:
    void createDockWidgets();
    KDDockWidgets::QtWidgets::DockWidget *newDockWidget();
    QMenu *m_toggleMenu = nullptr;
    const ExampleOptions m_exampleOptions;

    QVector<KDDockWidgets::QtWidgets::DockWidget *> m_dockwidgets;
};
