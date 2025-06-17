#include <stdexcept>
#include "node_tree.hpp"

#define BASE_NODETREE_MAKE_ERROR(message, self) \
    BASE_MAKE_RUNTIME_ERROR(message, "\nself: ", self)

namespace base
{
    NodeTreeRef NodeTree::create()
    {
        NodeTreeRef tree = std::shared_ptr<NodeTree>(new NodeTree());
        TreeNodeRef root = TreeNode::create();
        tree->_set_root(root);
        return tree;
    }

    std::string NodeTree::status_str(Status status)
    {
        switch (status)
        {
        case Status::Uninitialized:
            return "Uninitialized";

        case Status::Initializing:
            return "Initializing";

        case Status::Ready:
            return "Ready";

        default:
            return "Unknown";
        }
    }

    void NodeTree::_set_root(const TreeNodeRef &root)
    {
        root->m_tree = shared_from_this();
        m_root = root;
    }

    void NodeTree::_remove_root()
    {
        m_root->m_tree.reset();
        m_root->_recursive_set_root(m_root);
        m_root.reset();
    }

    std::string NodeTree::to_string() const
    {
        std::stringstream sstr;

        sstr << "NodeTree@" << this << "[";

        if (m_root)
            sstr << "root@" << m_root.get();
        else
            sstr << "root@null";

        sstr << ", status: " << status_str(m_status) << "]";

        return sstr.str();
    }

    void NodeTree::request_initialize()
    {
        // 只有在未被初始化时才能初始化
        if (m_status != Status::Uninitialized)
            throw BASE_NODETREE_MAKE_ERROR("The NodeTree has been initialized", shared_from_this());

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
            throw BASE_NODETREE_MAKE_ERROR("The NodeTree has not been initialized yet", shared_from_this());

        // 结束
        m_root->request_exit_tree();
        m_root->clear_children();
        _on_finalize();
        m_status = Status::Uninitialized;
    }

    std::ostream &operator<<(std::ostream &os, const NodeTree &tree)
    {
        os << tree.to_string();
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeTreeRef &tree)
    {
        if (tree)
            os << *tree;
        else
            os << "Node@null";
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const NodeTreeWeakRef &tree)
    {
        if (tree.expired())
            os << "Node@null";
        else
            os << *tree.lock();
        return os;
    }

} // namespace base
