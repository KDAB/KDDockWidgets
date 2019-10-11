/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// We don't care about performance related checks in the tests
// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates,qstring-allocations

#include "Operations.h"
#include "DockWidgetBase.h"
#include "DockRegistry_p.h"
#include "Fuzzer.h"
#include "../Testing.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;
using namespace KDDockWidgets::Testing::Operations;

OperationBase::OperationBase(KDDockWidgets::Testing::Operations::OperationType type, Fuzzer *fuzzer)
    : m_operationType(type)
    , m_fuzzer(fuzzer)
{

}

OperationBase::~OperationBase()
{
}

void OperationBase::execute()
{
    execute_impl();
}

DockWidgetBase *OperationBase::dockByName(const QString &name) const
{
    return DockRegistry::self()->dockByName(name);
}

MainWindowBase *OperationBase::mainWindowByName(const QString &name) const
{
    return DockRegistry::self()->mainWindowByName(name);
}

CloseViaDockWidgetAPI::CloseViaDockWidgetAPI(Fuzzer *fuzzer)
    : OperationBase(OperationType_CloseViaDockWidgetAPI, fuzzer)
{
}

void CloseViaDockWidgetAPI::execute_impl()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget()) {
        auto fw = qobject_cast<FloatingWindow*>(dw->window());
        dw->close();
        if (fw && fw->beingDeleted())
            Testing::waitForDeleted(fw);

    }
}

HideViaDockWidgetAPI::HideViaDockWidgetAPI(Fuzzer *fuzzer)
    : OperationBase(OperationType_HideViaDockWidgetAPI, fuzzer)
{
}

void HideViaDockWidgetAPI::execute_impl()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget()) {
        auto fw = qobject_cast<FloatingWindow*>(dw->window());
        dw->hide();
        if (fw && fw->beingDeleted())
            Testing::waitForDeleted(fw);
    }
}

ShowViaDockWidgetAPI::ShowViaDockWidgetAPI(Fuzzer *fuzzer)
    : OperationBase(OperationType_ShowViaDockWidgetAPI, fuzzer)
{
}

void ShowViaDockWidgetAPI::execute_impl()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget())
        dw->show();
}

AddDockWidget::AddDockWidget(Fuzzer *fuzzer)
    : OperationBase(OperationType_AddDockWidget, fuzzer)
{
}

void AddDockWidget::execute_impl()
{
    const Fuzzer::AddDockWidgetParams params = m_fuzzer->getRandomAddDockWidgetParams();

    auto fw = qobject_cast<FloatingWindow*>(params.dockWidget->window());
    params.mainWindow->addDockWidget(params.dockWidget, params.location, params.relativeTo, params.addingOption);
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
}
