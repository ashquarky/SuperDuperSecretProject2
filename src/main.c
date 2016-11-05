/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

#include <coreinit/core.h>
#include <coreinit/debug.h>
#include <coreinit/foreground.h>
#include <proc_ui/procui.h>

#include "emu/EmulationManager.h"

//Main application loop, called each frame.
//Retrun true to quit app.
//Generally, "false" = all good, "true" = error.
bool MainLoop() {
	return false;
}

bool AppIsInit = false;
bool InitApp() {
	if (AppIsInit) return false;
	bool error = false;
	error |= EmulationManagerInit();

	if (error) {
		AppIsInit = false;
		//OSFatal is perfectly acceptable in this situation
		OSFatal("Could not initialize app!");
		return true;
	}
	AppIsInit = true;
	return false;
}

bool DeInitApp() {
	if (!AppIsInit) return false;
	bool error = false;
	error |= EmulationManagerDeInit();

	if (error) {
		AppIsInit = true;
		OSFatal("Could not deinitialize app!");
		return true;
	}
	AppIsInit = false;
	return false;
}

//Main ProcUI loop, handles many cool things
void RunApplication() {
	while (1) {
		if(!OSIsMainCore()) {
			ProcUISubProcessMessages(true);
		}
		else {
			ProcUIStatus status = ProcUIProcessMessages(true);

			if(status == PROCUI_STATUS_IN_FOREGROUND) { //Run application
				if (!AppIsInit) InitApp();
				if (MainLoop()) break;
				//TODO: GX2WaitForVsync();
			} else if(status == PROCUI_STATUS_RELEASE_FOREGROUND) { //Clean up foreground stuff
				if (AppIsInit) DeInitApp();
				ProcUIDrawDoneRelease();
			} else if(status == PROCUI_STATUS_EXITING) { //Get ready to exit
				if (AppIsInit) DeInitApp();
				ProcUIShutdown();
				break;
			}
		}
	}
}

//TODO learn about this function, when it's called ETC
void SaveCallback() {
	OSSavesDone_ReadyToRelease();
}

int main(int argc, char **argv) {
	ProcUIInit(&SaveCallback);
	RunApplication();
	return 0;
}
