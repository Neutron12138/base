#include "process_manager.hpp"

namespace base
{
    void ProcessManager::_add_physics_frame_count()
    {
        m_last_physics_update_delta = get_raw_physics_elapsed();
        m_last_physics_update_time = Clock::now();
        m_physics_frame_count++;
    }

    double ProcessManager::get_raw_physics_elapsed() const
    {
        auto now = Clock::now();
        Duration duration = now - m_last_physics_update_time;
        return duration.count();
    }

    double ProcessManager::get_scaled_physics_elapsed() const
    {
        return get_raw_physics_elapsed() * get_time_scale();
    }

    UInt32 ProcessManager::get_current_physics_fps() const
    {
        return static_cast<UInt32>(1.0 / m_last_physics_update_delta);
    }

    UInt32 ProcessManager::get_target_physics_fps() const
    {
        return static_cast<UInt32>(1.0 / m_physics_update_interval);
    }

    void ProcessManager::set_target_physics_fps(UInt32 target_physics_fps)
    {
        m_physics_update_interval = 1.0 / static_cast<double>(target_physics_fps);
    }

    void ProcessManager::set_unlimited_physics_fps()
    {
        m_physics_update_interval = 0.0;
    }

    void ProcessManager::request_first_physics_frame()
    {
        if (m_physics_frame_count != 0)
            return;

        _on_first_physics_frame();
        _add_physics_frame_count();
    }

    void ProcessManager::request_first_frame()
    {
        request_first_physics_frame();
        FrameManager::request_first_frame();
    }

    void ProcessManager::update()
    {
        double elapsed = get_raw_physics_elapsed();
        if (elapsed >= m_physics_update_interval)
        {
            _on_physics_frame_updated(elapsed * get_time_scale());
            _add_physics_frame_count();
        }

        FrameManager::update();
    }

    void ProcessManager::restart()
    {
        FrameManager::restart();
        m_last_physics_update_time = Clock::now();
        m_last_physics_update_delta = 0.0;
        m_physics_frame_count = 0;
    }

} // namespace base
