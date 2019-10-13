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

#ifndef KDDOCKWIDGETS_TESTING_OPERATIONS_H
#define KDDOCKWIDGETS_TESTING_OPERATIONS_H

#include "KDDockWidgets.h"
#include "../Testing.h"

#include <QObject>
#include <QVector>

#include <memory>
#include <optional>

namespace KDDockWidgets {

class DockWidgetBase;
class MainWindowBase;

namespace Testing {

class Fuzzer;

namespace Operations {

enum OperationType {
    OperationType_None = 0,
    OperationType_CloseViaDockWidgetAPI, ///< Closing programatically via DockWidget::close()
    OperationType_HideViaDockWidgetAPI,  ///< Hidding programatically via DockWidget::hide()
    OperationType_ShowViaDockWidgetAPI,  ///< Hidding programatically via DockWidget::show()
    OperationType_AddDockWidget,         ///< MainWindow::addDockWidget()
    OperationType_AddDockWidgetAsTab,    ///< DockWidget::addDockWidgetAsTab()
    OperationType_Pause,                 ///< Sleeps. Just used for debugging purposes.
    OperationType_Count /// Keep at end
};

///@brief Describes a testable action.
class OperationBase {

public:
    typedef std::shared_ptr<OperationBase> Ptr;
    typedef QVector<OperationBase::Ptr> List;
    explicit OperationBase(OperationType, Fuzzer *);
    virtual ~OperationBase();

    void execute();

    QVariantMap toVariantMap() const;
    static OperationBase::Ptr fromVariantMap(Fuzzer *fuzzer, const QVariantMap &);
    static OperationBase::Ptr newOperation(Fuzzer *fuzzer, OperationType);

    OperationType type() const { return m_operationType; }

protected:
    virtual bool hasParams() const = 0;
    virtual void execute_impl() = 0;
    virtual void generateRandomParams() = 0;
    virtual QVariantMap paramsToVariantMap() const = 0;
    virtual void fillParamsFromVariantMap(const QVariantMap &) = 0;
    DockWidgetBase* dockByName(const QString &) const;
    MainWindowBase* mainWindowByName(const QString &) const;

    const OperationType m_operationType;
    Fuzzer *const m_fuzzer;
};

class CloseViaDockWidgetAPI : public OperationBase
{
public:
    explicit CloseViaDockWidgetAPI(Fuzzer *);

protected:
    void generateRandomParams() override;
    bool hasParams() const override;
    void execute_impl() override;
    QVariantMap paramsToVariantMap() const override;
    void fillParamsFromVariantMap(const QVariantMap &) override;
    QString m_dockWidgetName;
};

class HideViaDockWidgetAPI : public OperationBase
{
public:
    explicit HideViaDockWidgetAPI(Fuzzer *);

protected:
    void generateRandomParams() override;
    bool hasParams() const override;
    void execute_impl() override;
    QVariantMap paramsToVariantMap() const override;
    void fillParamsFromVariantMap(const QVariantMap &) override;
    QString m_dockWidgetName;
};

class ShowViaDockWidgetAPI : public OperationBase
{
public:
    explicit ShowViaDockWidgetAPI(Fuzzer *);

protected:
    void generateRandomParams() override;
    bool hasParams() const override;
    void execute_impl() override;
    QVariantMap paramsToVariantMap() const override;
    void fillParamsFromVariantMap(const QVariantMap &) override;
    QString m_dockWidgetName;
};

class AddDockWidget : public OperationBase
{
public:
    explicit AddDockWidget(Fuzzer *);

protected:
    void generateRandomParams() override;
    bool hasParams() const override;
    void execute_impl() override;
    QVariantMap paramsToVariantMap() const override;
    void fillParamsFromVariantMap(const QVariantMap &) override;
private:
    std::optional<Testing::AddDockWidgetParams> m_params;
};

class AddDockWidgetAsTab : public OperationBase
{
public:
    explicit AddDockWidgetAsTab(Fuzzer *);

protected:
    void generateRandomParams() override;
    bool hasParams() const override;
    void execute_impl() override;
    QVariantMap paramsToVariantMap() const override;
    void fillParamsFromVariantMap(const QVariantMap &) override;
private:
    QString m_dockWidgetName;
    QString m_dockWidgetToAddName;
};

class Pause : public OperationBase
{
public:
    explicit Pause(Fuzzer *);

protected:
    void generateRandomParams() override { m_sleepTimeMS = 6000000; }
    bool hasParams() const override { return m_sleepTimeMS != -1; }
    void execute_impl() override;
    QVariantMap paramsToVariantMap() const override;
    void fillParamsFromVariantMap(const QVariantMap &) override;
private:
    int m_sleepTimeMS = 6000000;
};

}
}
}

#endif
