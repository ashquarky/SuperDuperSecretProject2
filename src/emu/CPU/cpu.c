/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

//cpu.c - Compatibility layer for lame6502 to keep everything neat

#include <stdbool.h>
#include <stdlib.h>
#include <lame6502/lame6502.h>
#include "cpu.h"

inline void CPUExecute(int cycles) {
	CPU_execute(cycles); //lame6502 function
}

bool CPUInit() {
	write_memory_real = &CPUWriteMemory; //lame6502 variable
	allocate_memory(CPU_MEMORY_SIZE); //lame6502 function TODO get rid of this
	program_counter = 0x400;
	if (!memory) {
		return true;
	}
	return false;
}

bool CPUDeInit() {
	free(memory);
	//Looks like we just have to take this one on trust.
	return false;
}

inline unsigned char CPUReadMemory(unsigned int address) {
	return memory_read(address); //lame6502 function
}

inline void CPUWriteMemoryRaw(unsigned int address, unsigned char val) {
	memory[address] = val;
}

//TODO: bitshifting on this section
void CPUWriteMemory(unsigned int address, unsigned char val) {
	if (address < 0x0800) {
		memory[address] = val; //"real" memory
		memory[address + 0x0800] = val; //0800 mirror
		memory[address + 0x0800 + 0x0800] = val; //1000 mirror
		memory[address + 0x0800 + 0x0800 + 0x0800] = val; //1800 mirror
	} else {
		if (address < 0x1000) {
			memory[address] = val; //0800 mirror
			memory[address + 0x0800] = val; //1000 mirror
			memory[address + 0x0800 + 0x0800] = val; //1800 mirror
			memory[address - 0x0800] = val; //"real" memory
		} else {
			if (address < 0x1800) {
				memory[address] = val; //1000 mirror
				memory[address + 0x0800] = val; //1800 mirror
				memory[address - 0x0800] = val; //0800 mirror
				memory[address - 0x0800 - 0x0800] = val; //"real" memory
			} else {
				if (address < 0x2000) {
					memory[address] = val; //1800 mirror
					memory[address - 0x0800] = val; //1000 mirror
					memory[address - 0x0800 - 0x0800] = val; //0800 mirror
					memory[address + 0x0800 + 0x0800 + 0x0800] = val; //"real" memory
				} else {
					if (address < 0x2008) {
						//PPURegisterWrite()
					} else {
						if (address < 0x4000) {
							//NO
						} else {
							if (address < 0x4018) {
								//APURegiserWrite
							} else {
								if (address < 0x4020) {
									//CPU Test Mode stuff
								} else {
									//MAPPERS
									memory[address] = val;
								}
							}
						}
					}
				}
			}
		}
	}
}
