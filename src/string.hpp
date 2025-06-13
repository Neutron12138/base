#pragma once

#include <string>
#include <sstream>

namespace base
{
    /// @brief 将一串参数转换成字符串
    /// @return 空字符串
    std::string to_string() { return {}; }

    // STL中的to_string()

    std::string to_string(int value) { return std::to_string(value); }
    std::string to_string(long value) { return std::to_string(value); }
    std::string to_string(long long value) { return std::to_string(value); }
    std::string to_string(unsigned value) { return std::to_string(value); }
    std::string to_string(unsigned long value) { return std::to_string(value); }
    std::string to_string(unsigned long long value) { return std::to_string(value); }
    std::string to_string(float value) { return std::to_string(value); }
    std::string to_string(double value) { return std::to_string(value); }
    std::string to_string(long double value) { return std::to_string(value); }

    /// @brief 将一串参数转换成字符串
    /// @tparam ...Ts 参数类型
    /// @param ...args 参数
    /// @return 转换后的字符串
    template <typename... Ts>
    std::string to_string(Ts... args)
    {
        std::ostringstream oss;
        (oss << ... << args);
        return oss.str();
    }

} // namespace base
