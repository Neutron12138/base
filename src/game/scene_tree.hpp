#pragma once

#include "game_node.hpp"
#include "../node/node_tree.hpp"

namespace base
{
    /// @brief 场景树
    class SceneTree : virtual public GameObject,
                      virtual public NodeTree
    {
    public:
        static constexpr Int64 TYPE_ID = 2;
        static constexpr const char *TYPE_NAME = "SceneTree";

        static SceneTreeRef create(const std::string &name = {})
        {
            SceneTreeRef tree = std::shared_ptr<SceneTree>(new SceneTree(name));
            GameNodeRef root = GameNode::create();
            tree->_set_root(root);
            return tree;
        }

        static SceneTreeRef convert(const GameObjectRef &object) { return std::dynamic_pointer_cast<SceneTree>(object); }
        static SceneTreeRef convert(const NodeTreeRef &tree) { return std::dynamic_pointer_cast<SceneTree>(tree); }

    protected:
        SceneTree(const std::string &name = {}) : GameObject(name) {}

    public:
        ~SceneTree() override = default;
    };

} // namespace base
