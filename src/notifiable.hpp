#pragma once

#include "int.hpp"
#include "polymorphic_object.hpp"

namespace base
{
    /// @brief 可通知的对象
    class Notifiable : public PolymorphicObject
    {
    public:
        ~Notifiable() override = default;

    public:
        /// @brief 通知该对象
        /// @param notification 具体通知
        virtual void notify(Int64 notification) = 0;
    };

} // namespace base
