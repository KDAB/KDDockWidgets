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

#include <QWidget>
#include <QVector>


class QHBoxLayout;


namespace KDDockWidgets {

class DockWidget;
class Frame;
class Button;

class DOCKS_EXPORT_FOR_UNIT_TESTS TitleBar : public QWidget
    , public Draggable
{
    Q_OBJECT
public:
    typedef QVector<TitleBar *> List;
    explicit TitleBar(DockWidget *parent);
    explicit TitleBar(Frame *parent);
    explicit TitleBar(FloatingWindow *parent);
    ~TitleBar() override;

    void setTitle(const QString &title);
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    QWidget* closeButton() const;
protected:
    void paintEvent(QPaintEvent *) override;

private:
    void updateCloseButton();
    void onCloseClicked();
    void onFloatClicked();
    void init();
    int buttonAreaWidth() const;

    QPoint m_pressPos;
    QString m_title;
    QHBoxLayout *const m_layout;

    DockWidget *const m_dockWidget;
    Frame *const m_frame;
    FloatingWindow *const m_floatingWindow;
    Button *m_closeButton = nullptr;
    Button *m_floatButton = nullptr;
};
}

#endif
