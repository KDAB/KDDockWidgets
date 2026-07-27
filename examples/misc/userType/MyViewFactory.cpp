/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2026 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "MyViewFactory.h"

#include <kddockwidgets/qtwidgets/views/TitleBar.h>
#include <kddockwidgets/qtwidgets/views/Group.h>
#include <kddockwidgets/qtwidgets/views/TabBar.h>
#include <kddockwidgets/qtcommon/View.h>
#include <kddockwidgets/core/TitleBar.h>

#include <QPainter>

// clazy:excludeall=missing-qobject-macro,ctor-missing-parent-argument

using namespace KDDockWidgets;

namespace {

/// TitleBar for DockWidgets with UserType_Note. Just paints itself blue with a "NOTE" prefix.
class NoteTitleBar : public QtWidgets::TitleBar
{
public:
    explicit NoteTitleBar(Core::TitleBar *controller, Core::View *parent = nullptr)
        : QtWidgets::TitleBar(controller, parent)
        , m_controller(controller)
    {
    }

    ~NoteTitleBar() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), QColor(70, 130, 180)); // steel blue
        p.setPen(Qt::white);
        QFont f = p.font();
        f.setBold(true);
        p.setFont(f);
        p.drawText(rect().adjusted(8, 0, -8, 0), Qt::AlignVCenter | Qt::AlignLeft,
                   QStringLiteral("NOTE: %1").arg(m_controller->title()));
    }

private:
    Core::TitleBar *const m_controller;
};

NoteTitleBar::~NoteTitleBar() = default;

/// TitleBar for DockWidgets with UserType_Task. Just paints itself green with a "TASK" prefix.
class TaskTitleBar : public QtWidgets::TitleBar
{
public:
    explicit TaskTitleBar(Core::TitleBar *controller, Core::View *parent = nullptr)
        : QtWidgets::TitleBar(controller, parent)
        , m_controller(controller)
    {
    }

    ~TaskTitleBar() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), QColor(60, 160, 80)); // green
        p.setPen(Qt::white);
        QFont f = p.font();
        f.setBold(true);
        p.setFont(f);
        p.drawText(rect().adjusted(8, 0, -8, 0), Qt::AlignVCenter | Qt::AlignLeft,
                   QStringLiteral("TASK: %1").arg(m_controller->title()));
    }

private:
    Core::TitleBar *const m_controller;
};

TaskTitleBar::~TaskTitleBar() = default;

/// TitleBar for DockWidgets with UserType_Alert. Just paints itself red with an "ALERT" prefix.
class AlertTitleBar : public QtWidgets::TitleBar
{
public:
    explicit AlertTitleBar(Core::TitleBar *controller, Core::View *parent = nullptr)
        : QtWidgets::TitleBar(controller, parent)
        , m_controller(controller)
    {
    }

    ~AlertTitleBar() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), QColor(200, 60, 60)); // red
        p.setPen(Qt::white);
        QFont f = p.font();
        f.setBold(true);
        p.setFont(f);
        p.drawText(rect().adjusted(8, 0, -8, 0), Qt::AlignVCenter | Qt::AlignLeft,
                   QStringLiteral("ALERT: %1").arg(m_controller->title()));
    }

private:
    Core::TitleBar *const m_controller;
};

AlertTitleBar::~AlertTitleBar() = default;

/// Group for DockWidgets with UserType_Note. Draws a blue border, matching NoteTitleBar.
class NoteGroup : public QtWidgets::Group
{
public:
    explicit NoteGroup(Core::Group *controller, QWidget *parent = nullptr)
        : QtWidgets::Group(controller, parent)
    {
    }

    ~NoteGroup() override;

protected:
    void paintEvent(QPaintEvent *ev) override
    {
        QtWidgets::Group::paintEvent(ev);
        QPainter p(this);
        QPen pen(QColor(70, 130, 180)); // steel blue, matches NoteTitleBar
        pen.setWidth(3);
        p.setPen(pen);
        p.drawRect(rect().adjusted(1, 1, -2, -2));
    }
};

NoteGroup::~NoteGroup() = default;

/// Group for DockWidgets with UserType_Task. Draws a green border, matching TaskTitleBar.
class TaskGroup : public QtWidgets::Group
{
public:
    explicit TaskGroup(Core::Group *controller, QWidget *parent = nullptr)
        : QtWidgets::Group(controller, parent)
    {
    }

    ~TaskGroup() override;

protected:
    void paintEvent(QPaintEvent *ev) override
    {
        QtWidgets::Group::paintEvent(ev);
        QPainter p(this);
        QPen pen(QColor(60, 160, 80)); // green, matches TaskTitleBar
        pen.setWidth(3);
        p.setPen(pen);
        p.drawRect(rect().adjusted(1, 1, -2, -2));
    }
};

