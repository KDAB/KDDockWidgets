/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "doctest_main.h"

#include "core/layouting/Item_p.h"
#include "kddockwidgets/core/Separator.h"
#include "kddockwidgets/core/Platform.h"
#include "kddockwidgets/core/View.h"
#include "kddockwidgets/core/ViewFactory.h"

#include "Config.h"

#include <QScopedValueRollback>
#include <QPointer>

#include <memory.h>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Core;

static int st = Item::separatorThickness;


static bool serializeDeserializeTest(const std::unique_ptr<ItemBoxContainer> &root)
{
    // Serializes and deserializes a layout
    if (!root->checkSanity())
        return false;

    const QVariantMap serialized = root->toVariantMap();
    ItemBoxContainer root2(root->hostView());

    QHash<QString, View *> widgets;
    const Item::List originalItems = root->items_recursive();
    for (Item *item : originalItems)
        if (auto view = item->guestView())
            widgets.insert(view->id(), view);

    root2.fillFromVariantMap(serialized, widgets);

    return root2.checkSanity();
}

static std::unique_ptr<ItemBoxContainer> createRoot()
{
    auto hostWidget = Core::Platform::instance()->tests_createView({});
    hostWidget->setObjectName("HostWidget");
    hostWidget->show();
    auto root = new ItemBoxContainer(hostWidget);
    root->setSize({ 1000, 1000 });
    return std::unique_ptr<ItemBoxContainer>(root);
}

static Item *createItem(QSize minSz = {}, QSize maxSz = {})
{
    static int count = 0;
    count++;
    auto hostWidget = Core::Platform::instance()->tests_createView({});
    hostWidget->setObjectName("HostWidget");
    hostWidget->show();
    auto item = new Item(hostWidget);
    item->setGeometry(QRect(0, 0, 200, 200));
    item->setObjectName(QStringLiteral("%1").arg(count));
    Core::CreateViewOptions opts;
    if (minSz.isValid())
        opts.minSize = minSz;
    if (maxSz.isValid())
        opts.maxSize = maxSz;
    auto guest = Core::Platform::instance()->tests_createView(opts);

    guest->setObjectName(item->objectName());
    item->setGuestView(guest);
    return item;
}

static ItemBoxContainer *createRootWithSingleItem()
{
    auto host = Core::Platform::instance()->tests_createView({});
    auto root = new ItemBoxContainer(host);
    root->setSize({ 1000, 1000 });

    Item *item1 = createItem();
    root->insertItem(item1, Location_OnTop);

    return root;
}

