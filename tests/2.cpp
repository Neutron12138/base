#include <iostream>
#include "../src/base.hpp"

int main()
{
    base::NodeRef root = base::Node::create();
    auto child1 = base::Node::create();
    root->add_child(child1);
    auto child2 = base::Node::create();
    root->add_child(child2);

    base::NodeRef root2 = base::Node::create();
    root->reparent_to(root2);

    std::cout << root->is_child() << "," << root->is_root() << std::endl
              << root2->is_child() << "," << root2->is_root() << std::endl
              << child1->is_child() << "," << child1->is_root() << std::endl
              << child2->is_child() << "," << child2->is_root() << std::endl;

    std::cout << root->get_children().size() << std::endl;
    child1->detach_from_parent();
    std::cout << child1->is_root() << "," << root->get_children().size() << std::endl;
    root->remove_child(child2);
    std::cout << child2->is_root() << "," << root->get_children().size() << std::endl;

    return 0;
}
