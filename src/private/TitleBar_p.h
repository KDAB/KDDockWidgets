/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_TITLEBAR_P_H
#define KD_TITLEBAR_P_H

#include "docks_export.h"

#include "QWidgetAdapter.h"
#include "Draggable_p.h"
#include "Frame_p.h"
#include "DockWidgetBase.h"

#include <QVector>
#include <QIcon>

QT_BEGIN_NAMESPACE
class QHBoxLayout;
class QLabel;
QT_END_NAMESPACE

namespace KDDockWidgets {

class DockWidgetBase;
class Frame;
class Button;

class DOCKS_EXPORT TitleBar : public QWidgetAdapter
    , public Draggable
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(bool hasIcon READ hasIcon NOTIFY iconChanged)
public:
    typedef QVector<TitleBar *> List;
    explicit TitleBar(Frame *parent);
    explicit TitleBar(FloatingWindow *parent);
    ~TitleBar() override;

    void setTitle(const QString &title);
    QString title() const { return m_title; }

    void setIcon(const QIcon &icon);
    std::unique_ptr<WindowBeingDragged> makeWindow() override;

    DockWidgetBase *singleDockWidget() const override;

    ///@brief Returns true if the dock widget which has this title bar is floating
    bool isFloating() const;

    ///@brief the list of dockwidgets under this TitleBar.
    /// There should always be at least 1. If more than 1 then they are tabbed.
    DockWidgetBase::List dockWidgets() const;

    ///@brief returns whether this title bar supports a floating/docking button
    bool supportsFloatingButton() const;

    ///@brief returns whether this title bar supports a maximize/restore button
    bool supportsMaximizeButton() const;

    ///@brief returns whether this title bar has an icon
    bool hasIcon() const;

    ///@brief the icon
    QIcon icon() const;

    ///@brief toggle floating
    bool onDoubleClicked();

    ///@brief getter for m_frame
    const Frame *frame() const { return m_frame; }

    ///@brief getter for m_floatingWindow
    const FloatingWindow *floatingWindow() const { return m_floatingWindow; }

    virtual void updateCloseButton() {}

Q_SIGNALS:
    void titleChanged();
    void iconChanged();

protected:
    void onCloseClicked();
    void onFloatClicked();
    void onMaximizeClicked();
    void toggleMaximized();

    virtual void updateFloatButton() {}
    virtual void updateMaximizeButton() {}

    // The following are needed for the unit-tests
    virtual bool isCloseButtonVisible() const { return true; }
    virtual bool isCloseButtonEnabled() const { return true; }
    virtual bool isFloatButtonVisible() const { return true; }
    virtual bool isFloatButtonEnabled() const { return true; }

private:
    friend class TestDocks;

    void init();

    QPoint m_pressPos;
    QString m_title;
    QIcon m_icon;

    Frame *const m_frame;
    FloatingWindow *const m_floatingWindow;
};


}

#endif
