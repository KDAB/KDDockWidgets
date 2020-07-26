/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

/**
 * @file
 * @brief A class that is QWidget when building for QtWidgets, and QObject when building for QtQuick.
 *
 * Allows to have the same code base supporting both stacks.
 *
 * @author Sérgio Martins \<sergio.martins@kdab.com\>
 */

#ifndef KDDOCKWIDGETS_QWIDGETADAPTERQUICK_P_H
#define KDDOCKWIDGETS_QWIDGETADAPTERQUICK_P_H

#include "docks_export.h"

#include <QQuickItem>
#include <QObject>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
class QWindow;
QT_END_NAMESPACE

namespace KDDockWidgets {

class FloatingWindow;
/*
class QuickItem : public QQuickItem
{
public:
    explicit QuickItem(QQuickItem *parent)
        : QQuickItem(parent)
    {
    }
    ~QuickItem() override;

    QRect geometry() const { return {}; }
    void setGeometry(QRect) {}

    void releaseMouse()
    {
        ungrabMouse();
    }
};
QuickItem::~QuickItem() {}
*/

class DOCKS_EXPORT QWidgetAdapter : public QQuickItem
{
    Q_OBJECT
public:
    explicit QWidgetAdapter(QQuickItem *parent = nullptr, Qt::WindowFlags f = {});
    ~QWidgetAdapter() override;

    ///@brief returns the FloatingWindow this widget is in, otherwise nullptr
    FloatingWindow *floatingWindow() const;

    void setFlag(Qt::WindowType, bool on = true);

    int x() const { return int(QQuickItem::x()); }
    int y() const { return int(QQuickItem::y()); }
    int width() const { return int(QQuickItem::width()); }
    int height() const { return int(QQuickItem::height()); }

    void setGeometry(QRect);
    QRect geometry() const;
    QRect rect() const;
    void show();
    void setEnabled(bool) {}
    void setFixedHeight(int);
    void setFixedWidth(int);
    void raise();
    void update() {}

    QSize size() const { return QQuickItem::size().toSize(); }
    QSize minimumSizeHint() const { return m_minimumSize; }
    QSize minimumSize() const { return m_minimumSize; }
    QSize maximumize() const { return m_maximumSize; }
    int minimumHeight() const { return m_minimumSize.height(); }
    int minimumWidth() const { return m_minimumSize.width(); }

    void grabMouse();
    void releaseMouse();
    void setMinimumSize(QSize);
    void resize(QSize);
    bool isWindow() const { return false; }
    bool isMaximized() const;
    void showMaximized();
    void showNormal();

    QWindow *windowHandle() const;
    QWidgetAdapter *window() const { return nullptr; }
    QWidgetAdapter *parentWidget() const { return nullptr; }
    QPoint mapToGlobal(QPoint) const { return {}; }
    QPoint mapFromGlobal(QPoint) const { return {}; }
    bool testAttribute(Qt::WidgetAttribute) { return false; }

    void setWindowTitle(const QString &) {}
    void setWindowIcon(const QIcon &) {}
    void close() {}
    QWidgetAdapter* childAt(QPoint) { return nullptr; }
    void move(int x, int y);

    void setParent(QQuickItem*);
    void activateWindow();
    void setSizePolicy(QSizePolicy);

protected:
    void raiseAndActivate();

    virtual bool onResize(QSize newSize);
    virtual void onLayoutRequest();
    virtual void onMousePress();
    virtual void onMouseMove(QPoint globalPos);
    virtual void onMouseRelease();
    virtual void onCloseEvent(QCloseEvent *);
private:
    QSize m_minimumSize = {0, 0};
    QSize m_maximumSize = {0, 0};
};

}

#endif
