#include <iostream>

#include "cpu6205/core/cpu.h"
#include "cpu6205/core/memory_bus.h"

int main()
{
    cpu6205::core::CPU cpu;

    // Create memory for cpu
    using bus = cpu6205::core::memory::Bus;
    std::shared_ptr<bus> m = std::make_shared<bus>();

    cpu.Reset();

    /* 
    std::cout << "Hello world!" << std::endl;
    cpu6205::Engine e;
    e.GetInfo();
    */
    std::cin.ignore();
    return 0;
}