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

QVariantMap OperationBase::toVariantMap() const
{
    const QVariantMap params = paramsToVariantMap();
    if (params.isEmpty()) {
        qDebug() << Q_FUNC_INFO << "Invalid params" << m_operationType;
        return {};
    }

    QVariantMap map;
    map["type"] = m_operationType;
    map["params"] = params;

    return map;
}

OperationBase::Ptr OperationBase::fromVariantMap(Fuzzer *fuzzer, const QVariantMap &map)
{
    OperationBase::Ptr ptr;

    if (!map.contains("type") || !map.contains("params")) {
        qDebug() << Q_FUNC_INFO << "Invalid map";
        return {};
    }

    auto operationType = OperationType(map["type"].toInt());
    switch (operationType) {
    case OperationType_Count:
    case OperationType_None:
        break;
    case OperationType_CloseViaDockWidgetAPI:
        ptr = OperationBase::Ptr(new CloseViaDockWidgetAPI(fuzzer));
        break;
    case OperationType_HideViaDockWidgetAPI:
        ptr = OperationBase::Ptr(new HideViaDockWidgetAPI(fuzzer));
        break;
    case OperationType_ShowViaDockWidgetAPI:
        ptr = OperationBase::Ptr(new ShowViaDockWidgetAPI(fuzzer));
        break;
    case OperationType_AddDockWidget:
        ptr = OperationBase::Ptr(new AddDockWidget(fuzzer));
        break;
    case OperationType_AddDockWidgetAsTab:
        ptr = OperationBase::Ptr(new AddDockWidgetAsTab(fuzzer));
        break;
    }

    if (ptr) {

        const QVariantMap params = map["params"].toMap();
        if (params.isEmpty()) {
            qDebug() << Q_FUNC_INFO << "Invalid params";
        } else {
            ptr->fillParamsFromVariantMap(params);
        }
    } else {
        qDebug() << Q_FUNC_INFO << "Failed to fill params";
    }

    return ptr;
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
        if (dw->isVisible()) {
            m_dockWidgetName = dw->uniqueName();
            auto fw = qobject_cast<FloatingWindow*>(dw->window());
            dw->close();
            if (fw && fw->beingDeleted())
                Testing::waitForDeleted(fw);
        }
    }
}

QVariantMap CloseViaDockWidgetAPI::paramsToVariantMap() const
{
    QVariantMap map;
    if (!m_dockWidgetName.isEmpty())
        map["dockWidgetName"] = m_dockWidgetName;
    return map;
}

void CloseViaDockWidgetAPI::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_dockWidgetName = map["dockWidgetName"].toString();
}

HideViaDockWidgetAPI::HideViaDockWidgetAPI(Fuzzer *fuzzer)
    : OperationBase(OperationType_HideViaDockWidgetAPI, fuzzer)
{
}

void HideViaDockWidgetAPI::execute_impl()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget()) {
        if (dw->isVisible()) {
            m_dockWidgetName = dw->uniqueName();
            auto fw = qobject_cast<FloatingWindow*>(dw->window());
            dw->hide();
            if (fw && fw->beingDeleted())
                Testing::waitForDeleted(fw);
        }
    }
}

QVariantMap HideViaDockWidgetAPI::paramsToVariantMap() const
{
    QVariantMap map;
    if (!m_dockWidgetName.isEmpty())
        map["dockWidgetName"] = m_dockWidgetName;
    return map;
}

void HideViaDockWidgetAPI::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_dockWidgetName = map["dockWidgetName"].toString();
}

ShowViaDockWidgetAPI::ShowViaDockWidgetAPI(Fuzzer *fuzzer)
    : OperationBase(OperationType_ShowViaDockWidgetAPI, fuzzer)
{
}

void ShowViaDockWidgetAPI::execute_impl()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget()) {
        if (!dw->isVisible()) {
            m_dockWidgetName = dw->uniqueName();
            dw->show();
        }
    }
}

QVariantMap ShowViaDockWidgetAPI::paramsToVariantMap() const
{
    QVariantMap map;
    if (!m_dockWidgetName.isEmpty())
        map["dockWidgetName"] = m_dockWidgetName;
    return map;
}

void ShowViaDockWidgetAPI::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_dockWidgetName = map["dockWidgetName"].toString();
}

AddDockWidget::AddDockWidget(Fuzzer *fuzzer)
    : OperationBase(OperationType_AddDockWidget, fuzzer)
{
}

void AddDockWidget::execute_impl()
{
    m_params = m_fuzzer->getRandomAddDockWidgetParams();

    auto fw = qobject_cast<FloatingWindow*>(m_params->dockWidget()->window());
    m_params->mainWindow()->addDockWidget(m_params->dockWidget(), m_params->location,
                                          m_params->relativeTo(), m_params->addingOption);
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
}

QVariantMap AddDockWidget::paramsToVariantMap() const
{
    if (!m_params)
        qDebug() << Q_FUNC_INFO << "Invalid params!";

    return m_params ? m_params->toVariantMap()
                    : QVariantMap();
}

void AddDockWidget::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_params = AddDockWidgetParams::fillFromVariantMap(map);
}

AddDockWidgetAsTab::AddDockWidgetAsTab(Fuzzer *fuzzer)
    : OperationBase(OperationType_AddDockWidgetAsTab, fuzzer)
{
}

void AddDockWidgetAsTab::execute_impl()
{
    DockWidgetBase *dw = m_fuzzer->getRandomDockWidget();
    DockWidgetBase *dw2 = m_fuzzer->getRandomDockWidget(dw);

    m_dockWidgetName = dw->uniqueName();
    m_dockWidgetToAddName = dw2->uniqueName();

    auto fw = qobject_cast<FloatingWindow*>(dw2->window());
    dw->addDockWidgetAsTab(dw2);
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
}

QVariantMap AddDockWidgetAsTab::paramsToVariantMap() const
{
    QVariantMap map;

    map["dockWidgetName"] = m_dockWidgetName;
    map["dockWidgetToAddName"] = m_dockWidgetToAddName;

    return map;
}

void AddDockWidgetAsTab::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_dockWidgetName = map["dockWidgetName"].toString();
    m_dockWidgetToAddName = map["dockWidgetToAddName"].toString();
}
