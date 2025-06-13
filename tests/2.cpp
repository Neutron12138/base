#include <iostream>
#include "../src/base.hpp"

void test1();
void test2();
void test3();

int main()
{
    std::cout << "----------test1----------" << std::endl;
    test1();
    std::cout << "----------test2----------" << std::endl;
    test2();
    std::cout << "----------test3----------" << std::endl;
    test3();

    return 0;
}

void test1()
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
}

void test2()
{
    base::NodeTreeRef tree1 = base::NodeTree::create();

    base::TreeNodeRef node1 = base::TreeNode::create();
    base::TreeNodeRef node2 = base::TreeNode::create();
    node1->add_child(node2);
    tree1->get_root()->add_child(node1);
    std::cout << node1->is_child() << "," << (node1->get_parent().lock() == tree1->get_root())
              << "," << (node1->get_tree().lock() == tree1) << std::endl;

    base::NodeTreeRef tree2 = base::NodeTree::create();

    try
    {
        tree2->get_root()->add_child(node1);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    node1->detach_from_parent();
    std::cout << node1->is_root() << "," << (node1->get_parent().lock() == nullptr)
              << "," << (node1->get_tree().lock() == nullptr) << std::endl;

    tree2->get_root()->add_child(node1);
    std::cout << node1->is_child() << "," << (node1->get_parent().lock() == tree2->get_root())
              << "," << (node1->get_tree().lock() == tree2) << std::endl;

    std::cout << node2->is_child() << "," << (node2->get_parent().lock() == node1)
              << "," << (node2->get_tree().lock() == tree2) << std::endl;

    try
    {
        node1->reparent_to(tree1->get_root());
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

void test3()
{
    base::NodeTreeRef tree = base::NodeTree::create();

    tree->request_initialize();
    std::cout << (tree->get_status() == base::NodeTree::Status::Ready) << std::endl;

    tree->request_finalize();
    std::cout << (tree->get_status() == base::NodeTree::Status::Uninitialized) << std::endl;
}
