#pragma once

#include "../core/ref.hpp"
#include "../core/named_object.hpp"
#include "../core/rtti_object.hpp"
#include "../process/notifiable.hpp"

namespace base
{
    class GameObject;
    using GameObjectRef = Ref<GameObject>;
    using GameObjectWeakRef = WeakRef<GameObject>;

    /// @brief 游戏对象，可以被通知，也有RTTI
    class GameObject : virtual public RTTIObjectInt64,
                       virtual public NotifiableInt64,
                       virtual public NamedObject
    {
    public:
        static constexpr Int64 TYPE_ID = 0;
        static constexpr const char *TYPE_NAME = "GameObject";

        static GameObjectRef create(const std::string &name = {}) { return std::make_shared<GameObject>(name); }

    public:
        GameObject(const std::string &name = {}) : NamedObject(name) {}
        ~GameObject() override = default;

    public:
        Int64 get_type_id() const override { return TYPE_ID; }
        virtual const char *get_type_name() const { return TYPE_NAME; }
    };

} // namespace base
