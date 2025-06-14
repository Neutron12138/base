#include <iostream>
#define BASE_INCLUDING_GAME_OBJECTS
#include "../src/base.hpp"

int main()
{
    base::SceneTreeRef tree = base::SceneTree::create("tree");
    base::GameNodeRef root = base::GameNode::convert(tree->get_root());
    root->set_name("root");

    base::GameNodeRef node1 = base::GameNode::create("node1");
    base::GameNodeRef node2 = base::GameNode::create("node2");
    base::GameNodeRef node1_1 = base::GameNode::create("node1_child1");
    base::GameNodeRef node1_2 = base::GameNode::create("node1_child2");

    node1->add_child(node1_1);
    node1->add_child(node1_2);
    root->add_child(node1);
    root->add_child(node2);
    std::cout << !node1_1->is_in_tree() << "," << !node1_2->is_in_tree() << std::endl;

    tree->request_initialize();
    std::cout << "initialized: " << (tree->get_status() == base::NodeTree::Status::Ready) << std::endl;
    std::cout << node1_1->is_in_tree() << "," << node1_2->is_in_tree() << std::endl;

    tree->request_finalize();
    std::cout << "finalized: " << (tree->get_status() == base::NodeTree::Status::Uninitialized) << std::endl;
    std::cout << !node1_1->is_in_tree() << "," << !node1_2->is_in_tree() << std::endl;

    return 0;
}
