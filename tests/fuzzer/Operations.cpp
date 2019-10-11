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
#include "../Testing.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;
using namespace KDDockWidgets::Testing::Operations;

OperationBase::OperationBase(KDDockWidgets::Testing::Operations::OperationType type)
    : m_operationType(type)
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

CloseViaDockWidgetAPI::CloseViaDockWidgetAPI(const QString &dockWidgetName)
    : OperationBase(OperationType_CloseViaDockWidgetAPI)
    , m_dockWidgetName(dockWidgetName)
{
}

void CloseViaDockWidgetAPI::execute_impl()
{
    if (auto dw = dockByName(m_dockWidgetName)) {
        auto fw = qobject_cast<FloatingWindow*>(dw->window());
        dw->close();
        if (fw && fw->beingDeleted())
            Testing::waitForDeleted(fw);

    }
}

HideViaDockWidgetAPI::HideViaDockWidgetAPI(const QString &dockWidgetName)
    : OperationBase(OperationType_HideViaDockWidgetAPI)
    , m_dockWidgetName(dockWidgetName)
{
}

void HideViaDockWidgetAPI::execute_impl()
{
    if (auto dw = dockByName(m_dockWidgetName)) {
        auto fw = qobject_cast<FloatingWindow*>(dw->window());
        dw->hide();
        if (fw && fw->beingDeleted())
            Testing::waitForDeleted(fw);
    }
}

ShowViaDockWidgetAPI::ShowViaDockWidgetAPI(const QString &dockWidgetName)
    : OperationBase(OperationType_ShowViaDockWidgetAPI)
    , m_dockWidgetName(dockWidgetName)
{
}

void ShowViaDockWidgetAPI::execute_impl()
{
    if (auto dw = dockByName(m_dockWidgetName))
        dw->show();
}

AddDockWidget::AddDockWidget()
    : OperationBase(OperationType_AddDockWidget)
{
}

void AddDockWidget::execute_impl()
{
  /*  const AddDockWidgetParams params = m_paramsFunc();
    MainWindowBase *mainWindow = mainWindowByName(params.mainWindowName);
    DockWidgetBase *dw = dockByName(params.dockWidgetName);
    DockWidgetBase *relativeTo = dockByName(params.dockWidgetRelativeToName);

    auto fw = qobject_cast<FloatingWindow*>(dw->window());
    mainWindow->addDockWidget(dw, params.location, relativeTo, params.addingOption);
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);*/
}
