/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "core/layouting/Item_p.h"
#include "core/layouting/LayoutingHost_p.h"
#include "core/layouting/LayoutingGuest_p.h"
#include "core/layouting/LayoutingSeparator_p.h"
#include "core/DropArea.h"
#include "core/View_p.h"
#include "core/Utils_p.h"
#include "core/ObjectGuard_p.h"
#include "core/ScopedValueRollback_p.h"

#include <QTest>

#include <memory.h>
#include <cstdlib>
#include <utility>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

static int st = Item::layoutSpacing;

class TestLayouting : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void tst_createRoot();
    void tst_insertOne();
    void tst_insertThreeSideBySide();
    void tst_insertTwoHorizontal();
    void tst_insertTwoVertical();
    void tst_insertOnWidgetItem1();
    void tst_insertOnWidgetItem2();
    void tst_insertOnWidgetItem1DifferentOrientation();
    void tst_insertOnWidgetItem2DifferentOrientation();
    void tst_insertOnRootDifferentOrientation();
    void tst_removeItem1();
    void tst_removeItem2();
    void tst_minSize();
    void tst_resize();
    void tst_resizeWithConstraints();
    void tst_availableSize();
    void tst_missingSize();
    void tst_ensureEnoughSize();
    void tst_turnIntoPlaceholder();
    void tst_suggestedRect();
    void tst_suggestedRect2();
    void tst_suggestedRect3();
    void tst_suggestedRect4();
    void tst_insertAnotherRoot();
    void tst_misc1();
    void tst_misc2();
    void tst_misc3();
    void tst_containerGetsHidden();
    void tst_minSizeChanges();
    void tst_numSeparators();
    void tst_separatorMinMax();
    void tst_separatorRecreatedOnParentChange();
    void tst_containerReducesSize();
    void tst_insertHiddenContainer();
    void tst_availableOnSide();
    void tst_availableToGrowOnSide();
    void tst_resizeViaSeparator();
    void tst_resizeViaSeparator2();
    void tst_resizeViaSeparator3();
    void tst_mapToRoot();
    void tst_closeAndRestorePreservesPosition();
    void tst_minSizeChangedBeforeRestore();
    void tst_separatorMoveCrash();
    void tst_separatorMoveHonoursMax();
    void tst_maxSizeHonoured1();
    void tst_maxSizeHonoured2();
    void tst_maxSizeHonoured3();
    void tst_requestEqualSize();
    void tst_maxSizeHonouredWhenAnotherRemoved();
    void tst_simplify();
    void tst_adjacentLayoutBorders();
    void tst_numSideBySide_recursive();
    void tst_sizingInfoSerialization();
    void tst_itemSerialization();
    void tst_relayoutIfNeeded();
    void tst_outermostVisibleNeighbor();
    void tst_outermostNeighbor();
    void tst_relativeToHidden();
    void tst_spuriousResize();
};

namespace {

class Guest : public Core::LayoutingGuest
{
public:
    using Core::LayoutingGuest::LayoutingGuest;

    Guest(Core::View *view, LayoutingHost *host)
        : m_host(host)
        , m_view(view)
    {
        view->d->layoutInvalidated.connect([this] { layoutInvalidated.emit(); });
    }

    ~Guest() override
    {
        beingDestroyed.emit();
    }

    void setHost(LayoutingHost *host) override
    {
        m_host = host;
        if (m_view && host)
            m_view->setParent(dynamic_cast<DropArea *>(Layout::fromLayoutingHost(host))->view());
    }

    LayoutingHost *host() const override
    {
        return m_host;
    }

    Size minSize() const override
    {
        return m_view->minSize();
    }

    Size maxSizeHint() const override
    {
        return m_view->maxSizeHint();
    }

    void setGeometry(QRect r) override
    {
        if (r != geometry()) {
            m_numSetGeometry++;
            m_view->setGeometry(r);
        }
    }

    void setVisible(bool is) override
    {
        m_view->setVisible(is);
    }

    QRect geometry() const override
    {
        return m_view->geometry();
    }

    QString id() const override
    {
        return m_view->d->id();
    }

    LayoutingHost *m_host = nullptr;
    View *const m_view;
    int m_numSetGeometry = 0;
};

}

static std::vector<Core::Layout *> s_views;
struct DeleteViews
{
    ~DeleteViews()
    {
        qDeleteAll(s_views);
        s_views.clear();
    }
};

static bool
serializeDeserializeTest(const std::unique_ptr<ItemBoxContainer> &root)
{
    // Serializes and deserializes a layout
    if (!root->checkSanity())
        return false;

    nlohmann::json serialized;
    root->to_json(serialized);
    ItemBoxContainer root2(root->host());

    std::unordered_map<QString, LayoutingGuest *> widgets;
    const Item::List originalItems = root->items_recursive();
    for (Item *item : originalItems)
        if (auto guest = item->guest())
            widgets[guest->id()] = guest;

    root2.fillFromJson(serialized, widgets);

    return root2.checkSanity();
}

static std::unique_ptr<ItemBoxContainer> createRoot()
{
    auto dropArea = new DropArea(nullptr, MainWindowOption_None);
    s_views.push_back(dropArea);
    auto root = new ItemBoxContainer(dropArea->asLayoutingHost());
    root->setSize({ 1000, 1000 });

    return std::unique_ptr<ItemBoxContainer>(root);
}

static Item *createItem(Size minSz = {}, Size maxSz = {})
{
    static int count = 0;
    count++;
    auto item = new Item(nullptr);
    item->setGeometry(QRect(0, 0, 200, 200));
    item->setObjectName(QString::number(count));
    Core::CreateViewOptions opts;
    if (minSz.isValid())
        opts.minSize = minSz;
    if (maxSz.isValid())
        opts.maxSize = maxSz;
    auto guestView = Core::Platform::instance()->tests_createView(opts);

    guestView->setViewName(item->objectName());
    auto guest = new Guest(guestView, s_views[s_views.size() - 1]->asLayoutingHost());
    guestView->d->beingDestroyed.connect([guest] {
        delete guest;
    });
    item->setGuest(guest);
    return item;
}

static ItemBoxContainer *createRootWithSingleItem()
{
    auto dropArea = new DropArea(nullptr, MainWindowOption_None);
    s_views.push_back(dropArea);
    auto root = new ItemBoxContainer(dropArea->asLayoutingHost());
    root->setSize({ 1000, 1000 });

    Item *item1 = createItem();
    root->insertItem(item1, Location_OnTop);

    return root;
}

