#include "frame_manager.hpp"

namespace base
{
    void FrameManager::_add_frame_count()
    {
        m_last_update_delta = get_update_delta();
        m_last_update_time = get_current_time();
        m_frame_count++;
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
        // 计算距离上一帧经过的时间
        double delta = get_update_delta();
        if (delta < m_update_interval)
            return;

        _on_frame_updated(delta);
        _add_frame_count();
    }

    void FrameManager::restart()
    {
        TimeManager::restart();
        m_last_update_time = get_current_time();
        m_last_update_delta = 0.0;
        m_frame_count = 0;
    }

} // namespace base
