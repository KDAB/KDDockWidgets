/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2020-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#pragma once

#include "kddockwidgets/core/Action.h"

namespace KDDockWidgets {

namespace QtQuick {

class DOCKS_EXPORT Action : public QObject, public KDDockWidgets::Core::Action
{
    Q_OBJECT
public:
    explicit Action(Core::DockWidget *, const char *debugName = "");
    ~Action() override;

    // TODOm4: Remove. Check others as well
    void setCheckable(bool is) override
    {
        m_checkable = is;
    }

    // TODOm4: Remove
    bool isCheckable() const override
    {
        return m_checkable;
    }

    void setIcon(const KDDockWidgets::Icon &) override;
    KDDockWidgets::Icon icon() const override;

    void setText(const QString &text) override
    {
        m_text = text;
    }

    void setToolTip(const QString &text) override
    {
        m_toolTip = text;
    }

    QString toolTip() const override
    {
        return m_toolTip;
    }

    void setEnabled(bool enabled) override
    {
        m_enabled = enabled;
    }

    bool isChecked() const override
    {
        return m_checked;
    }

    void setChecked(bool checked) override;

    bool isEnabled() const override
    {
        return m_enabled;
    }

    void toggle()
    {
        setChecked(!m_checked);
    }

    bool blockSignals(bool) override;

Q_SIGNALS:
    bool toggled(bool);

private:
    QString m_text;
    QString m_toolTip;

    bool m_checkable = true;
    bool m_enabled = true;
    bool m_checked = false;
};

}

}
