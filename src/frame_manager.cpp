#include "frame_manager.hpp"

namespace base
{
    void FrameManager::_add_frame_count()
    {
        m_last_update_delta = get_raw_elapsed();
        TimeManager::update();
        m_frame_count++;
    }

    UInt32 FrameManager::get_current_fps() const
    {
        return static_cast<UInt32>(1.0 / m_last_update_delta);
    }

    UInt32 FrameManager::get_target_fps() const
    {
        return static_cast<UInt32>(1.0 / m_update_interval);
    }

    void FrameManager::set_target_fps(UInt32 target_fps)
    {
        m_update_interval = 1.0 / static_cast<double>(target_fps);
    }

    void FrameManager::set_unlimited_fps()
    {
        m_update_interval = 0.0;
    }

    void FrameManager::request_first_frame()
    {
        if (m_frame_count != 0)
            return;

        _on_first_frame();
        _add_frame_count();
    }

    void FrameManager::update()
    {
        double elapsed = get_raw_elapsed();
        if (elapsed < m_update_interval)
            return;

        _on_frame_updated(elapsed * get_time_scale());
        _add_frame_count();
    }

    void FrameManager::restart()
    {
        TimeManager::restart();
        m_last_update_delta = 0.0;
        m_frame_count = 0;
    }

} // namespace base
