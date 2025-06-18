#include <stdexcept>
#include "tree_node.hpp"
#include "node_tree.hpp"

namespace base
{
    TreeNodeRef TreeNode::create()
    {
        auto node = std::shared_ptr<TreeNode>(new TreeNode());
        node->_recursive_set_root(node);
        return node;
    }

    //
    // 受保护的接口
    //

    void TreeNode::_recursive_set_root(const NodeRef &root)
    {
        auto root2 = convert(root);
        m_tree = root2->m_tree;
        Node::_recursive_set_root(root);
    }

    void TreeNode::_reset_tree()
    {
        m_tree.reset();
    }

    //
    // 公共接口
    //

    std::string TreeNode::to_string() const
    {
        std::stringstream sstr;
        sstr << "TreeNode@" << this << "[";

        auto parent = get_parent().lock();
        if (parent)
            sstr << "parent@" << parent.get();
        else
            sstr << "parent@null";

        sstr << ", root@" << get_root().lock().get();

        auto tree = m_tree.lock();
        if (tree)
            sstr << ", tree@" << tree.get();
        else
            sstr << ", tree@null";

        sstr << ", is ready: " << (m_is_ready ? "true" : "false") << "]";

        return sstr.str();
    }

    void TreeNode::request_enter_tree()
    {
        // 本节点必须在节点树中
        if (m_tree.expired())
            throw std::runtime_error("This node must be in the NodeTree");

        _on_enter_tree(m_tree.lock());

        for (auto &node : get_children())
        {
            auto child = convert(node);
            if (!child)
                continue;

            child->request_enter_tree();
        }
    }

    void TreeNode::request_ready()
    {
        // 本节点必须在节点树中
        if (m_tree.expired())
            throw std::runtime_error("This node must be in the NodeTree");

        for (auto &node : get_children())
        {
            auto child = convert(node);
            if (!child)
                continue;

            child->request_ready();
        }

        // 如果本节点已就绪
        if (m_is_ready)
            return;

        _on_ready();
        m_is_ready = true;
    }

    void TreeNode::request_exit_tree()
    {
        // 本节点必须在节点树中
        if (m_tree.expired())
            throw std::runtime_error("This node must be in the NodeTree");

        _on_exit_tree(m_tree.lock());

        for (auto &node : get_children())
        {
            auto child = convert(node);
            if (!child)
                continue;

            child->request_exit_tree();
        }

        // 解除对节点树的引用
        _reset_tree();
    }

    void TreeNode::detach_from_parent()
    {
        Node::detach_from_parent();

        if (is_in_tree())
            request_exit_tree();
    }

    void TreeNode::add_child(const NodeRef &node)
    {
        auto self = shared_from_this();
        auto tree = m_tree.lock();

        auto child = convert(node);
        // 不能添加空对象或非TreeNode节点
        if (!child)
            throw BASE_NODE_MAKE_ERROR("Cannot add a non-TreeNode node as a child node", self, node);
        // 不能添加节点树里的节点
        if (child->is_in_tree())
            throw BASE_NODE_MAKE_ERROR("Cannot add a node which in tree as a child node", self, node);
        // 节点树初始化时，新增节点可能无法遍历到
        if (tree)
            if (tree->get_status() == NodeTree::Status::Initializing)
                throw BASE_NODE_MAKE_ERROR("Cannot add node during NodeTree initialization", self, node);

        Node::add_child(node);

        // 如果节点树已经就绪，则新加入的节点无法通过NodeTree::request_initialize()初始化
        if (!tree)
            return;

        if (tree->get_status() == NodeTree::Status::Ready)
        {
            // 手动调用
            child->request_enter_tree();
            child->request_ready();
        }
    }

    void TreeNode::remove_child(const NodeRef &node)
    {
        Node::remove_child(node);

        auto child = convert(node);
        // 非TreeNode节点
        if (!child)
            return;

        // 通知子节点退出节点树
        if (child->is_in_tree())
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
            if (child->is_in_tree())
                child->request_exit_tree();
        }
        Node::clear_children();
    }

    std::ostream &operator<<(std::ostream &os, const TreeNode &node)
    {
        os << node.to_string();
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const TreeNodeRef &node)
    {
        if (node)
            os << *node;
        else
            os << "TreeNode@null";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const TreeNodeWeakRef &node)
    {
        if (node.expired())
            os << "TreeNode@null";
        else
            os << *node.lock();
        return os;
    }

} // namespace base
