#pragma once

#include "../core/type.hpp"
#include "../core/ref.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    class Notifiable;
    using NotifiableRef = Ref<Notifiable>;
    using NotifiableWeakRef = WeakRef<Notifiable>;

    /// @brief 可通知对象
    class Notifiable : virtual public PolymorphicObject
    {
    public:
        Notifiable() = default;
        ~Notifiable() override = default;

    public:
        /// @brief 通知该对象
        /// @param what 具体通知
        virtual void notification(Int64 what) = 0;
    };

    /// @brief 通知一个对象
    /// @param notifiable 待通知对象
    /// @param what 具体通知
    void notify(const NotifiableRef &notifiable, Int64 what)
    {
        notifiable->notification(what);
    }

} // namespace base
