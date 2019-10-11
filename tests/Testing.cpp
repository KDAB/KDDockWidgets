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

#include "Testing.h"
#include "MainWindow.h"
#include "DockWidget.h"
#include "DockRegistry_p.h"

#include <QTest>
#include <QLoggingCategory>

using namespace KDDockWidgets;
using namespace KDDockWidgets::Testing;

extern quintptr Q_CORE_EXPORT qtHookData[];
static QString s_expectedWarning;
static QtMessageHandler s_original = nullptr;

static bool isGammaray()
{
    static bool is = qtHookData[3] != 0;
    return is;
}

static bool shouldBlacklistWarning(const QString &msg, const QString &category)
{
    if (category == QLatin1String("qt.qpa.xcb"))
        return true;

    return msg.contains(QLatin1String("QSocketNotifier: Invalid socket")) ||
           msg.contains(QLatin1String("QWindowsWindow::setGeometry")) ||
           msg.contains(QLatin1String("This plugin does not support")) ||
           msg.contains(QLatin1String("Note that Qt no longer ships fonts")) ||
           msg.contains(QLatin1String("Another dock KDDockWidgets::DockWidget")) ||
           msg.contains(QLatin1String("There's multiple MainWindows, not sure what to do about parenting"));
}

static void fatalWarningsMessageHandler(QtMsgType t, const QMessageLogContext &context, const QString &msg)
{
    if (shouldBlacklistWarning(msg, QLatin1String(context.category)))
        return;

    s_original(t, context, msg);
    if (t == QtWarningMsg) {

        if (!s_expectedWarning.isEmpty() && msg.contains(s_expectedWarning))
            return;

        if (!isGammaray() && !qEnvironmentVariableIsSet("NO_FATAL"))
            qFatal("Got a warning, category=%s", context.category);
    }
}

class HostedWidget : public QWidget
{
public:

    explicit HostedWidget(QSize minSz = QSize(1,1))
        : m_minSz(minSz)
    {
    }

    ~HostedWidget() override;

    QSize sizeHint() const override
    {
        return m_minSz;
    }

    QSize minimumSizeHint() const override
    {
        return m_minSz;
    }

    void setMinSize(QSize s)
    {
        m_minSz = s;
        updateGeometry();
    }

    QSize m_minSz;
};

HostedWidget::~HostedWidget() {}

static MainWindow* createMainWindow(const Testing::MainWindowDescriptor &mwd)
{
    static int count = 0;
    count++;
    auto mainWindow = new MainWindow(QStringLiteral("MainWindow-%1").arg(count), mwd.mainWindowOption);

    mainWindow->setGeometry(mwd.geometry);

    mainWindow->show();
    return mainWindow;
}

static DockWidget* createDockWidget(const Testing::DockWidgetDescriptor &dwd)
{
    static int count = 0;
    count++;
    auto dockWidget = new DockWidget(QStringLiteral("DockWidget-%1").arg(count));

    dockWidget->setWidget(new HostedWidget(dwd.minSize));

    if (dwd.isFloating)
        dockWidget->setGeometry(dwd.geometry);

    if (dwd.isVisible)
        dockWidget->show();

    return dockWidget;
}

static void createLayout(const Layout &layout)
{
    for (const Testing::MainWindowDescriptor &mwd : layout.mainWindows) {
        createMainWindow(mwd);
    }

    for (const Testing::DockWidgetDescriptor &dwd : layout.dockWidgets) {
        createDockWidget(dwd);
    }
}

void Testing::runTest(const Test &test)
{
    if (!DockRegistry::self()->isEmpty())
        qFatal("There's dock widgets and the start runTest");

    createLayout(test.initialLayout);
    for (const auto &op : test.operations) {
        op->execute();
    }

    for (MainWindowBase *mw : DockRegistry::self()->mainwindows())
        delete mw;

    for (FloatingWindow *fw : DockRegistry::self()->nestedwindows())
        delete fw;

    for (DockWidgetBase *dw : DockRegistry::self()->dockwidgets())
        delete dw;

    if (!DockRegistry::self()->isEmpty())
        qFatal("There's still dock widgets and the end of runTest");
}

void Testing::installFatalMessageHandler()
{
    s_original = qInstallMessageHandler(fatalWarningsMessageHandler);
}

void Testing::setExpectedWarning(const QString &expected)
{
    s_expectedWarning = expected;
}
