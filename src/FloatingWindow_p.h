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

#ifndef KD_FLOATING_WINDOW_P_H
#define KD_FLOATING_WINDOW_P_H

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

    /**
     * @brief checks if this FloatingWindow only has one frame.
     * If true it means there's no side-by-side dock widgets here. There's only 1 frame.
     * Note that despite having only 1 frame it can still have multiple DockWidgets,
     * as they can be tabbed into the single frame.
     * @return true if this FloatingWindow has a single frame.
     */
    bool hasSingleFrame() const;

    /**
     * @brief checks if this FloatingWindow only has one dockwidget.
     * This is a more specific case than hasSingleFrame(), it implies not only a single frame,
     * but that frame must only have 1 dock widget.
     * @return true if this FloatingWindow only has one dockwidget.
     */
    bool hasSingleDockWidget() const;

    ///@brief For tests-only. Returns the number of Frame instances in the whole application.
    static int dbg_numFrames();

Q_SIGNALS:
    void numFramesChanged();

protected:
    void closeEvent(QCloseEvent *) override;
    void paintEvent(QPaintEvent *) override;

    ///@brief reimplemented for debug purposes
    void resizeEvent(QResizeEvent *) override;
private:
    Q_DISABLE_COPY(FloatingWindow)
    void maybeCreateResizeHandler();
    void onFrameCountChanged(int count);
    void onVisibleFrameCountChanged(int count);
    void updateTitleBarVisibility();
    TitleBar *const m_titleBar;
    QVBoxLayout *const m_vlayout;
    DropArea *const m_dropArea;
    bool m_disableSetVisible = false;
};

QDataStream &operator<<(QDataStream &ds, FloatingWindow *);

}

#endif
