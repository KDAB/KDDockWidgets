/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_qtwidgets.h"
#include "../Window_qtwidgets.h"
#include "private/View_p.h"
#include "ViewWrapper_qtwidgets.h"

#include <QTabBar>
#include <QTabWidget>
#include <QMainWindow>
#include <QRubberBand>
#include <QLineEdit>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;

template<>
View_qtwidgets<QWidget>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags windowFlags)
    : QWidget(parent, windowFlags)
    , View_qt(controller, type, this)
{
}

template<>
View_qtwidgets<QTabBar>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QTabBar(parent)
    , View_qt(controller, type, this)
{
}

template<>
View_qtwidgets<QTabWidget>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QTabWidget(parent)
    , View_qt(controller, type, this)
{
}

template<>
View_qtwidgets<QMainWindow>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QMainWindow(parent)
    , View_qt(controller, type, this)
{
}

template<>
View_qtwidgets<QRubberBand>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QRubberBand(QRubberBand::Rectangle, parent)
    , View_qt(controller, type, this)
{
}

template<>
View_qtwidgets<QLineEdit>::View_qtwidgets(KDDockWidgets::Controller *controller, Type type, QWidget *parent, Qt::WindowFlags)
    : QLineEdit(parent)
    , View_qt(controller, type, this)
{
}

template<class T>
std::shared_ptr<Window> View_qtwidgets<T>::window() const
{
    if (QWidget *root = QWidget::window()) {
        if (root->window()) {
            return std::shared_ptr<Window>(new Window_qtwidgets(root));
        }
    }

    return {};
}

template<class T>
void View_qtwidgets<T>::setMaximumSize(QSize sz)
{
    if (sz != QWidget::maximumSize()) {
        T::setMaximumSize(sz);
        d->layoutInvalidated.emit();
    }
}

template<class T>
bool View_qtwidgets<T>::event(QEvent *e)
{
    if (e->type() == QEvent::LayoutRequest)
        d->layoutInvalidated.emit();

    return T::event(e);
}

template<class T>
void View_qtwidgets<T>::closeEvent(QCloseEvent *ev)
{
    d->closeRequested.emit(ev);
}

template<class T>
void View_qtwidgets<T>::setMinimumSize(QSize sz)
{
    if (sz != QWidget::minimumSize()) {
        QWidget::setMinimumSize(sz);
        d->layoutInvalidated.emit();
    }
}


template<class T>
std::shared_ptr<View> View_qtwidgets<T>::childViewAt(QPoint localPos) const
{
    if (QWidget *child = QWidget::childAt(localPos))
        return ViewWrapper_qtwidgets::create(child);

    return {};
}

template<class T>
std::shared_ptr<View> View_qtwidgets<T>::rootView() const
{
    if (auto w = QWidget::window()) {
        return ViewWrapper_qtwidgets::create(w);
    }

    return {};
}

template<class T>
std::shared_ptr<View> View_qtwidgets<T>::parentView() const
{
    if (QWidget *p = QWidget::parentWidget()) {
        return ViewWrapper_qtwidgets::create(p);
    }

    return {};
}

template<class T>
std::shared_ptr<View> View_qtwidgets<T>::asWrapper()
{
    return ViewWrapper_qtwidgets::create(this);
}

/* static */
template<class T>
QVector<std::shared_ptr<View>> View_qtwidgets<T>::childViewsFor(const QWidget *parent)
{
    QVector<std::shared_ptr<View>> result;
    const QObjectList children = parent->children();
    result.reserve(children.size());
    for (QObject *child : children) {
        if (auto widget = qobject_cast<QWidget *>(child)) {
            result.push_back(ViewWrapper_qtwidgets::create(widget));
        }
    }

    return result;
}

namespace KDDockWidgets::Views {
template class View_qtwidgets<QWidget>;
template class View_qtwidgets<QMainWindow>;
}
