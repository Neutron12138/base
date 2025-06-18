#pragma once

#include "processable.hpp"
#include "frame_manager.hpp"

namespace base
{
    /// @brief 处理管理器
    class ProcessManager : virtual public FrameManager
    {
    public:
        /// @brief 创建一个ProcessManager对象
        /// @return 对象引用
        static ProcessManagerRef create() { return std::make_shared<ProcessManager>(); }

    private:
        /// @brief 是否暂停
        bool m_paused = false;
        /// @brief 时间缩放
        double m_time_scale = 1.0;
        /// @brief 上次物理帧更新时间
        TimePoint m_last_physics_update_time = get_current_time();
        /// @brief 物理更新间隔，用来限制物理帧帧率
        double m_physics_update_interval = 1.0 / 60.0;
        /// @brief 上次物理更新的时间间隔
        double m_last_physics_update_delta = 0.0;
        /// @brief 总物理帧数
        Size m_physics_frame_count = 0;

    public:
        ProcessManager() = default;
        ~ProcessManager() override = default;

    protected:
        /// @brief 自启动以来的第一帧
        virtual void _on_first_physics_frame() {}

        /// @brief 当物理帧更新时
        /// @param delta 时间间隔
        virtual void _on_physics_frame_updated(double delta) {}

    public:
        void set_paused(bool paused) { m_paused = paused; }
        bool is_paused() const { return m_paused; }
        double get_time_scale() const { return m_time_scale; }
        void set_time_scale(double time_scale) { m_time_scale = time_scale; }
        const TimePoint &get_last_physics_update_time() const { return m_last_physics_update_time; }
        double get_physics_update_interval() const { return m_physics_update_interval; }
        void set_physics_update_interval(double physics_update_interval) { m_physics_update_interval = physics_update_interval; }
        double get_last_physics_update_delta() const { return m_last_physics_update_delta; }
        Size get_physics_frame_count() const { return m_physics_frame_count; }

    protected:
        /// @brief 增加一帧
        virtual void _add_physics_frame_count();

    public:
        /// @brief 获取当前物理帧帧率
        /// @return 当前物理帧帧率
        FPS get_current_physics_fps() const { return static_cast<FPS>(1.0 / m_last_physics_update_delta); }

        /// @brief 获取目标物理帧帧率
        /// @return 目标物理帧帧率
        FPS get_target_physics_fps() const { return static_cast<FPS>(1.0 / m_physics_update_interval); }

        /// @brief 设置目标物理帧帧率
        /// @param target_physics_fps 目标物理帧帧率
        void set_target_physics_fps(FPS target_physics_fps) { m_physics_update_interval = 1.0 / static_cast<double>(target_physics_fps); }

        /// @brief 关闭物理帧帧率限制
        void set_unlimited_physics_fps() { m_physics_update_interval = 0.0; }

        /// @brief 获取距离上一物理帧所经过的时间
        /// @return 距离上一物理帧所经过的时间
        double get_physics_update_delta() const { return Duration(get_current_time() - m_last_physics_update_time).count(); }

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
