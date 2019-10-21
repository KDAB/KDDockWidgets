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

#include "MyWidget.h"

#include <QPainter>
#include <QDebug>
#include <QFile>

MyWidget::MyWidget(const QString &backgroundFile, const QString &logoFile, QWidget *parent)
    : QWidget(parent)
    , m_background(QImage(backgroundFile))
    , m_logo(QImage(logoFile))
{
    if (!backgroundFile.isEmpty() && m_background.isNull())
        qWarning() << "Invalid image for background file" << backgroundFile;

    if (!logoFile.isEmpty() && m_logo.isNull())
        qWarning() << "Invalid image for logo file" << logoFile;
}

MyWidget::~MyWidget()
{
}

void MyWidget::drawLogo(QPainter &p)
{
    if (m_logo.isNull())
        return;

    const qreal ratio = m_logo.width() / (m_logo.height() * 1.0);

    const int height = size().height() - 100;
    const int width = int(height * ratio);
    QRect targetLogoRect(0,0, width, height);
    targetLogoRect.moveCenter(rect().center());
    p.drawImage(targetLogoRect, m_logo, m_logo.rect());
}

MyWidget1::MyWidget1(MyWidget::QWidget *parent)
    : MyWidget(QStringLiteral(":/assets/triangles.png"), QStringLiteral(":/assets/KDAB_bubble_white.png"), parent)
{
}

void MyWidget1::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(0xCC, 0xCC, 0xCC));
    p.drawImage(m_background.rect(), m_background, m_background.rect());

    drawLogo(p);
}

MyWidget2::MyWidget2(MyWidget::QWidget *parent)
    : MyWidget(QString(), QStringLiteral(":/assets/KDAB_bubble_blue.png"), parent)
    , m_triangle(QImage(QStringLiteral(":/assets/tri.png")))
{
}

void MyWidget2::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::white);

    //.drawImage(rect(), m_triangle, m_triangle.rect());

    drawLogo(p);
}

MyWidget3::MyWidget3(MyWidget::QWidget *parent)
    : MyWidget(QStringLiteral(":/assets/base.png"), QStringLiteral(":/assets/KDAB_bubble_fulcolor.png"), parent)
{
}

void MyWidget3::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(0xD5, 0xD5, 0xD5));

    p.drawImage(m_background.rect(), m_background, m_background.rect());
    drawLogo(p);
}
