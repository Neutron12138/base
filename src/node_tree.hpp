#pragma once

#include "tree_node.hpp"

namespace base
{
    class NodeTree
    {
    private:
        TreeNodeRef m_root;

    protected:
        virtual void _on_initialize() {}
        virtual void _on_ready() {}
        virtual void _on_finalize();
    };

} // namespace base
