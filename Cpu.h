#ifndef CPU_H
#define CPU_H

// Made by Ripich103 feel free to copy or use it

#include"Memory.h"
#include"Decoder.h"

#include<fstream>
#include<string> 
#include<iostream>

namespace CPU_4001
{
	class CPU
	{
	public:
		const byte c_ReservedAddress;
		const byte c_BaseAddress;
		const byte c_AddressCeiling;
		const byte c_JumpToAddress;
	private:
		byte m_ProgramCounter;
		byte m_Register0;
		byte m_Register1;
		bool m_OverflowFlag;
		bool m_UnderflowFlag;
		bool m_SigningFlag;
		byte m_PrintFlag; // true =  char / false =  int
		bool m_Halt;

		Memory* m_Memory;

		byte Fetch();

		void Decode(byte p_Opcode);

	    void Halt();
	   
	    void Add();
	   
	    void Sub();
	   
	    void Mul();
	   
	    void Div();
	   
	    void Beep() const;

		void Store();

		void Print();
		
		void JumpTo();

		void JumpIfEqu();

		void JumpNEqu();

	    void ResetReg1();
	   
	    void ResetReg0();

		void ErrorHandling();

		void SetPrintFlagToChar();

		void SetPrintFlagToInt();

	public:
		CPU(Memory* p_Memory);

		bool ReadFromFile(char* filename);
		 
		bool WriteToFile(char* filename);

		~CPU();

		void Reset();
		
		void Run();

		
	};
}

#endif 
