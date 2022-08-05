/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#include "kddockwidgets/views/DockWidgetViewInterface.h"
#include "View_flutter.h"

namespace KDDockWidgets {

namespace Controllers {
class Group;
class TitleBar;
}

namespace Views {
/**
 * @brief Represents a dock widget.
 *
 * Most of the interface lives in Controllers::DockWidget, to facilitate sharing with QtQuick.
 */
class DOCKS_EXPORT DockWidget_flutter : public Views::View_flutter,
                                        public Views::DockWidgetViewInterface
{
public:
    using Views::DockWidgetViewInterface::raise;
    using Views::DockWidgetViewInterface::show;

    /**
     * @brief constructs a new DockWidget
     * @param uniqueName the name of the dockwidget, should be unique. Use title for user visible
     * text.
     * @param options optional options controlling behaviour
     * @param layoutSaverOptions options regarding LayoutSaver behaviour
     * @param engine the QML engine this dock widget will be created on. If not specified then
     * Config::self().qmlEngine() will be used
     *
     * There's no parent argument. The DockWidget is either parented to FloatingWindow or MainWindow
     * when visible, or stays without a parent when hidden.
     */
    explicit DockWidget_flutter(const QString &uniqueName, DockWidgetOptions = {},
                                LayoutSaverOptions = {}, Qt::WindowFlags = Qt::Tool);

    ///@brief destructor
    ~DockWidget_flutter() override;

    /// @reimp
    QSize minSize() const override;

    /// @reimp
    QSize maximumSize() const override;

protected:
    void init() override;
};

}
}
