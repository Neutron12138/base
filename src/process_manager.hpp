#pragma once

#include "processable.hpp"
#include "frame_manager.hpp"

namespace base
{
    /// @brief 处理管理器
    class ProcessManager : public FrameManager
    {
    private:
        /// @brief 是否暂停
        bool m_paused = false;
        /// @brief 上次物理帧更新时间
        TimePoint m_last_physics_update_time = Clock::now();
        /// @brief 物理更新间隔，用来限制物理帧帧率
        double m_physics_update_interval = 1.0 / 60.0;
        /// @brief 上次物理更新的原始时间间隔
        double m_last_physics_update_delta = 0.0;
        /// @brief 总物理帧数
        UInt64 m_physics_frame_count = 0;

    public:
        ProcessManager() = default;
        ~ProcessManager() override = default;

    protected:
        /// @brief 自启动以来的第一帧
        virtual void _on_first_physics_frame() {}

        /// @brief 当距离上一帧的时间间隔大于physics_update_interval时
        /// @param delta 经过缩放后的时间间隔
        virtual void _on_physics_frame_updated(double delta) {}

    public:
        void set_paused(bool paused) { m_paused = paused; }
        bool is_paused() const { return m_paused; }

    public:
        const TimePoint &get_last_physics_update_time() const { return m_last_physics_update_time; }
        double get_physics_update_interval() const { return m_physics_update_interval; }
        void set_physics_update_interval(double physics_update_interval) { m_physics_update_interval = physics_update_interval; }
        double get_last_physics_update_delta() const { return m_last_physics_update_delta; }
        UInt64 get_physics_frame_count() const { return m_physics_frame_count; }

    protected:
        /// @brief 增加一帧
        virtual void _add_physics_frame_count();

    public:
        /// @brief 获取自last_physics_update_time以来经过的时间
        /// @return 未经过缩放的时间
        double get_raw_physics_elapsed() const;

        /// @brief 获取自last_physics_update_time以来经过的时间，但是会被time_scale缩放
        /// @return 经过缩放的时间
        double get_scaled_physics_elapsed() const;

        /// @brief 获取当前物理帧帧率
        /// @return 当前物理帧帧率
        UInt32 get_current_physics_fps() const;

        /// @brief 获取目标物理帧帧率
        /// @return 目标物理帧帧率
        UInt32 get_target_physics_fps() const;

        /// @brief 设置目标物理帧帧率
        /// @param target_physics_fps 目标物理帧帧率
        void set_target_physics_fps(UInt32 target_physics_fps);

        /// @brief 关闭物理帧帧率限制
        void set_unlimited_physics_fps();

        /// @brief 请求第一物理帧
        virtual void request_first_physics_frame();

        /// @brief 请求第一帧
        void request_first_frame() override;

        /// @brief 检查是否需要更新
        void update() override;

        /// @brief 重新开始计时
        void restart() override;
    };

} // namespace base
