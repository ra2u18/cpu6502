#include "core/bus.h"
#include <iostream>

namespace cpu6205::core
{
	Bus::Bus() {}

	Bus::~Bus() {}
	
	void Bus::write(Word address, Byte data)
	{
		if (address >= 0x0000 && address <= 0xFFFF) // if address within bounds
			(*RAM)[address] = data;
	}

	Byte Bus::read(Word address, bool bReadOnly)
	{
		if (address >= 0x0000 && address <= 0xFFFF) // if address within bounds
			return (*RAM)[address];
		
		return 0x00;
	}
}