/*
  This file is part of KDDockWidgets.

  Copyright (C) 2018-2019 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Sérgio Martins <sergio.martins@kdab.com>
  Author: Laurent Montel <laurent.montel@kdab.com>

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

#include "DockWidget.h"
#include "MainWindow.h"
#include "DropArea_p.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QTextEdit>

#include <iostream>

#ifdef Q_OS_WIN
# include <Windows.h>
#endif

using namespace KDDockWidgets;

static QtMessageHandler s_original = nullptr;

void fatalWarningsMessageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg)
{
    s_original(t, context, msg);
    if (t == QtWarningMsg) {

        if (QLatin1String(context.category) == QLatin1String("qt.qpa.xcb"))
            return;

        if (msg.contains(QLatin1String("QSocketNotifier: Invalid socket")) ||
            msg.contains(QLatin1String("QWindowsWindow::setGeometry")) ||
            msg.contains(QLatin1String("This plugin does not support")) ||
            msg.contains(QLatin1String("Note that Qt no longer ships fonts")) ||
            msg.contains(QLatin1String("Another dock KDDockWidgets::DockWidget")) ||
            msg.contains(QLatin1String("Dock widget already exists in the layout")))
            return;

        if (!qEnvironmentVariableIsSet("NO_FATAL"))
            qFatal("Got a warning, category=%s", context.category);
    }
}


static std::unique_ptr<MainWindow> createMainWindow(QSize sz = {600, 600}, MainWindowOptions options = MainWindowOption_HasCentralFrame)
{
    auto ptr = std::unique_ptr<MainWindow>(new MainWindow(QStringLiteral("MyMainWindow"), options));
    ptr->show();
    ptr->resize(sz);
    return ptr;
}

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    app.setOrganizationName(QStringLiteral("KDAB"));
    app.setApplicationName(QStringLiteral("Test random app"));

    QCommandLineParser parser;
    parser.addOption(QCommandLineOption(QStringList() <<  QStringLiteral("duration"), QStringLiteral("application duration in seconds"), QStringLiteral("second")));
    parser.process(app);
    int duration = -1;
    if (parser.isSet(QStringLiteral("duration"))) {
        duration = parser.value(QStringLiteral("duration")).toInt();
    }

    qDebug() << " Duration " << duration;
    if (duration > 0) {
        //QTimer::singleShot(duration, this, []() {quit();});
    }

    auto window = createMainWindow();
    std::cout << "auto window = createMainWindow();" << std::endl;
    s_original = qInstallMessageHandler(fatalWarningsMessageHandler);

    const int number = 20;
    qsrand(QDateTime::currentMSecsSinceEpoch());
    const int randomValue = (qrand() % number + 1);
    //qDebug() << " randomValue" << randomValue;
    QList<DockWidget *> listDockWidget;
    listDockWidget.reserve(randomValue);
    //Create DockWidget
    std::cout << "QList<DockWidget *> listDockWidget;" << std::endl;
    for (int i = 0; i < randomValue; ++i) {
        const QString name = QStringLiteral("foo-%1").arg(i);
        auto dock = new DockWidget(name);
        dock->setWidget(new QTextEdit(dock));
        listDockWidget.append(dock);
        std::cout << "{" << std::endl;
        std::cout << QString(QStringLiteral("   auto dock = new DockWidget(QStringLiteral(\"%1\"));").arg(name)).toLocal8Bit().constData() << std::endl;
        std::cout << "   dock->setWidget(new QTextEdit(dock));" << std::endl;
        std::cout << "   listDockWidget.append(dock);"<<std::endl;
        std::cout << "}" << std::endl;
    }

    //Add log !
    QWidget *central = window->centralWidget();
    auto dropArea = qobject_cast<DropArea *>(central);

    std::cout << "QWidget *central = window->centralWidget();" << std::endl;
    std::cout << "auto dropArea = qobject_cast<DropArea *>(central);" << std::endl;

    // Add dockWidget
    for (int i = 0; i < listDockWidget.count(); ++i) {
        //Don't use Location_None position
        const int position = (qrand() % 4 ) + 1;
        if (i == 0) {
            std::cout << QString(QStringLiteral("window->addDockWidget(listDockWidget.at(%1), static_cast<Location>(%2));").arg(i).arg(position)).toLocal8Bit().constData() << std::endl;
            window->addDockWidget(listDockWidget.at(i), static_cast<Location>(position));
        } else {
            const int attachAsTab = (qrand() % 3 ) ;
            if (attachAsTab == 0) {
                std::cout << QString(QStringLiteral("listDockWidget.at(%1 - 1)->addDockWidgetAsTab(listDockWidget.at(%1));").arg(i)).toLocal8Bit().constData() << std::endl;
                listDockWidget.at(i - 1)->addDockWidgetAsTab(listDockWidget.at(i));
            } else if (attachAsTab == 1) {
                std::cout << QString(QStringLiteral("window->addDockWidget(listDockWidget.at(%1), static_cast<Location>(%2));").arg(i).arg(position)).toLocal8Bit().constData() << std::endl;
                window->addDockWidget(listDockWidget.at(i), static_cast<Location>(position));
            } else {
                const int addingOption = (qrand() % 2 );
                std::cout << QString(QStringLiteral("window->addDockWidget(listDockWidget.at(%1-1), static_cast<Location>(%3), listDockWidget.at(%1), static_cast<AddingOption>(%2));").arg(i).arg(addingOption).arg(position)).toLocal8Bit().constData() << std::endl;
                window->addDockWidget(listDockWidget.at(i-1), static_cast<Location>(position), listDockWidget.at(i), static_cast<AddingOption>(addingOption));
            }
        }
        dropArea->checkSanity();
        std::cout << "dropArea->checkSanity();" << std::endl << std::endl;
    }

    window->show();


    return app.exec();
}
