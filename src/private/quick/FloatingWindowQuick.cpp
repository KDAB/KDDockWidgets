/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindowQuick_p.h"
#include "MainWindowBase.h"
#include "Logging_p.h"
#include "Utils_p.h"
#include "DropArea_p.h"
#include "TitleBar_p.h"
#include "Config.h"

#include <QQuickView>
#include <QDebug>

using namespace KDDockWidgets;

namespace KDDockWidgets {

class QuickView : public QQuickView
{
    using QQuickView::QQuickView;

    bool event(QEvent *ev) override
    {
        if (ev->type() == QEvent::FocusAboutToChange) {
            // qquickwindow.cpp::event(FocusAboutToChange) removes the item grabber. Inibit that
            return true;
        }

        return QQuickView::event(ev);
    }
};

}


FloatingWindowQuick::FloatingWindowQuick(MainWindowBase *parent)
    : FloatingWindow(parent)
    , m_quickWindow(new QuickView(Config::self().qmlEngine(), nullptr))
{
    init();
}

FloatingWindowQuick::FloatingWindowQuick(Frame *frame, MainWindowBase *parent)
    : FloatingWindow(frame, parent)
    , m_quickWindow(new QuickView(Config::self().qmlEngine(), nullptr))
{
    init();
}

FloatingWindowQuick::~FloatingWindowQuick()
{
    QWidgetAdapter::setParent(nullptr);
    if (qobject_cast<QQuickView*>(m_quickWindow)) // QObject cast just to make sure the QWindow is not in ~QObject already
        delete m_quickWindow;
}

void FloatingWindowQuick::setGeometry(QRect geo)
{
    parentItem()->setSize(geo.size());
    m_quickWindow->setGeometry(geo);
}

QWindow *FloatingWindowQuick::candidateParentWindow() const
{
    if (auto mainWindow = qobject_cast<MainWindowBase*>(QObject::parent())) {
        return mainWindow->QQuickItem::window();
    }

    return nullptr;
}

void FloatingWindowQuick::init()
{
    connect(this, &QQuickItem::visibleChanged, this, [this] {
        if (!isVisible() && !beingDeleted()) {
            scheduleDeleteLater();
        }
    });

    /* for debug:
      connect(m_quickWindow, &QQuickView::focusObjectChanged, this, [this] (QObject *object) {
        qDebug() << "Focus object changed to " << object << this << m_quickWindow;
    });*/

    const QSize minSize(200, 200);
    m_quickWindow->resize(minSize);
    m_quickWindow->contentItem()->setSize(minSize);


    if (QWindow *transientParent = candidateParentWindow()) {
        m_quickWindow->setTransientParent(candidateParentWindow());
        // This mimics the QWidget beaviour, where we not only have a transient parent but also
        // a parent for cleanup. Calling QWindow::setParent() here would clip it to the parent
        m_quickWindow->QObject::setParent(transientParent);
    }

    QWidgetAdapter::setParent(m_quickWindow->contentItem());
    QWidgetAdapter::makeItemFillParent(this);

    m_quickWindow->setResizeMode(QQuickView::SizeViewToRootObject);

    QQuickItem *visualItem = createItem(Config::self().qmlEngine(), QStringLiteral("qrc:/kddockwidgets/private/quick/qml/FloatingWindow.qml"));
    Q_ASSERT(visualItem);
    visualItem->setParent(this);
    visualItem->setParentItem(this);

    m_quickWindow->setFlags(windowFlags());
    m_quickWindow->show();
}
