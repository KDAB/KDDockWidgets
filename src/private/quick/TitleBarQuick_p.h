/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_TITLEBARQUICK_P_H
#define KD_TITLEBARQUICK_P_H

#include "../docks_export.h"
#include "../TitleBar_p.h"

namespace KDDockWidgets {

class DockWidget;
class Frame;

class DOCKS_EXPORT TitleBarQuick : public TitleBar
{
    Q_OBJECT
    // This property is just for the unit-tests
    Q_PROPERTY(QQuickItem* titleBarQmlItem READ titleBarQmlItem WRITE setTitleBarQmlItem NOTIFY titleBarQmlItemChanged)
public:
    explicit TitleBarQuick(Frame *parent);
    explicit TitleBarQuick(FloatingWindow *parent);
    ~TitleBarQuick() override;

protected:

    Q_INVOKABLE void filterEvents(QObject *);
    bool eventFilter(QObject *, QEvent *) override;

    // These 4 just for unit-tests
    bool isCloseButtonEnabled() const override;
    bool isCloseButtonVisible() const override;
    bool isFloatButtonEnabled() const override;
    bool isFloatButtonVisible() const override;

    /*void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
*/

    QQuickItem *titleBarQmlItem() const;
    void setTitleBarQmlItem(QQuickItem *);

Q_SIGNALS:
    void titleBarQmlItemChanged();

private:
    QQuickItem *floatButton() const;
    QQuickItem *closeButton() const;

    bool m_eventFilterInstalled = false;
    QPointer<QQuickItem> m_titleBarQmlItem;
};

}

#endif