void TestLayouting::tst_createRoot()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    QVERIFY(root->isRoot());
    QVERIFY(root->isContainer());
    QVERIFY(root->hasOrientation());
    QCOMPARE(root->size(), QSize(1000, 1000));
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertOne()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item = createItem();
    root->insertItem(item, Location_OnTop);
    QVERIFY(root->checkSanity());
    QCOMPARE(root->numChildren(), 1);
    QVERIFY(!item->isContainer());
    QCOMPARE(root->size(), QSize(1000, 1000));
    QCOMPARE(item->size(), root->size());
    QCOMPARE(item->pos(), QPoint());
    QCOMPARE(item->pos(), root->pos());
    QVERIFY(root->hasChildren());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertThreeSideBySide()
{
    DeleteViews deleteViews;

    // Result is [1, 2, 3]
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);

    QVERIFY(root->checkSanity());
    QCOMPARE(root->numChildren(), 3);
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertTwoHorizontal()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnLeft);
    ItemBoxContainer::insertItemRelativeTo(item2, item1, Location_OnRight);
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertTwoVertical()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnTop);
    ItemBoxContainer::insertItemRelativeTo(item2, item1, Location_OnBottom);
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertOnWidgetItem1()
{
    DeleteViews deleteViews;

    // We insert into a widget item instead of in a container. It will insert in the container still
    // Result is still [1, 2, 3]

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);

    QVERIFY(item3->x() > item2->x());
    QCOMPARE(item3->y(), item2->y());

    QVERIFY(root->checkSanity());
    QCOMPARE(root->numChildren(), 3);
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertOnWidgetItem2()
{
    DeleteViews deleteViews;

    // Same, but result [1, 3, 2]

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnLeft);

    QVERIFY(item1->x() < item3->x());
    QVERIFY(item3->x() < item2->x());
    QCOMPARE(item3->y(), item2->y());

    QVERIFY(root->checkSanity());
    QCOMPARE(root->numChildren(), 3);
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertOnWidgetItem1DifferentOrientation()
{
    DeleteViews deleteViews;

    // Result [1, 2, |3  |]
    //               |3.1|

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item31 = createItem();
    root->insertItem(item1, Location_OnLeft);
    QVERIFY(root->checkSanity());

    root->insertItem(item2, Location_OnRight);
    QVERIFY(root->checkSanity());

    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    QVERIFY(root->checkSanity());

    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);
    QVERIFY(root->checkSanity());

    auto container3 = item3->parentBoxContainer();
    QVERIFY(container3->isContainer());
    QVERIFY(container3 != root.get());
    QVERIFY(root->isHorizontal());
    QVERIFY(container3->isVertical());

    QCOMPARE(root->numChildren(), 3);
    QCOMPARE(container3->numChildren(), 2);

    QVERIFY(item1->x() < item2->x());
    QVERIFY(item3->parentBoxContainer()->x() > item2->x());
    QCOMPARE(item3->x(), 0);
    QCOMPARE(item3->y(), item2->y());
    QCOMPARE(item1->y(), item2->y());

    QVERIFY(item31->y() >= item3->y());
    QCOMPARE(item31->parentBoxContainer(), container3);
    QCOMPARE(item3->parentBoxContainer(), container3);
    QCOMPARE(container3->parentBoxContainer(), root.get());
    QCOMPARE(Point(0, 0), item3->pos());
    QCOMPARE(container3->width(), item3->width());
    QCOMPARE(container3->height(), item3->height() + st + item31->height());

    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertOnWidgetItem2DifferentOrientation()
{
    DeleteViews deleteViews;

    // Result [1, 2, |3 3.2|]
    //               |3.1  |

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item5 = createItem();
    auto item4 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnBottom);
    auto container3Parent = item3->parentBoxContainer();
    ItemBoxContainer::insertItemRelativeTo(item5, item3, Location_OnRight);
    QVERIFY(root->checkSanity());
    auto container3 = item3->parentBoxContainer();

    QCOMPARE(container3->parentBoxContainer(), container3Parent);

    QVERIFY(container3->isContainer());
    QVERIFY(container3 != root.get());
    QVERIFY(root->isHorizontal());
    QVERIFY(container3->isHorizontal());
    QVERIFY(container3Parent->isVertical());

    QCOMPARE(root->numChildren(), 3);
    QCOMPARE(container3->numChildren(), 2);
    QCOMPARE(container3Parent->numChildren(), 2);

    QVERIFY(item1->x() < item2->x());
    QCOMPARE(container3->pos(), QPoint(0, 0l));
    QCOMPARE(item3->pos(), container3->pos());
    QVERIFY(container3Parent->x() > item2->x());
    QCOMPARE(item3->y(), item2->y());
    QCOMPARE(item1->y(), item2->y());

    QVERIFY(item4->y() >= item3->y());
    QCOMPARE(item4->parentBoxContainer(), container3Parent);
    QCOMPARE(item3->parentBoxContainer(), container3);
    QCOMPARE(container3Parent->parentBoxContainer(), root.get());
    QCOMPARE(container3->pos(), item3->pos());
    QCOMPARE(container3->width(), item3->width() + item5->width() + st);
    QCOMPARE(container3->height(), item3->height());
    QCOMPARE(container3Parent->height(), item3->height() + st + item4->height());

    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_insertOnRootDifferentOrientation()
{
    DeleteViews deleteViews;

    //        [       4     ]
    // Result [1, 2, |3 3.2|]
    //               |3.1  |

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item31 = createItem();
    auto item32 = createItem();
    auto item4 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item32, item3, Location_OnRight);
    root->insertItem(item4, Location_OnTop);

    QCOMPARE(item4->parentBoxContainer(), root.get());
    QCOMPARE(item4->pos(), root->pos());
    QCOMPARE(item4->width(), root->width());

    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_removeItem1()
{
    //        [       4     ]
    // Result [1, 2, |3 3.2|]
    //               |3.1  |

    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item31 = createItem();
    auto item32 = createItem();
    auto item4 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item32, item3, Location_OnRight);
    root->insertItem(item4, Location_OnTop);
    QVERIFY(root->checkSanity());
    QCOMPARE(root->numChildren(), 2);

    root->removeItem(item4);
    QVERIFY(root->checkSanity());
    QCOMPARE(root->numChildren(), 1);

    auto c1 = item1->parentBoxContainer();
    QCOMPARE(c1->pos(), QPoint(0, 0));
    QCOMPARE(c1->width(), root->width());
    QCOMPARE(c1->height(), item1->height());
    QCOMPARE(c1->height(), root->height());

    const int item3and32Width = item3->width() + item32->width() + st;
    root->removeItem(item32);

    QCOMPARE(item3->width(), item3and32Width);
    QVERIFY(root->checkSanity());

    root->removeItem(item31);
    QVERIFY(root->checkSanity());

    QCOMPARE(item2->height(), item3->height());

    ObjectGuard<Item> c3 = item3->parentBoxContainer();
    root->removeItem(c3);
    QVERIFY(c3.isNull());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_removeItem2()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item31 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);
    item31->parentBoxContainer()->removeItem(item31);
    item3->parentBoxContainer()->removeItem(item3);
}

void TestLayouting::tst_minSize()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item22 = createItem();

    item1->m_sizingInfo.minSize = { 101, 150 };
    item2->m_sizingInfo.minSize = { 200, 300 };
    item2->setSize(item2->m_sizingInfo.minSize);
    item22->m_sizingInfo.minSize = { 100, 100 };

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item22, item2, Location_OnBottom);

    QCOMPARE(item2->minSize(), QSize(200, 300));
    QCOMPARE(item2->parentBoxContainer()->minSize(), QSize(200, 300 + 100 + st));

    QCOMPARE(root->minSize(), QSize(101 + 200 + st, 300 + 100 + st));
    QVERIFY(root->checkSanity());

    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_resize()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item31 = createItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);

    const int item1Percentage = item1->width() / root->width();
    const int item2Percentage = item1->width() / root->width();
    const int item3Percentage = item1->width() / root->width();

    // Now resize:
    root->setSize_recursive({ 2000, 505 });
    QVERIFY(root->checkSanity());

    QVERIFY(item1Percentage - (1.0 * item1->width() / root->width()) < 0.01);
    QVERIFY(item2Percentage - (1.0 * item2->width() / root->width()) < 0.01);
    QVERIFY(item3Percentage - (1.0 * item3->width() / root->width()) < 0.01);
    QCOMPARE(root->width(), 2000);
    QCOMPARE(root->height(), 505);
    QCOMPARE(item1->height(), 505);
    QCOMPARE(item2->height(), 505);
    QCOMPARE(item3->height(), 505);

    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);

    QVERIFY(root->checkSanity());
    root->setSize_recursive({ 2500, 505 });
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_resizeWithConstraints()
{
    DeleteViews deleteViews;

    Platform::instance()->m_expectedWarning = "New size doesn't respect size constraints";

    {
        // Test that resizing below minSize isn't permitted.

        auto root = createRoot();
        auto item1 = createItem();
        item1->setMinSize(Size(500, 500));
        root->insertItem(item1, Location_OnLeft);
        QVERIFY(root->checkSanity());

        root->setSize_recursive(item1->minSize()); // Still fits
        root->setSize_recursive(item1->minSize() - Size(1, 0)); // wouldn't fit
        QCOMPARE(root->size(), item1->size()); // still has the old size
        QVERIFY(serializeDeserializeTest(root));
    }

    {
        // |1|2|3|

        auto root = createRoot();
        auto item1 = createItem();
        auto item2 = createItem();
        auto item3 = createItem();
        root->setSize_recursive(Size(2000, 500));
        item1->setMinSize(Size(500, 500));
        item2->setMinSize(Size(500, 500));
        item3->setMinSize(Size(500, 500));
        root->insertItem(item1, Location_OnLeft);
        root->insertItem(item2, Location_OnRight);
        root->insertItem(item3, Location_OnRight);
        QVERIFY(root->checkSanity());
    }
    Platform::instance()->m_expectedWarning.clear();
}

