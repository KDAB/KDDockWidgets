/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2022 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/docks_export.h"

#include <QDebug>
#include <QObject>
#include <QIcon>

#if defined(QT_WIDGETS_LIB)
#include <QAction>
#else
// A QAction for QtQuick. So it compiles without widgets
class DOCKS_EXPORT QAction : public QObject
{
    Q_OBJECT
public:
    using QObject::QObject;

    ~QAction() override;

    bool isChecked() const
    {
        return m_isChecked;
    }

    void setCheckable(bool is)
    {
        m_isCheckable = is;
    }

    void setIcon(const QIcon &)
    {
        qWarning() << "Not implemented for QtQuick";
    }

    QIcon icon() const
    {
        qWarning() << "Not implemented for QtQuick";
        return {};
    }

    void setText(const QString &text)
    {
        m_text = text;
    }

    void setToolTip(const QString &text)
    {
        m_toolTip = text;
    }

    QString toolTip() const
    {
        return m_toolTip;
    }

    bool enabled() const
    {
        return m_enabled;
    }

    void setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }

    bool checked() const
    {
        return m_checked;
    }

    void setChecked(bool checked)
    {
        m_checked = checked;
    }

    bool isEnabled() const
    {
        return m_enabled;
    }

    void toggle()
    {
        m_enabled = !m_enabled;
        Q_EMIT toggled(m_enabled);
    }

Q_SIGNALS:
    bool toggled(bool);

private:
    QString m_text;
    QString m_toolTip;

    bool m_isChecked = false;
    bool m_isCheckable = false;
    bool m_enabled = false;
    bool m_checked = false;
};

#endif
