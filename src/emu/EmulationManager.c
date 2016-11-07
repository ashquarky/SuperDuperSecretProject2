/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

//EmulationManager.c - Manages the NES emulator core

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <coreinit/debug.h>
#include "CPU/cpu.h"

bool initialized = false;
bool EmulationManagerIsInit() {
	return initialized;
}

bool EmulationManagerInit() {
	if (EmulationManagerIsInit()) return false;
	bool error = false;
	error |= CPUInit();

	if (error) {
		initialized = false;
		return true;
	}
	initialized = true;
	return false;
}

bool EmulationManagerDeInit() {
	if (!EmulationManagerIsInit()) return false;
	bool error = false;
	error |= CPUDeInit();

	if (error) {
		initialized = true;
		return true;
	}
	initialized = false;
	return false;
}

void EmulationManagerRunFrame() {
	CPUExecute(CPU_CYCLES_PER_FRAME);
}

//TODO: clean up, maybe make ROMManager?
bool EmulationManagerLoadiNES(const char* filename) {
	FILE* rom = fopen(filename, "r");
	if (!rom) {
		return true;
	}
	fseek(rom, 0L, SEEK_END);
	unsigned int rom_size = ftell(rom);
	fseek(rom, 0L, SEEK_SET);
	unsigned char* rom_mem = malloc(rom_size);
	fread((void*)rom_mem, rom_size, 1, rom);

	OSReport("%02X %02X %02X %02X", rom_mem[0], rom_mem[1], rom_mem[2], rom_mem[3]);

	//LiteNES is licenced under something.
	//Yes, I really did reuse this code.

	if (memcmp(rom_mem, "NES\x1A", 4)) {
		return true;
	}

	unsigned short mmc_id = ((*((unsigned short*)(rom_mem + 6)) & 0xF0) >> 4);

	int prg_size = *(rom_mem + 4) * 0x4000;
	static unsigned char buf[1048576];
	memcpy(buf, rom_mem + 14, prg_size); //TODO 14 is a magical number
	if (mmc_id == 0 || mmc_id == 3) {
		// if there is only one PRG block, we must repeat it twice
		if (*(rom_mem + 4) == 1) {
			for (int i = 0x8000; i < 0x8000 + 0x4000; i++) {
				CPUWriteMemoryRaw(i, buf[i]);
			}
			for (int i = 0xC000; i < 0xC000 + 0x4000; i++) {
				CPUWriteMemoryRaw(i, buf[i]);
			}
		}
		else {
			for (int i = 0x8000; i < 0x8000 + 0x8000; i++) {
				CPUWriteMemoryRaw(i, buf[i]);
			}
		}
	}
	else {
		return true;
	}

	// Copying CHR pages into MMC and PPU
	/*int i;
	for (i = 0; i < *(rom_mem + 5); i++) {
		romread(rom, buf, 0x2000);
		mmc_append_chr_rom_page(buf);

		if (i == 0) {
			ppu_copy(0x0000, buf, 0x2000);
		}
	}*/

	return 0;
}
