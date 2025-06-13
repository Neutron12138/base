#include <exception>
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
        (*iter)->_reset_parent();
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
        m_children.push_back(node);
        node->m_parent = shared_from_this();
    }

    void Node::_clear_children()
    {
        m_children.clear();
    }

    void Node::reparent_to(const NodeRef &new_parent)
    {
        if (new_parent.get() == this)
            throw std::runtime_error("Cannot reparent to self");

        NodeRef old_parent = m_parent.lock();
        auto self = shared_from_this();

        if (old_parent == new_parent)
            return;

        if (is_child())
        {
            old_parent->_remove_child(self);
            _on_detached_from_parent(old_parent);
        }

        if (new_parent)
        {
            new_parent->_add_child(self);
            _on_attached_to_parent(new_parent);
        }
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
        if (!node)
            throw std::runtime_error("Cannot add a null object as a child node");
        if(node.get()==this)
        throw std::runtime_error("Cannot add self as a child node");

        NodeRef old_parent = node->m_parent.lock();

        if (old_parent.get() == this)
            return;

        if (old_parent)
        {
            old_parent->_remove_child(node);
            node->_on_detached_from_parent(old_parent);
        }

        _add_child(node);
        node->_on_attached_to_parent(shared_from_this());
    }

    void Node::remove_child(const NodeRef &node)
    {
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
            child->m_parent.reset();
            child->_on_detached_from_parent(self);
        }
        _clear_children();
    }

} // namespace base
