/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

//cpu.h - Compatibility layer for lame6502 to keep everything neat

#ifndef _CPU_H_
#define _CPU_H_

#define CPU_MEMORY_SIZE 0xFFFF
#define CPU_CYCLES_PER_FRAME 100 //TODO

inline void CPUExecute(int cycles);
bool CPUInit();
inline unsigned char CPUReadMemory(unsigned int address);
void CPUWriteMemory(unsigned int address, unsigned char val);

#endif //_CPU_H_
