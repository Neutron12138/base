#pragma once

#include "event.hpp"

namespace base
{
    /// @brief 事件处理器
    class EventHandler : virtual public PolymorphicObject
    {
    private:
        /// @brief 是否启用事件处理
        bool m_is_event_handling_enabled = true;

    public:
        EventHandler() = default;
        ~EventHandler() override = default;

    protected:
        /// @brief 处理事件
        /// @param event 待处理事件
        virtual void _handle_event(const EventRef &event) = 0;

    public:
        bool is_event_handling_enabled() const { return m_is_event_handling_enabled; }
        void set_event_handling_enabled(bool enabled) { m_is_event_handling_enabled = enabled; }

    public:
        /// @brief 请求处理事件
        /// @param event 待处理事件
        void request_handle_event(const EventRef &event)
        {
            if (m_is_event_handling_enabled)
                _handle_event(event);
        }
    };

} // namespace base
