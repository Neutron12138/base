#pragma once

#include <vector>
#include <algorithm>
#include "../core/ref.hpp"
#include "../core/polymorphic_object.hpp"

namespace base
{
    class Node;
    using NodeRef = Ref<Node>;
    using NodeWeakRef = WeakRef<Node>;
    using NodeArray = std::vector<NodeRef>;
    using NodeIterator = NodeArray::iterator;

    /// @brief 节点对象
    class Node : public PolymorphicObject, public std::enable_shared_from_this<Node>
    {
    public:
        /// @brief 创建一个节点对象
        /// @return 节点对象引用
        static NodeRef create() { return std::make_shared<Node>(); }

    private:
        /// @brief
        NodeWeakRef m_parent;
        /// @brief
        NodeArray m_children;

    public:
        Node() = default;
        ~Node() override = default;

    protected:
        /// @brief 当被附加到父级节点时
        /// @param new_parent 新父级
        virtual void _on_attached_to_parent(const NodeRef &new_parent) {}

        /// @brief 当从父级节点脱离时
        /// @param old_parent 旧父级
        virtual void _on_detached_from_parent(const NodeRef &old_parent) {}

    public:
        bool is_child() const { return !m_parent.expired(); }
        bool is_root() const { return m_parent.expired(); }
        bool has_children() const { return !m_children.empty(); }
        const NodeWeakRef &get_parent() const { return m_parent; }
        const NodeArray &get_children() const { return m_children; }

    protected:
        /// @brief 查找一个子节点（无检查）
        /// @param node 待查找节点
        /// @return 迭代器，如果找不到则返回m_children.end()
        NodeIterator _find_child(const NodeRef &node);

        /// @brief 清除对父级的引用，但不解除父级对自身的引用
        void _reset_parent();

        /// @brief 移除一个子节点（无检查）
        /// @param iter 待移除节点的迭代器
        void _remove_child(NodeIterator iter);

        /// @brief 移除一个子节点（无检查）
        /// @param node 待移除节点
        void _remove_child(const NodeRef &node);

        /// @brief 添加一个子节点（无检查）
        /// @param node 待添加节点
        void _add_child(const NodeRef &node);

        /// @brief 清空子节点数组
        void _clear_children();

    public:
        /// @brief 重设父节点
        /// @param new_parent 新父节点
        virtual void reparent_to(const NodeRef &new_parent);

        /// @brief 与父节点分离，会解除双方的引用
        virtual void detach_from_parent();

        /// @brief 添加一个子节点
        /// @param node 待添加节点
        virtual void add_child(const NodeRef &node);

        /// @brief 移除一个子节点
        /// @param node 待移除节点
        virtual void remove_child(const NodeRef &node);

        /// @brief 清空自身所有子节点
        virtual void clear_children();
    };

} // namespace base
