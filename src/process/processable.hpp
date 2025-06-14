#pragma once

#include "../core/int.hpp"
#include "../core/ref.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    class ProcessManager;
    using ProcessManagerRef = Ref<ProcessManager>;

    /// @brief 可处理的对象
    class Processable : public PolymorphicObject
    {
    public:
        /// @brief 处理模式
        enum class ProcessMode : Int32
        {
            /// @brief 永远不处理
            Disabled,
            /// @brief 永远处理
            Always,
            /// @brief 仅在非暂停时处理
            Pausable,
            /// @brief 仅在暂停时处理
            WhenPaused,
        };

    private:
        /// @brief 处理模式
        ProcessMode m_process_mode = ProcessMode::Pausable;
        /// @brief 管理器对象指针
        ProcessManagerRef m_process_manager;
        /// @brief 启用空闲帧处理
        bool m_enable_process = true;
        /// @brief 启用物理帧处理
        bool m_enable_physics_process = true;

    public:
        Processable(const ProcessManagerRef &process_manager) : m_process_manager(process_manager) {}
        ~Processable() override = default;

    protected:
        /// @brief 空闲帧处理
        /// @param delta 距上一次处理经过的时间
        virtual void _process(double delta) {}

        /// @brief 物理帧处理
        /// @param delta 距上一次处理经过的时间
        virtual void _physics_process(double delta) {}

    public:
        void set_process_mode(ProcessMode mode) { m_process_mode = mode; }
        ProcessMode get_process_mode() const { return m_process_mode; }
        void set_process_manager(const ProcessManagerRef &process_manager) { m_process_manager = process_manager; }
        const ProcessManagerRef &get_process_manager() const { return m_process_manager; }
        void set_process(bool enable_process) { m_enable_process = enable_process; }
        bool is_process_enabled() const { return m_enable_process; }
        void set_physics_process(bool enable_physics_process) { m_enable_physics_process = enable_physics_process; }
        bool is_physics_process_enabled() const { return m_enable_physics_process; }

    public:
        /// @brief 根据process_mode与paused判断是否需要处理
        /// @return 是否需要处理
        bool is_need_process() const;

        /// @brief 请求进行空闲帧处理，受enable_process控制
        /// @param delta 距上一次处理经过的时间
        void request_process(double delta);

        /// @brief 请求进行物理帧处理，受enable_physics_process控制
        /// @param delta 距上一次处理经过的时间
        void request_physics_process(double delta);
    };

} // namespace base
