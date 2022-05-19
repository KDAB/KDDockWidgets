/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "FloatingWindow_qtquick.h"
#include "Config.h"
#include "qtquick/ViewFactory_qtquick.h"

#include "TitleBar_qtquick.h"

#include "private/Logging_p.h"
#include "private/Utils_p.h"

#include "controllers/DropArea.h"
#include "controllers/FloatingWindow.h"
#include "controllers/MainWindow.h"

#include "private/WidgetResizeHandler_p.h"
#include "qtquick/Platform_qtquick.h"
#include "qtquick/views/MainWindow_qtquick.h"

#include <QQuickView>
#include <QDebug>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

namespace KDDockWidgets {

class QuickView : public QQuickView
{
    Q_OBJECT
public:
    explicit QuickView(QQmlEngine *qmlEngine, FloatingWindow_qtquick *view)
        : QQuickView(qmlEngine, nullptr)
        , m_view(view)
    {
        if (Config::self().internalFlags() & Config::InternalFlag_UseTransparentFloatingWindow)
            setColor(QColor(Qt::transparent));

        updateSize();

        auto item = asQQuickItem(view);
        connect(item, &QQuickItem::widthChanged, this, &QuickView::onRootItemWidthChanged);
        connect(item, &QQuickItem::heightChanged, this, &QuickView::onRootItemHeightChanged);
    }

    ~QuickView();

    bool event(QEvent *ev) override
    {
        if (ev->type() == QEvent::FocusAboutToChange) {
            // qquickwindow.cpp::event(FocusAboutToChange) removes the item grabber. Inibit that
            return true;
        } else if (ev->type() == QEvent::Resize) {
            updateRootItemSize();
        } else if (isNonClientMouseEvent(ev) || ev->type() == QEvent::Move) {
            // Mimic QWidget behaviour: The non-client mouse events go to the QWidget not the QWindow. In our case the QQuickItem.
            // I mean, they also go to QWindow, but for our QtWidgets impl we process them at the QWidget level, so use the same approach
            // so we maintain a single code path for processing mouse events
            qApp->sendEvent(m_view->asQObject(), ev);
            return true;
        }

        return QQuickView::event(ev);
    }

    void onRootItemWidthChanged()
    {
        setWidth(int(m_view->width()));
    }

    void onRootItemHeightChanged()
    {
        setHeight(int(m_view->height()));
    }

    void updateSize()
    {
        resize(m_view->View::size());
    }

    void updateRootItemSize()
    {
        m_view->View::setSize(size());
    }

#ifdef Q_OS_WIN
    bool nativeEvent(const QByteArray &eventType, void *message, Qt5Qt6Compat::qintptr *result) override
    {
        // To enable aero snap we need to tell Windows where's our custom title bar
        if (!m_floatingWindow->beingDeleted() && WidgetResizeHandler::handleWindowsNativeEvent(m_floatingWindow, eventType, message, result))
            return true;

        return QWindow::nativeEvent(eventType, message, result);
    }
#endif
private:
    FloatingWindow_qtquick *const m_view;
};

QuickView::~QuickView() = default;

}


FloatingWindow_qtquick::FloatingWindow_qtquick(Controllers::FloatingWindow *controller,
                                               Views::MainWindow_qtquick *parent, Qt::WindowFlags flags)
    : Views::View_qtquick(controller, Type::FloatingWindow, parent, flags)
    , m_quickWindow(new QuickView(plat()->qmlEngine(), this))
    , m_controller(controller)
{
}

FloatingWindow_qtquick::~FloatingWindow_qtquick()
{
    // Avoid a bunch of QML warnings and constraints being violated at destruction.
    // Also simply avoiding unneeded work, as QML is destroying stuff 1 by 1
    if (auto dropArea = m_controller->dropArea())
        asView_qtquick(dropArea)->setWindowIsBeingDestroyed(true);

    setParent(static_cast<View *>(nullptr));
    if (qobject_cast<QQuickView *>(m_quickWindow)) // QObject cast just to make sure the QWindow is not in ~QObject already
        delete m_quickWindow;
}

QSize FloatingWindow_qtquick::minSize() const
{
    // Doesn't matter if it's not visible. We don't want the min-size to jump around. Also not so
    // easy to track as we don't have layouts
    const int margins = contentsMargins();
    return m_controller->multiSplitter()->view()->minSize() + QSize(0, titleBarHeight()) + QSize(margins * 2, margins * 2);
}

void FloatingWindow_qtquick::setGeometry(QRect geo)
{
    // Not needed with QtWidgets, but needed with QtQuick as we don't have layouts
    geo.setSize(geo.size().expandedTo(minSize()));

    parentItem()->setSize(geo.size());
    m_quickWindow->setGeometry(geo);
}

int FloatingWindow_qtquick::contentsMargins() const
{
    return m_visualItem->property("margins").toInt();
}

int FloatingWindow_qtquick::titleBarHeight() const
{
    return m_visualItem->property("titleBarHeight").toInt();
}

QWindow *FloatingWindow_qtquick::candidateParentWindow() const
{
    if (auto mainWindow = qobject_cast<MainWindow_qtquick *>(QObject::parent())) {
        return mainWindow->QQuickItem::window();
    }

    return nullptr;
}

void FloatingWindow_qtquick::init()
{
    connect(this, &QQuickItem::visibleChanged, this, [this] {
        if (!isVisible() && !m_controller->beingDeleted()) {
            m_controller->scheduleDeleteLater();
        }
    });

    /* for debug:
      connect(m_quickWindow, &QQuickView::focusObjectChanged, this, [this] (QObject *object) {
        qDebug() << "Focus object changed to " << object << this << m_quickWindow;
    });*/


    if (QWindow *transientParent = candidateParentWindow()) {
        m_quickWindow->setTransientParent(candidateParentWindow());
        // This mimics the QWidget behaviour, where we not only have a transient parent but also
        // a parent for cleanup. Calling QWindow::setParent() here would clip it to the parent
        m_quickWindow->QObject::setParent(transientParent);
        m_quickWindow->setObjectName(QStringLiteral("Floating QWindow with parent")); // for debug
    } else {
        m_quickWindow->setObjectName(QStringLiteral("Floating QWindow"));
    }

    setParent(m_quickWindow->contentItem());
    WidgetResizeHandler::setupWindow(m_quickWindow);
    m_quickWindow->installEventFilter(this); // for window resizing
    m_controller->maybeCreateResizeHandler();

    m_visualItem = createItem(m_quickWindow->engine(),
                              plat()->viewFactory()->floatingWindowFilename().toString());
    Q_ASSERT(m_visualItem);

    // Ensure our window size is never smaller than our min-size
    View::setSize(View::size().expandedTo(minSize()));

    m_visualItem->setParent(this);
    m_visualItem->setParentItem(this);

    m_quickWindow->setFlags(flags());

    m_controller->updateTitleAndIcon();

    m_quickWindow->show();
}

#include "FloatingWindow_qtquick.moc"
