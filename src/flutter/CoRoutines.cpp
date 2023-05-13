/*
  This file is part of KDDockWidgets.

  SPDX-FileCopyrightText: 2019-2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  Author: Sérgio Martins <sergio.martins@kdab.com>

  SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "CoRoutines.h"

#include <iostream>
#include <queue>

using namespace KDDockWidgets::flutter;

class SleepTask
{
public:
    explicit SleepTask(int ms)
        : m_duration(ms)
    {
    }

    constexpr bool await_ready() const noexcept
    {
        return false;
    }

    void await_suspend(std::coroutine_handle<> h) const noexcept
    {
        // Q_ASSERT(!s_currentSleepTask);
        // Q_ASSERT(!m_handle);
        m_handle = h.address();
        s_currentSleepTask = const_cast<SleepTask *>(this);
        m_startTime = std::chrono::steady_clock::now();
    }

    void await_resume() const noexcept
    {
    }

    void maybeResume()
    {
        if (std::chrono::steady_clock::now() - m_startTime < m_duration)
            return;

        auto h = std::coroutine_handle<>::from_address(m_handle);
        s_currentSleepTask = nullptr;
        m_handle = nullptr;

        h.resume();
    }

public:
    static SleepTask *s_currentSleepTask;

private:
    mutable std::chrono::steady_clock::time_point m_startTime;
    mutable void *m_handle = nullptr;
    const std::chrono::milliseconds m_duration;
};

SleepTask *SleepTask::s_currentSleepTask = nullptr;

QCoro::Task<> CoRoutines::wait(int ms)
{
    co_await SleepTask(ms);
}

void CoRoutines::maybeResume()
{
    if (SleepTask::s_currentSleepTask)
        SleepTask::s_currentSleepTask->maybeResume();
}
