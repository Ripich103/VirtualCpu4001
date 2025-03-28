#include"Decoder.h"
// Made by Ripich103 feel free to copy or use it
namespace DC
{
	void Decode(CPU_4001::byte &value,std::string &option)
	{
        if (option == "MOVE_R0" || option == "mov_r0")
        {
            value = Asm::MOV_R0;
        }
        else if (option == "MOVE_R1" || option == "mov_r1")
        {
            value = Asm::MOV_R1;
        }
        else if (option == "ADD" || option == "add")
        {
            value = Asm::ADD;
        }
        else if (option == "SUB" || option == "sub")
        {
            value = Asm::SUB;
        }
        else if (option == "MUL" || option == "mul")
        {
            value = Asm::MUL;
        }
        else if (option == "DIV" || option == "div")
        {
            value = Asm::DIV;
        }
        else if (option == "BEEP" || option == "beep")
        {
            value = Asm::BEEP;
        }
        else if (option == "STORE" || option == "store")
        {
            value = Asm::STORE;
        }
        else if (option == "PRINT" || option == "print")
        {
            value = Asm::PRINT;
        }
        else if (option == "CLEAR_R0" || option == "clear_r0")
        {
            value = Asm::CLEAR_R0;
        }
        else if (option == "CLEAR_R1" || option == "clear_r1")
        {
            value = Asm::CLEAR_R1;
        }
        else if (option == "JM" || option == "jm")
        {
            value = Asm::JM;
        }
        else if (option == "JE" || option == "je")
        {
            value = Asm::JE;
        }
        else if (option == "JNE" || option == "jne")
        {
            value = Asm::JNE;
        }
        else if (option == "HALT" || option == "halt")
        {
            value = Asm::HALT;
        }
        else if (option == "NOP" || option == "nop")
        {
            value = Asm::NOP;
        }
        else
        {
            int temp = atoi(option.c_str());
            value = (CPU_4001::byte)temp;
        }
	}
}