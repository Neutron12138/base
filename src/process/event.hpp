#pragma once

#include "../core/int.hpp"
#include "../core/ref.hpp"

namespace base
{
    class Event;
    using EventRef = Ref<Event>;

    /// @brief 事件基类
    class Event
    {
    private:
        /// @brief 该事件是否已经被处理
        bool m_handled = false;

    public:
        Event() = default;
        ~Event() = default;

    public:
        void set_handled() { m_handled = true; }
        bool is_handled() const { return m_handled; }
    };

} // namespace base
