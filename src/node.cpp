#include <stdexcept>
#include "string.hpp"
#include "node.hpp"

namespace base
{
    NodeArray::iterator Node::_find_child(const NodeRef &node)
    {
        return std::find(m_children.begin(), m_children.end(), node);
    }

    void Node::_reset_parent()
    {
        m_parent.reset();
    }

    void Node::_remove_child(NodeArray::iterator &iter)
    {
        // 解除子节点对本节点的引用
        (*iter)->_reset_parent();
        // 解除本节点对子节点的引用
        m_children.erase(iter);
    }

    void Node::_remove_child(const NodeRef &node)
    {
        auto iter = _find_child(node);
        if (iter == m_children.end())
            return;

        _remove_child(iter);
    }

    void Node::_add_child(const NodeRef &node)
    {
        // 添加对子节点的引用
        m_children.push_back(node);
        // 重设子节点父级
        node->m_parent = shared_from_this();
    }

    void Node::_clear_children()
    {
        m_children.clear();
    }

    void Node::reparent_to(const NodeRef &new_parent)
    {
        // 父节点不能是空对象
        if (!new_parent)
            throw std::runtime_error("The new parent cannot be a null object");
        // 父节点不能是自己
        if (new_parent.get() == this)
            throw std::runtime_error("Cannot reparent to self");

        NodeRef old_parent = m_parent.lock();
        auto self = shared_from_this();

        // 新父节点与原父节点相同则返回
        if (old_parent == new_parent)
            return;

        // 如果原先有父级
        if (is_child())
        {
            old_parent->_remove_child(self);
            _on_detached_from_parent(old_parent);
        }

        new_parent->_add_child(self);
        _on_attached_to_parent(new_parent);
    }

    void Node::detach_from_parent()
    {
        if (is_root())
            return;

        NodeRef old_parent = m_parent.lock();
        old_parent->_remove_child(shared_from_this());
        _on_detached_from_parent(old_parent);
    }

    void Node::add_child(const NodeRef &node)
    {
        // 待添加节点不能是空对象
        if (!node)
            throw std::runtime_error("Cannot add a null object as a child node");
        // 待添加节点不能是自己
        if (node.get() == this)
            throw std::runtime_error("Cannot add self as a child node");
        // 待添加节点必须是独立的
        if (node->is_child())
            throw std::runtime_error("Cannot add an existing parent node as a child node");

        _add_child(node);
        node->_on_attached_to_parent(shared_from_this());
    }

    void Node::remove_child(const NodeRef &node)
    {
        // 待移除节点不能是空对象
        if (!node)
            throw std::runtime_error("Cannot remove a null object");

        _remove_child(node);
        node->_on_detached_from_parent(shared_from_this());
    }

    void Node::clear_children()
    {
        auto self = shared_from_this();
        for (auto &child : m_children)
        {
            // 子节点断开对父级的连接
            child->m_parent.reset();
            child->_on_detached_from_parent(self);
        }

        // 断开对子节点的连接
        _clear_children();
    }

} // namespace base
