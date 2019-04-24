/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018 Sérgio Martins <sergio.martins@kdab.com>

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

#ifndef KD_FLOATING_WINDOW_H
#define KD_FLOATING_WINDOW_H

#include "docks_export.h"
#include "Frame_p.h"
#include "Draggable_p.h"

#include <QWidget>

class QVBoxLayout;

namespace KDDockWidgets {

class DropArea;
class Frame;

class DOCKS_EXPORT_FOR_UNIT_TESTS FloatingWindow : public QWidget
    , public Draggable
{
    Q_OBJECT
public:
    explicit FloatingWindow(QWidget *parent = nullptr);
    explicit FloatingWindow(Frame *frame, QWidget *parent = nullptr);
    ~FloatingWindow() override;

    // Draggable:
    std::unique_ptr<WindowBeingDragged> makeWindow() override;
    const Frame::List frames() const;
    DropArea *dropArea() const { return m_dropArea; }
    TitleBar *titleBar() const { return m_titleBar; }
    TitleBar *actualTitleBar() const;

    static void paintFrame(QWidget *);
    bool anyNonClosable() const;
Q_SIGNALS:
    void numFramesChanged();

protected:
    void closeEvent(QCloseEvent *) override;
    void paintEvent(QPaintEvent *) override;

private:
    Q_DISABLE_COPY(FloatingWindow)
    void maybeCreateResizeHandler();
    void onFrameCountChanged(int count);
    void onVisibleFrameCountChanged(int count);
    void updateTitleBarVisibility();
    TitleBar *const m_titleBar;
    QVBoxLayout *const m_vlayout;
    DropArea *const m_dropArea;
};
}

#endif
