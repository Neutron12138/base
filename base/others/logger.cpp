#include <iomanip>
#include "logger.hpp"
#include "../core/string.hpp"

namespace base
{
    template <typename... T>
    std::string Logger::format_log(LogLevel level, T... args)
    {
        std::time_t time = Clock::to_time_t(Clock::now());
        std::tm *tm = std::localtime(&time);

        std::string str = to_string(
            "[time: ", std::put_time(tm, "%Y-%m-%d %H:%M:%S"), ", ",
            "level: ", level, "]\n",
            args...);
        return to_string(
            "--------------------\n",
            str, "\n",
            "--------------------\n");
    }

    void Logger::_output_log(const std::string &content)
    {
        m_log_stream << content;

        if (m_is_standard_output_enabled)
            std::cout << content;

        if (!m_is_extra_ostream_enabled)
            return;

        for (auto &os : m_extra_ostreams)
            if (os.get().good())
                os.get() << content;
    }

    template <typename... T>
    void Logger::logu(T... args) { _output_log(format_log(LogLevel::Unknown, args...)); }

    template <typename... T>
    void Logger::logd(T... args) { _output_log(format_log(LogLevel::Debug, args...)); }

    template <typename... T>
    void Logger::logi(T... args) { _output_log(format_log(LogLevel::Info, args...)); }

    template <typename... T>
    void Logger::logw(T... args) { _output_log(format_log(LogLevel::Warning, args...)); }

    template <typename... T>
    void Logger::loge(T... args) { _output_log(format_log(LogLevel::Error, args...)); }

    std::ostream &operator<<(std::ostream &os, Logger::LogLevel level)
    {
        switch (level)
        {
        case Logger::LogLevel::Debug:
            os << "Debug";
            break;

        case Logger::LogLevel::Info:
            os << "Info";
            break;

        case Logger::LogLevel::Warning:
            os << "Warning";
            break;

        case Logger::LogLevel::Error:
            os << "Error";
            break;

        default:
            os << "Unknown";
            break;
        }
        return os;
    }

} // namespace base
