#pragma once

#include "int.hpp"
#include "polymorphic_object.hpp"

namespace base
{
    /// @brief 能够在运行时获取类型的对象
    /// @tparam EnumT 枚举类型
    template <typename EnumT>
    class RTTIObject : public PolymorphicObject
    {
    public:
        ~RTTIObject() override = default;

    public:
        /// @brief 获取对象类型ID
        /// @return 类型ID
        virtual EnumT get_type_id() const = 0;
    };

    /// @brief 类型信息为Int64的RTTI对象
    using RTTIObjectInt64 = RTTIObject<Int64>;

} // namespace base
