/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "DockWidgetInstantiator.h"
#include "kddockwidgets/core/DockRegistry.h"
#include "core/DockWidget_p.h"
#include "ViewFactory.h"
#include "Config.h"
#include "Platform.h"

using namespace KDDockWidgets;
using namespace KDDockWidgets::QtQuick;

QString DockWidgetInstantiator::uniqueName() const
{
    return m_uniqueName;
}

void DockWidgetInstantiator::setUniqueName(const QString &name)
{
    m_uniqueName = name;
    Q_EMIT uniqueNameChanged();
}

QString DockWidgetInstantiator::source() const
{
    return m_sourceFilename;
}

void DockWidgetInstantiator::setSource(const QString &source)
{
    m_sourceFilename = source;
    Q_EMIT sourceChanged();
}

QtQuick::DockWidget *DockWidgetInstantiator::dockWidget() const
{
    if (m_dockWidget) {
        return static_cast<QtQuick::DockWidget *>(m_dockWidget->view());
    }

    return nullptr;
}

KDDockWidgets::Core::DockWidget *DockWidgetInstantiator::controller() const
{
    return m_dockWidget;
}

QObject *DockWidgetInstantiator::actualTitleBar() const
{
    if (auto dockView = dockWidget()) {
        return dockView->actualTitleBarView();
    }

    return nullptr;
}

QString DockWidgetInstantiator::title() const
{
    return m_dockWidget ? m_dockWidget->title() : QString();
}

void DockWidgetInstantiator::setTitle(const QString &title)
{
    if (m_dockWidget)
        m_dockWidget->setTitle(title);
    m_title = title;
}

bool DockWidgetInstantiator::isFocused() const
{
    return m_dockWidget && m_dockWidget->isFocused();
}

bool DockWidgetInstantiator::isFloating() const
{
    return m_dockWidget && m_dockWidget->isFloating();
}

bool DockWidgetInstantiator::isOpen() const
{
    return m_dockWidget && m_dockWidget->isOpen();
}

void DockWidgetInstantiator::setFloating(bool is)
{
    if (m_dockWidget)
        m_dockWidget->setFloating(is);
    m_isFloating = is;
}

void DockWidgetInstantiator::addDockWidgetAsTab(QQuickItem *other, InitialVisibilityOption option)
{
    if (!other || !m_dockWidget)
        return;

    Core::DockWidget *otherDockWidget = Platform::dockWidgetForItem(other);
    m_dockWidget->addDockWidgetAsTab(otherDockWidget, option);
}

void DockWidgetInstantiator::addDockWidgetToContainingWindow(QQuickItem *other, Location location,
                                                             QQuickItem *relativeTo,
                                                             QSize initialSize,
                                                             InitialVisibilityOption option)
{
    if (!other || !m_dockWidget)
        return;

    Core::DockWidget *otherDockWidget = Platform::dockWidgetForItem(other);
    Core::DockWidget *relativeToDockWidget = Platform::dockWidgetForItem(relativeTo);

    m_dockWidget->addDockWidgetToContainingWindow(otherDockWidget, location, relativeToDockWidget,
                                                  InitialOption(option, initialSize));
}

void DockWidgetInstantiator::setAsCurrentTab()
{
    if (m_dockWidget)
        m_dockWidget->setAsCurrentTab();
}

void DockWidgetInstantiator::forceClose()
{
    if (m_dockWidget)
        m_dockWidget->forceClose();
}

Q_INVOKABLE bool DockWidgetInstantiator::close()
{
    if (m_dockWidget)
        return m_dockWidget->close();

    return false;
}

void DockWidgetInstantiator::open()
{
    if (m_dockWidget)
        m_dockWidget->open();
}

void DockWidgetInstantiator::show()
{
    // "show" is deprecated vocabulary
    open();
}

void DockWidgetInstantiator::raise()
{
    if (m_dockWidget)
        m_dockWidget->raise();
}

void DockWidgetInstantiator::moveToSideBar()
{
    if (m_dockWidget)
        m_dockWidget->moveToSideBar();
}

void DockWidgetInstantiator::classBegin()
{
    // Nothing interesting to do here.
}

void DockWidgetInstantiator::componentComplete()
{
    if (m_uniqueName.isEmpty()) {
        qWarning() << Q_FUNC_INFO
                   << "Each DockWidget need an unique name. Set the uniqueName property.";
        return;
    }

    if (DockRegistry::self()->containsDockWidget(m_uniqueName)) {
        // Dock widget already exists. all good.
        return;
    }

    if (m_dockWidget) {
        qWarning() << Q_FUNC_INFO << "Unexpected bug.";
        return;
    }
    const auto childItems = this->childItems();
    if (m_sourceFilename.isEmpty() && childItems.size() != 1) {
        qWarning() << Q_FUNC_INFO << "Either 'source' property must be set or add exactly one child"
                   << "; source=" << m_sourceFilename << "; num children=" << childItems.size();
        return;
    }

    m_dockWidget = ViewFactory::self()
                       ->createDockWidget(m_uniqueName, qmlEngine(this))
                       ->asDockWidgetController();

    m_dockWidget->d->titleChanged.connect([this](const QString &title) { Q_EMIT titleChanged(title); });
    m_dockWidget->d->closed.connect([this] { Q_EMIT closed(); });
    m_dockWidget->d->iconChanged.connect([this] { Q_EMIT iconChanged(); });
    m_dockWidget->d->actualTitleBarChanged.connect([this] { Q_EMIT actualTitleBarChanged(); });
    m_dockWidget->d->optionsChanged.connect([this](KDDockWidgets::DockWidgetOptions opts) { Q_EMIT optionsChanged(opts); });

    m_dockWidget->d->windowActiveAboutToChange.connect([this](bool is) { Q_EMIT windowActiveAboutToChange(is); });
    m_dockWidget->d->isFocusedChanged.connect([this](bool is) { Q_EMIT isFocusedChanged(is); });

    m_dockWidget->d->isOverlayedChanged.connect([this](bool is) { Q_EMIT isOverlayedChanged(is); });
    m_dockWidget->d->isFloatingChanged.connect([this](bool is) { Q_EMIT isFloatingChanged(is); });
    m_dockWidget->d->isOpenChanged.connect([this](bool is) { Q_EMIT isOpenChanged(is); });

    m_dockWidget->d->guestViewChanged.connect([this] { Q_EMIT guestViewChanged(QtQuick::asQQuickItem(m_dockWidget->guestView().get())); });
    m_dockWidget->d->removedFromSideBar.connect([this] { Q_EMIT removedFromSideBar(); });

    if (m_sourceFilename.isEmpty()) {
        m_dockWidget->setGuestView(QtQuick::View::asQQuickWrapper(childItems.constFirst()));
    } else {
        auto view = this->dockWidget();
        view->setGuestItem(m_sourceFilename);
    }

    if (!m_title.isEmpty())
        m_dockWidget->setTitle(m_title);

    if (m_isFloating.has_value())
        m_dockWidget->setFloating(m_isFloating.value());

    Q_EMIT dockWidgetChanged();
}
