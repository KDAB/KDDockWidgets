/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company
  <info@kdab.com> Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "ViewWrapper.h"
#include "private/View_p.h"
#include "private/multisplitter/Item_p.h"
#include "../Window_flutter.h"
#include "View_flutter.h"


// TODOm4: Make this class available for other frontends ?

using namespace KDDockWidgets;
using namespace KDDockWidgets::Views;


ViewWrapper::ViewWrapper(View_flutter *wrapped)
    : View(wrapped->controller(), Type::ViewWrapper)
    , m_wrappedView(wrapped)
{
}

ViewWrapper::~ViewWrapper()
{
}

void ViewWrapper::setGeometry(QRect geo)
{
    m_wrappedView->setGeometry(geo);
}

void ViewWrapper::move(int x, int y)
{
    m_wrappedView->move(x, y);
}

bool ViewWrapper::close()
{
    return m_wrappedView->close();
}

bool ViewWrapper::isVisible() const
{
    return m_wrappedView->isVisible();
}

void ViewWrapper::setVisible(bool is)
{
    m_wrappedView->setVisible(is);
}

void ViewWrapper::setSize(int w, int h)
{
    m_wrappedView->setSize(w, h);
}

std::shared_ptr<View> ViewWrapper::rootView() const
{
    return m_wrappedView->rootView();
}

void ViewWrapper::setAttribute(Qt::WidgetAttribute attr, bool enabled)
{
    m_wrappedView->setAttribute(attr, enabled);
}

bool ViewWrapper::testAttribute(Qt::WidgetAttribute attr) const
{
    return m_wrappedView->testAttribute(attr);
}

void ViewWrapper::setFlag(Qt::WindowType flag, bool enabled)
{
    m_wrappedView->setFlag(flag, enabled);
}

Qt::WindowFlags ViewWrapper::flags() const
{
    return m_wrappedView->flags();
}

void ViewWrapper::free_impl()
{
}

QSize ViewWrapper::sizeHint() const
{
    return m_wrappedView->sizeHint();
}

QSize ViewWrapper::minSize() const
{
    return m_wrappedView->minSize();
}

QSize ViewWrapper::maxSizeHint() const
{
    return m_wrappedView->maxSizeHint();
}

QRect ViewWrapper::geometry() const
{
    return m_wrappedView->geometry();
}

QRect ViewWrapper::normalGeometry() const
{
    return m_wrappedView->normalGeometry();
}

void ViewWrapper::setNormalGeometry(QRect geo)
{
    m_wrappedView->setNormalGeometry(geo);
}

void ViewWrapper::setMaximumSize(QSize size)
{
    m_wrappedView->setMaximumSize(size);
}

void ViewWrapper::setWidth(int w)
{
    m_wrappedView->setWidth(w);
}

void ViewWrapper::setHeight(int h)
{
    m_wrappedView->setHeight(h);
}

void ViewWrapper::setFixedWidth(int w)
{
    m_wrappedView->setFixedWidth(w);
}

void ViewWrapper::setFixedHeight(int h)
{
    m_wrappedView->setFixedHeight(h);
}

void ViewWrapper::show()
{
    m_wrappedView->show();
}

void ViewWrapper::hide()
{
    m_wrappedView->hide();
}

void ViewWrapper::updateGeometry()
{
    m_wrappedView->updateGeometry();
}

void ViewWrapper::update()
{
    m_wrappedView->update();
}

void ViewWrapper::setParent(View *parent)
{
    m_wrappedView->setParent(parent);
}

void ViewWrapper::raiseAndActivate()
{
    m_wrappedView->raiseAndActivate();
}

void ViewWrapper::activateWindow()
{
    m_wrappedView->activateWindow();
}

void ViewWrapper::raise()
{
    m_wrappedView->raise();
}

QVariant ViewWrapper::property(const char *name) const
{
    return m_wrappedView->property(name);
}

bool ViewWrapper::isRootView() const
{
    return m_wrappedView->isRootView();
}

QPoint ViewWrapper::mapToGlobal(QPoint local) const
{
    return m_wrappedView->mapToGlobal(local);
}

QPoint ViewWrapper::mapFromGlobal(QPoint global) const
{
    return m_wrappedView->mapFromGlobal(global);
}

QPoint ViewWrapper::mapTo(View *view, QPoint pos) const
{
    return m_wrappedView->mapTo(view, pos);
}

