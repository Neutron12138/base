#include <iostream>
#include "../base/base.hpp"

void print_node_state(const base::NodeRef &node);
void print_node_state(const base::TreeNodeRef &node);
void test1();
void test2();

int main()
{
    std::cout << "----------test1----------" << std::endl;
    test1();
    std::cout << "----------test2----------" << std::endl;
    test2();

    return 0;
}

void print_node_state(const base::NodeRef &node)
{
    std::cout << node.get() << "\tis child: " << node->is_child() << "\tis root:" << node->is_root() << std::endl;
}

void print_node_state(const base::TreeNodeRef &node)
{
    std::cout << node.get() << "\tis child: " << node->is_child() << "\tis root: " << node->is_root()
              << "\ttree: " << node->get_tree().lock().get() << std::endl;
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

void test2()
{
    base::NodeTreeRef tree1 = base::NodeTree::create();
    base::NodeTreeRef tree2 = base::NodeTree::create();

    base::TreeNodeRef root1 = tree1->get_root();
    base::TreeNodeRef root2 = tree2->get_root();

    base::TreeNodeRef child1_1 = base::TreeNode::create();
    base::TreeNodeRef child1_2 = base::TreeNode::create();
    base::TreeNodeRef child2_1 = base::TreeNode::create();
    base::TreeNodeRef child2_2 = base::TreeNode::create();

    root1->add_child(child1_1);
    root1->add_child(child1_2);
    root2->add_child(child2_1);
    root2->add_child(child2_2);

    print_node_state(root1);
    print_node_state(root2);
    print_node_state(child1_1);
    print_node_state(child1_2);
    print_node_state(child2_1);
    print_node_state(child2_2);
}
