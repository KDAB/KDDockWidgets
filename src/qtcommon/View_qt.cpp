#include "View_qt.h"
#include "private/View_p.h"
#include "kddockwidgets/Controller.h"
#include "EventFilterInterface.h"

#ifdef KDDW_FRONTEND_QTWIDGETS
#include <QWidget>
#endif

#ifdef KDDW_FRONTEND_QTQUICK
#include <QQuickItem>
#endif

using namespace KDDockWidgets::Views;

class View_qt::EventFilter : public QObject
{
public:
    explicit EventFilter(View_qt *view, QObject *target)
        : q(view)
    {
        target->installEventFilter(this);
    }

    ~EventFilter() override;

    bool eventFilter(QObject *, QEvent *e) override
    {
        if (e->type() == QEvent::ParentChange)
            q->d->parentChanged.emit();

        if (e->type() == QEvent::MouseButtonPress || e->type() == QEvent::MouseButtonRelease || e->type() == QEvent::MouseMove)
            return handleMouseEvent(static_cast<QMouseEvent *>(e));

        return false;
    }

    bool handleMouseEvent(QMouseEvent *ev)
    {
        for (EventFilterInterface *filter : qAsConst(q->d->m_viewEventFilters)) {

            if (filter->onMouseEvent(q, ev))
                return true;

            switch (ev->type()) {
            case QEvent::MouseButtonPress:
                if (filter->onMouseButtonPress(q, ev))
                    return true;
                break;
            case QEvent::MouseButtonRelease:
                if (filter->onMouseButtonRelease(q, ev))
                    return true;
                break;
            case QEvent::MouseMove:
                if (filter->onMouseButtonMove(q, ev))
                    return true;
                break;
            case QEvent::MouseButtonDblClick:
                if (filter->onMouseDoubleClick(q, ev))
                    return true;
                break;
            default:
                break;
            }
        }

        return false;
    }

    View_qt *const q;
};

View_qt::View_qt(Controller *controller, Type type, QObject *thisObj)
    : View(controller, type, thisObj)
    , m_eventFilter(thisObj ? new EventFilter(this, thisObj) : nullptr)
    , m_thisObj(thisObj)
{
}

View_qt::~View_qt()
{
    delete m_eventFilter;
}

View_qt::EventFilter::~EventFilter() = default;

QObject *View_qt::thisObject() const
{
    return m_thisObj;
}

void View_qt::setObjectName(const QString &name)
{
    if (m_thisObj) {
        m_thisObj->setObjectName(name);
        d->debugNameChanged.emit();
    }
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