TEST_CASE("tst_createRoot()")
{
    auto root = createRoot();
    CHECK(root->isRoot());
    CHECK(root->isContainer());
    CHECK(root->hasOrientation());
    CHECK_EQ(root->size(), QSize(1000, 1000));
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertOne")
{
    auto root = createRoot();
    auto item = createItem();
    root->insertItem(item, Location_OnTop);
    CHECK(root->checkSanity());
    CHECK_EQ(root->numChildren(), 1);
    CHECK(!item->isContainer());
    CHECK_EQ(root->size(), QSize(1000, 1000));
    CHECK_EQ(item->size(), root->size());
    CHECK_EQ(item->pos(), QPoint());
    CHECK_EQ(item->pos(), root->pos());
    CHECK(root->hasChildren());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertThreeSideBySide")
{
    // Result is [1, 2, 3]
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();

    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);

    CHECK(root->checkSanity());
    CHECK_EQ(root->numChildren(), 3);
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertTwoHorizontal")
{
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnLeft);
    ItemBoxContainer::insertItemRelativeTo(item2, item1, Location_OnRight);
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertTwoVertical")
{
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnTop);
    ItemBoxContainer::insertItemRelativeTo(item2, item1, Location_OnBottom);
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertOnWidgetItem1")
{
    // We insert into a widget item instead of in a container. It will insert in the container still
    // Result is still [1, 2, 3]

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);

    CHECK(item3->x() > item2->x());
    CHECK_EQ(item3->y(), item2->y());

    CHECK(root->checkSanity());
    CHECK_EQ(root->numChildren(), 3);
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertOnWidgetItem2")
{
    // Same, but result [1, 3, 2]

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnLeft);

    CHECK(item1->x() < item3->x());
    CHECK(item3->x() < item2->x());
    CHECK_EQ(item3->y(), item2->y());

    CHECK(root->checkSanity());
    CHECK_EQ(root->numChildren(), 3);
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertOnWidgetItem1DifferentOrientation")
{
    // Result [1, 2, |3  |]
    //               |3.1|

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item31 = createItem();
    root->insertItem(item1, Location_OnLeft);
    CHECK(root->checkSanity());

    root->insertItem(item2, Location_OnRight);
    CHECK(root->checkSanity());

    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnRight);
    CHECK(root->checkSanity());

    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);
    CHECK(root->checkSanity());

    auto container3 = item3->parentBoxContainer();
    CHECK(container3->isContainer());
    CHECK(container3 != root.get());
    CHECK(root->isHorizontal());
    CHECK(container3->isVertical());

    CHECK_EQ(root->numChildren(), 3);
    CHECK_EQ(container3->numChildren(), 2);

    CHECK(item1->x() < item2->x());
    CHECK(item3->parentBoxContainer()->x() > item2->x());
    CHECK_EQ(item3->x(), 0);
    CHECK_EQ(item3->y(), item2->y());
    CHECK_EQ(item1->y(), item2->y());

    CHECK(item31->y() >= item3->y());
    CHECK_EQ(item31->parentBoxContainer(), container3);
    CHECK_EQ(item3->parentBoxContainer(), container3);
    CHECK_EQ(container3->parentBoxContainer(), root.get());
    CHECK_EQ(QPoint(0, 0), item3->pos());
    CHECK_EQ(container3->width(), item3->width());
    CHECK_EQ(container3->height(), item3->height() + st + item31->height());

    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertOnWidgetItem2DifferentOrientation")
{
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
    CHECK(root->checkSanity());
    auto container3 = item3->parentBoxContainer();

    CHECK_EQ(container3->parentBoxContainer(), container3Parent);

    CHECK(container3->isContainer());
    CHECK(container3 != root.get());
    CHECK(root->isHorizontal());
    CHECK(container3->isHorizontal());
    CHECK(container3Parent->isVertical());

    CHECK_EQ(root->numChildren(), 3);
    CHECK_EQ(container3->numChildren(), 2);
    CHECK_EQ(container3Parent->numChildren(), 2);

    CHECK(item1->x() < item2->x());
    CHECK_EQ(container3->pos(), QPoint(0, 0l));
    CHECK_EQ(item3->pos(), container3->pos());
    CHECK(container3Parent->x() > item2->x());
    CHECK_EQ(item3->y(), item2->y());
    CHECK_EQ(item1->y(), item2->y());

    CHECK(item4->y() >= item3->y());
    CHECK_EQ(item4->parentBoxContainer(), container3Parent);
    CHECK_EQ(item3->parentBoxContainer(), container3);
    CHECK_EQ(container3Parent->parentBoxContainer(), root.get());
    CHECK_EQ(container3->pos(), item3->pos());
    CHECK_EQ(container3->width(), item3->width() + item5->width() + st);
    CHECK_EQ(container3->height(), item3->height());
    CHECK_EQ(container3Parent->height(), item3->height() + st + item4->height());

    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_insertOnRootDifferentOrientation")
{
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

    CHECK_EQ(item4->parentBoxContainer(), root.get());
    CHECK_EQ(item4->pos(), root->pos());
    CHECK_EQ(item4->width(), root->width());

    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_removeItem1")
{
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
    CHECK(root->checkSanity());
    CHECK_EQ(root->numChildren(), 2);

    root->removeItem(item4);
    CHECK(root->checkSanity());
    CHECK_EQ(root->numChildren(), 1);

    auto c1 = item1->parentBoxContainer();
    CHECK_EQ(c1->pos(), QPoint(0, 0));
    CHECK_EQ(c1->width(), root->width());
    CHECK_EQ(c1->height(), item1->height());
    CHECK_EQ(c1->height(), root->height());

    const int item3and32Width = item3->width() + item32->width() + st;
    root->removeItem(item32);

    CHECK_EQ(item3->width(), item3and32Width);
    CHECK(root->checkSanity());

    root->removeItem(item31);
    CHECK(root->checkSanity());

    CHECK_EQ(item2->height(), item3->height());

    QPointer<Item> c3 = item3->parentBoxContainer();
    root->removeItem(c3);
    CHECK(c3.isNull());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_removeItem2")
{
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

TEST_CASE("tst_minSize")
{
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

    CHECK_EQ(item2->minSize(), QSize(200, 300));
    CHECK_EQ(item2->parentBoxContainer()->minSize(), QSize(200, 300 + 100 + st));

    CHECK_EQ(root->minSize(), QSize(101 + 200 + st, 300 + 100 + st));
    CHECK(root->checkSanity());

    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_resize")
{
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
    CHECK(root->checkSanity());

    CHECK(item1Percentage - (1.0 * item1->width() / root->width()) < 0.01);
    CHECK(item2Percentage - (1.0 * item2->width() / root->width()) < 0.01);
    CHECK(item3Percentage - (1.0 * item3->width() / root->width()) < 0.01);
    CHECK_EQ(root->width(), 2000);
    CHECK_EQ(root->height(), 505);
    CHECK_EQ(item1->height(), 505);
    CHECK_EQ(item2->height(), 505);
    CHECK_EQ(item3->height(), 505);

    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnBottom);

    CHECK(root->checkSanity());
    root->setSize_recursive({ 2500, 505 });
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_resizeWithConstraints")
{
    Platform::s_expectedWarning = QStringLiteral("New size doesn't respect size constraints");

    {
        // Test that resizing below minSize isn't permitted.

        auto root = createRoot();
        auto item1 = createItem();
        item1->setMinSize(QSize(500, 500));
        root->insertItem(item1, Location_OnLeft);
        CHECK(root->checkSanity());

        root->setSize_recursive(item1->minSize()); // Still fits
        root->setSize_recursive(item1->minSize() - QSize(1, 0)); // wouldn't fit
        CHECK_EQ(root->size(), item1->size()); // still has the old size
        CHECK(serializeDeserializeTest(root));
    }

    {
        // |1|2|3|

        auto root = createRoot();
        auto item1 = createItem();
        auto item2 = createItem();
        auto item3 = createItem();
        root->setSize_recursive(QSize(2000, 500));
        item1->setMinSize(QSize(500, 500));
        item2->setMinSize(QSize(500, 500));
        item3->setMinSize(QSize(500, 500));
        root->insertItem(item1, Location_OnLeft);
        root->insertItem(item2, Location_OnRight);
        root->insertItem(item3, Location_OnRight);
        CHECK(root->checkSanity());
    }
    Platform::s_expectedWarning.clear();
}

TEST_CASE("tst_availableSize")
{
    auto root = createRoot();
    CHECK_EQ(root->availableSize(), QSize(1000, 1000));
    CHECK_EQ(root->minSize(), QSize(0, 0));

    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    item1->m_sizingInfo.minSize = { 100, 100 };
    item2->m_sizingInfo.minSize = { 100, 100 };
    item3->m_sizingInfo.minSize = { 100, 100 };

    root->insertItem(item1, Location_OnLeft);
    CHECK_EQ(root->availableSize(), QSize(900, 900));
    CHECK_EQ(root->minSize(), QSize(100, 100));
    CHECK_EQ(root->neighboursLengthFor(item1, Side1, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursLengthFor(item1, Side2, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursMinLengthFor(item1, Side1, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursMinLengthFor(item1, Side2, Qt::Horizontal), 0);

    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side1, Qt::Vertical), 0);
    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side2, Qt::Vertical), 0);
    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side1, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side2, Qt::Horizontal), 0);

    root->insertItem(item2, Location_OnLeft);
    CHECK_EQ(root->availableSize(), QSize(800 - st, 900));
    CHECK_EQ(root->minSize(), QSize(200 + st, 100));
    CHECK_EQ(root->neighboursLengthFor(item1, Side1, Qt::Horizontal), item2->width());
    CHECK_EQ(root->neighboursLengthFor(item1, Side2, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursLengthFor(item2, Side1, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursLengthFor(item2, Side2, Qt::Horizontal), item1->width());
    CHECK_EQ(root->neighboursMinLengthFor(item1, Side1, Qt::Horizontal), item2->minSize().width());
    CHECK_EQ(root->neighboursMinLengthFor(item1, Side2, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursMinLengthFor(item2, Side1, Qt::Horizontal), 0);
    CHECK_EQ(root->neighboursMinLengthFor(item2, Side2, Qt::Horizontal), item1->minSize().width());

    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side1, Qt::Vertical), 0);
    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side2, Qt::Vertical), 0);
    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side1, Qt::Horizontal), item2->width());
    CHECK_EQ(root->neighboursLengthFor_recursive(item1, Side2, Qt::Horizontal), 0);

    root->insertItem(item3, Location_OnBottom);
    CHECK_EQ(root->availableSize(), QSize(800 - st, 800 - st));
    CHECK_EQ(root->minSize(), QSize(200 + st, 100 + 100 + st));
    CHECK_EQ(item3->parentBoxContainer()->neighboursMinLengthFor(item3, Side1, Qt::Vertical),
             item1->minSize().height());

    auto container2 = item2->parentBoxContainer();
    CHECK_EQ(container2->neighboursLengthFor_recursive(item1, Side1, Qt::Vertical), 0);
    CHECK_EQ(container2->neighboursLengthFor_recursive(item1, Side2, Qt::Vertical),
             item3->height());
    CHECK_EQ(container2->neighboursLengthFor_recursive(item1, Side1, Qt::Horizontal),
             item2->width());
    CHECK_EQ(container2->neighboursLengthFor_recursive(item1, Side2, Qt::Horizontal), 0);

    // More nesting
    auto item4 = createItem();
    auto item5 = createItem();
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item5, item4, Location_OnBottom);

    auto container4 = item4->parentBoxContainer();
    CHECK_EQ(container4->neighboursLengthFor_recursive(item4, Side1, Qt::Vertical),
             item1->height());
    CHECK_EQ(container4->neighboursLengthFor_recursive(item4, Side2, Qt::Vertical),
             item5->height());
    CHECK_EQ(container4->neighboursLengthFor_recursive(item4, Side1, Qt::Horizontal),
             item3->width());
    CHECK_EQ(container4->neighboursLengthFor_recursive(item4, Side2, Qt::Horizontal), 0);
    CHECK_EQ(container4->neighboursLengthFor_recursive(item5, Side1, Qt::Vertical),
             item4->height() + item1->height());
    CHECK_EQ(container4->neighboursLengthFor_recursive(item5, Side2, Qt::Vertical), 0);
    CHECK_EQ(container4->neighboursLengthFor_recursive(item5, Side1, Qt::Horizontal),
             item3->width());
    CHECK_EQ(container4->neighboursLengthFor_recursive(item5, Side2, Qt::Horizontal), 0);

    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_missingSize")
{
    auto root = createRoot();
    CHECK_EQ(root->size(), QSize(1000, 1000));
    CHECK_EQ(root->availableSize(), QSize(1000, 1000));

    Item *item1 = createItem();
    item1->setMinSize({ 100, 100 });

    Item *item2 = createItem();
    item2->setMinSize(root->size());

    Item *item3 = createItem();
    item3->setMinSize(root->size() + QSize(100, 200));

    // Test with an existing item
    root->insertItem(item1, Location_OnTop);
    CHECK(serializeDeserializeTest(root));

    delete item2;
    delete item3;
}

