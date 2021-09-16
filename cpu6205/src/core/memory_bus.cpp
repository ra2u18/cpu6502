#include "core/memory_bus.h"

namespace cpu6205::core::memory
{
	Bus::Bus()
	{
		// Connect Devices to the Memory Bus
		cpu.ConnectBus(getptr());

		// Clear RAM from garbage
		for (auto& iter : RAM) iter = 0x00;
	}
	
	void Bus::write(Word address, Byte data)
	{
		if (address >= 0x0000 && address <= 0xFFFF) // if address within bounds
			RAM[address] = data;
	}

	Byte Bus::read(Word address, bool bReadOnly = false)
	{
		if (address >= 0x0000 && address <= 0xFFFF) // if address within bounds
			return RAM[address];
		
		return 0x00;
	}
}