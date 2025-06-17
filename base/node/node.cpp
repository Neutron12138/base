#include <algorithm>
#include "node.hpp"
#include "../core/string.hpp"
#include "../core/exception.hpp"

#define BASE_NODE_MAKE_ERROR(message, self, node) \
    BASE_MAKE_RUNTIME_ERROR(message, "\nself: ", self, "\nnode: ", node)

namespace base
{
    NodeRef Node::create()
    {
        auto node = std::shared_ptr<Node>(new Node());
        node->m_root = node;
        return node;
    }

    //
    // 受保护的接口
    //

    void Node::_link_child(const NodeRef &node)
    {
        node->m_parent = shared_from_this();
        node->_recursive_set_root(m_root.lock());
    }

    void Node::_unlink_child(const NodeRef &node)
    {
        node->m_parent.reset();
        node->_recursive_set_root(node);
    }

    void Node::_recursive_set_root(const NodeRef &root)
    {
        m_root = root;
        for (auto &child : m_children)
        {
            if (!child)
                continue;

            child->_recursive_set_root(root);
        }
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
        _recursive_set_root(shared_from_this());
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

    std::string Node::to_string() const
    {
        std::stringstream sstr;
        sstr << "Node@" << this << "[";

        auto parent = m_parent.lock();
        if (parent)
            sstr << "parent@" << parent.get();
        else
            sstr << "parent@null";

        sstr << ", root@" << m_root.lock().get() << "]";

        return sstr.str();
    }

    NodeIterator Node::find_child(const NodeRef &node)
    {
        auto self = shared_from_this();

        // 不能查找空对象
        if (!node)
            throw BASE_NODE_MAKE_ERROR("Unable to find an invalid object", self, node);
        // 只能查找子节点
        if (node->get_parent().lock().get() != this)
            throw BASE_NODE_MAKE_ERROR("This node is not its parent", self, node);
        // 子节点有对父节点的引用，但是父节点没有对子节点的引用
        auto iter = _find_child(node);
        if (iter == m_children.end())
            throw BASE_NODE_MAKE_ERROR("Unable to find the node", self, node);

        return iter;
    }

    NodeConstIterator Node::find_child(const NodeRef &node) const
    {
        auto self = shared_from_this();

        // 不能查找空对象
        if (!node)
            throw BASE_NODE_MAKE_ERROR("Unable to find an invalid object", self, node);
        // 只能查找子节点
        if (node->get_parent().lock().get() != this)
            throw BASE_NODE_MAKE_ERROR("This node is not its parent", self, node);
        // 子节点有对父节点的引用，但是父节点没有对子节点的引用
        auto iter = _find_child(node);
        if (iter == m_children.cend())
            throw BASE_NODE_MAKE_ERROR("Unable to find the node", self, node);

        return iter;
    }

    void Node::detach_from_parent()
    {
        if (!is_child())
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
        auto self = shared_from_this();

        // 待添加节点不能是空对象
        if (!node)
            throw BASE_NODE_MAKE_ERROR("Cannot add a null object as a child node", self, node);
        // 待添加节点不能是自己
        if (node.get() == this)
            throw BASE_NODE_MAKE_ERROR("Cannot add self as a child node", self, node);
        // 待添加节点必须是独立的
        if (!node->is_root())
            throw BASE_NODE_MAKE_ERROR("Cannot add an existing parent node as a child node", self, node);

        _add_child(node);
        _link_child(node);
        node->_on_attached_to_parent(shared_from_this());
    }

    void Node::add_children(const NodeArray &children)
    {
        _add_children(children.cbegin(), children.cend());
        for (auto &child : children)
        {
            if (!child)
                continue;

            _link_child(child);
        }
    }

    void Node::remove_child(const NodeRef &node)
    {
        auto self = shared_from_this();

        // 待移除节点不能是空对象
        if (!node)
            throw BASE_NODE_MAKE_ERROR("Cannot remove a null object", self, node);
        // 只能移除子节点
        if (node->get_parent().lock().get() != this)
            throw BASE_NODE_MAKE_ERROR("This node is not its parent", self, node);
        // 子节点有对父节点的引用，但是父节点没有对子节点的引用
        auto iter = _find_child(node);
        if (iter == m_children.end())
            throw BASE_NODE_MAKE_ERROR("Unable to find the node", self, node);

        _remove_child(iter);
        _unlink_child(node);
        node->_on_detached_from_parent(shared_from_this());
    }

    void Node::clear_children()
    {
        auto self = shared_from_this();
        for (auto &child : m_children)
        {
            if (!child)
                continue;

            _unlink_child(child);
            child->_on_detached_from_parent(self);
        }

        // 断开对子节点的连接
        _clear_children();
    }

    std::ostream &operator<<(std::ostream &os, const Node &node)
    {
        os << node.to_string();
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeRef &node)
    {
        if (node)
            os << *node;
        else
            os << "Node@null";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeWeakRef &node)
    {
        if (node.expired())
            os << "Node@null";
        else
            os << *node.lock();
        return os;
    }

} // namespace base
