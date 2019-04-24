#ifndef ANCHORGROUP_H
#define ANCHORGROUP_H

#include "KDDockWidgets.h"
#include "Anchor_p.h"

#include <QWidget>

namespace KDDockWidgets {

class MultiSplitter;
class Anchor;
class Item;

struct AnchorGroup {
    explicit AnchorGroup(MultiSplitter *);

    void addItem(Item *item);
    void addItem(MultiSplitter *);
    void removeItem(Item *item);
    bool isValid() const { return top && left && bottom && right; }

    int width() const;
    int height() const;

    Anchor *oppositeAnchor(Anchor*) const;
    Anchor *createAnchorFrom(KDDockWidgets::Location fromAnchorLocation, Item *relativeTo);
    void setAnchor(Anchor *a, Qt::Orientation orientation, Anchor::Side side);

    Anchor *anchor(KDDockWidgets::Location) const;
    Anchor *anchor(Anchor::Side side, Qt::Orientation orientation) const;
    void setAnchor(Anchor *anchor, KDDockWidgets::Location);

    Anchor *top = nullptr;
    Anchor *left = nullptr;
    Anchor *bottom = nullptr;
    Anchor *right = nullptr;
    MultiSplitter * multiSplitter;
};
}

#endif
