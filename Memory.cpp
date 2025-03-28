#include "Memory.h"
// Made by Ripich103 feel free to copy or use it
namespace CPU_4001
{
	Memory::Memory()
		: c_MaxAddress(255), c_MemorySpace(new byte[c_MaxAddress])
	{
		Clear();
	}

	Memory::~Memory()
	{
		if (c_MemorySpace != nullptr)
		{
			delete[] c_MemorySpace;
			c_MemorySpace = nullptr;
		}
	}

	void Memory::Clear()
	{
		for (byte iterator = 0;iterator < c_MaxAddress;++iterator)
		{
			c_MemorySpace[iterator] = 0;
		}
	}

	const byte& Memory::Read(const byte& p_Address)
	{
		return c_MemorySpace[p_Address];
	}

	void Memory::Write(const byte& p_Address,const byte& p_Value)
	{
		c_MemorySpace[p_Address] = p_Value;
	}
}