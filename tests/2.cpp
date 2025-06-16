#include <iostream>
#include "../base/base.hpp"

void print_node_state(const base::NodeRef &node);
void test1();

int main()
{
    test1();

    return 0;
}

void print_node_state(const base::NodeRef &node)
{
    std::cout << node.get() << "\tis child: " << node->is_child() << "\tis root:" << node->is_root() << std::endl;
}

void test1()
{
    base::NodeRef root = base::Node::create();
    base::NodeRef child1 = base::Node::create();
    base::NodeRef child2 = base::Node::create();
    base::NodeRef child1_1 = base::Node::create();
    base::NodeRef child1_2 = base::Node::create();
    base::NodeRef child2_1 = base::Node::create();
    base::NodeRef child2_2 = base::Node::create();

    child1->add_child(child1_1);
    child1->add_child(child1_2);
    child2->add_child(child2_1);
    child2->add_child(child2_2);
    root->add_child(child1);
    root->add_child(child2);

    print_node_state(root);
    print_node_state(child1);
    print_node_state(child2);
    print_node_state(child1_1);
    print_node_state(child1_2);
    print_node_state(child2_1);
    print_node_state(child2_2);
}
