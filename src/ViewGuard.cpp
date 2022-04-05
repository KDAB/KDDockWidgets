#include "ViewGuard.h"
#include "View.h"

using namespace KDDockWidgets;

ViewGuard::ViewGuard(View *view)
    : v(view && view->inDtor() ? nullptr : view)
{
    if (v) {
        m_onDestroy = v->beingDestroyed.connect([this] {
            v = nullptr;
        });
    }
}

ViewGuard::operator bool() const
{
    return !isNull();
}

bool ViewGuard::isNull() const
{
    return v == nullptr;
}

View *ViewGuard::operator->()
{
    return v;
}

void ViewGuard::clear()
{
    v = nullptr;
}

View *ViewGuard::view() const
{
    return v;
}

ViewGuard& ViewGuard::operator=(View *view)
{
    if (view == v) {
        return *this;
    }

    // Remove the pervious connection
    if (m_onDestroy.isActive())
        m_onDestroy.disconnect();

    v = view;

    m_onDestroy = v->beingDestroyed.connect([this] {
        v = nullptr;
    });
    return *this;
}
