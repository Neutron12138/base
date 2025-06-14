#include "processable.hpp"
#include "process_manager.hpp"

namespace base
{
    bool Processable::is_need_process() const
    {
        switch (m_process_mode)
        {
        case ProcessMode::Always:
            return true;

        case ProcessMode::Pausable:
            return !m_process_manager->is_paused();

        case ProcessMode::WhenPaused:
            return m_process_manager->is_paused();

        default:
            return false;
        }
    }

    void Processable::request_process(double delta)
    {
        if (is_need_process() && m_enable_process)
            _process(delta);
    }

    void Processable::request_physics_process(double delta)
    {
        if (is_need_process() && m_enable_physics_process)
            _physics_process(delta);
    }

} // namespace base
