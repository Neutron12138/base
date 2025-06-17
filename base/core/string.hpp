#pragma once

#include <string>
#include <sstream>
#include <fstream>

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

    /// @brief  从输入流中读取全部内容
    /// @param is 输入流
    /// @return 内容字符串
    std::string read_from_istream(std::istream &is)
    {
        if (!is)
            throw std::runtime_error("Invalid std::istream object");

        return std::string(
            std::istreambuf_iterator<char>(is),
            std::istreambuf_iterator<char>());
    }

    /// @brief  从文件中读取全部内容
    /// @param is 输入流
    /// @return 内容字符串
    std::string read_from_file(const std::string &filename)
    {
        std::ifstream fin;
        fin.open(filename);
        if (!fin)
            throw std::runtime_error(to_string(
                "Failed to open file: \"", filename, "\""));

        std::string result = std::string(
            std::istreambuf_iterator<char>(fin),
            std::istreambuf_iterator<char>());
        fin.close();

        return result;
    }

} // namespace base
