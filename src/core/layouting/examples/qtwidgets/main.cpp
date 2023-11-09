/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/// Demonstrates how to use the KDDW layouting engine without the docking components
///
/// This is done by subclassing Core::LayoutingSeparator, Core::LayoutingGuest and Core::LayoutingHost

#include "../../Item_p.h"
#include "../../LayoutingHost_p.h"
#include "../../LayoutingGuest_p.h"
#include "../../LayoutingSeparator_p.h"

#include <QApplication>
#include <QDebug>
#include <QPainter>

using namespace KDDockWidgets;

namespace {

/// The separator separates widgets and offer mouse interaction for resize
class Separator : public QWidget, public Core::LayoutingSeparator
{
public:
    explicit Separator(Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container)
        : QWidget(dynamic_cast<QWidget *>(host))
        , Core::LayoutingSeparator(host, orientation, container)
    {
    }

    Rect geometry() const override
    {
        return QWidget::geometry();
    }

    void setGeometry(Rect r) override
    {
        QWidget::setGeometry(r);
    }
};

/// The Host is the widget which will contain (parent) all the Guest and Separator widgets
class Host : public QWidget, public Core::LayoutingHost
{
public:
    Host()
        : root(Core::ItemBoxContainer(this))
    {
        setObjectName("LayoutingHost QWidget");
        root.setSize_recursive(size());
    }

    bool supportsHonouringLayoutMinSize() const override
    {
        // Yes, it's supported by QtWidgets
        return true;
    }

    /// Our layout needs to be resized as well
    void resizeEvent(QResizeEvent *) override
    {
        root.setSize_recursive(size());
    }

    /// Inserts a guest widget into the layout, to the specified location with some initial options
    /// the location is relative to the window, meaning Location_OnBottom will make the widget fill
    /// the entire bottom
    void insertItem(Core::LayoutingGuest *guest, Location loc,
                    InitialOption initialOption = {})
    {
        if (!guest || !guest->layoutItem) {
            qWarning() << "insertItem: Something is null!";
            return;
        }

        root.insertItem(guest->layoutItem, loc, initialOption);
    }

    /// Inserts a guest widget into the layout but relative to another widget
    /// Similar to insertItem() but it's not relative to the window.
    /// See example in src/core/layouting/examples/qtwidgets/main.cpp
    void insertItemRelativeTo(Core::LayoutingGuest *guest, Core::LayoutingGuest *relativeTo, Location loc,
                              InitialOption initialOption = {})
    {
        if (!guest || !relativeTo || !guest->layoutItem || !relativeTo->layoutItem) {
            qWarning() << "insertItemRelativeTo: Something is null!";
            return;
        }

        root.insertItemRelativeTo(guest->layoutItem, relativeTo->layoutItem, loc, initialOption);
    }

    Core::ItemBoxContainer root;
};

/// The Guest wraps the widget you want to put into the layout
class Guest : public QWidget, public Core::LayoutingGuest
{
public:
    explicit Guest(Host *host, const QString &uniqueName, QColor color)
        : m_uniqueName(uniqueName)
        , m_color(color)
    {
        setObjectName(QString("%1 %2").arg(uniqueName).arg(color.name()));
        auto item = new Core::Item(host);
        item->setGuest(this);
    }

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.fillRect(rect(), m_color);
    }

    Size minSize() const override
    {
        return QWidget::minimumSize();
    }

    Size maxSizeHint() const override
    {
        return QWidget::maximumSize();
    }

    void setGeometry(Rect r) override
    {
        QWidget::setGeometry(r);
    }

    void setVisible(bool is) override
    {
        QWidget::setVisible(is);
    }

    Rect geometry() const override
    {
        return QWidget::geometry();
    }

    QString debugName() const override
    {
        return objectName();
    }

    void setHost(Core::LayoutingHost *parent) override
    {
        if (auto p = dynamic_cast<QWidget *>(parent)) {
            QWidget::setParent(p);
        } else if (!parent) {
            QWidget::setParent(nullptr);
        } else {
            qFatal("Expected a QWidget");
        }
    }

    Core::LayoutingHost *host() const override
    {
        return dynamic_cast<Core::LayoutingHost *>(parentWidget());
    }

    QString id() const override
    {
        return m_uniqueName;
    }

    virtual bool freed() const override
    {
        return false;
    }

    const QString m_uniqueName;
    const QColor m_color;
};

}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    /// Tell KDDW about our separators
    Core::Item::setCreateSeparatorFunc([](Core::LayoutingHost *host, Qt::Orientation orientation, Core::ItemBoxContainer *container) -> Core::LayoutingSeparator * {
        return new Separator(host, orientation, container);
    });

    Host host;
    host.resize(1000, 1000);

    auto guest1 = new Guest(&host, "1", QColor("#41729F"));
    auto guest2 = new Guest(&host, "2", QColor("#5885AF"));
    auto guest3 = new Guest(&host, "3", QColor("#274472"));
    auto guest4 = new Guest(&host, "4", QColor("#C3E0E5"));

    // Guest1 will occupy the whole left
    host.insertItem(guest1, KDDockWidgets::Location_OnLeft);

    // Guest2 will occupy the whole right
    host.insertItem(guest2, KDDockWidgets::Location_OnRight);


    // Actually guest2 will need to split the right side with guest 3 as well.
    host.insertItemRelativeTo(guest3, /*relativeTo=*/guest2, KDDockWidgets::Location_OnBottom);

    // Guest4 goes on top of everything, but with 200px height (width is ignored)
    host.insertItem(guest4, KDDockWidgets::Location_OnTop, Size(0, 200));

    host.root.dumpLayout();

    host.show();

    return app.exec();
}
