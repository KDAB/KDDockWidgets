#include "View_qt.h"
#include "kddockwidgets/Controller.h"

#ifdef KDDW_FRONTEND_QTWIDGETS
#include <QWidget>
#endif

#ifdef KDDW_FRONTEND_QTQUICK
#include <QQuickItem>
#endif

using namespace KDDockWidgets::Views;

View_qt::View_qt(Controller *controller, Type type, QObject *thisObj)
    : View(controller, type, thisObj)
    , m_thisObj(thisObj)
{
}

View_qt::~View_qt() = default;

QObject *View_qt::thisObject() const
{
    return m_thisObj;
}

/*static*/
QObject *View_qt::asObject(View *view)
{
    if (auto viewqt = dynamic_cast<View_qt *>(view))
        return viewqt->thisObject();

    return nullptr;
}

#ifdef KDDW_FRONTEND_QTWIDGETS

/*static */
QWidget *View_qt::asQWidget(View *view)
{
    return qobject_cast<QWidget *>(asObject(view));
}

/*static */
QWidget *View_qt::asQWidget(Controller *controller)
{
    if (!controller)
        return nullptr;

    return asQWidget(controller->view());
}

#endif

#ifdef KDDW_FRONTEND_QTQUICK

/*static */
QQuickItem *View_qt::asQQuickItem(View *view)
{
    return qobject_cast<QQuickItem *>(asObject(view));
}

#endif