TEST_CASE("tst_ensureEnoughSize")
{
    // Tests that the layout's size grows when the item being inserted wouldn't have enough space

    auto root = createRoot(); /// 1000x1000
    Item *item1 = createItem();
    item1->setMinSize({ 2000, 500 });

    // Insert to empty layout:

    root->insertItem(item1, Location_OnLeft);
    CHECK_EQ(root->size(), QSize(2000, 1000));
    CHECK_EQ(item1->size(), QSize(2000, 1000));
    CHECK_EQ(item1->minSize(), root->minSize());
    CHECK(root->checkSanity());

    // Insert to non-empty layout
    Item *item2 = createItem();
    item2->setMinSize({ 2000, 2000 });
    root->insertItem(item2, Location_OnRight);
    CHECK(root->checkSanity());
    CHECK_EQ(
        root->size(),
        QSize(item1->minSize().width() + item2->minSize().width() + st, item2->minSize().height()));
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_turnIntoPlaceholder")
{
    auto root = createRoot();

    int numVisibleItems = 0;
    root->numVisibleItemsChanged.connect(
        [&numVisibleItems](int count) { numVisibleItems = count; });

    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    CHECK_EQ(numVisibleItems, 1);
    CHECK(item1->isVisible());
    item1->turnIntoPlaceholder();
    CHECK_EQ(numVisibleItems, 0);
    CHECK(!item1->isVisible());
    CHECK_EQ(root->visibleCount_recursive(), 0);
    CHECK_EQ(root->count_recursive(), 1);
    CHECK(root->checkSanity());

    root->insertItem(item2, Location_OnLeft);
    CHECK(root->checkSanity());
    CHECK_EQ(numVisibleItems, 1);

    root->insertItem(item3, Location_OnLeft);
    CHECK_EQ(numVisibleItems, 2);
    CHECK(root->checkSanity());
    CHECK_EQ(item2->width() + item3->width() + st, root->width());
    item2->turnIntoPlaceholder();
    CHECK_EQ(numVisibleItems, 1);
    CHECK(root->checkSanity());
    CHECK_EQ(item3->width(), root->width());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_suggestedRect")
{
    auto root = createRoot();
    root->setSize(QSize(2000, 1000));
    const QSize minSize(100, 100);
    Item itemBeingDropped(nullptr);
    itemBeingDropped.setMinSize(minSize);

    QRect leftRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnLeft);
    QRect topRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnTop);
    QRect bottomRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnBottom);
    QRect rightRect = root->suggestedDropRect(&itemBeingDropped, nullptr, Location_OnRight);

    // Test relative to root:
    CHECK(leftRect.width() >= minSize.width());
    CHECK(topRect.height() >= minSize.height());
    CHECK(bottomRect.height() >= minSize.height());
    CHECK(rightRect.width() >= minSize.width());
    CHECK_EQ(leftRect.topLeft(), QPoint(0, 0));
    CHECK_EQ(leftRect.bottomLeft(), root->rect().bottomLeft());
    CHECK_EQ(rightRect.topRight(), root->rect().topRight());
    CHECK_EQ(rightRect.bottomRight(), root->rect().bottomRight());
    CHECK_EQ(topRect.topLeft(), root->rect().topLeft());
    CHECK_EQ(topRect.topRight(), root->rect().topRight());
    CHECK_EQ(bottomRect.bottomLeft(), root->rect().bottomLeft());
    CHECK_EQ(bottomRect.bottomRight(), root->rect().bottomRight());

    // Test relative to an item
    Item *item1 = createItem();
    item1->setMinSize(QSize(100, 100));
    root->insertItem(item1, Location_OnLeft);
    leftRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnLeft);
    topRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnTop);
    bottomRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnBottom);
    rightRect = root->suggestedDropRect(&itemBeingDropped, item1, Location_OnRight);
    CHECK(leftRect.width() >= minSize.width());
    CHECK(topRect.height() >= minSize.height());
    CHECK(bottomRect.height() >= minSize.height());
    CHECK(rightRect.width() >= minSize.width());
    CHECK_EQ(leftRect.topLeft(), QPoint(0, 0));
    CHECK_EQ(leftRect.bottomLeft(), root->rect().bottomLeft());
    CHECK_EQ(rightRect.topRight(), root->rect().topRight());
    CHECK_EQ(rightRect.bottomRight(), root->rect().bottomRight());
    CHECK_EQ(topRect.topLeft(), root->rect().topLeft());
    CHECK_EQ(topRect.topRight(), root->rect().topRight());
    CHECK_EQ(bottomRect.bottomLeft(), root->rect().bottomLeft());
    CHECK_EQ(bottomRect.bottomRight(), root->rect().bottomRight());


    // Insert another item:
    Item *item2 = createItem();
    item1->setMinSize(QSize(100, 100));
    root->insertItem(item2, Location_OnRight);
    leftRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnLeft);
    topRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnTop);
    bottomRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnBottom);
    rightRect = root->suggestedDropRect(&itemBeingDropped, item2, Location_OnRight);
    CHECK_EQ(leftRect.y(), item2->geometry().y());
    CHECK(leftRect.x() < item2->geometry().x());
    CHECK(leftRect.x() > item1->geometry().x());
    CHECK_EQ(rightRect.topRight(), root->rect().topRight());
    CHECK_EQ(rightRect.bottomRight(), root->rect().bottomRight());
    CHECK_EQ(topRect.topLeft(), item2->geometry().topLeft());
    CHECK_EQ(topRect.topRight(), item2->geometry().topRight());
    CHECK_EQ(bottomRect.bottomLeft(), item2->geometry().bottomLeft());
    CHECK_EQ(bottomRect.bottomRight(), item2->geometry().bottomRight());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_suggestedRect2")
{
    // Tests a bug where the inner drop locations didn't work when there was a nested container
    // Like container >> container >> Item

    auto root1 = createRoot();
    auto root2 = createRoot();

    Item itemBeingDropped(nullptr);
    itemBeingDropped.setMinSize(QSize(100, 100));

    Item *item = createItem();

    root2->insertItem(item, Location_OnRight);
    root1->insertItem(root2.release(), Location_OnRight);

    CHECK(item->parentBoxContainer()
              ->suggestedDropRect(&itemBeingDropped, item, Location_OnRight)
              .isValid());
}

