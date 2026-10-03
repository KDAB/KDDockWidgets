/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../utils.h"
#include "Config.h"
#include "core/Separator.h"
#include "core/MainWindow.h"
#include "core/Platform.h"
#include "core/DockWidget.h"
#include "core/Group.h"
#include "core/DropArea.h"

#include <QTest>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

class TestSeparator : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_separatorCtor();
    void tst_doubleClick();
};

void TestSeparator::tst_separatorCtor()
{
    Core::DropArea dropArea(nullptr, MainWindowOption_None);
    Core::Separator separator(dropArea.asLayoutingHost(), Qt::Vertical, nullptr);
    QVERIFY(separator.view()->is(Core::ViewType::Separator));
    QVERIFY(separator.view()->asWrapper()->is(Core::ViewType::Separator));
}

static Core::Separator *firstSeparator(Core::MainWindow *mw)
{
    for (const auto &child : mw->dropArea()->view()->childViews()) {
        if (child->is(Core::ViewType::Separator))
            return static_cast<Core::Separator *>(child->controller());
    }

    return nullptr;
}

void TestSeparator::tst_doubleClick()
{
    if (Platform::instance()->isQtQuick())
        QSKIP("QtQuick separators handle the mouse in QML");

    Tests::EnsureTopLevelsDeleted e;
    auto m = Tests::createMainWindow();
    auto dw1 = Tests::createDockWidget("dw1");
    auto dw2 = Tests::createDockWidget("dw2");
    m->addDockWidget(dw1, Location_OnLeft, nullptr, InitialOption(Size(200, 200)));
    m->addDockWidget(dw2, Location_OnRight);

    auto separator = firstSeparator(m.get());
    QVERIFY(separator);

    auto separatorView = separator->view();
    const Point pos = separatorView->mapToGlobal(separatorView->rect().center());
    Platform::instance()->tests_doubleClickOn(pos, separatorView);

    // Both sides now have the same width, give or take the separator
    const int w1 = dw1->dptr()->group()->width();
    const int w2 = dw2->dptr()->group()->width();
    QVERIFY(std::abs(w1 - w2) <= 1);

    delete dw1;
    delete dw2;
}

#define KDDW_TEST_NAME TestSeparator
#include "../test_main_qt.h"

#include "tst_separator.moc"
