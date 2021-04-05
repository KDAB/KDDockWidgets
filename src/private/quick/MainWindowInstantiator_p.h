/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#ifndef KD_MAIN_WINDOW_WRAPPER_P_H
#define KD_MAIN_WINDOW_WRAPPER_P_H

#include "QWidgetAdapter.h"
#include "kddockwidgets/docks_export.h"

#include <QQuickItem>

namespace KDDockWidgets {

class MainWindowQuick;

/// @brief A wrapper to workaround the limitation that QtQuick can't pass arguments through MainWindowQuick's ctor
/// So instead, user instantiates a MainWindowWrapper in QML and calls init.
class DOCKS_EXPORT MainWindowInstantiator
    : public QWidgetAdapter
{
    Q_OBJECT
    Q_PROPERTY(QString uniqueName READ uniqueName WRITE setUniqueName NOTIFY uniqueNameChanged)
    Q_PROPERTY(int options READ options WRITE setOptions NOTIFY optionsChanged) // TODO: Use num
public:
    ///@brief ctor, called by QML engine
    MainWindowInstantiator();

    QString uniqueName() const;
    void setUniqueName(const QString &);

    int options() const;
    void setOptions(int);

protected:
    void componentComplete() override;

Q_SIGNALS:
    void uniqueNameChanged();
    void optionsChanged();

private:
    QString m_uniqueName;
    MainWindowQuick *m_mainWindow = nullptr;
    int m_options = 0;
};

}

#endif
