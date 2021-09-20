#include "core/cpu.h"
#include "core/bus.h"

#include "log.h"

namespace cpu6205::core
{
	CPU::CPU() {}

	CPU::~CPU()	{}

	// An absolute address is read from location 0xFFFC which contains
	// a second address that the program counter is set to. This allows
	// the programmer to jump to a known programmable location in the memory
	// to start executing it
	void CPU::Reset()
	{
		//Byte testByte = read(0x0038);

		//Word address_abs = 0xFFFC;
		//
		//Word PCL = read(address_abs + 0); // Program Counter Low Byte
		//Word PCH = read(address_abs + 1); // Program Counter High Byte
		//
		//// In the memory PCL (LSB) is laid out first, so we need to recreate
		//// the full address by pushing MSB before LSB
		//PC = (PCH << 8) | PCL;

		PC = 0xFFFC;

		// Reset Internal registers
		A = X = Y = 0x00;
		SP = 0xFD;
		Status = 0x00 | U;

		// [TODO]: Reset takes time -- emulate cycles here
	}

	Byte CPU::fetchByte(uint32_t& cycles)
	{
		Byte data = read(PC);
		PC++;
		cycles--;
		return data;
	}

	void CPU::Execute(uint32_t cycles)
	{
		while (cycles > 0)
		{
			Byte Ins = fetchByte(cycles);
			switch(Ins)
			{
				case INS_LDA_IMM:
				{
					A = fetchByte(cycles);
					setFlag(N, A & 0x80);
					setFlag(Z, A == 0x00);
				} break;

				case INS_LDA_ZP:
				{
					Byte ZeroPageAddress = fetchByte(cycles);

					A = read(ZeroPageAddress); // don't increase PC again
					cycles--;

					setFlag(N, A & 0x80);
					setFlag(Z, A == 0x00);
				} break;

				case INS_LDA_ZPX:
				{
					Byte ZeroPageAddress = fetchByte(cycles);

					ZeroPageAddress += X;
					cycles--;

					A = read(ZeroPageAddress); // don't increase PC again
					cycles--;

					// Handle overflow, if we cross page zero wrap around!

					setFlag(N, A & 0x80);
					setFlag(Z, A == 0x00);
				} break;

				case INS_JSR:
				{
					// Fetch Word
					Word SubRoutine = read(PC + 0) | (read(PC + 1) << 8);
					PC += 2;
					cycles -= 2;
					// end - fetch word
				
					// Write Word
					write(SP, (PC - 1) & 0xFF);
					write(SP, PC >> 8);
	
					cycles -= 2;

					SP += 2;
					PC = SubRoutine;
					cycles--;

				} break;

				default:
				{
					C6205_TRACE("The instruction {} is not part of this architecture", Ins);
				}
			}
		}
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

	// Returns value of a specific bit of status register
	Byte CPU::getFlag(FLAGS6205 f) { return ((Status & f) > 0) ? 1 : 0; }
	// Sets or clears specific bit of status register
	void CPU::setFlag(FLAGS6205 f, bool cond)
	{
		if (cond)
			Status |= f;
		else
			Status &= ~f;
	}
}
