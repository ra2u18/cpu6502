#pragma once

#include "cpu.h"
#include <array>

namespace cpu6205::core
{
	class Bus
	{
	public:
		Bus();
		~Bus();

		void write(Word address, Byte data);
		Byte read(Word address, bool bReadOnly = false);
	
	public:
		// Devices on the Memory Bus
		CPU cpu;

		// Move RAM on heap, size exceeds stack size
		std::shared_ptr<std::array<Byte, 64 * 1024>> 
					RAM{new std::array<Byte, 64 * 1024> ()};
	};
}