TaskGroup::~TaskGroup() = default;

/// Group for DockWidgets with UserType_Alert. Draws a red border, matching AlertTitleBar.
class AlertGroup : public QtWidgets::Group
{
public:
    explicit AlertGroup(Core::Group *controller, QWidget *parent = nullptr)
        : QtWidgets::Group(controller, parent)
    {
    }

    ~AlertGroup() override;

protected:
    void paintEvent(QPaintEvent *ev) override
    {
        QtWidgets::Group::paintEvent(ev);
        QPainter p(this);
        QPen pen(QColor(200, 60, 60)); // red, matches AlertTitleBar
        pen.setWidth(3);
        p.setPen(pen);
        p.drawRect(rect().adjusted(1, 1, -2, -2));
    }
};

AlertGroup::~AlertGroup() = default;

/// TabBar for DockWidgets with UserType_Note. Tints its background blue, matching NoteTitleBar.
class NoteTabBar : public QtWidgets::TabBar
{
public:
    explicit NoteTabBar(Core::TabBar *controller, QWidget *parent = nullptr)
        : QtWidgets::TabBar(controller, parent)
    {
        setStyleSheet(QStringLiteral("QTabBar { background: rgba(70, 130, 180, 60); }"));
    }
};

/// TabBar for DockWidgets with UserType_Task. Tints its background green, matching TaskTitleBar.
class TaskTabBar : public QtWidgets::TabBar
{
public:
    explicit TaskTabBar(Core::TabBar *controller, QWidget *parent = nullptr)
        : QtWidgets::TabBar(controller, parent)
    {
        setStyleSheet(QStringLiteral("QTabBar { background: rgba(60, 160, 80, 60); }"));
    }
};

/// TabBar for DockWidgets with UserType_Alert. Tints its background red, matching AlertTitleBar.
class AlertTabBar : public QtWidgets::TabBar
{
public:
    explicit AlertTabBar(Core::TabBar *controller, QWidget *parent = nullptr)
        : QtWidgets::TabBar(controller, parent)
    {
        setStyleSheet(QStringLiteral("QTabBar { background: rgba(200, 60, 60, 60); }"));
    }
};

}

Core::View *UserDataViewFactory::createTitleBar(Core::TitleBar *controller, Core::View *parent,
                                                int userType) const
{
    // This is called once per TitleBar, with the userType() of the DockWidget that's initially
    // covered by it (see DockWidget::setUserType()). Note that a group can later have more
    // dock widgets tabbed into it, with different userTypes; only the initiating one is
    // reflected here, as the TitleBar's C++ type can't change afterwards.
    switch (userType) {
    case UserType_Note:
        return new NoteTitleBar(controller, parent);
    case UserType_Task:
        return new TaskTitleBar(controller, parent);
    case UserType_Alert:
        return new AlertTitleBar(controller, parent);
    default:
        // Fall back to the default styling for anything we don't recognize
        return QtWidgets::ViewFactory::createTitleBar(controller, parent);
    }
}

Core::View *UserDataViewFactory::createGroup(Core::Group *controller, Core::View *parent,
                                             int userType) const
{
    // Same idea as createTitleBar() above, but for the Group (the widget that holds the
    // title bar and tab widget together). Also only reflects the userType() of the DockWidget
    // that caused the group to be created.
    QWidget *parentWidget = QtCommon::View_qt::asQWidget(parent);
    switch (userType) {
    case UserType_Note:
        return new NoteGroup(controller, parentWidget);
    case UserType_Task:
        return new TaskGroup(controller, parentWidget);
    case UserType_Alert:
        return new AlertGroup(controller, parentWidget);
    default:
        // Fall back to the default styling for anything we don't recognize
        return QtWidgets::ViewFactory::createGroup(controller, parent);
    }
}

Core::View *UserDataViewFactory::createTabBar(Core::TabBar *tabBar, Core::View *parent,
                                              int userType) const
{
    // Same idea again, but for the TabBar. Reflects the userType() of the DockWidget that
    // caused the tab bar's Group to be created, not necessarily of every tab in it.
    QWidget *parentWidget = QtCommon::View_qt::asQWidget(parent);
    switch (userType) {
    case UserType_Note:
        return new NoteTabBar(tabBar, parentWidget);
    case UserType_Task:
        return new TaskTabBar(tabBar, parentWidget);
    case UserType_Alert:
        return new AlertTabBar(tabBar, parentWidget);
    default:
        // Fall back to the default styling for anything we don't recognize
        return QtWidgets::ViewFactory::createTabBar(tabBar, parent);
    }
}