void TestLayouting::tst_availableSize()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    QCOMPARE(root->availableSize(), QSize(1000, 1000));
    QCOMPARE(root->minSize(), QSize(0, 0));

    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    item1->m_sizingInfo.minSize = { 100, 100 };
    item2->m_sizingInfo.minSize = { 100, 100 };
    item3->m_sizingInfo.minSize = { 100, 100 };

    root->insertItem(item1, Location_OnLeft);
    QCOMPARE(root->availableSize(), QSize(900, 900));
    QCOMPARE(root->minSize(), QSize(100, 100));
    QCOMPARE(root->neighboursLengthFor(item1, Side1, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursLengthFor(item1, Side2, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursMinLengthFor(item1, Side1, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursMinLengthFor(item1, Side2, Qt::Horizontal), 0);

    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side1, Qt::Vertical), 0);
    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side2, Qt::Vertical), 0);
    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side1, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side2, Qt::Horizontal), 0);

    root->insertItem(item2, Location_OnLeft);
    QCOMPARE(root->availableSize(), QSize(800 - st, 900));
    QCOMPARE(root->minSize(), QSize(200 + st, 100));
    QCOMPARE(root->neighboursLengthFor(item1, Side1, Qt::Horizontal), item2->width());
    QCOMPARE(root->neighboursLengthFor(item1, Side2, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursLengthFor(item2, Side1, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursLengthFor(item2, Side2, Qt::Horizontal), item1->width());
    QCOMPARE(root->neighboursMinLengthFor(item1, Side1, Qt::Horizontal), item2->minSize().width());
    QCOMPARE(root->neighboursMinLengthFor(item1, Side2, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursMinLengthFor(item2, Side1, Qt::Horizontal), 0);
    QCOMPARE(root->neighboursMinLengthFor(item2, Side2, Qt::Horizontal), item1->minSize().width());

    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side1, Qt::Vertical), 0);
    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side2, Qt::Vertical), 0);
    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side1, Qt::Horizontal), item2->width());
    QCOMPARE(root->neighboursLengthFor_recursive(item1, Side2, Qt::Horizontal), 0);

    root->insertItem(item3, Location_OnBottom);
    QCOMPARE(root->availableSize(), QSize(800 - st, 800 - st));
    QCOMPARE(root->minSize(), QSize(200 + st, 100 + 100 + st));
    QCOMPARE(item3->parentBoxContainer()->neighboursMinLengthFor(item3, Side1, Qt::Vertical),
             item1->minSize().height());

    auto container2 = item2->parentBoxContainer();
    QCOMPARE(container2->neighboursLengthFor_recursive(item1, Side1, Qt::Vertical), 0);
    QCOMPARE(container2->neighboursLengthFor_recursive(item1, Side2, Qt::Vertical),
             item3->height());
    QCOMPARE(container2->neighboursLengthFor_recursive(item1, Side1, Qt::Horizontal),
             item2->width());
    QCOMPARE(container2->neighboursLengthFor_recursive(item1, Side2, Qt::Horizontal), 0);

    // More nesting
    auto item4 = createItem();
    auto item5 = createItem();
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item5, item4, Location_OnBottom);

    auto container4 = item4->parentBoxContainer();
    QCOMPARE(container4->neighboursLengthFor_recursive(item4, Side1, Qt::Vertical),
             item1->height());
    QCOMPARE(container4->neighboursLengthFor_recursive(item4, Side2, Qt::Vertical),
             item5->height());
    QCOMPARE(container4->neighboursLengthFor_recursive(item4, Side1, Qt::Horizontal),
             item3->width());
    QCOMPARE(container4->neighboursLengthFor_recursive(item4, Side2, Qt::Horizontal), 0);
    QCOMPARE(container4->neighboursLengthFor_recursive(item5, Side1, Qt::Vertical),
             item4->height() + item1->height());
    QCOMPARE(container4->neighboursLengthFor_recursive(item5, Side2, Qt::Vertical), 0);
    QCOMPARE(container4->neighboursLengthFor_recursive(item5, Side1, Qt::Horizontal),
             item3->width());
    QCOMPARE(container4->neighboursLengthFor_recursive(item5, Side2, Qt::Horizontal), 0);

    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_missingSize()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    QCOMPARE(root->size(), QSize(1000, 1000));
    QCOMPARE(root->availableSize(), QSize(1000, 1000));

    Item *item1 = createItem();
    item1->setMinSize({ 100, 100 });

    Item *item2 = createItem();
    item2->setMinSize(root->size());

    Item *item3 = createItem();
    item3->setMinSize(root->size() + Size(100, 200));

    // Test with an existing item
    root->insertItem(item1, Location_OnTop);
    QVERIFY(serializeDeserializeTest(root));

    // Add just so the views are deleted at the end
    root->insertItem(item2, Location_OnTop);
    root->insertItem(item3, Location_OnTop);

    delete item2;
    delete item3;
}

void TestLayouting::tst_ensureEnoughSize()
{
    DeleteViews deleteViews;

    // Tests that the layout's size grows when the item being inserted wouldn't have enough space

    auto root = createRoot(); /// 1000x1000
    Item *item1 = createItem();
    item1->setMinSize({ 2000, 500 });

    // Insert to empty layout:

    root->insertItem(item1, Location_OnLeft);
    QCOMPARE(root->size(), QSize(2000, 1000));
    QCOMPARE(item1->size(), QSize(2000, 1000));
    QCOMPARE(item1->minSize(), root->minSize());
    QVERIFY(root->checkSanity());

    // Insert to non-empty layout
    Item *item2 = createItem();
    item2->setMinSize({ 2000, 2000 });
    root->insertItem(item2, Location_OnRight);
    QVERIFY(root->checkSanity());
    QCOMPARE(
        root->size(),
        Size(item1->minSize().width() + item2->minSize().width() + st, item2->minSize().height()));
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_turnIntoPlaceholder()
{
    DeleteViews deleteViews;

    auto root = createRoot();

    int numVisibleItems = 0;
    root->numVisibleItemsChanged.connect(
        [&numVisibleItems](int count) { numVisibleItems = count; });

    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    QCOMPARE(numVisibleItems, 1);
    QVERIFY(item1->isVisible());
    item1->turnIntoPlaceholder();
    QCOMPARE(numVisibleItems, 0);
    QVERIFY(!item1->isVisible());
    QCOMPARE(root->visibleCount_recursive(), 0);
    QCOMPARE(root->count_recursive(), 1);
    QVERIFY(root->checkSanity());

    root->insertItem(item2, Location_OnLeft);
    QVERIFY(root->checkSanity());
    QCOMPARE(numVisibleItems, 1);

    root->insertItem(item3, Location_OnLeft);
    QCOMPARE(numVisibleItems, 2);
    QVERIFY(root->checkSanity());
    QCOMPARE(item2->width() + item3->width() + st, root->width());
    item2->turnIntoPlaceholder();
    QCOMPARE(numVisibleItems, 1);
    QVERIFY(root->checkSanity());
    QCOMPARE(item3->width(), root->width());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_suggestedRect()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    root->setSize(Size(2000, 1000));
    const Size minSize(100, 100);
    Item itemBeingDropped(nullptr);
    itemBeingDropped.setMinSize(minSize);

    QRect leftRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnLeft);
    QRect topRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnTop);
    QRect bottomRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnBottom);
    QRect rightRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnRight);

    // Test relative to root:
    QVERIFY(leftRect.width() >= minSize.width());
    QVERIFY(topRect.height() >= minSize.height());
    QVERIFY(bottomRect.height() >= minSize.height());
    QVERIFY(rightRect.width() >= minSize.width());
    QCOMPARE(leftRect.topLeft(), QPoint(0, 0));
    QCOMPARE(leftRect.bottomLeft(), root->rect().bottomLeft());
    QCOMPARE(rightRect.topRight(), root->rect().topRight());
    QCOMPARE(rightRect.bottomRight(), root->rect().bottomRight());
    QCOMPARE(topRect.topLeft(), root->rect().topLeft());
    QCOMPARE(topRect.topRight(), root->rect().topRight());
    QCOMPARE(bottomRect.bottomLeft(), root->rect().bottomLeft());
    QCOMPARE(bottomRect.bottomRight(), root->rect().bottomRight());

    // Test relative to an item
    Item *item1 = createItem();
    item1->setMinSize(Size(100, 100));
    root->insertItem(item1, Location_OnLeft);
    leftRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnLeft);
    topRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnTop);
    bottomRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnBottom);
    rightRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnRight);
    QVERIFY(leftRect.width() >= minSize.width());
    QVERIFY(topRect.height() >= minSize.height());
    QVERIFY(bottomRect.height() >= minSize.height());
    QVERIFY(rightRect.width() >= minSize.width());
    QCOMPARE(leftRect.topLeft(), QPoint(0, 0));
    QCOMPARE(leftRect.bottomLeft(), root->rect().bottomLeft());
    QCOMPARE(rightRect.topRight(), root->rect().topRight());
    QCOMPARE(rightRect.bottomRight(), root->rect().bottomRight());
    QCOMPARE(topRect.topLeft(), root->rect().topLeft());
    QCOMPARE(topRect.topRight(), root->rect().topRight());
    QCOMPARE(bottomRect.bottomLeft(), root->rect().bottomLeft());
    QCOMPARE(bottomRect.bottomRight(), root->rect().bottomRight());

    // Insert another item:
    Item *item2 = createItem();
    item1->setMinSize(Size(100, 100));
    root->insertItem(item2, Location_OnRight);
    leftRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnLeft);
    topRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnTop);
    bottomRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnBottom);
    rightRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnRight);
    QCOMPARE(leftRect.y(), item2->geometry().y());
    QVERIFY(leftRect.x() < item2->geometry().x());
    QVERIFY(leftRect.x() > item1->geometry().x());
    QCOMPARE(rightRect.topRight(), root->rect().topRight());
    QCOMPARE(rightRect.bottomRight(), root->rect().bottomRight());
    QCOMPARE(topRect.topLeft(), item2->geometry().topLeft());
    QCOMPARE(topRect.topRight(), item2->geometry().topRight());
    QCOMPARE(bottomRect.bottomLeft(), item2->geometry().bottomLeft());
    QCOMPARE(bottomRect.bottomRight(), item2->geometry().bottomRight());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_suggestedRect2()
{
    DeleteViews deleteViews;

    // Tests a bug where the inner drop locations didn't work when there was a nested container
    // Like container >> container >> Item

    auto root1 = createRoot();
    auto root2 = createRoot();

    Item itemBeingDropped(nullptr);
    itemBeingDropped.setMinSize(Size(100, 100));

    Item *item = createItem();

    root2->insertItem(item, Location_OnRight);
    root1->insertItem(root2.release(), Location_OnRight);

    QVERIFY(item->parentBoxContainer()
                ->suggestedDropRect(&itemBeingDropped, item, Location_OnRight)
                .isValid());
}

