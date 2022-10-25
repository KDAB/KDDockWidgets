/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/View.h"

QT_BEGIN_NAMESPACE
class QWidget;
class QQuickItem;
QT_END_NAMESPACE

namespace KDDockWidgets {
class Controller;
class EventFilter;
}

namespace KDDockWidgets::Views {

class DOCKS_EXPORT View_qt : public View
{
public:
    explicit View_qt(Controller *controller, Type type, QObject *thisObj);
    ~View_qt() override;

    QObject *thisObject() const;

    HANDLE handle() const override;
    void setObjectName(const QString &name) override;

    static QObject *asQObject(View *);

#ifdef KDDW_FRONTEND_QTWIDGETS
    static QWidget *asQWidget(View *);
    static QWidget *asQWidget(Controller *);
#endif

#ifdef KDDW_FRONTEND_QTQUICK
    static QQuickItem *asQQuickItem(View *);
#endif


    /// for debug purposes
    QDebug toQDebug(QDebug &deb) const override
    {
        deb << m_thisObj;
        return deb;
    }

protected:
    class EventFilter;
    EventFilter *const m_eventFilter;
    QObject *const m_thisObj;
};

}
