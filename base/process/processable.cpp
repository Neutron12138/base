#include "../core/exception.hpp"
#include "processable.hpp"
#include "process_manager.hpp"

#define BASE_PROCESSABLE_MAKE_ERROR(message) \
    BASE_MAKE_RUNTIME_ERROR(message)

namespace base
{
    bool Processable::is_need_process() const
    {
        auto manager = m_process_manager.lock();
        if (!manager)
            throw BASE_PROCESSABLE_MAKE_ERROR("The ProcessManager object is a null pointer");

        switch (m_process_mode)
        {
        case ProcessMode::Always:
            return true;

        case ProcessMode::Pausable:
            return !manager->is_paused();

        case ProcessMode::WhenPaused:
            return manager->is_paused();

        default:
            return false;
        }
    }

    void Processable::request_process()
    {
        auto manager = m_process_manager.lock();
        if (!manager)
            throw BASE_PROCESSABLE_MAKE_ERROR("The ProcessManager object is a null pointer");

        if (is_need_process() && m_is_process_enabled)
            _process(manager->get_last_update_delta() * manager->get_time_scale());
    }

    void Processable::request_physics_process()
    {
        auto manager = m_process_manager.lock();
        if (!manager)
            throw BASE_PROCESSABLE_MAKE_ERROR("The ProcessManager object is a null pointer");

        if (is_need_process() && m_is_physics_process_enabled)
            _physics_process(manager->get_last_physics_update_delta() * manager->get_time_scale());
    }

} // namespace base
