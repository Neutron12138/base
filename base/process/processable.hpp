#pragma once

#include "../core/enum.hpp"
#include "../core/ref.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    class ProcessManager;
    using ProcessManagerRef = Ref<ProcessManager>;
    using ProcessManagerWeakRef = WeakRef<ProcessManager>;

    /// @brief 可处理的对象
    class Processable : public PolymorphicObject
    {
    public:
        /// @brief 处理模式
        enum class ProcessMode : Enum
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
        ProcessManagerWeakRef m_process_manager;
        /// @brief 启用空闲帧处理
        bool m_is_process_enabled = true;
        /// @brief 启用物理帧处理
        bool m_is_physics_process_enabled = true;

    public:
        Processable(const ProcessManagerWeakRef &process_manager) : m_process_manager(process_manager) {}
        ~Processable() override = default;

    protected:
        /// @brief 空闲帧处理
        /// @param delta 距上一次处理经过的时间，会受到time_scale影响
        virtual void _process(double delta) = 0;

        /// @brief 物理帧处理
        /// @param delta 距上一次处理经过的时间，会受到time_scale影响
        virtual void _physics_process(double delta) = 0;

    public:
        void set_process_mode(ProcessMode mode) { m_process_mode = mode; }
        ProcessMode get_process_mode() const { return m_process_mode; }
        void set_process_manager(const ProcessManagerWeakRef &process_manager) { m_process_manager = process_manager; }
        const ProcessManagerWeakRef &get_process_manager() const { return m_process_manager; }
        void set_process(bool enabled) { m_is_process_enabled = enabled; }
        bool is_process_enabled() const { return m_is_process_enabled; }
        void set_physics_process(bool enabled) { m_is_physics_process_enabled = enabled; }
        bool is_physics_process_enabled() const { return m_is_physics_process_enabled; }

    public:
        /// @brief 根据process_mode与paused判断是否需要处理
        /// @return 是否需要处理
        bool is_need_process() const;

        /// @brief 请求进行空闲帧处理，受enable_process控制
        /// @param delta 距上一次处理经过的时间
        void request_process();

        /// @brief 请求进行物理帧处理，受enable_physics_process控制
        /// @param delta 距上一次处理经过的时间
        void request_physics_process();
    };

} // namespace base