TEST_CASE("tst_suggestedRect3")
{
    auto root1 = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    Item *itemToDrop = createItem();

    root1->insertItem(item1, Location_OnLeft);
    root1->insertItem(item2, Location_OnRight);
    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnBottom);

    CHECK(!item3->parentBoxContainer()
               ->suggestedDropRect(itemToDrop, item3, Location_OnLeft)
               .isEmpty());
    delete itemToDrop;
}

TEST_CASE("tst_suggestedRect4")
{
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

    CHECK(root->checkSanity());
    CHECK(!item3->parentBoxContainer()
               ->suggestedDropRect(itemToDrop, item3, Location_OnLeft)
               .isEmpty());

    delete itemToDrop;
}

TEST_CASE("tst_insertAnotherRoot")
{
    {
        auto root1 = createRoot();
        Item *item1 = createItem();
        root1->insertItem(item1, Location_OnRight);
        auto host1 = root1->hostView();

        auto root2 = createRoot();
        Item *item2 = createItem();
        root2->insertItem(item2, Location_OnRight);

        root1->insertItem(root2.release(), Location_OnBottom);

        CHECK(root1->hostView()->equals(host1));
        CHECK(item2->hostView()->equals(host1));
        const auto &items = root1->items_recursive();
        for (Item *item : items) {
            CHECK(item->hostView()->equals(host1));
            CHECK(item->isVisible());
        }
        CHECK(root1->checkSanity());
        CHECK(serializeDeserializeTest(root1));
    }

    {
        auto root1 = createRoot();
        Item *item1 = createItem();
        Item *item2 = createItem();
        root1->insertItem(item1, Location_OnLeft);
        root1->insertItem(item2, Location_OnRight);
        auto host1 = root1->hostView();

        auto root2 = createRoot();
        Item *item12 = createItem();
        root2->insertItem(item12, Location_OnRight);

        root1->insertItem(root2.release(), Location_OnTop);

        CHECK(root1->hostView()->equals(host1));
        CHECK(item2->hostView()->equals(host1));
        for (Item *item : root1->items_recursive()) {
            CHECK(item->hostView()->equals(host1));
            CHECK(item->isVisible());
        }
        CHECK(root1->checkSanity());
        CHECK(serializeDeserializeTest(root1));
    }
}

