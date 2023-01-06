/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "View_flutter.h"
#include "private/View_p.h"
#include "private/multisplitter/Item_p.h"
#include "../Window_flutter.h"
#include "ViewWrapper.h"


using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;


View_flutter::View_flutter(KDDockWidgets::Controller *controller, Type type, View *parent,
                           Qt::WindowFlags)
    : View(controller, type)
{
    m_parentView = static_cast<View_flutter *>(parent);

    if (parent) {
        // setParent(parent);
    }
}

View_flutter::~View_flutter()
{
    // qDebug() << "~View_flutter" << this << int(type());
    m_inDtor = true;
    if (m_parentView && !m_parentView->inDtor()) {
        m_parentView->onChildRemoved(this);
    }
}

void View_flutter::setGeometry(QRect)
{
}

void View_flutter::move(int, int)
{
}

bool View_flutter::close()
{
    return true;
}

bool View_flutter::isVisible() const
{
    return {};
}

void View_flutter::setVisible(bool)
{
}

void View_flutter::setSize(int w, int h)
{
    qDebug() << "View_flutter::setSize()" << w << h << this;
}

std::shared_ptr<View> View_flutter::rootView() const
{
    if (m_parentView)
        return m_parentView->rootView();

    return const_cast<View_flutter *>(this)->asWrapper();
}

void View_flutter::setAttribute(Qt::WidgetAttribute, bool)
{
}

bool View_flutter::testAttribute(Qt::WidgetAttribute) const
{
    return false;
}

void View_flutter::setFlag(Qt::WindowType, bool)
{
}

Qt::WindowFlags View_flutter::flags() const
{
    return {};
}

void View_flutter::free_impl()
{
    // QObject::deleteLater();
    delete this;
}

QSize View_flutter::sizeHint() const
{
    return {};
}

QSize View_flutter::minSize() const
{
    return {};
}

QSize View_flutter::maxSizeHint() const
{
    return {};
}

QRect View_flutter::geometry() const
{
    return {};
}

QRect View_flutter::normalGeometry() const
{
    return {};
}

void View_flutter::setNormalGeometry(QRect)
{
}

void View_flutter::setMaximumSize(QSize)
{
}

void View_flutter::setWidth(int)
{
}

void View_flutter::setHeight(int)
{
}

void View_flutter::setFixedWidth(int)
{
}

void View_flutter::setFixedHeight(int)
{
}

void View_flutter::show()
{
}

void View_flutter::hide()
{
}

void View_flutter::updateGeometry()
{
}

void View_flutter::update()
{
}

void View_flutter::setParent(View *parent)
{
    if (parent == m_parentView)
        return;

    m_parentView = static_cast<View_flutter *>(parent);

    if (parent) {
        static_cast<View_flutter *>(parent)->onChildAdded(this);
    }
}

void View_flutter::raiseAndActivate()
{
}

void View_flutter::activateWindow()
{
}

void View_flutter::raise()
{
}

QVariant View_flutter::property(const char *) const
{
    return {};
}

bool View_flutter::isRootView() const
{
    return m_parentView == nullptr;
}

QPoint View_flutter::mapToGlobal(QPoint) const
{
    return {};
}

QPoint View_flutter::mapFromGlobal(QPoint) const
{
    return {};
}

QPoint View_flutter::mapTo(View *, QPoint) const
{
    return {};
}

void View_flutter::setWindowOpacity(double)
{
}

void View_flutter::setSizePolicy(SizePolicy, SizePolicy)
{
}

SizePolicy View_flutter::verticalSizePolicy() const
{
    return {};
}

SizePolicy View_flutter::horizontalSizePolicy() const
{
    return {};
}

void View_flutter::setWindowTitle(const QString &)
{
}

void View_flutter::setWindowIcon(const QIcon &)
{
}

bool View_flutter::isActiveWindow() const
{
    return false;
}

void View_flutter::showNormal()
{
}

void View_flutter::showMinimized()
{
}

void View_flutter::showMaximized()
{
}

bool View_flutter::isMinimized() const
{
    return {};
}

bool View_flutter::isMaximized() const
{
    return {};
}

std::shared_ptr<Window> View_flutter::window() const
{
    return {};
}

std::shared_ptr<View> View_flutter::childViewAt(QPoint) const
{
    return {};
}

std::shared_ptr<View> View_flutter::parentView() const
{
    // qDebug() << Q_FUNC_INFO << "parent is" << ( void * )m_parentView << "this=" << ( void * )this
    //          << int(type());

    if (m_parentView)
        return m_parentView->asWrapper();

    return {};
}

std::shared_ptr<View> View_flutter::asWrapper()
{
    return ViewWrapper::create(this);
}

void View_flutter::setObjectName(const QString &name)
{
    m_name = name;
}

void View_flutter::grabMouse()
{
}

void View_flutter::releaseMouse()
{
}

void View_flutter::releaseKeyboard()
{
    // Not needed for QtQuick
}

void View_flutter::setFocus(Qt::FocusReason)
{
}

bool View_flutter::hasFocus() const
{
    return false;
}

Qt::FocusPolicy View_flutter::focusPolicy() const
{
    return {};
}

void View_flutter::setFocusPolicy(Qt::FocusPolicy)
{
}

QString View_flutter::objectName() const
{
    return m_name;
}

void View_flutter::setMinimumSize(QSize)
{
}

void View_flutter::render(QPainter *)
{
}

void View_flutter::setCursor(Qt::CursorShape)
{
}

void View_flutter::setMouseTracking(bool)
{
}

QVector<std::shared_ptr<View>> View_flutter::childViews() const
{
    return {};
}

void View_flutter::setZOrder(int)
{
}

HANDLE View_flutter::handle() const
{
    // TODOm4
    return this;
}

bool View_flutter::onResize(int w, int h)
{
    // Indirection so Dartagnan generates it, while we don't do bindings for View.cpp
    return View::onResize(w, h);
}
