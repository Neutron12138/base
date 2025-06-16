#pragma once

#include "type.hpp"
#include "ref.hpp"
#include "noncopyable_object.hpp"
#include "polymorphic_object.hpp"

namespace base
{
    class Resource;
    using ResourceRef = Ref<Resource>;
    using ResourceWeakRef = Ref<Resource>;

    /// @brief 不可拷贝的资源对象
    class Resource : public NoncopyableObject, public PolymorphicObject
    {
    public:
        Resource() = default;
        ~Resource() override = default;

    public:
        /// @brief 获取资源类型
        /// @return 资源类型枚举
        virtual Enum get_resource_type() const = 0;
    };

} // namespace base
