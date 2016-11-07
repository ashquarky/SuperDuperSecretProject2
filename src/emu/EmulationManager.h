/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

//EmulationManager.c - Manages the NES emulator core

#include <stdbool.h>

#ifndef _EMULATION_MANAGER_H_
#define _EMULATION_MANAGER_H_

bool EmulationManagerLoadiNES(const char* filename);
bool EmulationManagerInit();
bool EmulationManagerIsInit();
bool EmulationManagerDeInit();
void EmulationManagerRunFrame();

#endif //_EMULATION_MANAGER_H_
