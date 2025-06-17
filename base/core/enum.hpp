#pragma once

#include "type.hpp"

namespace base
{
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

    /// @brief 枚举层级，共4层
    enum class EnumLevel : Enum
    {
        /// @brief 库之间分类
        Library = 1LL << 48,
        /// @brief 库内主要分类
        Major = 1LL << 32,
        /// @brief 库内次要分类
        Minor = 1LL << 16,
    };

} // namespace base
