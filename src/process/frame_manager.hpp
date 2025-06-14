#pragma once

#include "../core/int.hpp"
#include "time_manager.hpp"

namespace base
{
    /// @brief 帧管理器，管理更新频率
    class FrameManager : public TimeManager
    {
    private:
        /// @brief 更新间隔，用来限制帧率
        double m_update_interval = 1.0 / 60.0;
        /// @brief 上次更新的原始时间间隔
        double m_last_update_delta = 0.0;
        /// @brief 总帧数
        UInt64 m_frame_count = 0;

    public:
        FrameManager() = default;
        ~FrameManager() override = default;

    protected:
        /// @brief 自启动以来的第一帧
        virtual void _on_first_frame() {}

        /// @brief 当距离上一帧的时间间隔大于update_interval时
        /// @param delta 经过缩放后的时间间隔
        virtual void _on_frame_updated(double delta) {}

    public:
        double get_update_interval() const { return m_update_interval; }
        void set_update_interval(double update_interval) { m_update_interval = update_interval; }
        double get_last_update_delta() const { return m_last_update_delta; }
        UInt64 get_frame_count() const { return m_frame_count; }

    protected:
        /// @brief 增加一帧
        virtual void _add_frame_count();

    public:
        /// @brief 获取当前帧率
        /// @return 当前帧率
        UInt32 get_current_fps() const;

        /// @brief 获取目标帧率
        /// @return 目标帧率
        UInt32 get_target_fps() const;

        /// @brief 设置目标帧率
        /// @param target_fps 目标帧率
        void set_target_fps(UInt32 target_fps);

        /// @brief 关闭帧率限制
        void set_unlimited_fps();

        /// @brief 请求第一帧
        virtual void request_first_frame();

        /// @brief 检查是否需要更新
        void update() override;

        /// @brief 重新开始计时
        void restart() override;
    };

} // namespace base