void TestLayouting::tst_suggestedRect3()
{
    DeleteViews deleteViews;

    auto root1 = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    Item *itemToDrop = createItem();

    root1->insertItem(item1, Location_OnLeft);
    root1->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnBottom);

    QVERIFY(!item3->parentBoxContainer()
                 ->suggestedDropRect(itemToDrop, item3, Location_OnLeft)
                 .isEmpty());

    /// insert just to cleanup at shutdown
    root1->insertItem(itemToDrop, Location_OnRight);
}

void TestLayouting::tst_suggestedRect4()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto root1 = createRoot();

    Item *item1 = createItem();
    root1->insertItem(item1, Location_OnLeft);
    root->insertItem(root1.release(), Location_OnLeft);

    auto root2 = createRoot();
    Item *item2 = createItem();
    root2->insertItem(item2, Location_OnLeft);

    auto root3 = createRoot();
    Item *item3 = createItem();
    root3->insertItem(item3, Location_OnLeft);

    ItemBoxContainer::insertItemRelativeTo(root2.release(), item1, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(root3.release(), item2, Location_OnBottom);

    Item *itemToDrop = createItem();

    QVERIFY(root->checkSanity());
    QVERIFY(!item3->parentBoxContainer()
                 ->suggestedDropRect(itemToDrop, item3, Location_OnLeft)
                 .isEmpty());

    /// insert just to cleanup at shutdown
    root->insertItem(itemToDrop, Location_OnRight);
}

void TestLayouting::tst_insertAnotherRoot()
{
    DeleteViews deleteViews;

    {
        auto root1 = createRoot();
        Item *item1 = createItem();
        root1->insertItem(item1, Location_OnRight);
        auto host1 = root1->host();

        auto root2 = createRoot();
        Item *item2 = createItem();
        root2->insertItem(item2, Location_OnRight);

        root1->insertItem(root2.release(), Location_OnBottom);

        QCOMPARE(root1->host(), host1);
        QCOMPARE(item2->host(), host1);
        const auto &items = root1->items_recursive();
        for (Item *item : items) {
            QCOMPARE(item->host(), host1);
            QVERIFY(item->isVisible());
        }
        QVERIFY(root1->checkSanity());
        QVERIFY(serializeDeserializeTest(root1));
    }

    {
        auto root1 = createRoot();
        Item *item1 = createItem();
        Item *item2 = createItem();
        root1->insertItem(item1, Location_OnLeft);
        root1->insertItem(item2, Location_OnRight);
        auto host1 = root1->host();

        auto root2 = createRoot();
        Item *item12 = createItem();
        root2->insertItem(item12, Location_OnRight);

        root1->insertItem(root2.release(), Location_OnTop);

        QCOMPARE(root1->host(), host1);
        QCOMPARE(item2->host(), host1);
        for (Item *item : root1->items_recursive()) {
            QCOMPARE(item->host(), host1);
            QVERIFY(item->isVisible());
        }
        QVERIFY(root1->checkSanity());
        QVERIFY(serializeDeserializeTest(root1));
    }
}

void TestLayouting::tst_misc1()
{
    DeleteViews deleteViews;

    // Random test1

    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    Item *item4 = createItem();
    Item *item5 = createItem();

    root->insertItem(item1, Location_OnTop);
    ItemBoxContainer::insertItemRelativeTo(item2, item1, Location_OnRight);
    root->insertItem(item3, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnRight);
    root->insertItem(item5, Location_OnLeft);

    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_misc2()
{
    DeleteViews deleteViews;

    // Random test1
    // |5|1|2|
    // | |3|4|

    auto root = createRoot();
    ItemBoxContainer *root1 = createRootWithSingleItem();
    Item *item1 = root1->childItems().constFirst();
    ItemBoxContainer *root2 = createRootWithSingleItem();
    Item *item3 = createItem();
    ItemBoxContainer *root4 = createRootWithSingleItem();
    ItemBoxContainer *root5 = createRootWithSingleItem();
    Item *item5 = root5->childItems().constFirst();

    root->insertItem(root1, Location_OnTop);
    QVERIFY(root->checkSanity());
    ItemBoxContainer::insertItemRelativeTo(root2, item1, Location_OnRight);
    QVERIFY(root->checkSanity());
    root->insertItem(item3, Location_OnBottom);
    QVERIFY(root->checkSanity());
    ItemBoxContainer::insertItemRelativeTo(root4, item3, Location_OnRight);
    QVERIFY(root->checkSanity());

    root->insertItem(root5, Location_OnLeft);
    QVERIFY(root->checkSanity());

    item5->parentBoxContainer()->removeItem(item5);
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_misc3()
{
    DeleteViews deleteViews;

    // Random test1
    // |1|2|3|
    // | |3|4|

    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *root2 = createRootWithSingleItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(root2, Location_OnRight);
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_containerGetsHidden()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    QVERIFY(root->checkSanity());

    root->insertItem(item2, Location_OnRight);
    QVERIFY(root->checkSanity());

    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnBottom);
    QVERIFY(root->checkSanity());

    item2->turnIntoPlaceholder();
    QVERIFY(root->checkSanity());

    item3->turnIntoPlaceholder();
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_minSizeChanges()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    Item *item1 = createItem();
    root->insertItem(item1, Location_OnLeft);

    root->setSize_recursive(Size(200, 200));
    QVERIFY(root->checkSanity());

    auto w1 = item1;
    w1->setMinSize(Size(300, 300));
    QVERIFY(root->checkSanity());
    QCOMPARE(root->size(), QSize(300, 300));

    Item *item2 = createItem();
    root->insertItem(item2, Location_OnTop);
    QVERIFY(root->checkSanity());

    root->setSize_recursive(Size(1000, 1000));
    QVERIFY(root->checkSanity());

    w1->setMinSize(Size(700, 700));
    QVERIFY(root->checkSanity());
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_numSeparators()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    Item *item4 = createItem();

    QCOMPARE(root->separators_recursive().size(), 0);

    root->insertItem(item1, Location_OnLeft);
    QCOMPARE(root->separators_recursive().size(), 0);

    root->insertItem(item2, Location_OnLeft);
    QCOMPARE(root->separators_recursive().size(), 1);

    root->insertItem(item3, Location_OnTop);
    QCOMPARE(root->separators_recursive().size(), 2);
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnRight);
    QCOMPARE(root->separators_recursive().size(), 3);

    root->removeItem(item3);
    QCOMPARE(root->separators_recursive().size(), 2);

    root->clear();
    QCOMPARE(root->separators_recursive().size(), 0);

    Item *item5 = createItem();
    Item *item6 = createItem();

    root->insertItem(item5, Location_OnLeft);
    QCOMPARE(root->separators_recursive().size(), 0);
    root->insertItem(item6, Location_OnLeft, KDDockWidgets::InitialVisibilityOption::StartHidden);
    QCOMPARE(root->separators_recursive().size(), 0);
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_separatorMinMax()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnLeft);
    item1->setMinSize(Size(200, 200));
    item2->setMinSize(Size(200, 200));

    auto separator = root->separators_recursive().at(0);
    QCOMPARE(root->minPosForSeparator(separator), 200);
    QCOMPARE(root->minPosForSeparator_global(separator), 200); // same, since there's no nesting

    QCOMPARE(root->maxPosForSeparator(separator), root->width() - st - 200);
    QCOMPARE(root->maxPosForSeparator(separator), root->width() - st - 200);
    QVERIFY(serializeDeserializeTest(root));
}

