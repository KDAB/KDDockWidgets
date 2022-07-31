/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

// tag=1040
#include "KDDockWidgetsBindings_exports.h"
#include <KDDockWidgets.h>
#include <qsize.h>

namespace KDDockWidgetsBindings_wrappersNS {
// tag=1043
class InitialOption_wrapper : public ::KDDockWidgets::InitialOption
{
public:
    ~InitialOption_wrapper();
    // tag=1041
    InitialOption_wrapper();
    // tag=1041
    InitialOption_wrapper(QSize size);
    // tag=1041
    bool preservesCurrentTab() const;
    // tag=1041
    bool startsHidden() const;
};
}
extern "C" {

// tag=1067
//  KDDockWidgets::InitialOption::InitialOption()
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__InitialOption__constructor();

// tag=1067
//  KDDockWidgets::InitialOption::InitialOption(QSize size)
KDDockWidgetsBindings_EXPORT void *c_KDDockWidgets__InitialOption__constructor_QSize(void *size_);

// tag=1067
//  KDDockWidgets::InitialOption::preservesCurrentTab() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__InitialOption__preservesCurrentTab(void *thisObj);

// tag=1067
//  KDDockWidgets::InitialOption::startsHidden() const
KDDockWidgetsBindings_EXPORT bool c_KDDockWidgets__InitialOption__startsHidden(void *thisObj);

// tag=1066
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__InitialOption__destructor(void *thisObj);

// tag=1047
KDDockWidgetsBindings_EXPORT void c_KDDockWidgets__InitialOption_Finalizer(void *, void *cppObj, void *);
}
