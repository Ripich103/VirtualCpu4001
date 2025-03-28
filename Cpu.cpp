#include"Cpu.h"
// Made by Ripich103 feel free to copy or use it
namespace CPU_4001
{
	
	const byte& CPU::Fetch()
	{
		byte l_opCode = 0;
		l_opCode = m_Memory->Read(m_ProgramCounter);
		++m_ProgramCounter;
		if (m_ProgramCounter > c_AddressCeiling)
		{
			Halt();
		}
		return l_opCode;
	}

	void CPU::Halt()
	{
		m_Halt = true;
	}

	void CPU::Decode(const byte& p_Opcode)
	{
		
		if (m_Halt) return;

		switch (p_Opcode)
		{
		//EXIT PROGRAM
		case 0:
			Halt();
			break;
		//LOAD reg0
		case 1:
			m_Register0 = m_Memory->Read(m_ProgramCounter);
			++m_ProgramCounter;
			break;
		//LOAD reg1
		case 2:
			m_Register1 = m_Memory->Read(m_ProgramCounter);
			++m_ProgramCounter;
			break;
		//ADD reg0 TO reg1
		case 3:
			Add();
			break;
		// Substract reg0 and reg1, save result in reg0
		case 4:
			Sub();
			break;
		// Multiply reg0 and reg1, save result in reg0
		case 5:
			Mul();
			break;
		// Divide reg0 and reg1, save result in reg0
		case 6:
			Div();
			break;
		//BEEP
		case 7:
			Beep();
			break;
		//STORE reg0 AT MEMORY ADDRESS
		case 8:
			Store();
			break;
		//PRINT reg0
		case 9:
			Print();
			break;
		case 10:
		//SET reg0 TO zero xd!
			ResetReg0();
			break;
		case 11:
		//SET reg1 TO zero.
			ResetReg1();
			break;
		case 12:
		//JUMP to specified memory address
			JumpTo();
			break;
		case 13:
		//JUMP IF EQUAL to specified memory address
			JumpIfEqu();
			break;
		case 14:
		//JUMP IF NOT EQUAL to specified memory address
			JumpNEqu();
			break;
		//UNKNOWN OPCODE
		default:
			std::cerr << "Unknown opcode: " << (int)p_Opcode << std::endl;
			Halt();
		}
	}

	void CPU::ResetReg0()
	{
		m_Register0 = 0;
	}

	void CPU::ErrorHandling()
	{
		if (m_UnderflowFlag)
		{
			std::cerr << "\nUnderflow detected, undefined behavior in reg0\n setting it to 0..." << std::endl;
			ResetReg0();
			m_UnderflowFlag = false;
		}
		if (m_OverflowFlag)
		{
			std::cerr << "\nOverflow detected, undefined behavior in reg0\n setting it to 0..." << std::endl;
			ResetReg0();
			m_OverflowFlag = false;
		}
	}

	bool CPU::ReadFromFile(char* filename)
	{
		std::string line;
		byte opcode;

		line.reserve(255);
		

		std::ifstream out(filename);
		if (!out.is_open())
		{
			return false;
		}
		
		while (std::getline(out, line))
		{
			DC::Decode(opcode, line);
			m_Memory->Write(m_ProgramCounter, opcode);
			++m_ProgramCounter;
		}

		out.close();
		return true;
	}

	bool CPU::WriteToFile(char* filename)
	{

		std::ofstream out(filename, std::ios::trunc);

		if (!out.is_open())
		{
			return false;
		}

		while (m_Memory->Read(m_ProgramCounter) != 0)
		{
			out << (int)m_Memory->Read(m_ProgramCounter) << std::endl;
			++m_ProgramCounter;
		}

		m_ProgramCounter = c_BaseAddress;
		out.close();
		return true;
	}

	void CPU::ResetReg1()
	{
		m_Register1 = 0;
	}

	void CPU::JumpTo()
	{
		byte val = m_Memory->Read(m_ProgramCounter);
		m_Memory->Write(c_JumpToAddress, val);
		++m_ProgramCounter;

		m_ProgramCounter = m_Memory->Read(c_JumpToAddress);
	}

	void CPU::JumpIfEqu()
	{
		if (m_Register0 == m_Register1)
		{
			JumpTo();
		}
		else
		{
			++m_ProgramCounter;
		}
	}

	void CPU::JumpNEqu()
	{
		if (m_Register0 != m_Register1)
		{
			JumpTo();
		}
		else
		{
			++m_ProgramCounter;
		}
	}

	void CPU::Beep()
	{
		std::cout << "\a";
	}
	
	void CPU::Store()
	{
		// load the target address in register1
		m_Register1 = m_Memory->Read(m_ProgramCounter);
		++m_ProgramCounter;

		// write the value of reg0 to address of reg1
		m_Memory->Write(m_Register1, m_Register0);
	}

	void CPU::Print()
	{
		m_Register1 = m_Memory->Read(m_ProgramCounter);
		++m_ProgramCounter;

		m_Register0 = m_Memory->Read(m_Register1);

		std::cout << (int)m_Register0 << std::endl;
		
	}

	void CPU::Add()
	{
		byte oldVal = m_Register0;
		m_Register0 = m_Register0 + m_Register1;
		if (oldVal > m_Register0)
		{
			m_OverflowFlag = true;
		}
	}

	void CPU::Sub()
	{
		if (m_Register0 >= m_Register1)
		{
			m_Register0 = m_Register0 - m_Register1;
		}
		else
		{
			m_UnderflowFlag = true;
		}

	}

	void CPU::Mul()
	{
		byte oldVal = m_Register0;
		m_Register0 = m_Register0 * m_Register1;

		if (oldVal > m_Register0 && m_Register1 != 0)
		{
			m_OverflowFlag = true;
		}
	}

	void CPU::Div()
	{
		if (m_Register1 != 0)
		{
			m_Register0 = m_Register0 / m_Register1;
		}
		else
		{
			m_UnderflowFlag = true;
		}
			
		
	}

	CPU::CPU(Memory* p_Memory) :
		c_ReservedAddress(0),
		c_BaseAddress(2),
		c_AddressCeiling(253),
		c_JumpToAddress(1),
		m_ProgramCounter(c_BaseAddress),
		m_Register0(0),
		m_Register1(0),
		m_OverflowFlag(false),
		m_UnderflowFlag(false),
		m_SigningFlag(false),
		m_Halt(false),

		m_Memory(p_Memory)
	{
	}

	CPU::~CPU()
	{
		m_Memory = nullptr;
	}

	void CPU::Reset()
	{
		m_Halt = false;
		m_ProgramCounter = c_BaseAddress;
		m_OverflowFlag = false;
		m_UnderflowFlag = false;
		m_SigningFlag = false;
	}

	void CPU::Run()
	{
		while (!m_Halt)
		{
			// Somehow without this var this shit is going to be infinite
			// m_Memory->Write(c_ReservedAddress, Fetch()); Fucking compiler a hour wasted...
			byte fetchedOpcode = Fetch();

			m_Memory->Write(c_ReservedAddress, fetchedOpcode);

			//byte opcode = m_Memory->Read(c_ReservedAddress);
			Decode(m_Memory->Read(c_ReservedAddress));

			//Error handling
			ErrorHandling();
		}
	}
}