void TestLayouting::tst_separatorRecreatedOnParentChange()
{
    DeleteViews deleteViews;

    auto root1 = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    root1->insertItem(item1, Location_OnLeft);
    root1->insertItem(item2, Location_OnLeft);

    auto root2 = createRoot();
    Item *item21 = createItem();
    Item *item22 = createItem();
    root2->insertItem(item21, Location_OnLeft);
    root2->insertItem(item22, Location_OnLeft);

    root1->insertItem(root2.get(), Location_OnTop);
    QVERIFY(root1->checkSanity());
}

void TestLayouting::tst_containerReducesSize()
{
    DeleteViews deleteViews;

    // Tests that the container reduces size when its children get hidden

    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnLeft);
    Item *item21 = createItem();
    Item *item22 = createItem();
    ItemBoxContainer::insertItemRelativeTo(item21, item2, Location_OnTop);
    ItemBoxContainer::insertItemRelativeTo(item22, item2, Location_OnTop);
    QVERIFY(root->checkSanity());

    item2->turnIntoPlaceholder();
    QVERIFY(root->checkSanity());

    item21->turnIntoPlaceholder();
    QVERIFY(root->checkSanity());

    item22->turnIntoPlaceholder();
    QVERIFY(root->checkSanity());
}

void TestLayouting::tst_insertHiddenContainer()
{
    DeleteViews deleteViews;

    auto root1 = createRoot();
    auto root2 = createRoot();
    Item *item2 = createItem();
    root2->insertItem(item2, Location_OnLeft, KDDockWidgets::InitialVisibilityOption::StartHidden);

    QVERIFY(root1->checkSanity());
    QVERIFY(root2->checkSanity());

    root1->insertItem(root2.release(), Location_OnTop);
    QVERIFY(root1->checkSanity());

    auto anotherRoot = createRoot();
    anotherRoot->insertItem(root1.release(), Location_OnTop);
    QVERIFY(anotherRoot->checkSanity());
}

void TestLayouting::tst_availableOnSide()
{
    DeleteViews deleteViews;

    // Tests that items are available to squeeze a certain amount (without violating their min-size)

    auto root = createRoot();
    Item *item1 = createItem(/*min=*/Size(100, 100));
    root->setSize(Size(1000, 1000));
    root->insertItem(item1, Location_OnLeft);

    QCOMPARE(root->availableToSqueezeOnSide(item1, Side1), 0);
    QCOMPARE(root->availableToSqueezeOnSide(item1, Side2), 0);

    Item *item2 = createItem(/*min=*/Size(200, 200));
    root->insertItem(item2, Location_OnRight);
    auto separator = root->separators_recursive()[0];
    QCOMPARE(root->minPosForSeparator_global(separator), item1->minSize().width());
    QCOMPARE(root->maxPosForSeparator_global(separator),
             root->width() - item2->minSize().width() - Item::layoutSpacing);

    QCOMPARE(root->availableToSqueezeOnSide(item1, Side1), 0);
    QCOMPARE(root->availableToSqueezeOnSide(item1, Side2),
             item2->width() - item2->minSize().width());
    QCOMPARE(root->availableToSqueezeOnSide(item2, Side1),
             item1->width() - item1->minSize().width());
    QCOMPARE(root->availableToSqueezeOnSide(item2, Side2), 0);

    Item *item3 = createItem(/*min=*/Size(200, 200));
    root->insertItem(item3, Location_OnRight);
    QVERIFY(root->checkSanity());
    QCOMPARE(root->availableToSqueezeOnSide(item3, Side1),
             (item1->width() - item1->minSize().width())
                 + (item2->width() - item2->minSize().width()));
    QCOMPARE(root->availableToSqueezeOnSide(item3, Side2), 0);

    auto separator2 = root->separators_recursive()[1];
    QCOMPARE(root->minPosForSeparator_global(separator2),
             item1->minSize().width() + item2->minSize().width() + Item::layoutSpacing);
    QCOMPARE(root->maxPosForSeparator_global(separator2),
             root->width() - item3->minSize().width() - Item::layoutSpacing);

    Item *item4 = createItem(/*min=*/Size(200, 200));
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnBottom);

    auto c = item3->parentBoxContainer();
    QCOMPARE(c->availableToSqueezeOnSide_recursive(item3, Side1, Qt::Horizontal),
             (item1->width() - item1->minSize().width())
                 + (item2->width() - item2->minSize().width()));
    QCOMPARE(c->availableToSqueezeOnSide_recursive(item3, Side2, Qt::Horizontal), 0);
    QCOMPARE(c->availableToSqueezeOnSide_recursive(item4, Side1, Qt::Horizontal),
             (item1->width() - item1->minSize().width())
                 + (item2->width() - item2->minSize().width()));
    QCOMPARE(c->availableToSqueezeOnSide_recursive(item4, Side2, Qt::Horizontal), 0);
    QCOMPARE(c->availableToSqueezeOnSide_recursive(item4, Side1, Qt::Vertical),
             (item3->height() - item3->minSize().height()));
    QCOMPARE(c->availableToSqueezeOnSide_recursive(item4, Side2, Qt::Vertical), 0);

    Item *item31 = createItem(/*min=*/Size(100, 100));
    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnRight);
    auto container31 = item31->parentBoxContainer();
    auto separator31 = container31->separators().at(0);

    // Since we don't have widgets with max-size, these two must be the same
    QCOMPARE(container31->minPosForSeparator_global(separator31, false),
             container31->minPosForSeparator_global(separator31, true));

    QCOMPARE(container31->minPosForSeparator_global(separator31),
             item1->minSize().width() + item2->minSize().width() + item3->minSize().width()
                 + 2 * Item::layoutSpacing);
    QCOMPARE(container31->maxPosForSeparator_global(separator31),
             root->width() - item31->minSize().width() - Item::layoutSpacing);
}

void TestLayouting::tst_availableToGrowOnSide()
{
    DeleteViews deleteViews;

    // Tests that items are available to grow a certain amount (without violating their max-size)
    auto root = createRoot();
    Item *item1 = createItem(/*min=*/Size(100, 100), /*max=*/Size(230, 230));
    root->setSize(Size(1000, 1000));
    root->insertItem(item1, Location_OnLeft);

    QCOMPARE(root->availableToGrowOnSide(item1, Side1), 0);
    QCOMPARE(root->availableToGrowOnSide(item1, Side2), 0);

    Item *item2 = createItem(/*min=*/Size(200, 200));
    root->insertItem(item2, Location_OnRight);

    // give a resize, so item1 gets smaller than its max-size. Will be unneeded soon
    root->setSize_recursive(Size(1001, 1001));

    QCOMPARE(root->availableToGrowOnSide(item1, Side1), 0);
    QCOMPARE(root->availableToGrowOnSide(item2, Side2), 0);
    QCOMPARE(root->availableToGrowOnSide(item1, Side2), root->length() - item2->width());
    QCOMPARE(root->availableToGrowOnSide(item2, Side1),
             item1->maxSizeHint().width() - item1->width());

    auto separator = root->separators_recursive()[0];
    QCOMPARE(root->minPosForSeparator_global(separator, true), item1->minSize().width());
    QCOMPARE(root->maxPosForSeparator_global(separator, true), item1->maxSizeHint().width());

    Item *item3 = createItem(/*min=*/Size(200, 200), /*max=*/Size(200, 200));
    root->insertItem(item3, Location_OnRight);
    QVERIFY(root->checkSanity());

    QCOMPARE(root->availableToGrowOnSide(item3, Side2), 0);
    QCOMPARE(root->availableToGrowOnSide(item3, Side1),
             root->length() - item2->width() - item1->width());
    QCOMPARE(root->availableToGrowOnSide(item2, Side1),
             item1->maxSizeHint().width() - item1->width());
    QCOMPARE(root->availableToGrowOnSide(item2, Side2),
             item3->maxSizeHint().width() - item3->width());
}

