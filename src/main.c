/*	SuperDuperSecretProject2 - An NES Emulator for the Wii U
	https://github.com/QuarkTheAwesome/SuperDuperSecretProject2
	I'd appreciate it if you didn't post this on GBATemp or anything until I think up a name */

#include <coreinit/core.h>
#include <coreinit/debug.h>
#include <coreinit/foreground.h>
#include <proc_ui/procui.h>

//Main application loop, called each frame.
//Retrun true to quit app.
bool MainLoop() {
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
				if (MainLoop()) break;
				//TODO: GX2WaitForVsync();
			} else if(status == PROCUI_STATUS_RELEASE_FOREGROUND) { //Clean up foreground stuff
				ProcUIDrawDoneRelease();
			} else if(status == PROCUI_STATUS_EXITING) { //Get ready to exit
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