TEST_CASE("tst_misc1")
{
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

    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_misc2")
{
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
    CHECK(root->checkSanity());
    ItemBoxContainer::insertItemRelativeTo(root2, item1, Location_OnRight);
    CHECK(root->checkSanity());
    root->insertItem(item3, Location_OnBottom);
    CHECK(root->checkSanity());
    ItemBoxContainer::insertItemRelativeTo(root4, item3, Location_OnRight);
    CHECK(root->checkSanity());

    root->insertItem(root5, Location_OnLeft);
    CHECK(root->checkSanity());

    item5->parentBoxContainer()->removeItem(item5);
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_misc3")
{
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
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_containerGetsHidden")
{
    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    CHECK(root->checkSanity());

    root->insertItem(item2, Location_OnRight);
    CHECK(root->checkSanity());

    ItemBoxContainer::insertItemRelativeTo(item3, item2, Location_OnBottom);
    CHECK(root->checkSanity());

    item2->turnIntoPlaceholder();
    CHECK(root->checkSanity());

    item3->turnIntoPlaceholder();
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_minSizeChanges")
{
    auto root = createRoot();
    Item *item1 = createItem();
    root->insertItem(item1, Location_OnLeft);

    root->setSize_recursive(QSize(200, 200));
    CHECK(root->checkSanity());

    auto w1 = item1;
    w1->setMinSize(QSize(300, 300));
    CHECK(root->checkSanity());
    CHECK_EQ(root->size(), QSize(300, 300));

    Item *item2 = createItem();
    root->insertItem(item2, Location_OnTop);
    CHECK(root->checkSanity());

    root->setSize_recursive(QSize(1000, 1000));
    CHECK(root->checkSanity());

    w1->setMinSize(QSize(700, 700));
    CHECK(root->checkSanity());
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_numSeparators")
{
    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    Item *item3 = createItem();
    Item *item4 = createItem();

    CHECK_EQ(root->separators_recursive().size(), 0);

    root->insertItem(item1, Location_OnLeft);
    CHECK_EQ(root->separators_recursive().size(), 0);

    root->insertItem(item2, Location_OnLeft);
    CHECK_EQ(root->separators_recursive().size(), 1);

    root->insertItem(item3, Location_OnTop);
    CHECK_EQ(root->separators_recursive().size(), 2);
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnRight);
    CHECK_EQ(root->separators_recursive().size(), 3);

    root->removeItem(item3);
    CHECK_EQ(root->separators_recursive().size(), 2);

    root->clear();
    CHECK_EQ(root->separators_recursive().size(), 0);

    Item *item5 = createItem();
    Item *item6 = createItem();

    root->insertItem(item5, Location_OnLeft);
    CHECK_EQ(root->separators_recursive().size(), 0);
    root->insertItem(item6, Location_OnLeft, KDDockWidgets::InitialVisibilityOption::StartHidden);
    CHECK_EQ(root->separators_recursive().size(), 0);
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_separatorMinMax")
{
    auto root = createRoot();
    Item *item1 = createItem();
    Item *item2 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnLeft);
    item1->setMinSize(QSize(200, 200));
    item2->setMinSize(QSize(200, 200));

    auto separator = root->separators_recursive().at(0);
    CHECK_EQ(root->minPosForSeparator(separator), 200);
    CHECK_EQ(root->minPosForSeparator_global(separator), 200); // same, since there's no nesting

    CHECK_EQ(root->maxPosForSeparator(separator), root->width() - st - 200);
    CHECK_EQ(root->maxPosForSeparator(separator), root->width() - st - 200);
    CHECK(serializeDeserializeTest(root));
}

TEST_CASE("tst_separatorRecreatedOnParentChange")
{
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
    CHECK(root1->checkSanity());
}

TEST_CASE("tst_containerReducesSize")
{
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
    CHECK(root->checkSanity());

    item2->turnIntoPlaceholder();
    CHECK(root->checkSanity());

    item21->turnIntoPlaceholder();
    CHECK(root->checkSanity());

    item22->turnIntoPlaceholder();
    CHECK(root->checkSanity());
}

TEST_CASE("tst_insertHiddenContainer")
{
    auto root1 = createRoot();
    auto root2 = createRoot();
    Item *item2 = createItem();
    root2->insertItem(item2, Location_OnLeft, KDDockWidgets::InitialVisibilityOption::StartHidden);

    CHECK(root1->checkSanity());
    CHECK(root2->checkSanity());

    root1->insertItem(root2.release(), Location_OnTop);
    CHECK(root1->checkSanity());

    auto anotherRoot = createRoot();
    anotherRoot->insertItem(root1.release(), Location_OnTop);
    CHECK(anotherRoot->checkSanity());
}

TEST_CASE("tst_availableOnSide")
{
    // Tests that items are available to squeeze a certain amount (without violating their min-size)

    auto root = createRoot();
    Item *item1 = createItem(/*min=*/QSize(100, 100));
    root->setSize(QSize(1000, 1000));
    root->insertItem(item1, Location_OnLeft);

    CHECK_EQ(root->availableToSqueezeOnSide(item1, Side1), 0);
    CHECK_EQ(root->availableToSqueezeOnSide(item1, Side2), 0);

    Item *item2 = createItem(/*min=*/QSize(200, 200));
    root->insertItem(item2, Location_OnRight);
    auto separator = root->separators_recursive()[0];
    CHECK_EQ(root->minPosForSeparator_global(separator), item1->minSize().width());
    CHECK_EQ(root->maxPosForSeparator_global(separator),
             root->width() - item2->minSize().width() - Item::separatorThickness);

    CHECK_EQ(root->availableToSqueezeOnSide(item1, Side1), 0);
    CHECK_EQ(root->availableToSqueezeOnSide(item1, Side2),
             item2->width() - item2->minSize().width());
    CHECK_EQ(root->availableToSqueezeOnSide(item2, Side1),
             item1->width() - item1->minSize().width());
    CHECK_EQ(root->availableToSqueezeOnSide(item2, Side2), 0);

    Item *item3 = createItem(/*min=*/QSize(200, 200));
    root->insertItem(item3, Location_OnRight);
    CHECK(root->checkSanity());
    CHECK_EQ(root->availableToSqueezeOnSide(item3, Side1),
             (item1->width() - item1->minSize().width())
                 + (item2->width() - item2->minSize().width()));
    CHECK_EQ(root->availableToSqueezeOnSide(item3, Side2), 0);

    auto separator2 = root->separators_recursive()[1];
    CHECK_EQ(root->minPosForSeparator_global(separator2),
             item1->minSize().width() + item2->minSize().width() + Item::separatorThickness);
    CHECK_EQ(root->maxPosForSeparator_global(separator2),
             root->width() - item3->minSize().width() - Item::separatorThickness);

    Item *item4 = createItem(/*min=*/QSize(200, 200));
    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnBottom);

    auto c = item3->parentBoxContainer();
    CHECK_EQ(c->availableToSqueezeOnSide_recursive(item3, Side1, Qt::Horizontal),
             (item1->width() - item1->minSize().width())
                 + (item2->width() - item2->minSize().width()));
    CHECK_EQ(c->availableToSqueezeOnSide_recursive(item3, Side2, Qt::Horizontal), 0);
    CHECK_EQ(c->availableToSqueezeOnSide_recursive(item4, Side1, Qt::Horizontal),
             (item1->width() - item1->minSize().width())
                 + (item2->width() - item2->minSize().width()));
    CHECK_EQ(c->availableToSqueezeOnSide_recursive(item4, Side2, Qt::Horizontal), 0);
    CHECK_EQ(c->availableToSqueezeOnSide_recursive(item4, Side1, Qt::Vertical),
             (item3->height() - item3->minSize().height()));
    CHECK_EQ(c->availableToSqueezeOnSide_recursive(item4, Side2, Qt::Vertical), 0);

    Item *item31 = createItem(/*min=*/QSize(100, 100));
    ItemBoxContainer::insertItemRelativeTo(item31, item3, Location_OnRight);
    auto container31 = item31->parentBoxContainer();
    auto separator31 = container31->separators().at(0);

    // Since we don't have widgets with max-size, these two must be the same
    CHECK_EQ(container31->minPosForSeparator_global(separator31, false),
             container31->minPosForSeparator_global(separator31, true));

    CHECK_EQ(container31->minPosForSeparator_global(separator31),
             item1->minSize().width() + item2->minSize().width() + item3->minSize().width()
                 + 2 * Item::separatorThickness);
    CHECK_EQ(container31->maxPosForSeparator_global(separator31),
             root->width() - item31->minSize().width() - Item::separatorThickness);
}

TEST_CASE("tst_availableToGrowOnSide")
{
    // Tests that items are available to grow a certain amount (without violating their max-size)
    auto root = createRoot();
    Item *item1 = createItem(/*min=*/QSize(100, 100), /*max=*/QSize(230, 230));
    root->setSize(QSize(1000, 1000));
    root->insertItem(item1, Location_OnLeft);

    CHECK_EQ(root->availableToGrowOnSide(item1, Side1), 0);
    CHECK_EQ(root->availableToGrowOnSide(item1, Side2), 0);

    Item *item2 = createItem(/*min=*/QSize(200, 200));
    root->insertItem(item2, Location_OnRight);

    // give a resize, so item1 gets smaller than its max-size. Will be unneeded soon
    root->setSize_recursive(QSize(1001, 1001));

    CHECK_EQ(root->availableToGrowOnSide(item1, Side1), 0);
    CHECK_EQ(root->availableToGrowOnSide(item2, Side2), 0);
    CHECK_EQ(root->availableToGrowOnSide(item1, Side2), root->length() - item2->width());
    CHECK_EQ(root->availableToGrowOnSide(item2, Side1),
             item1->maxSizeHint().width() - item1->width());

    auto separator = root->separators_recursive()[0];
    CHECK_EQ(root->minPosForSeparator_global(separator, true), item1->minSize().width());
    CHECK_EQ(root->maxPosForSeparator_global(separator, true), item1->maxSizeHint().width());

    Item *item3 = createItem(/*min=*/QSize(200, 200), /*max=*/QSize(200, 200));
    root->insertItem(item3, Location_OnRight);
    CHECK(root->checkSanity());

    CHECK_EQ(root->availableToGrowOnSide(item3, Side2), 0);
    CHECK_EQ(root->availableToGrowOnSide(item3, Side1),
             root->length() - item2->width() - item1->width());
    CHECK_EQ(root->availableToGrowOnSide(item2, Side1),
             item1->maxSizeHint().width() - item1->width());
    CHECK_EQ(root->availableToGrowOnSide(item2, Side2),
             item3->maxSizeHint().width() - item3->width());
}

TEST_CASE("tst_resizeViaSeparator")
{
    auto root = createRoot();
    Item *item1 = createItem(/*min=*/QSize(100, 100));
    Item *item2 = createItem(/*min=*/QSize(100, 100));
    root->setSize(QSize(1000, 1000));
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);

    auto separator = root->separators_recursive().at(0);
    int oldPos = separator->position();
    const int delta = -50;

    root->requestSeparatorMove(separator, delta);
    CHECK_EQ(separator->position(), oldPos + delta);

    // Now move right
    oldPos = separator->position();
    root->requestSeparatorMove(separator, -delta);
    CHECK_EQ(separator->position(), oldPos - delta);


    Item *item3 = createItem(/*min=*/QSize(100, 100));
    Item *item4 = createItem(/*min=*/QSize(100, 100));
    root->insertItem(item4, Location_OnLeft);
    root->insertItem(item3, Location_OnRight);
    item2->turnIntoPlaceholder();
    item1->turnIntoPlaceholder();
    separator = root->separators_recursive().at(0);
    root->requestSeparatorMove(separator, delta);
}

TEST_CASE("tst_resizeViaSeparator2")
{
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
        for (auto item : qAsConst(children)) {
            item->m_sizingInfo.percentageWithinParent = 1.0 / numChildren;
        }
        root->setSize_recursive(QSize(4000 + Item::separatorThickness * (numChildren - 1), 1000));
    };

    const int delta = 100;
    const int originalChildWidth = 1000;
    resizeChildrenTo1000px();

    const auto separators = root->separators_recursive();
    CHECK(root->checkSanity());
    CHECK_EQ(separators.size(), 3);

    root->requestSeparatorMove(separators[1], delta);

    CHECK_EQ(item1->width(),
             originalChildWidth); // item1 didn't change when we moved the second separator, only
                                  // item2 and 3 are supposed to move
    CHECK_EQ(item2->width(), originalChildWidth + delta);
    CHECK_EQ(item3->width(), originalChildWidth - delta);
    CHECK_EQ(item4->width(), originalChildWidth);

    // And back
    root->requestSeparatorMove(separators[1], -delta);
    CHECK_EQ(item1->width(),
             originalChildWidth); // item1 didn't change when we moved the second separator, only
                                  // item2 and 3 are supposed to move
    CHECK_EQ(item2->width(), originalChildWidth);
    CHECK_EQ(item3->width(), originalChildWidth);
    CHECK_EQ(item4->width(), originalChildWidth);
}

TEST_CASE("tst_resizeViaSeparator3")
{
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
    root->setSize_recursive(QSize(1000, 4000));

    // Our horizontal separator
    const auto separators = root->separators();
    const auto horizontalSeparator = separators[0];
    CHECK_EQ(separators.size(), 1);

    const int delta = 10;
    const int oldH1 = item1->height();
    const int oldH2 = item2->height();
    const int oldH3 = item3->height();
    const int oldH4 = item4->height();

    // If the following ever fails, then make sure item4 has space before we move the separator
    CHECK(item4->availableLength(Qt::Vertical) > delta);

    // Move separator up:
    root->requestSeparatorMove(horizontalSeparator, -delta);

    CHECK_EQ(item2->height(), oldH2 + delta);
    CHECK_EQ(item3->height(), oldH3 - delta);
    CHECK_EQ(item4->height(), oldH4 - delta);
    CHECK_EQ(item1->height(), oldH1);

    // Move down again
    root->requestSeparatorMove(horizontalSeparator, delta);

    CHECK_EQ(item2->height(), oldH2);
    CHECK_EQ(item3->height(), oldH3);
    CHECK_EQ(item4->height(), oldH4);
    CHECK_EQ(item1->height(), oldH1);
}

TEST_CASE("tst_mapToRoot")
{
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
    CHECK(root->checkSanity());

    auto c = item22->parentBoxContainer();
    QPoint rootPt = c->mapToRoot(QPoint(0, 0));
    CHECK_EQ(rootPt, QPoint(0, item1->height() + st));
    CHECK_EQ(c->mapFromRoot(rootPt), QPoint(0, 0));
}

TEST_CASE("tst_closeAndRestorePreservesPosition")
{
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

    auto guest3 = item3->guestView();
    item3->turnIntoPlaceholder();

    // Test that both sides reclaimed the space equally
    CHECK_EQ(item1->width(), oldW1);
    CHECK(qAbs(item2->width() - (oldW2 + (oldW2 / 2))) < Item::separatorThickness);
    CHECK(qAbs(item4->width() - (oldW4 + (oldW4 / 2))) < Item::separatorThickness);

    item3->restore(guest3);

    CHECK_EQ(item1->width(), oldW1);
    CHECK_EQ(item2->width(), oldW2);
    CHECK_EQ(item3->width(), oldW3);
    CHECK_EQ(item4->width(), oldW4);
}

TEST_CASE("tst_minSizeChangedBeforeRestore")
{
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();

    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);
    const QSize originalSize2 = item2->size();

    auto guest2 = item2->guestView();
    const QSize newMinSize = originalSize2 + QSize(10, 10);

    item2->turnIntoPlaceholder();
    guest2->setMinimumSize(newMinSize);
    item2->restore(guest2);
}