void TestLayouting::tst_resizeViaSeparator()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    Item *item1 = createItem(/*min=*/Size(100, 100));
    Item *item2 = createItem(/*min=*/Size(100, 100));
    root->setSize(Size(1000, 1000));
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);

    auto separator = root->separators_recursive().at(0);
    int oldPos = separator->position();
    const int delta = -50;

    root->requestSeparatorMove(separator, delta);
    QCOMPARE(separator->position(), oldPos + delta);

    // Now move right
    oldPos = separator->position();
    root->requestSeparatorMove(separator, -delta);
    QCOMPARE(separator->position(), oldPos - delta);


    Item *item3 = createItem(/*min=*/Size(100, 100));
    Item *item4 = createItem(/*min=*/Size(100, 100));
    root->insertItem(item4, Location_OnLeft);
    root->insertItem(item3, Location_OnRight);
    item2->turnIntoPlaceholder();
    item1->turnIntoPlaceholder();
    separator = root->separators_recursive().at(0);
    root->requestSeparatorMove(separator, delta);
}

void TestLayouting::tst_resizeViaSeparator2()
{
    DeleteViews deleteViews;

    // Here we resize one of the separators and make sure only the items next to the separator move
    // propagation should only start when constraints have been met

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item4 = createItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);
    root->insertItem(item4, Location_OnRight);

    auto resizeChildrenTo1000px = [&root] {
        /// Make sure each item has 1000  of width. Cheating here as we don't have API to resize
        /// all.
        const int numChildren = root->numChildren();
        auto children = root->childItems();
        for (auto item : std::as_const(children)) {
            item->m_sizingInfo.percentageWithinParent = 1.0 / numChildren;
        }
        root->setSize_recursive(Size(4000 + Item::layoutSpacing * (numChildren - 1), 1000));
    };

    const int delta = 100;
    const int originalChildWidth = 1000;
    resizeChildrenTo1000px();

    const auto separators = root->separators_recursive();
    QVERIFY(root->checkSanity());
    QCOMPARE(separators.size(), 3);

    root->requestSeparatorMove(separators[1], delta);

    QCOMPARE(item1->width(),
             originalChildWidth); // item1 didn't change when we moved the second separator, only
                                  // item2 and 3 are supposed to move
    QCOMPARE(item2->width(), originalChildWidth + delta);
    QCOMPARE(item3->width(), originalChildWidth - delta);
    QCOMPARE(item4->width(), originalChildWidth);

    // And back
    root->requestSeparatorMove(separators[1], -delta);
    QCOMPARE(item1->width(),
             originalChildWidth); // item1 didn't change when we moved the second separator, only
                                  // item2 and 3 are supposed to move
    QCOMPARE(item2->width(), originalChildWidth);
    QCOMPARE(item3->width(), originalChildWidth);
    QCOMPARE(item4->width(), originalChildWidth);
}

void TestLayouting::tst_resizeViaSeparator3()
{
    DeleteViews deleteViews;

    // Like tst_resizeViaSeparator2 but we have nesting, when a container is shrunk, it too
    // should only shrink its children that are near the separator, instead of all of them equally

    // Layout: |1 | 3|
    //         |4 |  |
    //         -------
    //            2

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item4 = createItem();

    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item3, item1, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item4, item1, Location_OnBottom);

    // Make some room, so each item has enough space to shrink without hitting constraints
    root->setSize_recursive(Size(1000, 4000));

    // Our horizontal separator
    const auto separators = root->separators();
    const auto horizontalSeparator = separators[0];
    QCOMPARE(separators.size(), 1);

    const int delta = 10;
    const int oldH1 = item1->height();
    const int oldH2 = item2->height();
    const int oldH3 = item3->height();
    const int oldH4 = item4->height();

    // If the following ever fails, then make sure item4 has space before we move the separator
    QVERIFY(item4->availableLength(Qt::Vertical) > delta);

    // Move separator up:
    root->requestSeparatorMove(horizontalSeparator, -delta);

    QCOMPARE(item2->height(), oldH2 + delta);
    QCOMPARE(item3->height(), oldH3 - delta);
    QCOMPARE(item4->height(), oldH4 - delta);
    QCOMPARE(item1->height(), oldH1);

    // Move down again
    root->requestSeparatorMove(horizontalSeparator, delta);

    QCOMPARE(item2->height(), oldH2);
    QCOMPARE(item3->height(), oldH3);
    QCOMPARE(item4->height(), oldH4);
    QCOMPARE(item1->height(), oldH1);
}

void TestLayouting::tst_mapToRoot()
{
    DeleteViews deleteViews;

    //   1
    // -----
    // 21|22

    auto root = createRoot();
    Item *item1 = createItem();
    root->insertItem(item1, Location_OnLeft);
    auto root2 = createRoot();
    Item *item21 = createItem();
    Item *item22 = createItem();
    root2->insertItem(item21, Location_OnLeft);
    root2->insertItem(item22, Location_OnRight);
    root->insertItem(root2.release(), Location_OnBottom);
    QVERIFY(root->checkSanity());

    auto c = item22->parentBoxContainer();
    Point rootPt = c->mapToRoot(Point(0, 0));
    QCOMPARE(rootPt, QPoint(0, item1->height() + st));
    QCOMPARE(c->mapFromRoot(rootPt), QPoint(0, 0));
}

void TestLayouting::tst_closeAndRestorePreservesPosition()
{
    DeleteViews deleteViews;

    // Result is [1, 2, 3]

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item4 = createItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);
    root->insertItem(item4, Location_OnRight);

    const int oldW1 = item1->width();
    const int oldW2 = item2->width();
    const int oldW3 = item3->width();
    const int oldW4 = item4->width();

    auto guest3 = item3->guest();
    item3->turnIntoPlaceholder();

    // Test that both sides reclaimed the space equally
    QCOMPARE(item1->width(), oldW1);
    QVERIFY(std::abs(item2->width() - (oldW2 + (oldW2 / 2))) < Item::layoutSpacing);
    QVERIFY(std::abs(item4->width() - (oldW4 + (oldW4 / 2))) < Item::layoutSpacing);

    item3->restore(guest3);

    QCOMPARE(item1->width(), oldW1);
    QCOMPARE(item2->width(), oldW2);
    QCOMPARE(item3->width(), oldW3);
    QCOMPARE(item4->width(), oldW4);
}

void TestLayouting::tst_minSizeChangedBeforeRestore()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();

    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);
    const Size originalSize2 = item2->size();

    auto guest2 = item2->guest();
    const Size newMinSize = originalSize2 + Size(10, 10);

    item2->turnIntoPlaceholder();
    dynamic_cast<Guest *>(guest2)->m_view->setMinimumSize(newMinSize);
    item2->restore(guest2);
}

void TestLayouting::tst_separatorMoveCrash()
{
    DeleteViews deleteViews;

    // Tests a crash I got when moving separator to the right

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item4 = createItem();
    auto item5 = createItem();
    auto item6 = createItem();
    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item5, item4, Location_OnRight);
    root->insertItem(item6, Location_OnRight);

    ItemBoxContainer *c = item5->parentBoxContainer();
    auto separator = c->separators().constFirst();

    const int available5 = item5->availableLength(Qt::Horizontal);

    // Separator squeezes item5 and starts squeezing item6 by 10px
    c->requestSeparatorMove(separator, available5 + 10);
}

