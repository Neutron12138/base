#include <iostream>
#include "../src/base.hpp"

int main()
{
    base::TreeNodeRef a = std::make_shared<base::TreeNode>();
    a->clear_children();

    return 0;
}
