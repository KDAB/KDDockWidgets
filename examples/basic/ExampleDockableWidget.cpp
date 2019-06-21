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

#include "ExampleDockableWidget.h"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
{
    auto l = new QVBoxLayout(this);

    auto box = new QGroupBox();
    auto l2 = new QVBoxLayout(box);
    auto radio1 = new QRadioButton(QStringLiteral("foo"), box);
    auto radio2 = new QRadioButton(QStringLiteral("bar"), box);
    auto radio3 = new QRadioButton(QStringLiteral("baz"), box);
    l2->addWidget(radio1);
    l2->addWidget(radio2);
    l2->addWidget(radio3);

    l->addWidget(box);
    l->addWidget(new QPushButton(QStringLiteral("Test")));
    l->addWidget(new QPushButton(QStringLiteral("Test")));
    l->addStretch();
}

MyWidget::~MyWidget()
{
}
