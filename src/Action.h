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

    void setCheckable(bool is)
    {
        m_checkable = is;
    }

    bool isCheckable() const
    {
        return m_checkable;
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

    bool isChecked() const
    {
        return m_checked;
    }

    void setChecked(bool checked)
    {
        if (m_checked != checked) {
            m_checked = checked;
            Q_EMIT toggled(checked);
        }
    }

    bool isEnabled() const
    {
        return m_enabled;
    }

    void toggle()
    {
        setChecked(!m_checked);
    }

Q_SIGNALS:
    bool toggled(bool);

private:
    QString m_text;
    QString m_toolTip;

    bool m_checkable = true;
    bool m_enabled = true;
    bool m_checked = false;
};

#endif
