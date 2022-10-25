/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/
#include "KDDockWidgetsBindings_exports.h"
#include <KDDockWidgets.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
class InitialOption_wrapper : public ::KDDockWidgets::InitialOption
{
public:
    ~InitialOption_wrapper();
    InitialOption_wrapper();
    InitialOption_wrapper(KDDockWidgets::DefaultSizeMode mode);
    InitialOption_wrapper(KDDockWidgets::InitialVisibilityOption v);
    InitialOption_wrapper(KDDockWidgets::InitialVisibilityOption v, QSize size);
    InitialOption_wrapper(QSize size);
    bool preservesCurrentTab() const;
    bool startsHidden() const;
};
}
extern "C" {
// KDDockWidgets::InitialOption::InitialOption()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__InitialOption__constructor();
// KDDockWidgets::InitialOption::InitialOption(KDDockWidgets::DefaultSizeMode mode)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__InitialOption__constructor_DefaultSizeMode(int mode);
// KDDockWidgets::InitialOption::InitialOption(KDDockWidgets::InitialVisibilityOption v)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__InitialOption__constructor_InitialVisibilityOption(int v);
// KDDockWidgets::InitialOption::InitialOption(KDDockWidgets::InitialVisibilityOption v, QSize size)
KDDockWidgetsBindings_EXPORT void *
c_KDDockWidgets__InitialOption__constructor_InitialVisibilityOption_QSize(int v, void *size_);
// KDDockWidgets::InitialOption::InitialOption(QSize size)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__InitialOption__constructor_QSize(void *size_);
// KDDockWidgets::InitialOption::preservesCurrentTab() const
KDDockWidgetsBindings_EXPORT bool
c_KDDockWidgets__InitialOption__preservesCurrentTab(void *thisObj);
// KDDockWidgets::InitialOption::startsHidden() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__InitialOption__startsHidden(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__InitialOption__destructor(void *thisObj);
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__InitialOption_Finalizer(void *, void *cppObj,
                                                                           void *);
}
