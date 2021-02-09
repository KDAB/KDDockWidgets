/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2021 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "Config.h"
#include "DockWidgetBase_p.h"
#include "FloatingWindow_p.h"
#include "FrameworkWidgetFactory.h"
#include "LayoutWidget_p.h"
#include "MainWindowBase.h"
#include "Position_p.h"

using namespace KDDockWidgets;


LayoutWidget::LayoutWidget(QWidgetOrQuick *parent)
    : LayoutGuestWidget(parent)
{
}

LayoutWidget::~LayoutWidget()
{
}

bool LayoutWidget::isInMainWindow() const
{
    return mainWindow() != nullptr;
}

MainWindowBase *LayoutWidget::mainWindow() const
{
    if (auto pw = QWidgetAdapter::parentWidget()) {
        // Note that if pw is a FloatingWindow then pw->parentWidget() can be a MainWindow too, as
        // it's parented
        if (pw->objectName() == QLatin1String("MyCentralWidget"))
            return qobject_cast<MainWindowBase *>(pw->parentWidget());

        if (auto mw = qobject_cast<MainWindowBase *>(pw))
            return mw;
    }

    return nullptr;
}

FloatingWindow *LayoutWidget::floatingWindow() const
{
    return qobject_cast<FloatingWindow *>(QWidgetAdapter::parentWidget());
}

void LayoutWidget::setRootItem(Layouting::ItemContainer *root)
{
    delete m_rootItem;
    m_rootItem = root;
    connect(m_rootItem, &Layouting::ItemContainer::numVisibleItemsChanged, this,
            &MultiSplitter::visibleWidgetCountChanged);
    connect(m_rootItem, &Layouting::ItemContainer::minSizeChanged, this,
            [this] { setMinimumSize(layoutMinimumSize()); });
}

QSize LayoutWidget::layoutMinimumSize() const
{
    return m_rootItem->minSize();
}

QSize LayoutWidget::layoutMaximumSizeHint() const
{
    return m_rootItem->maxSizeHint();
}

void LayoutWidget::setLayoutMinimumSize(QSize sz)
{
    if (sz != m_rootItem->minSize()) {
        setLayoutSize(size().expandedTo(m_rootItem->minSize())); // Increase size in case we need to
        m_rootItem->setMinSize(sz);
    }
}

QSize LayoutWidget::size() const
{
    return m_rootItem->size();
}

void LayoutWidget::clearLayout()
{
    m_rootItem->clear();
}

bool LayoutWidget::checkSanity() const
{
    return m_rootItem->checkSanity();
}

void LayoutWidget::dumpLayout() const
{
    m_rootItem->dumpLayout();
}

void LayoutWidget::restorePlaceholder(DockWidgetBase *dw, Layouting::Item *item, int tabIndex)
{
    if (item->isPlaceholder()) {
        Frame *newFrame = Config::self().frameworkWidgetFactory()->createFrame(this);
        item->restore(newFrame);
    }

    auto frame = qobject_cast<Frame *>(item->guestAsQObject());
    Q_ASSERT(frame);

    if (tabIndex != -1 && frame->dockWidgetCount() >= tabIndex) {
        frame->insertWidget(dw, tabIndex);
    } else {
        frame->addWidget(dw);
    }

    frame->QWidgetAdapter::setVisible(true);
}

void LayoutWidget::unrefOldPlaceholders(const Frame::List &framesBeingAdded) const
{
    for (Frame *frame : framesBeingAdded) {
        for (DockWidgetBase *dw : frame->dockWidgets()) {
            dw->d->lastPositions().removePlaceholders(this);
        }
    }
}

void LayoutWidget::setLayoutSize(QSize size)
{
    if (size != this->size()) {
        m_rootItem->setSize_recursive(size);
        if (!m_inResizeEvent && !LayoutSaver::restoreInProgress())
            resize(size);
    }
}
