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

#include <QTest>

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
    if (!hasParams())
        generateRandomParams();

    if (hasParams()) // Check again, as generateRandomParams() is not guaranteed
        execute_impl();
}

QVariantMap OperationBase::toVariantMap() const
{
    const QVariantMap params = paramsToVariantMap();
    if (params.isEmpty()) {
        return {};
    }

    QVariantMap map;
    map["type"] = m_operationType;
    map["params"] = params;
    map["comment"] = description();

    return map;
}

OperationBase::Ptr OperationBase::fromVariantMap(Fuzzer *fuzzer, const QVariantMap &map)
{
    if (!map.contains("type") || !map.contains("params")) {
        qDebug() << Q_FUNC_INFO << "Invalid map";
        return {};
    }

    auto operationType = OperationType(map["type"].toInt());

    OperationBase::Ptr ptr = OperationBase::newOperation(fuzzer, operationType);
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

OperationBase::Ptr OperationBase::newOperation(Fuzzer *fuzzer, OperationType type)
{
    OperationBase::Ptr ptr;

    switch (type) {
    case OperationType_Count:
    case OperationType_None:
        qDebug() << Q_FUNC_INFO << "Invalid type";
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
    case OperationType_Pause:
        ptr = OperationBase::Ptr(new Pause(fuzzer));
        break;
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

QString CloseViaDockWidgetAPI::description() const
{
    return QStringLiteral("Closing %1").arg(m_dockWidgetName);
}

void CloseViaDockWidgetAPI::generateRandomParams()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget())
        if (dw->isVisible())
            m_dockWidgetName = dw->uniqueName();
}

bool CloseViaDockWidgetAPI::hasParams() const
{
    return !m_dockWidgetName.isEmpty();
}

void CloseViaDockWidgetAPI::execute_impl()
{
    DockWidgetBase *dw = dockByName(m_dockWidgetName);
    auto fw = qobject_cast<FloatingWindow*>(dw->window());
    dw->close();
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
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

QString HideViaDockWidgetAPI::description() const
{
    return QStringLiteral("Hidding %1").arg(m_dockWidgetName);
}

void HideViaDockWidgetAPI::generateRandomParams()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget())
        if (dw->isVisible())
            m_dockWidgetName = dw->uniqueName();
}

bool HideViaDockWidgetAPI::hasParams() const
{
    return !m_dockWidgetName.isEmpty();
}

void HideViaDockWidgetAPI::execute_impl()
{
    DockWidgetBase *dw = dockByName(m_dockWidgetName);
    auto fw = qobject_cast<FloatingWindow*>(dw->window());
    dw->close();
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
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

QString ShowViaDockWidgetAPI::description() const
{
    return QStringLiteral("Showing %1").arg(m_dockWidgetName);
}

void ShowViaDockWidgetAPI::generateRandomParams()
{
    if (DockWidgetBase *dw = m_fuzzer->getRandomDockWidget())
        if (!dw->isVisible())
            m_dockWidgetName = dw->uniqueName();
}

bool ShowViaDockWidgetAPI::hasParams() const
{
    return !m_dockWidgetName.isEmpty();
}

void ShowViaDockWidgetAPI::execute_impl()
{
    DockWidgetBase *dw = dockByName(m_dockWidgetName);
    dw->show();
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

QString AddDockWidget::description() const
{
    if (!hasParams())
        return QStringLiteral("null");

    if (m_params->relativeToName.isEmpty())
        return QStringLiteral("AddDockWidget %1 to %2").arg(m_params->dockWidgetName).arg(m_params->location);
    else
        return QStringLiteral("AddDockWidget %1 to %2, relative to %3").arg(m_params->dockWidgetName).arg(m_params->location).arg(m_params->relativeToName);
}

void AddDockWidget::generateRandomParams()
{
    m_params = m_fuzzer->getRandomAddDockWidgetParams();
}

bool AddDockWidget::hasParams() const
{
    return m_params.has_value();
}

void AddDockWidget::execute_impl()
{
    auto fw = qobject_cast<FloatingWindow*>(m_params->dockWidget()->window());
    m_params->mainWindow()->addDockWidget(m_params->dockWidget(), m_params->location,
                                          m_params->relativeTo(), m_params->addingOption);
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
}

QVariantMap AddDockWidget::paramsToVariantMap() const
{
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

QString AddDockWidgetAsTab::description() const
{
    if (!hasParams())
        return QStringLiteral("null");

    return QStringLiteral("AddDockWidgetAsTab %1 onto %2").arg(m_dockWidgetToAddName, m_dockWidgetName);
}

void AddDockWidgetAsTab::generateRandomParams()
{
    DockWidgetBase *dw = m_fuzzer->getRandomDockWidget();
    if (!dw)
        return;

    DockWidgetBase *dw2 = nullptr;

    if (auto frame = dw->frame()) {
        auto toExclude = frame->dockWidgets();
        for (auto dockWidget : DockRegistry::self()->dockwidgets()) {
            if (dockWidget->window() == dw->window())
                toExclude.push_back(dockWidget);
        }

        dw2 = m_fuzzer->getRandomDockWidget(toExclude);
    }

    if (!dw2)
        return;
    m_dockWidgetName = dw->uniqueName();
    m_dockWidgetToAddName = dw2->uniqueName();
}

bool AddDockWidgetAsTab::hasParams() const
{
    return !m_dockWidgetName.isEmpty() && !m_dockWidgetToAddName.isEmpty();
}

void AddDockWidgetAsTab::execute_impl()
{
    DockWidgetBase *dw = dockByName(m_dockWidgetName);
    DockWidgetBase *dw2 = dockByName(m_dockWidgetToAddName);

    auto fw = qobject_cast<FloatingWindow*>(dw2->window());
    dw->addDockWidgetAsTab(dw2);
    if (fw && fw->beingDeleted())
        Testing::waitForDeleted(fw);
}

QVariantMap AddDockWidgetAsTab::paramsToVariantMap() const
{
    QVariantMap map;

    if (hasParams()) {
        map["dockWidgetName"] = m_dockWidgetName;
        map["dockWidgetToAddName"] = m_dockWidgetToAddName;
    }

    return map;
}

void AddDockWidgetAsTab::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_dockWidgetName = map["dockWidgetName"].toString();
    m_dockWidgetToAddName = map["dockWidgetToAddName"].toString();
}

Pause::Pause(Fuzzer *fuzzer)
    : OperationBase(OperationType_Pause, fuzzer)
{

}

QString Pause::description() const
{
    return QStringLiteral("Pausing for %1 ms").arg(m_sleepTimeMS);
}

void Pause::execute_impl()
{
    qDebug() << Q_FUNC_INFO << "Sleeping for" << m_sleepTimeMS << "...";
    QTest::qWait(m_sleepTimeMS);
}

QVariantMap Pause::paramsToVariantMap() const
{
    QVariantMap map;
    map["sleepTimeMS"] = m_sleepTimeMS;
    return map;
}

void Pause::fillParamsFromVariantMap(const QVariantMap &map)
{
    m_sleepTimeMS = map["sleepTimeMS"].toInt();
}
