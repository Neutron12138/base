#pragma once

#include "event.hpp"

namespace base
{
    /// @brief 事件处理器
    class EventHandler : public PolymorphicObject
    {
    private:
        /// @brief 启用事件处理
        bool m_enable_handle_event = true;

    public:
        EventHandler() = default;
        ~EventHandler() override = default;

    protected:
        /// @brief 处理事件
        /// @param event 待处理事件
        virtual void _handle_event(const EventRef &event) {}

    public:
        bool is_handle_event_enabled() const { return m_enable_handle_event; }
        void set_handle_event(bool enable_handle_event) { m_enable_handle_event = enable_handle_event; }

    public:
        /// @brief 请求处理事件
        /// @param event 待处理事件
        void request_handle_event(const EventRef &event)
        {
            if (m_enable_handle_event)
                _handle_event(event);
        }
    };

} // namespace base
