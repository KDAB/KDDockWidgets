/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group
  company <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "KDDockWidgets.h"
#include "Platform_qtwidgets.h"
#include "views/ViewWrapper_qtwidgets.h"
#include "views/View_qtwidgets.h"

#include <QStyleFactory>
#include <QApplication>
#include <QWidget>

using namespace KDDockWidgets;

#ifdef DOCKS_DEVELOPER_MODE

namespace KDDockWidgets {
class TestView_qtwidgets : public Views::View_qtwidgets<QWidget>
{
public:
    explicit TestView_qtwidgets(Platform::CreateViewOptions opts, QWidget *parent)
        : Views::View_qtwidgets<QWidget>(nullptr, Type::None, parent)
        , m_opts(opts)
    {
        create();
        setMinimumSize(opts.minSize);
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

#endif