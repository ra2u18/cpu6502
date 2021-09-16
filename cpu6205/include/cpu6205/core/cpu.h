#pragma once
#include "memory_bus.h"

#include <cstdint>
#include <memory>
#include <string>
#include <stdio.h>
#include <vector>

namespace cpu6205::core
{
	using Word = uint16_t;
	using Byte = uint8_t;
	using bus = cpu6205::core::memory::Bus;

	class CPU
	{
	public:
		CPU();
		~CPU();
	public:
		// CPU core registers
		Word PC	{ 0x0000 };		// Program Counter
		Byte SP	{ 0x00 };		// Stack Pointer
		Byte A	{ 0x00 };		// Accumulator Register
		Byte X	{ 0x00 };		// Index Register X
		Byte Y	{ 0x00 };		// Index Register Y

		/*
	     	 PROCESSOR STATUS REGISTER P
			7	6	5	4	3	2	1	0
			N	V	-	B	D	I	Z	C

			C - carry flag
			Z - zero flag
			I - IRQ disable flag
			D - decimal mode flag
			B - break command flag
			V - overflow flag
			N - negative flag
		*/
		Byte Status{ 0x00 }; // Status Register

		enum FLAGS6205
		{
			C = (1 << 0),	// Carry Bit
			Z = (1 << 1),	// Zero Bit
			I = (1 << 2),	// Disable interrupts
			D = (1 << 3),	// Decimal Mode (unused in this implementation)
			B = (1 << 4),	// Break
			U = (1 << 5),	// Unused
			V = (1 << 6),	// Overflow
			N = (1 << 7),	// Negative
		};
	public:
		/*	
			External event functions, in hardware these are pins asserted into the microprocessor
			to produce a change in state
		*/
		void Reset(); // Reset Interrupt - Forces CPU into initial known state
		void ConnectBus(std::shared_ptr<bus> b) { mBus = std::move(b); }
	private:
		uint8_t GetFlag(FLAGS6205 f);
		void	SetFlag(FLAGS6205 f, bool v);

		uint8_t		cycles = 0;			// How many cycles the instruction has remaining
		uint32_t	clock_count = 0;	// Global accumulation of the nb. of cycles 

		struct INSTRUCTION
		{
			std::string	name;
			uint8_t		(CPU::* opcode) (void)		= nullptr;
			uint8_t		(CPU::* addrmode) (void)	= nullptr;
			uint8_t		cycles = 0;
		};

		std::vector<INSTRUCTION> lookup;
	private:
		// Communication bus interface
		std::shared_ptr<bus> mBus = nullptr;
		Byte read(Word address);
		void write(Word address, Byte data);

		void IMM();
	};
}