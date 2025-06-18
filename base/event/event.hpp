#pragma once

#include "../core/type.hpp"
#include "../core/ref.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    class Event;
    using EventRef = Ref<Event>;
    using EventWeakRef = WeakRef<Event>;

    /// @brief 事件基类
    class Event : public PolymorphicObject
    {
    private:
        /// @brief 该事件是否已经被处理
        bool m_handled = false;

    public:
        Event() = default;
        ~Event() override = default;

    public:
        bool is_handled() const { return m_handled; }
        void set_handled() { m_handled = true; }

    public:
        /// @brief 获取事件类型
        /// @return 事件类型
        virtual Int64 get_event_type() const = 0;
    };

} // namespace base
