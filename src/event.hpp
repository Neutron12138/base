#pragma once

#include "int.hpp"
#include "ref.hpp"
#include "polymorphic_object.hpp"

namespace base
{
    class Event;
    using EventRef = Ref<Event>;

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
        void set_handled() { m_handled = true; }
        bool is_handled() const { return m_handled; }

    public:
        /// @brief 获取事件类型
        /// @return 事件类型
        virtual Int64 type() const = 0;
    };

} // namespace base
