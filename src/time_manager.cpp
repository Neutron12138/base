#include "time_manager.hpp"

namespace base
{
    double TimeManager::get_raw_elapsed() const
    {
        auto now = Clock::now();
        Duration duration = now - m_last_update_time;
        return duration.count();
    }

    double TimeManager::get_scaled_elapsed() const
    {
        return get_raw_elapsed() * m_time_scale;
    }

    double TimeManager::get_total_elapsed() const
    {
        auto now = Clock::now();
        Duration duration = now - m_start_time;
        return duration.count();
    }

    void TimeManager::update()
    {
        m_last_update_time = Clock::now();
    }

    void TimeManager::restart()
    {
        m_start_time = Clock::now();
        m_last_update_time = Clock::now();
    }

} // namespace base
