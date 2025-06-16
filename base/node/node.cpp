#include <stdexcept>
#include <algorithm>
#include "node.hpp"
#include "../core/string.hpp"

namespace base
{
    //
    // 受保护的接口
    //

    void Node::_link_child(const NodeRef &node)
    {
        node->m_parent = shared_from_this();
    }

    void Node::_unlink_child(const NodeRef &node)
    {
        node->m_parent.reset();
    }

    NodeIterator Node::_find_child(const NodeRef &node)
    {
        return std::find(m_children.begin(), m_children.end(), node);
    }

    NodeConstIterator Node::_find_child(const NodeRef &node) const
    {
        return std::find(m_children.cbegin(), m_children.cend(), node);
    }

    void Node::_reset_parent()
    {
        m_parent.reset();
    }

    void Node::_add_child(const NodeRef &node)
    {
        m_children.push_back(node);
    }

    void Node::_add_children(NodeConstIterator begin, NodeConstIterator end)
    {
        m_children.insert(m_children.end(), begin, end);
    }

    void Node::_remove_child(NodeIterator iter)
    {
        m_children.erase(iter);
    }

    void Node::_remove_children(NodeConstIterator begin, NodeConstIterator end)
    {
        m_children.erase(begin, end);
    }

    void Node::_clear_children()
    {
        m_children.clear();
    }

    //
    // 公共接口
    //

    NodeIterator Node::find_child(const NodeRef &node)
    {
        // 不能查找空对象
        if (!node)
            throw std::runtime_error("Unable to find an invalid object");
        // 只能查找子节点
        if (node->get_parent().lock().get() != this)
            throw std::runtime_error("This node is not its parent");
        // 子节点有对父节点的引用，但是父节点没有对子节点的引用
        auto iter = _find_child(node);
        if (iter == m_children.end())
            throw std::logic_error(to_string("Unable to find the node: ", node.get()));

        return iter;
    }

    NodeConstIterator Node::find_child(const NodeRef &node) const
    {
        // 不能查找空对象
        if (!node)
            throw std::runtime_error("Unable to find an invalid object");
        // 只能查找子节点
        if (node->get_parent().lock().get() != this)
            throw std::runtime_error("This node is not its parent");
        // 子节点有对父节点的引用，但是父节点没有对子节点的引用
        auto iter = _find_child(node);
        if (iter == m_children.cend())
            throw std::logic_error(to_string("Unable to find the node: ", node.get()));

        return iter;
    }

    void Node::detach_from_parent()
    {
        if (is_root())
            return;

        NodeRef old_parent = m_parent.lock();
        auto self = shared_from_this();

        auto iter = old_parent->find_child(self);
        old_parent->_remove_child(iter);
        old_parent->_unlink_child(self);
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
        _link_child(node);
        node->_on_attached_to_parent(shared_from_this());
    }

    void Node::add_children(const NodeArray &children)
    {
        _add_children(children.cbegin(), children.cend());
        for (auto &child : children)
            _link_child(child);
    }

    void Node::remove_child(const NodeRef &node)
    {
        // 待移除节点不能是空对象
        if (!node)
            throw std::runtime_error("Cannot remove a null object");
        // 只能移除子节点
        if (node->get_parent().lock().get() != this)
            throw std::runtime_error("This node is not its parent");
        // 子节点有对父节点的引用，但是父节点没有对子节点的引用
        auto iter = _find_child(node);
        if (iter == m_children.end())
            throw std::logic_error(to_string("Unable to find the node: ", node.get()));

        _remove_child(iter);
        _unlink_child(node);
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
