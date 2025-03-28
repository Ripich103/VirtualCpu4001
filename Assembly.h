#ifndef ASSEMBLY_H
#define ASSEMBLY_H
// Made by Ripich103 feel free to copy or use it
#include"Memory.h"

namespace Asm
{
	constexpr CPU_4001::byte MOV_R0 =	0x01;
	constexpr CPU_4001::byte MOV_R1 =	0x02;
	constexpr CPU_4001::byte ADD =		0x03;
	constexpr CPU_4001::byte SUB =		0x04;
	constexpr CPU_4001::byte MUL =		0x05;
	constexpr CPU_4001::byte DIV =		0x06;
	constexpr CPU_4001::byte BEEP =		0x07;
	constexpr CPU_4001::byte STORE =	0x08;
	constexpr CPU_4001::byte PRINT =	0x09;
	constexpr CPU_4001::byte CLEAR_R0 = 0x0A;
	constexpr CPU_4001::byte CLEAR_R1 = 0x0B;
	constexpr CPU_4001::byte JM =		0x0C;
	constexpr CPU_4001::byte JE =		0x0D;
	constexpr CPU_4001::byte JNE =		0x0E;
	constexpr CPU_4001::byte HALT =		0x00;
	constexpr CPU_4001::byte NOP =		0x00; // for readability.
}


#endif