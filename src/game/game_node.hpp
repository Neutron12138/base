#pragma once

#include "game_object.hpp"
#include "../process/event_handler.hpp"
#include "../node/tree_node.hpp"

namespace base
{
    class GameNode;
    using GameNodeRef = Ref<GameNode>;
    using GameNodeWeakRef = WeakRef<GameNode>;

    class SceneTree;
    using SceneTreeRef = Ref<SceneTree>;
    using SceneTreeWeakRef = WeakRef<SceneTree>;

    /// @brief 游戏节点
    class GameNode : virtual public GameObject,
                     virtual public TreeNode,
                     virtual public EventHandler
    {
    public:
        static constexpr Int64 TYPE_ID = 1;
        static constexpr const char *TYPE_NAME = "GameNode";

        static GameNodeRef create(const std::string &name = {}) { return std::make_shared<GameNode>(name); }

        static GameNodeRef convert(const GameObjectRef &object) { return std::dynamic_pointer_cast<GameNode>(object); }
        static GameNodeRef convert(const TreeNodeRef &node) { return std::dynamic_pointer_cast<GameNode>(node); }

    public:
        GameNode(const std::string &name = {}) : GameObject(name) {}
        ~GameNode() override = default;
    };

} // namespace base
