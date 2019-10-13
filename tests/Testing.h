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

#ifndef KDDOCKWIDGETS_TESTING_H
#define KDDOCKWIDGETS_TESTING_H

#include "KDDockWidgets.h"
#include "MainWindowBase.h"
#include "DockWidgetBase.h"
#include "DockRegistry_p.h"

#include <QSize>
#include <QRect>
#include <QVector>
#include <QEvent>
#include <QWidget>
#include <QVariant>

/**
 * @file
 * @brief Namespace for tests related enums and classes
 */

namespace KDDockWidgets {


namespace Testing {

    class WarningObserver
    {
    public:
        virtual void onFatal() = 0;
    };

    struct AddDockWidgetParams {
        MainWindowBase *mainWindow;
        DockWidgetBase *dockWidget;
        DockWidgetBase *relativeTo;
        KDDockWidgets::Location location;
        KDDockWidgets::AddingOption addingOption;

        QVariantMap toVariantMap() const
        {
            QVariantMap map;
            map["mainWindowName"] = mainWindow->uniqueName();
            map["dockWidgetName"] = dockWidget->uniqueName();

            if (relativeTo)
                map["relativeToName"] = relativeTo->uniqueName();

            map["location"] = location;
            map["addingOption"] = addingOption;

            return map;
        }

        void fillFromVariantMap(const QVariantMap &map)
        {
            const QString mainWindowName = map["mainWindowName"].toString();
            const QString dockWidgetName = map["dockWidgetName"].toString();
            const QString relativeToName = map["relativeToName"].toString();
            location = KDDockWidgets::Location(map["location"].toInt());
            addingOption = KDDockWidgets::AddingOption(map["addingOption"].toInt());


            if (mainWindowName.isEmpty())
                mainWindow = nullptr;
            else
                mainWindow = DockRegistry::self()->mainWindowByName(mainWindowName);

            if (dockWidgetName.isEmpty())
                dockWidget = nullptr;
            else
                dockWidget = DockRegistry::self()->dockByName(dockWidgetName);

            if (relativeToName.isEmpty())
                relativeTo = nullptr;
            else
                relativeTo = DockRegistry::self()->dockByName(relativeToName);
        }
    };

    void setWarningObserver(WarningObserver *);

    void installFatalMessageHandler();
    void setExpectedWarning(const QString &);

    bool waitForEvent(QWidget *w, QEvent::Type type, int timeout = 2000);
    bool waitForDeleted(QObject *o, int timeout = 2000);
    bool waitForResize(QWidget *w, int timeout = 2000);

    class HostedWidget : public QWidget
    {
    public:

        explicit HostedWidget(QSize minSz = QSize(1,1))
            : m_minSz(minSz)
        {
        }

        ~HostedWidget() override;

        QSize sizeHint() const override
        {
            return m_minSz;
        }

        QSize minimumSizeHint() const override
        {
            return m_minSz;
        }

        void setMinSize(QSize s)
        {
            m_minSz = s;
            updateGeometry();
        }

        QSize m_minSz;
    };
}
}

#endif