void ViewWrapper::setWindowOpacity(double opacity)
{
    m_wrappedView->setWindowOpacity(opacity);
}

void ViewWrapper::setSizePolicy(SizePolicy hp, SizePolicy vp)
{
    m_wrappedView->setSizePolicy(hp, vp);
}

SizePolicy ViewWrapper::verticalSizePolicy() const
{
    return m_wrappedView->verticalSizePolicy();
}

SizePolicy ViewWrapper::horizontalSizePolicy() const
{
    return m_wrappedView->horizontalSizePolicy();
}

void ViewWrapper::setWindowTitle(const QString &title)
{
    m_wrappedView->setWindowTitle(title);
}

void ViewWrapper::setWindowIcon(const QIcon &icon)
{
    m_wrappedView->setWindowIcon(icon);
}

bool ViewWrapper::isActiveWindow() const
{
    return m_wrappedView->isActiveWindow();
}

void ViewWrapper::showNormal()
{
    m_wrappedView->showNormal();
}

void ViewWrapper::showMinimized()
{
    m_wrappedView->showMinimized();
}

void ViewWrapper::showMaximized()
{
    m_wrappedView->showMaximized();
}

bool ViewWrapper::isMinimized() const
{
    return m_wrappedView->isMinimized();
}

bool ViewWrapper::isMaximized() const
{
    return m_wrappedView->isMaximized();
}

std::shared_ptr<Window> ViewWrapper::window() const
{
    return m_wrappedView->window();
}

std::shared_ptr<View> ViewWrapper::childViewAt(QPoint pos) const
{
    return m_wrappedView->childViewAt(pos);
}

std::shared_ptr<View> ViewWrapper::parentView() const
{
    return m_wrappedView->parentView();
}

std::shared_ptr<View> ViewWrapper::asWrapper()
{
    return m_thisWeakPtr.lock();
}

void ViewWrapper::setObjectName(const QString &name)
{
    m_wrappedView->setObjectName(name);
}

void ViewWrapper::grabMouse()
{
    m_wrappedView->grabMouse();
}

void ViewWrapper::releaseMouse()
{
    m_wrappedView->releaseMouse();
}

void ViewWrapper::releaseKeyboard()
{
    m_wrappedView->releaseKeyboard();
}

void ViewWrapper::setFocus(Qt::FocusReason reason)
{
    m_wrappedView->setFocus(reason);
}

bool ViewWrapper::hasFocus() const
{
    return m_wrappedView->hasFocus();
}

Qt::FocusPolicy ViewWrapper::focusPolicy() const
{
    return m_wrappedView->focusPolicy();
}

void ViewWrapper::setFocusPolicy(Qt::FocusPolicy policy)
{
    m_wrappedView->setFocusPolicy(policy);
}

QString ViewWrapper::objectName() const
{
    return m_wrappedView->objectName();
}

void ViewWrapper::setMinimumSize(QSize size)
{
    m_wrappedView->setMinimumSize(size);
}

void ViewWrapper::render(QPainter *render)
{
    m_wrappedView->render(render);
}

void ViewWrapper::setCursor(Qt::CursorShape shape)
{
    m_wrappedView->setCursor(shape);
}

void ViewWrapper::setMouseTracking(bool tracking)
{
    m_wrappedView->setMouseTracking(tracking);
}

QVector<std::shared_ptr<View>> ViewWrapper::childViews() const
{
    return m_wrappedView->childViews();
}

void ViewWrapper::setZOrder(int z)
{
    m_wrappedView->setZOrder(z);
}

HANDLE ViewWrapper::handle() const
{
    return m_wrappedView->handle();
}

bool ViewWrapper::onResize(int w, int h)
{
    // Indirection so Dartagnan generates it, while we don't do bindings for View.cpp
    return View::onResize(w, h);
}

/*static*/ std::shared_ptr<View> ViewWrapper::create(View_flutter *wrapped)
{
    auto wrapper = new ViewWrapper(wrapped);
    auto ptr = std::shared_ptr<ViewWrapper>(wrapper);
    wrapper->setWeakPtr(ptr);

    return ptr;
}

void ViewWrapper::setWeakPtr(std::weak_ptr<ViewWrapper> thisPtr)
{
    m_thisWeakPtr = thisPtr;
}
