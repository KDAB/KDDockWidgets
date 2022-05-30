/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief Represents a dock widget.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KD_DOCKWIDGET_QUICK_H
#define KD_DOCKWIDGET_QUICK_H

#include "controllers/DockWidget.h"
#include "View_qtquick.h"

QT_BEGIN_NAMESPACE
class QCloseEvent;
class QQmlEngine;
QT_END_NAMESPACE

namespace KDDockWidgets {

namespace Controllers {
class Frame;
class TitleBar;
}

namespace Views {
/**
 * @brief Represents a dock widget.
 *
 * Most of the interface lives in Controllers::DockWidget, to facilitate sharing with QtQuick.
 */
class DOCKS_EXPORT DockWidget_qtquick : public Views::View_qtquick
{
    Q_OBJECT
    Q_PROPERTY(QObject *actualTitleBar READ actualTitleBarView NOTIFY actualTitleBarChanged)
public:
    /**
     * @brief constructs a new DockWidget
     * @param uniqueName the name of the dockwidget, should be unique. Use title for user visible text.
     * @param options optional options controlling behaviour
     * @param layoutSaverOptions options regarding LayoutSaver behaviour
     * @param engine the QML engine this dock widget will be created on. If not specified then
     * Config::self().qmlEngine() will be used
     *
     * There's no parent argument. The DockWidget is either parented to FloatingWindow or MainWindow
     * when visible, or stays without a parent when hidden.
     */
    explicit DockWidget_qtquick(const QString &uniqueName,
                                Controllers::DockWidget::Options = {},
                                Controllers::DockWidget::LayoutSaverOptions = {},
                                Qt::WindowFlags = Qt::Tool,
                                QQmlEngine *engine = nullptr);

    ///@brief destructor
    ~DockWidget_qtquick() override;

    /// Sets the DockWidget's guest item
    /// Similar to Controllers::DockWidget::setWidget(QQuickItem*)
    void setWidget(const QString &qmlFilename);

    void init() override;

    /// @reimp // TODOv2: Rename to setGuestView
    Q_INVOKABLE void setWidget(QQuickItem *widget);

    /// @reimp
    QSize minSize() const override;

    /// @reimp
    QSize maximumSize() const override;

    /// @brief Returns the title bar
    Controllers::TitleBar *actualTitleBar() const;

    /// @brief Returns the title bar
    /// Qt6 requires us to include TitleBar_p.h, so instead the Q_PROPERTY uses
    /// QObject so we don't include private headers in public headers
    QObject *actualTitleBarView() const;

    /// @brief Returns the visual item which represents Frame in the screen
    /// Equivalent to Frame::visualItem().
    QQuickItem *frameVisualItem() const;

    Controllers::DockWidget *dockWidget() const;

    ///@internal
    Q_INVOKABLE KDDockWidgets::Controllers::Frame *frame() const;

    /// @brief Called by QtQuick when min-size changes
    Q_INVOKABLE void onGeometryUpdated();

Q_SIGNALS:
    /// @brief The geometry of the frame container this dock widget is in changed
    /// For example, when dragging a dockwidget
    void frameGeometryChanged(QRect);
    void actualTitleBarChanged();

protected:
    bool event(QEvent *e) override;

private:
    class Private;
    Private *const d;
};

}
}

#endif
