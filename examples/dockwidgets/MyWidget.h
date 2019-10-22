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

#ifndef EXAMPLEDOCKABLEWIDGET_H
#define EXAMPLEDOCKABLEWIDGET_H

#include <QWidget>

class QPainter;

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(const QString &backgroundFile, const QString &logoFile, QWidget *parent = nullptr);
    ~MyWidget();
protected:
    void drawLogo(QPainter &);
    QImage m_background;
    QImage m_logo;
};

class MyWidget1 : public MyWidget
{
public:
    explicit MyWidget1(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*) override;
};

class MyWidget2 : public MyWidget
{
public:
    explicit MyWidget2(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*) override;
};

class MyWidget3 : public MyWidget
{
public:
    explicit MyWidget3(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*) override;
    QImage m_triangle;
};


#endif
