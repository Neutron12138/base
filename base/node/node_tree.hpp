#pragma once

#include "../core/int.hpp"
#include "tree_node.hpp"

namespace base
{
    /// @brief 节点树
    class NodeTree : public PolymorphicObject, public std::enable_shared_from_this<NodeTree>
    {
    public:
        /// @brief 节点树状态
        enum class Status : Int32
        {
            /// @brief 尚未初始化
            Uninitialized,
            /// @brief 正在初始化
            Initializing,
            /// @brief 已就绪
            Ready,
        };

        /// @brief 创建一个节点树
        /// @return 节点树引用
        static NodeTreeRef create();

    private:
        /// @brief 根节点
        TreeNodeRef m_root;
        /// @brief 当前状态
        Status m_status = Status::Uninitialized;

    protected:
        NodeTree() = default;

    public:
        ~NodeTree() override
        {
            if (!m_root)
                return;

            m_root->clear_children();
        }

    protected:
        /// @brief 当节点树初始化时
        virtual void _on_initialize() {}

        /// @brief 当节点树就绪时
        virtual void _on_ready() {}

        /// @brief 当节点树结束时
        virtual void _on_finalize() {}

    public:
        const TreeNodeRef &get_root() const { return m_root; }
        Status get_status() const { return m_status; }

    protected:
        /// @brief 强行设为根节点
        /// @param root 待设置根节点
        void _set_root(const TreeNodeRef &root);

        /// @brief 强行移除根节点
        void _remove_root();

    public:
        /// @brief 请求节点树初始化
        virtual void request_initialize();

        /// @brief 请求节点树结束
        virtual void request_finalize();
    };

} // namespace base
