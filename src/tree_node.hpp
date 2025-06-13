#pragma once

#include "node.hpp"

namespace base
{
    class TreeNode;
    using TreeNodeRef = Ref<TreeNode>;
    using TreeNodeWeakRef = WeakRef<TreeNode>;

    class NodeTree;
    using NodeTreeRef = Ref<NodeTree>;
    using NodeTreeWeakRef = WeakRef<NodeTree>;

    /// @brief 树节点类，用于NodeTree，不兼容Node
    class TreeNode : public Node
    {
    public:
        static NodeRef create() { return std::make_shared<TreeNode>(); }

    private:
        /// @brief 该节点是否在NodeTree中
        bool m_in_tree = false;
        /// @brief 该节点所归属的节点树
        NodeTreeWeakRef m_tree;
        /// @brief 该节点是否准备就绪
        bool m_is_ready = false;

    public:
        TreeNode() {}
        ~TreeNode() override
        {
            _reset_tree();
            Node::~Node();
        }

    protected:
        /// @brief 当进入节点树时
        /// @param tree 节点树
        virtual void _on_enter_tree(const NodeTreeRef &tree) {}

        /// @brief 当所有子节点ready时
        virtual void _on_ready() {}

        /// @brief 当退出节点树时
        /// @param tree 节点树
        virtual void _on_exit_tree(const NodeTreeRef &tree) {}

    public:
        bool is_in_tree() const { return m_in_tree; }
        const NodeTreeWeakRef &get_tree() const { return m_tree; }
        bool is_ready() const { return m_is_ready; }

    protected:
        /// @brief 清除对父级的引用，但不解除父级对自身的引用
        void _reset_parent() { Node::_reset_parent(); }

        /// @brief 解除与节点树的联系
        void _reset_tree()
        {
            m_in_tree = false;
            m_tree.reset();
        }

        /// @brief 使进入节点树
        void _enter_tree()
        {
            for (auto &child : get_children())
                dynamic_cast<TreeNode *>(child.get())->_enter_tree();
        }

        /// @brief 使准备就绪
        void _ready()
        {
            for (auto &child : get_children())
                dynamic_cast<TreeNode *>(child.get())->_ready();
        }

        /// @brief 使退出节点树
        void _exit_tree()
        {
            for (auto &child : get_children())
                dynamic_cast<TreeNode *>(child.get())->_exit_tree();
        }

    public:
        /// @brief 从节点树脱离
        virtual void detach_from_tree()
        {
            if (!m_in_tree)
                return;

            auto tree = m_tree;
            _reset_tree();
            _exit_tree();
            _on_exit_tree(tree.lock());
        }

        /// @brief 重设父节点
        /// @param new_parent 新父节点
        void reparent_to(const NodeRef &new_parent) override
        {
            if (!new_parent)
            {
                Node::reparent_to(new_parent);
                _exit_tree();
                return;
            }
        }

        /// @brief 与父节点分离，会解除双方的引用
        void detach_from_parent() override
        {
            Node::detach_from_parent();
            _reset_tree();
            _exit_tree();
        }

        /// @brief 添加一个子节点
        /// @param node 待添加节点
        void add_child(const NodeRef &node) override
        {
        }

        /// @brief 移除一个子节点
        /// @param node 待移除节点
        void remove_child(const NodeRef &node) override
        {
        }

        /// @brief 清空自身所有子节点
        void clear_children() override
        {
            for (auto &child : get_children())
            {
                dynamic_cast<TreeNode *>(child.get())->_reset_parent();
            }
        }
    };

} // namespace base
