#include "View_qt.h"

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