void TestLayouting::tst_separatorMoveHonoursMax()
{
    DeleteViews deleteViews;

    const int maxWidth = 250;
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem({}, QSize(maxWidth, 250));
    auto item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);
    QVERIFY(root->checkSanity());

    auto separator1 = root->separators()[0];
    auto separator2 = root->separators()[1];

    const int min1 = root->minPosForSeparator_global(separator1);
    const int max1 = root->maxPosForSeparator_global(separator1);
    // const int min2 = root->minPosForSeparator_global(separator2);
    const int max2 = root->maxPosForSeparator_global(separator2);

    QCOMPARE(min1, item1->minSize().width());

    root->requestSeparatorMove(separator1, -(separator1->position() - min1));
    QVERIFY(item2->width() <= maxWidth);
    QVERIFY(root->checkSanity());

    root->requestSeparatorMove(separator2, max2 - separator2->position());
    QVERIFY(root->checkSanity());
    QVERIFY(item2->width() <= maxWidth);

    root->requestSeparatorMove(separator1, max1 - separator1->position());
    QVERIFY(root->checkSanity());
    QVERIFY(item2->width() <= maxWidth);

    root->requestSeparatorMove(separator1, -(separator1->position() - min1));
    QVERIFY(root->checkSanity());
    QVERIFY(item2->width() <= maxWidth);
}

void TestLayouting::tst_maxSizeHonoured1()
{
    DeleteViews deleteViews;

    // Tests that the suggested rect honors max size when adding an item to a layout.

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnTop);
    root->setSize_recursive(Size(3000, 3000));

    auto guest2 = item2->guest();
    const int maxHeight = 250;
    QCOMPARE(dynamic_cast<Guest *>(guest2)->m_view->size(), item2->size());
    dynamic_cast<Guest *>(guest2)->m_view->setMaximumSize(Size(250, maxHeight));
    QCOMPARE(dynamic_cast<Guest *>(guest2)->m_view->size(), item2->size());
    QCOMPARE(item2->maxSizeHint(), guest2->maxSizeHint());

    root->insertItem(item2, Location_OnBottom);
    QCOMPARE(item2->height(), maxHeight);
}

void TestLayouting::tst_maxSizeHonoured2()
{
    DeleteViews deleteViews;

    // Tests that a container gets the max size of its children

    //   2
    // -----
    //  1|3

    auto root1 = createRoot();
    auto root2 = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();

    root1->insertItem(item1, Location_OnTop);
    root1->insertItem(item3, Location_OnRight);
    root2->insertItem(item2, Location_OnTop);
    root2->insertItem(item3, Location_OnLeft);
    root2->removeItem(item3, /*hardRemove=*/false);

    item2->setMaxSizeHint(Size(200, 200));

    root1->insertItem(root2.release(), Location_OnBottom);
    QCOMPARE(item2->parentBoxContainer()->maxSizeHint(), item2->maxSizeHint());
}

void TestLayouting::tst_maxSizeHonoured3()
{
    DeleteViews deleteViews;

    {
        // Tests that resizing a window will now make the item with max-size grow past its max
        auto root = createRoot();
        const int minHeight = 100;
        const int maxHeight = 200;
        auto item1 = createItem(Size(100, minHeight), QSize(200, maxHeight));
        auto item2 = createItem();
        root->setSize(Size(2000, 2000));

        root->insertItem(item2, Location_OnBottom);
        root->insertItem(item1, Location_OnTop);

        // When adding, we respect max-size
        QVERIFY(item1->height() <= maxHeight);
        QVERIFY(item1->height() >= minHeight);

        // Now resize the window
        root->setSize_recursive(Size(200, 8000));

        // and we respected max-size too
        QVERIFY(item1->height() <= maxHeight);
        QVERIFY(item1->height() >= minHeight);
    }

    {
        // Also do it with nested containers
        auto root1 = createRoot();
        auto root2 = createRoot();
        const int minHeight = 100;
        const int maxHeight = 200;
        auto item1 = createItem(Size(100, minHeight), QSize(200, maxHeight));
        auto item2 = createItem();
        root1->setSize(Size(2000, 2000));
        root2->setSize(Size(2000, 2000));

        root2->insertItem(item2, Location_OnBottom);
        root1->insertItem(item1, Location_OnTop);
        root2->insertItem(root1.release(), Location_OnTop);

        // When adding, we respect max-size
        QVERIFY(item1->height() <= maxHeight);
        QVERIFY(item1->height() >= minHeight);

        // Now resize the window
        root2->setSize_recursive(Size(200, 8000));

        // and we respected max-size too
        QVERIFY(item1->height() <= maxHeight);
        QVERIFY(item1->height() >= minHeight);
    }
}

void TestLayouting::tst_requestEqualSize()
{
    DeleteViews deleteViews;

    // Tests that double-clicking a separator will make both sides equal

    {
        auto root = createRoot();
        auto item1 = createItem();
        auto item2 = createItem();
        root->insertItem(item1, Location_OnLeft);
        root->insertItem(item2, Location_OnRight);

        auto separator = root->separators().constFirst();

        const int item1Squeeze = item1->m_sizingInfo.availableLength(Qt::Horizontal);

        root->requestSeparatorMove(separator, -item1Squeeze);

        QCOMPARE(item1->width(), item1->minSize().width());
        QCOMPARE(item2->width(), root->length() - st - item1->width());

        root->requestEqualSize(separator);
        QVERIFY(std::abs(item1->width() - item2->width()) < 5);
    }

    {
        // Similar, but now we have max-size to honour too
        auto root = createRoot();
        const int minWidth1 = 100;
        const int maxWidth1 = 200;
        auto item1 = createItem(Size(minWidth1, 100), QSize(maxWidth1, 200));
        auto item2 = createItem();
        root->insertItem(item2, Location_OnRight);
        root->insertItem(item1, Location_OnLeft);

        QCOMPARE(item1->width(), item1->maxSizeHint().width());
        auto separator = root->separators().constFirst();
        root->requestEqualSize(separator);
        // Separator didn't move, doing so would make item1 bigger than its max size
        QCOMPARE(item1->width(), item1->maxSizeHint().width());

        {
            // Let's put the separator further right manually, then try again:
            // (Can't use ItemBoxContainer::requstSeparatorMove() as it respects max-size
            // constraints
            item1->m_sizingInfo.incrementLength(20, Qt::Horizontal);
            item2->m_sizingInfo.incrementLength(-20, Qt::Horizontal);
            root->positionItems();
        }


        QCOMPARE(item1->width(), maxWidth1 + 20);

        // Double clicking on the separator will put it back at a sane place

        const int minPos = root->minPosForSeparator_global(separator, true);
        const int maxPos = root->maxPosForSeparator_global(separator, true);

        QCOMPARE(minPos, minWidth1);
        QCOMPARE(maxPos, maxWidth1);

        root->requestEqualSize(separator);
        QCOMPARE(item1->width(), maxWidth1);
    }
}

void TestLayouting::tst_maxSizeHonouredWhenAnotherRemoved()
{
    DeleteViews deleteViews;

    // Test that when removing item 3 that all the new available space goes to item1, so that
    // we don't violate the space of item 1

    auto root = createRoot();
    root->setSize(Size(300, 3000));
    auto item1 = createItem();
    const int minHeight = 100;
    const int maxHeight = 200;
    auto item2 = createItem(Size(100, minHeight), QSize(200, maxHeight));
    auto item3 = createItem();
    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);
    root->insertItem(item3, Location_OnBottom);

    QVERIFY(item2->height() <= maxHeight);
    root->removeItem(item3);
    QVERIFY(item2->height() <= maxHeight);

    root->dumpLayout();
}

void TestLayouting::tst_simplify()
{
    DeleteViews deleteViews;

    ScopedValueRollback inhibitSimplify(ItemBoxContainer::s_inhibitSimplify, true);

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);

    auto root2 = createRoot();
    auto root22 = createRoot();
    auto item21 = createItem();
    root22->insertItem(item21, Location_OnLeft);
    root2->insertItem(root22.release(), Location_OnLeft);
    root->insertItem(root2.release(), Location_OnBottom);

    QVERIFY(root->childItems().at(2)->isContainer());

    root->simplify();

    for (Item *item : root->childItems()) {
        QVERIFY(!item->isContainer());
    }
}

