/*
  This file is part of KDDockWidgets.

  Copyright (C) 2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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
#include "DockWidget.h"

#include <QWidget>
#include <QPointer>
#include <QVector>

#include <memory>

namespace KDDockWidgets {
namespace Tests {

struct DockDescriptor {
    Location loc;
    int relativeToIndex;
    QPointer<DockWidget> createdDock;
    KDDockWidgets::AddingOption option;
};


bool shouldBlacklistWarning(const QString &msg, const QString &category = {});

std::unique_ptr<KDDockWidgets::MainWindow> createMainWindow(QSize sz = {600, 600},
                                                            KDDockWidgets::MainWindowOptions options = MainWindowOption_HasCentralFrame);



std::unique_ptr<KDDockWidgets::MainWindow> createMainWindow(QVector<DockDescriptor> &docks);

KDDockWidgets::DockWidget *createDockWidget(const QString &name, QWidget *w,
                                            DockWidget::Options options = {});
KDDockWidgets::DockWidget *createDockWidget(const QString &name, QColor color);

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


}
}

Q_DECLARE_METATYPE(KDDockWidgets::Tests::DockDescriptor)


#endif

