#pragma once

#include <iostream>
#include <vector>
#include "../core/ref.hpp"
#include "../core/printable_object.hpp"

namespace base
{
    class Node;
    using NodeRef = Ref<Node>;
    using NodeWeakRef = WeakRef<Node>;
    using NodeArray = std::vector<NodeRef>;
    using NodeIterator = NodeArray::iterator;
    using NodeConstIterator = NodeArray::const_iterator;

    /// @brief 节点对象
    class Node : virtual public PrintableObject, public std::enable_shared_from_this<Node>
    {
    public:
        /// @brief 创建一个节点对象
        /// @return 节点对象引用
        static NodeRef create();

    private:
        /// @brief 父级引用
        NodeWeakRef m_parent;
        /// @brief 子节点数组
        NodeArray m_children;
        /// @brief 根节点引用
        NodeWeakRef m_root;

    protected:
        Node() = default;

    public:
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
        bool is_root() const { return m_root.lock().get() == this; }
        bool has_children() const { return !m_children.empty(); }
        const NodeWeakRef &get_parent() const { return m_parent; }
        const NodeArray &get_children() const { return m_children; }
        const NodeWeakRef &get_root() const { return m_root; }

    protected:
        /// @brief 连接子节点
        /// @param node 待连接子节点
        virtual void _link_child(const NodeRef &node);

        /// @brief 与子节点断开连接
        /// @param node 子节点
        virtual void _unlink_child(const NodeRef &node);

        /// @brief 递归设置根节点
        /// @param root 根节点
        virtual void _recursive_set_root(const NodeRef &root);

        /// @brief 查找一个子节点
        /// @param node 待查找节点
        /// @return 迭代器，如果找不到则返回m_children.end()
        NodeIterator _find_child(const NodeRef &node);

        /// @brief 查找一个子节点
        /// @param node 待查找节点
        /// @return 迭代器，如果找不到则返回m_children.end()
        NodeConstIterator _find_child(const NodeRef &node) const;

        /// @brief 清除对父级的引用，但不解除父级对自身的引用
        void _reset_parent();

        /// @brief 添加一个子节点
        /// @param node 待添加节点
        void _add_child(const NodeRef &node);

        /// @brief 添加一串子节点
        /// @param begin 起始位置迭代器
        /// @param end 结束位置迭代器
        void _add_children(NodeConstIterator begin, NodeConstIterator end);

        /// @brief 移除一个子节点
        /// @param iter 待移除节点的迭代器
        void _remove_child(NodeIterator iter);

        /// @brief 移除一串子节点
        /// @param begin 起始位置迭代器
        /// @param end 结束位置迭代器
        void _remove_children(NodeConstIterator begin, NodeConstIterator end);

        /// @brief 清空子节点数组
        void _clear_children();

    public:
        /// @brief 转换成字符串
        /// @return 转换后的字符串
        std::string to_string() const override;

        /// @brief 查找子节点
        /// @param node 子节点
        /// @return 子节点的迭代器，如果找不到则返回m_children.end()
        virtual NodeIterator find_child(const NodeRef &node);

        /// @brief 查找子节点
        /// @param node 子节点
        /// @return 子节点的迭代器，如果找不到则返回m_children.end()
        virtual NodeConstIterator find_child(const NodeRef &node) const;

        /// @brief 与父节点分离，会解除双方的引用
        virtual void detach_from_parent();

        /// @brief 添加一个子节点
        /// @param node 待添加节点
        virtual void add_child(const NodeRef &node);

        /// @brief 添加一串子节点，没有检查
        /// @param node 待添加节点
        virtual void add_children(const NodeArray &children);

        /// @brief 移除一个子节点
        /// @param node 待移除节点
        virtual void remove_child(const NodeRef &node);

        /// @brief 清空自身所有子节点，没有检查
        virtual void clear_children();
    };

    /// @brief 序列化节点
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const Node &node);

    /// @brief 序列化节点
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeRef &node);

    /// @brief 序列化节点
    /// @param os 输出流
    /// @param node 待序列化节点
    /// @return 输出流
    std::ostream &operator<<(std::ostream &os, const NodeWeakRef &node);

} // namespace base
