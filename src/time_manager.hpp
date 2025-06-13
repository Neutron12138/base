#pragma once

#include <chrono>
#include "polymorphic_object.hpp"

namespace base
{
    /// @brief 时间管理器
    class TimeManager : public PolymorphicObject
    {
    public:
        using Clock = std::chrono::system_clock;
        using TimePoint = Clock::time_point;
        using Duration = std::chrono::duration<double>;

    private:
        /// @brief 开始时间
        TimePoint m_start_time = Clock::now();
        /// @brief 上次更新时间
        TimePoint m_last_update_time = Clock::now();
        /// @brief 时间缩放
        double m_time_scale = 1.0;

    public:
        TimeManager() = default;
        ~TimeManager() override = default;

    public:
        const TimePoint &get_start_time() const { return m_start_time; }
        const TimePoint &get_last_update_time() const { return m_last_update_time; }
        double get_time_scale() const { return m_time_scale; }
        void set_time_scale(double time_scale) { m_time_scale = time_scale; }

    public:
        /// @brief 获取自last_update_time以来经过的时间
        /// @return 未经过缩放的时间
        double get_raw_elapsed() const;

        /// @brief 获取自last_update_time以来经过的时间，但是会被time_scale缩放
        /// @return 经过缩放的时间
        double get_scaled_elapsed() const;

        /// @brief 获取自start_time以来总共经过的时间
        /// @return 未经过缩放的时间
        double get_total_elapsed() const;

        /// @brief 更新last_update_time
        virtual void update();

        /// @brief 重新开始计时
        virtual void restart();
    };

} // namespace base
