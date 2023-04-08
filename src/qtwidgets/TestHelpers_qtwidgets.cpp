/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "Platform_qtwidgets.h"
#include "views/ViewWrapper_qtwidgets.h"
#include "views/View_qtwidgets.h"
#include "kddockwidgets/core/MainWindow.h"
#include "qtwidgets/views/MainWindow_qtwidgets.h"
#include "Window_qtwidgets.h"

#include <QStyleFactory>
#include <QApplication>
#include <QLineEdit>
#include <QWidget>

using namespace KDDockWidgets;
using namespace KDDockWidgets::qtwidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets::qtwidgets {
class TestView : public qtwidgets::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit TestView(Core::CreateViewOptions opts, QWidget *parent)
        : qtwidgets::View_qtwidgets<QWidget>(nullptr, Type::None, parent)
        , m_opts(opts)
    {
        create();
        setMinimumSize(opts.minSize.boundedTo(opts.maxSize));
    }

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

    QSize maxSizeHint() const override
    {
        return m_opts.maxSize.boundedTo(qtwidgets::View_qtwidgets<QWidget>::maximumSize());
    }

private:
    Core::CreateViewOptions m_opts;
};

class FocusableTestView : public qtwidgets::View_qtwidgets<QLineEdit>
{
    Q_OBJECT
public:
    explicit FocusableTestView(Core::CreateViewOptions opts, QWidget *parent)
        : qtwidgets::View_qtwidgets<QLineEdit>(nullptr, Type::None, parent)
        , m_opts(opts)
    {
        create();
        setMinimumSize(opts.minSize.boundedTo(opts.maxSize));
        setSizePolicy(SizePolicy::Preferred, SizePolicy::Preferred);
    }

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

    QSize maxSizeHint() const override
    {
        return m_opts.maxSize.boundedTo(qtwidgets::View_qtwidgets<QLineEdit>::maximumSize());
    }

private:
    Core::CreateViewOptions m_opts;
};

class NonClosableTestView : public qtwidgets::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit NonClosableTestView(QWidget *parent)
        : qtwidgets::View_qtwidgets<QWidget>(nullptr, Type::None, parent)
    {
        create();
    }

    void closeEvent(QCloseEvent *ev) override
    {
        ev->ignore(); // don't allow to close
    }
};

}

void Platform::tests_initPlatform_impl()
{
    Platform_qt::tests_initPlatform_impl();
}

void Platform::tests_deinitPlatform_impl()
{
    tests_wait(500); // Some windows are currently being destroyed

    qDeleteAll(qApp->topLevelWidgets());

    Platform_qt::tests_deinitPlatform_impl();
}

View *Platform::tests_createView(Core::CreateViewOptions opts, View *parent)
{
    QWidget *parentWidget = Views::View_qt::asQWidget(parent);

    auto newWidget = new TestView(opts, parentWidget);
    if (opts.isVisible)
        newWidget->show();

    return newWidget;
}

View *Platform::tests_createFocusableView(Core::CreateViewOptions opts, View *parent)
{
    QWidget *parentWidget = Views::View_qt::asQWidget(parent);

    auto newWidget = new FocusableTestView(opts, parentWidget);
    if (opts.isVisible)
        newWidget->show();

    return newWidget;
}

View *Platform::tests_createNonClosableView(View *parent)
{
    QWidget *parentWidget = Views::View_qt::asQWidget(parent);
    auto newWidget = new NonClosableTestView(parentWidget);

    return newWidget;
}

Core::MainWindow *Platform::createMainWindow(const QString &uniqueName,
                                             Core::CreateViewOptions opts,
                                             MainWindowOptions options,
                                             View *parent,
                                             Qt::WindowFlags flags) const
{
    auto view = new qtwidgets::MainWindow(
        uniqueName, options,
        parent ? static_cast<qtwidgets::View_qtwidgets<QMainWindow> *>(parent) : nullptr, flags);

    if (opts.isVisible)
        view->show();
    view->resize(opts.size);

    return view->mainWindow();
}

std::shared_ptr<Core::Window> Platform::tests_createWindow()
{
    auto window = new Window(new QWidget());
    window->setVisible(true);
    return std::shared_ptr<Core::Window>(window);
}

#endif

#include "TestHelpers_qtwidgets.moc"
