/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MAIN_WINDOW_WRAPPER_P_H
#define KD_MAIN_WINDOW_WRAPPER_P_H

#include "docks_export.h"
#include "QWidgetAdapter.h"

#include <QQuickItem>

namespace KDDockWidgets {

class MainWindowQuick;

/// @brief A wrapper to workaround the limitation that QtQuick can't pass arguments through MainWindowQuick's ctor
/// So instead, user instantiates a MainWindowWrapper in QML and calls init.
class DOCKS_EXPORT MainWindowWrapper : public QWidgetAdapter
{
    Q_OBJECT
public:
    ///@brief ctor, called by QML engine
    MainWindowWrapper();

    ///@brief called by the user, typically in main.qml or so, in Component.onCompleted{}
    Q_INVOKABLE void init(const QString &uniqueName);

private:
    MainWindowQuick *m_mainWindow = nullptr;
};

}

#endif
