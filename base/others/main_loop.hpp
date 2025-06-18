#pragma once

#include <cstdlib>
#include "../core/type.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    /// @brief 主循环
    class MainLoop : virtual public PolymorphicObject
    {
    public:
        /// @brief 主循环的状态
        enum class Status : Int32
        {
            /// @brief 尚未初始化
            Uninitialized,
            /// @brief 正在初始化
            Initializing,
            /// @brief 正在运行
            Running,
            /// @brief 正在关闭
            ShuttingDown,
            /// @brief 已关闭
            Terminated,
        };

    private:
        /// @brief 当前状态
        Status m_status = Status::Uninitialized;
        /// @brief 程序退出码
        Int32 m_exit_code = EXIT_SUCCESS;

    public:
        MainLoop() = default;
        ~MainLoop() override = default;

    protected:
        /// @brief 当程序初始化时
        virtual void _on_initialize() = 0;

        /// @brief 当更新时
        virtual void _on_update() = 0;

        /// @brief 当程序结束时
        virtual void _on_shutdown() = 0;

    public:
        Status get_status() const { return m_status; }
        void set_exit_code(Int32 exit_code = EXIT_FAILURE) { m_exit_code = exit_code; }
        Int32 get_exit_code() const { return m_exit_code; }

    protected:
        /// @brief 设置当前状态
        /// @param status 目标状态
        void _set_status(Status status) { m_status = status; }

    public:
        /// @brief 请求退出
        virtual void request_quit()
        {
            if (m_status != Status::Terminated)
                m_status = Status::ShuttingDown;
        }

        /// @brief 主运行逻辑
        virtual void run()
        {
            if (m_status != Status::Uninitialized)
                return;

            m_status = Status::Initializing;
            _on_initialize();

            m_status = Status::Running;
            while (m_status == Status::Running)
                _on_update();

            m_status = Status::ShuttingDown;
            _on_shutdown();

            m_status = Status::Terminated;
        }
    };

} // namespace base