TEST_CASE("tst_separatorMoveCrash")
{
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

TEST_CASE("tst_separatorMoveHonoursMax")
{
    const int maxWidth = 250;
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem({}, QSize(maxWidth, 250));
    auto item3 = createItem();
    root->insertItem(item1, Location_OnLeft);
    root->insertItem(item2, Location_OnRight);
    root->insertItem(item3, Location_OnRight);
    CHECK(root->checkSanity());

    auto separator1 = root->separators()[0];
    auto separator2 = root->separators()[1];

    const int min1 = root->minPosForSeparator_global(separator1);
    const int max1 = root->maxPosForSeparator_global(separator1);
    // const int min2 = root->minPosForSeparator_global(separator2);
    const int max2 = root->maxPosForSeparator_global(separator2);

    CHECK_EQ(min1, item1->minSize().width());

    root->requestSeparatorMove(separator1, -(separator1->position() - min1));
    CHECK(item2->width() <= maxWidth);
    CHECK(root->checkSanity());

    root->requestSeparatorMove(separator2, max2 - separator2->position());
    CHECK(root->checkSanity());
    CHECK(item2->width() <= maxWidth);

    root->requestSeparatorMove(separator1, max1 - separator1->position());
    CHECK(root->checkSanity());
    CHECK(item2->width() <= maxWidth);

    root->requestSeparatorMove(separator1, -(separator1->position() - min1));
    CHECK(root->checkSanity());
    CHECK(item2->width() <= maxWidth);
}

TEST_CASE("tst_maxSizeHonoured1")
{
    // Tests that the suggested rect honors max size when adding an item to a layout.

    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    root->insertItem(item1, Location_OnTop);
    root->setSize_recursive(QSize(3000, 3000));

    auto guest2 = item2->guestView();
    const int maxHeight = 250;
    CHECK_EQ(guest2->size(), item2->size());
    guest2->setMaximumSize(QSize(250, maxHeight));
    CHECK_EQ(guest2->size(), item2->size());
    CHECK_EQ(item2->maxSizeHint(), guest2->maxSizeHint());

    root->insertItem(item2, Location_OnBottom);
    CHECK_EQ(item2->height(), maxHeight);
}

TEST_CASE("tst_maxSizeHonoured2")
{
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

    item2->setMaxSizeHint(QSize(200, 200));

    root1->insertItem(root2.release(), Location_OnBottom);
    CHECK_EQ(item2->parentBoxContainer()->maxSizeHint(), item2->maxSizeHint());
}

TEST_CASE("tst_maxSizeHonoured3")
{
    {
        // Tests that resizing a window will now make the item with max-size grow past its max
        auto root = createRoot();
        const int minHeight = 100;
        const int maxHeight = 200;
        auto item1 = createItem(QSize(100, minHeight), QSize(200, maxHeight));
        auto item2 = createItem();
        root->setSize(QSize(2000, 2000));

        root->insertItem(item2, Location_OnBottom);
        root->insertItem(item1, Location_OnTop);

        // When adding, we respect max-size
        CHECK(item1->height() <= maxHeight);
        CHECK(item1->height() >= minHeight);

        // Now resize the window
        root->setSize_recursive(QSize(200, 8000));

        // and we respected max-size too
        CHECK(item1->height() <= maxHeight);
        CHECK(item1->height() >= minHeight);
    }

    {
        // Also do it with nested containers
        auto root1 = createRoot();
        auto root2 = createRoot();
        const int minHeight = 100;
        const int maxHeight = 200;
        auto item1 = createItem(QSize(100, minHeight), QSize(200, maxHeight));
        auto item2 = createItem();
        root1->setSize(QSize(2000, 2000));
        root2->setSize(QSize(2000, 2000));

        root2->insertItem(item2, Location_OnBottom);
        root1->insertItem(item1, Location_OnTop);
        root2->insertItem(root1.release(), Location_OnTop);

        // When adding, we respect max-size
        CHECK(item1->height() <= maxHeight);
        CHECK(item1->height() >= minHeight);

        // Now resize the window
        root2->setSize_recursive(QSize(200, 8000));

        // and we respected max-size too
        CHECK(item1->height() <= maxHeight);
        CHECK(item1->height() >= minHeight);
    }
}

TEST_CASE("tst_requestEqualSize")
{
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

        CHECK_EQ(item1->width(), item1->minSize().width());
        CHECK_EQ(item2->width(), root->length() - st - item1->width());

        root->requestEqualSize(separator);
        CHECK(qAbs(item1->width() - item2->width()) < 5);
    }

    {
        // Similar, but now we have max-size to honour too
        auto root = createRoot();
        const int minWidth1 = 100;
        const int maxWidth1 = 200;
        auto item1 = createItem(QSize(minWidth1, 100), QSize(maxWidth1, 200));
        auto item2 = createItem();
        root->insertItem(item2, Location_OnRight);
        root->insertItem(item1, Location_OnLeft);

        CHECK_EQ(item1->width(), item1->maxSizeHint().width());
        auto separator = root->separators().constFirst();
        root->requestEqualSize(separator);
        // Separator didn't move, doing so would make item1 bigger than its max size
        CHECK_EQ(item1->width(), item1->maxSizeHint().width());

        {
            // Let's put the separator further right manually, then try again:
            // (Can't use ItemBoxContainer::requstSeparatorMove() as it respects max-size
            // constraints
            item1->m_sizingInfo.incrementLength(20, Qt::Horizontal);
            item2->m_sizingInfo.incrementLength(-20, Qt::Horizontal);
            root->positionItems();
        }


        CHECK_EQ(item1->width(), maxWidth1 + 20);

        // Double clicking on the separator will put it back at a sane place

        const int minPos = root->minPosForSeparator_global(separator, true);
        const int maxPos = root->maxPosForSeparator_global(separator, true);

        CHECK_EQ(minPos, minWidth1);
        CHECK_EQ(maxPos, maxWidth1);

        root->requestEqualSize(separator);
        CHECK_EQ(item1->width(), maxWidth1);
    }
}

