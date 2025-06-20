#pragma once

#include "../core/type.hpp"
#include "../core/ref.hpp"
#include "../core/noncopyable_object.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    class Resource;
    using ResourceRef = Ref<Resource>;
    using ResourceWeakRef = Ref<Resource>;

    /// @brief 不可拷贝的资源对象
    class Resource : public NoncopyableObject,
                     virtual public PolymorphicObject
    {
    public:
        Resource() = default;
        ~Resource() override = default;

    public:
        /// @brief 获取资源类型
        /// @return 资源类型枚举
        virtual Int64 get_resource_type() const = 0;
    };

} // namespace base
