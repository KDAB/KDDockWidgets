/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KDDOCKWIDGETS_ViewFactory_QTWIDGETS_H
#define KDDOCKWIDGETS_ViewFactory_QTWIDGETS_H

#include "kddockwidgets/ViewFactory.h"

#include <QMap>

#include <utility>

// clazy:excludeall=ctor-missing-parent-argument

/**
 * @file
 * @brief A factory class for allowing the user to customize some internal widgets.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

QT_BEGIN_NAMESPACE
class QAbstractButton;
QT_END_NAMESPACE


namespace KDDockWidgets {

class DropIndicatorOverlay;

namespace Core {
class DropArea;
class Separator;
class TabBar;
class SideBar;
class FloatingWindow;
class MainWindow;
}

namespace qtwidgets {

/**
 * @brief The default ViewFactory for QtWidgets frontend.
 */
class DOCKS_EXPORT ViewFactory : public Core::ViewFactory
{
    Q_OBJECT
public:
    ViewFactory() = default;
    ~ViewFactory() override;

    View *createDockWidget(const QString &uniqueName, DockWidgetOptions = {},
                           LayoutSaverOptions = {}, Qt::WindowFlags = {}) const override;

    View *createGroup(Core::Group *, View *parent) const override;
    View *createTitleBar(Core::TitleBar *, View *parent) const override;
    View *createStack(Core::Stack *, View *parent) const override;
    View *createTabBar(Core::TabBar *tabBar, View *parent) const override;
    View *createSeparator(Core::Separator *, View *parent = nullptr) const override;
    View *createFloatingWindow(Core::FloatingWindow *,
                               Core::MainWindow *parent = nullptr,
                               Qt::WindowFlags windowFlags = {}) const override;
    View *createRubberBand(View *parent) const override;
    View *createSideBar(Core::SideBar *, View *parent) const override;
    View *createDropArea(Core::DropArea *, View *parent) const override;
    View *createMDILayout(Core::MDILayout *, View *parent) const override;
    QIcon iconForButtonType(TitleBarButtonType type, qreal dpr) const override;
    void clearIconCache();
    QAbstractButton *createTitleBarButton(QWidget *parent, TitleBarButtonType) const;

    Views::ClassicIndicatorWindowViewInterface *
    createClassicIndicatorWindow(Core::ClassicIndicators *) const override;
    View *createSegmentedDropIndicatorOverlayView(Core::SegmentedIndicators *controller,
                                                  View *parent = nullptr) const override;

private:
    Q_DISABLE_COPY(ViewFactory)
    mutable QMap<std::pair<TitleBarButtonType, qreal>, QIcon> m_cachedIcons;
};

}

}

#endif
