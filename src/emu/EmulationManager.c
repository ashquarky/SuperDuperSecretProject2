/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

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

void EmulationManagerRunFrame() {
	CPUExecute(CPU_CYCLES_PER_FRAME);
}