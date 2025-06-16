#pragma once

#include <cstdint>

namespace base
{
    /// @brief 8位有符号整数
    using Int8 = std::int8_t;
    /// @brief 19位有符号整数
    using Int16 = std::int16_t;
    /// @brief 32位有符号整数
    using Int32 = std::int32_t;
    /// @brief 64位有符号整数
    using Int64 = std::int64_t;

    /// @brief 8位无符号整数
    using UInt8 = std::uint8_t;
    /// @brief 16位无符号整数
    using UInt16 = std::uint16_t;
    /// @brief 32位无符号整数
    using UInt32 = std::uint32_t;
    /// @brief 64位无符号整数
    using UInt64 = std::uint64_t;

    /// @brief 大小类型
    using Size = std::size_t;

#ifdef BASE_ENUM_USE_INT32
    /// @brief 枚举类型
    using Enum = Int32;
    /// @brief 位标志类型
    using Flag = UInt32;
#else
    /// @brief 枚举类型
    using Enum = Int64;
    /// @brief 位标志类型
    using Flag = UInt64;
#endif

#ifdef BASE_DEFINE_FLOAT_TYPE
    /// @brief 32位浮点数
    using Float32 = float;
    /// @brief 64位浮点数
    using Float64 = double;
#if __SIZEOF_LONG_DOUBLE__ == 16
    /// @brief 128位浮点数
    using Float128 = long double;
#endif
#endif

} // namespace base
