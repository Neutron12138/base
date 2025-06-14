#pragma once

#include "../core/int.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    /// @brief 可通知对象
    /// @tparam EnumT 枚举类型
    template <typename EnumT>
    class Notifiable : public PolymorphicObject
    {
    public:
        ~Notifiable() override = default;

    public:
        /// @brief 通知该对象
        /// @param notification 具体通知
        virtual void notify(EnumT notification) {}
    };

    /// @brief 通知消息为Int64的可通知对象
    using NotifiableInt64 = Notifiable<Int64>;

} // namespace base
