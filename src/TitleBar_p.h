/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KD_TITLEBAR_P_H
#define KD_TITLEBAR_P_H

#include "docks_export.h"
#include "Draggable_p.h"
#include "Frame_p.h"
#include "DockWidget.h"

#include <QPainter>
#include <QToolButton>
#include <QStyle>
#include <QWidget>
#include <QVector>
#include <QStyleOptionToolButton>

class QHBoxLayout;
class QLabel;

namespace KDDockWidgets {

class DockWidget;
class Frame;
class Button;

class DOCKS_EXPORT_FOR_UNIT_TESTS TitleBar : public QWidget
    , public Draggable
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(bool hasIcon READ hasIcon NOTIFY iconChanged)
public:
    typedef QVector<TitleBar *> List;
    explicit TitleBar(DockWidget *parent);
    explicit TitleBar(Frame *parent);
    explicit TitleBar(FloatingWindow *parent);
    ~TitleBar() override;

    void setTitle(const QString &title);
    QString title() const { return m_title; }

    void setIcon(const QIcon &icon);
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    QWidget* closeButton() const;

    ///@brief Returns true if the dock widget which has this title bar is floating
    bool isFloating() const;

    ///@brief the list of dockwidgets under this TitleBar.
    /// There should always be at least 1. If more than 1 then they are tabbed.
    DockWidget::List dockWidgets() const;

    ///@brief returns whether this title bar supports a floating/unfloating button
    bool supportsFloatingButton() const;

    ///@brief returns whether this title bar has an icon
    bool hasIcon() const;

    ///@brief toggle floating
    bool onDoubleClicked();

Q_SIGNALS:
    void titleChanged();
    void iconChanged();
protected:
    void paintEvent(QPaintEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;

private:
    friend class TestDocks;
    void updateFloatButton();
    void updateCloseButton();
    void onCloseClicked();
    void onFloatClicked();
    void init();
    int buttonAreaWidth() const;
    QRect iconRect() const;

    QPoint m_pressPos;
    QString m_title;
    QIcon m_icon;
    QHBoxLayout *const m_layout;

    DockWidget *const m_dockWidget;
    Frame *const m_frame;
    FloatingWindow *const m_floatingWindow;
    Button *m_closeButton = nullptr;
    Button *m_floatButton = nullptr;
    QLabel *m_dockWidgetIcon = nullptr;
};

class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(QWidget *parent)
        : QToolButton(parent)
    {
        //const int margin = style()->pixelMetric(QStyle::PM_DockWidgetTitleBarButtonMargin, nullptr, this) * 2;
        QSize sz = /*QSize(margin, margin) + */ QSize(16, 16);
        setFixedSize(sz);
    }

    ~Button() override;

    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        QStyleOptionToolButton opt;
        opt.init(this);

        if (isEnabled() && underMouse()) {
            if (isDown()) {
                opt.state |= QStyle::State_Sunken;
            } else {
                opt.state |= QStyle::State_Raised;
            }
            style()->drawPrimitive(QStyle::PE_PanelButtonTool, &opt, &p, this);
        }

        opt.subControls = QStyle::SC_None;
        opt.features = QStyleOptionToolButton::None;
        opt.icon = icon();
        opt.iconSize = size();
        style()->drawComplexControl(QStyle::CC_ToolButton, &opt, &p, this);
    }
};

}

#endif