void TestLayouting::tst_adjacentLayoutBorders()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item4 = createItem();
    auto item5 = createItem();

    root->insertItem(item1, Location_OnTop);
    const int allBorders = int(LayoutBorderLocation_All);

    auto borders1 = item1->adjacentLayoutBorders();
    QCOMPARE(borders1, allBorders);
    root->insertItem(item2, Location_OnBottom);

    borders1 = item1->adjacentLayoutBorders();
    QCOMPARE(borders1, allBorders & ~LayoutBorderLocation_South);

    auto borders2 = item2->adjacentLayoutBorders();
    QCOMPARE(borders2, allBorders & ~LayoutBorderLocation_North);

    root->insertItem(item3, Location_OnRight);

    borders1 = item1->adjacentLayoutBorders();
    QCOMPARE(borders1, LayoutBorderLocation_North | LayoutBorderLocation_West);

    borders2 = item2->adjacentLayoutBorders();
    QCOMPARE(borders2, LayoutBorderLocation_South | LayoutBorderLocation_West);

    auto borders3 = item3->adjacentLayoutBorders();
    QCOMPARE(borders3, allBorders & ~(LayoutBorderLocation_West));

    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnBottom);
    auto borders4 = item4->adjacentLayoutBorders();
    QCOMPARE(borders4, LayoutBorderLocation_East | LayoutBorderLocation_South);

    root->insertItem(item5, Location_OnRight);
    borders4 = item4->adjacentLayoutBorders();
    QCOMPARE(borders4, LayoutBorderLocation_South);
}

void TestLayouting::tst_numSideBySide_recursive()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    QVERIFY(root->isVertical());
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 0);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 0);

    auto item1 = createItem();
    root->insertItem(item1, Location_OnRight);
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 1);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 1);


    auto item2 = createItem();
    root->insertItem(item2, Location_OnTop);
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 2);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 1);

    auto item3 = createItem();
    root->insertItem(item3, Location_OnTop);
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 3);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 1);

    auto item1Child = createItem();
    ItemBoxContainer::insertItemRelativeTo(item1Child, item1, Location_OnLeft);
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 3);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 2);

    auto item1Child1Child = createItem();
    ItemBoxContainer::insertItemRelativeTo(item1Child1Child, item1Child, Location_OnBottom);
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 4);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 2);

    item2->turnIntoPlaceholder();
    QCOMPARE(root->numSideBySide_recursive(Qt::Vertical), 3);
    QCOMPARE(root->numSideBySide_recursive(Qt::Horizontal), 2);
}

void TestLayouting::tst_sizingInfoSerialization()
{
    DeleteViews deleteViews;

    SizingInfo info;
    info.minSize = { 10, 10 };
    info.geometry = { 10, 10, 100, 100 };
    info.maxSizeHint = { 300, 300 };
    info.percentageWithinParent = 5;
    info.isBeingInserted = false;

    nlohmann::json json = info;

    SizingInfo info2;
    json.get_to(info2);

    QCOMPARE(info2.minSize, info.minSize);
    QCOMPARE(info2.maxSizeHint, info.maxSizeHint);
    QCOMPARE(info2.geometry, info.geometry);
    QCOMPARE(info2.isBeingInserted, info.isBeingInserted);
    QCOMPARE(info2.percentageWithinParent, info.percentageWithinParent);
}

void TestLayouting::tst_itemSerialization()
{
    DeleteViews deleteViews;

    auto root = createRoot();

    auto item1 = createItem();
    root->insertItem(item1, Location_OnRight);

    auto item2 = createItem();
    root->insertItem(item2, Location_OnRight);

    auto item3 = createItem();
    ItemBoxContainer::insertItemRelativeTo(item3, item1, Location_OnBottom);

    Item *rootItem = root.get();
    nlohmann::json json = rootItem;

    QCOMPARE(json["children"].size(), 2);
    QVERIFY(json["isContainer"]);
    QVERIFY(json["children"][0]["isContainer"]);
    QVERIFY(!json["children"][1]["isContainer"]);
}

void TestLayouting::tst_outermostVisibleNeighbor()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    root->setSize({ 1000, 1000 });

    QVERIFY(!root->outermostNeighbor(KDDockWidgets::Location_OnRight));

    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item0 = createItem();
    auto itemTop = createItem();


    root->insertItem(item1, Location_OnRight);
    QVERIFY(!item1->outermostNeighbor(KDDockWidgets::Location_OnLeft));
    QVERIFY(!item1->outermostNeighbor(KDDockWidgets::Location_OnRight));

    root->insertItem(item2, Location_OnRight);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight), item2);

    root->insertItem(item3, Location_OnRight);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight), item3);

    root->insertItem(item0, Location_OnLeft);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft), item0);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight), item3);

    root->insertItem(itemTop, Location_OnTop);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnBottom), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop), itemTop);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft), item0);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight), item3);
}

void TestLayouting::tst_outermostNeighbor()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    root->setSize({ 1000, 1000 });

    QVERIFY(!root->outermostNeighbor(KDDockWidgets::Location_OnRight, false));

    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item0 = createItem();
    auto itemTop = createItem();

    root->insertItem(item1, Location_OnRight, InitialVisibilityOption::StartHidden);
    QVERIFY(item1->parentBoxContainer() == root.get());
    QVERIFY(!item1->outermostNeighbor(KDDockWidgets::Location_OnLeft, false));
    QVERIFY(!item1->outermostNeighbor(KDDockWidgets::Location_OnRight, false));

    root->insertItem(item2, Location_OnRight, InitialVisibilityOption::StartHidden);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop, false), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft, false), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight, false), item2);

    root->insertItem(item3, Location_OnRight, InitialVisibilityOption::StartHidden);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop, false), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft, false), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight, false), item3);

    root->insertItem(item0, Location_OnLeft, InitialVisibilityOption::StartHidden);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop, false), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft, false), item0);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight, false), item3);

    root->insertItem(itemTop, Location_OnTop, InitialVisibilityOption::StartHidden);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnBottom, false), nullptr);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnTop, false), itemTop);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnLeft, false), item0);
    QCOMPARE(item1->outermostNeighbor(KDDockWidgets::Location_OnRight, false), item3);
}

void TestLayouting::tst_relativeToHidden()
{
    // Tests that we can insert relative to an hidden item

    DeleteViews deleteViews;
    auto root = createRoot();
    root->setSize({ 1000, 1000 });

    auto item0 = createItem();
    auto item1 = createItem();
    auto item2 = createItem();

    root->insertItem(item0, Location_OnRight);
    root->insertItem(item1, Location_OnRight, InitialVisibilityOption::StartHidden);
    QVERIFY(!item1->isVisible());

    QVERIFY(root->checkSanity());
    ItemBoxContainer::insertItemRelativeTo(item2, item1, Location_OnBottom);
    QVERIFY(root->checkSanity());
    QVERIFY(!item1->isVisible());
    QVERIFY(item2->isVisible());

    QCOMPARE(root->childItems().size(), 2);
    auto innerContainer = root->childItems().constLast()->asBoxContainer();
    QVERIFY(innerContainer);

    QCOMPARE(innerContainer->childItems().size(), 2);
    QVERIFY(innerContainer->isVertical());
    QCOMPARE(innerContainer->childItems()[0], item1);
    QCOMPARE(innerContainer->childItems()[1], item2);
}

void TestLayouting::tst_spuriousResize()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    root->setSize({ 1000, 1000 });

    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();

    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnTop);

    // root was vertical, now it will be horizontal.
    // This used to generate a spurious resize
    auto guest1 = static_cast<Guest *>(item1->guest());
    guest1->m_numSetGeometry = 0;
    root->insertItem(item3, Location_OnRight, QSize(200, 200));
    QCOMPARE(guest1->m_numSetGeometry, 1);
}

void TestLayouting::tst_relayoutIfNeeded()
{
    DeleteViews deleteViews;

    auto root = createRoot();
    root->setSize({ 1000, 1000 });

    auto item1 = createItem({ 600, 0 });
    item1->setSize({ 600, 100 });

    auto item11 = createItem();
    auto item12 = createItem();
    auto item2 = createItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item11, item1, Location_OnBottom);
    ItemBoxContainer::insertItemRelativeTo(item12, item1, Location_OnBottom);

    QVERIFY(root->checkSanity());
    QVERIFY(!root->isOverflowing());

    // Make item1's min width bigger than it's actual width. Layout is now invalid!
    item1->m_sizingInfo.minSize = { item1->width() + 1, 0 };

    {
        SetExpectedWarning w("Size constraints not honoured");
        QVERIFY(!root->checkSanity());
    }

    root->relayoutIfNeeded();
    root->positionItems_recursive();
    QVERIFY(!root->isOverflowing());
    QVERIFY(root->checkSanity());
}

#define KDDW_TEST_NAME TestLayouting
#include "test_main_qt.h"

#include "tst_multisplitter.moc"
