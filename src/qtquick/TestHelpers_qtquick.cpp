/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "KDDockWidgets.h"
#include "Platform_qtquick.h"
#include "views/View_qtquick.h"
#include "qtquick/views/MainWindow_qtquick.h"
#include "kddockwidgets/controllers/MainWindow.h"

#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickStyle>
#include <QQuickItem>
#include <QQuickView>
#include <QtTest/QTest>

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets {
class TestView_qtquick : public Views::View_qtquick
{
public:
    explicit TestView_qtquick(Platform::CreateViewOptions opts, QQuickItem *parent)
        : Views::View_qtquick(nullptr, Type::None, parent)
        , m_opts(opts)
    {
        setMinimumSize(opts.minSize);
        setMaximumSize(opts.maxSize);
    }

    QSize sizeHint() const override
    {
        return m_opts.sizeHint;
    }

private:
    Platform::CreateViewOptions m_opts;
};
}

Platform_qtquick::Platform_qtquick(int &argc, char **argv)
    : Platform_qt(argc, argv)
{
    new QGuiApplication(argc, argv);
    init();
}

void Platform_qtquick::tests_initPlatform_impl()
{
    Platform_qt::tests_initPlatform_impl();

    QQuickStyle::setStyle(QStringLiteral("Material")); // so we don't load KDE plugins
    plat()->setQmlEngine(new QQmlEngine());
}

void Platform_qtquick::tests_deinitPlatform_impl()
{
    delete m_qmlEngine;
    Platform_qt::tests_deinitPlatform_impl();
}

View *Platform_qtquick::tests_createView(CreateViewOptions opts, View *parent)
{
    auto parentItem = parent ? Views::asQQuickItem(parent) : nullptr;
    auto newItem = new TestView_qtquick(opts, parentItem);

    if (!parentItem && opts.createWindow) {
        auto view = new QQuickView(m_qmlEngine, nullptr);
        view->resize(QSize(800, 800));

        newItem->QQuickItem::setParentItem(view->contentItem());
        newItem->QQuickItem::setParent(view->contentItem());
        if (opts.isVisible)
            newItem->Views::View_qtquick::setVisible(true);

        QTest::qWait(100); // the root object gets sized delayed
    }

    return newItem;
}

View *Platform_qtquick::tests_createFocusableView(CreateViewOptions opts, View *parent)
{
    auto view = tests_createView(opts, parent);
    view->setFocusPolicy(Qt::StrongFocus);

    return view;
}

View *Platform_qtquick::tests_createNonClosableView(View *parent)
{
    CreateViewOptions opts;
    opts.isVisible = true;
    auto view = tests_createView(opts, parent);
    view->closeRequested.connect([](QCloseEvent *ev) {
        ev->ignore();
    });

    return view;
}

Controllers::MainWindow *Platform_qtquick::createMainWindow(const QString &uniqueName,
                                                            CreateViewOptions viewOpts,
                                                            MainWindowOptions options,
                                                            View *parent, Qt::WindowFlags flags) const
{
    QQuickItem *parentItem = Views::asQQuickItem(parent);

    if (!parentItem) {
        auto view = new QQuickView(m_qmlEngine, nullptr);
        view->resize(viewOpts.size);

        view->setResizeMode(QQuickView::SizeRootObjectToView);
        view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));

        if (viewOpts.isVisible)
            view->show();

        parentItem = view->rootObject();
        Platform::instance()->tests_wait(100); // the root object gets sized delayed
    }

    auto view = new Views::MainWindow_qtquick(uniqueName, options,
                                              parentItem, flags);

    return view->mainWindow();
}

#endif
