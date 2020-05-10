/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019-2020 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef KDDOCKWIDGETS_TESTS_UTILS_H
#define KDDOCKWIDGETS_TESTS_UTILS_H

#include "MainWindow.h"
#include "KDDockWidgets.h"
#include "DropIndicatorOverlayInterface_p.h"
#include "DockWidget.h"

#include <QWidget>
#include <QPointer>
#include <QVector>

#include <memory>

// clazy:excludeall=ctor-missing-parent-argument,missing-qobject-macro,range-loop,missing-typeinfo,detaching-member,function-args-by-ref,non-pod-global-static,reserve-candidates

namespace KDDockWidgets {

class FrameWidget;

namespace Tests {

enum ButtonAction {
    ButtonAction_None,
    ButtonAction_Press = 1,
    ButtonAction_Release = 2
};
Q_DECLARE_FLAGS(ButtonActions, ButtonAction)

struct DockDescriptor {
    Location loc;
    int relativeToIndex;
    QPointer<DockWidgetBase> createdDock;
    KDDockWidgets::AddingOption option;
};

QWidget* draggableFor(QWidget *);

bool shouldBlacklistWarning(const QString &msg, const QString &category = {});

QPoint dragPointForWidget(Frame* frame, int index);

std::unique_ptr<KDDockWidgets::MainWindow> createMainWindow(QSize sz = {600, 600},
                                                            KDDockWidgets::MainWindowOptions options = MainWindowOption_HasCentralFrame, const QString &name = {});



std::unique_ptr<KDDockWidgets::MainWindow> createMainWindow(QVector<DockDescriptor> &docks);

KDDockWidgets::DockWidgetBase *createDockWidget(const QString &name, QWidget *w,
                                                DockWidgetBase::Options options = {}, bool show = true,
                                                const QString &affinityName = {});
KDDockWidgets::DockWidgetBase *createDockWidget(const QString &name, QColor color);

class NonClosableWidget : public QWidget
{
public:
    Q_OBJECT
public:
    explicit NonClosableWidget(QWidget *parent = nullptr);
    ~NonClosableWidget() override;

protected:
    void closeEvent(QCloseEvent *event) override;
};

class MyWidget : public QWidget
{
public:
    explicit MyWidget(const QString &, QColor c);
    ~MyWidget() override;


    QSize minimumSizeHint() const override
    {
        return {100, 100};
    }

protected:
    void paintEvent(QPaintEvent *) override;
private:
    QColor c;
};


void doubleClickOn(QPoint globalPos, QWidget *receiver);
void pressOn(QPoint globalPos, QWidget *receiver);
void releaseOn(QPoint globalPos, QWidget *receiver);
void moveMouseTo(QPoint globalDest, QWidget *receiver);
void drag(QWidget *sourceWidget, QPoint pressGlobalPos, QPoint globalDest, ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release);
void drag(QWidget *sourceWidget, QPoint globalDest, ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release);
void dragFloatingWindowTo(FloatingWindow *fw, QPoint globalDest, ButtonActions buttonActions = ButtonActions(ButtonAction_Press) | ButtonAction_Release);
void dragFloatingWindowTo(FloatingWindow *fw, DropArea *target, DropIndicatorOverlayInterface::DropLocation dropLocation);

}

inline bool qpaPassedAsArgument(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        if (qstrcmp(argv[i], "-platform") == 0) {
            return true;
        }
    }

    return false;
}

}

Q_DECLARE_METATYPE(KDDockWidgets::Tests::DockDescriptor)


#endif

