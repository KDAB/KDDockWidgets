/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Platform_qtwidgets.h"
#include "kddockwidgets/KDDockWidgets.h"

#include "Window_qtwidgets.h"
#include "DebugWindow.h"
#include "views/ViewWrapper_qtwidgets.h"
#include "views/View_qtwidgets.h"
#include "private/Platform_p.h"
#include "ViewFactory_qtwidgets.h"

#include <QScreen>
#include <QApplication>
#include <QLineEdit>
#include <QAbstractButton>
#include <QStyleFactory>

#include <memory.h>

#if defined(KDDOCKWIDGETS_STATICLIB) || defined(QT_STATIC)
static void initResources()
{
    Q_INIT_RESOURCE(kddockwidgets_resources);
}
#endif

using namespace KDDockWidgets;

static_assert(SizePolicy::Fixed == SizePolicy(QSizePolicy::Fixed), "Enums dont match");
static_assert(SizePolicy::Minimum == SizePolicy(QSizePolicy::Minimum), "Enums dont match");
static_assert(SizePolicy::Maximum == SizePolicy(QSizePolicy::Maximum), "Enums dont match");
static_assert(SizePolicy::Preferred == SizePolicy(QSizePolicy::Preferred), "Enums dont match");
static_assert(SizePolicy::Expanding == SizePolicy(QSizePolicy::Expanding), "Enums dont match");


class Platform_qtwidgets::GlobalEventFilter : public QObject
{
public:
    GlobalEventFilter()
    {
        if (qGuiApp)
            qGuiApp->installEventFilter(this);
    }

    bool eventFilter(QObject *o, QEvent *ev) override
    {
        if (!o->isWidgetType()) // QWindow is not receiving it
            return false;

        if (auto w = qobject_cast<QWidget *>(o)) {
            if (w->isWindow()) {
                if (ev->type() == QEvent::WindowActivate) {
                    Platform::instance()->d->windowActivated.emit(
                        Views::ViewWrapper_qtwidgets::create(w));
                }

                if (ev->type() == QEvent::WindowDeactivate) {
                    Platform::instance()->d->windowDeactivated.emit(
                        Views::ViewWrapper_qtwidgets::create(w));
                }
            }
        }

        return false;
    }

    ~GlobalEventFilter() override;
};

Platform_qtwidgets::GlobalEventFilter::~GlobalEventFilter() = default;

Platform_qtwidgets::Platform_qtwidgets()
    : m_globalEventFilter(new GlobalEventFilter())
{
    init();
}

void Platform_qtwidgets::init()
{
#if defined(KDDOCKWIDGETS_STATICLIB) || defined(QT_STATIC)
    initResources();
#endif

#ifdef DOCKS_DEVELOPER_MODE
    if (qEnvironmentVariableIntValue("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW") == 1) {
        auto dv = new Debug::DebugWindow();
        dv->show();
    }
#endif

    qGuiApp->connect(qApp, &QGuiApplication::focusObjectChanged, qApp, [this](QObject *obj) {
        d->focusedViewChanged.emit(Views::ViewWrapper_qtwidgets::create(obj));
    });
}

Platform_qtwidgets::~Platform_qtwidgets()
{
    delete m_globalEventFilter;
}

const char *Platform_qtwidgets::name() const
{
    return "qtwidgets";
}

bool Platform_qtwidgets::hasActivePopup() const
{
    return qApp->activePopupWidget() != nullptr;
}

std::shared_ptr<View> Platform_qtwidgets::qobjectAsView(QObject *obj) const
{
    return Views::ViewWrapper_qtwidgets::create(obj);
}

std::shared_ptr<Window> Platform_qtwidgets::windowFromQWindow(QWindow *qwindow) const
{
    return std::shared_ptr<Window>(new Window_qtwidgets(qwindow));
}

ViewFactory *Platform_qtwidgets::createDefaultViewFactory()
{
    return new ViewFactory_qtwidgets();
}

Window::Ptr Platform_qtwidgets::windowAt(QPoint globalPos) const
{
    if (auto qwindow = qGuiApp->QGuiApplication::topLevelAt(globalPos)) {
        auto window = new Window_qtwidgets(qwindow);
        return Window::Ptr(window);
    }

    return {};
}

int Platform_qtwidgets::screenNumberFor(View *view) const
{
    if (auto widget = Views::View_qt::asQWidget(view)) {
        if (QWindow *qtwindow = widget->window()->windowHandle())
            return screenNumberForQWindow(qtwindow);
    }

    return -1;
}

QSize Platform_qtwidgets::screenSizeFor(View *view) const
{
    if (auto widget = Views::View_qt::asQWidget(view)) {
        if (QScreen *screen = widget->screen()) {
            return screen->size();
        }
    }

    return {};
}

int Platform_qtwidgets::startDragDistance_impl() const
{
    return QApplication::startDragDistance();
}

View *Platform_qtwidgets::createView(Controller *controller, View *parent) const
{
    return new Views::View_qtwidgets<QWidget>(controller, Type::None,
                                              Views::View_qt::asQWidget(parent));
}

bool Platform_qtwidgets::usesFallbackMouseGrabber() const
{
    // For QtWidgets we just use QWidget::grabMouse()
    return false;
}

bool Platform_qtwidgets::inDisallowedDragView(QPoint globalPos) const
{
    QWidget *widget = qApp->widgetAt(globalPos);
    if (!widget)
        return false;

    // User might have a line edit on the toolbar.
    // Not so elegant fix, we should make the user's tabbar implement some virtual method...
    return qobject_cast<QAbstractButton *>(widget) || qobject_cast<QLineEdit *>(widget);
}

void Platform_qtwidgets::ungrabMouse()
{
    if (QWidget *grabber = QWidget::mouseGrabber())
        grabber->releaseMouse();
}

#ifdef DOCKS_DEVELOPER_MODE

inline QCoreApplication *createCoreApplication(int &argc, char **argv)
{
    Platform_qt::maybeSetOffscreenQPA(argc, argv);
    return new QApplication(argc, argv);
}

Platform_qtwidgets::Platform_qtwidgets(int &argc, char **argv)
    : Platform_qt(createCoreApplication(argc, argv))
    , m_globalEventFilter(new Platform_qtwidgets::GlobalEventFilter())
{
    qputenv("KDDOCKWIDGETS_SHOW_DEBUG_WINDOW", "");
    qApp->setStyle(QStyleFactory::create(QStringLiteral("fusion")));
    init();
}

#endif
