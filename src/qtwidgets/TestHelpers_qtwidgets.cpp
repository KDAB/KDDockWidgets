/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "kddockwidgets/KDDockWidgets.h"
#include "Platform_qtwidgets.h"
#include "views/ViewWrapper_qtwidgets.h"
#include "views/View_qtwidgets.h"
#include "kddockwidgets/controllers/MainWindow.h"
#include "qtwidgets/views/MainWindow_qtwidgets.h"

#include <QStyleFactory>
#include <QApplication>
#include <QLineEdit>
#include <QWidget>

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets {
class TestView_qtwidgets : public Views::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit TestView_qtwidgets(Platform::CreateViewOptions opts, QWidget *parent)
        : Views::View_qtwidgets<QWidget>(nullptr, Type::None, parent)
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
        return m_opts.maxSize.boundedTo(Views::View_qtwidgets<QWidget>::maximumSize());
    }

private:
    Platform::CreateViewOptions m_opts;
};

class FocusableTestView_qtwidgets : public Views::View_qtwidgets<QLineEdit>
{
    Q_OBJECT
public:
    explicit FocusableTestView_qtwidgets(Platform::CreateViewOptions opts, QWidget *parent)
        : Views::View_qtwidgets<QLineEdit>(nullptr, Type::None, parent)
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
        return m_opts.maxSize.boundedTo(Views::View_qtwidgets<QLineEdit>::maximumSize());
    }

private:
    Platform::CreateViewOptions m_opts;
};

class NonClosableTestView_qtwidgets : public Views::View_qtwidgets<QWidget>
{
    Q_OBJECT
public:
    explicit NonClosableTestView_qtwidgets(QWidget *parent)
        : Views::View_qtwidgets<QWidget>(nullptr, Type::None, parent)
    {
        create();
    }

    void closeEvent(QCloseEvent *ev) override
    {
        ev->ignore(); // don't allow to close
    }
};

}

Platform_qtwidgets::Platform_qtwidgets(int &argc, char **argv)
    : Platform_qt(argc, argv)
{
    qputenv("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW", "");
    new QApplication(argc, argv);
    qApp->setStyle(QStyleFactory::create(QStringLiteral("fusion")));
    init();
}

void Platform_qtwidgets::tests_initPlatform_impl()
{
    Platform_qt::tests_initPlatform_impl();
}

void Platform_qtwidgets::tests_deinitPlatform_impl()
{
    qDeleteAll(qApp->topLevelWidgets());

    Platform_qt::tests_deinitPlatform_impl();
}

View *Platform_qtwidgets::tests_createView(CreateViewOptions opts, View *parent)
{
    QWidget *parentWidget = Views::View_qtwidgets<QWidget>::asQWidget(parent);

    auto newWidget = new TestView_qtwidgets(opts, parentWidget);
    if (opts.isVisible)
        newWidget->show();

    return newWidget;
}

View *Platform_qtwidgets::tests_createFocusableView(CreateViewOptions opts, View *parent)
{
    QWidget *parentWidget = Views::View_qtwidgets<QWidget>::asQWidget(parent);

    auto newWidget = new FocusableTestView_qtwidgets(opts, parentWidget);
    if (opts.isVisible)
        newWidget->show();

    return newWidget;
}

View *Platform_qtwidgets::tests_createNonClosableView(View *parent)
{
    QWidget *parentWidget = Views::View_qtwidgets<QWidget>::asQWidget(parent);
    auto newWidget = new NonClosableTestView_qtwidgets(parentWidget);

    return newWidget;
}

Controllers::MainWindow *Platform_qtwidgets::createMainWindow(const QString &uniqueName,
                                                              CreateViewOptions opts, MainWindowOptions options,
                                                              View *parent, Qt::WindowFlags flags) const
{
    auto view = new Views::MainWindow_qtwidgets(uniqueName, options,
                                                parent ? static_cast<Views::View_qtwidgets<QMainWindow> *>(parent) : nullptr,
                                                flags);

    if (opts.isVisible)
        view->show();
    view->resize(opts.size);

    return view->mainWindow();
}


#endif

#include "TestHelpers_qtwidgets.moc"
