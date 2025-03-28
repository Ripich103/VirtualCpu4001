#ifndef CPU_MEMORY
#define CPU_MEMORY
// Made by Ripich103 feel free to copy or use it
namespace CPU_4001
{
	// char = byte 
	// cuz size of char = 1 byte.
	typedef unsigned char byte; 

	class Memory
	{
	public:
		// maximum address from wich we can
		// write or read from!
		const byte c_MaxAddress;

	private:
		// memory space that we are
		// going to use.
		byte* c_MemorySpace;
	public:

		Memory();

		~Memory();

		void Clear();

		const byte& Read(const byte& p_Address);

		void Write(const byte& p_Address,const byte& p_Value);
	};
}
#endif 
