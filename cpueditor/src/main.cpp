#include <iostream>

#include "cpu6205/core/cpu.h"
#include "cpu6205/core/bus.h"
#include "cpu6205/managers/logmanager.h"

int main()
{
    // Initialize the log manager
    cpu6205::managers::LogManager logManager;
    logManager.Initialize();

    using Bus = cpu6205::core::Bus;
    using CPU = cpu6205::core::CPU;

    CPU cpu;
    Bus bus;

    cpu.ConnectBus(&bus);
    cpu.Reset();
   
    /* ------- [START] Insert hardcoded tests here ------- */
    
    // Test LDA IMM
    //bus.write(0xFFFC, CPU::INS_LDA_IMM);
    //bus.write(0xFFFD, 0x42);
    
    // Test LDA Zero page
    // bus.write(0xFFFC, CPU::INS_LDA_ZP);
    // bus.write(0xFFFD, 0x42);
    // bus.write(0x0042, 0x12);

    // Test JSR Instruction
    bus.write(0xFFFC, CPU::INS_JSR);
    bus.write(0xFFFD, 0x42);
    bus.write(0xFFFE, 0x42);
    bus.write(0x4242, CPU::INS_LDA_IMM);
    bus.write(0x4243, 0x12);
    /* ------- [END]   Insert hardcoded tests here ------- */

    cpu.Execute(9);

    std::cin.ignore();
    return 0;
}