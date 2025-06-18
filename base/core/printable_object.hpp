#pragma once

#include <string>
#include <iostream>
#include "polymorphic_object.hpp"

namespace base
{
    /// @brief 可打印的对象
    class PrintableObject : virtual public PolymorphicObject
    {
    public:
        PrintableObject() = default;
        ~PrintableObject() override = default;

    public:
        /// @brief 转换成字符串
        /// @return 转换后的字符串
        virtual std::string to_string() const = 0;
    };

    std::ostream &operator<<(std::ostream &os, const PrintableObject &printable)
    {
        os << printable.to_string();
        return os;
    }

} // namespace base
