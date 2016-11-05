/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

//cpu.h - Compatibility layer for lame6502 to keep everything neat

#include <stdbool.h>

#ifndef _CPU_H_
#define _CPU_H_

#define CPU_MEMORY_SIZE 0xFFFF
#define CPU_CYCLES_PER_FRAME 100 //TODO

void CPUExecute(int cycles);
bool CPUInit();
bool CPUDeInit();
unsigned char CPUReadMemory(unsigned int address);
void CPUWriteMemory(unsigned int address, unsigned char val);
void CPUWriteMemoryRaw(unsigned int address, unsigned char val);

#endif //_CPU_H_
