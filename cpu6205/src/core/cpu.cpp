#include "core/cpu.h"

namespace cpu6205::core
{
	CPU::CPU()
	{

	}

	// An absolute address is read from location 0xFFFC which contains
	// a second address that the program counter is set to. This allows
	// the programmer to jump to a known programmable location in the memory
	// to start executing it
	void CPU::Reset()
	{
		Byte address_abs = 0xFFFC;
		
		Word PCL = read(address_abs + 0); // Program Counter Low Byte
		Word PCH = read(address_abs + 1); // Program Counter High Byte

		// In the memory PCL (LSB) is laid out first, so we need to recreate
		// the full address by pushing MSB before LSB
		PC = (PCH << 8) | PCL;

		// Reset Internal registers
		A = X = Y = 0x00;
		SP = 0xFD;
		Status = 0x00 | U;

		// [TODO]: Reset takes time -- emulate cycles here
	}

	// Read an 8-bit byte from memory bus, located at 16-bit address
	Byte CPU::read(Word address)
	{
		return mBus->read(address, false);
	}

	// Write a byte to the memory bus at specified address
	void CPU::write(Word address, Byte data)
	{
		mBus->write(address, data);
	}
}