TEST_CASE("tst_maxSizeHonouredWhenAnotherRemoved")
{
    // Test that when removing item 3 that all the new available space goes to item1, so that
    // we don't violate the space of item 1

    auto root = createRoot();
    root->setSize(QSize(300, 3000));
    auto item1 = createItem();
    const int minHeight = 100;
    const int maxHeight = 200;
    auto item2 = createItem(QSize(100, minHeight), QSize(200, maxHeight));
    auto item3 = createItem();
    root->insertItem(item1, Location_OnTop);
    root->insertItem(item2, Location_OnBottom);
    root->insertItem(item3, Location_OnBottom);

    CHECK(item2->height() <= maxHeight);
    root->removeItem(item3);
    CHECK(item2->height() <= maxHeight);

    root->dumpLayout();
}

TEST_CASE("tst_simplify")
{
    QScopedValueRollback<bool> inhibitSimplify(ItemBoxContainer::s_inhibitSimplify, true);

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

    CHECK(root->childItems().at(2)->isContainer());

    root->simplify();

    for (Item *item : root->childItems()) {
        CHECK(!item->isContainer());
    }
}

TEST_CASE("tst_adjacentLayoutBorders")
{
    auto root = createRoot();
    auto item1 = createItem();
    auto item2 = createItem();
    auto item3 = createItem();
    auto item4 = createItem();
    auto item5 = createItem();

    root->insertItem(item1, Location_OnTop);
    const int allBorders = int(LayoutBorderLocation_All);

    auto borders1 = item1->adjacentLayoutBorders();
    CHECK_EQ(borders1, allBorders);
    root->insertItem(item2, Location_OnBottom);

    borders1 = item1->adjacentLayoutBorders();
    CHECK_EQ(borders1, allBorders & ~LayoutBorderLocation_South);

    auto borders2 = item2->adjacentLayoutBorders();
    CHECK_EQ(borders2, allBorders & ~LayoutBorderLocation_North);

    root->insertItem(item3, Location_OnRight);

    borders1 = item1->adjacentLayoutBorders();
    CHECK_EQ(borders1, LayoutBorderLocation_North | LayoutBorderLocation_West);

    borders2 = item2->adjacentLayoutBorders();
    CHECK_EQ(borders2, LayoutBorderLocation_South | LayoutBorderLocation_West);

    auto borders3 = item3->adjacentLayoutBorders();
    CHECK_EQ(borders3, allBorders & ~(LayoutBorderLocation_West));

    ItemBoxContainer::insertItemRelativeTo(item4, item3, Location_OnBottom);
    auto borders4 = item4->adjacentLayoutBorders();
    CHECK_EQ(borders4, LayoutBorderLocation_East | LayoutBorderLocation_South);

    root->insertItem(item5, Location_OnRight);
    borders4 = item4->adjacentLayoutBorders();
    CHECK_EQ(borders4, LayoutBorderLocation_South);
}

TEST_CASE("tst_numSideBySide_recursive")
{
    auto root = createRoot();
    CHECK(root->isVertical());
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 0);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 0);

    auto item1 = createItem();
    root->insertItem(item1, Location_OnRight);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 1);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 1);


    auto item2 = createItem();
    root->insertItem(item2, Location_OnTop);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 2);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 1);

    auto item3 = createItem();
    root->insertItem(item3, Location_OnTop);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 3);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 1);

    auto item1Child = createItem();
    ItemBoxContainer::insertItemRelativeTo(item1Child, item1, Location_OnLeft);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 3);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 2);

    auto item1Child1Child = createItem();
    ItemBoxContainer::insertItemRelativeTo(item1Child1Child, item1Child, Location_OnBottom);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 4);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 2);

    item2->turnIntoPlaceholder();
    CHECK_EQ(root->numSideBySide_recursive(Qt::Vertical), 3);
    CHECK_EQ(root->numSideBySide_recursive(Qt::Horizontal), 2);
}
