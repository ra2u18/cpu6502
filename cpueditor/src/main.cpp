#include <iostream>
#include "cpu6205/engine.h"

int main()
{
    std::cout << "Hello world!" << std::endl;
    cpu6205::Engine e;
    e.GetInfo();
    std::cin.ignore();
    return 0;
}