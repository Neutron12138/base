#include <stdexcept>
#include "node_tree.hpp"

namespace base
{
    NodeTreeRef NodeTree::create()
    {
        NodeTreeRef tree = std::shared_ptr<NodeTree>(new NodeTree());
        TreeNodeRef root = TreeNode::create();
        tree->_set_root(root);
        return tree;
    }

    void NodeTree::_set_root(const TreeNodeRef &root)
    {
        root->m_in_tree = true;
        root->m_tree = shared_from_this();
        m_root = root;
    }

    void NodeTree::_remove_root()
    {
        m_root->m_in_tree = false;
        m_root->m_tree.reset();
        m_root.reset();
    }

    void NodeTree::request_initialize()
    {
        // 只有在未被初始化时才能初始化
        if (m_status != Status::Uninitialized)
            throw std::runtime_error("The NodeTree has been initialized");

        // 初始化
        m_status = Status::Initializing;
        _on_initialize();
        m_root->request_enter_tree();

        // 准备就绪
        m_root->request_ready();
        m_status = Status::Ready;
        _on_ready();
    }

    void NodeTree::request_finalize()
    {
        // 只有准备就绪后才能结束
        if (m_status != Status::Ready)
            throw std::runtime_error("The NodeTree has not been initialized yet");

        // 结束
        m_root->request_exit_tree();
        m_status = Status::Uninitialized;
    }

} // namespace base
