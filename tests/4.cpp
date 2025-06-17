#include <iostream>
#include "../base/base.hpp"

int main()
{
    std::cout << base::read_from_file("1.txt") << std::endl;

    return 0;
}
