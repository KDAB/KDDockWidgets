#ifndef KDDW_VIEW_GUARD_H
#define KDDW_VIEW_GUARD_H

#include "docks_export.h"

#include "kdbindings/signal.h"

namespace KDDockWidgets {
class View;

/// @brief This class provides a weak reference to a view
/// i.e., it becomes null automatically once a View is destroyed
class DOCKS_EXPORT ViewGuard
{
public:
    ViewGuard(View *v);

    operator bool() const;
    View *operator->();
    void clear();
    bool isNull() const;
    View *view() const;

    ViewGuard& operator=(View *);

private:
    View *v = nullptr;
    KDBindings::ConnectionHandle m_onDestroy;
};

}

#endif
