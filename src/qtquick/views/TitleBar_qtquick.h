/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_TITLEBARQUICK_P_H
#define KD_TITLEBARQUICK_P_H
#pragma once

#include "kddockwidgets/docks_export.h"
#include "views/TitleBarViewInterface.h"
#include "View_qtquick.h"

namespace KDDockWidgets {


namespace Controllers {
class TitleBar;
}

namespace Views {

class DOCKS_EXPORT TitleBar_qtquick : public View_qtquick, public Views::TitleBarViewInterface
{
    Q_OBJECT
    // These properties is just for the unit-tests
    Q_PROPERTY(QQuickItem *titleBarQmlItem READ titleBarQmlItem WRITE setTitleBarQmlItem NOTIFY
                   titleBarQmlItemChanged)
    Q_PROPERTY(QQuickItem *titleBarMouseArea READ titleBarMouseArea CONSTANT)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(bool hasIcon READ hasIcon NOTIFY iconChanged)
    Q_PROPERTY(bool closeButtonEnabled READ closeButtonEnabled WRITE setCloseButtonEnabled NOTIFY
                   closeButtonEnabledChanged)
    Q_PROPERTY(bool floatButtonVisible READ floatButtonVisible WRITE setFloatButtonVisible NOTIFY
                   floatButtonVisibleChanged)
    Q_PROPERTY(QString floatButtonToolTip READ floatButtonToolTip NOTIFY floatButtonToolTipChanged)
    Q_PROPERTY(bool isFocused READ isFocused NOTIFY isFocusedChanged)

public:
    explicit TitleBar_qtquick(Controllers::TitleBar *controller, QQuickItem *parent = nullptr);
    ~TitleBar_qtquick() override;

protected:
#ifdef DOCKS_DEVELOPER_MODE
    // These 3 just for unit-tests
    bool isCloseButtonEnabled() const override;
    bool isCloseButtonVisible() const override;
    bool isFloatButtonVisible() const override;
#endif

    QQuickItem *titleBarQmlItem() const;
    QQuickItem *titleBarMouseArea() const;
    void setTitleBarQmlItem(QQuickItem *);

    // QML interface
    bool isFocused() const;
    bool floatButtonVisible() const;
    bool closeButtonEnabled() const;
    QString floatButtonToolTip() const;
    bool hasIcon() const;
    QString title() const;
    void setCloseButtonEnabled(bool);
    void setFloatButtonVisible(bool);

    Q_INVOKABLE bool onDoubleClicked();
    Q_INVOKABLE void onCloseClicked();
    Q_INVOKABLE void onFloatClicked();
    Q_INVOKABLE void onMaximizeClicked();
    Q_INVOKABLE void onMinimizeClicked();
    Q_INVOKABLE void onAutoHideClicked();
    Q_INVOKABLE void toggleMaximized();

Q_SIGNALS:
    void titleBarQmlItemChanged();
    void titleChanged();
    void iconChanged();
    void isFocusedChanged();
    void closeButtonEnabledChanged(bool);
    void floatButtonVisibleChanged(bool);
    void floatButtonToolTipChanged(const QString &);

protected:
    void init() override;

private:
    QQuickItem *floatButton() const;
    QQuickItem *closeButton() const;

    QPointer<QQuickItem> m_titleBarQmlItem;
};

}

}

#endif
