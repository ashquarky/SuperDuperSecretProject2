/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

//cpu.c - Compatibility layer for lame6502 to keep everything neat

#include <lame6502/lame6502.h>
#include "cpu.h"

inline void CPUExecute(int cycles) {
	CPU_execute(cycles); //lame6502 function
}

void CPUInit() {
	write_memory_real = &CPUWriteMemory; //lame6502 variable
	allocate_memory(CPU_MEMORY_SIZE); //lame6502 function
}

inline unsigned char CPUReadMemory(unsigned int address) {
	return memory_read(address); //lame6502 function
}

void CPUWriteMemory(unsigned int address, unsigned char val) {
	//TODO: paging and all those other NESy things
	memory[address] = val; //lame6502 variable
}
