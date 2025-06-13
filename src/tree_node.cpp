#include <stdexcept>
#include "string.hpp"
#include "tree_node.hpp"

namespace base
{
    void TreeNode::_reset_tree()
    {
        m_in_tree = false;
        m_tree.reset();
        m_is_ready = false;
    }

    void TreeNode::request_enter_tree()
    {
        // 本节点必须在节点树中
        if (!m_in_tree)
            throw std::runtime_error("This node must be in the NodeTree");
        // 本节点必须尚未就绪
        if (m_is_ready)
            throw std::runtime_error("This node must not be ready yet");

        _on_enter_tree(m_tree.lock());
        for (auto &node : get_children())
        {
            auto child = convert(node);
            if (!child)
                continue;

            // 更新所有子节点的m_in_tree与m_tree
            child->m_in_tree = true;
            child->m_tree = m_tree;
            child->request_enter_tree();
        }
    }

    void TreeNode::request_ready()
    {
        // 本节点必须在节点树中
        if (!m_in_tree)
            throw std::runtime_error("This node must be in the NodeTree");
        // 如果本节点已就绪
        if (m_is_ready)
            return;

        for (auto &node : get_children())
        {
            auto child = convert(node);
            if (child)
                child->request_ready();
        }

        // 准备就绪
        m_is_ready = true;
        _on_ready();
    }

    void TreeNode::request_exit_tree()
    {
        // 本节点必须在节点树中
        if (!m_in_tree)
            throw std::runtime_error("This node must be in the NodeTree");

        m_is_ready = false;
        _on_exit_tree(m_tree.lock());
        for (auto &node : get_children())
        {
            auto child = convert(node);
            if (child)
                child->request_exit_tree();
        }

        // 解除对节点树的引用
        _reset_tree();
    }

    void TreeNode::reparent_to(const NodeRef &new_parent)
    {
        // 必须得是非空对象且为TreeNode类型
        auto parent = convert(new_parent);
        if (!parent)
            throw std::runtime_error("Cannot reparent to an invalid node");

        // 如果新都在节点树中，且是同一个节点树，或都不在节点树中
        if ((parent->m_in_tree && m_in_tree && (parent->get_tree().lock() == m_tree.lock())) ||
            (!parent->m_in_tree && !m_in_tree))
            // 不需要跨树移动
            Node::reparent_to(new_parent);
        else
            // 无法跨树移动
            throw std::runtime_error("Cannot moving node across trees");
    }

    void TreeNode::detach_from_parent()
    {
        Node::detach_from_parent();

        if (!m_in_tree)
            return;

        request_exit_tree();
    }

    void TreeNode::add_child(const NodeRef &node)
    {
        auto child = convert(node);
        // 不能添加空对象或非TreeNode节点
        if (!child)
            throw std::runtime_error("Cannot add a non-TreeNode node as a child node");
        // 不能添加节点树里的节点
        if (child->m_in_tree)
            throw std::runtime_error("Cannot add a node which in tree as a child node");

        Node::add_child(node);
        child->m_in_tree = true;
        child->m_tree = m_tree;
        child->request_enter_tree();
    }

    void TreeNode::remove_child(const NodeRef &node)
    {
        Node::remove_child(node);

        auto child = convert(node);
        // 非TreeNode节点
        if (!child)
            return;

        // 通知子节点退出节点树
        if (child->m_in_tree)
            child->request_exit_tree();
    }

    void TreeNode::clear_children()
    {
        for (auto &node : get_children())
        {
            auto child = convert(node);
            // 非TreeNode节点
            if (!child)
                continue;

            // 通知子节点退出节点树
            if (child->m_in_tree)
                child->request_exit_tree();
        }
        Node::clear_children();
    }

} // namespace base
