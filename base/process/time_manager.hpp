#pragma once

#include <chrono>
#include "../core/polymorphic_object.hpp"

namespace base
{
    /// @brief 时间管理器
    /// @tparam ClockType 时钟类型，默认为std::chrono::steady_clock
    template <typename ClockType = std::chrono::steady_clock>
    class TimeManager : public PolymorphicObject
    {
    public:
        /// @brief 时钟
        using Clock = ClockType;
        /// @brief 时间点
        using TimePoint = typename Clock::time_point;
        /// @brief 时间段
        using Duration = std::chrono::duration<double>;

        /// @brief 获取当前时间
        /// @return 当前时间
        static TimePoint get_current_time() { return Clock::now(); }

    private:
        /// @brief 开始时间
        TimePoint m_start_time = get_current_time();

    public:
        TimeManager() = default;
        ~TimeManager() override = default;

    public:
        const TimePoint &get_start_time() const { return m_start_time; }

    public:
        /// @brief 获取自start_time以来总共经过的时间
        /// @return 经过的时间（秒）
        double get_total_elapsed() const { return Duration(get_current_time() - m_start_time).count(); }

        /// @brief 重新开始计时
        virtual void restart() { m_start_time = get_current_time(); }
    };

} // namespace base
