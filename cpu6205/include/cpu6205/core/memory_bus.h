#pragma once

#include "cpu.h"
#include <array>

namespace cpu6205::core::memory
{
	class Bus : public std::enable_shared_from_this<Bus>
	{
	public:
		Bus();

	public:
		// Devices on the Memory Bus
		CPU cpu;
		std::array<Byte, 64 * 1025> RAM;

	public:
		void write(Word address, Byte data);
		Byte read(Word address, bool bReadOnly = false);
	
	private:
		std::shared_ptr<Bus> getptr() { return shared_from_this(); }
	};
}