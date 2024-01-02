/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "../simple_test_framework.h"
#include "core/Separator.h"
#include "core/Platform.h"
#include "core/DropArea.h"

using namespace KDDockWidgets;

KDDW_QCORO_TASK tst_separatorCtor()
{
    Core::DropArea dropArea(nullptr, MainWindowOption_None);
    Core::Separator separator(dropArea.asLayoutingHost(), Qt::Vertical, nullptr);
    CHECK(separator.view()->is(Core::ViewType::Separator));
    CHECK(separator.view()->asWrapper()->is(Core::ViewType::Separator));

    KDDW_TEST_RETURN(true);
}

static const auto s_tests = std::vector<KDDWTest> { TEST(tst_separatorCtor) };

#include "../tests_main.h"
