#pragma once

namespace base
{
    /// @brief 多态对象，有虚函数表（8字节）
    class PolymorphicObject
    {
    public:
        virtual ~PolymorphicObject() = default;
    };

} // namespace base
